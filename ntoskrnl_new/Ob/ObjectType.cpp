
#include "Obp.hpp"

namespace Ob {

extern "C" {

POBJECT_TYPE ObpTypeObjectType;

} // extern "C"

LONG OBJECT_TYPE::NextObjectIndex = 0;
POBJECT_TYPE OBJECT_TYPE::ObjectTypeTable[MAX_OBJECT_TYPES];

INIT_FUNCTION
VOID
OBJECT_TYPE::InitializeClass (
    VOID)
{
    OBJECT_TYPE_INITIALIZER TypeInitializer;
    ULONG PoolCharge;

    /* Calculate the full size for the type object */
    PoolCharge = sizeof(OBJECT_TYPE) +
                 sizeof(OBJECT_HEADER) +
                 sizeof(OBJECT_HEADER_CREATOR_INFO) +
                 sizeof(OBJECT_HEADER_NAME_INFO);

    /* Setup the type initializer */
    TypeInitializer.Length = sizeof(OBJECT_TYPE_INITIALIZER);
    TypeInitializer.ObjectTypeFlags = 0;
    TypeInitializer.MaintainTypeList = 1;
    TypeInitializer.ObjectTypeCode = 0;
    TypeInitializer.InvalidAttributes = 0x100;
    TypeInitializer.GenericMapping.GenericRead = READ_CONTROL;
    TypeInitializer.GenericMapping.GenericWrite = READ_CONTROL;
    TypeInitializer.GenericMapping.GenericExecute = READ_CONTROL;
    TypeInitializer.GenericMapping.GenericAll = STANDARD_RIGHTS_REQUIRED|1;
    TypeInitializer.ValidAccessMask = STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|1;
    TypeInitializer.RetainAccess = 0;
    TypeInitializer.PoolType = NonPagedPool;
    TypeInitializer.DefaultPagedPoolCharge = 0;
    TypeInitializer.DefaultNonPagedPoolCharge = PoolCharge;
    TypeInitializer.DumpProcedure = NULL;
    TypeInitializer.OpenProcedure = NULL;
    TypeInitializer.CloseProcedure = NULL;
    TypeInitializer.DeleteProcedure = NULL;
    TypeInitializer.ParseProcedure = NULL;
    TypeInitializer.SecurityProcedure = SeDefaultObjectMethodEx;
    TypeInitializer.QueryNameProcedure = NULL;
    TypeInitializer.OkayToCloseProcedure = NULL;
    TypeInitializer.WaitObjectFlagMask = 0;
    TypeInitializer.WaitObjectFlagOffset = 0;
    TypeInitializer.WaitObjectPointerOffset = 0;

    /* Allocate the type object type */
    ObpTypeObjectType = new OBJECT_TYPE(&TypeInitializer);
    if (ObpTypeObjectType == NULL)
    {
        NT_ASSERT(FALSE);
    }

    /* Insert the type object type into itself */
    ObpTypeObjectType->InsertObject(ObpTypeObjectType);

}


void*
OBJECT_TYPE::operator new (
    _In_ size_t Size)
{
    return OBJECT::operator new(Size,
                                NonPagedPool,
                                'TjbO',
                                OBJECT::CREATOR_INFO_MASK | OBJECT::NAME_INFO_MASK);
}

OBJECT_TYPE::OBJECT_TYPE (
    POBJECT_TYPE_INITIALIZER TypeInitializer)
        : OBJECT(TypeObjectTypeIndex)
{
    POBJECT_HEADER_NAME_INFO NameInfo;
    PUNICODE_STRING TypeName;

    NameInfo = GetNameInfo();
    TypeName = &NameInfo->Name;

    /* Construct a key / pooltag from the type name */
    ((PCHAR)&_Key)[0] = (TypeName->Length >= 2) ? (CHAR)TypeName->Buffer[0] : ' ';
    ((PCHAR)&_Key)[1] = (TypeName->Length >= 4) ? (CHAR)TypeName->Buffer[1] : ' ';
    ((PCHAR)&_Key)[2] = (TypeName->Length >= 6) ? (CHAR)TypeName->Buffer[2] : ' ';
    ((PCHAR)&_Key)[3] = (TypeName->Length >= 8) ? (CHAR)TypeName->Buffer[3] : ' ';

    /* Initialize the basic type fields */
    InitializeListHead(&_TypeList);
    InitializeListHead(&_CallbackList);
    ExInitializePushLock(&_TypeLock);
    _Name = *TypeName;
    _DefaultObject = 0; // FIXME
    _TotalNumberOfObjects = 0;
    _HighWaterNumberOfObjects = 0;
    _TotalNumberOfHandles = 0;
    _HighWaterNumberOfHandles = 0;

    /* Copy the type info */
    _TypeInfo = *TypeInitializer;

    /* Get a type index */
    _Index = InterlockedIncrement(&NextObjectIndex);
    ASSERT(_Index < MAX_OBJECT_TYPES);

    /* Set the global object type table entry */
    ObjectTypeTable[_Index] = this;

}

OBJECT_TYPE::~OBJECT_TYPE (
    VOID)
{
    /* This cannot happen! */
    NT_ASSERT(FALSE);
}

NTSTATUS
OBJECT_TYPE::InsertObject (
    _In_ POBJECT Object)
{
    POBJECT_HEADER_CREATOR_INFO CreatorInfo;

    /* Get the object's creator info header */
    CreatorInfo = Object->GetCreatorInfo();
    if (CreatorInfo == NULL)
    {
        return STATUS_UNSUCCESSFUL;
    }

    /* Lock the object type */
    ExAcquirePushLockExclusive(&_TypeLock);

    /* Insert the object into the type list */
    InsertTailList(&_TypeList, &CreatorInfo->TypeList);

    /* Increment number of objects */
    _TotalNumberOfObjects++;
    if (_TotalNumberOfObjects > _HighWaterNumberOfObjects)
    {
        _HighWaterNumberOfObjects = _TotalNumberOfObjects;
    }

    /* Unlock the object type */
    ExReleasePushLockExclusive(&_TypeLock);

    return STATUS_SUCCESS;
}

VOID
OBJECT_TYPE::RemoveObject (
    _In_ POBJECT Object)
{
    POBJECT_HEADER_CREATOR_INFO CreatorInfo;

    /* Get the object's creator info header */
    CreatorInfo = Object->GetCreatorInfo();
    NT_ASSERT(CreatorInfo != NULL);

    /* Lock the object type */
    ExAcquirePushLockExclusive(&_TypeLock);

    /* Remove the object from the type list */
    RemoveEntryList(&CreatorInfo->TypeList);

    /* Decrement number of objects */
    _TotalNumberOfObjects++;

    /* Unlock the object type */
    ExReleasePushLockExclusive(&_TypeLock);
}

// ntosifs.h
extern "C"
NTSTATUS
NTAPI
ObCreateObjectTypeEx (
    _In_ PUNICODE_STRING TypeName,
    _In_ POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ LONG_PTR WaitObjectInfo,
    _Outptr_ POBJECT_TYPE *ObjectType);

// ntosifs.h
extern "C"
NTSTATUS
NTAPI
ObCreateObjectType (
    _In_ PUNICODE_STRING TypeName,
    _In_ POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Outptr_ POBJECT_TYPE *ObjectType)
{
    POBJECT_TYPE ObjectType;
    NTSTATUS Status;

    /* Allocate a type object */
    ObjectType = new OBJECT_TYPE(ObjectTypeInitializer);
    if (ObjectType == NULL)
    {
        *OutObjectType = NULL;
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /// set ObpTypeObjectType as type
    /// set type name

    /* Insert it into the Type object directory */
    Status = 0;// TypeDirectoryObject->InsertEntry(ObjectType);
    if (!NT_SUCCESS(Status))
    {
        /* Delete the type object and return failure status */
        ObjectType->Release();
        *OutObjectType = NULL;
        return Status;
    }

    *OutObjectType = ObjectType;
    return STATUS_SUCCESS;
}

extern "C"
POBJECT_TYPE
NTAPI
ObGetObjectType (
    _In_ PVOID Object)
{
    __debugbreak();
    return NULL;
}

}; // namespace Ob

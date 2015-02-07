
#include "Obp.hpp"

namespace Ob {

extern "C" {

POBJECT_TYPE ObpTypeObjectType;

} // extern "C"

LONG OBJECT_TYPE::NextObjectIndex = -1;
POBJECT_TYPE OBJECT_TYPE::ObjectTypeTable[MAX_OBJECT_TYPES];

INIT_FUNCTION
VOID
OBJECT_TYPE::InitializeClass (
    VOID)
{
    static const UNICODE_STRING TypeName = RTL_CONSTANT_STRING(L"Type");
    OBJECT_TYPE_INITIALIZER TypeInitializer;
    ULONG PoolCharge;

    /* Calculate the full size for the type object */
    PoolCharge = sizeof(OBJECT_TYPE) +
                 sizeof(OBJECT_HEADER) +
                 sizeof(OBJECT_HEADER_CREATOR_INFO) +
                 sizeof(OBJECT_HEADER_NAME_INFO);

    /* Setup the type initializer */
    RtlZeroMemory(&TypeInitializer, sizeof(TypeInitializer));
    TypeInitializer.Length = sizeof(TypeInitializer);
    TypeInitializer.MaintainTypeList = 1;
    TypeInitializer.InvalidAttributes = 0x100;
    TypeInitializer.GenericMapping.GenericRead = READ_CONTROL;
    TypeInitializer.GenericMapping.GenericWrite = READ_CONTROL;
    TypeInitializer.GenericMapping.GenericExecute = READ_CONTROL;
    TypeInitializer.GenericMapping.GenericAll = STANDARD_RIGHTS_REQUIRED|1;
    TypeInitializer.ValidAccessMask = STANDARD_RIGHTS_ALL|1;
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

    /* Create the type object type */
    ObpTypeObjectType = new OBJECT_TYPE(&TypeName, &TypeInitializer);
    if (ObpTypeObjectType == NULL)
    {
        NT_ASSERT(FALSE);
    }

    /* Insert the type object type into itself */
    ObpTypeObjectType->InsertObject(ObpTypeObjectType);

}


void*
OBJECT_TYPE::operator new (
    _In_ size_t Size) throw()
{
    return OBJECT::Allocate(NonPagedPool,
                            Size,
                            'TjbO',
                            TypeObjectTypeIndex,
                            CREATOR_INFO_MASK | NAME_INFO_MASK);
}

OBJECT_TYPE::OBJECT_TYPE (
    _In_ PCUNICODE_STRING TypeName,
    _In_ POBJECT_TYPE_INITIALIZER TypeInitializer)
        : OBJECT(TypeName)
{
    PCHAR KeyString;

    /* Construct a key / pooltag from the type name */
    KeyString = (PCHAR)&_Key;
    KeyString[0] = (TypeName->Length >= 2) ? (CHAR)TypeName->Buffer[0] : ' ';
    KeyString[1] = (TypeName->Length >= 4) ? (CHAR)TypeName->Buffer[1] : ' ';
    KeyString[2] = (TypeName->Length >= 6) ? (CHAR)TypeName->Buffer[2] : ' ';
    KeyString[3] = (TypeName->Length >= 8) ? (CHAR)TypeName->Buffer[3] : ' ';

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
    NT_ASSERT(_Index < MAX_OBJECT_TYPES);

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
OBJECT_TYPE::CreateObject (
    _Out_ PVOID *OutObject,
    _In_ SIZE_T ObjectSize,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ SIZE_T PagedPoolCharge,
    _In_opt_ SIZE_T NonPagedPoolCharge)
{
    UCHAR InfoMask;
    POBJECT Object;

    InfoMask = 0;
    if ((PagedPoolCharge != 0) || (NonPagedPoolCharge != 0))
    {
        InfoMask |= QUOTA_INFO_MASK;
    }

    if (ObjectAttributes->ObjectName->Length != 0)
    {
        InfoMask |= NAME_INFO_MASK;
    }

    /// \todo Handle PagedPoolCharge and NonPagedPoolCharge

    if (_TypeInfo.MaintainTypeList)
    {
        InfoMask |= CREATOR_INFO_MASK;
    }

    /* Allocate the object */
    Object = (POBJECT)OBJECT::Allocate(_TypeInfo.PoolType,
                              ObjectSize,
                              _Key,
                              _Index,
                              InfoMask);
    if (Object == NULL)
    {
        *OutObject = NULL;
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Check if a type list is to be maintained */
    if (_TypeInfo.MaintainTypeList)
    {
        /* Insert the header into the type's list */
        InsertObject(Object);
    }

    *OutObject = Object;
    return STATUS_SUCCESS;
}

VOID
OBJECT_TYPE::InsertObject (
    _In_ POBJECT Object)
{
    POBJECT_HEADER_CREATOR_INFO CreatorInfo;

    /* Get the object's creator info header */
    CreatorInfo = Object->GetCreatorInfo();
    NT_ASSERT(CreatorInfo != NULL);

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
    _Outptr_ POBJECT_TYPE *OutObjectType)
{
    POBJECT_TYPE ObjectType;
    NTSTATUS Status;
__debugbreak();

    Status = ObpTypeObjectType->CreateObject((PVOID*)&ObjectType,
                                             sizeof(OBJECT_TYPE),
                                             NULL, //ObjectAttributes,
                                             0, //PagedPoolCharge,
                                             0); //NonPagedPoolCharge)

    /* Allocate a type object */
    ObjectType = new OBJECT_TYPE(TypeName, ObjectTypeInitializer);
    if (ObjectType == NULL)
    {
        *OutObjectType = NULL;
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /// set type name

    /* Insert it into the Type object directory */
    Status = STATUS_SUCCESS;// TypeDirectoryObject->InsertEntry(ObjectType);
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

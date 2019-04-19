/*
 * PROJECT:         ReactOS Kernel
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            ntoskrnl/ob/init.c
 * PURPOSE:         Ob init functions
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <ntoskrnl.h>
#include "ob_internal.h"

#define NDEBUG
#include <debug.h>


/* GLOBALS *******************************************************************/

POBJECT_TYPE ObpTypeObjectType;
POBJECT_TYPE ObpDirectoryObjectType;
POBJECT_DIRECTORY ObpRootDirectoryObject;
POBJECT_DIRECTORY ObpTypeDirectoryObject;
PDEVICE_MAP NTSYSAPI ObSystemDeviceMap;
KGUARDED_MUTEX ObpDeviceMapLock;

LONG ObpLastObjectIndex = 2; /* 0, 1 are reserved */
POBJECT_TYPE ObpObjectType[MAX_OBJECT_TYPES];
UCHAR ObpObjectHeaderInfoSize[1 << MAX_HEADER_INFO];

/* FUNCTIONS *****************************************************************/


/*! \name ObpDuplicateString
 *
 *  \brief Creates a copy of a given UNICODE_STRING, allocating the buffer
 *      from paged pool.
 *
 *  \param [out] Destination
 *      Pointer to a UNICODE_STRING, that receives the copied string.
 *
 *  \param [in] Source
 *      Pointer to a UNICODE_STRING that contains the string to be copied.
 *
 *  \param [in] AccessMode
 *      Specifies the access mode for the source string: KernelMode or UserMode
 *
 *  \return
 *      The result status of the operation. Either STATUS_SUCCESS or an
 *      exception code, when the copy caused an exception.
 *
 *  \remarks
 *      If AccessMode is UserMode, the Source pointer and the string buffer
 *      are probed. The actual copy is protected with SEH.
 */
NTSTATUS
NTAPI
ObpDuplicateString(
    OUT PUNICODE_STRING Destination,
    IN PUNICODE_STRING Source,
    IN KPROCESSOR_MODE AccessMode)
{
    /* Check for user mode buffer */
    if (AccessMode != KernelMode)
    {
        _SEH2_TRY
        {
            /* Probe the structure and the buffer before accessing it */
            ProbeForRead(Source, sizeof(UNICODE_STRING), sizeof(PVOID));
            ProbeForRead(Source->Buffer, Source->Length, sizeof(WCHAR));
            Destination->Length = Source->Length;
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            _SEH2_YIELD(return _SEH2_GetExceptionCode());
        }
        _SEH2_END
    }
    else
    {
        /* Kernel mode buffer, just get the length */
        Destination->Length = Source->Length;
    }

    /* Allocate the string buffer from paged pool */
    Destination->MaximumLength = Destination->Length + sizeof(UNICODE_NULL);
    Destination->Buffer = ExAllocatePoolWithTag(PagedPool,
                                                Destination->MaximumLength,
                                                'mNbO');
    if (!Destination->Buffer)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Again protected with SEH... */
    _SEH2_TRY
    {
        /* Copy the string */
        RtlCopyMemory(Destination->Buffer, Source->Buffer, Source->Length);
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        /* An exception happened, cleanup and return failure */
        ExFreePool(Destination->Buffer);
        _SEH2_YIELD(return _SEH2_GetExceptionCode());
    }
    _SEH2_END

    return STATUS_SUCCESS;
}

/*! \name ObpInitializeHeaderOffsets
 *
 *  \brief Initializes the static offset array ObpObjectHeaderInfoSize that
 *      is used for the fast calculation of the location of the different
 *      header info structures, based on the objects InfoMask.
 *
 *  \remarks The offset is the negative byte offset from the object header.
 *      The index is calculated by masking all bits higher than the desired
 *      header's mask from the objects InfoMask.
 */
static
VOID
INIT_FUNCTION
ObpInitializeHeaderOffsets (
    VOID)
{
    UCHAR i, Offset;

    /* Loop through all possible mask combinations */
    for (i = 0; i < 1 << MAX_HEADER_INFO; i++)
    {
        /* Calculate the offset */
        Offset = 0;
        if (i & OBJECT_HEADER_CREATOR_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_CREATOR_INFO);
        if (i & OBJECT_HEADER_NAME_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_NAME_INFO);
        if (i & OBJECT_HEADER_PROCESS_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_PROCESS_INFO);
        if (i & OBJECT_HEADER_QUOTA_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_QUOTA_INFO);
        if (i & OBJECT_HEADER_HANDLE_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_HANDLE_INFO);
        ObpObjectHeaderInfoSize[i] = Offset;
    }
}


/*! \name ObpCreateTypeObjectType
 *
 *  \brief Creates the Type object type
 *
 *  \remarks
 *      The object type is created and inserted into the global table, but
 *      Its not yet put into the ObjectTypes directory, since that doesn't
 *      exist yet.
 */
NTSTATUS
NTAPI
INIT_FUNCTION
ObpCreateTypeObjectType(VOID)
{
    UNICODE_STRING TypeName = RTL_CONSTANT_STRING(L"Type");
    POBJECT_TYPE ObjectType;
    POBJECT_HEADER ObjectHeader;
    POBJECT_HEADER_CREATOR_INFO CreatorInfo;
    POBJECT_HEADER_NAME_INFO NameInfo;
    PVOID Pointer;
    ULONG AllocSize;
    NTSTATUS Status;
    UCHAR TypeIndex;

    /* Calculate the full size we need for this object */
    AllocSize = sizeof(OBJECT_TYPE) +
                sizeof(OBJECT_HEADER) +
                sizeof(OBJECT_HEADER_CREATOR_INFO) +
                sizeof(OBJECT_HEADER_NAME_INFO);

    /* Now allocate the structure */
    Pointer = ExAllocatePoolWithTag(NonPagedPool, AllocSize, 'TjbO');
    if (!Pointer)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Get pointers to the structures */
    NameInfo = Pointer;
    CreatorInfo = (POBJECT_HEADER_CREATOR_INFO)(NameInfo + 1);
    ObjectHeader = (POBJECT_HEADER)(CreatorInfo + 1);
    ObjectType = (POBJECT_TYPE)(&ObjectHeader->Body);

    /* Now create a name */
    Status = ObpDuplicateString(&NameInfo->Name, &TypeName, KernelMode);
    if (!NT_SUCCESS(Status))
    {
        ExFreePool(Pointer);
        return Status;
    }

    /* We don't have any directories yet */
    NameInfo->Directory = NULL;
    NameInfo->ReferenceCount = 0;

    /* Get an object type index */
    TypeIndex = (UCHAR)ObpLastObjectIndex++;

    /* Initialize the object header */
    ExInitializePushLock(&ObjectHeader->Lock);
    ObjectHeader->PointerCount = 0;
    ObjectHeader->HandleCount = 0;
    ObjectHeader->ObjectCreateInfo = NULL;
    ObjectHeader->SecurityDescriptor = NULL;
    ObjectHeader->TypeIndex = TypeIndex;
    ObjectHeader->TraceFlags = 0;
    ObjectHeader->Flags = OB_FLAG_PERMANENT |
                          OB_FLAG_KERNEL_MODE |
                          OB_FLAG_CREATE_INFO;
    ObjectHeader->InfoMask = OBJECT_HEADER_CREATOR_INFO_MASK  |
                             OBJECT_HEADER_NAME_INFO_MASK;

    /* Initialize the creator info */
    CreatorInfo->CreatorUniqueProcess = NULL;
    CreatorInfo->CreatorBackTraceIndex = 0;
    CreatorInfo->Reserved = 0;

    /* Initialize the basic type fields */
    InitializeListHead(&ObjectType->TypeList);
    InitializeListHead(&ObjectType->CallbackList);
    ExInitializePushLock(&ObjectType->TypeLock);
    ObjectType->Key = 'TjbO';
    ObjectType->Name = NameInfo->Name;
    ObjectType->Index = TypeIndex;
    ObjectType->DefaultObject = 0; // FIXME

    /* We have one object of this type: this object */
    ObjectType->TotalNumberOfObjects = 1;
    ObjectType->HighWaterNumberOfObjects = 1;
    ObjectType->TotalNumberOfHandles = 0;
    ObjectType->HighWaterNumberOfHandles = 0;

    /* Initialize the TypeInfo */
    ObjectType->TypeInfo.Length = sizeof(OBJECT_TYPE_INITIALIZER);
    ObjectType->TypeInfo.ObjectTypeFlags = 0;
    ObjectType->TypeInfo.UseDefaultObject = 1;
    ObjectType->TypeInfo.MaintainTypeList = 1;
    ObjectType->TypeInfo.SupportsObjectCallbacks = 0;
    ObjectType->TypeInfo.ObjectTypeCode = 0;
    ObjectType->TypeInfo.InvalidAttributes = 0x100;
    ObjectType->TypeInfo.GenericMapping.GenericRead = READ_CONTROL;
    ObjectType->TypeInfo.GenericMapping.GenericWrite = READ_CONTROL;
    ObjectType->TypeInfo.GenericMapping.GenericExecute = READ_CONTROL;
    ObjectType->TypeInfo.GenericMapping.GenericAll = STANDARD_RIGHTS_REQUIRED|1;
    ObjectType->TypeInfo.ValidAccessMask = STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|1;
    ObjectType->TypeInfo.RetainAccess = 0;
    ObjectType->TypeInfo.PoolType = NonPagedPool;
    ObjectType->TypeInfo.DefaultPagedPoolCharge = 0;
    ObjectType->TypeInfo.DefaultNonPagedPoolCharge = AllocSize;
    ObjectType->TypeInfo.DumpProcedure = NULL;
    ObjectType->TypeInfo.OpenProcedure = NULL;
    ObjectType->TypeInfo.CloseProcedure = NULL;
    ObjectType->TypeInfo.DeleteProcedure = NULL;
    ObjectType->TypeInfo.ParseProcedure = NULL;
    ObjectType->TypeInfo.SecurityProcedure = SeDefaultObjectMethod;
    ObjectType->TypeInfo.QueryNameProcedure = NULL;
    ObjectType->TypeInfo.OkayToCloseProcedure = NULL;

    /* Insert the type object itself into the type list */
    InsertTailList(&ObjectType->TypeList, &CreatorInfo->TypeList);

    /* Set the global object type table entry */
    ObpObjectType[TypeIndex] = ObjectType;

    /* Set the global pointer */
    ObpTypeObjectType = ObjectType;

    /* Return success */
    return STATUS_SUCCESS;
}

/*! \name ObpCreateSystemRootDirectory
 *
 *  \brief Creates the Directory object type, the root directory "\" and the
 *      "Types" subdirectory.
 *
 *  \remarks The creation of the directory type is done half-manually, since
 *      the ObCreateObjectType function cannot be used yet.
 */
NTSTATUS
NTAPI
INIT_FUNCTION
ObpCreateSystemRootDirectory(VOID)
{
    UNICODE_STRING DirectoryTypeName = RTL_CONSTANT_STRING(L"Directory");
    UNICODE_STRING RootDirectoryName = RTL_CONSTANT_STRING(L"\\");
    UNICODE_STRING TypesDirectoryName = RTL_CONSTANT_STRING(L"Types");
    POBJECT_HEADER ObjectHeader;
    POBJECT_HEADER_NAME_INFO HeaderNameInfo;
    POBJECT_TYPE ObjectType;
    NTSTATUS Status;

    /* Allocate a type object */
    Status = ObpAllocateObject(ObpTypeObjectType,
                               sizeof(OBJECT_TYPE),
                               OBJECT_HEADER_CREATOR_INFO_MASK |
                                   OBJECT_HEADER_NAME_INFO_MASK,
                               &DirectoryTypeName,
                               KernelMode,
                               (PVOID*)&ObjectType);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Get the header and name info */
    ObjectHeader = CONTAINING_RECORD(ObjectType, OBJECT_HEADER, Body);
    HeaderNameInfo = ObpGetHeaderNameInfo(ObjectHeader);

    /* Initialize the basic type fields */
    InitializeListHead(&ObjectType->TypeList);
    InitializeListHead(&ObjectType->CallbackList);
    ExInitializePushLock(&ObjectType->TypeLock);
    ObjectType->Key = 'eriD';
    ObjectType->Name = HeaderNameInfo->Name;;
    ObjectType->Index = OBJECT_HEADER_CREATOR_INFO_MASK |
                        OBJECT_HEADER_NAME_INFO_MASK;
    ObjectType->DefaultObject = 0; // FIXME
    ObjectType->TotalNumberOfObjects = 0;
    ObjectType->HighWaterNumberOfObjects = 0;
    ObjectType->TotalNumberOfHandles = 0;
    ObjectType->HighWaterNumberOfHandles = 0;

    /* Initialize the type info */
    ObjectType->TypeInfo.Length = sizeof(OBJECT_TYPE_INITIALIZER);
    ObjectType->TypeInfo.ObjectTypeFlags = 0;
    ObjectType->TypeInfo.CaseInsensitive = 1;
    ObjectType->TypeInfo.UseDefaultObject = 1;
    ObjectType->TypeInfo.SecurityRequired = 1;
    ObjectType->TypeInfo.ObjectTypeCode = 0;
    ObjectType->TypeInfo.InvalidAttributes = 0x100;
    ObjectType->TypeInfo.GenericMapping.GenericRead = 0x20003;
    ObjectType->TypeInfo.GenericMapping.GenericWrite = 0x2000c;
    ObjectType->TypeInfo.GenericMapping.GenericExecute = 0x20003;
    ObjectType->TypeInfo.GenericMapping.GenericAll = 0xf000f;
    ObjectType->TypeInfo.ValidAccessMask = 0xf000f;
    ObjectType->TypeInfo.RetainAccess = 0;
    ObjectType->TypeInfo.PoolType = PagedPool;
    ObjectType->TypeInfo.DefaultPagedPoolCharge = 0x58;
    ObjectType->TypeInfo.DefaultNonPagedPoolCharge = 0x150;
    ObjectType->TypeInfo.DumpProcedure = NULL;
    ObjectType->TypeInfo.OpenProcedure = NULL;
    ObjectType->TypeInfo.CloseProcedure = ObpCloseDirectoryObject;
    ObjectType->TypeInfo.DeleteProcedure = NULL;
    ObjectType->TypeInfo.ParseProcedure = NULL;
    ObjectType->TypeInfo.SecurityProcedure = SeDefaultObjectMethod;
    ObjectType->TypeInfo.QueryNameProcedure = NULL;
    ObjectType->TypeInfo.OkayToCloseProcedure = NULL;

    /* Save the type in a global variable */
    ObpDirectoryObjectType = ObjectType;

    /* Allocate the root directory object */
    Status = ObpAllocateObject(ObpDirectoryObjectType,
                               sizeof(OBJECT_DIRECTORY),
                               OBJECT_HEADER_CREATOR_INFO_MASK |
                                   OBJECT_HEADER_NAME_INFO_MASK,
                               &RootDirectoryName,
                               KernelMode,
                               (PVOID*)&ObpRootDirectoryObject);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Zero out the directory */
    RtlZeroMemory(ObpRootDirectoryObject, sizeof(OBJECT_DIRECTORY));

    /* Allocate the type directory object */
    Status = ObpAllocateObject(ObpDirectoryObjectType,
                               sizeof(OBJECT_DIRECTORY),
                               OBJECT_HEADER_CREATOR_INFO_MASK |
                                   OBJECT_HEADER_NAME_INFO_MASK,
                               &TypesDirectoryName,
                               KernelMode,
                               (PVOID*)&ObpTypeDirectoryObject);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Zero out the directory */
    RtlZeroMemory(ObpRootDirectoryObject, sizeof(OBJECT_DIRECTORY));

    /* Insert the types directory into the root directory */
    Status = ObpInsertDirectoryEntry(ObpRootDirectoryObject,
                                     ObpTypeDirectoryObject);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    return STATUS_SUCCESS;
}

BOOLEAN
NTAPI
INIT_FUNCTION
ObInitSystem(
    VOID)
{
    __debugbreak();

    /* Start with preparing the offset array */
    ObpInitializeHeaderOffsets();

    /* Now create the Type object type, that we need for everything else */
    if (!NT_SUCCESS(ObpCreateTypeObjectType()))
    {
        KeBugCheck(PHASE0_INITIALIZATION_FAILED);
    }

    /* Create the system root directory */
    if (!NT_SUCCESS(ObpCreateSystemRootDirectory()))
    {
        KeBugCheck(PHASE0_INITIALIZATION_FAILED);
    }

    /* Always return TRUE */
    return TRUE;
}

NTSTATUS
NTAPI
ObRegisterCallbacks (
    IN POB_CALLBACK_REGISTRATION CallbackRegistration,
    OUT PVOID *RegistrationHandle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
ObUnRegisterCallbacks (
    IN PVOID RegistrationHandle)
{
    __debugbreak();
}

USHORT
NTAPI
ObGetFilterVersion(VOID)
{
    __debugbreak();
    return 0;
}


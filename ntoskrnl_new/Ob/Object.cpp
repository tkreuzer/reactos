
#include "Obp.hpp"

namespace Ob {

UCHAR OBJECT::HeaderInfoSize[MAX_INFO_MASK + 1];

INIT_FUNCTION
VOID
OBJECT::InitializeClass (
    VOID)
{
    UCHAR i, Offset;

    /* Loop through all possible info mask combinations */
    for (i = 0; i < MAX_INFO_MASK; i++)
    {
        /* Calculate the offset */
        Offset = 0;
        if (i & CREATOR_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_CREATOR_INFO);
        if (i & NAME_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_NAME_INFO);
        if (i & PROCESS_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_PROCESS_INFO);
        if (i & QUOTA_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_QUOTA_INFO);
        if (i & HANDLE_INFO_MASK)
            Offset += sizeof(OBJECT_HEADER_HANDLE_INFO);
        HeaderInfoSize[i] = Offset;
    }
}

PVOID
OBJECT::Allocate (
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T ObjectSize,
    _In_ ULONG PoolTag,
    _In_ UCHAR TypeIndex,
    _In_ UCHAR InfoMask)
{
    POBJECT_HEADER ObjectHeader;
    POBJECT Object;
    SIZE_T HeaderSize;
    PVOID Base;

    /* Calculate the size of the headers */
    HeaderSize = HeaderInfoSize[InfoMask];
    HeaderSize += FIELD_OFFSET(OBJECT_HEADER, Body);

    /* Allocate the object */
    Base = ExAllocatePoolWithTag(PoolType, ObjectSize + HeaderSize, PoolTag);
    if (Base == NULL)
    {
        return NULL;
    }

    /* Calculate the start of the object header */
    ObjectHeader = reinterpret_cast<POBJECT_HEADER>(
        reinterpret_cast<PUCHAR>(Base) + HeaderInfoSize[InfoMask]);

    /* Initialize the object header */
    ExInitializePushLock(&ObjectHeader->Lock);
    ObjectHeader->PointerCount = 0;
    ObjectHeader->HandleCount = 0;
    ObjectHeader->TypeIndex = TypeIndex;
    ObjectHeader->TraceFlags = 0;
    ObjectHeader->InfoMask = InfoMask;
    ObjectHeader->Flags = 0;
    ObjectHeader->ObjectCreateInfo = NULL;
    ObjectHeader->SecurityDescriptor = NULL;

    /* Get a pointer to the object body */
    Object = reinterpret_cast<POBJECT>(&ObjectHeader->Body);

    /* Check if there is a creator info */
    if (ObjectHeader->InfoMask & CREATOR_INFO_MASK)
    {
        POBJECT_HEADER_CREATOR_INFO CreatorInfo = Object->GetCreatorInfo();
        CreatorInfo->CreatorUniqueProcess = 0;
        CreatorInfo->CreatorBackTraceIndex = 0;
        InitializeListHead(&CreatorInfo->TypeList);
    }

    /* Check if there is a name info */
    if (ObjectHeader->InfoMask & NAME_INFO_MASK)
    {
        POBJECT_HEADER_NAME_INFO NameInfo = Object->GetNameInfo();
        NameInfo->Directory = NULL;
        NameInfo->ReferenceCount = 0;
        NameInfo->Name.Buffer = NULL;
        NameInfo->Name.Length = 0;
        NameInfo->Name.MaximumLength = 0;
    }

    /* Check if there is a process info */
    if (ObjectHeader->InfoMask & PROCESS_INFO_MASK)
    {
        __debugbreak();
    }

    /* Check if there is a quota info */
    if (ObjectHeader->InfoMask & QUOTA_INFO_MASK)
    {
        __debugbreak();
    }

    /* Check if there is a handle info */
    if (ObjectHeader->InfoMask & HANDLE_INFO_MASK)
    {
        __debugbreak();
    }

    /* Return a pointer to the object body */
    return Object;
}

OBJECT::OBJECT (
    _In_ PCUNICODE_STRING ObjectName = NULL)
{

    if (ObjectName != NULL)
    {
        POBJECT_HEADER_NAME_INFO NameInfo = GetNameInfo();
        NT_ASSERT(NameInfo != NULL);
        NameInfo->Name = *ObjectName;
    }


}

OBJECT::~OBJECT (
    VOID)
{
    __debugbreak();
}

PVOID
OBJECT::GetHeaderInfo (
    _In_ INFO_INDEX InfoIndex)
{
    POBJECT_HEADER Header;
    UCHAR InfoMask;
    SIZE_T Offset;

    /* Get the object header */
    Header = GetObjectHeader();

    /* Check if the object has this header */
    if ((Header->InfoMask & (1 << InfoIndex)) == 0)
    {
        NT_ASSERT(FALSE);
        return NULL;
    }

    /* Calculate the effective info mask */
    InfoMask = Header->InfoMask & (MAX_INFO_MASK >> (MAX_INFO - InfoIndex));

    /* Calculate the offset to the header */
    Offset = HeaderInfoSize[InfoMask];

    /* Return the pointer to the info header */
    return static_cast<PVOID>(reinterpret_cast<PUCHAR>(Header) - Offset);
}

VOID
OBJECT::InitializeStackObjectHeader (
    _In_ POBJECT_TYPE ObjectType,
    _In_ LONG_PTR PointerCount)
{
    POBJECT_HEADER Header;

    Header = GetObjectHeader();
    RtlZeroMemory(Header, sizeof(*Header));
    Header->TypeIndex = ObjectType->GetIndex();
    Header->PointerCount = PointerCount;
}

extern "C"
VOID
NTAPI
ObInitializeStackObjectHeader(
    _Out_ PVOID ObjectBody,
    _In_ POBJECT_TYPE ObjectType,
    _In_ LONG_PTR PointerCount)
{
    POBJECT Object = reinterpret_cast<POBJECT>(ObjectBody);
    Object->InitializeStackObjectHeader(ObjectType, PointerCount);
}

extern "C"
VOID
NTAPI
ObFreeObjectCreateInfoBuffer(
    _Pre_notnull_ __drv_freesMem(Mem)
        POBJECT_CREATE_INFORMATION ObjectCreateInfo)
{
    __debugbreak();
}

extern "C"
VOID
NTAPI
ObDeleteCapturedInsertInfo (
    _In_ PVOID Object)
{
    __debugbreak();
}

static
NTSTATUS
CaptureObjectAttributes (
    _Out_ POBJECT_ATTRIBUTES CapturedObjectAttributes,
    _Out_ PUNICODE_STRING CapturedObjectName,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ KPROCESSOR_MODE ObjectAttributesAccessMode)
{
    PUNICODE_STRING ObjectName;
    PWCHAR _SEH2_VOLATILE Buffer = NULL;

    __try
    {
        if (ObjectAttributesAccessMode != KernelMode)
            ProbeForRead(ObjectAttributes, sizeof(*ObjectAttributes), 1);

        *CapturedObjectAttributes = *ObjectAttributes;

        /* Check if there is an object name */
        ObjectName = CapturedObjectAttributes->ObjectName;
        if (ObjectName != NULL)
        {
            if (ObjectAttributesAccessMode != KernelMode)
                ProbeForRead(ObjectName, sizeof(*ObjectName), 1);

            /* Allocate a buffer for the name (this is always paged pool) */
            Buffer = static_cast<PWCHAR>(ExAllocatePoolWithTag(PagedPool,
                                           ObjectName->Length + sizeof(WCHAR),
                                           'mNbO'));
            if (Buffer == NULL)
            {
                return STATUS_INSUFFICIENT_RESOURCES;
            }

            /* Copy the buffer and set the new buffer */
            RtlCopyMemory(Buffer, ObjectName->Buffer, ObjectName->Length);
            Buffer[ObjectName->Length / sizeof(WCHAR)] = UNICODE_NULL;

            /* Initialize the captured object name string */
            CapturedObjectName->Buffer = Buffer;
            CapturedObjectName->Length = ObjectName->Length;
            CapturedObjectName->MaximumLength = ObjectName->Length + sizeof(WCHAR);

            /* Set the captured object name */
            CapturedObjectAttributes->ObjectName = CapturedObjectName;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        if (Buffer != NULL)
        {
            ExFreePoolWithTag(Buffer, 'mNbO');
        }

        return GetExceptionCode();
    }
    __endtry;

    if (CapturedObjectAttributes->SecurityDescriptor != NULL)
    {
        __debugbreak();
#if 0
        Status = SeCaptureSecurityDescriptor(CapturedObjectAttributes->SecurityDescriptor,
                                             ObjectAttributesAccessMode,
                                             PoolType,
                                             TRUE,
                                             &CapturedSecurityDescriptor);
        if (!NT_SUCCESS(Status))
        {
        }

        CapturedObjectAttributes->SecurityDescriptor = CapturedSecurityDescriptor;
#endif
    }

    if (CapturedObjectAttributes->SecurityQualityOfService != NULL)
    {
        __debugbreak();
    }

    return STATUS_SUCCESS;
}

static
VOID
FreeCapturedObjectAttributes (
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    if (ObjectAttributes->ObjectName != NULL)
    {
        ExFreePool(ObjectAttributes->ObjectName->Buffer);
    }
}

// ntosifs.h
extern "C"
NTSTATUS
NTAPI
ObCreateObject (
    _In_ KPROCESSOR_MODE ProbeMode,
    _In_ ::POBJECT_TYPE ObjectTypePtr,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ KPROCESSOR_MODE OwnershipMode,
    _Inout_opt_ PVOID ParseContext,
    _In_ ULONG ObjectBodySize,
    _In_ ULONG PagedPoolCharge,
    _In_ ULONG NonPagedPoolCharge,
    _Outptr_ PVOID *OutObject)
{
    POBJECT_TYPE ObjectType = reinterpret_cast<POBJECT_TYPE>(ObjectTypePtr);
    OBJECT_ATTRIBUTES CapturedObjectAttributes;
    UNICODE_STRING CapturedObjectName;
    NTSTATUS Status;

    __debugbreak();

    /* Check if we have object attributes */
    if (ObjectAttributes != NULL)
    {
        /* Capture object attributes */
        Status = CaptureObjectAttributes(&CapturedObjectAttributes,
                                         &CapturedObjectName,
                                         ObjectAttributes,
                                         ProbeMode);
        if (!NT_SUCCESS(Status))
        {
            __debugbreak();
            return Status;
        }

        /* Use the captured object attributes */
        ObjectAttributes = &CapturedObjectAttributes;
    }

    /* Call the object type's CreateObject method */
    Status = ObjectType->CreateObject(OutObject,
                                      ObjectBodySize,
                                      ObjectAttributes,
                                      PagedPoolCharge,
                                      NonPagedPoolCharge);
    if (!NT_SUCCESS(Status))
    {
        __debugbreak();

        if (ObjectAttributes != NULL)
            FreeCapturedObjectAttributes(&CapturedObjectAttributes);

        *OutObject = NULL;
        return Status;
    }

    /* Initialize the object */
    //new(*OutObject) OBJECT;

    return STATUS_SUCCESS;
}

extern "C"
PVOID
NTAPI
ObQueryNameInfo (
    _In_ PVOID ObjectPtr)
{
    POBJECT Object = static_cast<POBJECT>(ObjectPtr);
    return Object->GetNameInfo();
}

extern "C"
VOID
NTAPI
ObMakeTemporaryObject (
    _In_ PVOID Object)
{
    *(PVOID*)Object = new FAST_REF(NULL);
    __debugbreak();
}

}; // namespace Ob

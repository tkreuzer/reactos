
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

OBJECT::~OBJECT (
    VOID)
{
}

POBJECT
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
    ObjectHeader->InfoMask = InfoMask;
    ObjectHeader->ObjectCreateInfo = NULL;
    ObjectHeader->SecurityDescriptor = NULL;

    /* Get a pointer to the object */
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

    /* Return the pointer to the object body! */
    return Object;
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
    return reinterpret_cast<void*>(reinterpret_cast<PUCHAR>(Header) - Offset);
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

// ntosifs.h
extern "C"
NTSTATUS
NTAPI
ObCreateObject (
    _In_ KPROCESSOR_MODE ProbeMode,
    _In_ POBJECT_TYPE ObjectType,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ KPROCESSOR_MODE OwnershipMode,
    _Inout_opt_ PVOID ParseContext,
    _In_ ULONG ObjectBodySize,
    _In_ ULONG PagedPoolCharge,
    _In_ ULONG NonPagedPoolCharge,
    _Outptr_ PVOID *Object)
{
    NTSTATUS Status;

    __debugbreak();

    // Capture object attributes


    Status = ObjectType->CreateObject(Object,
                                      ObjectSize,
                                      PagedPoolCharge,
                                      NonPagedPoolCharge);

    return STATUS_NOT_IMPLEMENTED;
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
    __debugbreak();
}

}; // namespace Ob

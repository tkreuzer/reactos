
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

void*
OBJECT::operator new (
    _In_ size_t DefaultSize,
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T ObjectSize,
    _In_ ULONG PoolTag,
    _In_ UCHAR InfoMask)
{
    POBJECT_HEADER ObjectHeader;
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

    /// This is pretty hacky, but works...
    ObjectHeader = reinterpret_cast<POBJECT_HEADER>(
        reinterpret_cast<PUCHAR>(Base) + HeaderInfoSize[InfoMask]);
    ObjectHeader->InfoMask = InfoMask;

    /* Return the pointer to the object body! */
    return reinterpret_cast<void*>(reinterpret_cast<PUCHAR>(Base) + HeaderSize);
}

OBJECT::OBJECT (
    _In_ UCHAR TypeIndex)
{
    POBJECT_HEADER ObjectHeader;

    /* Initialize the object header */
    ObjectHeader = GetObjectHeader();
    ExInitializePushLock(&ObjectHeader->Lock);
    ObjectHeader->PointerCount = 0;
    ObjectHeader->HandleCount = 0;
    ObjectHeader->TypeIndex = TypeIndex;
    ObjectHeader->TraceFlags = 0;
    ObjectHeader->Flags = 0;
    //ObjectHeader->InfoMask = InfoMask; /// currently set by operator new
    ObjectHeader->ObjectCreateInfo = NULL;
    ObjectHeader->SecurityDescriptor = NULL;

    /* Check if there is a creator info */
    if (ObjectHeader->InfoMask & CREATOR_INFO_MASK)
    {
        POBJECT_HEADER_CREATOR_INFO CreatorInfo = GetCreatorInfo();
        CreatorInfo->CreatorUniqueProcess = 0;
        CreatorInfo->CreatorBackTraceIndex = 0;
        InitializeListHead(&CreatorInfo->TypeList);
#if 0
        /* Check if a type list is to be maintained */
        if (ObjectType->TypeInfo.MaintainTypeList)
        {
            /* Insert the header into the object type's list */
            ExAcquirePushLockExclusive(&ObjectType->TypeLock);
            InsertTailList(&ObjectType->TypeList, &CreatorInfo->TypeList);
            ExReleasePushLockExclusive(&ObjectType->TypeLock);
        }
#endif
    }

    /* Check if there is a name info */
    if (ObjectHeader->InfoMask & NAME_INFO_MASK)
    {
        POBJECT_HEADER_NAME_INFO NameInfo = GetNameInfo();
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

}

OBJECT::~OBJECT (
    VOID)
{
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
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
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

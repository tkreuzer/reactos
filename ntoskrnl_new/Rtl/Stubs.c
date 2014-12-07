
#include <ntifs.h>
#include <pseh/pseh2.h>

typedef struct _RTL_ATOM_TABLE *PRTL_ATOM_TABLE;
typedef struct _RTL_ATOM_TABLE_ENTRY *PRTL_ATOM_TABLE_ENTRY;
typedef struct _HEAP_LOCK *PHEAP_LOCK;

SIZE_T RtlpAllocDeallocQueryBufferSize = 128;
BOOLEAN LdrpShutdownInProgress;
HANDLE LdrpShutdownThreadId;

/// SList:


VOID
FASTCALL
CHECK_PAGED_CODE_RTL(char *file, int line)
{
    __debugbreak();
}

struct _LDR_RESOURCE_INFO;

NTSTATUS
find_entry (
    PVOID BaseAddress,
    struct _LDR_RESOURCE_INFO *info,
    ULONG level,
    void **ret,
    int want_dir)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
NTAPI
RtlpGetStackLimits(PULONG_PTR LowLimit,
PULONG_PTR HighLimit)
{
    __debugbreak();
}


BOOLEAN
NTAPI
RtlpCheckForActiveDebugger(VOID)
{
    return 0;
}

BOOLEAN
NTAPI
RtlpSetInDbgPrint (
    VOID)
{
    /* Nothing to set in kernel mode */
    return FALSE;
}

VOID
NTAPI
RtlpClearInDbgPrint (
    VOID)
{
    /* Nothing to clear in kernel mode */
}

NTSTATUS
RtlpInitAtomTableLock(PRTL_ATOM_TABLE AtomTable)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

VOID
RtlpDestroyAtomTableLock(PRTL_ATOM_TABLE AtomTable)
{
    __debugbreak();
}

BOOLEAN
RtlpLockAtomTable(PRTL_ATOM_TABLE AtomTable)
{
    return FALSE;
}

VOID
RtlpUnlockAtomTable(PRTL_ATOM_TABLE AtomTable)
{
    __debugbreak();
}

BOOLEAN
RtlpCreateAtomHandleTable(PRTL_ATOM_TABLE AtomTable)
{
    __debugbreak();
    return FALSE;
}

VOID
RtlpDestroyAtomHandleTable(PRTL_ATOM_TABLE AtomTable)
{
    __debugbreak();
}

PRTL_ATOM_TABLE
RtlpAllocAtomTable(ULONG Size)
{
    __debugbreak();
    return NULL;
}

VOID
RtlpFreeAtomTable(PRTL_ATOM_TABLE AtomTable)
{
    __debugbreak();
}

PRTL_ATOM_TABLE_ENTRY
RtlpAllocAtomTableEntry(ULONG Size)
{
    __debugbreak();
    return NULL;
}

VOID
RtlpFreeAtomTableEntry(PRTL_ATOM_TABLE_ENTRY Entry)
{
    __debugbreak();
}

BOOLEAN
RtlpCreateAtomHandle(PRTL_ATOM_TABLE AtomTable, PRTL_ATOM_TABLE_ENTRY Entry)
{
    __debugbreak();
    return FALSE;
}

PRTL_ATOM_TABLE_ENTRY
RtlpGetAtomEntry(PRTL_ATOM_TABLE AtomTable, ULONG Index)
{
    __debugbreak();
    return NULL;
}

VOID
RtlpFreeAtomHandle(PRTL_ATOM_TABLE AtomTable, PRTL_ATOM_TABLE_ENTRY Entry)
{
    __debugbreak();
}

PVOID
NTAPI
RtlpAllocateMemory (
    _In_ ULONG Bytes,
    _In_ ULONG Tag)
{
    return ExAllocatePoolWithTag(PagedPool, Bytes, Tag);
}

VOID
NTAPI
RtlpFreeMemory(
    PVOID Mem,
    ULONG Tag)
{
    __debugbreak();
}

KPROCESSOR_MODE
NTAPI
RtlpGetMode()
{
    return KernelMode;
}

NTSTATUS
NTAPI
RtlDeleteHeapLock(
    PHEAP_LOCK Lock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
RtlEnterHeapLock(IN OUT PHEAP_LOCK Lock, IN BOOLEAN Exclusive)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
RtlInitializeHeapLock(IN OUT PHEAP_LOCK *Lock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
RtlLeaveHeapLock(IN OUT PHEAP_LOCK Lock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

BOOLEAN
NTAPI
RtlTryEnterHeapLock(IN OUT PHEAP_LOCK Lock, IN BOOLEAN Exclusive)
{
    return FALSE;
}

VOID
NTAPI
RtlpSetHeapParameters(IN PRTL_HEAP_PARAMETERS Parameters)
{
    __debugbreak();
}

PPEB
NTAPI
RtlGetCurrentPeb(VOID)
{
    __debugbreak();
    return NULL;
}

VOID
NTAPI
RtlAcquirePebLock(VOID)
{
    __debugbreak();
}

VOID
NTAPI
RtlReleasePebLock(VOID)
{
    __debugbreak();
}

NTSTATUS
NTAPI
RtlpSafeCopyMemory(
    _Out_writes_bytes_all_(Length) VOID UNALIGNED *Destination,
    _In_reads_bytes_(Length) CONST VOID UNALIGNED *Source,
    _In_ SIZE_T Length)
{
    _SEH2_TRY
    {
        RtlCopyMemory(Destination, Source, Length);
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        _SEH2_YIELD(return _SEH2_GetExceptionCode());
    }
    _SEH2_END;

    return STATUS_SUCCESS;
}

typedef struct _EXCEPTION_REGISTRATION_RECORD *PEXCEPTION_REGISTRATION_RECORD;

BOOLEAN
NTAPI
RtlpHandleDpcStackException(
    IN PEXCEPTION_REGISTRATION_RECORD RegistrationFrame,
    IN ULONG_PTR RegistrationFrameEnd,
    IN OUT PULONG_PTR StackLow,
    IN OUT PULONG_PTR StackHigh)
{
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
RtlpCheckLogException(
    IN PEXCEPTION_RECORD ExceptionRecord,
    IN PCONTEXT ContextRecord,
    IN PVOID ContextData,
    IN ULONG Size)
{
    __debugbreak();
}


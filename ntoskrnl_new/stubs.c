
#include <ntoskrnl.h>

typedef struct _DEVICE_OBJECT *PDEVICE_OBJECT;
typedef ULONG_PTR PFN_NUMBER;
typedef enum _CONFIGURATION_TYPE
{
    ArcSystem,
    CentralProcessor,
    FloatingPointProcessor,
    PrimaryIcache,
    PrimaryDcache,
    SecondaryIcache,
    SecondaryDcache,
    SecondaryCache,
    EisaAdapter,
    TcAdapter,
    ScsiAdapter,
    DtiAdapter,
    MultiFunctionAdapter,
    DiskController,
    TapeController,
    CdromController,
    WormController,
    SerialController,
    NetworkController,
    DisplayController,
    ParallelController,
    PointerController,
    KeyboardController,
    AudioController,
    OtherController,
    DiskPeripheral,
    FloppyDiskPeripheral,
    TapePeripheral,
    ModemPeripheral,
    MonitorPeripheral,
    PrinterPeripheral,
    PointerPeripheral,
    KeyboardPeripheral,
    TerminalPeripheral,
    OtherPeripheral,
    LinePeripheral,
    NetworkPeripheral,
    SystemMemory,
    DockingInformation,
    RealModeIrqRoutingTable,
    RealModePCIEnumeration,
    MaximumType
} CONFIGURATION_TYPE, *PCONFIGURATION_TYPE;

#include <arc/arc.h>
#include <ioaccess.h>

VOID FASTCALL ExAcquireFastMutexUnsafe(PVOID FastMutex);
NTSTATUS NTAPI NtQueryDebugFilterState(ULONG ComponentId, ULONG Level);
NTSTATUS NTAPI NtWaitForKeyedEvent(HANDLE Handle, PVOID Key, BOOLEAN Alertable, PLARGE_INTEGER Timeout);
BOOLEAN FASTCALL ExAcquireRundownProtection(PVOID RunRef);
VOID FASTCALL KeAcquireGuardedMutex(PVOID Mutex);
VOID FASTCALL KeAcquireInStackQueuedSpinLock(PVOID SpinLock, PVOID LockHandle);
VOID FASTCALL PoNotifyMediaBuffering(BOOLEAN Engaged);
#undef InterlockedDecrement
LONG FASTCALL InterlockedDecrement(LONG volatile *Addend);

/* Pull in some files */
PVOID pExAcquireFastMutexUnsafe = (PVOID)ExAcquireFastMutexUnsafe;
PVOID pExAcquireRundownProtection = (PVOID)ExAcquireRundownProtection;
PVOID pKeAcquireGuardedMutex = (PVOID)KeAcquireGuardedMutex;
PVOID pKeAcquireInStackQueuedSpinLock = (PVOID)KeAcquireInStackQueuedSpinLock;
PVOID pNtQueryDebugFilterState = (PVOID)NtQueryDebugFilterState;
PVOID pNtWaitForKeyedEvent = (PVOID)NtWaitForKeyedEvent;
PVOID pPoNotifyMediaBuffering = (PVOID)PoNotifyMediaBuffering;

PVOID pREAD_REGISTER_UCHAR = (PVOID)READ_REGISTER_UCHAR;
PVOID pREAD_REGISTER_USHORT = (PVOID)READ_REGISTER_USHORT;
PVOID pREAD_REGISTER_ULONG = (PVOID)READ_REGISTER_ULONG;
PVOID pREAD_REGISTER_BUFFER_UCHAR = (PVOID)READ_REGISTER_BUFFER_UCHAR;
PVOID pREAD_REGISTER_BUFFER_USHORT = (PVOID)READ_REGISTER_BUFFER_USHORT;
PVOID pREAD_REGISTER_BUFFER_ULONG = (PVOID)READ_REGISTER_BUFFER_ULONG;
PVOID pWRITE_REGISTER_UCHAR = (PVOID)WRITE_REGISTER_UCHAR;
PVOID pWRITE_REGISTER_USHORT = (PVOID)WRITE_REGISTER_USHORT;
PVOID pWRITE_REGISTER_ULONG = (PVOID)WRITE_REGISTER_ULONG;
PVOID pWRITE_REGISTER_BUFFER_UCHAR = (PVOID)WRITE_REGISTER_BUFFER_UCHAR;
PVOID pWRITE_REGISTER_BUFFER_USHORT = (PVOID)WRITE_REGISTER_BUFFER_USHORT;
PVOID pWRITE_REGISTER_BUFFER_ULONG = (PVOID)WRITE_REGISTER_BUFFER_ULONG;
PVOID pInterlockedDecrement = (PVOID)InterlockedDecrement;

typedef struct { PVOID p; } HAL_DISPATCH;

HAL_DISPATCH HalDispatchTable;
char HalPrivateDispatchTable;
BOOLEAN InitSafeBootMode;

errno_t
_strnset_s (
   char *str,
   size_t numberOfElements,
   int c,
   size_t count)
{
    __debugbreak();
    return -1;
}

errno_t
_strset_s (
   char *str,
   size_t numberOfElements,
   int c )
{
    __debugbreak();
    return -1;
}

errno_t
_wcslwr_s (
   wchar_t *str,
   size_t numberOfElements)
{
    __debugbreak();
    return -1;
}

errno_t
_wcsnset_s (
   wchar_t *str,
   size_t numberOfElements,
   wchar_t c,
   size_t count)
{
    __debugbreak();
    return -1;
}

errno_t
_wcsset_s (
   wchar_t *str,
   size_t numberOfElements,
   wchar_t c)
{
    __debugbreak();
    return -1;
}

errno_t
strcat_s (
   char *strDestination,
   size_t numberOfElements,
   const char *strSource)
{
    __debugbreak();
    return -1;
}

errno_t
strcpy_s (
   char *strDestination,
   size_t numberOfElements,
   const char *strSource)
{
    __debugbreak();
    return -1;
}

#undef ProbeForRead
_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
ProbeForRead (
    __in_data_source(USER_MODE) _In_reads_bytes_(Length) const volatile VOID *Address,
    _In_ SIZE_T Length,
    _In_ ULONG Alignment)
{
    __debugbreak();
}

VOID
NTAPI
ProbeForWrite (
    __in_data_source(USER_MODE) _Inout_updates_bytes_(Length) volatile VOID *Address,
    _In_ SIZE_T Length,
    _In_ ULONG Alignment)
{
    __debugbreak();
}

// prototype from pHalExamineMBR
VOID
FASTCALL
HalExamineMBR (
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ ULONG MBRTypeIdentifier,
    _Out_ PVOID *Buffer)
{
    __debugbreak();
}

VOID
NTAPI
RaiseException(IN ULONG dwExceptionCode,
    IN ULONG dwExceptionFlags,
    IN ULONG nNumberOfArguments,
    IN CONST ULONG_PTR *lpArguments OPTIONAL)
{
    __debugbreak();
}

NTSTATUS
NTAPI
LdrShutdownThread(
    VOID)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

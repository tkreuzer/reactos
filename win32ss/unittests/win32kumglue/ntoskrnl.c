
#include <win32k.h>


PVOID MmSystemRangeStart;
PROCESSINFO gpiCurrent;
THREADINFO gtiCurrent;
volatile KSYSTEM_TIME KeTickCount;

VOID
NTAPI
ProbeForRead(
    const VOID *Address,
    SIZE_T Length,
    ULONG Alignment)
{
    /* Do nothing */
}

VOID
NTAPI
ProbeForWrite(
    PVOID Address,
    SIZE_T Length,
    ULONG Alignment)
{
    /* Do nothing */
}

_Acquires_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
KeEnterCriticalRegion(VOID)
{
    /* Do nothing */
}

_Releases_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
KeLeaveCriticalRegion(VOID)
{
    /* Do nothing */
}

VOID
NTAPI
KeInitializeEvent(
  _Out_ PRKEVENT Event,
  _In_ EVENT_TYPE Type,
  _In_ BOOLEAN State)
{
    __debugbreak();
}

_IRQL_requires_min_(PASSIVE_LEVEL)
_When_((Timeout==NULL || Timeout->QuadPart!=0), _IRQL_requires_max_(APC_LEVEL))
_When_((Timeout!=NULL && Timeout->QuadPart==0), _IRQL_requires_max_(DISPATCH_LEVEL))
NTKERNELAPI
NTSTATUS
NTAPI
KeWaitForSingleObject(
  _In_ _Points_to_data_ PVOID Object,
  _In_ __drv_strictTypeMatch(__drv_typeCond) KWAIT_REASON WaitReason,
  _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst) KPROCESSOR_MODE WaitMode,
  _In_ BOOLEAN Alertable,
  _In_opt_ PLARGE_INTEGER Timeout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

PVOID
NTAPI
ExAllocatePoolWithTag(
    _In_ POOL_TYPE PoolType,
    SIZE_T NumberOfBytes,
    ULONG Tag)
{
    return malloc(NumberOfBytes);
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Function_class_(FREE_FUNCTION)
NTKERNELAPI
VOID
NTAPI
ExFreePool(
  _Pre_notnull_ __drv_freesMem(Mem) PVOID P)
{
    free(P);
}

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
ExFreePoolWithTag(
  _Pre_notnull_ __drv_freesMem(Mem) PVOID P,
  _In_ ULONG Tag)
{
    free(P);
}

VOID
FASTCALL
ExfAcquirePushLockExclusive(
    _Inout_ PEX_PUSH_LOCK PushLock)
{
    __debugbreak();
}

VOID
FASTCALL
ExEnterCriticalRegionAndAcquireFastMutexUnsafe(
    _Inout_ PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

VOID
FASTCALL
ExReleaseFastMutexUnsafeAndLeaveCriticalRegion(
    _Inout_ PFAST_MUTEX FastMutex)
{
    __debugbreak();
}

VOID
FASTCALL
ExfTryToWakePushLock(
    _Inout_ PEX_PUSH_LOCK PushLock)
{
    __debugbreak();
}

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
DECLSPEC_NORETURN
VOID
NTAPI
ExRaiseStatus(
  _In_ NTSTATUS Status)
{
    __debugbreak();
    RtlRaiseStatus(Status);
}

NTKERNELAPI
PEPROCESS
NTAPI
IoGetCurrentProcess(VOID)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
IoGetDeviceObjectPointer(
  _In_ PUNICODE_STRING ObjectName,
  _In_ ACCESS_MASK DesiredAccess,
  _Out_ PFILE_OBJECT *FileObject,
  _Out_ PDEVICE_OBJECT *DeviceObject)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTKERNELAPI
PDEVICE_OBJECT
NTAPI
IoGetRelatedDeviceObject(
  _In_ PFILE_OBJECT FileObject)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
__drv_aliasesMem
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
PIRP
NTAPI
IoBuildSynchronousFsdRequest(
  _In_ ULONG MajorFunction,
  _In_ PDEVICE_OBJECT DeviceObject,
  _Inout_opt_ PVOID Buffer,
  _In_opt_ ULONG Length,
  _In_opt_ PLARGE_INTEGER StartingOffset,
  _In_ PKEVENT Event,
  _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return NULL;
}

_Must_inspect_result_
__drv_aliasesMem
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
PIRP
NTAPI
IoBuildDeviceIoControlRequest(
  _In_ ULONG IoControlCode,
  _In_ PDEVICE_OBJECT DeviceObject,
  _In_opt_ PVOID InputBuffer,
  _In_ ULONG InputBufferLength,
  _Out_opt_ PVOID OutputBuffer,
  _In_ ULONG OutputBufferLength,
  _In_ BOOLEAN InternalDeviceIoControl,
  _In_opt_ PKEVENT Event,
  _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Success_(TRUE)
NTKERNELAPI
NTSTATUS
FASTCALL
IofCallDriver(
  _In_ PDEVICE_OBJECT DeviceObject,
  _Inout_ __drv_aliasesMem PIRP Irp)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmCreateSection(
    _Out_ PVOID *SectionObject,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle,
    _In_opt_ PFILE_OBJECT File)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
MmMapViewInSystemSpace(
  _In_ PVOID Section,
  _Outptr_result_bytebuffer_(*ViewSize) PVOID *MappedBase,
  _Inout_ PSIZE_T ViewSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
MmUnmapViewInSystemSpace(
  _In_ PVOID MappedBase)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
MmMapViewInSessionSpace(
  _In_ PVOID Section,
  _Outptr_result_bytebuffer_(*ViewSize) PVOID *MappedBase,
  _Inout_ PSIZE_T ViewSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
MmUnmapViewInSessionSpace(
  _In_ PVOID MappedBase)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmMapViewOfSection(
    _In_ PVOID SectionObject,
    _In_ PEPROCESS Process,
    _Inout_ PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmUnmapViewOfSection(
    _In_ struct _EPROCESS* Process,
    _In_ PVOID BaseAddress)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

PVOID
NTAPI
PsGetCurrentProcessWin32Process(VOID)
{
    __debugbreak();
    return &gpiCurrent;
}

PVOID
NTAPI
PsGetCurrentThreadWin32Thread(VOID)
{
    __debugbreak();
    return &gtiCurrent;
}

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
ObReferenceObjectByHandle(
  _In_ HANDLE Handle,
  _In_ ACCESS_MASK DesiredAccess,
  _In_opt_ POBJECT_TYPE ObjectType,
  _In_ KPROCESSOR_MODE AccessMode,
  _Out_ PVOID *Object,
  _Out_opt_ POBJECT_HANDLE_INFORMATION HandleInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
LONG_PTR
FASTCALL
ObfDereferenceObject(
  _In_ PVOID Object)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
__MINGW_IMP_SYMBOL(RtlGetDefaultCodePage)(PUSHORT AnsiCodePage, PUSHORT oemCodePage)
{
    __debugbreak();
}

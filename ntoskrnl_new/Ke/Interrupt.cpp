
#include "Interrupt.hpp"
#include "Irql.hpp"

PVOID pKeGetCurrentIrql = (PVOID)KeGetCurrentIrql;

extern "C" {

//@ stdcall -stub KeInitializeInterrupt(ptr ptr ptr ptr long long long long long long long)
// from Ke_NUKE
VOID
NTAPI
KeInitializeInterrupt(
    PKINTERRUPT Interrupt,
    PKSERVICE_ROUTINE ServiceRoutine,
    PVOID ServiceContext,
    PKSPIN_LOCK SpinLock,
    ULONG Vector,
    KIRQL Irql,
    KIRQL SynchronizeIrql,
    KINTERRUPT_MODE InterruptMode,
    BOOLEAN ShareVector,
    CHAR ProcessorNumber,
    BOOLEAN FloatingSave)
{
    __debugbreak();
}

//@ cdecl -stub -arch=i386,arm KiUnexpectedInterrupt()
//; ??? @ fastcall -arch=??? KiEoiHelper(ptr)
//@ stdcall -stub -arch=i386 Kei386EoiHelper()

_Requires_lock_not_held_(*Interrupt->ActualLock)
_Acquires_lock_(*Interrupt->ActualLock)
_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_saves_
_IRQL_raises_(HIGH_LEVEL)
KIRQL
NTAPI
KeAcquireInterruptSpinLock (
    _Inout_ PKINTERRUPT Interrupt)
{
    __debugbreak();
    return 0;
}

_Requires_lock_held_(*Interrupt->ActualLock)
_Releases_lock_(*Interrupt->ActualLock)
_IRQL_requires_(HIGH_LEVEL)
VOID
NTAPI
KeReleaseInterruptSpinLock (
    _Inout_ PKINTERRUPT Interrupt,
    _In_ _IRQL_restores_ KIRQL OldIrql)
{
    __debugbreak();
}

// wdm.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
KeRegisterNmiCallback (
    _In_ PNMI_CALLBACK CallbackRoutine,
    _In_opt_ PVOID Context)
{
    __debugbreak();
    return NULL;
}

// wdm.h / ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
KeDeregisterNmiCallback (
    _In_ PVOID Handle)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
BOOLEAN
NTAPI
KeDispatchSecondaryInterrupt (
    _In_ ULONG Vector,
    _In_ ULONG Flags,
    _Out_opt_ PKINTERRUPT_DISPATCH_STATUS DispatchStatus)
{
    __debugbreak();
    return FALSE;
}

// ntosp.h
NTSTATUS
NTAPI
KeInitializeSecondaryInterruptServices (
    _In_ PVOID SecondaryIcExports)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
VOID
NTAPI
KeProfileInterruptWithSource (
    _In_ struct _KTRAP_FRAME *TrapFrame,
    _In_ KPROFILE_SOURCE ProfileSource)
{
    __debugbreak();
}

// wdm.h
_IRQL_requires_max_(HIGH_LEVEL)
BOOLEAN
NTAPI
KeSynchronizeExecution (
    _Inout_ PKINTERRUPT Interrupt,
    _In_ PKSYNCHRONIZE_ROUTINE SynchronizeRoutine,
    _In_opt_ __drv_aliasesMem PVOID SynchronizeContext)
{
    __debugbreak();
    return FALSE;
}


}; // extern "C"

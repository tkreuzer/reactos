$if (_WDMDDK_)
/** Kernel definitions for x86 **/

#define YieldProcessor _mm_pause

FORCEINLINE
VOID
KeMemoryBarrier(VOID)
{
  LONG Barrier, *Dummy = &Barrier;
  UNREFERENCED_LOCAL_VARIABLE(Dummy);

#if defined(__GNUC__)
  __asm__ __volatile__ ("xchg %%eax, %0" : : "m" (Barrier) : "%eax");
#elif defined(_MSC_VER)
  __asm xchg [Barrier], eax
#endif
}

#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_saves_
NTHALAPI
KIRQL
NTAPI
KeGetCurrentIrql(VOID);

_IRQL_requires_max_(HIGH_LEVEL)
NTHALAPI
VOID
FASTCALL
KfLowerIrql(
  _In_ _IRQL_restores_ _Notliteral_ KIRQL NewIrql);
#define KeLowerIrql(a) KfLowerIrql(a)

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_raises_(NewIrql)
_IRQL_saves_
NTHALAPI
KIRQL
FASTCALL
KfRaiseIrql(
  _In_ KIRQL NewIrql);
#define KeRaiseIrql(a,b) *(b) = KfRaiseIrql(a)

_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
NTHALAPI
KIRQL
NTAPI
KeRaiseIrqlToDpcLevel(VOID);

NTHALAPI
KIRQL
NTAPI
KeRaiseIrqlToSynchLevel(VOID);

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
NTHALAPI
KIRQL
FASTCALL
KfAcquireSpinLock(
  _Inout_ PKSPIN_LOCK SpinLock);
#define KeAcquireSpinLock(a,b) *(b) = KfAcquireSpinLock(a)

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_(DISPATCH_LEVEL)
NTHALAPI
VOID
FASTCALL
KfReleaseSpinLock(
  _Inout_ PKSPIN_LOCK SpinLock,
  _In_ _IRQL_restores_ KIRQL NewIrql);
#define KeReleaseSpinLock(a,b) KfReleaseSpinLock(a,b)

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
FASTCALL
KefAcquireSpinLockAtDpcLevel(
  _Inout_ PKSPIN_LOCK SpinLock);
#define KeAcquireSpinLockAtDpcLevel(SpinLock) KefAcquireSpinLockAtDpcLevel(SpinLock)

_Requires_lock_held_(*SpinLock)
_Releases_lock_(*SpinLock)
_IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
FASTCALL
KefReleaseSpinLockFromDpcLevel(
  _Inout_ PKSPIN_LOCK SpinLock);
#define KeReleaseSpinLockFromDpcLevel(SpinLock) KefReleaseSpinLockFromDpcLevel(SpinLock)

NTSYSAPI
PKTHREAD
NTAPI
KeGetCurrentThread(VOID);

_Always_(_Post_satisfies_(return<=0))
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Kernel_float_saved_
_At_(*FloatSave, _Kernel_requires_resource_not_held_(FloatState) _Kernel_acquires_resource_(FloatState))
NTKERNELAPI
NTSTATUS
NTAPI
KeSaveFloatingPointState(
  _Out_ PKFLOATING_SAVE FloatSave);

_Success_(1)
_Kernel_float_restored_
_At_(*FloatSave, _Kernel_requires_resource_held_(FloatState) _Kernel_releases_resource_(FloatState))
NTKERNELAPI
NTSTATUS
NTAPI
KeRestoreFloatingPointState(
  _In_ PKFLOATING_SAVE FloatSave);

/* VOID
 * KeFlushIoBuffers(
 *   IN PMDL Mdl,
 *   IN BOOLEAN ReadOperation,
 *   IN BOOLEAN DmaOperation)
 */
#define KeFlushIoBuffers(_Mdl, _ReadOperation, _DmaOperation)

/* x86 and x64 performs a 0x2C interrupt */
#define DbgRaiseAssertionFailure __int2c

FORCEINLINE
VOID
_KeQueryTickCount(
  OUT PLARGE_INTEGER CurrentCount)
{
  for (;;) {
#ifdef NONAMELESSUNION
    CurrentCount->s.HighPart = KeTickCount.High1Time;
    CurrentCount->s.LowPart = KeTickCount.LowPart;
    if (CurrentCount->s.HighPart == KeTickCount.High2Time) break;
#else
    CurrentCount->HighPart = KeTickCount.High1Time;
    CurrentCount->LowPart = KeTickCount.LowPart;
    if (CurrentCount->HighPart == KeTickCount.High2Time) break;
#endif
    YieldProcessor();
  }
}
#define KeQueryTickCount(CurrentCount) _KeQueryTickCount(CurrentCount)

$endif (_WDMDDK_)
$if (_NTDDK_)

FORCEINLINE
ULONG
KeGetCurrentProcessorNumber(VOID)
{
    return (ULONG)__readfsbyte(FIELD_OFFSET(KPCR, Number));
}

$endif (_NTDDK_)

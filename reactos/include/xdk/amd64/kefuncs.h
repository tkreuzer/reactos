$if (_WDMDDK_)
/** Kernel definitions for AMD64 **/

#define KeQueryInterruptTime() \
    (*(volatile ULONG64*)SharedInterruptTime)

#define KeQuerySystemTime(CurrentCount) \
    *(ULONG64*)(CurrentCount) = *(volatile ULONG64*)SharedSystemTime

#define KeQueryTickCount(CurrentCount) \
    *(ULONG64*)(CurrentCount) = *(volatile ULONG64*)SharedTickCount

#define KeGetDcacheFillSize() 1L

#define YieldProcessor _mm_pause
#define MemoryBarrier __faststorefence
#define FastFence __faststorefence
#define LoadFence _mm_lfence
#define MemoryFence _mm_mfence
#define StoreFence _mm_sfence
#define LFENCE_ACQUIRE() LoadFence()

FORCEINLINE
VOID
KeMemoryBarrier(VOID)
{
  // FIXME: Do we really need lfence after the __faststorefence ?
  FastFence();
  LFENCE_ACQUIRE();
}

#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()

FORCEINLINE
KIRQL
KeGetCurrentIrql(VOID)
{
  return (KIRQL)__readcr8();
}

FORCEINLINE
VOID
KeLowerIrql(IN KIRQL NewIrql)
{
  ASSERT((KIRQL)__readcr8() >= NewIrql);
  __writecr8(NewIrql);
}

FORCEINLINE
KIRQL
KfRaiseIrql(IN KIRQL NewIrql)
{
  KIRQL OldIrql;

  OldIrql = (KIRQL)__readcr8();
  ASSERT(OldIrql <= NewIrql);
  __writecr8(NewIrql);
  return OldIrql;
}
#define KeRaiseIrql(a,b) *(b) = KfRaiseIrql(a)

FORCEINLINE
KIRQL
KeRaiseIrqlToDpcLevel(VOID)
{
  return KfRaiseIrql(DISPATCH_LEVEL);
}

FORCEINLINE
KIRQL
KeRaiseIrqlToSynchLevel(VOID)
{
  return KfRaiseIrql(12); // SYNCH_LEVEL = IPI_LEVEL - 2
}

FORCEINLINE
PKTHREAD
KeGetCurrentThread(VOID)
{
  return (struct _KTHREAD *)__readgsqword(0x188);
}

FORCEINLINE
NTSTATUS
KeSaveFloatingPointState(PVOID FloatingState)
{
  UNREFERENCED_PARAMETER(FloatingState);
  return STATUS_SUCCESS;
}

FORCEINLINE
NTSTATUS
KeRestoreFloatingPointState(PVOID FloatingState)
{
  UNREFERENCED_PARAMETER(FloatingState);
  return STATUS_SUCCESS;
}

/* VOID
 * KeFlushIoBuffers(
 *   IN PMDL Mdl,
 *   IN BOOLEAN ReadOperation,
 *   IN BOOLEAN DmaOperation)
 */
#define KeFlushIoBuffers(_Mdl, _ReadOperation, _DmaOperation)

/* x86 and x64 performs a 0x2C interrupt */
#define DbgRaiseAssertionFailure __int2c

$endif /* _WDMDDK_ */
$if (_NTDDK_)

FORCEINLINE
PKPCR
KeGetPcr(VOID)
{
    return (PKPCR)__readgsqword(FIELD_OFFSET(KPCR, Self));
}

FORCEINLINE
ULONG
KeGetCurrentProcessorNumber(VOID)
{
    return (ULONG)__readgsword(0x184);
}

$endif /* _NTDDK_ */

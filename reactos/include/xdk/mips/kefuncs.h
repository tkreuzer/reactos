$if (_WDMDDK_)
#error MIPS Headers are totally incorrect

#define KeGetPcr()                      PCR

static __inline
ULONG
NTAPI
KeGetCurrentProcessorNumber(VOID)
{
  return 0;
}

#define YieldProcessor() __asm__ __volatile__("nop");

#define KeLowerIrql(a) KfLowerIrql(a)
#define KeRaiseIrql(a,b) *(b) = KfRaiseIrql(a)

NTKERNELAPI
VOID
NTAPI
KfLowerIrql(
  IN KIRQL NewIrql);

NTKERNELAPI
KIRQL
NTAPI
KfRaiseIrql(
  IN KIRQL NewIrql);

NTKERNELAPI
KIRQL
NTAPI
KeRaiseIrqlToDpcLevel(VOID);

NTKERNELAPI
KIRQL
NTAPI
KeRaiseIrqlToSynchLevel(VOID);

$endif


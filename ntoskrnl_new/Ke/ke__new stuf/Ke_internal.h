
#define _KE_INTERNAL_

#if defined(_M_AMD64)
#include "amd64/Ke_amd64.h"
#elif defined(_M_IX86)
#include "ix86/Ke_ix86.h"
#else
#error unimplemented architecture
#endif

#define PRCB_BUILD_DEBUG 1
#define PRCB_BUILD_RELEASE 0

#define PRCB_BUILD_UNIPROCESSOR 2
#define PRCB_BUILD_MULTIROCESSOR 0

#ifdef CONFIG_SMP
#define PRCB_CPU_BUILD_TYPE PRCB_BUILD_MULTIROCESSOR
#else
#define PRCB_CPU_BUILD_TYPE PRCB_BUILD_UNIPROCESSOR
#endif

#ifdef DBG
#define PRCB_BUILD_TYPE (PRCB_CPU_BUILD_TYPE|PRCB_BUILD_DEBUG)
#else
#define PRCB_BUILD_TYPE (PRCB_CPU_BUILD_TYPE|PRCB_BUILD_RELEASE)
#endif

#define PRCB_MAJOR_VERSION 1
#define PRCB_MINOR_VERSION 1

VOID
NTAPI
KxAttachProcessAddressSpace(
    PKPROCESS Process);

VOID
NTAPI
KxDumpProcessorState(
    PKPROCESSOR_STATE ProcessorState);

VOID
NTAPI
KxGetExceptionContext(
    PCONTEXT Context,
    PKTRAP_FRAME TrapFrame,
    PKEXCEPTION_FRAME ExceptionFrame);

VOID
NTAPI
KxSetExceptionContext(
    PCONTEXT Context,
    PKTRAP_FRAME TrapFrame,
    PKEXCEPTION_FRAME ExceptionFrame);


/* Interrupt.c ****************************************************************/

typedef struct _KINTERRUPT
{
    SHORT Type;
    SHORT Size;
    LIST_ENTRY InterruptListEntry;
    //FUNCT_006E_2255_ServiceRoutine* ServiceRoutine;
    //FUNCT_006E_225A_MessageServiceRoutine* MessageServiceRoutine;
    ULONG MessageIndex;
    PVOID ServiceContext;
    KSPIN_LOCK SpinLock;
    ULONG TickCount;
    PKSPIN_LOCK ActualLock;
    //FUNCT_00AE_0282_PostProcessInitRoutine_DispatchAddress_FinishRoutine* DispatchAddress;
    ULONG Vector;
    KIRQL Irql;
    KIRQL SynchronizeIrql;
    BOOLEAN FloatingSave;
    BOOLEAN Connected;
    ULONG Number;
    UCHAR ShareVector;
    USHORT ActiveCount;
    LONG InternalState;
    enum _KINTERRUPT_MODE Mode;
    enum _KINTERRUPT_POLARITY Polarity;
    ULONG ServiceCount;
    ULONG DispatchCount;
    PKEVENT PassiveEvent;
    struct _KTRAP_FRAME* TrapFrame;
    ULONG DispatchCode[4];
    PVOID DisconnectData;
    PKTHREAD ServiceThread;
} KINTERRUPT, *PKINTERRUPT;

VOID
NTAPI
KxSwapContext(
    PKTHREAD OldThread,
    PKTHREAD NewThread);


/* KeInit.c *******************************************************************/

extern PKPCREX KiPcrBlock[];
extern KPCREX KiBootstrapPcr;
extern const PVOID KiDoubleFaultStack;
extern PKPRCB KeProcessorBlock[];

VOID
NTAPI
KxInitializeArchitectureSpecific(
    PLOADER_PARAMETER_BLOCK LoaderBlock);


/* Timer.c ********************************************************************/

BOOLEAN
FORCEINLINE
KiIsTimerExpired(
    PKTIMER Timer)
{
    LARGE_INTEGER CurrentTime;

    /* Query the system time */
    KeQuerySystemTime(&CurrentTime);

    /* TRUE if current time > due time */
    return ((ULONGLONG)CurrentTime.QuadPart >= Timer->DueTime.QuadPart);
}


/* Thread.c *******************************************************************/

typedef enum _KTHREAD_STATE
{
    Initialized      = 0,
    Ready            = 1,
    Running          = 2,
    Standby          = 3,
    Terminated       = 4,
    Waiting          = 5,
    Transition       = 6,
    DeferredReady    = 7,
    GateWaitObsolete = 8
} KTHREAD_STATE, *PKTHREAD_STATE;

VOID
NTAPI
KiBoostPriorityThread(
    PKTHREAD Thread,
    CHAR Priority);

PKTHREAD
NTAPI
KiGetNextReadyThread();

VOID
NTAPI
KiSwapThread(
    PKTHREAD NewThread);

VOID
NTAPI
KiReadyThread(
    PKTHREAD Thread,
    LONG_PTR WaitState);


/* Wait.c *********************************************************************/

#define DH_LOCK_MASK 0x80
#define DH_LOCK_BIT 7

typedef enum _KOBJECTS
{
    EventNotificationObject    = 0,
    EventSynchronizationObject = 1,
    MutantObject               = 2,
    ProcessObject              = 3,
    QueueObject                = 4,
    SemaphoreObject            = 5,
    ThreadObject               = 6,
    GateObject                 = 7,
    TimerNotificationObject    = 8,
    TimerSynchronizationObject = 9,
    Spare2Object               = 10,
    Spare3Object               = 11,
    Spare4Object               = 12,
    Spare5Object               = 13,
    Spare6Object               = 14,
    Spare7Object               = 15,
    Spare8Object               = 16,
    ProfileCallbackObject      = 17,
    ApcObject                  = 18,
    DpcObject                  = 19,
    DeviceQueueObject          = 20,
    EventPairObject            = 21,
    InterruptObject            = 22,
    ProfileObject              = 23,
    ThreadedDpcObject          = 24,
    MaximumKernelObject        = 25
} KOBJECTS, *PKOBJECTS;

LONG
NTAPI
KiSignalObject(
    PDISPATCHER_HEADER DispatcherHeader,
    BOOLEAN WakeAll,
    KPRIORITY PriorityIncrement);

NTSTATUS
NTAPI
KiWaitThread(
    __in PKTIMER TimeoutTimer);


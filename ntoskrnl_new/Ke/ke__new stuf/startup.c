
#include <ntoskrnl.h>
#include "Ke_internal.h"

/* Boot and double-fault/NMI/DPC stack */
static UCHAR DECLSPEC_ALIGN(16) P0BootStackData[KERNEL_STACK_SIZE];
static UCHAR DECLSPEC_ALIGN(16) KiDoubleFaultStackData[KERNEL_STACK_SIZE];
static UCHAR DECLSPEC_ALIGN(16) KiP0IdleStackData[KERNEL_STACK_SIZE];

const PVOID P0BootStack = &P0BootStackData[sizeof(P0BootStackData)];
const PVOID KiDoubleFaultStack = &KiDoubleFaultStackData[sizeof(KiDoubleFaultStackData)];
const PVOID KiP0IdleStack = &KiP0IdleStackData[sizeof(KiP0IdleStackData)];

PLOADER_PARAMETER_BLOCK KeLoaderBlock;
KPCREX KiBootstrapPcr;
PKPCREX KiPcrBlock[64];
ETHREAD KiInitialThread;
ETHREAD KiP0IdleThread;
EPROCESS KiInitialProcess;
PLOADER_PARAMETER_BLOCK KeLoaderBlock;


VOID
NTAPI
KiInitializePcr(
    IN PKPCREX Pcr,
    IN ULONG ProcessorNumber,
    IN PKTHREAD Thread)
{
    PKPRCB Prcb = &Pcr->Prcb;

    /* Zero out the PCR */
    RtlZeroMemory(Pcr, sizeof(KPCREX));

    /* Set self pointers */
    Pcr->Self = (PKPCR)Pcr;
    Pcr->CurrentPrcb = Prcb;

    /* Set the PCR and PRCB Version */
    Pcr->MajorVersion = PCR_MAJOR_VERSION;
    Pcr->MinorVersion = PCR_MINOR_VERSION;
    Prcb->MajorVersion = PRCB_MAJOR_VERSION;
    Prcb->MinorVersion = PRCB_MINOR_VERSION;

    /* Set the Build Type */
    Prcb->BuildType = PRCB_BUILD_TYPE;

    Prcb->CurrentThread = Thread;
    Prcb->Number = ProcessorNumber;

    KiPcrBlock[ProcessorNumber] = Pcr;
}

void
TestEvent()
{
    //KEVENT Event;

    //KeInitializeEvent(&Event, Synch
}

VOID
KiIdleLoop()
{
    __debugbreak();
}

VOID
NTAPI
KiSystemStartup(
    IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    /* HACK */
    LoaderBlock->u.I386.CommonDataArea = RawDbgPrint;
    //RawDbgPrint("Hello from KiSystemStartup!!!\n");

    /* Initialize the PCR common parts */
    KiInitializePcr(&KiBootstrapPcr, 0, &KiInitialThread.Tcb);

    /* Initialize architecture specific parts */
    KxInitializeArchitectureSpecific(LoaderBlock);

    /* Initialize debugging */
    KdInitialize(LoaderBlock);

    /* Initialize the processor with hal */
    HalInitializeProcessor(0, LoaderBlock);

    /* Initialize the hal */
    HalInitSystem(0, LoaderBlock);

    /* Initialite the memory manager */
    MmInitialize(LoaderBlock);


    KeInitializeThread(&KiP0IdleThread.Tcb,
                       &KiInitialProcess.Pcb,
                       KiP0IdleStack,
                       NULL,
                       KiIdleLoop,
                       NULL);

    KiReadyThread(&KiP0IdleThread.Tcb, 0);


    //HalInitializeBios();

    // ExInitialize() -> initialize pools etc

    // ObInitialize() -> initialize the object manager

    // start application cpus

    /* terminate this thread */
    // KeExitThread()

__debugbreak();
    for (;;);
}

PKPCR
NTAPI
KeGetPcrFromNumber(ULONG Number)
{
    ASSERT(Number < 32);
    return (PKPCR)KiPcrBlock[Number];
}


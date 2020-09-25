/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Kernel
 * FILE:            ntoskrnl/kd/kdinit.c
 * PURPOSE:         Kernel Debugger Initializtion
 *
 * PROGRAMMERS:     Alex Ionescu (alex@relsoft.net)
 */

#include <ntoskrnl.h>
#define NDEBUG
#include <debug.h>

/* Make bochs debug output in the very early boot phase available */
//#define AUTO_ENABLE_BOCHS

/* VARIABLES ***************************************************************/

ULONG  PortNumber = DEFAULT_DEBUG_PORT;
CPPORT PortInfo   = {0, DEFAULT_DEBUG_BAUD_RATE, 0};
ULONG KdpPortIrq;
#ifdef AUTO_ENABLE_BOCHS
KDP_DEBUG_MODE KdpDebugMode = {{{.Bochs=TRUE}}};
#else
KDP_DEBUG_MODE KdpDebugMode;
#endif
PKDP_INIT_ROUTINE WrapperInitRoutine;
KD_DISPATCH_TABLE WrapperTable;
LIST_ENTRY KdProviders = {&KdProviders, &KdProviders};
KD_DISPATCH_TABLE DispatchTable[KdMax];

PKDP_INIT_ROUTINE InitRoutines[KdMax] = {KdpScreenInit,
                                         KdpSerialInit,
                                         KdpDebugLogInit,
                                         KdpBochsInit,
                                         KdpKdbgInit};

extern ANSI_STRING KdpLogFileName;

/* PRIVATE FUNCTIONS *********************************************************/

BOOLEAN
NTAPI
KdRegisterDebuggerDataBlock(IN ULONG Tag,
                            IN PDBGKD_DEBUG_DATA_HEADER64 DataHeader,
                            IN ULONG Size);

INIT_FUNCTION
VOID
NTAPI
KdpCallInitRoutine(ULONG BootPhase)
{
    PLIST_ENTRY CurrentEntry;
    PKD_DISPATCH_TABLE CurrentTable;

    /* Call the registered handlers */
    CurrentEntry = KdProviders.Flink;
    while (CurrentEntry != &KdProviders)
    {
        /* Get the current table */
        CurrentTable = CONTAINING_RECORD(CurrentEntry,
                                         KD_DISPATCH_TABLE,
                                         KdProvidersList);

        /* Call it */
        CurrentTable->KdpInitRoutine(CurrentTable, BootPhase);

        /* Next Table */
        CurrentEntry = CurrentEntry->Flink;
    }

    /* Call the Wrapper Init Routine */
    if (WrapperInitRoutine)
        WrapperTable.KdpInitRoutine(&WrapperTable, BootPhase);
}

BOOLEAN
NTAPI
KdInitSystem(IN ULONG BootPhase,
             IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    BOOLEAN EnableKd;
    LPSTR DebugLine;
    PLDR_DATA_TABLE_ENTRY LdrEntry;
    ULONG i;
    PCHAR CommandLine;

    /* Check if this is Phase 1 */
    if (BootPhase)
    {
        /* Call the Initialization Routines of the Registered Providers */
        KdpCallInitRoutine(BootPhase);
        return TRUE;
    }

    /* Check if we already initialized once */
    if (KdDebuggerEnabled) return TRUE;

    /* Disable break after symbol load for now */
    KdBreakAfterSymbolLoad = FALSE;

    /* Check if the Debugger Data Block was already initialized */
    if (!KdpDebuggerDataListHead.Flink)
    {
        /* It wasn't...Initialize the KD Data Listhead */
        InitializeListHead(&KdpDebuggerDataListHead);

        /* Register the Debugger Data Block */
        KdRegisterDebuggerDataBlock(KDBG_TAG,
                                    &KdDebuggerDataBlock.Header,
                                    sizeof(KdDebuggerDataBlock));

        /* Fill out the KD Version Block */
        KdVersionBlock.MajorVersion = (USHORT)((DBGKD_MAJOR_NT << 8) | (NtBuildNumber >> 28));
        KdVersionBlock.MinorVersion = (USHORT)(NtBuildNumber & 0xFFFF);

#ifdef CONFIG_SMP
        /* This is an MP Build */
        KdVersionBlock.Flags |= DBGKD_VERS_FLAG_MP;
#endif

        /* Save Pointers to Loaded Module List and Debugger Data */
        KdVersionBlock.PsLoadedModuleList = (ULONG64)(LONG_PTR)&PsLoadedModuleList;
        KdVersionBlock.DebuggerDataList = (ULONG64)(LONG_PTR)&KdpDebuggerDataListHead;

        /* Set protocol limits */
        KdVersionBlock.MaxStateChange = DbgKdMaximumStateChange -
                                        DbgKdMinimumStateChange;
        KdVersionBlock.MaxManipulate = DbgKdMaximumManipulate -
                                       DbgKdMinimumManipulate;
        KdVersionBlock.Unused[0] = 0;

        /* Link us in the KPCR */
        KeGetPcr()->KdVersionBlock =  &KdVersionBlock;
    }

    /* Check if we have a loader block */
    if (LoaderBlock)
    {
        /* Get the image entry */
        LdrEntry = CONTAINING_RECORD(LoaderBlock->LoadOrderListHead.Flink,
                                     LDR_DATA_TABLE_ENTRY,
                                     InLoadOrderLinks);

        /* Save the Kernel Base */
        PsNtosImageBase = (ULONG_PTR)LdrEntry->DllBase;
        KdVersionBlock.KernBase = (ULONG64)(LONG_PTR)LdrEntry->DllBase;

        /* Check if we have a command line */
        CommandLine = LoaderBlock->LoadOptions;
        if (CommandLine)
        {
            /* Upcase it */
            _strupr(CommandLine);

            /* Assume we'll disable KD */
            EnableKd = FALSE;

            /* Check for CRASHDEBUG, NODEBUG and just DEBUG */
            if (strstr(CommandLine, "CRASHDEBUG"))
            {
                /* Don't enable KD now, but allow it to be enabled later */
                KdPitchDebugger = FALSE;
            }
            else if (strstr(CommandLine, "NODEBUG"))
            {
                /* Don't enable KD and don't let it be enabled later */
                KdPitchDebugger = TRUE;
            }
            else if ((DebugLine = strstr(CommandLine, "DEBUG")) != NULL)
            {
                /* Enable KD */
                EnableKd = TRUE;
                KdDebuggerNotPresent = FALSE;
#ifdef KDBG
                /* Get the KDBG Settings */
                KdbpGetCommandLineSettings(LoaderBlock->LoadOptions);
#endif
            }
        }
        else
        {
            /* No command line options? Disable debugger by default */
            KdPitchDebugger = TRUE;
            EnableKd = FALSE;
        }
    }
    else
    {
        /* Called from a bugcheck or a re-enable. Save the Kernel Base. */
        KdVersionBlock.KernBase = (ULONG64)(LONG_PTR)PsNtosImageBase;

        /* Unconditionally enable KD */
        EnableKd = TRUE;
    }

    /* Set the Kernel Base in the Data Block */
    KdDebuggerDataBlock.KernBase = (ULONG_PTR)KdVersionBlock.KernBase;

    /* Initialize the debugger if requested */
    if (EnableKd && (NT_SUCCESS(KdDebuggerInitialize0(LoaderBlock))))
    {
        /* Check if we've already initialized our structures */
        if (!KdpDebuggerStructuresInitialized)
        {
            /* Set the Debug Switch Routine and Retries */
            KdpContext.KdpDefaultRetries = 20;
            KiDebugSwitchRoutine = KdpSwitchProcessor;

            /* Initialize breakpoints owed flag and table */
            KdpOweBreakpoint = FALSE;
            for (i = 0; i < KD_BREAKPOINT_MAX; i++)
            {
                KdpBreakpointTable[i].Flags   = 0;
                KdpBreakpointTable[i].DirectoryTableBase = 0;
                KdpBreakpointTable[i].Address = NULL;
            }

            /* Initialize the Time Slip DPC */
            KeInitializeDpc(&KdpTimeSlipDpc, KdpTimeSlipDpcRoutine, NULL);
            KeInitializeTimer(&KdpTimeSlipTimer);
            ExInitializeWorkItem(&KdpTimeSlipWorkItem, KdpTimeSlipWork, NULL);

            /* First-time initialization done! */
            KdpDebuggerStructuresInitialized = TRUE;
        }

        /* Initialize the timer */
        KdTimerStart.QuadPart = 0;

        /* Officially enable KD */
        KdPitchDebugger = FALSE;
        KdDebuggerEnabled = TRUE;

        /* Let user-mode know that it's enabled as well */
        SharedUserData->KdDebuggerEnabled = TRUE;
    }
    else
    {
        /* Disable debugger */
        KdDebuggerNotPresent = TRUE;
    }

    /* Return initialized */
    return TRUE;
}

/* EOF */



#include <ntoskrnl.h>
#include <windbgkd.h>
#include <kddll.h>
#include "Kd_internal.h"
#include "../Ke/Ke_internal.h"

PVOID KdPrintCircularBuffer;
PVOID KdPrintCircularBufferEnd;
PVOID KdPrintWritePointer;
ULONG KdPrintRolloverCount;
PVOID KdPrintCircularBufferPtr;
ULONG KdPrintBufferSize;
BOOLEAN KdDebuggerNotPresent;
BOOLEAN KdDebuggerEnabled;
BOOLEAN KdEnteredDebugger;
LIST_ENTRY KdpDebuggerDataListHead;
static PVOID KdpBreakPointTable[KDP_MAX_BREAK_POINTS];
static UCHAR KdpBreakPointBackupTable[KDP_MAX_BREAK_POINTS][KDP_BREAKPOINT_LENGTH];
CHAR NtBuildLab[] = "7600.16385.amd64fre.win7_rtm.090713-1255";
static BOOLEAN KdpDebuggerActive;

C_ASSERT(sizeof(KDDEBUGGER_DATA64) == 0x340);

static KDDEBUGGER_DATA64 KdpDebuggerData =
{
    { { MAKESIGNED64(&KdpDebuggerDataListHead),
        MAKESIGNED64(&KdpDebuggerDataListHead)},
      KDBG_TAG, sizeof(KDDEBUGGER_DATA64) }, // Header;
    MAKESIGNED64(&__ImageBase), // KernBase;
    MAKESIGNED64(&RtlpBreakWithStatusInstruction), // ULONG64 BreakpointWithStatus;
    0, // ULONG64 SavedContext;
    FIELD_OFFSET(KTHREAD, CallbackStack), // USHORT ThCallbackStack;
    0, // USHORT NextCallback;
    0, // USHORT FramePointer;
    0, // USHORT PaeEnabled:1;
    0, // ULONG64 KiCallUserMode;
    0, // ULONG64 KeUserCallbackDispatcher;
    MAKESIGNED64(&PsLoadedModuleList),
    0, // ULONG64 PsActiveProcessHead;
    0, // ULONG64 PspCidTable;
    0, // ULONG64 ExpSystemResourcesList;
    0, // ULONG64 ExpPagedPoolDescriptor;
    0, // ULONG64 ExpNumberOfPagedPools;
    0, // ULONG64 KeTimeIncrement;
    0, // ULONG64 KeBugCheckCallbackListHead;
    0, // ULONG64 KiBugcheckData;
    0, // ULONG64 IopErrorLogListHead;
    0, // ULONG64 ObpRootDirectoryObject;
    0, // ULONG64 ObpTypeObjectType;
    MAKESIGNED64(&MmSystemCacheStart),
    MAKESIGNED64(&MmSystemCacheEnd),
    MAKESIGNED64(&MmSystemCacheWs),
    MAKESIGNED64(&MmPfnDatabase),
    MAKESIGNED64(&MmSystemPtesStart),
    MAKESIGNED64(&MmSystemPtesEnd),
    MAKESIGNED64(&MmSubsectionBase),
    MAKESIGNED64(&MmNumberOfPagingFiles),
    MAKESIGNED64(&MmLowestPhysicalPage),
    MAKESIGNED64(&MmHighestPhysicalPage),
    MAKESIGNED64(&MmNumberOfPhysicalPages),
    MAKESIGNED64(&MmMaximumNonPagedPoolInBytes),
    MAKESIGNED64(&MmNonPagedSystemStart),
    MAKESIGNED64(&MmNonPagedPoolStart),
    MAKESIGNED64(&MmNonPagedPoolEnd),
    MAKESIGNED64(&MmPagedPoolStart),
    MAKESIGNED64(&MmPagedPoolEnd),
    MAKESIGNED64(&MmPagedPoolInformation),
    PAGE_SIZE,
    MAKESIGNED64(&MmSizeOfPagedPoolInBytes),
    MAKESIGNED64(&MmTotalCommitLimit),
    MAKESIGNED64(&MmTotalCommittedPages),
    MAKESIGNED64(&MmSharedCommit),
    MAKESIGNED64(&MmDriverCommit),
    MAKESIGNED64(&MmProcessCommit),
    MAKESIGNED64(&MmPagedPoolCommit),
    MAKESIGNED64(&MmExtendedCommit),
    MAKESIGNED64(&MmZeroedPageListHead),
    MAKESIGNED64(&MmFreePageListHead),
    MAKESIGNED64(&MmStandbyPageListHead),
    MAKESIGNED64(&MmModifiedPageListHead),
    MAKESIGNED64(&MmModifiedNoWritePageListHead),
    MAKESIGNED64(&MmAvailablePages),
    MAKESIGNED64(&MmResidentAvailablePages),
    0, // ULONG64 PoolTrackTable;
    0, // ULONG64 NonPagedPoolDescriptor;
    MAKESIGNED64(&MmHighestUserAddress),
    MAKESIGNED64(&MmSystemRangeStart),
    MAKESIGNED64(&MmUserProbeAddress),
    MAKESIGNED64(&KdPrintCircularBuffer),
    MAKESIGNED64(&KdPrintCircularBufferEnd),
    MAKESIGNED64(&KdPrintWritePointer),
    MAKESIGNED64(&KdPrintRolloverCount),
    MAKESIGNED64(&MmLoadedUserImageList),
    MAKESIGNED64(&NtBuildLab), // ULONG64 NtBuildLab;
    0, // ULONG64 KiNormalSystemCall;
    0, // ULONG64 KiProcessorBlock;
    MAKESIGNED64(&MmUnloadedDrivers),
    MAKESIGNED64(&MmLastUnloadedDriver),
    MAKESIGNED64(&MmTriageActionTaken),
    MAKESIGNED64(&MmSpecialPoolTag),
    0, // ULONG64 KernelVerifier;
    MAKESIGNED64(&MmVerifierData),
    MAKESIGNED64(&MmAllocatedNonPagedPool),
    MAKESIGNED64(&MmPeakCommitment),
    MAKESIGNED64(&MmTotalCommitLimitMaximum),
    0, // ULONG64 CmNtCSDVersion;
    MAKESIGNED64(&MmPhysicalMemoryBlock),
    MAKESIGNED64(&MmSessionBase),
    MAKESIGNED64(&MmSessionSize),
    MAKESIGNED64(&MmSystemParentTablePage),
    MAKESIGNED64(&MmVirtualTranslationBase),
    FIELD_OFFSET(KTHREAD, NextProcessor), // USHORT OffsetKThreadNextProcessor;
    FIELD_OFFSET(KTHREAD, Teb), // USHORT OffsetKThreadTeb;
    FIELD_OFFSET(KTHREAD, KernelStack), // USHORT OffsetKThreadKernelStack;
    FIELD_OFFSET(KTHREAD, InitialStack), // USHORT OffsetKThreadInitialStack;
    FIELD_OFFSET(KTHREAD, ApcState.Process), // USHORT OffsetKThreadApcProcess;
    FIELD_OFFSET(KTHREAD, State), // USHORT OffsetKThreadState;
    0, // USHORT OffsetKThreadBStore;
    0, // USHORT OffsetKThreadBStoreLimit;
    sizeof(EPROCESS), // USHORT SizeEProcess;
    FIELD_OFFSET(EPROCESS, Peb), // USHORT OffsetEprocessPeb;
    0, // USHORT OffsetEprocessParentCID;
    FIELD_OFFSET(EPROCESS, Pcb.DirectoryTableBase), // USHORT OffsetEprocessDirectoryTableBase;
    sizeof(KPRCB), // USHORT SizePrcb;
    0, // USHORT OffsetPrcbDpcRoutine;
    0, // USHORT OffsetPrcbCurrentThread;
    FIELD_OFFSET(KPRCB, MHz), // USHORT OffsetPrcbMhz;
    FIELD_OFFSET(KPRCB, CpuType), // USHORT OffsetPrcbCpuType;
    FIELD_OFFSET(KPRCB, VendorString), // USHORT OffsetPrcbVendorString;
    FIELD_OFFSET(KPRCB, ProcessorState.ContextFrame), // USHORT OffsetPrcbProcStateContext;
    FIELD_OFFSET(KPRCB, LegacyNumber), // USHORT OffsetPrcbNumber;
    sizeof(ETHREAD), // USHORT SizeEThread;
    MAKESIGNED64(&KdPrintCircularBufferPtr),
    MAKESIGNED64(&KdPrintBufferSize),
    MAKESIGNED64(&KeLoaderBlock),
    sizeof(KPCREX), // USHORT SizePcr;
    FIELD_OFFSET(KPCR, Self), // USHORT OffsetPcrSelfPcr;
    FIELD_OFFSET(KPCR, CurrentPrcb), // USHORT OffsetPcrCurrentPrcb;
    FIELD_OFFSET(KPCREX, Prcb), // USHORT OffsetPcrContainedPrcb;
    0, // USHORT OffsetPcrInitialBStore;
    0, // USHORT OffsetPcrBStoreLimit;
    0, // USHORT OffsetPcrInitialStack;
    0, // USHORT OffsetPcrStackLimit;
    0, // USHORT OffsetPrcbPcrPage;
    FIELD_OFFSET(KPRCB, ProcessorState.SpecialRegisters), // USHORT OffsetPrcbProcStateSpecialReg;
    KGDT64_R0_CODE, // USHORT GdtR0Code;
    KGDT64_R0_DATA, // USHORT GdtR0Data;
    0, // USHORT GdtR0Pcr;
    KGDT64_R3_CODE, // USHORT GdtR3Code;
    KGDT64_R3_DATA, // USHORT GdtR3Data;
    0, // USHORT GdtR3Teb;
    0, // USHORT GdtLdt;
    KGDT64_SYS_TSS, // USHORT GdtTss;
    KGDT64_R3_CMCODE, // USHORT Gdt64R3CmCode;
    KGDT64_R3_CMTEB, // USHORT Gdt64R3CmTeb;
    0, // ULONG64 IopNumTriageDumpDataBlocks;
    0, // ULONG64 IopTriageDumpDataBlocks;
    0, // GCC_ULONG64 VfCrashDataBlock;
    MAKESIGNED64(&MmBadPagesDetected),
    MAKESIGNED64(&MmZeroedPageSingleBitErrorsDetected)
};

static DBGKD_GET_VERSION64 KdVersionBlock =
{
    0x0F, /* MajorVersion */
    0x1DB0, /* MinorVersion */
    DBGKD_64BIT_PROTOCOL_VERSION2, /* ProtocolVersion */
    CURRENT_KD_SECONDARY_VERSION, /* KdSecondaryVersion */
    DBGKD_VERS_FLAGS, /* Flags */
    IMAGE_FILE_MACHINE_NATIVE, /* MachineType */
    PACKET_TYPE_MAX, /* MaxPacketType */
    DbgKdMaximumStateChange - DbgKdMinimumStateChange, /* MaxStateChange */
    DbgKdMaximumManipulate - DbgKdMinimumManipulate, /* MaxManipulate */
    0, /* Simulation */
    {0}, /* Unused[1] */
    MAKESIGNED64(&__ImageBase), /* KernBase */
    MAKESIGNED64(&PsLoadedModuleList), /* PsLoadedModuleList */
    MAKESIGNED64(&KdpDebuggerDataListHead)/* DebuggerDataList */
};

NTSTATUS
NTAPI
KdEnableDebugger(void)
{
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
KdDisableDebugger(void)
{
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
KdChangeOption(
    __in KD_OPTION Option,
    __in_opt   ULONG InBufferBytes,
    __in       PVOID InBuffer,
    __in_opt   ULONG OutBufferBytes,
    __out      PVOID OutBuffer,
    __out_opt  PULONG OutBufferNeeded)
{
    __debugbreak();
    return 0;
}

BOOLEAN
NTAPI
KdRefreshDebuggerNotPresent(void)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KdLogDbgPrint(PANSI_STRING String)
{
    __debugbreak();
}

BOOLEAN
NTAPI
KdPollBreakIn(void)
{
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
KdPowerTransition(
    IN DEVICE_POWER_STATE NewState)
{
    __debugbreak();
    return 0;
}

typedef enum _SYSDBG_COMMAND SYSDBG_COMMAND;

NTSTATUS
NTAPI
KdSystemDebugControl(
    SYSDBG_COMMAND Command,
    PVOID InputBuffer,
    ULONG InputBufferLength,
    PVOID OutputBuffer,
    ULONG OutputBufferLength,
    PULONG ReturnLength,
    KPROCESSOR_MODE PreviousMode)
{
    __debugbreak();
    return 0;
}


VOID
NTAPI
KdPrintString(const CHAR *String)
{
    STRING MessageHeader, MessageData;
    KD_CONTEXT Context;
    DBGKD_DEBUG_IO DebugIoHeader;
    SIZE_T Length;

    Length = (ULONG)strlen(String);

    DebugIoHeader.ApiNumber = DbgKdPrintStringApi;
    DebugIoHeader.ProcessorLevel = 0;
    DebugIoHeader.Processor = 0;
    DebugIoHeader.u.PrintString.LengthOfString = (ULONG)Length;


    MessageHeader.Length = MessageHeader.MaximumLength = sizeof(DebugIoHeader);
    MessageHeader.Buffer = (PSTR)&DebugIoHeader;

    MessageData.Length = MessageData.MaximumLength = (USHORT)Length;
    MessageData.Buffer = (PSTR)String;

    KdSendPacket(PACKET_TYPE_KD_DEBUG_IO,
                 &MessageHeader,
                 &MessageData,
                 &Context);
}

ULONG
KdPrint(const char *Format, ...)
{
    va_list argptr;
    char buffer[256];

    va_start(argptr, Format);
    _vsnprintf(buffer, 256, Format, argptr);
    va_end(argptr);

    KdPrintString(buffer);

    return 0;
}

static
KDSTATUS
KdpReceivePacketRetry(
    IN ULONG PacketType,
    OUT PSTRING MessageHeader,
    OUT PSTRING MessageData,
    OUT PULONG DataLength,
    IN OUT PKD_CONTEXT Context)
{
    KDSTATUS KdStatus;

    do
    {
        /* Send the packet */
        KdStatus = KdReceivePacket(PacketType,
                                   MessageHeader,
                                   MessageData,
                                   DataLength,
                                   Context);

        /* Retry on timeout */
    } while (KdStatus == KdPacketTimedOut);

    return KdStatus;
}

static
VOID
KdpGetVersion(PDBGKD_MANIPULATE_STATE64 ManipulateState)
{
    PDBGKD_GET_VERSION64 GetVersion64 = &ManipulateState->u.GetVersion64;

    /* Copy the static table */
    RtlCopyMemory(GetVersion64, &KdVersionBlock, sizeof(DBGKD_GET_VERSION64));
    ManipulateState->ReturnStatus = STATUS_SUCCESS;
}

static
VOID
KdpReadVirtualMemory(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData)
{
    PDBGKD_READ_MEMORY64 ReadMemory = &ManipulateState->u.ReadMemory;
    ULONG TransferCount;
    NTSTATUS Status;
    //RawDbgPrint("KdpReadVirtualMemory\n");

    /* Don't let the transfer count go beyond the maximum */
    TransferCount = min(ReadMemory->TransferCount, PACKET_MAX_SIZE);

    /* Safely copy the memory */
    Status = MmDebugCopyMemory(MessageData->Buffer,
                               (PVOID)(ULONG_PTR)ReadMemory->TargetBaseAddress,
                               &TransferCount,
                               MmDebugCopyRead);

    ReadMemory->ActualBytesRead = TransferCount;
    MessageData->Length = (USHORT)TransferCount;
    ManipulateState->ReturnStatus = Status;
}

static
VOID
KdpWriteVirtualMemory(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData)
{
    PDBGKD_WRITE_MEMORY64 WriteMemory = &ManipulateState->u.WriteMemory;
    ULONG TransferCount;
    NTSTATUS Status;
    //RawDbgPrint("KdpWriteVirtualMemory\n");

    /* Don't let the transfer count go beyond the maximum */
    TransferCount = min(WriteMemory->TransferCount, PACKET_MAX_SIZE);

    /* Safely copy the memory */
    Status = MmDebugCopyMemory((PVOID)(ULONG_PTR)WriteMemory->TargetBaseAddress,
                               MessageData->Buffer,
                               &TransferCount,
                               MmDebugCopyRead);

    WriteMemory->ActualBytesWritten = TransferCount;
    MessageData->Length = (USHORT)TransferCount;
    ManipulateState->ReturnStatus = Status;
}

static
VOID
KdpReadPhysicalMemory(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData)
{
    PDBGKD_READ_MEMORY64 ReadMemory = &ManipulateState->u.ReadMemory;
    ULONG TransferCount;
    NTSTATUS Status;

    /* Don't let the transfer count go beyond the maximum */
    TransferCount = min(ReadMemory->TransferCount, PACKET_MAX_SIZE);

    /* Safely copy the memory */
    Status = MmDebugCopyPhysicalMemory(MessageData->Buffer,
                                       ReadMemory->TargetBaseAddress,
                                       TransferCount,
                                       FALSE);

    ReadMemory->ActualBytesRead = TransferCount;
    MessageData->Length = (USHORT)TransferCount;
    ManipulateState->ReturnStatus = Status;
}


static
VOID
KdpQueryMemory(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData)
{
    // FIXME
    ManipulateState->u.QueryMemory.Flags =  DBGKD_QUERY_MEMORY_READ |
                                            DBGKD_QUERY_MEMORY_WRITE |
                                            DBGKD_QUERY_MEMORY_EXECUTE;

    ManipulateState->ReturnStatus = STATUS_SUCCESS;
}



static
VOID
KdpHideAllBreakPoints(VOID)
{
    ULONG i, Size;

    /* Loop all break points */
    for (i = 0; i < KDP_MAX_BREAK_POINTS; i++)
    {
        /* Check if the break point is present */
        if (KdpBreakPointTable[i])
        {
            /* Restore the original instruction */
            Size = KDP_BREAKPOINT_LENGTH;
            MmDebugCopyMemory(KdpBreakPointTable[i],
                              KdpBreakPointBackupTable[i],
                              &Size,
                              MmDebugCopyWriteReadOnly);
        }
    }
}

static
VOID
KdpShowAllBreakPoints(VOID)
{
    ULONG Size, i;

    /* Loop all break points */
    for (i = 0; i < KDP_MAX_BREAK_POINTS; i++)
    {
        /* Check if the break point is present */
        if (KdpBreakPointTable[i])
        {
            /* Write the break point instruction */
            Size = KDP_BREAKPOINT_LENGTH;
            MmDebugCopyMemory(KdpBreakPointTable[i],
                              KdxBreakPointTemplate,
                              &Size,
                              MmDebugCopyWriteReadOnly);
        }
    }
}

static
VOID
KdpWriteBreakPoint(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData,
    IN PCONTEXT Context)
{
    PDBGKD_WRITE_BREAKPOINT64 WriteBreakPoint = &ManipulateState->u.WriteBreakPoint;
    PVOID BreakPointAddress = (PVOID)(ULONG_PTR)WriteBreakPoint->BreakPointAddress;
    ULONG Size, BreakPointNumber = 0;
    NTSTATUS Status;

    RawDbgPrint("KdpWriteBreakPoint %p\n", BreakPointAddress);

    /* Try to find a free break point slot */
    while ((BreakPointNumber < KDP_MAX_BREAK_POINTS) &&
           (KdpBreakPointTable[BreakPointNumber] != NULL)) BreakPointNumber++;

    /* Check for failure */
    if (BreakPointNumber == KDP_MAX_BREAK_POINTS)
    {
        /* All slots are full */
        ManipulateState->ReturnStatus = STATUS_UNSUCCESSFUL;
        WriteBreakPoint->BreakPointHandle = 0;
        return;
    }

    /* Safely copy the original instruction */
    Size = KDP_BREAKPOINT_LENGTH;
    Status = MmDebugCopyMemory(KdpBreakPointBackupTable[BreakPointNumber],
                               BreakPointAddress,
                               &Size,
                               MmDebugCopyRead);

    if (!NT_SUCCESS(Status))
    {
        ManipulateState->ReturnStatus = Status;
        return;
    }

    /* Write the break point */
    Size = KDP_BREAKPOINT_LENGTH;
    Status = MmDebugCopyMemory(BreakPointAddress,
                               KdxBreakPointTemplate,
                               &Size,
                               MmDebugCopyWriteReadOnly);
    if (NT_SUCCESS(Status))
    {
        /* Save the break point address */
        KdpBreakPointTable[BreakPointNumber] = BreakPointAddress;
        WriteBreakPoint->BreakPointHandle = BreakPointNumber + 1;
    }

    ManipulateState->ReturnStatus = Status;
}

static
VOID
KdpRestoreBreakPoint(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData)
{
    PDBGKD_RESTORE_BREAKPOINT RestoreBreakPoint = &ManipulateState->u.RestoreBreakPoint;
    ULONG BreakPointNumber = RestoreBreakPoint->BreakPointHandle - 1;
    NTSTATUS Status = STATUS_UNSUCCESSFUL;
    ULONG Size;

    /* Check if the break point is valid */
    if ( (BreakPointNumber >= KDP_MAX_BREAK_POINTS) ||
         (KdpBreakPointTable[BreakPointNumber] == NULL) )
    {
        ManipulateState->ReturnStatus = STATUS_UNSUCCESSFUL;
        return;
    }

    /* Restore the original instruction */
    Size = KDP_BREAKPOINT_LENGTH;
    Status =  MmDebugCopyMemory(KdpBreakPointTable[BreakPointNumber],
                                KdpBreakPointBackupTable[BreakPointNumber],
                                &Size,
                                MmDebugCopyWriteReadOnly);

    /* On success clear the break point */
    if (NT_SUCCESS(Status))
        KdpBreakPointTable[BreakPointNumber] = NULL;

    ManipulateState->ReturnStatus = Status;
}

static
VOID
KdpClearAllInternalBreakpoints(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState)
{
    NTSTATUS Status;
    ULONG i;
    ULONG Size;

    /* Loop all break points */
    for (i = 0; i < KDP_MAX_BREAK_POINTS; i++)
    {
        /* Check if the break point is present */
        if (KdpBreakPointTable[i])
        {
            /* Restore the original instruction */
            Size = KDP_BREAKPOINT_LENGTH;
            Status =  MmDebugCopyMemory(KdpBreakPointTable[i],
                                        KdpBreakPointBackupTable[i],
                                        &Size,
                                        MmDebugCopyWriteReadOnly);

            /* Delete the break point */
            KdpBreakPointTable[i] = 0;
        }
    }

    ManipulateState->ReturnStatus = STATUS_SUCCESS;
}

static
VOID
KdpGetContext(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData,
    IN PCONTEXT Context)
{
    RtlCopyMemory(MessageData->Buffer, Context, sizeof(CONTEXT));
    MessageData->Length = sizeof(CONTEXT);

    ManipulateState->ReturnStatus = STATUS_SUCCESS;
}

static
VOID
KdpSetContext(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData,
    IN PCONTEXT Context)
{
    ULONG Length = min(MessageData->Length, sizeof(CONTEXT));
    RtlCopyMemory(Context, MessageData->Buffer, Length);

    ManipulateState->ReturnStatus = STATUS_SUCCESS;
}

static
NTSTATUS
KdpContinue(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    IN PCONTEXT Context)
{
    PDBGKD_CONTINUE Continue = &ManipulateState->u.Continue;

    /* Show all break points */
    KdpShowAllBreakPoints();

    /* Return the status */
    return Continue->ContinueStatus;
}

static
NTSTATUS
KdpContinue2(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    IN PCONTEXT Context)
{
    PDBGKD_CONTINUE2 Continue2 = &ManipulateState->u.Continue2;

    /* Show all break points */
    KdpShowAllBreakPoints();

    /* Enable single stepping if requested */
    KxContextEnableSingleStep(Context, Continue2->ControlSet.TraceFlag);

    /* Return the status */
    return Continue2->ContinueStatus;
}


/*! \name KdpSendReceiveReplyLoop
 *
 *  \brief Sends a message to the kernel debugger, waits for an answer and
 *      handles the requested operation and loops until a continue message.
 *
 *  \param [in] SendPacketType
 *      The type of packet to be used for the first message.
 *
 *  \param [in] SendMessageHeader
 *      Pointer to a string containing the header for the first message.
 *
 *  \param [in] SendMessageData
 *      Pointer to a string containing the data for the first message.
 *
 *  \param [in] Context
 *      Pointer to a CONTEXT structure, containing the current context.
 *
 *  \remarks This function does not return, before the kernel debugger sents a
 *      continue message.
 */
NTSTATUS
NTAPI
KdpSendReceiveReplyLoop(
    IN ULONG SendPacketType,
    IN PSTRING SendMessageHeader,
    IN PSTRING SendMessageData,
    IN PCONTEXT Context)
{
    static CHAR KdpDataBuffer[PACKET_MAX_SIZE];
    STRING MessageHeader, MessageData;
    DBGKD_MANIPULATE_STATE64 ManipulateState;
    ULONG ReceiveLength;
    KD_CONTEXT KdContext;
    KDSTATUS KdStatus;

    /* Prepare KdContext */
    KdContext.KdpControlCPending = 0;
    KdContext.KdpDefaultRetries = 10;

    /* Prepare a receive header */
    MessageHeader.Buffer = (PCHAR)&ManipulateState;
    MessageHeader.MaximumLength = sizeof(ManipulateState);
    MessageHeader.Length = 0;

    /* Use the static buffer to receive data */
    MessageData.Buffer = KdpDataBuffer;
    MessageData.MaximumLength = sizeof(KdpDataBuffer);
    MessageData.Length = 0;

    /* Enter the loop */
    while (1)
    {
        /* Check if we have any message to send */
        if (SendPacketType != PACKET_TYPE_UNUSED)
        {
            /* Send the message */
            KdSendPacket(SendPacketType,
                         SendMessageHeader,
                         SendMessageData,
                         &KdContext);
        }

        /* Receive the answer from the kernel debugger */
        KdStatus = KdpReceivePacketRetry(PACKET_TYPE_KD_STATE_MANIPULATE,
                                         &MessageHeader,
                                         &MessageData,
                                         &ReceiveLength,
                                         &KdContext);

        /* The kernel debugger requests the previous message to be resent. */
        if (KdStatus == KdPacketNeedsResend)
        {
            RawDbgPrint("KdPacketNeedsResend\n");
            continue;
        }

        /* Check what operation the kernel debugger requests */
        switch (ManipulateState.ApiNumber)
        {
            case DbgKdGetVersionApi:
                KdpGetVersion(&ManipulateState);
                break;

            case DbgKdReadVirtualMemoryApi:
                KdpReadVirtualMemory(&ManipulateState, &MessageData);
                break;

            case DbgKdWriteVirtualMemoryApi:
                KdpWriteVirtualMemory(&ManipulateState, &MessageData);
                break;

            case DbgKdReadControlSpaceApi:
                KdxReadControlSpace(&ManipulateState, &MessageData);
                break;

            case DbgKdWriteControlSpaceApi:
                KdxWriteControlSpace(&ManipulateState, &MessageData);
                break;

            case DbgKdRestoreBreakPointApi:
                KdpRestoreBreakPoint(&ManipulateState, &MessageData);
                break;

            case DbgKdClearAllInternalBreakpointsApi:
                KdpClearAllInternalBreakpoints(&ManipulateState);

                /* Do not respond to this message */
                SendPacketType = PACKET_TYPE_UNUSED;
                continue;

            case DbgKdGetContextApi:
                KdpGetContext(&ManipulateState, &MessageData, Context);
                break;

            case DbgKdSetContextApi:
                KdpSetContext(&ManipulateState, &MessageData, Context);
                break;

            case DbgKdWriteBreakPointApi:
                KdpWriteBreakPoint(&ManipulateState, &MessageData, Context);
                break;

            case DbgKdReadMachineSpecificRegister:
                KdxReadMsr(&ManipulateState, &MessageData);
                break;

            case DbgKdWriteMachineSpecificRegister:
                KdxWriteMsr(&ManipulateState, &MessageData);
                break;

            case DbgKdQueryMemoryApi:
                KdpQueryMemory(&ManipulateState, &MessageData);
                break;

            case DbgKdReadPhysicalMemoryApi:
                KdpReadPhysicalMemory(&ManipulateState, &MessageData);
                break;

            case DbgKdReadIoSpaceApi:
            case DbgKdWriteIoSpaceApi:
            case DbgKdRebootApi:
            case DbgKdWritePhysicalMemoryApi:
            case DbgKdQuerySpecialCallsApi:
            case DbgKdSetSpecialCallApi:
            case DbgKdClearSpecialCallsApi:
            case DbgKdSetInternalBreakPointApi:
            case DbgKdGetInternalBreakPointApi:
            case DbgKdReadIoSpaceExtendedApi:
            case DbgKdWriteIoSpaceExtendedApi:
            case DbgKdWriteBreakPointExApi:
            case DbgKdRestoreBreakPointExApi:
            case DbgKdCauseBugCheckApi:
            case DbgKdSwitchProcessor:
            case DbgKdPageInApi:
            case OldVlm1:
            case OldVlm2:
            case DbgKdSearchMemoryApi:
            case DbgKdGetBusDataApi:
            case DbgKdSetBusDataApi:
            case DbgKdCheckLowMemoryApi:
            case DbgKdFillMemoryApi:
            case DbgKdSwitchPartition:
                RawDbgPrint("Unhandled ApiNumber %lx\n", ManipulateState.ApiNumber);
                for (;;);
                return STATUS_UNSUCCESSFUL;

            case DbgKdContinueApi:
                 return KdpContinue(&ManipulateState, Context);

            case DbgKdContinueApi2:
                return KdpContinue2(&ManipulateState, Context);

            default:
                RawDbgPrint("Invalid ApiNumber %lx\n", ManipulateState.ApiNumber);
                return STATUS_UNSUCCESSFUL;
        }

        /* Use the receive buffers for the reply */
        SendPacketType = PACKET_TYPE_KD_STATE_MANIPULATE;
        SendMessageHeader = &MessageHeader;
        SendMessageData = &MessageData;
    }
}

/*! \name KdpAnyWaitStateChange
 *
 *  \brief Does the common header initialization for the Kdp*StateChange
 *      functions and calls KdpSendReceiveReplyLoop to handle the communication
 *
 *  \param [in] NewState
 *      The type of state change message that is to be sent.
 *
 *  \param [in] WaitStateChange
 *      Pointer to a DBGKD_ANY_WAIT_STATE_CHANGE structure, that has the
 *      state specific part already initialized.
 *
 *  \param [in] Context
 *      Pointer to a CONTEXT structure holding the current machine context.
 *
 *  \param [in] MessageData
 *      Pointer to a string containing the message specific data that is to be
 *      sent in the message.
 */
VOID
NTAPI
KdpAnyWaitStateChange(
    IN ULONG NewState,
    IN PDBGKD_ANY_WAIT_STATE_CHANGE WaitStateChange,
    IN PCONTEXT Context,
    IN PSTRING MessageData)
{
    PDBGKD_CONTROL_REPORT ControlReport = &WaitStateChange->ControlReport;
    STRING MessageHeader;
    NTSTATUS Status;
    ULONG InstructionCount;

    /* Check for nested entry */
    if (KdpDebuggerActive)
    {
        RawDbgPrint("Nested debugger entry!\n");
        for (;;);
    }

    /* Remember the debugger is active */
    KdpDebuggerActive = TRUE;

    /* Initialize the common header fields */
    WaitStateChange->NewState = NewState;
    WaitStateChange->ProcessorLevel = 0;
    WaitStateChange->Processor = (USHORT)KeGetCurrentProcessorNumber();
    WaitStateChange->NumberProcessors = 1;
    WaitStateChange->Thread = MAKESIGNED64(KeGetCurrentThread());
    WaitStateChange->ProgramCounter = KxContextGetPc(Context);

    /* Hide all break points */
    KdpHideAllBreakPoints();

    /* Copy the instruction stream */
    InstructionCount = DBGKD_MAXSTREAM;
    Status = MmDebugCopyMemory(ControlReport->InstructionStream,
                               (PVOID)WaitStateChange->ProgramCounter,
                               &InstructionCount,
                               MmDebugCopyRead);

    ControlReport->InstructionCount = (USHORT)InstructionCount;

    /* Fill the architecture specific part of the ControlReport */
    KdxFillControlReport(ControlReport, Context);

    /* Setup the message header string */
    MessageHeader.Length = MessageHeader.MaximumLength = sizeof(*WaitStateChange);
    MessageHeader.Buffer = (PSTR)WaitStateChange;

    /* Jump with the header and data into the send / receive loop */
    KdpSendReceiveReplyLoop(PACKET_TYPE_KD_STATE_CHANGE64,
                            &MessageHeader,
                            MessageData,
                            Context);

    /* Debugger is not active */
    KdpDebuggerActive = FALSE;
}


/*! \name KdLoadSymbolsStateChange
 *
 *  \brief Sends a packet to inform the kernel debugger about a loaded module.
 *
 *  \param [in] PathName
 *      Pointer to a zero terminated string that contains the full path name.
 *      Example: '\SystemRoot\system32\mydriver.sys'
 *
 *  \param [in] ImageBase
 *      Pointer to the module's image base.
 *
 *  \remarks The PathName string must be zero terminated
 *
 */
VOID
NTAPI
KdLoadSymbolsStateChange(
    IN PCHAR PathName,
    IN PVOID ImageBase)
{
    DBGKD_ANY_WAIT_STATE_CHANGE StateChange;
    PIMAGE_NT_HEADERS NtHeader;
    STRING MessageData;
    CONTEXT Context;

    /* Get the NT header (FIXME: this is not safe for user mode modules) */
    NtHeader = RtlImageNtHeader(ImageBase);
    if (!NtHeader)
    {
        RawDbgPrint("NtHeader == NULL!\n");
        return;
    }

    /* Initialize the message data string (0 terminated!) */
    MessageData.Buffer = PathName;
    MessageData.Length = (USHORT)strlen(PathName) + 1;
    MessageData.MaximumLength = MessageData.Length;

    /* Setup the specific part of the message header */
    StateChange.u.LoadSymbols.PathNameLength = MessageData.Length;
    StateChange.u.LoadSymbols.BaseOfDll = (LONG_PTR)ImageBase;
    StateChange.u.LoadSymbols.ProcessId = 0xFFFFFFFF;
    StateChange.u.LoadSymbols.CheckSum = NtHeader->OptionalHeader.CheckSum;
    StateChange.u.LoadSymbols.SizeOfImage = NtHeader->OptionalHeader.SizeOfImage;
    StateChange.u.LoadSymbols.UnloadSymbols = FALSE;

    Context.ContextFlags = 0x10001f;
    RtlCaptureContext(&Context);

    /* Do the common work */
    KdpAnyWaitStateChange(DbgKdLoadSymbolsStateChange,
                          &StateChange,
                          &Context,
                          &MessageData);
}

NTSTATUS
NTAPI
KdExceptionStateChange(
    PEXCEPTION_RECORD ExceptionRecord,
    PCONTEXT ExceptionContext,
    BOOLEAN FirstChance)
{
    DBGKD_ANY_WAIT_STATE_CHANGE StateChange;
    PEXCEPTION_RECORD64 ExceptionRecord64;
    STRING MessageData;
    ULONG i;

    /* Initialize the message data string */
    MessageData.Buffer = NULL;
    MessageData.Length = 0;
    MessageData.MaximumLength = 0;

    /* Setup the specific part of the message header */
    StateChange.u.Exception.FirstChance = FirstChance;

    /* Copy the exception record to the 64 bit version */
    ExceptionRecord64 = &StateChange.u.Exception.ExceptionRecord;
    ExceptionRecord64->ExceptionCode = ExceptionRecord->ExceptionCode;
    ExceptionRecord64->ExceptionFlags = ExceptionRecord->ExceptionFlags;
    ExceptionRecord64->ExceptionRecord = (ULONG64)ExceptionRecord->ExceptionRecord;
    ExceptionRecord64->ExceptionAddress = (ULONG64)ExceptionRecord->ExceptionAddress;
    ExceptionRecord64->NumberParameters = ExceptionRecord->NumberParameters;
    for (i = 0; i < EXCEPTION_MAXIMUM_PARAMETERS; i++)
    {
        ExceptionRecord64->ExceptionInformation[i] =
            ExceptionRecord->ExceptionInformation[i];
    }

    /* Do the common work */
    KdpAnyWaitStateChange(DbgKdExceptionStateChange,
                          &StateChange,
                          ExceptionContext,
                          &MessageData);
    return STATUS_SUCCESS;
}

ULONG
NTAPI
KdDebugServiceHandler(
    ULONG Service,
    PVOID Buffer,
    SIZE_T Length,
    KPROCESSOR_MODE PreviousMode)
{
    NTSTATUS Status = STATUS_SUCCESS;

    _SEH2_TRY
    {
        if (PreviousMode != KernelMode)
        {
            ProbeForRead(Buffer, Length, 1);
        }

        // FIXME: this might be a problem, due to nested debugger entry
        KdPrintString(Buffer);
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        Status = _SEH2_GetExceptionCode();
    }
    _SEH2_END;

    return Status;
}


static LDR_DATA_TABLE_ENTRY LdrCoreEntries[3];

static
void
KdpInitModuleList(IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    PLDR_DATA_TABLE_ENTRY LdrEntry;
    PLIST_ENTRY Entry;
    ULONG i;

    /* Initialize the list head */
    InitializeListHead(&PsLoadedModuleList);

    /* Loop the first 3 entries */
    for (Entry = LoaderBlock->LoadOrderListHead.Flink, i = 0;
         Entry != &LoaderBlock->LoadOrderListHead && i < 3;
         Entry = Entry->Flink, i++)
    {
        /* Get the data table entry */
        LdrEntry = CONTAINING_RECORD(Entry,
                                     LDR_DATA_TABLE_ENTRY,
                                     InLoadOrderLinks);

        /* Copy the entry */
        LdrCoreEntries[i] = *LdrEntry;

        /* Insert the copy into the list */
        InsertTailList(&PsLoadedModuleList, &LdrCoreEntries[i].InLoadOrderLinks);
    }
}

INIT_FUNCTION
VOID
NTAPI
KdInitialize(PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    /* Set pointer to the version block */
    KeGetPcr()->KdVersionBlock = &KdVersionBlock;

    /* Initialize the kernel debugger dll */
    KdDebuggerInitialize0(LoaderBlock);

    /* Initialized some lists */
    KdpDebuggerDataListHead.Flink = (PLIST_ENTRY)&KdpDebuggerData;
    KdpDebuggerDataListHead.Blink = (PLIST_ENTRY)&KdpDebuggerData;

    /* Create the initial loaded module list */
    KdpInitModuleList(LoaderBlock);

    /* Tell the kernel debugger about the loaded kernel */
    KdLoadSymbolsStateChange("\\SystemRoot\\system32\\ntoskrnl.exe",
                             LdrCoreEntries[0].DllBase);

    KdLoadSymbolsStateChange("\\SystemRoot\\system32\\hal.dll",
                             LdrCoreEntries[1].DllBase);
}





#include <ntoskrnl.h>
#include <windbgkd.h>
#include <kddll.h>



BOOLEAN KdDebuggerNotPresent;
LIST_ENTRY PsLoadedModuleList;
LIST_ENTRY KdpDebuggerDataListHead;

static CHAR KdpDataBuffer[PACKET_MAX_SIZE];


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




NTSTATUS
NTAPI
KdpSafeCopyMemory(
    IN PVOID Destination,
    IN PVOID Source,
    IN SIZE_T Size)
{
    // FIXME!
    RtlCopyMemory(Destination, Source, Size);
    return STATUS_SUCCESS;
}


VOID
NTAPI
KdpSendReceiveReplyLoop(
    IN ULONG SendPacketType,
    OUT PSTRING SendMessageHeader,
    OUT PSTRING SendMessageData)
{
    STRING ReceiveHeader, ReceiveData;
    DBGKD_MANIPULATE_STATE64 ManipulateState;
    ULONG ReceiveLength;
    KD_CONTEXT KdContext;
    KDSTATUS KdStatus;

    /* Prepare a receive header */
    ReceiveHeader.Buffer = (PCHAR)&ManipulateState;
    ReceiveHeader.MaximumLength = sizeof(ManipulateState);
    ReceiveHeader.Length = 0;

    /* Use the static buffer to receive data */
    ReceiveData.Buffer = KdpDataBuffer;
    ReceiveData.MaximumLength = sizeof(KdpDataBuffer);
    ReceiveData.Length = 0;

    while (1)
    {
        /* Send the message */
        KdSendPacket(SendPacketType,
                     SendMessageHeader,
                     SendMessageData,
                     &KdContext);

        /* Receive the answer from the kernel debugger */
        KdStatus = KdpReceivePacketRetry(PACKET_TYPE_KD_STATE_MANIPULATE,
                                         &ReceiveHeader,
                                         &ReceiveData,
                                         &ReceiveLength,
                                         &KdContext);

        /* The kernel debugger requests the previous message to be resent. */
        if (KdStatus == KdPacketNeedsResend) continue;

        /* Check what the kernel debugger wants */
        switch (ManipulateState.ApiNumber)
        {
            case DbgKdGetVersionApi:
                KdpGetVersion(&ManipulateState);
                break;

            case DbgKdReadVirtualMemoryApi:
                KdpReadVirtualMemory(&ManipulateState, &ReceiveData);
                break;

            case DbgKdWriteVirtualMemoryApi:
            case DbgKdGetContextApi:
            case DbgKdSetContextApi:
            case DbgKdWriteBreakPointApi:
            case DbgKdRestoreBreakPointApi:
            case DbgKdContinueApi:
            case DbgKdReadControlSpaceApi:
            case DbgKdWriteControlSpaceApi:
            case DbgKdReadIoSpaceApi:
            case DbgKdWriteIoSpaceApi:
            case DbgKdRebootApi:
            case DbgKdContinueApi2:
            case DbgKdReadPhysicalMemoryApi:
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
            case DbgKdReadMachineSpecificRegister:
            case DbgKdWriteMachineSpecificRegister:
            case OldVlm1:
            case OldVlm2:
            case DbgKdSearchMemoryApi:
            case DbgKdGetBusDataApi:
            case DbgKdSetBusDataApi:
            case DbgKdCheckLowMemoryApi:
            case DbgKdClearAllInternalBreakpointsApi:
            case DbgKdFillMemoryApi:
            case DbgKdQueryMemoryApi:
            case DbgKdSwitchPartition:
                KdPrint("Unhandled ApiNumber %lx\n", ManipulateState.ApiNumber);
                return;

            default:
                KdPrint("Invalid ApiNumber %lx\n", ManipulateState.ApiNumber);
                return;
        }

        /* Use the receive buffers for the reply */
        SendPacketType = PACKET_TYPE_KD_STATE_MANIPULATE;
        SendMessageHeader = &ReceiveHeader;
        SendMessageData = &ReceiveData;

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
 *  \param [in] ProgramCounter
 *      Value of the instruction pointer (eip, rip, ...) to be used in the
 *      message.
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
    IN ULONG64 ProgramCounter,
    IN PSTRING MessageData)
{
    STRING MessageHeader;

    /* Initialize the common header fields */
    WaitStateChange->NewState = NewState;
    WaitStateChange->ProcessorLevel = 0;
    WaitStateChange->Processor = 0;
    WaitStateChange->NumberProcessors = 1;
    WaitStateChange->Thread = 0; // KeGetCurrentThread();
    WaitStateChange->ProgramCounter = ProgramCounter;

    //FIXME: fill WaitStateChange.AnyControlReport

    /* Setup the message header string */
    MessageHeader.Length = MessageHeader.MaximumLength = sizeof(*WaitStateChange);
    MessageHeader.Buffer = (PSTR)WaitStateChange;

    /* Jump with the header and data into the send / receive loop */
    KdpSendReceiveReplyLoop(PACKET_TYPE_KD_STATE_CHANGE64,
                            &MessageHeader,
                            MessageData);
}


/*! \name KdpLoadSymbolsStateChange
 *
 *  \brief Sends a packet to inform the kernel debugger about a loaded module.
 *
 *  \param [in] PathName
 *      Pointer to a string that contains the full path name of the module.
 *      Example: '\SystemRoot\system32\mydriver.sys'
 *
 *  \param [in] ImageBase
 *      Pointer to the module's image base.
 */
VOID
NTAPI
KdpLoadSymbolsStateChange(
    IN PSTRING PathName,
    IN PVOID ImageBase)
{
    DBGKD_ANY_WAIT_STATE_CHANGE StateChange;
    PIMAGE_NT_HEADERS NtHeader;

    /* Get the NT header */
    NtHeader = RtlImageNtHeader(ImageBase);
    if (!NtHeader)
    {
        FrLdrDbgPrint("NtHeader == NULL!\n");
        return;
    }

    /* Setup the specific part of the message header */
    StateChange.u.LoadSymbols.PathNameLength = PathName->Length;
    StateChange.u.LoadSymbols.BaseOfDll = (LONG_PTR)ImageBase;
    StateChange.u.LoadSymbols.ProcessId = 0xFFFFFFFF;
    StateChange.u.LoadSymbols.CheckSum = NtHeader->OptionalHeader.CheckSum;
    StateChange.u.LoadSymbols.SizeOfImage = NtHeader->OptionalHeader.SizeOfImage;
    StateChange.u.LoadSymbols.UnloadSymbols = FALSE;

    /* Do the common work */
    KdpAnyWaitStateChange(DbgKdLoadSymbolsStateChange,
                          &StateChange,
                          (ULONG_PTR)_ReturnAddress(),
                          PathName);
}

VOID
NTAPI
KdInitialize(PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    STRING KernelImageName = RTL_CONSTANT_STRING("\\SystemRoot\\system32\\ntoskrnl.exe");

    /* Initialize the kernel debugger dll */
    KdDebuggerInitialize0(LoaderBlock);

    InitializeListHead(&PsLoadedModuleList);
    InitializeListHead(&KdpDebuggerDataListHead);

    /* Send an empty string to initialize */
    KdPrintString("");

    /* Say hello! */
    KdPrintString("Hello from WinDebug!\n");

    KdpLoadSymbolsStateChange(&KernelImageName, &__ImageBase);
}


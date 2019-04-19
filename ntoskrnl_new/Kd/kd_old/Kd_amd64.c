#include <ntoskrnl.h>
#include <windbgkd.h>
#include <kddll.h>
#include "Kd_internal.h"
#include "../Ke/Ke_internal.h"

UCHAR KdxBreakPointTemplate[1] = {0xCC};

VOID
NTAPI
KdxFillControlReport(
    IN PDBGKD_CONTROL_REPORT ControlReport,
    IN PCONTEXT Context)
{
    ControlReport->ReportFlags = REPORT_INCLUDES_SEGS;

    ControlReport->Dr6 = Context->Dr6;
    ControlReport->Dr7 = Context->Dr7;
    ControlReport->EFlags = Context->EFlags;
    ControlReport->SegCs = Context->SegCs;
    ControlReport->SegDs = Context->SegDs;
    ControlReport->SegEs = Context->SegEs;
    ControlReport->SegFs = Context->SegFs;
}

VOID
NTAPI
KdxReadControlSpace(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData)
{
    PDBGKD_READ_MEMORY64 ReadMemory = &ManipulateState->u.ReadMemory;
    PVOID ControlStart;
    PKPCR Pcr = KeGetPcrFromNumber(ManipulateState->Processor);
    PKPRCB Prcb = Pcr->CurrentPrcb;
    ULONG TransferCount;
    RawDbgPrint("KdpReadControlSpace %p\n", ReadMemory->TargetBaseAddress);

    switch ((ULONG64)ReadMemory->TargetBaseAddress)
    {
        case AMD64_DEBUG_CONTROL_SPACE_KPCR:
            /* Copy a pointer to the Pcr */
            ControlStart = &Pcr;
            TransferCount = sizeof(PVOID);
            break;

        case AMD64_DEBUG_CONTROL_SPACE_KPRCB:
            /* Copy a pointer to the Prcb */
            ControlStart = &Prcb;
            TransferCount = sizeof(PVOID);
            break;

        case AMD64_DEBUG_CONTROL_SPACE_KSPECIAL:
            /* Copy SpecialRegisters */
            ControlStart = &Prcb->ProcessorState.SpecialRegisters;
            TransferCount = sizeof(KSPECIAL_REGISTERS);
            break;

        case AMD64_DEBUG_CONTROL_SPACE_KTHREAD:
            /* Copy a pointer to the current Thread */
            ControlStart = &Prcb->CurrentThread;
            TransferCount = sizeof(PVOID);
            break;

        default:
            RawDbgPrint("invalid control space %p\n", ReadMemory->TargetBaseAddress);
            ReadMemory->ActualBytesRead = 0;
            ManipulateState->ReturnStatus = STATUS_UNSUCCESSFUL;
            return;
    }

    /* Do not go beyond the requested size */
    TransferCount = min(ReadMemory->TransferCount, TransferCount);

    /* Copy the data */
    RtlCopyMemory(MessageData->Buffer, ControlStart, TransferCount);
    MessageData->Length = (USHORT)TransferCount;

    /* Return success */
    ReadMemory->ActualBytesRead = TransferCount;
    ManipulateState->ReturnStatus = STATUS_SUCCESS;
}

VOID
NTAPI
KdxWriteControlSpace(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData)
{
    PDBGKD_READ_MEMORY64 ReadMemory = &ManipulateState->u.ReadMemory;
    PVOID ControlStart;
    PKPCR Pcr = KeGetPcrFromNumber(ManipulateState->Processor);
    PKPRCB Prcb = Pcr->CurrentPrcb;
    ULONG TransferCount;
    //RawDbgPrint("KdpReadControlSpace %p\n", ReadMemory->TargetBaseAddress);

    switch ((UINT64)ReadMemory->TargetBaseAddress)
    {
        case AMD64_DEBUG_CONTROL_SPACE_KSPECIAL:
            /* Copy SpecialRegisters */
            ControlStart = &Prcb->ProcessorState.SpecialRegisters;
            TransferCount = sizeof(KSPECIAL_REGISTERS);
            break;

        case AMD64_DEBUG_CONTROL_SPACE_KTHREAD:
        case AMD64_DEBUG_CONTROL_SPACE_KPCR:
        case AMD64_DEBUG_CONTROL_SPACE_KPRCB:
        default:
            //RawDbgPrint("invalid control space %p\n", ReadMemory->TargetBaseAddress);
            ReadMemory->ActualBytesRead = 0;
            ManipulateState->ReturnStatus = STATUS_UNSUCCESSFUL;
            return;
    }

    /* Do not go beyond the requested size */
    TransferCount = min(ReadMemory->TransferCount, TransferCount);

    /* Copy the data */
    RtlCopyMemory(ControlStart, MessageData->Buffer, TransferCount);
    MessageData->Length = (USHORT)TransferCount;

    /* Return success */
    ReadMemory->ActualBytesRead = TransferCount;
    ManipulateState->ReturnStatus = STATUS_SUCCESS;
}

VOID
KdxReadMsr(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData)
{
    PDBGKD_READ_WRITE_MSR ReadWriteMsr = &ManipulateState->u.ReadWriteMsr;
    UINT64 Value;

    // FIXME: protect this somehow
    Value = __readmsr(ReadWriteMsr->Msr);
    ReadWriteMsr->DataValueHigh = Value >> 32;
    ReadWriteMsr->DataValueLow = Value & 0xFFFFFFFF;

    ManipulateState->ReturnStatus = STATUS_SUCCESS;
}

VOID
KdxWriteMsr(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData)
{
    PDBGKD_READ_WRITE_MSR ReadWriteMsr = &ManipulateState->u.ReadWriteMsr;
    UINT64 Value;

    // FIXME: protect this somehow
    Value = (UINT64)ReadWriteMsr->DataValueHigh << 32;
    Value |= ReadWriteMsr->DataValueLow;

    __writemsr(ReadWriteMsr->Msr, Value);

    ManipulateState->ReturnStatus = STATUS_SUCCESS;
}

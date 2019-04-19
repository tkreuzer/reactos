
#include <ntbase.h>
#include <ntstatus.h>
#include "../Ke/KeTypes.hpp"
#include <RtlString.hpp>

/*! \name KdBlockEnable
 *
 * \ref http://msdn.microsoft.com/en-us/library/windows/hardware/ff548078%28v=vs.85%29.aspx
 */
static UCHAR KdBlockEnable;


extern "C" {

/*! \name KdDebuggerEnabled
 *
 * \ref
 */
BOOLEAN KdDebuggerEnabled;

/*! \name KdDebuggerNotPresent
 *
 * \ref
 */
extern __declspec(dllimport) BOOLEAN KdDebuggerNotPresent;

/*! \name KdEnteredDebugger
 *
 * \ref
 */
BOOLEAN KdEnteredDebugger;

/// \todo move to header
typedef enum _KD_OPTION
{
    KD_OPTION_SET_BLOCK_ENABLE,
} KD_OPTION;

/*! \name KdChangeOption
 *
 * \ref http://msdn.microsoft.com/en-us/library/windows/hardware/ff548078%28v=VS.85%29.aspx
 */
NTSTATUS
NTAPI
KdChangeOption(
    _In_ KD_OPTION Option,
    _In_opt_ ULONG InBufferBytes,
    _In_ PVOID InBuffer,
    _In_opt_ ULONG OutBufferBytes,
    _Out_ PVOID OutBuffer,
    _Out_opt_ PULONG OutBufferNeeded)
{
    NTSTATUS status;

    (void)OutBufferNeeded;

    // if (no debugger)
        // return STATUS_DEBUGGER_INACTIVE;

    switch (Option)
    {
    case KD_OPTION_SET_BLOCK_ENABLE:
        if ((InBufferBytes != sizeof(BOOLEAN)) ||
             (OutBufferBytes != 0) ||
             (OutBuffer != NULL))
        {
            return STATUS_INVALID_PARAMETER;
        }

        /* Check if enabling is blocked. See KdChangeOption */
        if (KdBlockEnable & 0x80)
        {
            return STATUS_ACCESS_DENIED;
        }

        KdBlockEnable = *reinterpret_cast<PUCHAR>(InBuffer);
        status = STATUS_SUCCESS;
        break;

    default:
        return STATUS_INVALID_INFO_CLASS;
    }

    return status;
}

/*! \name KdDisableDebugger
 *
 * \ref http://msdn.microsoft.com/en-us/library/windows/hardware/ff548083%28v=VS.85%29.aspx
 */
NTSTATUS
NTAPI
KdDisableDebugger (
    VOID)
{
    NTSTATUS status;

    status = STATUS_SUCCESS;//g_KernelDebugger->DisableDebugger();
    if (NT_SUCCESS(status))
    {
        KdDebuggerEnabled = FALSE;
    }

    return status;
}


/*! \name KdEnableDebugger
 *
 * \ref http://msdn.microsoft.com/en-us/library/windows/hardware/ff548085%28v=VS.85%29.aspx
 * \ref http://msdn.microsoft.com/en-us/library/windows/hardware/ff548078%28v=vs.85%29.aspx
 */
NTSTATUS
NTAPI
KdEnableDebugger (
    VOID)
{
    NTSTATUS status;

    /* Check if enabling is blocked. */
    if (KdBlockEnable != FALSE)
    {
        return STATUS_ACCESS_DENIED;
    }

    status = STATUS_SUCCESS; // g_KernelDebugger->EnableDebugger();
    if (NT_SUCCESS(status))
    {
        KdDebuggerEnabled = TRUE;
    }

    return status;
}

/*! \name KdLogDbgPrint
 *
 * \ref
 */
VOID
NTAPI
KdLogDbgPrint (
    _In_ PSTRING String)
{
    (void)String;
    // should log debugprints while WinDbg is not connected
    __debugbreak();
}

/*! \name KdPollBreakIn
 *
 * \remarks
 *     - being called by KeUpdateSystemTime
 * \ref http://www.eggheadcafe.com/microsoft/Windows-Debugging/35999094/losing-serial-connection-to-debug-kernel.aspx
 */
VOID
NTAPI
KdPollBreakIn (
    VOID)
{
    //g_KernelDebugger->PollBreakIn();
}

/*! \name KdPowerTransition
 *
 * \ref
 */
NTSTATUS
NTAPI
KdPowerTransition (
    _In_ enum _DEVICE_POWER_STATE NewState)
{
    (void)NewState;
    return STATUS_NOT_IMPLEMENTED; // g_KernelDebugger->PowerTransition(NewState);;
}

/*! \name KdRefreshDebuggerNotPresent
 *
 * \ref http://msdn.microsoft.com/en-us/library/windows/hardware/ff548109%28v=VS.85%29.aspx
 */
BOOLEAN
NTAPI
KdRefreshDebuggerNotPresent (
    VOID)
{
    KdDebuggerNotPresent = !0;//!g_KernelDebugger->DebuggerPresent();
    return KdDebuggerNotPresent;
}

typedef enum _SYSDBG_COMMAND
{
    SYSDBG_COMMAND_1,
} SYSDBG_COMMAND;

typedef UCHAR KPROCESSOR_MODE;


/*! \name KdSystemDebugControl
 *
 * \ref http://www.ivanlef0u.tuxfamily.org/?p=382
 */
NTSTATUS
NTAPI
KdSystemDebugControl (
    _In_ SYSDBG_COMMAND Command,
    _In_ PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Inout_ PULONG ReturnLength,
    _In_ KPROCESSOR_MODE PreviousMode)
{
    (void)Command;
    (void)InputBuffer;
    (void)InputBufferLength;
    (void)OutputBuffer;
    (void)OutputBufferLength;
    (void)ReturnLength;
    (void)PreviousMode;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"

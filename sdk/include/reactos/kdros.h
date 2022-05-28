


#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if 0

FORCEINLINE
VOID
KdRosDumpAllThreads(VOID)
{
    KdSystemDebugControl((SYSDBG_COMMAND)' soR', (PVOID)DumpAllThreads, 0, 0, 0, 0, 0);
}

FORCEINLINE
VOID
KdRosDumpUserThreads(VOID)
{
    KdSystemDebugControl((SYSDBG_COMMAND)' soR', (PVOID)DumpUserThreads, 0, 0, 0, 0, 0);
}

FORCEINLINE
VOID
KdRosDumpArmPfnDatabase(VOID)
{
    KdSystemDebugControl((SYSDBG_COMMAND)' soR', (PVOID)KdSpare3, 0, 0, 0, 0, 0);
}
#endif

FORCEINLINE
VOID
KdRosSetDebugCallback(
    ULONG Id,
    PVOID Callback)
{
    KdSystemDebugControl((SYSDBG_COMMAND)'CsoR', Callback, Id, 0, 0, 0, 0);
}

FORCEINLINE
VOID
KdRosDumpStackFrames(
    ULONG Count,
    PULONG_PTR Backtrace)
{
    KdSystemDebugControl((SYSDBG_COMMAND)'DsoR', Backtrace, Count, 0, 0, 0, 0);
}

#if defined(KDBG)
typedef
BOOLEAN
(NTAPI KDBG_CLI_ROUTINE)(
    IN PCHAR Command,
    IN ULONG Argc,
    IN PCH Argv[]);
typedef KDBG_CLI_ROUTINE *PKDBG_CLI_ROUTINE;

FORCEINLINE
ULONG
KdRosRegisterCliCallback(
    PKDBG_CLI_ROUTINE Callback)
{
    return KdSystemDebugControl((SYSDBG_COMMAND)'RbdK', Callback, FALSE, 0, 0, 0, 0);
}

FORCEINLINE
VOID
KdRosDeregisterCliCallback(
    PKDBG_CLI_ROUTINE Callback)
{
    KdSystemDebugControl((SYSDBG_COMMAND)'RbdK', Callback, TRUE, 0, 0, 0, 0);
}
#endif

#ifdef __cplusplus
} // extern "C"
#endif

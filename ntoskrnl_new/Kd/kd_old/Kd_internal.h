

#ifdef CONFIG_SMP
#define DBGKD_VERS_FLAG_CPU DBGKD_VERS_FLAG_MP
#else
#define DBGKD_VERS_FLAG_CPU 0
#endif
#ifdef _WIN64
#define DBGKD_VERS_FLAG_PTR DBGKD_VERS_FLAG_PTR64
#else
#define DBGKD_VERS_FLAG_PTR 0
#endif
#define DBGKD_VERS_FLAGS (DBGKD_VERS_FLAG_CPU|DBGKD_VERS_FLAG_PTR|DBGKD_VERS_FLAG_DATA)

#define KDP_BREAKPOINT_LENGTH 1
#define KDP_MAX_BREAK_POINTS 32

#define MAKESIGNED64(x) ((ULONG64)(LONG64)(LONG_PTR)(x))
extern UCHAR RtlpBreakWithStatusInstruction;
extern UCHAR KdxBreakPointTemplate[];

NTSTATUS
NTAPI
KdpSafeCopyMemory(
    IN PVOID Destination,
    IN PVOID Source,
    IN SIZE_T Size,
    BOOLEAN Write);

VOID
NTAPI
KdxFillControlReport(
    IN PDBGKD_CONTROL_REPORT ControlReport,
    IN PCONTEXT Context);

VOID
NTAPI
KdxReadControlSpace(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData);

VOID
NTAPI
KdxWriteControlSpace(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData);

VOID
NTAPI
KdxReadMsr(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData);

VOID
NTAPI
KdxWriteMsr(
    IN PDBGKD_MANIPULATE_STATE64 ManipulateState,
    OUT PSTRING MessageData);


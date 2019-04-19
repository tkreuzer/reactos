

VOID
NTAPI
KdInitialize(PLOADER_PARAMETER_BLOCK LoaderBlock);

VOID
NTAPI
KdPrintString(const CHAR *String);

#undef KdPrint
#undef KdPrintEx

ULONG
KdPrint(const char *Format, ...);

VOID
NTAPI
KdLoadSymbolsStateChange(
    IN PCHAR PathName,
    IN PVOID ImageBase);

NTSTATUS
NTAPI
KdExceptionStateChange(
    PEXCEPTION_RECORD ExceptionRecord,
    PCONTEXT Context,
    BOOLEAN FirstChance);


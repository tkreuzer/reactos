
#include "Exp.hpp"

extern "C" {

DECLSPEC_NORETURN
NTSYSAPI
VOID
NTAPI
RtlRaiseStatus (
    _In_ NTSTATUS Status);

_IRQL_requires_max_(APC_LEVEL)
DECLSPEC_NORETURN
VOID
NTAPI
ExRaiseAccessViolation (
    VOID)
{
    RtlRaiseStatus(STATUS_ACCESS_VIOLATION);
}

_IRQL_requires_max_(APC_LEVEL)
DECLSPEC_NORETURN
VOID
NTAPI
ExRaiseDatatypeMisalignment (
    VOID)
{
    RtlRaiseStatus(STATUS_DATATYPE_MISALIGNMENT);
}

_IRQL_requires_max_(APC_LEVEL)
int
NTAPI
ExSystemExceptionFilter(
    VOID)
{
    __debugbreak();
    return 0;
}

}; // extern "C"


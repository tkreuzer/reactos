
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

WINBASEAPI
BOOL
WINAPI
SetThreadStackGuarantee(
    _Inout_ PULONG StackSizeInBytes
    );

FORCEINLINE
HANDLE
GetCurrentThreadEffectiveToken (
    VOID)
{
    return (HANDLE)(LONG_PTR)-6;
}


#ifdef __cplusplus
} // extern "C"
#endif

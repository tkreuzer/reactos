
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//#if (_WIN32_WINNT >= 0x0600)

WINBASEAPI
BOOL
WINAPI
InitializeCriticalSectionEx(
    _Out_ LPCRITICAL_SECTION lpCriticalSection,
    _In_ DWORD dwSpinCount,
    _In_ DWORD Flags
    );

//#endif // (_WIN32_WINNT >= 0x0600)

#ifdef __cplusplus
} // extern "C"
#endif

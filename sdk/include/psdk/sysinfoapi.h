
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)

WINBASEAPI
VOID
WINAPI
GetSystemTimePreciseAsFileTime(
    _Out_ LPFILETIME lpSystemTimeAsFileTime
    );

//#endif // (_WIN32_WINNT >= _WIN32_WINNT_WIN8)

#ifdef __cplusplus
} // extern "C"
#endif

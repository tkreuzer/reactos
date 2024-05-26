//
// __security_check_cookie.c
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Implementation of __security_check_cookie.
//
// SPDX-License-Identifier: MIT
//

#include <intrin.h>
#include <ntrtl.h>

#if defined(_M_IX86)
    void __fastcall __security_check_cookie(_In_ uintptr_t _StackCookie)
#elif defined(_M_ARM64EC)
    void __cdecl __security_check_cookie_arm64ec(_In_ uintptr_t _StackCookie)
#else
    void __cdecl __security_check_cookie(_In_ uintptr_t _StackCookie)
#endif
{
    if (_StackCookie != __security_cookie)
    {
        __fastfail(FAST_FAIL_STACK_COOKIE_CHECK_FAILURE);
    }
}

//
// __security_init_cookie.c
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Implementation of __security_init_cookie.
//
// SPDX-License-Identifier: MIT
//

#define _CRT_RAND_S
#include <stdlib.h>
#include <intrin.h>

uintptr_t __security_cookie = 0x2B992DDFA232;

void __security_init_cookie(void)
{
    unsigned int randomValue;

    rand_s(&randomValue);
    __security_cookie ^= randomValue;

#ifdef _WIN64
    rand_s(&randomValue);
    __security_cookie ^= ((unsigned long long)randomValue << 32);

    // Zero out upper 16 bits
    __security_cookie &= 0x0000FFFFFFFFFFFFull;
#endif
}

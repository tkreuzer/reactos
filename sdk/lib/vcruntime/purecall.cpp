//
// purecall.cpp
//
//      Copyright (c) 2025 Timo Kreuzer
//
// Implementation of _get_purecall_handler, _set_purecall_handler and _purecall function.
//
// SPDX-License-Identifier: MIT
//

#include <stdlib.h>
#include <intrin.h>

static _purecall_handler purecall_handler;

_purecall_handler _cdecl _get_purecall_handler(void)
{
    return purecall_handler;
}

_purecall_handler _cdecl _set_purecall_handler(_In_opt_ _purecall_handler _Handler)
{
    return reinterpret_cast<_purecall_handler>(
        _InterlockedExchangePointer(reinterpret_cast<void**>(&purecall_handler),
                                    reinterpret_cast<void*>(_Handler)));
}

extern "C"
int __cdecl _purecall(void)
{
    if (purecall_handler)
        purecall_handler();
    abort();
}

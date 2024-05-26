//
// memset.c
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Implementation of memset.
//
// SPDX-License-Identifier: MIT
//

#include <string.h>

void*
__cdecl
memset (
    _Out_writes_bytes_all_(_Size) void* _Dst,
    _In_ int _Val,
    _In_ size_t _Size)
{
    unsigned char* bytes = (unsigned char*)_Dst;
    unsigned char uc = (unsigned char)_Val;

    while (_Size--)
    {
        *bytes++ = uc;
    }

    return _Dst;
}

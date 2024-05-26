//
// memchr.c
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Implementation of memchr.
//
// SPDX-License-Identifier: MIT
//

#include <string.h>

void*
__cdecl
memchr(
    _In_reads_bytes_opt_(_MaxCount) void const* _Buf,
    _In_ int _Val,
    _In_ size_t _MaxCount)
{
    unsigned char const* buf = (unsigned char const*)_Buf;
    unsigned char val = (unsigned char)_Val;

    for (size_t i = 0; i < _MaxCount; i++)
    {
        if (buf[i] == val)
        {
            return (void*)&buf[i];
        }
    }

    return NULL;
}

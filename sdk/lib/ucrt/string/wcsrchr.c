//
// wcsrchr.c
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Implementation of wcsrchr.
//
// SPDX-License-Identifier: MIT
//

#include <string.h>

_Check_return_
_CONST_RETURN
wchar_t*
__cdecl
wcsrchr(
    _In_z_ const wchar_t *_Str,
    _In_ wchar_t _Ch)
{
    wchar_t *last_found = NULL;

    for (; *_Str; _Str++)
    {
        if (*_Str == _Ch)
        {
            last_found = (wchar_t *)_Str;
        }
    }

    return last_found;
}

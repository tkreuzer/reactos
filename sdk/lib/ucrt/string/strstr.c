//
// strstr.c
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Implementation of strstr.
//
// SPDX-License-Identifier: MIT
//

#include <string.h>

#ifdef _CRT_WCS_OVERRIDE
#define _tscstr wcsstr
typedef wchar_t char_t;
#else
#define _tscstr strstr
typedef char char_t;
#endif

_Check_return_
_Ret_maybenull_
_When_(return != NULL, _Ret_range_(_Str, _Str + _String_length_(_Str) - 1))
char_t*
__cdecl
_tscstr(
    _In_z_ char_t const* _Str,
    _In_z_ char_t const* _SubStr)
{
    size_t len;

    for (len = 0; _SubStr[len]; len++)
        ;

    if (len == 0)
    {
        return (char_t*)_Str;
    }

    for (; *_Str; _Str++)
    {
        if (*_Str == *_SubStr)
        {
            size_t i;
            for (i = 1; i < len; i++)
            {
                if (_Str[i] != _SubStr[i])
                {
                    break;
                }
            }
            if (i == len)
            {
                return (char_t*)_Str;
            }
        }
    }

    return NULL;
}

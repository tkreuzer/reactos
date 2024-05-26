//
// strchr.c
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Implementation of strchr.
//
// SPDX-License-Identifier: MIT
//

#include <string.h>

_Check_return_
char *
__cdecl strchr(
    _In_z_ char const* _Str,
    _In_ int _Ch)
{
    for (; *_Str; _Str++)
    {
        if (*_Str == _Ch)
        {
            return (char *)_Str;
        }
    }

    return NULL;
}


#pragma once

#include <vcruntime.h>

_CRT_BEGIN_C_HEADER

void*
__cdecl
memset(
    _Out_writes_bytes_all_(_Size) void* _Dst,
    _In_ int _Val,
    _In_ size_t _Size);

_CRT_INSECURE_DEPRECATE_MEMORY(memcpy_s)
_Post_equal_to_(_Dst)
_At_buffer_((unsigned char*)_Dst, _Iter_, _Size,
            _Post_satisfies_(((unsigned char*)_Dst)[_Iter_] == ((unsigned char*)_Src)[_Iter_]))
void*
__cdecl
memcpy(
    _Out_writes_bytes_all_(_Size) void* _Dst,
    _In_reads_bytes_(_Size) void const* _Src,
    _In_ size_t _Size);

_CRT_INSECURE_DEPRECATE_MEMORY(memmove_s)
_VCRTIMP
void*
__cdecl
memmove(
    _Out_writes_bytes_all_opt_(_Size) void* _Dst,
    _In_reads_bytes_opt_(_Size) void const* _Src,
    _In_ size_t _Size);

_CRT_END_C_HEADER

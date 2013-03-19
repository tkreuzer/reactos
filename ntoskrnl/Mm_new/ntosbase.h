
#pragma once

/* Dependencies */
#define NT_INCLUDED
#include <excpt.h>
#include <ntdef.h>
#include <ntstatus.h>
#include <kernelspecs.h>
#include <ntiologc.h>
#include <intrin.h>
#include <pseh/pseh2.h>

#if defined(_MSC_VER)

/* Disable some warnings */
#pragma warning(disable:4115) /* Named type definition in parentheses */
#pragma warning(disable:4201) /* Nameless unions and structs */
#pragma warning(disable:4214) /* Bit fields of other types than int */
#pragma warning(disable:4820) /* Padding added, due to alignment requirement */

#endif /* _MSC_VER */

/* Hacks! */
#define IoFileObjectType _IoFileObjectType

#include <ntifs.h>

#define ProbeForWriteHandle(x) ProbeForWrite(x, sizeof(HANDLE), sizeof(HANDLE))

#define MmLowestUserAddress ((PVOID)0x10000)


#pragma once

#include <ntoskrnl.h>
#include "Memory.hpp"

typedef struct _RTL_BITMAP
{
    ULONG _SizeOfBitMap;
    PULONG Buffer;
} RTL_BITMAP, *PRTL_BITMAP;

typedef struct _RTL_BITMAP_RUN
{
    ULONG StartingIndex;
    ULONG NumberOfBits;
} RTL_BITMAP_RUN, *PRTL_BITMAP_RUN;

#ifdef _WIN64
typedef struct _RTL_BITMAP64
{
    ULONG64 _SizeOfBitMap;
    PULONG64 Buffer;
} RTL_BITMAP64, *PRTL_BITMAP64;

typedef struct _RTL_BITMAP_RUN64
{
    ULONG StartingIndex;
    ULONG NumberOfBits;
} RTL_BITMAP_RUN64, *PRTL_BITMAP_RUN64;
#endif


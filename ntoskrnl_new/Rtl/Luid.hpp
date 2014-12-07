
#pragma once

#include "Rtl.hpp"

// ntdef.h
//typedef struct _LUID
//{
//    ULONG LowPart;
//    LONG HighPart;
//} LUID, *PLUID;

typedef struct _LUID_AND_ATTRIBUTES
{
    LUID Luid;
    ULONG Attributes;
} LUID_AND_ATTRIBUTES, *PLUID_AND_ATTRIBUTES;

typedef LUID_AND_ATTRIBUTES LUID_AND_ATTRIBUTES_ARRAY[ANYSIZE_ARRAY];
typedef LUID_AND_ATTRIBUTES_ARRAY *PLUID_AND_ATTRIBUTES_ARRAY;

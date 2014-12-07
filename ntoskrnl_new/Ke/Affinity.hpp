
#pragma once

#include "Kep.hpp"

#if defined(_M_AMD64)
#define AFFINITY_GROUP_COUNT 20
#elif defined(_M_IX86)
#define AFFINITY_GROUP_COUNT 1
#else
#define AFFINITY_GROUP_COUNT 1
#endif

typedef struct _KAFFINITY_EX
{
    USHORT Count;
    USHORT Size;
    ULONG Reserved;
    KAFFINITY Bitmap[AFFINITY_GROUP_COUNT];
} KAFFINITY_EX, *PKAFFINITY_EX;

typedef struct _KAFFINITY_ENUMERATION_CONTEXT
{
    PKAFFINITY_EX Affinity;
    ULONG CurrentMask;
    USHORT CurrentIndex;
} KAFFINITY_ENUMERATION_CONTEXT, *PKAFFINITY_ENUMERATION_CONTEXT;


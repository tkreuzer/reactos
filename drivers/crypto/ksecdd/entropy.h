
#pragma once

#include "ksecdd.h"
#include <sha512.h>

typedef struct _SHA512
{
    UCHAR Data[64];
} SHA512;

typedef struct _HASH2048
{
    SHA512 Hashes[4];
} HASH2048, *PHASH2048;

// Size is 800 bytes!
typedef struct _HASH2048_CTX
{
    SHA512_CTX Sha512Cts[4];
} HASH2048_CTX, * PHASH2048_CTX;

// Size should be a multiple of 6
typedef struct _FAST_ENTROPY
{
    PEPROCESS CurrentProcess;
    PETHREAD CurrentThread;
    ULONG64 TickCount;
    ULONG64 SystemTime;
    LARGE_INTEGER PerformanceCounter;
    LARGE_INTEGER PerformanceFrequency;
    KSEC_MACHINE_SPECIFIC_COUNTERS MachineSpecificCounters;

    UCHAR Uninitialized[6];
} FAST_ENTROPY, *PFAST_ENTROPY;

VOID
NTAPI
KsecGatherFastEntropy(
    _Out_ PFAST_ENTROPY Entropy);

NTSTATUS
NTAPI
KsecGatherBootEntropy(
    _Out_ PHASH2048 Hash2048);

#pragma once

#include <stddef.h>

typedef struct _VMPCR_CTX
{
    unsigned char P[256];
    unsigned char S[256];
    unsigned char a, b, c, d, e, f, n;
} VMPCR_CTX, * PVMPCR_CTX;

void
VMPCR_Init(
    PVMPCR_CTX Ctx,
    const unsigned char Key[],
    size_t KeyLen,
    const unsigned char Vector[],
    size_t VectorLen);

void
VMPCR_Crypt(
    PVMPCR_CTX Ctx,
    const unsigned char Source[],
    unsigned char Dest[],
    size_t Len);

void
VMPCR_Permutate(
    PVMPCR_CTX Ctx,
    const unsigned char Data[],
    size_t Len);

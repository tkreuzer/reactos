
#pragma once


typedef struct
{
    ULONG64 len;
    ULONG64 h[8];
    UCHAR buf[128];
} SHA512_CTX;

void
sha512_init(SHA512_CTX *ctx) DECLSPEC_HIDDEN;

void
sha512_update(SHA512_CTX *ctx, const UCHAR *buffer, ULONG len) DECLSPEC_HIDDEN;

void
sha512_finalize(SHA512_CTX *ctx, UCHAR *buffer) DECLSPEC_HIDDEN;

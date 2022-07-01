
#pragma once

typedef struct
{
    ULONG64 len;
    DWORD h[8];
    UCHAR buf[64];
} SHA256_CTX;

void
sha256_init(SHA256_CTX *ctx) DECLSPEC_HIDDEN;

void
sha256_update(SHA256_CTX *ctx, const UCHAR *buffer, ULONG len) DECLSPEC_HIDDEN;

void
sha256_finalize(SHA256_CTX *ctx, UCHAR *buffer) DECLSPEC_HIDDEN;


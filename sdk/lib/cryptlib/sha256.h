
#pragma once

typedef struct
{
    unsigned long long len;
    unsigned long h[8];
    unsigned char buf[64];
} SHA256_CTX;

void
sha256_init(SHA256_CTX *ctx);

void
sha256_update(SHA256_CTX *ctx, const unsigned char*buffer, unsigned long len);

void
sha256_finalize(SHA256_CTX *ctx, unsigned char*buffer);



#pragma once


typedef struct
{
    unsigned long long len;
    unsigned long long h[8];
    unsigned char buf[128];
} SHA512_CTX;

void
sha512_init(SHA512_CTX *ctx);

void
sha512_update(SHA512_CTX *ctx, const unsigned char*buffer, unsigned long len);

void
sha512_finalize(SHA512_CTX *ctx, unsigned char*buffer);

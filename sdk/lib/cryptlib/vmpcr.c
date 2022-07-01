/*---------------------------------------------------------------------------------------------------

                 Implementation of the Cryptographically Secure
                      Pseudo-Random Number Generator VMPC-R
                                   in C

                Author of the algorithms: Bartosz Zoltak
              Author of the implementation: Bartosz Zoltak
              

                         www.vmpcfunction.com

-----------------------------------------------------------------------------------------------------
----------------------- Usage of the algorithm: -----------------------------------------------------
-----------------------------------------------------------------------------------------------------

unsigned char Key[256], Vector[256]; Message[1000];

Pseudo-Random Number Generation / Encryption:

   VMPCR_InitKey(Key, Vector, 32, 32);
   VMPCR_Crypt(Message, 1000);

Decryption:

   VMPCR_Init(Key, Vector, 16, 16);
   VMPCR_Crypt(Message, 1000);

   (the VMPRCEncrypt function is used for pseudo-random number generation, encryption and decryption).

----------------------------------------------------------------------------------------------------
CAUTION!
A DIFFERENT value of the initialization vector("Vector")
should be used for each encryption with the same key("Key").

Encrypting two messages with THE SAME keyand THE SAME initialization vector
drastically reduces security level!

The key is a secret value.
The initialization vector is not secret - it can be passed in plain form along with the encrypted message.
---------------------------------------------------------------------------------------------------- */

#include "vmpcr.h"
#include <stdlib.h>
#include <assert.h>

// InitKeyRounds[x] = Ceiling((x+1)*(x+1) / (6*256))
unsigned char InitKeyRounds[256] =
{ 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 9, 9,
    9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11,
    11, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 14, 14, 14,
    14, 14, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 17, 17, 17, 17,
    17, 18, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 20, 21,
    21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 24, 24,
    25, 25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29,
    29, 29, 29, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 33, 33, 33,
    33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 38, 38,
    38, 39, 39, 39, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43
};

// Data: key or initialization vector
// Len=1,2,3,...,256: key/initialization vector length (in bytes)
static
void
VMPCR_InitKeyRound(
    PVMPCR_CTX Ctx,
    const unsigned char Data[],
    size_t Len)
{
    unsigned char a = Ctx->a, b = Ctx->b, c = Ctx->c, d = Ctx->d, e = Ctx->e, f = Ctx->f, n = Ctx->n;
    unsigned char *P = Ctx->P, *S= Ctx->S;
    unsigned char i, t;
    int r, x;

    assert(Len > 0);

    i = 0;

    // InitKeyRounds[Len-1] = Ceiling(Len*Len / (6*256))
    for (r = 1; r <= InitKeyRounds[Len - 1]; r++)
    {
        for (x = 0; x < 256; x++)
        {
            size_t safe_len = Len - i;
            int safe_count = (int)(safe_len / 6);
            int safe_max = min(x + safe_count, 254);

            /* Optimization for larger keys */
            for (; x < safe_max; x++)
            {
                a = (P[(a + f + Data[i]) & 255] + i) & 255;   i++;
                b = (S[(b + a + Data[i]) & 255] + i) & 255;   i++;
                c = (P[(c + b + Data[i]) & 255] + i) & 255;   i++;
                d = (S[(d + c + Data[i]) & 255] + i) & 255;   i++;
                e = (P[(e + d + Data[i]) & 255] + i) & 255;   i++;
                f = (S[(f + e + Data[i]) & 255] + i) & 255;   i++;
                t = P[x];  P[x] = P[b];  P[b] = t;
                t = S[x];  S[x] = S[e];  S[e] = t;
                t = P[d];  P[d] = P[f];  P[f] = t;
                t = S[a];  S[a] = S[c];  S[c] = t;
            }
            
            if (i == Len) i = 0;

            //x will take on the same values as n in the algorithm's specification
            a = (P[(a + f + Data[i]) & 255] + i) & 255;   i++; if (i == Len) i = 0;
            b = (S[(b + a + Data[i]) & 255] + i) & 255;   i++; if (i == Len) i = 0;
            c = (P[(c + b + Data[i]) & 255] + i) & 255;   i++; if (i == Len) i = 0;
            d = (S[(d + c + Data[i]) & 255] + i) & 255;   i++; if (i == Len) i = 0;
            e = (P[(e + d + Data[i]) & 255] + i) & 255;   i++; if (i == Len) i = 0;
            f = (S[(f + e + Data[i]) & 255] + i) & 255;   i++; if (i == Len) i = 0;
            t = P[x];  P[x] = P[b];  P[b] = t;
            t = S[x];  S[x] = S[e];  S[e] = t;
            t = P[d];  P[d] = P[f];  P[f] = t;
            t = S[a];  S[a] = S[c];  S[c] = t;
        }
    }

    Ctx->a = a; Ctx->b = b; Ctx->c = c; Ctx->d = d; Ctx->e = e; Ctx->f = f; Ctx->n = n;
}

static
void
VMPCR_InitKeyFinalize(
    PVMPCR_CTX Ctx)
{
    unsigned char a = Ctx->a, b = Ctx->b, c = Ctx->c, d = Ctx->d, e = Ctx->e, f = Ctx->f, n = Ctx->n;
    unsigned char *P = Ctx->P, *S = Ctx->S;
    unsigned char t;
    int x;

    for (x = 0; x < 256; x++)
    {
        a = P[(a + c + S[n]) & 255];
        b = P[(b + a) & 255];
        c = P[(c + b) & 255];
        d = S[(d + f + P[n]) & 255];
        e = S[(e + d) & 255];
        f = S[(f + e) & 255];
        t = P[n];  P[n] = P[f];  P[f] = t;
        t = S[n];  S[n] = S[a];  S[a] = t;
        n++;
    }
    
    Ctx->a = a; Ctx->b = b; Ctx->c = c; Ctx->d = d; Ctx->e = e; Ctx->f = f; Ctx->n = n;
}

// Key: key or initialization vector
// KeyLen=1,2,3,...,256: key/initialization vector length (in bytes)
// Vector: initialization vector
// VectorLen=1,2,3,...,256: initialization vector length (in bytes)
void
VMPCR_Init(
    PVMPCR_CTX Ctx,
    const unsigned char Key[],
    size_t KeyLen,
    const unsigned char Vector[],
    size_t VectorLen)
{
    int x;

    for (x = 0; x < 256; x++)
    {
        Ctx->P[x] = (unsigned char)x;
        Ctx->S[x] = (unsigned char)x;
    }

    Ctx->a = 0; Ctx->b = 0; Ctx->c = 0; Ctx->d = 0; Ctx->e = 0; Ctx->f = 0; Ctx->n = 0;

    VMPCR_InitKeyRound(Ctx, Key, KeyLen);
    VMPCR_InitKeyRound(Ctx, Vector, VectorLen);
    VMPCR_InitKeyRound(Ctx, Key, KeyLen);
    Ctx->n = Ctx->S[(Ctx->S[Ctx->S[(Ctx->c + Ctx->d) & 255]] + 1) & 255];
    VMPCR_InitKeyFinalize(Ctx);
}

void
VMPCR_Crypt(
    PVMPCR_CTX Ctx,
    const unsigned char Source[],
    unsigned char Dest[],
    size_t Len)
{
    unsigned char a = Ctx->a, b = Ctx->b, c = Ctx->c, d = Ctx->d, e = Ctx->e, f = Ctx->f, n = Ctx->n;
    unsigned char* P = Ctx->P, * S = Ctx->S;
    unsigned char t;
    size_t x;

    for (x = 0; x < Len; x++)
    {
        a = P[(a + c + S[n]) & 255];
        b = P[(b + a) & 255];
        c = P[(c + b) & 255];
        d = S[(d + f + P[n]) & 255];
        e = S[(e + d) & 255];
        f = S[(f + e) & 255];

        t = S[(S[S[ (c + d) & 255 ]]+1) & 255];
        Dest[x] = Source[x] ^ t;

        t = P[n];  P[n] = P[f];  P[f] = t;
        t = S[n];  S[n] = S[a];  S[a] = t;

        n++;
    }
}

// Quick entropy adder
void
VMPCR_Permutate(
    PVMPCR_CTX Ctx,
    const unsigned char Data[],
    size_t Len)
{
    unsigned char a = Ctx->a, b = Ctx->b, c = Ctx->c, d = Ctx->d, e = Ctx->e, f = Ctx->f, n = Ctx->n;
    unsigned char* P = Ctx->P, * S = Ctx->S;
    unsigned char i, t;
    int x;

    i = 0;

    for (x = 0; x < Len / 6; x++)
    {
        //x will take on the same values as n in the algorithm's specification
        a = (P[(a + f + Data[i]) & 255] + i) & 255;   i++;
        b = (S[(b + a + Data[i]) & 255] + i) & 255;   i++;
        c = (P[(c + b + Data[i]) & 255] + i) & 255;   i++;
        d = (S[(d + c + Data[i]) & 255] + i) & 255;   i++;
        e = (P[(e + d + Data[i]) & 255] + i) & 255;   i++;
        f = (S[(f + e + Data[i]) & 255] + i) & 255;   i++;
        t = P[x];  P[x] = P[b];  P[b] = t;
        t = S[x];  S[x] = S[e];  S[e] = t;
        t = P[d];  P[d] = P[f];  P[f] = t;
        t = S[a];  S[a] = S[c];  S[c] = t;
    }

    Ctx->a = a; Ctx->b = b; Ctx->c = c; Ctx->d = d; Ctx->e = e; Ctx->f = f; Ctx->n = n;
}


#if 1 // def _VMPCR_TEST_
#include <stdio.h>

void
Test_VMPCR_Single(
    const unsigned char Key[],
    size_t KeyLen,
    const unsigned char Vector[],
    size_t VectorLen,
    const unsigned char TestOutP[8],
    const unsigned char TestOutS[8],
    const unsigned char TestOut[16])
{
    static const unsigned char TestOutPSInd[8] = { 0, 1, 2, 3, 252, 253, 254, 255 };
    static const unsigned int  TestOutInd[16] = { 0, 1, 2, 3, 254, 255, 256, 257,1000,1001,10000,10001,100000,100001,1000000,1000001 };
    static unsigned char Table[1000002];

    VMPCR_CTX ctx;
    int x;

    VMPCR_Init(&ctx, Key, KeyLen, Vector, VectorLen);

    //P[TestOutPSInd[x]]==TestOutP[x];   x=0,1,...,7
    for (x = 0; x < _countof(TestOutPSInd); x++)
    {
        assert(ctx.P[TestOutPSInd[x]] == TestOutP[x]);
    }

    //S[TestOutPSInd[x]]==TestOutS[x];   x=0,1,...,7
    for (x = 0; x < _countof(TestOutPSInd); x++)
    {
        assert(ctx.S[TestOutPSInd[x]] == TestOutS[x]);
    }

    //VMPCREncrypt(Table, 1000002);
    memset(Table, 0, sizeof(Table));
    VMPCR_Crypt(&ctx, Table, Table, sizeof(Table));

    //Table[TestOutInd[x]]==TestOut[x];  x=0,1,...,15
    for (x = 0; x < _countof(TestOutInd); x++)
    {
        assert(Table[TestOutInd[x]] == TestOut[x]);
    }
}

void
Test_VMPCR(void)
{
    {
        static const unsigned char TestKey[9] = { 11,22,33,144,155,166,233,244,255 };
        static const unsigned char TestVector[8] = { 255,250,200,150,100,50,5,1 };
        static const unsigned char TestOutP[8] = { 97,218,106,125,139,86,36,126 };
        static const unsigned char TestOutS[8] = { 152,143,19,154,92,25,24,157 };
        static const unsigned char TestOut[16] = { 49,161,79,69,85,237,96,243,181,184,136,99,67,27,253,231 };
        Test_VMPCR_Single(TestKey, sizeof(TestKey), TestVector, sizeof(TestVector), TestOutP, TestOutS, TestOut);
    }

    {
        static const unsigned char TestKey32[32] = { 104, 9, 46, 231, 132, 149, 234, 147, 224, 97, 230, 127, 124, 109, 34, 171,
                                                     88, 185, 158, 23, 116, 69, 90, 195, 208, 17, 86, 175, 108, 29, 146, 219 };
        //RND=123; repeat 32 times:{RND=RND*134775813+1; output=(RND & 255)}
        static const unsigned char TestVector32[32] = { 149, 234, 147, 224, 97, 230, 127, 124, 109, 34, 171, 88, 185, 158, 23, 116,
                                                        69, 90, 195, 208, 17, 86, 175, 108, 29, 146, 219, 72, 105, 14, 71, 100 };
        //RND=132; repeat 32 times:{RND=RND*134775813+1; output=(RND & 255)}
        static const unsigned char TestOutP32[8] = { 76, 44, 167, 7, 250, 147, 240, 51 };
        static const unsigned char TestOutS32[8] = { 239, 59, 110, 207, 98, 23, 178, 227 };
        static const unsigned char TestOut32[16] = { 219, 178, 157, 119, 2, 155, 62, 20, 3, 239, 236, 81, 195, 11, 186, 127 };
        Test_VMPCR_Single(TestKey32, sizeof(TestKey32), TestVector32, sizeof(TestVector32), TestOutP32, TestOutS32, TestOut32);
    }

    {
        static const unsigned char TestKey256[256] = { 147, 224, 97, 230, 127, 124, 109, 34, 171, 88, 185, 158, 23, 116, 69, 90, 195, 208, 17, 86, 175,
                                   108, 29, 146, 219, 72, 105, 14, 71, 100, 245, 202, 243, 192, 193, 198, 223, 92, 205, 2, 11, 56,
                                   25, 126, 119, 84, 165, 58, 35, 176, 113, 54, 15, 76, 125, 114, 59, 40, 201, 238, 167, 68, 85, 170,
                                   83, 160, 33, 166, 63, 60, 45, 226, 107, 24, 121, 94, 215, 52, 5, 26, 131, 144, 209, 22, 111, 44,
                                   221, 82, 155, 8, 41, 206, 7, 36, 181, 138, 179, 128, 129, 134, 159, 28, 141, 194, 203, 248, 217,
                                   62, 55, 20, 101, 250, 227, 112, 49, 246, 207, 12, 61, 50, 251, 232, 137, 174, 103, 4, 21, 106, 19,
                                   96, 225, 102, 255, 252, 237, 162, 43, 216, 57, 30, 151, 244, 197, 218, 67, 80, 145, 214, 47, 236,
                                   157, 18, 91, 200, 233, 142, 199, 228, 117, 74, 115, 64, 65, 70, 95, 220, 77, 130, 139, 184, 153,
                                   254, 247, 212, 37, 186, 163, 48, 241, 182, 143, 204, 253, 242, 187, 168, 73, 110, 39, 196, 213,
                                   42, 211, 32, 161, 38, 191, 188, 173, 98, 235, 152, 249, 222, 87, 180, 133, 154, 3, 16, 81, 150,
                                   239, 172, 93, 210, 27, 136, 169, 78, 135, 164, 53, 10, 51, 0, 1, 6, 31, 156, 13, 66, 75, 120, 89,
                                   190, 183, 148, 229, 122, 99, 240, 177, 118, 79, 140, 189, 178, 123, 104, 9, 46, 231, 132, 149, 234 };
                                   //RND=234; repeat 256 times:{RND=RND*134775813+1; output=(RND & 255)}
        static const unsigned char TestVector[8] = { 255,250,200,150,100,50,5,1 };
        unsigned char TestOutP256[8] = { 10, 34, 13, 239, 209, 9, 154, 220 };
        unsigned char TestOutS256[8] = { 253, 106, 200, 178, 75, 251, 129, 209 };
        unsigned char TestOut256[16] = { 201, 85, 155, 17, 187, 48, 55, 198, 110, 179, 189, 210, 4, 15, 253, 83 };
        Test_VMPCR_Single(TestKey256, sizeof(TestKey256), TestVector, sizeof(TestVector), TestOutP256, TestOutS256, TestOut256);
    }

    {
        static const unsigned char TestKey[9] = { 11,22,33,144,155,166,233,244,255 };
        static const unsigned char TestVector[8] = { 255,250,200,150,100,50,5,1 };
        VMPCR_CTX ctx;
        unsigned char Table[32];
        int i;

        VMPCR_Init(&ctx, TestKey, sizeof(TestKey), TestVector, sizeof(TestVector));
        
        memset(Table, 0, sizeof(Table));
        VMPCR_Crypt(&ctx, Table, Table, sizeof(Table));
        for (i = 0; i < 32; i++) printf("%02x", Table[i]); printf("\n");
        VMPCR_InitKeyRound(&ctx, Table, sizeof(Table));
        VMPCR_Crypt(&ctx, Table, Table, sizeof(Table));
        for (i = 0; i < 32; i++) printf("%02x", Table[i]); printf("\n");
    }
}

#endif /* _VMPCR_TEST_ */


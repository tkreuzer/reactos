/* Automatically generated file; DO NOT EDIT!! */

#define STANDALONE
#include <wine/test.h>

extern void func_imm32(void);

const struct test winetest_testlist[] =
{
#ifndef _M_AMD64 // crashes rosautotest
    { "imm32", func_imm32 },
#endif
    { 0, 0 }
};

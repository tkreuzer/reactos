#define STANDALONE
#include <apitest.h>

extern void func_BasicOperations(void);

const struct test winetest_testlist[] =
{
    { "BasicOperations", func_BasicOperations },
    { 0, 0 }
};

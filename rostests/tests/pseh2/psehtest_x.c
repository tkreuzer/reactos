#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pseh/pseh2.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <setjmp.h>

int
DbgPrint(char *Format, ...)
{
    return 0;
}

void
print_stack_address()
{
    printf("stack = %p\n", _AddressOfReturnAddress());
}

	static int count = 0;


static
void test_finally_13_helper(void)
{
	_SEH2_TRY
	{
        *((char*)0xc0000000) = 0;
	}
	_SEH2_FINALLY
	{
	    __debugbreak();
	    count++;
		RaiseException(0xE00DEAD0, 0, 0, NULL);
	}
	_SEH2_END;
}

#ifndef _USE_PSEH3
int test_finally_13_x() // this one!!!
{
	static int  ret;
	_SEH2Frame_t  __attribute__((aligned(4))) _SEH2Frame;

	//printf("stack = %p\n", _AddressOfReturnAddress());
	//print_stack_address();

	ret = 0;

	_SEH2_TRY
	{
		//if (&_SEHHandleTryLevel) ret = 1;
		test_finally_13_helper();
		ret = 2;
	}
	_SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
	{
		ret = 3;
	}
	_SEH2_END;

    printf("count = %d\n", count);


	return ret;
}
#endif

typedef struct
{
    int c;
} cccc;


static int hello(int c)
{
    return c + 1;
}

void
Test_PSEH2(int p1)
{
    //volatile int p = p1 + 1;
    //volatile int q = p1 + 2;
    int reg1 = 0;
    int reg2 = 0;
    int reg3 = 0;

    puts("Start!");

    _SEH2_TRY
    {
        reg1 = 1;
        reg2 = 2;
        puts("Try!");
        *((char*)0xc0000000) = 0;
        reg3 = 3;
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        puts("Except!");
        printf("edi = %i, %i, %i\n", reg1, reg2, reg3);
    }
    _SEH2_END;

    puts("End!");
    printf("regs = %i, %i, %i\n", reg1, reg2, reg3);

    //printf("%p, %p", &p, &q);
}

int
main()
{
    int ret = 0;

    Test_PSEH2(0);

#if 0
	_SEH2_TRY
	{
		//if (&_SEHHandleTryLevel) ret = 1;
		test_finally_13_helper();
		ret = 2;
	}
	_SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
	{
		ret = 3;
	}
	_SEH2_END;

	_SEH2_TRY
	{
		//if (&_SEHHandleTryLevel) ret = 1;
		test_finally_13_helper();
		ret = 2;
	}
	_SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
	{
		ret = 3;
	}
	_SEH2_END;

    printf("start\n");
    test_finally_13_x();
#endif
    return ret;
}

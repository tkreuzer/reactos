// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for
// full license information.

#include <windows.h>
#include <setjmp.h>

#include "seh.h"

char test[] = "SEH0026.c";

void dojump(jmp_buf JumpBuffer, PLONG Counter) {
  try {printf("try 5: %lu\n", *Counter);
    try {printf("try 6: %lu\n", *Counter);
      /* set Counter = 1 */
      *Counter += 1;__debugbreak();
      RaiseException(EXCEPTION_INT_OVERFLOW, 0, /*no flags*/ 0, 0);
    }
    finally {printf("finally 6: %lu\n", *Counter);
      /* set counter = 2 */
      *Counter += 1;__debugbreak();
    }
    endtry
  }
  finally {printf("finally 5: %lu\n", *Counter);
    /* set counter = 3 */
    *Counter += 1;__debugbreak();
    longjmp(JumpBuffer, 1);
  }
  endtry
}

int main() {
  jmp_buf JumpBuffer;
  LONG Counter;

  Counter = 0;
  __debugbreak();
  if (_setjmp(JumpBuffer) == 0) {
    try {printf("try 1\n");
      try {printf("try 2\n");
        try {printf("try 3\n");
          try {printf("try 4\n");
            *(volatile LONG*)&Counter += 1;
            dojump(JumpBuffer, &Counter);
          }
          finally { printf("finally 4: %lu\n", Counter); *(volatile LONG*)&Counter += 1; __debugbreak();}
          endtry
        }
        finally {printf("finally 3: %lu\n", Counter);
          *(volatile LONG*)&Counter += 1;__debugbreak();
          longjmp(JumpBuffer, 1);
        }
        endtry
      }
      finally { printf("finally 2: %lu\n", Counter); *(volatile LONG*)&Counter += 1; }
      endtry
    }
    except(1)
    /* EXECUTE HANDLER after unwinding */
    {printf("except 1: %lu\n", Counter);
      *(volatile LONG*)&Counter += 1;
    }
    endtry
  } else {printf("else: %lu\n", Counter);
    /* set Counter  = 4 */ //
    *(volatile LONG*)&Counter += 1;
  }

  if (Counter != 8) {
    printf("TEST 26 FAILED. Counter = %d\n\r", Counter);
    return -1;
  }

  return 0;
}

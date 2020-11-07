/*
* PROJECT:         ReactOS API tests
* LICENSE:         LGPLv2.1+ - See COPYING.LIB in the top level directory
* PURPOSE:         Test for __dllonexit
* PROGRAMMER:      Timo Kreuzer <timo.kreuzer@reactos.org>
*/

#include <apitest.h>

#include <stdlib.h>
#include <ntndk.h>
#include <malloc.h>

_onexit_t CDECL __dllonexit(_onexit_t func, _onexit_t **start, _onexit_t **end);

int __cdecl my_onexit_func(void)
{
    return 0;
}

START_TEST(__dllonexit)
{
    size_t alloc_size;
    _onexit_t result;
    _onexit_t *alloc, *start, *end;

    result = NULL;
    StartSeh()
        result = __dllonexit(NULL, NULL, NULL);
    EndSeh(STATUS_ACCESS_VIOLATION);
    ok_ptr(result, NULL);

    start = NULL;
    end = NULL;
    result = NULL;
    StartSeh()
        result = __dllonexit(NULL, &start, NULL);
    EndSeh(STATUS_ACCESS_VIOLATION);
    ok_ptr(result, NULL);

    result = NULL;
    StartSeh()
        result = __dllonexit(NULL, NULL, &end);
    EndSeh(STATUS_ACCESS_VIOLATION);
    ok_ptr(result, NULL);

    result = NULL;
    StartSeh()
        result = __dllonexit(NULL, &start, &end);
    EndSeh(STATUS_ACCESS_VIOLATION);
    ok_ptr(result, NULL);

    result = NULL;
    StartSeh()
        result = __dllonexit(my_onexit_func, &start, &end);
    EndSeh(STATUS_ACCESS_VIOLATION);
    ok_ptr(start, NULL);
    ok_ptr(end, NULL);
    ok_ptr(result, NULL);

    /* Allocate 1 element */
    alloc = calloc(1, sizeof(_onexit_t));
    ok(alloc != NULL, "Failed to allocate buffer\n");
    alloc_size = _msize(alloc);
    ok(alloc_size == sizeof(_onexit_t), "Unexpected size: %Iu\n", alloc_size);

    /* Try with only start set */
    start = alloc;
    result = NULL;
    StartSeh()
        result = __dllonexit(my_onexit_func, &start, &end);
    EndSeh(STATUS_ACCESS_VIOLATION);
    ok_ptr(start, alloc);
    ok_ptr(end, NULL);
    ok_ptr(result, NULL);

    /* Try with end set to start */
    end = start = alloc;
    result = NULL;
    result = __dllonexit(NULL, &start, &end);
    ok_ptr(start, alloc);
    ok_ptr(end, start + 1);
    ok_ptr(start[0], NULL);
    ok_ptr(result, NULL);
    alloc_size = _msize(alloc);
    ok(alloc_size == 2 * sizeof(_onexit_t), "Unexpected size: %Iu\n", alloc_size);

    /* Try again */
    result = __dllonexit(my_onexit_func, &start, &end);
    ok_ptr(end, start + 2);
    ok_ptr(start[1], my_onexit_func);
    ok_ptr(result, my_onexit_func);
    alloc_size = _msize(alloc);
    ok(alloc_size == 2 * sizeof(_onexit_t), "Unexpected size: %Iu\n", alloc_size);

    /* Allocate a buffer for 4 elements, 3 used */
    alloc = realloc(start, 4 * sizeof(_onexit_t));
    ok(alloc != NULL, "Failed to reallocate buffer\n");
    memset(alloc, 0, 4 * sizeof(_onexit_t));
    start = alloc;
    end = start + 3;
    start[1] = (_onexit_t)(intptr_t)-1;
    *end = my_onexit_func;

    /* Try once */
    result = __dllonexit(my_onexit_func, &start, &end);
    ok_ptr(start, alloc);
    ok_ptr(end, start + 4);
    ok_ptr(result, my_onexit_func);
    alloc_size = _msize(alloc);
    ok(alloc_size == 4 * sizeof(_onexit_t), "Unexpected size: %Iu\n", alloc_size);

    /* Try again */
    result = __dllonexit(my_onexit_func, &start, &end);
    ok_ptr(end, start + 5);
    ok_ptr(result, my_onexit_func);
    alloc_size = _msize(alloc);
    ok(alloc_size == 8 * sizeof(_onexit_t), "Unexpected size: %Iu\n", alloc_size);

    /* Allocate a buffer for 511 elements */
    alloc = realloc(start, 511 * sizeof(_onexit_t));
    ok(alloc != NULL, "Failed to reallocate buffer\n");
    alloc_size = _msize(alloc);
    ok(alloc_size == 511 * sizeof(_onexit_t), "Unexpected size: %Iu\n", alloc_size);
    start = alloc;
    end = start + 511;

    result = __dllonexit(my_onexit_func, &start, &end);
    ok_ptr(end, start + 512);
    ok_ptr(start[511], my_onexit_func);
    ok_ptr(result, my_onexit_func);
    alloc_size = _msize(start);
    ok(alloc_size == 511 * 2 * sizeof(_onexit_t), "Unexpected size: %Iu\n", alloc_size);

    /* Allocate a buffer for 512 elements */
    alloc = realloc(start, 513 * sizeof(_onexit_t));
    ok(alloc != NULL, "Failed to reallocate buffer\n");
    alloc_size = _msize(alloc);
    ok(alloc_size == 513 * sizeof(_onexit_t), "Unexpected size: %Iu\n", alloc_size);
    start = alloc;
    end = start + 513;

    result = __dllonexit(my_onexit_func, &start, &end);
    ok_ptr(end, start + 514);
    ok_ptr(result, my_onexit_func);
    alloc_size = _msize(start);
    ok(alloc_size == (513 + 512) * sizeof(_onexit_t), "Unexpected size: %Iu\n", alloc_size);

}

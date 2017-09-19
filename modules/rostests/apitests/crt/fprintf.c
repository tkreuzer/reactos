/*
 * PROJECT:         ReactOS api tests
 * LICENSE:         GPLv2+ - See COPYING in the top level directory
 * PURPOSE:         Test for sprintf
 * PROGRAMMER:      Timo Kreuzer <timo.kreuzer@reactos.org>
 */

#define MINGW_HAS_SECURE_API
#include <apitest.h>

#define WIN32_NO_STATUS
#include <stdio.h>
#include <tchar.h>
#include <stdarg.h>
#include <pseh/pseh2.h>
#include <ntstatus.h>
typedef _Return_type_success_(return >= 0) long NTSTATUS, *PNTSTATUS;

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#pragma GCC diagnostic ignored "-Wnonnull"
#endif

START_TEST(fprintf)
{
    FILE stream;
    char buffer[128];
    size_t result;

    result = snprintf(0, 0, "test %i\n", -123);
    ok_int(result, 10);

    result = snprintf(0, 9, "test %i\n", -123);
    ok_int(result, -1);

    result = snprintf(buffer, 0, "test %i\n", -123);
    ok_int(result, -1);

    result = snprintf(buffer, 9, "test %i\n", -123);
    ok_int(result, -1);

    result = snprintf(buffer, 10, "test %i\n", -123);
    ok_int(result, 10);

    /* Setup the FILE structure */
    stream._base = buffer;
    stream._ptr = buffer;
    stream._charbuf = 0;
    stream._cnt = sizeof(buffer);
    stream._bufsiz = 0;
    stream._flag = _IOSTRG | _IOWRT;
    stream._tmpfname = 0;

//    StartSeh()
        result = fprintf(&stream, "test %i\n", -123);
//    EndSeh(STATUS_SUCCESS);
    //ok_int(result, 10);


}

/*
 * PROJECT:         ReactOS api tests
 * LICENSE:         GPL - See COPYING in the top level directory
 * PURPOSE:         Test for _vsnprintf
 */

#define WIN32_NO_STATUS
#include <wine/test.h>
#include <pseh/pseh2.h>
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <errno.h>

#define StartSeh()              ExceptionStatus = STATUS_SUCCESS; _SEH2_TRY {
#define EndSeh(ExpectedStatus)  } _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER) { ExceptionStatus = _SEH2_GetExceptionCode(); } _SEH2_END; ok(ExceptionStatus == ExpectedStatus, "Exception %lx, expected %lx\n", ExceptionStatus, ExpectedStatus)

int
__cdecl
swprintf_s(
    wchar_t *buffer,
    size_t sizeOfBuffer,
    const wchar_t *format,
    ...);

int
__cdecl
snwprintf_s(
    wchar_t *buffer,
    size_t sizeOfBuffer,
    size_t count,
    const wchar_t *format,
    ...);

#define MSVCRT_CHECK_PMT(x) (x)
#define MSVCRT_INVALID_PMT(...)


int
__cdecl
swprintf_s_(
    wchar_t *buffer,
    size_t sizeOfBuffer,
    const wchar_t *format,
    ...)
{
    va_list argptr;
    size_t count = INT_MAX;
    int result;

    /* Check trivial case */
    if ((buffer == NULL) && (count == 0) && (sizeOfBuffer == 0))
    {
        return 0;
    }

    /* Validate parameters */
    if (MSVCRT_CHECK_PMT(((buffer == NULL) || (format == NULL) || (sizeOfBuffer <= 0))))
    {
        errno = EINVAL;
        return -1;
    }

    /* Limit output to count + 1 characters */
    if (count != -1)
        sizeOfBuffer = min(sizeOfBuffer, count + 1);

    /* Call the 'unsafe' function */
    va_start(argptr, format);
    result = _snwprintf(buffer, sizeOfBuffer, format, argptr);
    va_end(argptr);

    /* Check for failure or unterminated string */
    if ((result < 0) || (result == sizeOfBuffer))
    {
        /* Null-terminate the buffer at the end */
        buffer[sizeOfBuffer-1] = '\0';

        /* Check if we can truncate */
        if (count != _TRUNCATE)
        {
            /* We can't, invoke invalid parameter handler */
            MSVCRT_INVALID_PMT("Buffer is too small", ERANGE);

            /* If we came back, set the buffer to an empty string */
            *buffer = 0;
        }

        /* Return failure */
        return -1;
    }

    /* Null-terminate the buffer after the string */
    buffer[result] = L'\0';

    /* Return the result */
    return result;
}

//#define swprintf_s swprintf_s_

START_TEST(swprintf_s)
{
    wchar_t buffer[20];
//    int result;

    memset(buffer, 0, sizeof(buffer));
    ok_int(swprintf_s(NULL, 0, NULL), -1);
    ok_int(errno, EINVAL);
    ok_int(swprintf_s(NULL, 0, L"abc"), -1);
    ok_int(swprintf_s(NULL, -1, L"abc"), -1);
    ok_int(buffer[0], L'\0');
    ok_int(buffer[1], L'\0');
    ok_int(buffer[2], L'\0');

    ok_int(swprintf_s(buffer, 0, L"abc"), -1);
    ok_int(errno, EINVAL);
    ok_int(swprintf_s(buffer, -1, L"abc"), 3);
    ok_int(swprintf_s(buffer, 4, L"abc"), 3);
    ok_int(wcscmp(buffer, L"abc"), 0);
    ok_int(swprintf_s(buffer, 3, L"abc"), -1);
    ok_int(errno, ERANGE);
    ok_int(buffer[0], L'\0');
    ok_int(buffer[1], L'b');
    ok_int(buffer[2], L'\0');
    ok_int(wcscmp(buffer, L""), 0);


    ok_int(swprintf_s(buffer, 20, L"a%y", 0), -1);
    ok_int(errno, EINVAL);
    ok_int(wcscmp(buffer, L""), 0);

    ok_int(swprintf(buffer, L"a%y", 0), 2);

    ok_int(snprintf(NULL, 0, NULL), -1);

}

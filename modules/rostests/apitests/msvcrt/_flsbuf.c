/*
 * PROJECT:         ReactOS api tests
 * LICENSE:         GPL - See COPYING in the top level directory
 * PURPOSE:         Test for _splitpath
 * PROGRAMMER:      Timo Kreuzer
 */

#include <wine/test.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdarg.h>

START_TEST(_flsbuf)
{
    FILE stream;

    stream._ptr = 0;
    stream._cnt = 0;
    stream._base = 0;
    stream._flag = 0;
    stream._file = 0;
    stream._charbuf = 0;
    stream._bufsiz = 0;
    stream._tmpfname = 0;

    ok_int(_flsbuf('a', &stream), EOF);


}


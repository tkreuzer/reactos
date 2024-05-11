
#pragma once

// This is no longer defined in latest CRT headers
struct _iobuf {
    char *_ptr;
    int _cnt;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char *_tmpfname;
};
typedef struct _iobuf FILE;
#define _FILE_DEFINED

#include <stdio.h>

#define _IOREAD 0x0001
#define _IOWRT 0x0002
#define _IOMYBUF 0x0008
#define _IOEOF 0x0010
#define _IOERR 0x0020
#define _IOSTRG 0x0040
#define _IORW 0x0080
#define _USERBUF 0x0100

#define	STDIN_FILENO	0
#define	STDOUT_FILENO	1
#define	STDERR_FILENO	2

_Check_return_opt_
_CRTIMP
int
__cdecl
_flsbuf(
    _In_ int _Ch,
    _Inout_ FILE *_File);

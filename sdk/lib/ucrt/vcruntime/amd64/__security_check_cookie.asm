        title   __security_check_cookie - Check the provided cookie value
;***
;strcat.asm - contains strcat() and strcpy() routines
;
;       Copyright (c) Microsoft Corporation. All rights reserved.
;
;Purpose:
;       STRCAT concatenates (appends) a copy of the source string to the
;       end of the destination string, returning the destination string.
;
;*******************************************************************************
include ksamd64.inc
        subttl  "strcat"

EXTERN __security_cookie:QWORD

PUBLIC __security_check_cookie
__security_check_cookie:
    cmp rcx, __security_cookie
    je  __security_check_cookie_return
    call __report_securityfailure
__security_check_cookie_return:
    ret

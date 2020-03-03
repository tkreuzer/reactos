# Created from 7601.24214.180801-1700.win7sp1_ldr_escrow_CLIENT_PROFESSIONAL_x86FRE_en-us.iso
@ cdecl -stub -version=0x601 -arch=i386 _CIacos()
@ cdecl -stub -version=0x601 -arch=i386 _CIasin()
@ cdecl -stub -version=0x601 -arch=i386 _CIatan()
@ cdecl -stub -version=0x601 -arch=i386 _CIatan2()
@ cdecl -stub -version=0x601 -arch=i386 _CIcos()
@ cdecl -stub -version=0x601 -arch=i386 _CIcosh()
@ cdecl -stub -version=0x601 -arch=i386 _CIexp()
@ cdecl -stub -version=0x601 -arch=i386 _CIfmod()
@ cdecl -stub -version=0x601 -arch=i386 _CIlog()
@ cdecl -stub -version=0x601 -arch=i386 _CIlog10()
@ cdecl -stub -version=0x601 -arch=i386 _CIpow()
@ cdecl -stub -version=0x601 -arch=i386 _CIsin()
@ cdecl -stub -version=0x601 -arch=i386 _CIsinh()
@ cdecl -stub -version=0x601 -arch=i386 _CIsqrt()
@ cdecl -stub -version=0x601 -arch=i386 _CItan()
@ cdecl -stub -version=0x601 -arch=i386 _CItanh()
#@ stub -version=0x601 _Cbuild
#@ stub -version=0x601 _Cmulcc
#@ stub -version=0x601 _Cmulcr
#@ stub -version=0x601 _CreateFrameInfo
@ stdcall _CxxThrowException(long long)
@ cdecl -i386 -norelay _EH_prolog()
#@ stub -version=0x601 _Exit
#@ stub -version=0x601 _FCbuild
#@ stub -version=0x601 _FCmulcc
#@ stub -version=0x601 _FCmulcr
#@ stub -version=0x601 _FindAndUnlinkFrame
#@ stub -version=0x601 -arch=x86_64 _GetImageBase
#@ stub -version=0x601 -arch=x86_64 _GetThrowImageBase
@ cdecl _Getdays()
@ cdecl _Getmonths()
@ cdecl _Gettnames()
#@ stub -version=0x601 _IsExceptionObjectToBeDestroyed
#@ stub -version=0x601 _LCbuild
#@ stub -version=0x601 _LCmulcc
#@ stub -version=0x601 _LCmulcr
#@ stub -version=0x601 -arch=i386 _NLG_Dispatch2
#@ stub -version=0x601 -arch=i386 _NLG_Return
#@ stub -version=0x601 -arch=i386 _NLG_Return2
#@ stub -version=0x601 -arch=x86_64 _SetImageBase
#@ stub -version=0x601 -arch=x86_64 _SetThrowImageBase
#@ stub -version=0x601 _SetWinRTOutOfMemoryExceptionCallback
@ cdecl _Strftime(str long str ptr ptr)
#@ stub -version=0x601 _W_Getdays
#@ stub -version=0x601 _W_Getmonths
#@ stub -version=0x601 _W_Gettnames
#@ stub -version=0x601 _Wcsftime
#@ stub -version=0x601 __AdjustPointer
#@ stub -version=0x601 __BuildCatchObject
#@ stub -version=0x601 __BuildCatchObjectHelper
@ stdcall -arch=x86_64,arm __C_specific_handler(ptr long ptr ptr)
@ cdecl __CxxDetectRethrow(ptr)
@ cdecl __CxxExceptionFilter()
@ cdecl -arch=i386,x86_64 -norelay __CxxFrameHandler(ptr ptr ptr ptr)
@ cdecl -arch=i386 -norelay __CxxFrameHandler2(ptr ptr ptr ptr) __CxxFrameHandler
@ cdecl -arch=arm -norelay __CxxFrameHandler3(ptr ptr ptr ptr)
@ stdcall -i386 __CxxLongjmpUnwind(ptr)
#@ stub -version=0x601 __CxxQueryExceptionSize
#@ stub -version=0x601 __CxxRegisterExceptionObject
#@ stub -version=0x601 __CxxUnregisterExceptionObject
@ cdecl -version=0x600+ __DestructExceptionObject(ptr)
#@ stub -version=0x601 __FrameUnwindFilter
#@ stub -version=0x601 __GetPlatformExceptionInfo
#@ stub -version=0x601 -arch=x86_64 __NLG_Dispatch2
#@ stub -version=0x601 -arch=x86_64 __NLG_Return2
#@ stub -version=0x601 __RTCastToVoid
@ cdecl __RTDynamicCast(ptr long ptr ptr long) MSVCRT___RTDynamicCast
@ cdecl __RTtypeid(ptr) MSVCRT___RTtypeid
#@ stub -version=0x601 __TypeMatch
@ cdecl ___lc_codepage_func()
@ cdecl ___lc_collate_cp_func()
#@ stub -version=0x601 ___lc_locale_name_func
@ cdecl ___mb_cur_max_func()
#@ stub -version=0x601 ___mb_cur_max_l_func
#@ stub -version=0x601 __acrt_iob_func
#@ stub -version=0x601 __conio_common_vcprintf
#@ stub -version=0x601 __conio_common_vcprintf_p
#@ stub -version=0x601 __conio_common_vcprintf_s
#@ stub -version=0x601 __conio_common_vcscanf
#@ stub -version=0x601 __conio_common_vcwprintf
#@ stub -version=0x601 __conio_common_vcwprintf_p
#@ stub -version=0x601 __conio_common_vcwprintf_s
#@ stub -version=0x601 __conio_common_vcwscanf
#@ stub -version=0x601 -arch=i386 __control87_2
#@ stub -version=0x601 __current_exception
#@ stub -version=0x601 __current_exception_context
#@ stub -version=0x601 __daylight
#@ stub -version=0x601 __dcrt_get_wide_environment_from_os
#@ stub -version=0x601 __dcrt_initial_narrow_environment
@ cdecl __doserrno()
#@ stub -version=0x601 __dstbias
#@ stub -version=0x601 __fpe_flt_rounds
@ cdecl __fpecode()
#@ stub -version=0x601 __initialize_lconv_for_unsigned_char
#@ stub -version=0x601 -arch=i386 __intrinsic_abnormal_termination
#@ stub -version=0x601 __intrinsic_setjmp
#@ stub -version=0x601 -arch=x86_64 __intrinsic_setjmpex
@ cdecl __isascii(long)
@ cdecl __iscsym(long)
@ cdecl __iscsymf(long)
#@ stub -version=0x601 __iswcsym
#@ stub -version=0x601 __iswcsymf
#@ stub -version=0x601 -arch=i386 __libm_sse2_acos
#@ stub -version=0x601 -arch=i386 __libm_sse2_acosf
#@ stub -version=0x601 -arch=i386 __libm_sse2_asin
#@ stub -version=0x601 -arch=i386 __libm_sse2_asinf
#@ stub -version=0x601 -arch=i386 __libm_sse2_atan
#@ stub -version=0x601 -arch=i386 __libm_sse2_atan2
#@ stub -version=0x601 -arch=i386 __libm_sse2_atanf
#@ stub -version=0x601 -arch=i386 __libm_sse2_cos
#@ stub -version=0x601 -arch=i386 __libm_sse2_cosf
#@ stub -version=0x601 -arch=i386 __libm_sse2_exp
#@ stub -version=0x601 -arch=i386 __libm_sse2_expf
#@ stub -version=0x601 -arch=i386 __libm_sse2_log
#@ stub -version=0x601 -arch=i386 __libm_sse2_log10
#@ stub -version=0x601 -arch=i386 __libm_sse2_log10f
#@ stub -version=0x601 -arch=i386 __libm_sse2_logf
#@ stub -version=0x601 -arch=i386 __libm_sse2_pow
#@ stub -version=0x601 -arch=i386 __libm_sse2_powf
#@ stub -version=0x601 -arch=i386 __libm_sse2_sin
#@ stub -version=0x601 -arch=i386 __libm_sse2_sinf
#@ stub -version=0x601 -arch=i386 __libm_sse2_tan
#@ stub -version=0x601 -arch=i386 __libm_sse2_tanf
@ cdecl __p___argc()
#@ stub -version=0x601 __p___argv
#@ stub -version=0x601 __p___wargv
#@ stub -version=0x601 __p__acmdln
#@ stub -version=0x601 __p__commode
#@ stub -version=0x601 __p__environ
#@ stub -version=0x601 __p__fmode
#@ stub -version=0x601 __p__mbcasemap
#@ stub -version=0x601 __p__mbctype
#@ stub -version=0x601 __p__pgmptr
#@ stub -version=0x601 __p__wcmdln
#@ stub -version=0x601 __p__wenviron
#@ stub -version=0x601 __p__wpgmptr
@ cdecl __pctype_func()
#@ stub -version=0x601 __processing_throw
@ cdecl __pwctype_func()
@ cdecl __pxcptinfoptrs()
#@ stub -version=0x601 __report_gsfailure
@ cdecl __setusermatherr(ptr)
#@ stub -version=0x601 __std_exception_copy
#@ stub -version=0x601 __std_exception_destroy
#@ stub -version=0x601 __std_terminate
#@ stub -version=0x601 __std_type_info_compare
#@ stub -version=0x601 __std_type_info_destroy_list
#@ stub -version=0x601 __std_type_info_hash
#@ stub -version=0x601 __std_type_info_name
#@ stub -version=0x601 __stdio_common_vfprintf
#@ stub -version=0x601 __stdio_common_vfprintf_p
#@ stub -version=0x601 __stdio_common_vfprintf_s
#@ stub -version=0x601 __stdio_common_vfscanf
#@ stub -version=0x601 __stdio_common_vfwprintf
#@ stub -version=0x601 __stdio_common_vfwprintf_p
#@ stub -version=0x601 __stdio_common_vfwprintf_s
#@ stub -version=0x601 __stdio_common_vfwscanf
#@ stub -version=0x601 __stdio_common_vsnprintf_s
#@ stub -version=0x601 __stdio_common_vsnwprintf_s
#@ stub -version=0x601 __stdio_common_vsprintf
#@ stub -version=0x601 __stdio_common_vsprintf_p
#@ stub -version=0x601 __stdio_common_vsprintf_s
#@ stub -version=0x601 __stdio_common_vsscanf
#@ stub -version=0x601 __stdio_common_vswprintf
#@ stub -version=0x601 __stdio_common_vswprintf_p
#@ stub -version=0x601 __stdio_common_vswprintf_s
#@ stub -version=0x601 __stdio_common_vswscanf
#@ stub -version=0x601 __strncnt
#@ stub -version=0x601 __sys_errlist
#@ stub -version=0x601 __sys_nerr
@ cdecl __threadhandle() kernel32.GetCurrentThread
@ cdecl __threadid() kernel32.GetCurrentThreadId
#@ stub -version=0x601 __timezone
@ cdecl __toascii(long)
#@ stub -version=0x601 __tzname
@ cdecl __unDName(ptr str long ptr ptr long)
@ cdecl __unDNameEx(ptr str long ptr ptr ptr long)
#@ stub -version=0x601 __uncaught_exception
#@ stub -version=0x601 __uncaught_exceptions
@ cdecl __wcserror(wstr)
#@ stub -version=0x601 __wcserror_s
#@ stub -version=0x601 __wcsncnt
# stub _abs64
@ cdecl _access(str long)
#@ stub -version=0x601 _access_s
@ cdecl _aligned_free(ptr)
@ cdecl _aligned_malloc(long long)
#@ stub -version=0x601 _aligned_msize
@ cdecl _aligned_offset_malloc(long long long)
@ cdecl _aligned_offset_realloc(ptr long long long)
#@ stub -version=0x601 _aligned_offset_recalloc
@ cdecl _aligned_realloc(ptr long long)
#@ stub -version=0x601 _aligned_recalloc
@ cdecl _assert(str str long)
@ cdecl -stub _atodbl(ptr str)
#@ stub -version=0x601 _atodbl_l
#@ stub -version=0x601 _atof_l
#@ stub -version=0x601 _atoflt
#@ stub -version=0x601 _atoflt_l
@ cdecl -ret64 _atoi64(str)
#@ stub -version=0x601 _atoi64_l
#@ stub -version=0x601 _atoi_l
#@ stub -version=0x601 _atol_l
@ cdecl _atoldbl(ptr str)
#@ stub -version=0x601 _atoldbl_l
#@ stub -version=0x601 _atoll_l
@ cdecl _beep(long long)
@ cdecl _beginthread(ptr long ptr)
@ cdecl _beginthreadex(ptr long ptr ptr long ptr)
#@ stub -version=0x601 _byteswap_uint64
#@ stub -version=0x601 _byteswap_ulong
#@ stub -version=0x601 _byteswap_ushort
@ cdecl _c_exit()
@ cdecl _cabs(long)
@ cdecl _callnewh(long)
#@ stub -version=0x601 _calloc_base
@ cdecl _cexit()
@ cdecl _cgets(str)
#@ stub -version=0x601 _cgets_s
@ cdecl -stub _cgetws(wstr)
#@ stub -version=0x601 _cgetws_s
@ cdecl _chdir(str)
@ cdecl _chdrive(long)
@ cdecl _chgsign(double)
#@ stub -version=0x601 _chgsignf
@ cdecl -i386 -norelay _chkesp()
@ cdecl _chmod(str long)
@ cdecl _chsize(long long)
#@ stub -version=0x601 _chsize_s
#@ stub -version=0x601 _clearfp
@ cdecl _close(long)
@ cdecl _commit(long)
#@ stub -version=0x601 _configthreadlocale
#@ stub -version=0x601 _configure_narrow_argv
#@ stub -version=0x601 _configure_wide_argv
#@ stub -version=0x601 _control87
@ cdecl _controlfp(long long)
#@ stub -version=0x601 _controlfp_s
@ cdecl _copysign( double double )
@ cdecl -stub _copysignf(long long) # got this for x86
@ cdecl _cputs(str)
@ cdecl -stub _cputws(wstr)
@ cdecl _creat(str long)
#@ stub -version=0x601 _create_locale
#@ stub -version=0x601 _crt_at_quick_exit
#@ stub -version=0x601 _crt_atexit
#@ stub -version=0x601 -arch=i386 _crt_debugger_hook
#@ stub -version=0x601 _ctime32
#@ stub -version=0x601 _ctime32_s
@ cdecl _ctime64(ptr)
#@ stub -version=0x601 _ctime64_s
@ cdecl _cwait(ptr long long)
#@ stub -version=0x601 _d_int
#@ stub -version=0x601 _dclass
#@ stub -version=0x601 _dexp
#@ stub -version=0x601 _difftime32
#@ stub -version=0x601 _difftime64
#@ stub -version=0x601 _dlog
#@ stub -version=0x601 _dnorm
#@ stub -version=0x601 _dpcomp
#@ stub -version=0x601 _dpoly
#@ stub -version=0x601 _dscale
#@ stub -version=0x601 _dsign
#@ stub -version=0x601 _dsin
#@ stub -version=0x601 _dtest
#@ stub -version=0x601 _dunscale
@ cdecl _dup(long)
@ cdecl _dup2(long long)
#@ stub -version=0x601 _dupenv_s
@ cdecl _ecvt(double long ptr ptr)
#@ stub -version=0x601 _ecvt_s
@ cdecl _endthread()
@ cdecl _endthreadex(long)
@ cdecl _eof(long)
@ cdecl _errno()
#@ stub -version=0x601 _except1
@ cdecl -i386 _except_handler2(ptr ptr ptr ptr)
@ cdecl -i386 _except_handler3(ptr ptr ptr ptr)
@ cdecl -i386 -version=0x600+ _except_handler4_common(ptr ptr ptr ptr ptr ptr)
@ varargs _execl(str str)
@ varargs _execle(str str)
@ varargs _execlp(str str)
@ varargs _execlpe(str str)
#@ stub -version=0x601 _execute_onexit_table
@ cdecl _execv(str ptr)
@ cdecl _execve(str ptr ptr)
@ cdecl _execvp(str ptr)
@ cdecl _execvpe(str ptr ptr)
@ cdecl _exit(long)
@ cdecl _expand(ptr long)
#@ stub -version=0x601 _fclose_nolock
@ cdecl _fcloseall()
@ cdecl _fcvt(double long ptr ptr)
#@ stub -version=0x601 _fcvt_s
#@ stub -version=0x601 _fd_int
#@ stub -version=0x601 _fdclass
#@ stub -version=0x601 _fdexp
#@ stub -version=0x601 _fdlog
#@ stub -version=0x601 _fdnorm
@ cdecl _fdopen(long str)
#@ stub -version=0x601 _fdpcomp
#@ stub -version=0x601 _fdpoly
#@ stub -version=0x601 _fdscale
#@ stub -version=0x601 _fdsign
#@ stub -version=0x601 _fdsin
#@ stub -version=0x601 _fdtest
#@ stub -version=0x601 _fdunscale
#@ stub -version=0x601 _fflush_nolock
#@ stub -version=0x601 _fgetc_nolock
@ cdecl _fgetchar()
#@ stub -version=0x601 _fgetwc_nolock
@ cdecl _fgetwchar()
@ cdecl _filelength(long)
@ cdecl -ret64 _filelengthi64(long)
@ cdecl _fileno(ptr)
@ cdecl _findclose(long)
#@ stub -version=0x601 _findfirst32
#@ stub -version=0x601 _findfirst32i64
@ cdecl _findfirst64(str ptr)
#@ stub -version=0x601 _findfirst64i32
#@ stub -version=0x601 _findnext32
#@ stub -version=0x601 _findnext32i64
@ cdecl _findnext64(long ptr)
#@ stub -version=0x601 _findnext64i32
@ cdecl _finite(double)
#@ stub -version=0x601 -arch=x86_64 _finitef
@ cdecl _flushall()
@ cdecl _fpclass(double)
#@ stub -version=0x601 -arch=x86_64 _fpclassf
@ cdecl _fpieee_flt(long ptr ptr)
@ cdecl _fpreset()
#@ stub -version=0x601 _fputc_nolock
@ cdecl _fputchar(long)
#@ stub -version=0x601 _fputwc_nolock
@ cdecl _fputwchar(long)
#@ stub -version=0x601 _fread_nolock
#@ stub -version=0x601 _fread_nolock_s
#@ stub -version=0x601 _free_base
#@ stub -version=0x601 _free_locale
#@ stub -version=0x601 _fseek_nolock
#@ stub -version=0x601 _fseeki64
#@ stub -version=0x601 _fseeki64_nolock
@ cdecl _fsopen(str str long)
#@ stub -version=0x601 _fstat32
#@ stub -version=0x601 _fstat32i64
@ cdecl _fstat64(long ptr)
#@ stub -version=0x601 _fstat64i32
#@ stub -version=0x601 _ftell_nolock
#@ stub -version=0x601 _ftelli64
#@ stub -version=0x601 _ftelli64_nolock
#@ stub -version=0x601 _ftime32
#@ stub -version=0x601 _ftime32_s
@ cdecl _ftime64(ptr)
#@ stub -version=0x601 _ftime64_s
@ cdecl -arch=i386 -ret64 _ftol()
@ cdecl _fullpath(ptr str long)
#@ stub -version=0x601 _futime32
@ cdecl _futime64(long ptr)
#@ stub -version=0x601 _fwrite_nolock
@ cdecl _gcvt(double long str)
#@ stub -version=0x601 _gcvt_s
#@ stub -version=0x601 -arch=x86_64 _get_FMA3_enable
#@ stub -version=0x601 _get_current_locale
#@ stub -version=0x601 _get_daylight
#@ stub -version=0x601 _get_doserrno
#@ stub -version=0x601 _get_dstbias
#@ stub -version=0x601 _get_errno
#@ stub -version=0x601 _get_fmode
# @ cdecl _get_heap_handle()
#@ stub -version=0x601 _get_initial_narrow_environment
#@ stub -version=0x601 _get_initial_wide_environment
#@ stub -version=0x601 _get_invalid_parameter_handler
#@ stub -version=0x601 _get_narrow_winmain_command_line
@ cdecl _get_osfhandle(long)
#@ stub -version=0x601 _get_pgmptr
#@ stub -version=0x601 _get_printf_count_output
#@ stub -version=0x601 _get_purecall_handler
#@ stub -version=0x601 _get_stream_buffer_pointers
#@ stub -version=0x601 _get_terminate
#@ stub -version=0x601 _get_thread_local_invalid_parameter_handler
#@ stub -version=0x601 _get_timezone
#@ stub -version=0x601 _get_tzname
#@ stub -version=0x601 _get_unexpected
#@ stub -version=0x601 _get_wide_winmain_command_line
#@ stub -version=0x601 _get_wpgmptr
#@ stub -version=0x601 _getc_nolock
@ cdecl _getch()
#@ stub -version=0x601 _getch_nolock
@ cdecl _getche()
#@ stub -version=0x601 _getche_nolock
@ cdecl _getcwd(str long)
@ cdecl _getdcwd(long str long)
@ cdecl _getdiskfree(long ptr)
@ cdecl _getdllprocaddr(long str long)
@ cdecl _getdrive()
@ cdecl _getdrives() kernel32.GetLogicalDrives
@ cdecl _getmaxstdio()
@ cdecl _getmbcp()
@ cdecl _getpid() kernel32.GetCurrentProcessId
@ cdecl _getsystime(ptr)
@ cdecl _getw(ptr)
#@ stub -version=0x601 _getwc_nolock
@ cdecl -stub _getwch()
#@ stub -version=0x601 _getwch_nolock
@ cdecl -stub _getwche()
#@ stub -version=0x601 _getwche_nolock
@ cdecl _getws(ptr)
#@ stub -version=0x601 _getws_s
@ cdecl -i386 _global_unwind2(ptr)
#@ stub -version=0x601 _gmtime32
#@ stub -version=0x601 _gmtime32_s
@ cdecl _gmtime64(ptr)
#@ stub -version=0x601 _gmtime64_s
@ cdecl _heapchk()
@ cdecl _heapmin()
@ cdecl _heapwalk(ptr)
@ cdecl _hypot(double double)
@ cdecl -stub _hypotf(long long) # got this for x86
@ cdecl _i64toa(long long ptr long)
#@ stub -version=0x601 _i64toa_s
@ cdecl _i64tow(long long ptr long)
#@ stub -version=0x601 _i64tow_s
#@ stub -version=0x601 _initialize_narrow_environment
#@ stub -version=0x601 _initialize_onexit_table
#@ stub -version=0x601 _initialize_wide_environment
@ cdecl _initterm(ptr ptr)
#@ stub -version=0x601 _initterm_e
#@ stub -version=0x601 _invalid_parameter_noinfo
#@ stub -version=0x601 _invalid_parameter_noinfo_noreturn
#@ stub -version=0x601 _invoke_watson
#@ stub -version=0x601 _is_exception_typeof
#@ stub -version=0x601 _isalnum_l
#@ stub -version=0x601 _isalpha_l
@ cdecl _isatty(long)
#@ stub -version=0x601 _isblank_l
#@ stub -version=0x601 _iscntrl_l
@ cdecl _isctype(long long)
#@ stub -version=0x601 _isctype_l
#@ stub -version=0x601 _isdigit_l
#@ stub -version=0x601 _isgraph_l
#@ stub -version=0x601 _isleadbyte_l
#@ stub -version=0x601 _islower_l
@ cdecl _ismbbalnum(long)
#@ stub -version=0x601 _ismbbalnum_l
@ cdecl _ismbbalpha(long)
#@ stub -version=0x601 _ismbbalpha_l
#@ stub -version=0x601 _ismbbblank
#@ stub -version=0x601 _ismbbblank_l
@ cdecl _ismbbgraph(long)
#@ stub -version=0x601 _ismbbgraph_l
@ cdecl _ismbbkalnum(long)
#@ stub -version=0x601 _ismbbkalnum_l
@ cdecl _ismbbkana(long)
#@ stub -version=0x601 _ismbbkana_l
@ cdecl -stub _ismbbkprint(long) # in msvcrt/stubs.c
#@ stub -version=0x601 _ismbbkprint_l
@ cdecl _ismbbkpunct(long)
#@ stub -version=0x601 _ismbbkpunct_l
@ cdecl _ismbblead(long)
#@ stub -version=0x601 _ismbblead_l
@ cdecl _ismbbprint(long)
#@ stub -version=0x601 _ismbbprint_l
@ cdecl _ismbbpunct(long)
#@ stub -version=0x601 _ismbbpunct_l
@ cdecl _ismbbtrail(long)
#@ stub -version=0x601 _ismbbtrail_l
@ cdecl _ismbcalnum(long)
#@ stub -version=0x601 _ismbcalnum_l
@ cdecl _ismbcalpha(long)
#@ stub -version=0x601 _ismbcalpha_l
#@ stub -version=0x601 _ismbcblank
#@ stub -version=0x601 _ismbcblank_l
@ cdecl _ismbcdigit(long)
#@ stub -version=0x601 _ismbcdigit_l
@ cdecl _ismbcgraph(long)
#@ stub -version=0x601 _ismbcgraph_l
@ cdecl _ismbchira(long)
#@ stub -version=0x601 _ismbchira_l
@ cdecl _ismbckata(long)
#@ stub -version=0x601 _ismbckata_l
@ cdecl _ismbcl0(long)
#@ stub -version=0x601 _ismbcl0_l
@ cdecl _ismbcl1(long)
#@ stub -version=0x601 _ismbcl1_l
@ cdecl _ismbcl2(long)
#@ stub -version=0x601 _ismbcl2_l
@ cdecl _ismbclegal(long)
#@ stub -version=0x601 _ismbclegal_l
@ cdecl _ismbclower(long)
#@ stub -version=0x601 _ismbclower_l
@ cdecl _ismbcprint(long)
#@ stub -version=0x601 _ismbcprint_l
@ cdecl _ismbcpunct(long)
#@ stub -version=0x601 _ismbcpunct_l
@ cdecl _ismbcspace(long)
#@ stub -version=0x601 _ismbcspace_l
@ cdecl _ismbcsymbol(long)
#@ stub -version=0x601 _ismbcsymbol_l
@ cdecl _ismbcupper(long)
#@ stub -version=0x601 _ismbcupper_l
@ cdecl _ismbslead(ptr ptr)
#@ stub -version=0x601 _ismbslead_l
@ cdecl _ismbstrail(ptr ptr)
#@ stub -version=0x601 _ismbstrail_l
@ cdecl _isnan(double)
#@ stub -version=0x601 -arch=x86_64 _isnanf
#@ stub -version=0x601 _isprint_l
#@ stub -version=0x601 _ispunct_l
#@ stub -version=0x601 _isspace_l
#@ stub -version=0x601 _isupper_l
#@ stub -version=0x601 _iswalnum_l
#@ stub -version=0x601 _iswalpha_l
#@ stub -version=0x601 _iswblank_l
#@ stub -version=0x601 _iswcntrl_l
#@ stub -version=0x601 _iswcsym_l
#@ stub -version=0x601 _iswcsymf_l
#@ stub -version=0x601 _iswctype_l
#@ stub -version=0x601 _iswdigit_l
#@ stub -version=0x601 _iswgraph_l
#@ stub -version=0x601 _iswlower_l
#@ stub -version=0x601 _iswprint_l
#@ stub -version=0x601 _iswpunct_l
#@ stub -version=0x601 _iswspace_l
#@ stub -version=0x601 _iswupper_l
#@ stub -version=0x601 _iswxdigit_l
#@ stub -version=0x601 _isxdigit_l
@ cdecl _itoa(long ptr long)
#@ stub -version=0x601 _itoa_s
@ cdecl _itow(long ptr long)
#@ stub -version=0x601 _itow_s
@ cdecl _j0(double)
@ cdecl _j1(double)
@ cdecl _jn(long double)
@ cdecl _kbhit()
#@ stub -version=0x601 _ld_int
#@ stub -version=0x601 _ldclass
#@ stub -version=0x601 _ldexp
#@ stub -version=0x601 _ldlog
#@ stub -version=0x601 _ldpcomp
#@ stub -version=0x601 _ldpoly
#@ stub -version=0x601 _ldscale
#@ stub -version=0x601 _ldsign
#@ stub -version=0x601 _ldsin
#@ stub -version=0x601 _ldtest
#@ stub -version=0x601 _ldunscale
@ cdecl _lfind(ptr ptr ptr long ptr)
#@ stub -version=0x601 _lfind_s
#@ stub -version=0x601 -arch=i386 _libm_sse2_acos_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_asin_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_atan_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_cos_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_exp_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_log10_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_log_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_pow_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_sin_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_sqrt_precise
#@ stub -version=0x601 -arch=i386 _libm_sse2_tan_precise
@ cdecl _loaddll(str)
#@ stub -version=0x601 -arch=x86_64 _local_unwind
@ cdecl -i386 _local_unwind2(ptr long)
@ cdecl -i386 -version=0x600+ _local_unwind4(ptr ptr long)
#@ stub -version=0x601 _localtime32
#@ stub -version=0x601 _localtime32_s
@ cdecl _localtime64(ptr)
#@ stub -version=0x601 _localtime64_s
#@ stub -version=0x601 _lock_file
#@ stub -version=0x601 _lock_locales
@ cdecl _locking(long long long)
@ cdecl _logb(double)
#@ stub -version=0x601 -arch=x86_64 _logbf
@ cdecl -i386 _longjmpex(ptr long) longjmp
@ cdecl _lrotl(long long)
@ cdecl _lrotr(long long)
@ cdecl _lsearch(ptr ptr long long ptr)
#@ stub -version=0x601 _lsearch_s
@ cdecl _lseek(long long long)
@ cdecl -ret64 _lseeki64(long double long)
@ cdecl _ltoa(long ptr long)
#@ stub -version=0x601 _ltoa_s
@ cdecl _ltow(long ptr long)
#@ stub -version=0x601 _ltow_s
@ cdecl _makepath(ptr str str str str)
#@ stub -version=0x601 _makepath_s
#@ stub -version=0x601 _malloc_base
@ cdecl _mbbtombc(long)
#@ stub -version=0x601 _mbbtombc_l
@ cdecl _mbbtype(long long)
#@ stub -version=0x601 _mbbtype_l
#@ extern _mbcasemap # in msvcrt(stubs.c
@ cdecl _mbccpy (str str)
#@ stub -version=0x601 _mbccpy_l
#@ stub -version=0x601 _mbccpy_s
#@ stub -version=0x601 _mbccpy_s_l
@ cdecl _mbcjistojms(long)
#@ stub -version=0x601 _mbcjistojms_l
@ cdecl _mbcjmstojis(long)
#@ stub -version=0x601 _mbcjmstojis_l
@ cdecl _mbclen(ptr)
#@ stub -version=0x601 _mbclen_l
@ cdecl _mbctohira(long)
#@ stub -version=0x601 _mbctohira_l
@ cdecl _mbctokata(long)
#@ stub -version=0x601 _mbctokata_l
@ cdecl _mbctolower(long)
#@ stub -version=0x601 _mbctolower_l
@ cdecl _mbctombb(long)
#@ stub -version=0x601 _mbctombb_l
@ cdecl _mbctoupper(long)
#@ stub -version=0x601 _mbctoupper_l
#@ stub -version=0x601 _mblen_l
@ cdecl _mbsbtype(str long)
#@ stub -version=0x601 _mbsbtype_l
#@ stub -version=0x601 _mbscat_s
#@ stub -version=0x601 _mbscat_s_l
@ cdecl _mbschr(str long)
#@ stub -version=0x601 _mbschr_l
@ cdecl _mbscmp(str str)
#@ stub -version=0x601 _mbscmp_l
@ cdecl _mbscoll(str str)
#@ stub -version=0x601 _mbscoll_l
#@ stub -version=0x601 _mbscpy_s
#@ stub -version=0x601 _mbscpy_s_l
@ cdecl _mbscspn(str str)
#@ stub -version=0x601 _mbscspn_l
@ cdecl _mbsdec(ptr ptr)
#@ stub -version=0x601 _mbsdec_l
@ cdecl _mbsdup(str)
@ cdecl _mbsicmp(str str)
#@ stub -version=0x601 _mbsicmp_l
@ cdecl _mbsicoll(str str)
#@ stub -version=0x601 _mbsicoll_l
@ cdecl _mbsinc(str)
#@ stub -version=0x601 _mbsinc_l
@ cdecl _mbslen(str)
#@ stub -version=0x601 _mbslen_l
@ cdecl _mbslwr(str)
#@ stub -version=0x601 _mbslwr_l
#@ stub -version=0x601 _mbslwr_s
#@ stub -version=0x601 _mbslwr_s_l
@ cdecl _mbsnbcat(str str long)
#@ stub -version=0x601 _mbsnbcat_l
#@ stub -version=0x601 _mbsnbcat_s
#@ stub -version=0x601 _mbsnbcat_s_l
@ cdecl _mbsnbcmp(str str long)
#@ stub -version=0x601 _mbsnbcmp_l
@ cdecl _mbsnbcnt(ptr long)
#@ stub -version=0x601 _mbsnbcnt_l
@ cdecl _mbsnbcoll(str str long)
#@ stub -version=0x601 _mbsnbcoll_l
@ cdecl _mbsnbcpy(ptr str long)
#@ stub -version=0x601 _mbsnbcpy_l
#@ stub -version=0x601 _mbsnbcpy_s
#@ stub -version=0x601 _mbsnbcpy_s_l
@ cdecl _mbsnbicmp(str str long)
#@ stub -version=0x601 _mbsnbicmp_l
@ cdecl _mbsnbicoll(str str long)
#@ stub -version=0x601 _mbsnbicoll_l
@ cdecl _mbsnbset(str long long)
#@ stub -version=0x601 _mbsnbset_l
#@ stub -version=0x601 _mbsnbset_s
#@ stub -version=0x601 _mbsnbset_s_l
@ cdecl _mbsncat(str str long)
#@ stub -version=0x601 _mbsncat_l
#@ stub -version=0x601 _mbsncat_s
#@ stub -version=0x601 _mbsncat_s_l
@ cdecl _mbsnccnt(str long)
#@ stub -version=0x601 _mbsnccnt_l
@ cdecl _mbsncmp(str str long)
#@ stub -version=0x601 _mbsncmp_l
@ cdecl _mbsncoll(str str long)
#@ stub -version=0x601 _mbsncoll_l
@ cdecl _mbsncpy(str str long)
#@ stub -version=0x601 _mbsncpy_l
#@ stub -version=0x601 _mbsncpy_s
#@ stub -version=0x601 _mbsncpy_s_l
@ cdecl _mbsnextc(str)
#@ stub -version=0x601 _mbsnextc_l
@ cdecl _mbsnicmp(str str long)
#@ stub -version=0x601 _mbsnicmp_l
@ cdecl _mbsnicoll(str str long)
#@ stub -version=0x601 _mbsnicoll_l
@ cdecl _mbsninc(str long)
#@ stub -version=0x601 _mbsninc_l
#@ stub -version=0x601 _mbsnlen
#@ stub -version=0x601 _mbsnlen_l
@ cdecl _mbsnset(str long long)
#@ stub -version=0x601 _mbsnset_l
#@ stub -version=0x601 _mbsnset_s
#@ stub -version=0x601 _mbsnset_s_l
@ cdecl _mbspbrk(str str)
#@ stub -version=0x601 _mbspbrk_l
@ cdecl _mbsrchr(str long)
#@ stub -version=0x601 _mbsrchr_l
@ cdecl _mbsrev(str)
#@ stub -version=0x601 _mbsrev_l
@ cdecl _mbsset(str long)
#@ stub -version=0x601 _mbsset_l
#@ stub -version=0x601 _mbsset_s
#@ stub -version=0x601 _mbsset_s_l
@ cdecl _mbsspn(str str)
#@ stub -version=0x601 _mbsspn_l
@ cdecl _mbsspnp(str str)
#@ stub -version=0x601 _mbsspnp_l
@ cdecl _mbsstr(str str)
#@ stub -version=0x601 _mbsstr_l
@ cdecl _mbstok(str str)
#@ stub -version=0x601 _mbstok_l
#@ stub -version=0x601 _mbstok_s
#@ stub -version=0x601 _mbstok_s_l
#@ stub -version=0x601 _mbstowcs_l
#@ stub -version=0x601 _mbstowcs_s_l
@ cdecl _mbstrlen(str)
#@ stub -version=0x601 _mbstrlen_l
#@ stub -version=0x601 _mbstrnlen
#@ stub -version=0x601 _mbstrnlen_l
@ cdecl _mbsupr(str)
#@ stub -version=0x601 _mbsupr_l
#@ stub -version=0x601 _mbsupr_s
#@ stub -version=0x601 _mbsupr_s_l
#@ stub -version=0x601 _mbtowc_l
@ cdecl _memccpy(ptr ptr long long)
@ cdecl _memicmp(str str long)
#@ stub -version=0x601 _memicmp_l
@ cdecl _mkdir(str)
#@ stub -version=0x601 _mkgmtime32
@ cdecl _mkgmtime64(ptr)
@ cdecl _mktemp(str)
#@ stub -version=0x601 _mktemp_s
#@ stub -version=0x601 _mktime32
@ cdecl _mktime64(ptr)
@ cdecl _msize(ptr)
@ cdecl _nextafter(double double)
#@ stub -version=0x601 -arch=x86_64 _nextafterf
#@ stub -version=0x601 -arch=i386 _o__CIacos
#@ stub -version=0x601 -arch=i386 _o__CIasin
#@ stub -version=0x601 -arch=i386 _o__CIatan
#@ stub -version=0x601 -arch=i386 _o__CIatan2
#@ stub -version=0x601 -arch=i386 _o__CIcos
#@ stub -version=0x601 -arch=i386 _o__CIcosh
#@ stub -version=0x601 -arch=i386 _o__CIexp
#@ stub -version=0x601 -arch=i386 _o__CIfmod
#@ stub -version=0x601 -arch=i386 _o__CIlog
#@ stub -version=0x601 -arch=i386 _o__CIlog10
#@ stub -version=0x601 -arch=i386 _o__CIpow
#@ stub -version=0x601 -arch=i386 _o__CIsin
#@ stub -version=0x601 -arch=i386 _o__CIsinh
#@ stub -version=0x601 -arch=i386 _o__CIsqrt
#@ stub -version=0x601 -arch=i386 _o__CItan
#@ stub -version=0x601 -arch=i386 _o__CItanh
#@ stub -version=0x601 _o__Getdays
#@ stub -version=0x601 _o__Getmonths
#@ stub -version=0x601 _o__Gettnames
#@ stub -version=0x601 _o__Strftime
#@ stub -version=0x601 _o__W_Getdays
#@ stub -version=0x601 _o__W_Getmonths
#@ stub -version=0x601 _o__W_Gettnames
#@ stub -version=0x601 _o__Wcsftime
#@ stub -version=0x601 _o____lc_codepage_func
#@ stub -version=0x601 _o____lc_collate_cp_func
#@ stub -version=0x601 _o____lc_locale_name_func
#@ stub -version=0x601 _o____mb_cur_max_func
#@ stub -version=0x601 _o___acrt_iob_func
#@ stub -version=0x601 _o___conio_common_vcprintf
#@ stub -version=0x601 _o___conio_common_vcprintf_p
#@ stub -version=0x601 _o___conio_common_vcprintf_s
#@ stub -version=0x601 _o___conio_common_vcscanf
#@ stub -version=0x601 _o___conio_common_vcwprintf
#@ stub -version=0x601 _o___conio_common_vcwprintf_p
#@ stub -version=0x601 _o___conio_common_vcwprintf_s
#@ stub -version=0x601 _o___conio_common_vcwscanf
#@ stub -version=0x601 _o___daylight
#@ stub -version=0x601 _o___dstbias
#@ stub -version=0x601 _o___fpe_flt_rounds
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_acos
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_acosf
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_asin
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_asinf
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_atan
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_atan2
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_atanf
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_cos
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_cosf
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_exp
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_expf
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_log
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_log10
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_log10f
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_logf
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_pow
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_powf
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_sin
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_sinf
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_tan
#@ stub -version=0x601 -arch=i386 _o___libm_sse2_tanf
#@ stub -version=0x601 _o___p___argc
#@ stub -version=0x601 _o___p___argv
#@ stub -version=0x601 _o___p___wargv
#@ stub -version=0x601 _o___p__acmdln
#@ stub -version=0x601 _o___p__commode
#@ stub -version=0x601 _o___p__environ
#@ stub -version=0x601 _o___p__fmode
#@ stub -version=0x601 _o___p__mbcasemap
#@ stub -version=0x601 _o___p__mbctype
#@ stub -version=0x601 _o___p__pgmptr
#@ stub -version=0x601 _o___p__wcmdln
#@ stub -version=0x601 _o___p__wenviron
#@ stub -version=0x601 _o___p__wpgmptr
#@ stub -version=0x601 _o___pctype_func
#@ stub -version=0x601 _o___pwctype_func
#@ stub -version=0x601 _o___std_exception_copy
#@ stub -version=0x601 _o___std_exception_destroy
#@ stub -version=0x601 _o___std_type_info_destroy_list
#@ stub -version=0x601 _o___std_type_info_name
#@ stub -version=0x601 _o___stdio_common_vfprintf
#@ stub -version=0x601 _o___stdio_common_vfprintf_p
#@ stub -version=0x601 _o___stdio_common_vfprintf_s
#@ stub -version=0x601 _o___stdio_common_vfscanf
#@ stub -version=0x601 _o___stdio_common_vfwprintf
#@ stub -version=0x601 _o___stdio_common_vfwprintf_p
#@ stub -version=0x601 _o___stdio_common_vfwprintf_s
#@ stub -version=0x601 _o___stdio_common_vfwscanf
#@ stub -version=0x601 _o___stdio_common_vsnprintf_s
#@ stub -version=0x601 _o___stdio_common_vsnwprintf_s
#@ stub -version=0x601 _o___stdio_common_vsprintf
#@ stub -version=0x601 _o___stdio_common_vsprintf_p
#@ stub -version=0x601 _o___stdio_common_vsprintf_s
#@ stub -version=0x601 _o___stdio_common_vsscanf
#@ stub -version=0x601 _o___stdio_common_vswprintf
#@ stub -version=0x601 _o___stdio_common_vswprintf_p
#@ stub -version=0x601 _o___stdio_common_vswprintf_s
#@ stub -version=0x601 _o___stdio_common_vswscanf
#@ stub -version=0x601 _o___timezone
#@ stub -version=0x601 _o___tzname
#@ stub -version=0x601 _o___wcserror
#@ stub -version=0x601 _o__access
#@ stub -version=0x601 _o__access_s
#@ stub -version=0x601 _o__aligned_free
#@ stub -version=0x601 _o__aligned_malloc
#@ stub -version=0x601 _o__aligned_msize
#@ stub -version=0x601 _o__aligned_offset_malloc
#@ stub -version=0x601 _o__aligned_offset_realloc
#@ stub -version=0x601 _o__aligned_offset_recalloc
#@ stub -version=0x601 _o__aligned_realloc
#@ stub -version=0x601 _o__aligned_recalloc
#@ stub -version=0x601 _o__atodbl
#@ stub -version=0x601 _o__atodbl_l
#@ stub -version=0x601 _o__atof_l
#@ stub -version=0x601 _o__atoflt
#@ stub -version=0x601 _o__atoflt_l
#@ stub -version=0x601 _o__atoi64
#@ stub -version=0x601 _o__atoi64_l
#@ stub -version=0x601 _o__atoi_l
#@ stub -version=0x601 _o__atol_l
#@ stub -version=0x601 _o__atoldbl
#@ stub -version=0x601 _o__atoldbl_l
#@ stub -version=0x601 _o__atoll_l
#@ stub -version=0x601 _o__beep
#@ stub -version=0x601 _o__beginthread
#@ stub -version=0x601 _o__beginthreadex
#@ stub -version=0x601 _o__cabs
#@ stub -version=0x601 _o__callnewh
#@ stub -version=0x601 _o__calloc_base
#@ stub -version=0x601 _o__cexit
#@ stub -version=0x601 _o__cgets
#@ stub -version=0x601 _o__cgets_s
#@ stub -version=0x601 _o__cgetws
#@ stub -version=0x601 _o__cgetws_s
#@ stub -version=0x601 _o__chdir
#@ stub -version=0x601 _o__chdrive
#@ stub -version=0x601 _o__chmod
#@ stub -version=0x601 _o__chsize
#@ stub -version=0x601 _o__chsize_s
#@ stub -version=0x601 _o__close
#@ stub -version=0x601 _o__commit
#@ stub -version=0x601 _o__configthreadlocale
#@ stub -version=0x601 _o__configure_narrow_argv
#@ stub -version=0x601 _o__configure_wide_argv
#@ stub -version=0x601 _o__controlfp_s
#@ stub -version=0x601 _o__cputs
#@ stub -version=0x601 _o__cputws
#@ stub -version=0x601 _o__creat
#@ stub -version=0x601 _o__create_locale
#@ stub -version=0x601 _o__crt_atexit
#@ stub -version=0x601 _o__ctime32_s
#@ stub -version=0x601 _o__ctime64_s
#@ stub -version=0x601 _o__cwait
#@ stub -version=0x601 _o__d_int
#@ stub -version=0x601 _o__dclass
#@ stub -version=0x601 _o__difftime32
#@ stub -version=0x601 _o__difftime64
#@ stub -version=0x601 _o__dlog
#@ stub -version=0x601 _o__dnorm
#@ stub -version=0x601 _o__dpcomp
#@ stub -version=0x601 _o__dpoly
#@ stub -version=0x601 _o__dscale
#@ stub -version=0x601 _o__dsign
#@ stub -version=0x601 _o__dsin
#@ stub -version=0x601 _o__dtest
#@ stub -version=0x601 _o__dunscale
#@ stub -version=0x601 _o__dup
#@ stub -version=0x601 _o__dup2
#@ stub -version=0x601 _o__dupenv_s
#@ stub -version=0x601 _o__ecvt
#@ stub -version=0x601 _o__ecvt_s
#@ stub -version=0x601 _o__endthread
#@ stub -version=0x601 _o__endthreadex
#@ stub -version=0x601 _o__eof
#@ stub -version=0x601 _o__errno
#@ stub -version=0x601 _o__except1
#@ stub -version=0x601 _o__execute_onexit_table
#@ stub -version=0x601 _o__execv
#@ stub -version=0x601 _o__execve
#@ stub -version=0x601 _o__execvp
#@ stub -version=0x601 _o__execvpe
#@ stub -version=0x601 _o__exit
#@ stub -version=0x601 _o__expand
#@ stub -version=0x601 _o__fclose_nolock
#@ stub -version=0x601 _o__fcloseall
#@ stub -version=0x601 _o__fcvt
#@ stub -version=0x601 _o__fcvt_s
#@ stub -version=0x601 _o__fd_int
#@ stub -version=0x601 _o__fdclass
#@ stub -version=0x601 _o__fdexp
#@ stub -version=0x601 _o__fdlog
#@ stub -version=0x601 _o__fdopen
#@ stub -version=0x601 _o__fdpcomp
#@ stub -version=0x601 _o__fdpoly
#@ stub -version=0x601 _o__fdscale
#@ stub -version=0x601 _o__fdsign
#@ stub -version=0x601 _o__fdsin
#@ stub -version=0x601 _o__fflush_nolock
#@ stub -version=0x601 _o__fgetc_nolock
#@ stub -version=0x601 _o__fgetchar
#@ stub -version=0x601 _o__fgetwc_nolock
#@ stub -version=0x601 _o__fgetwchar
#@ stub -version=0x601 _o__filelength
#@ stub -version=0x601 _o__filelengthi64
#@ stub -version=0x601 _o__fileno
#@ stub -version=0x601 _o__findclose
#@ stub -version=0x601 _o__findfirst32
#@ stub -version=0x601 _o__findfirst32i64
#@ stub -version=0x601 _o__findfirst64
#@ stub -version=0x601 _o__findfirst64i32
#@ stub -version=0x601 _o__findnext32
#@ stub -version=0x601 _o__findnext32i64
#@ stub -version=0x601 _o__findnext64
#@ stub -version=0x601 _o__findnext64i32
#@ stub -version=0x601 _o__flushall
#@ stub -version=0x601 _o__fpclass
#@ stub -version=0x601 -arch=x86_64 _o__fpclassf
#@ stub -version=0x601 _o__fputc_nolock
#@ stub -version=0x601 _o__fputchar
#@ stub -version=0x601 _o__fputwc_nolock
#@ stub -version=0x601 _o__fputwchar
#@ stub -version=0x601 _o__fread_nolock
#@ stub -version=0x601 _o__fread_nolock_s
#@ stub -version=0x601 _o__free_base
#@ stub -version=0x601 _o__free_locale
#@ stub -version=0x601 _o__fseek_nolock
#@ stub -version=0x601 _o__fseeki64
#@ stub -version=0x601 _o__fseeki64_nolock
#@ stub -version=0x601 _o__fsopen
#@ stub -version=0x601 _o__fstat32
#@ stub -version=0x601 _o__fstat32i64
#@ stub -version=0x601 _o__fstat64
#@ stub -version=0x601 _o__fstat64i32
#@ stub -version=0x601 _o__ftell_nolock
#@ stub -version=0x601 _o__ftelli64
#@ stub -version=0x601 _o__ftelli64_nolock
#@ stub -version=0x601 _o__ftime32
#@ stub -version=0x601 _o__ftime32_s
#@ stub -version=0x601 _o__ftime64
#@ stub -version=0x601 _o__ftime64_s
#@ stub -version=0x601 _o__fullpath
#@ stub -version=0x601 _o__futime32
#@ stub -version=0x601 _o__futime64
#@ stub -version=0x601 _o__fwrite_nolock
#@ stub -version=0x601 _o__gcvt
#@ stub -version=0x601 _o__gcvt_s
#@ stub -version=0x601 _o__get_daylight
#@ stub -version=0x601 _o__get_doserrno
#@ stub -version=0x601 _o__get_dstbias
#@ stub -version=0x601 _o__get_errno
#@ stub -version=0x601 _o__get_fmode
#@ stub -version=0x601 _o__get_heap_handle
#@ stub -version=0x601 _o__get_initial_narrow_environment
#@ stub -version=0x601 _o__get_initial_wide_environment
#@ stub -version=0x601 _o__get_invalid_parameter_handler
#@ stub -version=0x601 _o__get_narrow_winmain_command_line
#@ stub -version=0x601 _o__get_osfhandle
#@ stub -version=0x601 _o__get_pgmptr
#@ stub -version=0x601 _o__get_stream_buffer_pointers
#@ stub -version=0x601 _o__get_terminate
#@ stub -version=0x601 _o__get_thread_local_invalid_parameter_handler
#@ stub -version=0x601 _o__get_timezone
#@ stub -version=0x601 _o__get_tzname
#@ stub -version=0x601 _o__get_wide_winmain_command_line
#@ stub -version=0x601 _o__get_wpgmptr
#@ stub -version=0x601 _o__getc_nolock
#@ stub -version=0x601 _o__getch
#@ stub -version=0x601 _o__getch_nolock
#@ stub -version=0x601 _o__getche
#@ stub -version=0x601 _o__getche_nolock
#@ stub -version=0x601 _o__getcwd
#@ stub -version=0x601 _o__getdcwd
#@ stub -version=0x601 _o__getdiskfree
#@ stub -version=0x601 _o__getdllprocaddr
#@ stub -version=0x601 _o__getdrive
#@ stub -version=0x601 _o__getdrives
#@ stub -version=0x601 _o__getmbcp
#@ stub -version=0x601 _o__getsystime
#@ stub -version=0x601 _o__getw
#@ stub -version=0x601 _o__getwc_nolock
#@ stub -version=0x601 _o__getwch
#@ stub -version=0x601 _o__getwch_nolock
#@ stub -version=0x601 _o__getwche
#@ stub -version=0x601 _o__getwche_nolock
#@ stub -version=0x601 _o__getws
#@ stub -version=0x601 _o__getws_s
#@ stub -version=0x601 _o__gmtime32
#@ stub -version=0x601 _o__gmtime32_s
#@ stub -version=0x601 _o__gmtime64
#@ stub -version=0x601 _o__gmtime64_s
#@ stub -version=0x601 _o__heapchk
#@ stub -version=0x601 _o__heapmin
#@ stub -version=0x601 _o__hypot
#@ stub -version=0x601 _o__hypotf
#@ stub -version=0x601 _o__i64toa
#@ stub -version=0x601 _o__i64toa_s
#@ stub -version=0x601 _o__i64tow
#@ stub -version=0x601 _o__i64tow_s
#@ stub -version=0x601 _o__initialize_narrow_environment
#@ stub -version=0x601 _o__initialize_onexit_table
#@ stub -version=0x601 _o__initialize_wide_environment
#@ stub -version=0x601 _o__invalid_parameter_noinfo
#@ stub -version=0x601 _o__invalid_parameter_noinfo_noreturn
#@ stub -version=0x601 _o__isatty
#@ stub -version=0x601 _o__isctype
#@ stub -version=0x601 _o__isctype_l
#@ stub -version=0x601 _o__isleadbyte_l
#@ stub -version=0x601 _o__ismbbalnum
#@ stub -version=0x601 _o__ismbbalnum_l
#@ stub -version=0x601 _o__ismbbalpha
#@ stub -version=0x601 _o__ismbbalpha_l
#@ stub -version=0x601 _o__ismbbblank
#@ stub -version=0x601 _o__ismbbblank_l
#@ stub -version=0x601 _o__ismbbgraph
#@ stub -version=0x601 _o__ismbbgraph_l
#@ stub -version=0x601 _o__ismbbkalnum
#@ stub -version=0x601 _o__ismbbkalnum_l
#@ stub -version=0x601 _o__ismbbkana
#@ stub -version=0x601 _o__ismbbkana_l
#@ stub -version=0x601 _o__ismbbkprint
#@ stub -version=0x601 _o__ismbbkprint_l
#@ stub -version=0x601 _o__ismbbkpunct
#@ stub -version=0x601 _o__ismbbkpunct_l
#@ stub -version=0x601 _o__ismbblead
#@ stub -version=0x601 _o__ismbblead_l
#@ stub -version=0x601 _o__ismbbprint
#@ stub -version=0x601 _o__ismbbprint_l
#@ stub -version=0x601 _o__ismbbpunct
#@ stub -version=0x601 _o__ismbbpunct_l
#@ stub -version=0x601 _o__ismbbtrail
#@ stub -version=0x601 _o__ismbbtrail_l
#@ stub -version=0x601 _o__ismbcalnum
#@ stub -version=0x601 _o__ismbcalnum_l
#@ stub -version=0x601 _o__ismbcalpha
#@ stub -version=0x601 _o__ismbcalpha_l
#@ stub -version=0x601 _o__ismbcblank
#@ stub -version=0x601 _o__ismbcblank_l
#@ stub -version=0x601 _o__ismbcdigit
#@ stub -version=0x601 _o__ismbcdigit_l
#@ stub -version=0x601 _o__ismbcgraph
#@ stub -version=0x601 _o__ismbcgraph_l
#@ stub -version=0x601 _o__ismbchira
#@ stub -version=0x601 _o__ismbchira_l
#@ stub -version=0x601 _o__ismbckata
#@ stub -version=0x601 _o__ismbckata_l
#@ stub -version=0x601 _o__ismbcl0
#@ stub -version=0x601 _o__ismbcl0_l
#@ stub -version=0x601 _o__ismbcl1
#@ stub -version=0x601 _o__ismbcl1_l
#@ stub -version=0x601 _o__ismbcl2
#@ stub -version=0x601 _o__ismbcl2_l
#@ stub -version=0x601 _o__ismbclegal
#@ stub -version=0x601 _o__ismbclegal_l
#@ stub -version=0x601 _o__ismbclower
#@ stub -version=0x601 _o__ismbclower_l
#@ stub -version=0x601 _o__ismbcprint
#@ stub -version=0x601 _o__ismbcprint_l
#@ stub -version=0x601 _o__ismbcpunct
#@ stub -version=0x601 _o__ismbcpunct_l
#@ stub -version=0x601 _o__ismbcspace
#@ stub -version=0x601 _o__ismbcspace_l
#@ stub -version=0x601 _o__ismbcsymbol
#@ stub -version=0x601 _o__ismbcsymbol_l
#@ stub -version=0x601 _o__ismbcupper
#@ stub -version=0x601 _o__ismbcupper_l
#@ stub -version=0x601 _o__ismbslead
#@ stub -version=0x601 _o__ismbslead_l
#@ stub -version=0x601 _o__ismbstrail
#@ stub -version=0x601 _o__ismbstrail_l
#@ stub -version=0x601 _o__iswctype_l
#@ stub -version=0x601 _o__itoa
#@ stub -version=0x601 _o__itoa_s
#@ stub -version=0x601 _o__itow
#@ stub -version=0x601 _o__itow_s
#@ stub -version=0x601 _o__j0
#@ stub -version=0x601 _o__j1
#@ stub -version=0x601 _o__jn
#@ stub -version=0x601 _o__kbhit
#@ stub -version=0x601 _o__ld_int
#@ stub -version=0x601 _o__ldclass
#@ stub -version=0x601 _o__ldexp
#@ stub -version=0x601 _o__ldlog
#@ stub -version=0x601 _o__ldpcomp
#@ stub -version=0x601 _o__ldpoly
#@ stub -version=0x601 _o__ldscale
#@ stub -version=0x601 _o__ldsign
#@ stub -version=0x601 _o__ldsin
#@ stub -version=0x601 _o__ldtest
#@ stub -version=0x601 _o__ldunscale
#@ stub -version=0x601 _o__lfind
#@ stub -version=0x601 _o__lfind_s
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_acos_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_asin_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_atan_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_cos_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_exp_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_log10_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_log_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_pow_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_sin_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_sqrt_precise
#@ stub -version=0x601 -arch=i386 _o__libm_sse2_tan_precise
#@ stub -version=0x601 _o__loaddll
#@ stub -version=0x601 _o__localtime32
#@ stub -version=0x601 _o__localtime32_s
#@ stub -version=0x601 _o__localtime64
#@ stub -version=0x601 _o__localtime64_s
#@ stub -version=0x601 _o__lock_file
#@ stub -version=0x601 _o__locking
#@ stub -version=0x601 _o__logb
#@ stub -version=0x601 -arch=x86_64 _o__logbf
#@ stub -version=0x601 _o__lsearch
#@ stub -version=0x601 _o__lsearch_s
#@ stub -version=0x601 _o__lseek
#@ stub -version=0x601 _o__lseeki64
#@ stub -version=0x601 _o__ltoa
#@ stub -version=0x601 _o__ltoa_s
#@ stub -version=0x601 _o__ltow
#@ stub -version=0x601 _o__ltow_s
#@ stub -version=0x601 _o__makepath
#@ stub -version=0x601 _o__makepath_s
#@ stub -version=0x601 _o__malloc_base
#@ stub -version=0x601 _o__mbbtombc
#@ stub -version=0x601 _o__mbbtombc_l
#@ stub -version=0x601 _o__mbbtype
#@ stub -version=0x601 _o__mbbtype_l
#@ stub -version=0x601 _o__mbccpy
#@ stub -version=0x601 _o__mbccpy_l
#@ stub -version=0x601 _o__mbccpy_s
#@ stub -version=0x601 _o__mbccpy_s_l
#@ stub -version=0x601 _o__mbcjistojms
#@ stub -version=0x601 _o__mbcjistojms_l
#@ stub -version=0x601 _o__mbcjmstojis
#@ stub -version=0x601 _o__mbcjmstojis_l
#@ stub -version=0x601 _o__mbclen
#@ stub -version=0x601 _o__mbclen_l
#@ stub -version=0x601 _o__mbctohira
#@ stub -version=0x601 _o__mbctohira_l
#@ stub -version=0x601 _o__mbctokata
#@ stub -version=0x601 _o__mbctokata_l
#@ stub -version=0x601 _o__mbctolower
#@ stub -version=0x601 _o__mbctolower_l
#@ stub -version=0x601 _o__mbctombb
#@ stub -version=0x601 _o__mbctombb_l
#@ stub -version=0x601 _o__mbctoupper
#@ stub -version=0x601 _o__mbctoupper_l
#@ stub -version=0x601 _o__mblen_l
#@ stub -version=0x601 _o__mbsbtype
#@ stub -version=0x601 _o__mbsbtype_l
#@ stub -version=0x601 _o__mbscat_s
#@ stub -version=0x601 _o__mbscat_s_l
#@ stub -version=0x601 _o__mbschr
#@ stub -version=0x601 _o__mbschr_l
#@ stub -version=0x601 _o__mbscmp
#@ stub -version=0x601 _o__mbscmp_l
#@ stub -version=0x601 _o__mbscoll
#@ stub -version=0x601 _o__mbscoll_l
#@ stub -version=0x601 _o__mbscpy_s
#@ stub -version=0x601 _o__mbscpy_s_l
#@ stub -version=0x601 _o__mbscspn
#@ stub -version=0x601 _o__mbscspn_l
#@ stub -version=0x601 _o__mbsdec
#@ stub -version=0x601 _o__mbsdec_l
#@ stub -version=0x601 _o__mbsicmp
#@ stub -version=0x601 _o__mbsicmp_l
#@ stub -version=0x601 _o__mbsicoll
#@ stub -version=0x601 _o__mbsicoll_l
#@ stub -version=0x601 _o__mbsinc
#@ stub -version=0x601 _o__mbsinc_l
#@ stub -version=0x601 _o__mbslen
#@ stub -version=0x601 _o__mbslen_l
#@ stub -version=0x601 _o__mbslwr
#@ stub -version=0x601 _o__mbslwr_l
#@ stub -version=0x601 _o__mbslwr_s
#@ stub -version=0x601 _o__mbslwr_s_l
#@ stub -version=0x601 _o__mbsnbcat
#@ stub -version=0x601 _o__mbsnbcat_l
#@ stub -version=0x601 _o__mbsnbcat_s
#@ stub -version=0x601 _o__mbsnbcat_s_l
#@ stub -version=0x601 _o__mbsnbcmp
#@ stub -version=0x601 _o__mbsnbcmp_l
#@ stub -version=0x601 _o__mbsnbcnt
#@ stub -version=0x601 _o__mbsnbcnt_l
#@ stub -version=0x601 _o__mbsnbcoll
#@ stub -version=0x601 _o__mbsnbcoll_l
#@ stub -version=0x601 _o__mbsnbcpy
#@ stub -version=0x601 _o__mbsnbcpy_l
#@ stub -version=0x601 _o__mbsnbcpy_s
#@ stub -version=0x601 _o__mbsnbcpy_s_l
#@ stub -version=0x601 _o__mbsnbicmp
#@ stub -version=0x601 _o__mbsnbicmp_l
#@ stub -version=0x601 _o__mbsnbicoll
#@ stub -version=0x601 _o__mbsnbicoll_l
#@ stub -version=0x601 _o__mbsnbset
#@ stub -version=0x601 _o__mbsnbset_l
#@ stub -version=0x601 _o__mbsnbset_s
#@ stub -version=0x601 _o__mbsnbset_s_l
#@ stub -version=0x601 _o__mbsncat
#@ stub -version=0x601 _o__mbsncat_l
#@ stub -version=0x601 _o__mbsncat_s
#@ stub -version=0x601 _o__mbsncat_s_l
#@ stub -version=0x601 _o__mbsnccnt
#@ stub -version=0x601 _o__mbsnccnt_l
#@ stub -version=0x601 _o__mbsncmp
#@ stub -version=0x601 _o__mbsncmp_l
#@ stub -version=0x601 _o__mbsncoll
#@ stub -version=0x601 _o__mbsncoll_l
#@ stub -version=0x601 _o__mbsncpy
#@ stub -version=0x601 _o__mbsncpy_l
#@ stub -version=0x601 _o__mbsncpy_s
#@ stub -version=0x601 _o__mbsncpy_s_l
#@ stub -version=0x601 _o__mbsnextc
#@ stub -version=0x601 _o__mbsnextc_l
#@ stub -version=0x601 _o__mbsnicmp
#@ stub -version=0x601 _o__mbsnicmp_l
#@ stub -version=0x601 _o__mbsnicoll
#@ stub -version=0x601 _o__mbsnicoll_l
#@ stub -version=0x601 _o__mbsninc
#@ stub -version=0x601 _o__mbsninc_l
#@ stub -version=0x601 _o__mbsnlen
#@ stub -version=0x601 _o__mbsnlen_l
#@ stub -version=0x601 _o__mbsnset
#@ stub -version=0x601 _o__mbsnset_l
#@ stub -version=0x601 _o__mbsnset_s
#@ stub -version=0x601 _o__mbsnset_s_l
#@ stub -version=0x601 _o__mbspbrk
#@ stub -version=0x601 _o__mbspbrk_l
#@ stub -version=0x601 _o__mbsrchr
#@ stub -version=0x601 _o__mbsrchr_l
#@ stub -version=0x601 _o__mbsrev
#@ stub -version=0x601 _o__mbsrev_l
#@ stub -version=0x601 _o__mbsset
#@ stub -version=0x601 _o__mbsset_l
#@ stub -version=0x601 _o__mbsset_s
#@ stub -version=0x601 _o__mbsset_s_l
#@ stub -version=0x601 _o__mbsspn
#@ stub -version=0x601 _o__mbsspn_l
#@ stub -version=0x601 _o__mbsspnp
#@ stub -version=0x601 _o__mbsspnp_l
#@ stub -version=0x601 _o__mbsstr
#@ stub -version=0x601 _o__mbsstr_l
#@ stub -version=0x601 _o__mbstok
#@ stub -version=0x601 _o__mbstok_l
#@ stub -version=0x601 _o__mbstok_s
#@ stub -version=0x601 _o__mbstok_s_l
#@ stub -version=0x601 _o__mbstowcs_l
#@ stub -version=0x601 _o__mbstowcs_s_l
#@ stub -version=0x601 _o__mbstrlen
#@ stub -version=0x601 _o__mbstrlen_l
#@ stub -version=0x601 _o__mbstrnlen
#@ stub -version=0x601 _o__mbstrnlen_l
#@ stub -version=0x601 _o__mbsupr
#@ stub -version=0x601 _o__mbsupr_l
#@ stub -version=0x601 _o__mbsupr_s
#@ stub -version=0x601 _o__mbsupr_s_l
#@ stub -version=0x601 _o__mbtowc_l
#@ stub -version=0x601 _o__memicmp
#@ stub -version=0x601 _o__memicmp_l
#@ stub -version=0x601 _o__mkdir
#@ stub -version=0x601 _o__mkgmtime32
#@ stub -version=0x601 _o__mkgmtime64
#@ stub -version=0x601 _o__mktemp
#@ stub -version=0x601 _o__mktemp_s
#@ stub -version=0x601 _o__mktime32
#@ stub -version=0x601 _o__mktime64
#@ stub -version=0x601 _o__msize
#@ stub -version=0x601 _o__nextafter
#@ stub -version=0x601 -arch=x86_64 _o__nextafterf
#@ stub -version=0x601 _o__open_osfhandle
#@ stub -version=0x601 _o__pclose
#@ stub -version=0x601 _o__pipe
#@ stub -version=0x601 _o__popen
#@ stub -version=0x601 _o__purecall
#@ stub -version=0x601 _o__putc_nolock
#@ stub -version=0x601 _o__putch
#@ stub -version=0x601 _o__putch_nolock
#@ stub -version=0x601 _o__putenv
#@ stub -version=0x601 _o__putenv_s
#@ stub -version=0x601 _o__putw
#@ stub -version=0x601 _o__putwc_nolock
#@ stub -version=0x601 _o__putwch
#@ stub -version=0x601 _o__putwch_nolock
#@ stub -version=0x601 _o__putws
#@ stub -version=0x601 _o__read
#@ stub -version=0x601 _o__realloc_base
#@ stub -version=0x601 _o__recalloc
#@ stub -version=0x601 _o__register_onexit_function
#@ stub -version=0x601 _o__resetstkoflw
#@ stub -version=0x601 _o__rmdir
#@ stub -version=0x601 _o__rmtmp
#@ stub -version=0x601 _o__scalb
#@ stub -version=0x601 -arch=x86_64 _o__scalbf
#@ stub -version=0x601 _o__searchenv
#@ stub -version=0x601 _o__searchenv_s
#@ stub -version=0x601 _o__seh_filter_dll
#@ stub -version=0x601 _o__seh_filter_exe
#@ stub -version=0x601 _o__set_abort_behavior
#@ stub -version=0x601 _o__set_app_type
#@ stub -version=0x601 _o__set_doserrno
#@ stub -version=0x601 _o__set_errno
#@ stub -version=0x601 _o__set_fmode
#@ stub -version=0x601 _o__set_invalid_parameter_handler
#@ stub -version=0x601 _o__set_new_handler
#@ stub -version=0x601 _o__set_new_mode
#@ stub -version=0x601 _o__set_thread_local_invalid_parameter_handler
#@ stub -version=0x601 _o__seterrormode
#@ stub -version=0x601 _o__setmbcp
#@ stub -version=0x601 _o__setmode
#@ stub -version=0x601 _o__setsystime
#@ stub -version=0x601 _o__sleep
#@ stub -version=0x601 _o__sopen
#@ stub -version=0x601 _o__sopen_dispatch
#@ stub -version=0x601 _o__sopen_s
#@ stub -version=0x601 _o__spawnv
#@ stub -version=0x601 _o__spawnve
#@ stub -version=0x601 _o__spawnvp
#@ stub -version=0x601 _o__spawnvpe
#@ stub -version=0x601 _o__splitpath
#@ stub -version=0x601 _o__splitpath_s
#@ stub -version=0x601 _o__stat32
#@ stub -version=0x601 _o__stat32i64
#@ stub -version=0x601 _o__stat64
#@ stub -version=0x601 _o__stat64i32
#@ stub -version=0x601 _o__strcoll_l
#@ stub -version=0x601 _o__strdate
#@ stub -version=0x601 _o__strdate_s
#@ stub -version=0x601 _o__strdup
#@ stub -version=0x601 _o__strerror
#@ stub -version=0x601 _o__strerror_s
#@ stub -version=0x601 _o__strftime_l
#@ stub -version=0x601 _o__stricmp
#@ stub -version=0x601 _o__stricmp_l
#@ stub -version=0x601 _o__stricoll
#@ stub -version=0x601 _o__stricoll_l
#@ stub -version=0x601 _o__strlwr
#@ stub -version=0x601 _o__strlwr_l
#@ stub -version=0x601 _o__strlwr_s
#@ stub -version=0x601 _o__strlwr_s_l
#@ stub -version=0x601 _o__strncoll
#@ stub -version=0x601 _o__strncoll_l
#@ stub -version=0x601 _o__strnicmp
#@ stub -version=0x601 _o__strnicmp_l
#@ stub -version=0x601 _o__strnicoll
#@ stub -version=0x601 _o__strnicoll_l
#@ stub -version=0x601 _o__strnset_s
#@ stub -version=0x601 _o__strset_s
#@ stub -version=0x601 _o__strtime
#@ stub -version=0x601 _o__strtime_s
#@ stub -version=0x601 _o__strtod_l
#@ stub -version=0x601 _o__strtof_l
#@ stub -version=0x601 _o__strtoi64
#@ stub -version=0x601 _o__strtoi64_l
#@ stub -version=0x601 _o__strtol_l
#@ stub -version=0x601 _o__strtold_l
#@ stub -version=0x601 _o__strtoll_l
#@ stub -version=0x601 _o__strtoui64
#@ stub -version=0x601 _o__strtoui64_l
#@ stub -version=0x601 _o__strtoul_l
#@ stub -version=0x601 _o__strtoull_l
#@ stub -version=0x601 _o__strupr
#@ stub -version=0x601 _o__strupr_l
#@ stub -version=0x601 _o__strupr_s
#@ stub -version=0x601 _o__strupr_s_l
#@ stub -version=0x601 _o__strxfrm_l
#@ stub -version=0x601 _o__swab
#@ stub -version=0x601 _o__tell
#@ stub -version=0x601 _o__telli64
#@ stub -version=0x601 _o__timespec32_get
#@ stub -version=0x601 _o__timespec64_get
#@ stub -version=0x601 _o__tolower
#@ stub -version=0x601 _o__tolower_l
#@ stub -version=0x601 _o__toupper
#@ stub -version=0x601 _o__toupper_l
#@ stub -version=0x601 _o__towlower_l
#@ stub -version=0x601 _o__towupper_l
#@ stub -version=0x601 _o__tzset
#@ stub -version=0x601 _o__ui64toa
#@ stub -version=0x601 _o__ui64toa_s
#@ stub -version=0x601 _o__ui64tow
#@ stub -version=0x601 _o__ui64tow_s
#@ stub -version=0x601 _o__ultoa
#@ stub -version=0x601 _o__ultoa_s
#@ stub -version=0x601 _o__ultow
#@ stub -version=0x601 _o__ultow_s
#@ stub -version=0x601 _o__umask
#@ stub -version=0x601 _o__umask_s
#@ stub -version=0x601 _o__ungetc_nolock
#@ stub -version=0x601 _o__ungetch
#@ stub -version=0x601 _o__ungetch_nolock
#@ stub -version=0x601 _o__ungetwc_nolock
#@ stub -version=0x601 _o__ungetwch
#@ stub -version=0x601 _o__ungetwch_nolock
#@ stub -version=0x601 _o__unlink
#@ stub -version=0x601 _o__unloaddll
#@ stub -version=0x601 _o__unlock_file
#@ stub -version=0x601 _o__utime32
#@ stub -version=0x601 _o__utime64
#@ stub -version=0x601 _o__waccess
#@ stub -version=0x601 _o__waccess_s
#@ stub -version=0x601 _o__wasctime
#@ stub -version=0x601 _o__wasctime_s
#@ stub -version=0x601 _o__wchdir
#@ stub -version=0x601 _o__wchmod
#@ stub -version=0x601 _o__wcreat
#@ stub -version=0x601 _o__wcreate_locale
#@ stub -version=0x601 _o__wcscoll_l
#@ stub -version=0x601 _o__wcsdup
#@ stub -version=0x601 _o__wcserror
#@ stub -version=0x601 _o__wcserror_s
#@ stub -version=0x601 _o__wcsftime_l
#@ stub -version=0x601 _o__wcsicmp
#@ stub -version=0x601 _o__wcsicmp_l
#@ stub -version=0x601 _o__wcsicoll
#@ stub -version=0x601 _o__wcsicoll_l
#@ stub -version=0x601 _o__wcslwr
#@ stub -version=0x601 _o__wcslwr_l
#@ stub -version=0x601 _o__wcslwr_s
#@ stub -version=0x601 _o__wcslwr_s_l
#@ stub -version=0x601 _o__wcsncoll
#@ stub -version=0x601 _o__wcsncoll_l
#@ stub -version=0x601 _o__wcsnicmp
#@ stub -version=0x601 _o__wcsnicmp_l
#@ stub -version=0x601 _o__wcsnicoll
#@ stub -version=0x601 _o__wcsnicoll_l
#@ stub -version=0x601 _o__wcsnset
#@ stub -version=0x601 _o__wcsnset_s
#@ stub -version=0x601 _o__wcsset
#@ stub -version=0x601 _o__wcsset_s
#@ stub -version=0x601 _o__wcstod_l
#@ stub -version=0x601 _o__wcstof_l
#@ stub -version=0x601 _o__wcstoi64
#@ stub -version=0x601 _o__wcstoi64_l
#@ stub -version=0x601 _o__wcstol_l
#@ stub -version=0x601 _o__wcstold_l
#@ stub -version=0x601 _o__wcstoll_l
#@ stub -version=0x601 _o__wcstombs_l
#@ stub -version=0x601 _o__wcstombs_s_l
#@ stub -version=0x601 _o__wcstoui64
#@ stub -version=0x601 _o__wcstoui64_l
#@ stub -version=0x601 _o__wcstoul_l
#@ stub -version=0x601 _o__wcstoull_l
#@ stub -version=0x601 _o__wcsupr
#@ stub -version=0x601 _o__wcsupr_l
#@ stub -version=0x601 _o__wcsupr_s
#@ stub -version=0x601 _o__wcsupr_s_l
#@ stub -version=0x601 _o__wcsxfrm_l
#@ stub -version=0x601 _o__wctime32
#@ stub -version=0x601 _o__wctime32_s
#@ stub -version=0x601 _o__wctime64
#@ stub -version=0x601 _o__wctime64_s
#@ stub -version=0x601 _o__wctomb_l
#@ stub -version=0x601 _o__wctomb_s_l
#@ stub -version=0x601 _o__wdupenv_s
#@ stub -version=0x601 _o__wexecv
#@ stub -version=0x601 _o__wexecve
#@ stub -version=0x601 _o__wexecvp
#@ stub -version=0x601 _o__wexecvpe
#@ stub -version=0x601 _o__wfdopen
#@ stub -version=0x601 _o__wfindfirst32
#@ stub -version=0x601 _o__wfindfirst32i64
#@ stub -version=0x601 _o__wfindfirst64
#@ stub -version=0x601 _o__wfindfirst64i32
#@ stub -version=0x601 _o__wfindnext32
#@ stub -version=0x601 _o__wfindnext32i64
#@ stub -version=0x601 _o__wfindnext64
#@ stub -version=0x601 _o__wfindnext64i32
#@ stub -version=0x601 _o__wfopen
#@ stub -version=0x601 _o__wfopen_s
#@ stub -version=0x601 _o__wfreopen
#@ stub -version=0x601 _o__wfreopen_s
#@ stub -version=0x601 _o__wfsopen
#@ stub -version=0x601 _o__wfullpath
#@ stub -version=0x601 _o__wgetcwd
#@ stub -version=0x601 _o__wgetdcwd
#@ stub -version=0x601 _o__wgetenv
#@ stub -version=0x601 _o__wgetenv_s
#@ stub -version=0x601 _o__wmakepath
#@ stub -version=0x601 _o__wmakepath_s
#@ stub -version=0x601 _o__wmkdir
#@ stub -version=0x601 _o__wmktemp
#@ stub -version=0x601 _o__wmktemp_s
#@ stub -version=0x601 _o__wperror
#@ stub -version=0x601 _o__wpopen
#@ stub -version=0x601 _o__wputenv
#@ stub -version=0x601 _o__wputenv_s
#@ stub -version=0x601 _o__wremove
#@ stub -version=0x601 _o__wrename
#@ stub -version=0x601 _o__write
#@ stub -version=0x601 _o__wrmdir
#@ stub -version=0x601 _o__wsearchenv
#@ stub -version=0x601 _o__wsearchenv_s
#@ stub -version=0x601 _o__wsetlocale
#@ stub -version=0x601 _o__wsopen_dispatch
#@ stub -version=0x601 _o__wsopen_s
#@ stub -version=0x601 _o__wspawnv
#@ stub -version=0x601 _o__wspawnve
#@ stub -version=0x601 _o__wspawnvp
#@ stub -version=0x601 _o__wspawnvpe
#@ stub -version=0x601 _o__wsplitpath
#@ stub -version=0x601 _o__wsplitpath_s
#@ stub -version=0x601 _o__wstat32
#@ stub -version=0x601 _o__wstat32i64
#@ stub -version=0x601 _o__wstat64
#@ stub -version=0x601 _o__wstat64i32
#@ stub -version=0x601 _o__wstrdate
#@ stub -version=0x601 _o__wstrdate_s
#@ stub -version=0x601 _o__wstrtime
#@ stub -version=0x601 _o__wstrtime_s
#@ stub -version=0x601 _o__wsystem
#@ stub -version=0x601 _o__wtmpnam_s
#@ stub -version=0x601 _o__wtof
#@ stub -version=0x601 _o__wtof_l
#@ stub -version=0x601 _o__wtoi
#@ stub -version=0x601 _o__wtoi64
#@ stub -version=0x601 _o__wtoi64_l
#@ stub -version=0x601 _o__wtoi_l
#@ stub -version=0x601 _o__wtol
#@ stub -version=0x601 _o__wtol_l
#@ stub -version=0x601 _o__wtoll
#@ stub -version=0x601 _o__wtoll_l
#@ stub -version=0x601 _o__wunlink
#@ stub -version=0x601 _o__wutime32
#@ stub -version=0x601 _o__wutime64
#@ stub -version=0x601 _o__y0
#@ stub -version=0x601 _o__y1
#@ stub -version=0x601 _o__yn
#@ stub -version=0x601 _o_abort
#@ stub -version=0x601 _o_acos
#@ stub -version=0x601 -arch=x86_64 _o_acosf
#@ stub -version=0x601 _o_acosh
#@ stub -version=0x601 _o_acoshf
#@ stub -version=0x601 _o_acoshl
#@ stub -version=0x601 _o_asctime
#@ stub -version=0x601 _o_asctime_s
#@ stub -version=0x601 _o_asin
#@ stub -version=0x601 -arch=x86_64 _o_asinf
#@ stub -version=0x601 _o_asinh
#@ stub -version=0x601 _o_asinhf
#@ stub -version=0x601 _o_asinhl
#@ stub -version=0x601 _o_atan
#@ stub -version=0x601 _o_atan2
#@ stub -version=0x601 -arch=x86_64 _o_atan2f
#@ stub -version=0x601 -arch=x86_64 _o_atanf
#@ stub -version=0x601 _o_atanh
#@ stub -version=0x601 _o_atanhf
#@ stub -version=0x601 _o_atanhl
#@ stub -version=0x601 _o_atof
#@ stub -version=0x601 _o_atoi
#@ stub -version=0x601 _o_atol
#@ stub -version=0x601 _o_atoll
#@ stub -version=0x601 _o_bsearch
#@ stub -version=0x601 _o_bsearch_s
#@ stub -version=0x601 _o_btowc
#@ stub -version=0x601 _o_calloc
#@ stub -version=0x601 _o_cbrt
#@ stub -version=0x601 _o_cbrtf
#@ stub -version=0x601 _o_ceil
#@ stub -version=0x601 -arch=x86_64 _o_ceilf
#@ stub -version=0x601 _o_clearerr
#@ stub -version=0x601 _o_clearerr_s
#@ stub -version=0x601 _o_cos
#@ stub -version=0x601 -arch=x86_64 _o_cosf
#@ stub -version=0x601 _o_cosh
#@ stub -version=0x601 -arch=x86_64 _o_coshf
#@ stub -version=0x601 _o_erf
#@ stub -version=0x601 _o_erfc
#@ stub -version=0x601 _o_erfcf
#@ stub -version=0x601 _o_erfcl
#@ stub -version=0x601 _o_erff
#@ stub -version=0x601 _o_erfl
#@ stub -version=0x601 _o_exit
#@ stub -version=0x601 _o_exp
#@ stub -version=0x601 _o_exp2
#@ stub -version=0x601 _o_exp2f
#@ stub -version=0x601 _o_exp2l
#@ stub -version=0x601 -arch=x86_64 _o_expf
#@ stub -version=0x601 _o_fabs
#@ stub -version=0x601 _o_fclose
#@ stub -version=0x601 _o_feof
#@ stub -version=0x601 _o_ferror
#@ stub -version=0x601 _o_fflush
#@ stub -version=0x601 _o_fgetc
#@ stub -version=0x601 _o_fgetpos
#@ stub -version=0x601 _o_fgets
#@ stub -version=0x601 _o_fgetwc
#@ stub -version=0x601 _o_fgetws
#@ stub -version=0x601 _o_floor
#@ stub -version=0x601 -arch=x86_64 _o_floorf
#@ stub -version=0x601 _o_fma
#@ stub -version=0x601 _o_fmaf
#@ stub -version=0x601 _o_fmal
#@ stub -version=0x601 _o_fmod
#@ stub -version=0x601 -arch=x86_64 _o_fmodf
#@ stub -version=0x601 _o_fopen
#@ stub -version=0x601 _o_fopen_s
#@ stub -version=0x601 _o_fputc
#@ stub -version=0x601 _o_fputs
#@ stub -version=0x601 _o_fputwc
#@ stub -version=0x601 _o_fputws
#@ stub -version=0x601 _o_fread
#@ stub -version=0x601 _o_fread_s
#@ stub -version=0x601 _o_free
#@ stub -version=0x601 _o_freopen
#@ stub -version=0x601 _o_freopen_s
#@ stub -version=0x601 _o_frexp
#@ stub -version=0x601 _o_fseek
#@ stub -version=0x601 _o_fsetpos
#@ stub -version=0x601 _o_ftell
#@ stub -version=0x601 _o_fwrite
#@ stub -version=0x601 _o_getc
#@ stub -version=0x601 _o_getchar
#@ stub -version=0x601 _o_getenv
#@ stub -version=0x601 _o_getenv_s
#@ stub -version=0x601 _o_gets
#@ stub -version=0x601 _o_gets_s
#@ stub -version=0x601 _o_getwc
#@ stub -version=0x601 _o_getwchar
#@ stub -version=0x601 _o_hypot
#@ stub -version=0x601 _o_is_wctype
#@ stub -version=0x601 _o_isalnum
#@ stub -version=0x601 _o_isalpha
#@ stub -version=0x601 _o_isblank
#@ stub -version=0x601 _o_iscntrl
#@ stub -version=0x601 _o_isdigit
#@ stub -version=0x601 _o_isgraph
#@ stub -version=0x601 _o_isleadbyte
#@ stub -version=0x601 _o_islower
#@ stub -version=0x601 _o_isprint
#@ stub -version=0x601 _o_ispunct
#@ stub -version=0x601 _o_isspace
#@ stub -version=0x601 _o_isupper
#@ stub -version=0x601 _o_iswalnum
#@ stub -version=0x601 _o_iswalpha
#@ stub -version=0x601 _o_iswascii
#@ stub -version=0x601 _o_iswblank
#@ stub -version=0x601 _o_iswcntrl
#@ stub -version=0x601 _o_iswctype
#@ stub -version=0x601 _o_iswdigit
#@ stub -version=0x601 _o_iswgraph
#@ stub -version=0x601 _o_iswlower
#@ stub -version=0x601 _o_iswprint
#@ stub -version=0x601 _o_iswpunct
#@ stub -version=0x601 _o_iswspace
#@ stub -version=0x601 _o_iswupper
#@ stub -version=0x601 _o_iswxdigit
#@ stub -version=0x601 _o_isxdigit
#@ stub -version=0x601 _o_ldexp
#@ stub -version=0x601 _o_lgamma
#@ stub -version=0x601 _o_lgammaf
#@ stub -version=0x601 _o_lgammal
#@ stub -version=0x601 _o_llrint
#@ stub -version=0x601 _o_llrintf
#@ stub -version=0x601 _o_llrintl
#@ stub -version=0x601 _o_llround
#@ stub -version=0x601 _o_llroundf
#@ stub -version=0x601 _o_llroundl
#@ stub -version=0x601 _o_localeconv
#@ stub -version=0x601 _o_log
#@ stub -version=0x601 _o_log10
#@ stub -version=0x601 -arch=x86_64 _o_log10f
#@ stub -version=0x601 _o_log1p
#@ stub -version=0x601 _o_log1pf
#@ stub -version=0x601 _o_log1pl
#@ stub -version=0x601 _o_log2
#@ stub -version=0x601 _o_log2f
#@ stub -version=0x601 _o_log2l
#@ stub -version=0x601 _o_logb
#@ stub -version=0x601 _o_logbf
#@ stub -version=0x601 _o_logbl
#@ stub -version=0x601 -arch=x86_64 _o_logf
#@ stub -version=0x601 _o_lrint
#@ stub -version=0x601 _o_lrintf
#@ stub -version=0x601 _o_lrintl
#@ stub -version=0x601 _o_lround
#@ stub -version=0x601 _o_lroundf
#@ stub -version=0x601 _o_lroundl
#@ stub -version=0x601 _o_malloc
#@ stub -version=0x601 _o_mblen
#@ stub -version=0x601 _o_mbrlen
#@ stub -version=0x601 _o_mbrtoc16
#@ stub -version=0x601 _o_mbrtoc32
#@ stub -version=0x601 _o_mbrtowc
#@ stub -version=0x601 _o_mbsrtowcs
#@ stub -version=0x601 _o_mbsrtowcs_s
#@ stub -version=0x601 _o_mbstowcs
#@ stub -version=0x601 _o_mbstowcs_s
#@ stub -version=0x601 _o_mbtowc
#@ stub -version=0x601 _o_memcpy_s
#@ stub -version=0x601 _o_memset
#@ stub -version=0x601 _o_modf
#@ stub -version=0x601 -arch=x86_64 _o_modff
#@ stub -version=0x601 _o_nan
#@ stub -version=0x601 _o_nanf
#@ stub -version=0x601 _o_nanl
#@ stub -version=0x601 _o_nearbyint
#@ stub -version=0x601 _o_nearbyintf
#@ stub -version=0x601 _o_nearbyintl
#@ stub -version=0x601 _o_nextafter
#@ stub -version=0x601 _o_nextafterf
#@ stub -version=0x601 _o_nextafterl
#@ stub -version=0x601 _o_nexttoward
#@ stub -version=0x601 _o_nexttowardf
#@ stub -version=0x601 _o_nexttowardl
#@ stub -version=0x601 _o_pow
#@ stub -version=0x601 _o_powf
#@ stub -version=0x601 _o_putc
#@ stub -version=0x601 _o_putchar
#@ stub -version=0x601 _o_puts
#@ stub -version=0x601 _o_putwc
#@ stub -version=0x601 _o_putwchar
#@ stub -version=0x601 _o_qsort
#@ stub -version=0x601 _o_qsort_s
#@ stub -version=0x601 _o_raise
#@ stub -version=0x601 _o_rand
#@ stub -version=0x601 _o_rand_s
#@ stub -version=0x601 _o_realloc
#@ stub -version=0x601 _o_remainder
#@ stub -version=0x601 _o_remainderf
#@ stub -version=0x601 _o_remainderl
#@ stub -version=0x601 _o_remove
#@ stub -version=0x601 _o_remquo
#@ stub -version=0x601 _o_remquof
#@ stub -version=0x601 _o_remquol
#@ stub -version=0x601 _o_rename
#@ stub -version=0x601 _o_rewind
#@ stub -version=0x601 _o_rint
#@ stub -version=0x601 _o_rintf
#@ stub -version=0x601 _o_rintl
#@ stub -version=0x601 _o_round
#@ stub -version=0x601 _o_roundf
#@ stub -version=0x601 _o_roundl
#@ stub -version=0x601 _o_scalbln
#@ stub -version=0x601 _o_scalblnf
#@ stub -version=0x601 _o_scalblnl
#@ stub -version=0x601 _o_scalbn
#@ stub -version=0x601 _o_scalbnf
#@ stub -version=0x601 _o_scalbnl
#@ stub -version=0x601 _o_set_terminate
#@ stub -version=0x601 _o_setbuf
#@ stub -version=0x601 _o_setlocale
#@ stub -version=0x601 _o_setvbuf
#@ stub -version=0x601 _o_sin
#@ stub -version=0x601 -arch=x86_64 _o_sinf
#@ stub -version=0x601 _o_sinh
#@ stub -version=0x601 -arch=x86_64 _o_sinhf
#@ stub -version=0x601 _o_sqrt
#@ stub -version=0x601 -arch=x86_64 _o_sqrtf
#@ stub -version=0x601 _o_srand
#@ stub -version=0x601 _o_strcat_s
#@ stub -version=0x601 _o_strcoll
#@ stub -version=0x601 _o_strcpy_s
#@ stub -version=0x601 _o_strerror
#@ stub -version=0x601 _o_strerror_s
#@ stub -version=0x601 _o_strftime
#@ stub -version=0x601 _o_strncat_s
#@ stub -version=0x601 _o_strncpy_s
#@ stub -version=0x601 _o_strtod
#@ stub -version=0x601 _o_strtof
#@ stub -version=0x601 _o_strtok
#@ stub -version=0x601 _o_strtok_s
#@ stub -version=0x601 _o_strtol
#@ stub -version=0x601 _o_strtold
#@ stub -version=0x601 _o_strtoll
#@ stub -version=0x601 _o_strtoul
#@ stub -version=0x601 _o_strtoull
#@ stub -version=0x601 _o_system
#@ stub -version=0x601 _o_tan
#@ stub -version=0x601 -arch=x86_64 _o_tanf
#@ stub -version=0x601 _o_tanh
#@ stub -version=0x601 -arch=x86_64 _o_tanhf
#@ stub -version=0x601 _o_terminate
#@ stub -version=0x601 _o_tgamma
#@ stub -version=0x601 _o_tgammaf
#@ stub -version=0x601 _o_tgammal
#@ stub -version=0x601 _o_tmpfile_s
#@ stub -version=0x601 _o_tmpnam_s
#@ stub -version=0x601 _o_tolower
#@ stub -version=0x601 _o_toupper
#@ stub -version=0x601 _o_towlower
#@ stub -version=0x601 _o_towupper
#@ stub -version=0x601 _o_ungetc
#@ stub -version=0x601 _o_ungetwc
#@ stub -version=0x601 _o_wcrtomb
#@ stub -version=0x601 _o_wcrtomb_s
#@ stub -version=0x601 _o_wcscat_s
#@ stub -version=0x601 _o_wcscoll
#@ stub -version=0x601 _o_wcscpy
#@ stub -version=0x601 _o_wcscpy_s
#@ stub -version=0x601 _o_wcsftime
#@ stub -version=0x601 _o_wcsncat_s
#@ stub -version=0x601 _o_wcsncpy_s
#@ stub -version=0x601 _o_wcsrtombs
#@ stub -version=0x601 _o_wcsrtombs_s
#@ stub -version=0x601 _o_wcstod
#@ stub -version=0x601 _o_wcstof
#@ stub -version=0x601 _o_wcstok
#@ stub -version=0x601 _o_wcstok_s
#@ stub -version=0x601 _o_wcstol
#@ stub -version=0x601 _o_wcstold
#@ stub -version=0x601 _o_wcstoll
#@ stub -version=0x601 _o_wcstombs
#@ stub -version=0x601 _o_wcstombs_s
#@ stub -version=0x601 _o_wcstoul
#@ stub -version=0x601 _o_wcstoull
#@ stub -version=0x601 _o_wctob
#@ stub -version=0x601 _o_wctomb
#@ stub -version=0x601 _o_wctomb_s
#@ stub -version=0x601 _o_wmemcpy_s
#@ stub -version=0x601 _o_wmemmove_s
@ varargs _open(str long)
@ cdecl _open_osfhandle(long long)
@ cdecl _pclose(ptr)
@ cdecl _pipe(ptr long long)
@ cdecl _popen(str str)
@ cdecl _purecall()
#@ stub -version=0x601 _putc_nolock
@ cdecl _putch(long)
#@ stub -version=0x601 _putch_nolock
@ cdecl _putenv(str)
#@ stub -version=0x601 _putenv_s
@ cdecl _putw(long ptr)
#@ stub -version=0x601 _putwc_nolock
@ cdecl _putwch(long)
#@ stub -version=0x601 _putwch_nolock
@ cdecl _putws(wstr)
#@ stub -version=0x601 _query_app_type
#@ stub -version=0x601 _query_new_handler
#@ stub -version=0x601 _query_new_mode
@ cdecl _read(long ptr long)
#@ stub -version=0x601 _realloc_base
#@ stub -version=0x601 _recalloc
#@ stub -version=0x601 _register_onexit_function
#@ stub -version=0x601 _register_thread_local_exe_atexit_callback
@ cdecl _resetstkoflw()
@ cdecl _rmdir(str)
@ cdecl _rmtmp()
@ cdecl _rotl(long long)
# stub _rotl64
@ cdecl _rotr(long long)
# stub _rotr64
@ cdecl _scalb(double long)
#@ stub -version=0x601 -arch=x86_64 _scalbf
@ cdecl _searchenv(str str ptr)
#@ stub -version=0x601 _searchenv_s
#@ stub -version=0x601 _seh_filter_dll
#@ stub -version=0x601 _seh_filter_exe
#@ stub -version=0x601 -arch=i386 _seh_longjmp_unwind4
@ stdcall -i386 _seh_longjmp_unwind(ptr)
#@ stub -version=0x601 -arch=x86_64 _set_FMA3_enable
#@ stub -version=0x601 -arch=i386 _set_SSE2_enable
#@ stub -version=0x601 _set_abort_behavior
#@ stub -version=0x601 _set_app_type
#@ stub -version=0x601 _set_controlfp
#@ stub -version=0x601 _set_doserrno
#@ stub -version=0x601 _set_errno
@ cdecl _set_error_mode(long)
#@ stub -version=0x601 _set_fmode
#@ stub -version=0x601 _set_invalid_parameter_handler
#@ stub -version=0x601 _set_new_handler
#@ stub -version=0x601 _set_new_mode
#@ stub -version=0x601 _set_printf_count_output
#@ stub -version=0x601 _set_purecall_handler
#@ stub -version=0x601 _set_se_translator
#@ stub -version=0x601 _set_thread_local_invalid_parameter_handler
@ cdecl _seterrormode(long)
@ cdecl -arch=i386 -norelay _setjmp3(ptr long)
@ cdecl _setmaxstdio(long)
@ cdecl _setmbcp(long)
@ cdecl _setmode(long long)
@ cdecl _setsystime(ptr long)
@ cdecl _sleep(long)
@ varargs _sopen(str long long)
#@ stub -version=0x601 _sopen_dispatch
#@ stub -version=0x601 _sopen_s
@ varargs _spawnl(long str str)
@ varargs _spawnle(long str str)
@ varargs _spawnlp(long str str)
@ varargs _spawnlpe(long str str)
@ cdecl _spawnv(long str ptr)
@ cdecl _spawnve(long str ptr ptr)
@ cdecl _spawnvp(long str ptr)
@ cdecl _spawnvpe(long str ptr ptr)
@ cdecl _splitpath(str ptr ptr ptr ptr)
#@ stub -version=0x601 _splitpath_s
#@ stub -version=0x601 _stat32
#@ stub -version=0x601 _stat32i64
@ cdecl _stat64(str ptr)
#@ stub -version=0x601 _stat64i32
@ cdecl _statusfp()
#@ stub -version=0x601 -arch=i386 _statusfp2
#@ stub -version=0x601 _strcoll_l
@ cdecl _strdate(ptr)
#@ stub -version=0x601 _strdate_s
@ cdecl _strdup(str)
@ cdecl _strerror(long)
#@ stub -version=0x601 _strerror_s
#@ stub -version=0x601 _strftime_l
@ cdecl _stricmp(str str)
#@ stub -version=0x601 _stricmp_l
@ cdecl _stricoll(str str)
#@ stub -version=0x601 _stricoll_l
@ cdecl _strlwr(str)
#@ stub -version=0x601 _strlwr_l
#@ stub -version=0x601 _strlwr_s
#@ stub -version=0x601 _strlwr_s_l
@ cdecl _strncoll(str str long)
#@ stub -version=0x601 _strncoll_l
@ cdecl _strnicmp(str str long)
#@ stub -version=0x601 _strnicmp_l
@ cdecl _strnicoll(str str long)
#@ stub -version=0x601 _strnicoll_l
@ cdecl _strnset(str long long)
#@ stub -version=0x601 _strnset_s
@ cdecl _strrev(str)
@ cdecl _strset(str long)
#@ stub -version=0x601 _strset_s
@ cdecl _strtime(ptr)
#@ stub -version=0x601 _strtime_s
#@ stub -version=0x601 _strtod_l
#@ stub -version=0x601 _strtof_l
@ cdecl _strtoi64(str ptr long)
#@ stub -version=0x601 _strtoi64_l
#@ stub -version=0x601 _strtoimax_l
#@ stub -version=0x601 _strtol_l
#@ stub -version=0x601 _strtold_l
#@ stub -version=0x601 _strtoll_l
@ cdecl _strtoui64(str ptr long) strtoull
#@ stub -version=0x601 _strtoui64_l
#@ stub -version=0x601 _strtoul_l
#@ stub -version=0x601 _strtoull_l
#@ stub -version=0x601 _strtoumax_l
@ cdecl _strupr(str)
#@ stub -version=0x601 _strupr_l
#@ stub -version=0x601 _strupr_s
#@ stub -version=0x601 _strupr_s_l
#@ stub -version=0x601 _strxfrm_l
@ cdecl _swab(str str long)
@ cdecl _tell(long)
@ cdecl -ret64 _telli64(long)
@ cdecl _tempnam(str str)
#@ stub -version=0x601 _time32
@ cdecl _time64(ptr)
#@ stub -version=0x601 _timespec32_get
#@ stub -version=0x601 _timespec64_get
@ cdecl _tolower(long)
#@ stub -version=0x601 _tolower_l
@ cdecl _toupper(long)
#@ stub -version=0x601 _toupper_l
#@ stub -version=0x601 _towlower_l
#@ stub -version=0x601 _towupper_l
@ cdecl _tzset()
@ cdecl _ui64toa(long long ptr long)
#@ stub -version=0x601 _ui64toa_s
@ cdecl _ui64tow(long long ptr long)
#@ stub -version=0x601 _ui64tow_s
@ cdecl _ultoa(long ptr long)
#@ stub -version=0x601 _ultoa_s
@ cdecl _ultow(long ptr long)
#@ stub -version=0x601 _ultow_s
@ cdecl _umask(long)
#@ stub -version=0x601 _umask_s
#@ stub -version=0x601 _ungetc_nolock
@ cdecl _ungetch(long)
#@ stub -version=0x601 _ungetch_nolock
#@ stub -version=0x601 _ungetwc_nolock
# stub _ungetwch
#@ stub -version=0x601 _ungetwch_nolock
@ cdecl _unlink(str)
@ cdecl _unloaddll(long)
#@ stub -version=0x601 _unlock_file
#@ stub -version=0x601 _unlock_locales
#@ stub -version=0x601 _utime32
@ cdecl _utime64(str ptr)
@ cdecl _waccess(wstr long)
#@ stub -version=0x601 _waccess_s
@ cdecl _wasctime(ptr)
#@ stub -version=0x601 _wasctime_s
#@ stub -version=0x601 _wassert
@ cdecl _wchdir(wstr)
@ cdecl _wchmod(wstr long)
@ cdecl _wcreat(wstr long)
#@ stub -version=0x601 _wcreate_locale
#@ stub -version=0x601 _wcscoll_l
@ cdecl _wcsdup(wstr)
@ cdecl _wcserror(long)
#@ stub -version=0x601 _wcserror_s
#@ stub -version=0x601 _wcsftime_l
@ cdecl _wcsicmp(wstr wstr)
#@ stub -version=0x601 _wcsicmp_l
@ cdecl _wcsicoll(wstr wstr)
#@ stub -version=0x601 _wcsicoll_l
@ cdecl _wcslwr(wstr)
#@ stub -version=0x601 _wcslwr_l
#@ stub -version=0x601 _wcslwr_s
#@ stub -version=0x601 _wcslwr_s_l
@ cdecl _wcsncoll(wstr wstr long)
#@ stub -version=0x601 _wcsncoll_l
@ cdecl _wcsnicmp(wstr wstr long)
#@ stub -version=0x601 _wcsnicmp_l
@ cdecl _wcsnicoll(wstr wstr long)
#@ stub -version=0x601 _wcsnicoll_l
@ cdecl _wcsnset(wstr long long)
#@ stub -version=0x601 _wcsnset_s
@ cdecl _wcsrev(wstr)
@ cdecl _wcsset(wstr long)
#@ stub -version=0x601 _wcsset_s
#@ stub -version=0x601 _wcstod_l
#@ stub -version=0x601 _wcstof_l
@ cdecl _wcstoi64(wstr ptr long)
#@ stub -version=0x601 _wcstoi64_l
#@ stub -version=0x601 _wcstoimax_l
#@ stub -version=0x601 _wcstol_l
#@ stub -version=0x601 _wcstold_l
#@ stub -version=0x601 _wcstoll_l
#@ stub -version=0x601 _wcstombs_l
#@ stub -version=0x601 _wcstombs_s_l
@ cdecl _wcstoui64(wstr ptr long)
#@ stub -version=0x601 _wcstoui64_l
#@ stub -version=0x601 _wcstoul_l
#@ stub -version=0x601 _wcstoull_l
#@ stub -version=0x601 _wcstoumax_l
@ cdecl _wcsupr(wstr)
#@ stub -version=0x601 _wcsupr_l
#@ stub -version=0x601 _wcsupr_s
#@ stub -version=0x601 _wcsupr_s_l
#@ stub -version=0x601 _wcsxfrm_l
#@ stub -version=0x601 _wctime32
#@ stub -version=0x601 _wctime32_s
@ cdecl _wctime64(ptr)
#@ stub -version=0x601 _wctime64_s
#@ stub -version=0x601 _wctomb_l
#@ stub -version=0x601 _wctomb_s_l
# stub _wctype
#@ stub -version=0x601 _wdupenv_s
@ varargs _wexecl(wstr wstr)
@ varargs _wexecle(wstr wstr)
@ varargs _wexeclp(wstr wstr)
@ varargs _wexeclpe(wstr wstr)
@ cdecl _wexecv(wstr ptr)
@ cdecl _wexecve(wstr ptr ptr)
@ cdecl _wexecvp(wstr ptr)
@ cdecl _wexecvpe(wstr ptr ptr)
@ cdecl _wfdopen(long wstr)
#@ stub -version=0x601 _wfindfirst32
#@ stub -version=0x601 _wfindfirst32i64
# stub _wfindfirst64
#@ stub -version=0x601 _wfindfirst64i32
#@ stub -version=0x601 _wfindnext32
#@ stub -version=0x601 _wfindnext32i64
# stub _wfindnext64
#@ stub -version=0x601 _wfindnext64i32
@ cdecl _wfopen(wstr wstr)
#@ stub -version=0x601 _wfopen_s
@ cdecl _wfreopen(wstr wstr ptr)
#@ stub -version=0x601 _wfreopen_s
@ cdecl _wfsopen(wstr wstr long)
@ cdecl _wfullpath(ptr wstr long)
@ cdecl _wgetcwd(wstr long)
@ cdecl _wgetdcwd(long wstr long)
@ cdecl _wgetenv(wstr)
#@ stub -version=0x601 _wgetenv_s
@ cdecl _wmakepath(ptr wstr wstr wstr wstr)
#@ stub -version=0x601 _wmakepath_s
@ cdecl _wmkdir(wstr)
@ cdecl _wmktemp(wstr)
#@ stub -version=0x601 _wmktemp_s
@ varargs _wopen(wstr long)
@ cdecl _wperror(wstr)
@ cdecl _wpopen(wstr wstr)
@ cdecl _wputenv(wstr)
#@ stub -version=0x601 _wputenv_s
@ cdecl _wremove(wstr)
@ cdecl _wrename(wstr wstr)
@ cdecl _write(long ptr long)
@ cdecl _wrmdir(wstr)
@ cdecl _wsearchenv(wstr wstr ptr)
#@ stub -version=0x601 _wsearchenv_s
@ cdecl _wsetlocale(long wstr)
@ varargs _wsopen(wstr long long)
#@ stub -version=0x601 _wsopen_dispatch
#@ stub -version=0x601 _wsopen_s
@ varargs _wspawnl(long wstr wstr)
@ varargs _wspawnle(long wstr wstr)
@ varargs _wspawnlp(long wstr wstr)
@ varargs _wspawnlpe(long wstr wstr)
@ cdecl _wspawnv(long wstr ptr)
@ cdecl _wspawnve(long wstr ptr ptr)
@ cdecl _wspawnvp(long wstr ptr)
@ cdecl _wspawnvpe(long wstr ptr ptr)
@ cdecl _wsplitpath(wstr ptr ptr ptr ptr)
#@ stub -version=0x601 _wsplitpath_s
#@ stub -version=0x601 _wstat32
#@ stub -version=0x601 _wstat32i64
@ cdecl _wstat64(wstr ptr)
#@ stub -version=0x601 _wstat64i32
@ cdecl _wstrdate(ptr)
#@ stub -version=0x601 _wstrdate_s
@ cdecl _wstrtime(ptr)
#@ stub -version=0x601 _wstrtime_s
@ cdecl _wsystem(wstr)
@ cdecl _wtempnam(wstr wstr)
@ cdecl _wtmpnam(ptr)
#@ stub -version=0x601 _wtmpnam_s
@ cdecl _wtof(wstr)
#@ stub -version=0x601 _wtof_l
@ cdecl _wtoi(wstr)
@ cdecl _wtoi64(wstr)
#@ stub -version=0x601 _wtoi64_l
#@ stub -version=0x601 _wtoi_l
@ cdecl _wtol(wstr)
#@ stub -version=0x601 _wtol_l
#@ stub -version=0x601 _wtoll
#@ stub -version=0x601 _wtoll_l
@ cdecl _wunlink(wstr)
#@ stub -version=0x601 _wutime32
@ cdecl _wutime64(wstr ptr)
@ cdecl _y0(double)
@ cdecl _y1(double)
@ cdecl _yn(long double )
@ cdecl abort()
@ cdecl abs(long)
@ cdecl acos(double)
@ cdecl -arch=x86_64,arm acosf(long)
#@ stub -version=0x601 acosh
#@ stub -version=0x601 acoshf
#@ stub -version=0x601 acoshl
@ cdecl asctime(ptr)
#@ stub -version=0x601 asctime_s
@ cdecl asin(double)
@ cdecl -arch=x86_64,arm asinf(long)
#@ stub -version=0x601 asinh
#@ stub -version=0x601 asinhf
#@ stub -version=0x601 asinhl
@ cdecl atan(double)
@ cdecl atan2(double double)
@ cdecl -arch=x86_64,arm atan2f(long)
@ cdecl -arch=x86_64,arm atanf(long)
#@ stub -version=0x601 atanh
#@ stub -version=0x601 atanhf
#@ stub -version=0x601 atanhl
@ cdecl atof(str)
@ cdecl atoi(str)
@ cdecl atol(str)
#@ stub -version=0x601 atoll
@ cdecl bsearch(ptr ptr long long ptr)
#@ stub -version=0x601 bsearch_s
#@ stub -version=0x601 btowc
#@ stub -version=0x601 c16rtomb
#@ stub -version=0x601 c32rtomb
#@ stub -version=0x601 cabs
#@ stub -version=0x601 cabsf
#@ stub -version=0x601 cabsl
#@ stub -version=0x601 cacos
#@ stub -version=0x601 cacosf
#@ stub -version=0x601 cacosh
#@ stub -version=0x601 cacoshf
#@ stub -version=0x601 cacoshl
#@ stub -version=0x601 cacosl
@ cdecl calloc(long long)
#@ stub -version=0x601 carg
#@ stub -version=0x601 cargf
#@ stub -version=0x601 cargl
#@ stub -version=0x601 casin
#@ stub -version=0x601 casinf
#@ stub -version=0x601 casinh
#@ stub -version=0x601 casinhf
#@ stub -version=0x601 casinhl
#@ stub -version=0x601 casinl
#@ stub -version=0x601 catan
#@ stub -version=0x601 catanf
#@ stub -version=0x601 catanh
#@ stub -version=0x601 catanhf
#@ stub -version=0x601 catanhl
#@ stub -version=0x601 catanl
#@ stub -version=0x601 cbrt
#@ stub -version=0x601 cbrtf
#@ stub -version=0x601 cbrtl
#@ stub -version=0x601 ccos
#@ stub -version=0x601 ccosf
#@ stub -version=0x601 ccosh
#@ stub -version=0x601 ccoshf
#@ stub -version=0x601 ccoshl
#@ stub -version=0x601 ccosl
@ cdecl ceil(double)
@ cdecl -arch=x86_64,arm ceilf(long)
#@ stub -version=0x601 cexp
#@ stub -version=0x601 cexpf
#@ stub -version=0x601 cexpl
#@ stub -version=0x601 cimag
#@ stub -version=0x601 cimagf
#@ stub -version=0x601 cimagl
@ cdecl clearerr(ptr)
#@ stub -version=0x601 clearerr_s
@ cdecl clock()
#@ stub -version=0x601 clog
#@ stub -version=0x601 clog10
#@ stub -version=0x601 clog10f
#@ stub -version=0x601 clog10l
#@ stub -version=0x601 clogf
#@ stub -version=0x601 clogl
#@ stub -version=0x601 conj
#@ stub -version=0x601 conjf
#@ stub -version=0x601 conjl
#@ stub -version=0x601 copysign
#@ stub -version=0x601 copysignf
#@ stub -version=0x601 copysignl
@ cdecl cos(double)
@ cdecl -arch=x86_64,arm cosf(long)
@ cdecl cosh(double)
@ cdecl -arch=x86_64,arm coshf(long)
#@ stub -version=0x601 cpow
#@ stub -version=0x601 cpowf
#@ stub -version=0x601 cpowl
#@ stub -version=0x601 cproj
#@ stub -version=0x601 cprojf
#@ stub -version=0x601 cprojl
#@ stub -version=0x601 creal
#@ stub -version=0x601 crealf
#@ stub -version=0x601 creall
#@ stub -version=0x601 csin
#@ stub -version=0x601 csinf
#@ stub -version=0x601 csinh
#@ stub -version=0x601 csinhf
#@ stub -version=0x601 csinhl
#@ stub -version=0x601 csinl
#@ stub -version=0x601 csqrt
#@ stub -version=0x601 csqrtf
#@ stub -version=0x601 csqrtl
#@ stub -version=0x601 ctan
#@ stub -version=0x601 ctanf
#@ stub -version=0x601 ctanh
#@ stub -version=0x601 ctanhf
#@ stub -version=0x601 ctanhl
#@ stub -version=0x601 ctanl
@ cdecl div(long long)
#@ stub -version=0x601 erf
#@ stub -version=0x601 erfc
#@ stub -version=0x601 erfcf
#@ stub -version=0x601 erfcl
#@ stub -version=0x601 erff
#@ stub -version=0x601 erfl
@ cdecl exit(long)
@ cdecl exp(double)
#@ stub -version=0x601 exp2
#@ stub -version=0x601 exp2f
#@ stub -version=0x601 exp2l
@ cdecl -arch=x86_64,arm expf(long)
#@ stub -version=0x601 expm1
#@ stub -version=0x601 expm1f
#@ stub -version=0x601 expm1l
@ cdecl fabs(double)
@ cdecl fclose(ptr)
#@ stub -version=0x601 fdim
#@ stub -version=0x601 fdimf
#@ stub -version=0x601 fdiml
#@ stub -version=0x601 feclearexcept
#@ stub -version=0x601 fegetenv
#@ stub -version=0x601 fegetexceptflag
#@ stub -version=0x601 fegetround
#@ stub -version=0x601 feholdexcept
@ cdecl feof(ptr)
@ cdecl ferror(ptr)
#@ stub -version=0x601 fesetenv
#@ stub -version=0x601 fesetexceptflag
#@ stub -version=0x601 fesetround
#@ stub -version=0x601 fetestexcept
@ cdecl fflush(ptr)
@ cdecl fgetc(ptr)
@ cdecl fgetpos(ptr ptr)
@ cdecl fgets(ptr long ptr)
@ cdecl fgetwc(ptr)
@ cdecl fgetws(ptr long ptr)
@ cdecl floor(double)
@ cdecl -arch=x86_64,arm floorf(long)
#@ stub -version=0x601 fma
#@ stub -version=0x601 fmaf
#@ stub -version=0x601 fmal
#@ stub -version=0x601 fmax
#@ stub -version=0x601 fmaxf
#@ stub -version=0x601 fmaxl
#@ stub -version=0x601 fmin
#@ stub -version=0x601 fminf
#@ stub -version=0x601 fminl
@ cdecl fmod(double double)
@ cdecl -arch=x86_64,arm fmodf(long)
@ cdecl fopen(str str)
#@ stub -version=0x601 fopen_s
@ cdecl fputc(long ptr)
@ cdecl fputs(str ptr)
@ cdecl fputwc(long ptr)
@ cdecl fputws(wstr ptr)
@ cdecl fread(ptr long long ptr)
#@ stub -version=0x601 fread_s
@ cdecl free(ptr)
@ cdecl freopen(str str ptr)
#@ stub -version=0x601 freopen_s
@ cdecl frexp(double ptr)
@ cdecl fseek(ptr long long)
@ cdecl fsetpos(ptr ptr)
@ cdecl ftell(ptr)
@ cdecl fwrite(ptr long long ptr)
@ cdecl getc(ptr)
@ cdecl getchar()
@ cdecl getenv(str)
#@ stub -version=0x601 getenv_s
@ cdecl gets(str)
#@ stub -version=0x601 gets_s
@ cdecl getwc(ptr)
@ cdecl getwchar()
#@ stub -version=0x601 hypot
#@ stub -version=0x601 ilogb
#@ stub -version=0x601 ilogbf
#@ stub -version=0x601 ilogbl
#@ stub -version=0x601 imaxabs
#@ stub -version=0x601 imaxdiv
@ cdecl is_wctype(long long)
@ cdecl isalnum(long)
@ cdecl isalpha(long)
#@ stub -version=0x601 isblank
@ cdecl iscntrl(long)
@ cdecl isdigit(long)
@ cdecl isgraph(long)
@ cdecl isleadbyte(long)
@ cdecl islower(long)
@ cdecl isprint(long)
@ cdecl ispunct(long)
@ cdecl isspace(long)
@ cdecl isupper(long)
@ cdecl iswalnum(long)
@ cdecl iswalpha(long)
@ cdecl iswascii(long)
#@ stub -version=0x601 iswblank
@ cdecl iswcntrl(long)
@ cdecl iswctype(long long)
@ cdecl iswdigit(long)
@ cdecl iswgraph(long)
@ cdecl iswlower(long)
@ cdecl iswprint(long)
@ cdecl iswpunct(long)
@ cdecl iswspace(long)
@ cdecl iswupper(long)
@ cdecl iswxdigit(long)
@ cdecl isxdigit(long)
@ cdecl labs(long)
@ cdecl ldexp(double long)
@ cdecl ldiv(long long)
#@ stub -version=0x601 lgamma
#@ stub -version=0x601 lgammaf
#@ stub -version=0x601 lgammal
#@ stub -version=0x601 llabs
#@ stub -version=0x601 lldiv
#@ stub -version=0x601 llrint
#@ stub -version=0x601 llrintf
#@ stub -version=0x601 llrintl
#@ stub -version=0x601 llround
#@ stub -version=0x601 llroundf
#@ stub -version=0x601 llroundl
@ cdecl localeconv()
@ cdecl log(double)
@ cdecl log10(double)
@ cdecl -arch=x86_64,arm log10f(long)
#@ stub -version=0x601 log1p
#@ stub -version=0x601 log1pf
#@ stub -version=0x601 log1pl
#@ stub -version=0x601 log2
#@ stub -version=0x601 log2f
#@ stub -version=0x601 log2l
#@ stub -version=0x601 logb
#@ stub -version=0x601 logbf
#@ stub -version=0x601 logbl
@ cdecl -arch=x86_64,arm logf(long)
@ cdecl longjmp(ptr long)
#@ stub -version=0x601 lrint
#@ stub -version=0x601 lrintf
#@ stub -version=0x601 lrintl
#@ stub -version=0x601 lround
#@ stub -version=0x601 lroundf
#@ stub -version=0x601 lroundl
@ cdecl malloc(long)
@ cdecl mblen(ptr long)
#@ stub -version=0x601 mbrlen
#@ stub -version=0x601 mbrtoc16
#@ stub -version=0x601 mbrtoc32
#@ stub -version=0x601 mbrtowc
#@ stub -version=0x601 mbsrtowcs
#@ stub -version=0x601 mbsrtowcs_s
@ cdecl mbstowcs(ptr str long)
#@ stub -version=0x601 mbstowcs_s
@ cdecl mbtowc(wstr str long)
@ cdecl memchr(ptr long long)
@ cdecl memcmp(ptr ptr long)
@ cdecl memcpy(ptr ptr long)
#@ stub -version=0x601 memcpy_s
@ cdecl memmove(ptr ptr long)
#@ stub -version=0x601 memmove_s
@ cdecl memset(ptr long long)
@ cdecl modf(double ptr)
@ cdecl -arch=x86_64,arm modff(long ptr)
#@ stub -version=0x601 nan
#@ stub -version=0x601 nanf
#@ stub -version=0x601 nanl
#@ stub -version=0x601 nearbyint
#@ stub -version=0x601 nearbyintf
#@ stub -version=0x601 nearbyintl
#@ stub -version=0x601 nextafter
#@ stub -version=0x601 nextafterf
#@ stub -version=0x601 nextafterl
#@ stub -version=0x601 nexttoward
#@ stub -version=0x601 nexttowardf
#@ stub -version=0x601 nexttowardl
#@ stub -version=0x601 norm
#@ stub -version=0x601 normf
#@ stub -version=0x601 norml
@ cdecl perror(str)
@ cdecl pow(double double)
@ cdecl powf(long)
@ cdecl putc(long ptr)
@ cdecl putchar(long)
@ cdecl puts(str)
@ cdecl putwc(long ptr) fputwc
@ cdecl putwchar(long) _fputwchar
@ cdecl qsort(ptr long long ptr)
#@ stub -version=0x601 qsort_s
#@ stub -version=0x601 quick_exit
@ cdecl raise(long)
@ cdecl rand()
#@ stub -version=0x601 rand_s
@ cdecl realloc(ptr long)
#@ stub -version=0x601 remainder
#@ stub -version=0x601 remainderf
#@ stub -version=0x601 remainderl
@ cdecl remove(str)
#@ stub -version=0x601 remquo
#@ stub -version=0x601 remquof
#@ stub -version=0x601 remquol
@ cdecl rename(str str)
@ cdecl rewind(ptr)
#@ stub -version=0x601 rint
#@ stub -version=0x601 rintf
#@ stub -version=0x601 rintl
#@ stub -version=0x601 round
#@ stub -version=0x601 roundf
#@ stub -version=0x601 roundl
#@ stub -version=0x601 scalbln
#@ stub -version=0x601 scalblnf
#@ stub -version=0x601 scalblnl
#@ stub -version=0x601 scalbn
#@ stub -version=0x601 scalbnf
#@ stub -version=0x601 scalbnl
#@ stub -version=0x601 set_terminate
#@ stub -version=0x601 set_unexpected
@ cdecl setbuf(ptr ptr)
@ cdecl -arch=x86_64,arm -norelay setjmp(ptr ptr) _setjmp
@ cdecl setlocale(long str)
@ cdecl setvbuf(ptr str long long)
@ cdecl signal(long long)
@ cdecl sin(double)
@ cdecl -arch=x86_64,arm sinf(long)
@ cdecl sinh(double)
@ cdecl -arch=x86_64,arm sinhf(long)
@ cdecl sqrt(double)
@ cdecl -arch=x86_64,arm sqrtf(long)
@ cdecl srand(long)
@ cdecl strcat(str str)
#@ stub -version=0x601 strcat_s
@ cdecl strchr(str long)
@ cdecl strcmp(str str)
@ cdecl strcoll(str str)
@ cdecl strcpy(ptr str)
#@ stub -version=0x601 strcpy_s
@ cdecl strcspn(str str)
@ cdecl strerror(long)
#@ stub -version=0x601 strerror_s
@ cdecl strftime(str long str ptr)
@ cdecl strlen(str)
@ cdecl strncat(str str long)
#@ stub -version=0x601 strncat_s
@ cdecl strncmp(str str long)
@ cdecl strncpy(ptr str long)
#@ stub -version=0x601 strncpy_s
#@ stub -version=0x601 strnlen
@ cdecl strpbrk(str str)
@ cdecl strrchr(str long)
@ cdecl strspn(str str)
@ cdecl strstr(str str)
@ cdecl strtod(str ptr)
#@ stub -version=0x601 strtof
#@ stub -version=0x601 strtoimax
@ cdecl strtok(str str)
#@ stub -version=0x601 strtok_s
@ cdecl strtol(str ptr long)
#@ stub -version=0x601 strtold
#@ stub -version=0x601 strtoll
@ cdecl strtoul(str ptr long)
#@ stub -version=0x601 strtoull
#@ stub -version=0x601 strtoumax
@ cdecl strxfrm(ptr str long)
@ cdecl system(str)
@ cdecl tan(double)
@ cdecl -arch=x86_64,arm tanf(long)
@ cdecl tanh(double)
@ cdecl -arch=x86_64,arm tanhf(long)
#@ stub -version=0x601 terminate
#@ stub -version=0x601 tgamma
#@ stub -version=0x601 tgammaf
#@ stub -version=0x601 tgammal
@ cdecl tmpfile()
#@ stub -version=0x601 tmpfile_s
@ cdecl tmpnam(ptr)
#@ stub -version=0x601 tmpnam_s
@ cdecl tolower(long)
@ cdecl toupper(long)
#@ stub -version=0x601 towctrans
@ cdecl towlower(long)
@ cdecl towupper(long)
#@ stub -version=0x601 trunc
#@ stub -version=0x601 truncf
#@ stub -version=0x601 truncl
#@ stub -version=0x601 unexpected
@ cdecl ungetc(long ptr)
@ cdecl ungetwc(long ptr)
#@ stub -version=0x601 wcrtomb
#@ stub -version=0x601 wcrtomb_s
@ cdecl wcscat(wstr wstr)
#@ stub -version=0x601 wcscat_s
@ cdecl wcschr(wstr long)
@ cdecl wcscmp(wstr wstr)
@ cdecl wcscoll(wstr wstr)
@ cdecl wcscpy(ptr wstr)
#@ stub -version=0x601 wcscpy_s
@ cdecl wcscspn(wstr wstr)
@ cdecl wcsftime(ptr long wstr ptr)
@ cdecl wcslen(wstr)
@ cdecl wcsncat(wstr wstr long)
#@ stub -version=0x601 wcsncat_s
@ cdecl wcsncmp(wstr wstr long)
@ cdecl wcsncpy(ptr wstr long)
#@ stub -version=0x601 wcsncpy_s
#@ stub -version=0x601 wcsnlen
@ cdecl wcspbrk(wstr wstr)
@ cdecl wcsrchr(wstr long)
#@ stub -version=0x601 wcsrtombs
#@ stub -version=0x601 wcsrtombs_s
@ cdecl wcsspn(wstr wstr)
@ cdecl wcsstr(wstr wstr)
@ cdecl wcstod(wstr ptr)
#@ stub -version=0x601 wcstof
#@ stub -version=0x601 wcstoimax
@ cdecl wcstok(wstr wstr)
#@ stub -version=0x601 wcstok_s
@ cdecl wcstol(wstr ptr long)
#@ stub -version=0x601 wcstold
#@ stub -version=0x601 wcstoll
@ cdecl wcstombs(ptr ptr long)
#@ stub -version=0x601 wcstombs_s
@ cdecl wcstoul(wstr ptr long)
#@ stub -version=0x601 wcstoull
#@ stub -version=0x601 wcstoumax
@ cdecl wcsxfrm(ptr wstr long)
#@ stub -version=0x601 wctob
@ cdecl wctomb(ptr long)
#@ stub -version=0x601 wctomb_s
#@ stub -version=0x601 wctrans
#@ stub -version=0x601 wctype
#@ stub -version=0x601 wmemcpy_s
#@ stub -version=0x601 wmemmove_s
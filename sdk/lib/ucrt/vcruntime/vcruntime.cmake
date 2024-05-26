
list(APPEND CRT_VCRUNTIME_SOURCES
    vcruntime/__security_init_cookie.c
    vcruntime/__security_check_cookie.c
    vcruntime/__report_rangecheckfailure.c
    vcruntime/__report_gsfailure.c
    vcruntime/__vcrt_init.c
    vcruntime/__std_terminate.c
)

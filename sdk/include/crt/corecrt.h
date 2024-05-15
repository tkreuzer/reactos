
#pragma once

#include <crtdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _CRTRESTRICT
#define _CRTRESTRICT
#endif

#ifndef DEFINED_localeinfo_struct
typedef struct localeinfo_struct {
    pthreadlocinfo locinfo;
    pthreadmbcinfo mbcinfo;
}_locale_tstruct,*_locale_t;
#define DEFINED_localeinfo_struct 1
#endif

typedef struct __crt_locale_data_public
{
      unsigned short const* _locale_pctype;
    _Field_range_(1, 2) int _locale_mb_cur_max;
               unsigned int _locale_lc_codepage;
} __crt_locale_data_public;

#ifdef __cplusplus
} // extern "C"
#endif

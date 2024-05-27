#define _CRTIMP
#define _ACRTIMP
//#include <windows.h>

// runtime
void __GSHandlerCheck_EH(void) {}
void __GSHandlerCheck_SEH(void) {}
void __GSHandlerCheck(void) {}
void __GSHandlerCheck_EH_noexcept(void) {}
void __GSHandlerCheck_SEH_noexcept(void) {}

// initialization
void __acrt_initialize_user_matherr(void) {}
void __scrt_uninitialize_crt(void) {}

// float
int _fltused = 0;

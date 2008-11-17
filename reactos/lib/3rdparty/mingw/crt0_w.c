/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#include <windows.h>

/* Do the UNICODE prototyping of WinMain.  Be aware that in winbase.h WinMain is a macro
   defined to wWinMain.  */
int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nShowCmd);

void __main(void);
int wmain (int flags, wchar_t **cmdline, wchar_t **inst)
{
#ifdef __GNUC__
  /* C++ initialization. (gcc inserts this call automatically for
   * a function called "main", but not for "wmain") */
  __main();
#endif
  return (int) wWinMain ((HINSTANCE) inst, NULL, (LPWSTR) cmdline,(DWORD) flags);
}

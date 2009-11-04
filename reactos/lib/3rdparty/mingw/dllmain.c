#define _DECL_DLLMAIN
#define _WINDOWS_
#include <windows.h>
#include <process.h>

BOOL WINAPI DllMain (HANDLE hDllHandle __attribute__ ((__unused__)),
		     DWORD dwReason __attribute__ ((__unused__)),
		     LPVOID lpreserved __attribute__ ((__unused__)))
{
  return TRUE;
}

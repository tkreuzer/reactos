
#include <stdio.h>
#include <windows.h>
#define DESKTOP_ALL_ACCESS 0x01ff

HDESK CreateInheritableDesktop(WCHAR* name, ACCESS_MASK dwDesiredAccess, BOOL inheritable)
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = inheritable;
    return CreateDesktopW(name, NULL, NULL, 0, dwDesiredAccess, &sa );
}

int
main(int argc, char *argv[])
{
    HDESK hdesk;

    hdesk = CreateInheritableDesktop(L"TestDesktop", DESKTOP_ALL_ACCESS, TRUE);
    if (!hdesk)
    {
        printf("coun#t create desktop\n");
        return -1;
    }

    system("PAUSE");

    SetThreadDesktop(hdesk);

    system("PAUSE");

    return 0;
}

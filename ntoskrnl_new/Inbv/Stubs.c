
#include <ntifs.h>

// http://exploitpack.com/repository/modules/code/Symantec-Workspace-Virtualization-6.4.1895.0.py
// https://git.ipxe.org/sanbootconf.git/blob/6bc630a36c94c8a715aeed79de8c4e9870551bfc:/src/driver/boottext.c
// https://www.acc.umu.se/~bosse/wdkundoc/

// http://downloads.securityfocus.com/vulnerabilities/exploits/61349.c
VOID
NTAPI
InbvAcquireDisplayOwnership (
    VOID)
{
    __debugbreak();
}

// https://git.ipxe.org/sanbootconf.git/blob/6bc630a36c94c8a715aeed79de8c4e9870551bfc:/src/driver/boottext.c
BOOLEAN
NTAPI
InbvCheckDisplayOwnership (
    VOID)
{
    __debugbreak();
    return FALSE;
}

// http://downloads.securityfocus.com/vulnerabilities/exploits/61349.c
BOOLEAN
NTAPI
InbvResetDisplay (
    VOID)
{
    __debugbreak();
    return FALSE;
}
// http://downloads.securityfocus.com/vulnerabilities/exploits/61349.c
VOID
NTAPI
InbvSolidColorFill (
    ULONG Left,
    ULONG Top,
    ULONG Width,
    ULONG Height,
    ULONG color)
{
    __debugbreak();
}

// http://downloads.securityfocus.com/vulnerabilities/exploits/61349.c
ULONG
NTAPI
InbvSetTextColor (
    ULONG Color)
{
    __debugbreak();
    return 0;
}

// http://downloads.securityfocus.com/vulnerabilities/exploits/61349.c
typedef
VOID
(NTAPI *INBV_DISPLAY_STRING_FILTER) (
    PUCHAR *String);

// http://downloads.securityfocus.com/vulnerabilities/exploits/61349.c
VOID
NTAPI
InbvInstallDisplayStringFilter (
    INBV_DISPLAY_STRING_FILTER DisplayStringFilter)
{
    __debugbreak();
}

// http://downloads.securityfocus.com/vulnerabilities/exploits/61349.c
BOOLEAN
NTAPI
InbvEnableDisplayString (
    BOOLEAN bEnable)
{
    __debugbreak();
    return FALSE;
}

// http://downloads.securityfocus.com/vulnerabilities/exploits/61349.c
VOID
NTAPI
InbvSetScrollRegion (
    ULONG x1,
    ULONG y1,
    ULONG x2,
    ULONG y2)
{
    __debugbreak();
}

// https://www.acc.umu.se/~bosse/wdkundoc/
BOOLEAN
NTAPI
InbvDisplayString (
    PUCHAR Str)
{
    __debugbreak();
    return FALSE;
}

// https://git.ipxe.org/sanbootconf.git/blob/6bc630a36c94c8a715aeed79de8c4e9870551bfc:/src/driver/boottext.c
VOID
NTAPI
InbvEnableBootDriver (
    _In_ BOOLEAN Enable)
{
    __debugbreak();
}

// https://git.ipxe.org/sanbootconf.git/blob/6bc630a36c94c8a715aeed79de8c4e9870551bfc:/src/driver/boottext.c
BOOLEAN
NTAPI
InbvIsBootDriverInstalled (
    VOID)
{
    __debugbreak();
    return FALSE;
}

//@ stub InbvNotifyDisplayOwnershipChange
VOID
NTAPI
InbvNotifyDisplayOwnershipChange (
    VOID)
{
    __debugbreak();
}

typedef
BOOLEAN
(NTAPI *INBV_RESET_DISPLAY_PARAMETERS) (
    ULONG Cols,
    ULONG Rows);

// https://git.ipxe.org/sanbootconf.git/blob/6bc630a36c94c8a715aeed79de8c4e9870551bfc:/src/driver/boottext.c
VOID
NTAPI
InbvNotifyDisplayOwnershipLost (
    _In_ INBV_RESET_DISPLAY_PARAMETERS Callback)
{
    __debugbreak();
}


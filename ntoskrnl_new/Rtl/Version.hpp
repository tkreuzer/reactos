
#pragma once

#include "Rtl.hpp"

typedef struct _OSVERSIONINFOW
{
    ULONG dwOSVersionInfoSize;
    ULONG dwMajorVersion;
    ULONG dwMinorVersion;
    ULONG dwBuildNumber;
    ULONG dwPlatformId;
    WCHAR szCSDVersion[128];
} OSVERSIONINFOW, *POSVERSIONINFOW, *LPOSVERSIONINFOW,
  RTL_OSVERSIONINFOW, *PRTL_OSVERSIONINFOW;

typedef struct _OSVERSIONINFOEXW
{
    ULONG dwOSVersionInfoSize;
    ULONG dwMajorVersion;
    ULONG dwMinorVersion;
    ULONG dwBuildNumber;
    ULONG dwPlatformId;
    WCHAR szCSDVersion[128];
    USHORT wServicePackMajor;
    USHORT wServicePackMinor;
    USHORT wSuiteMask;
    UCHAR wProductType;
    UCHAR wReserved;
} OSVERSIONINFOEXW, *POSVERSIONINFOEXW, *LPOSVERSIONINFOEXW,
  RTL_OSVERSIONINFOEXW, *PRTL_OSVERSIONINFOEXW;

typedef enum _OS_DEPLOYEMENT_STATE_VALUES
{
    OS_DEPLOYMENT_STANDARD = 1,
    OS_DEPLOYMENT_COMPACT
} OS_DEPLOYEMENT_STATE_VALUES;

typedef
BOOLEAN
NTAPI
FN_RTL_IS_NTDDI_VERSION_AVAILABLE (
    _In_ ULONG Version);
typedef FN_RTL_IS_NTDDI_VERSION_AVAILABLE
    *PFN_RTL_IS_NTDDI_VERSION_AVAILABLE;

typedef
BOOLEAN
NTAPI
FN_RTL_IS_SERVICE_PACK_VERSION_INSTALLED (
    _In_ ULONG Version);
typedef FN_RTL_IS_SERVICE_PACK_VERSION_INSTALLED
    *PFN_RTL_IS_SERVICE_PACK_VERSION_INSTALLED;

#define VER_EQUAL                        1
#define VER_GREATER                      2
#define VER_GREATER_EQUAL                3
#define VER_LESS                         4
#define VER_LESS_EQUAL                   5
#define VER_AND                          6
#define VER_OR                           7

#define VER_CONDITION_MASK               7
#define VER_NUM_BITS_PER_CONDITION_MASK  3

#define VER_MINORVERSION         0x0000001
#define VER_MAJORVERSION         0x0000002
#define VER_BUILDNUMBER          0x0000004
#define VER_PLATFORMID           0x0000008
#define VER_SERVICEPACKMINOR     0x0000010
#define VER_SERVICEPACKMAJOR     0x0000020
#define VER_SUITENAME            0x0000040
#define VER_PRODUCT_TYPE         0x0000080

#define VER_NT_WORKSTATION       0x0000001
#define VER_NT_DOMAIN_CONTROLLER 0x0000002
#define VER_NT_SERVER            0x0000003

#define VER_PLATFORM_WIN32s              0
#define VER_PLATFORM_WIN32_WINDOWS       1
#define VER_PLATFORM_WIN32_NT            2

#define VER_SET_CONDITION(m, t, c)  \
        ((m) = VerSetConditionMask((m), (t), (c)))


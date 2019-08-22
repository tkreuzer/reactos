/*!
    \brief Header shared by ntdll/ldr and spec3def
*/
#pragma once

//#include <stdint.h> meh
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

typedef enum _ROSCOMPAT_VERSION_BIT
{
    ROSCOMPAT_VERSION_BIT_NT4 = 0,
    ROSCOMPAT_VERSION_BIT_WIN2K = 1,
    ROSCOMPAT_VERSION_BIT_WINXP = 2,
    ROSCOMPAT_VERSION_BIT_WS03 = 3,
    ROSCOMPAT_VERSION_BIT_VISTA = 4,
    ROSCOMPAT_VERSION_BIT_WIN7 = 5,
    ROSCOMPAT_VERSION_BIT_WIN8 = 6,
    ROSCOMPAT_VERSION_BIT_WIN81 = 7,
    ROSCOMPAT_VERSION_BIT_WIN10 = 8,
} ROSCOMPAT_VERSION_BIT;

#ifndef IMAGE_DOS_SIGNATURE
typedef struct _IMAGE_EXPORT_DIRECTORY
{
    uint32_t Characteristics;
    uint32_t TimeDateStamp;
    uint16_t MajorVersion;
    uint16_t MinorVersion;
    uint32_t Name;
    uint32_t Base;
    uint32_t NumberOfFunctions;
    uint32_t NumberOfNames;
    uint32_t AddressOfFunctions;
    uint32_t AddressOfNames;
    uint32_t AddressOfNameOrdinals;
} IMAGE_EXPORT_DIRECTORY, * PIMAGE_EXPORT_DIRECTORY;
#endif

typedef struct _ROSCOMPAT_DESCRIPTOR
{
    uint32_t* ExportNameMasks; // Array with size NumberOfNames
    uint32_t NumberOfExportNames;
    PIMAGE_EXPORT_DIRECTORY MagicExportDir;
} ROSCOMPAT_DESCRIPTOR, * PROSCOMPAT_DESCRIPTOR;


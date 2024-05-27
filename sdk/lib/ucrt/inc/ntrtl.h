//
// ntrtl.h
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Header for RTL NT things.
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windef.h>

#include <NTSecAPI.h> // for UNICODE_STRING

typedef struct _CURDIR
{
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURDIR, *PCURDIR;

typedef struct RTL_DRIVE_LETTER_CURDIR
{
    USHORT Flags;
    USHORT Length;
    ULONG TimeStamp;
    UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
    ULONG MaximumLength;                                                    //0x0
    ULONG Length;                                                           //0x4
    ULONG Flags;                                                            //0x8
    ULONG DebugFlags;                                                       //0xc
    HANDLE ConsoleHandle;                                                   //0x10
    ULONG ConsoleFlags;                                                     //0x18
    PVOID StandardInput;                                                    //0x20
    PVOID StandardOutput;                                                   //0x28
    PVOID StandardError;                                                    //0x30
    CURDIR CurrentDirectory;                                                //0x38
    UNICODE_STRING DllPath;                                                 //0x50
    UNICODE_STRING ImagePathName;                                           //0x60
    UNICODE_STRING CommandLine;                                             //0x70
    PVOID Environment;                                                      //0x80
    ULONG StartingX;                                                        //0x88
    ULONG StartingY;                                                        //0x8c
    ULONG CountX;                                                           //0x90
    ULONG CountY;                                                           //0x94
    ULONG CountCharsX;                                                      //0x98
    ULONG CountCharsY;                                                      //0x9c
    ULONG FillAttribute;                                                    //0xa0
    ULONG WindowFlags;                                                      //0xa4
    ULONG ShowWindowFlags;                                                  //0xa8
    UNICODE_STRING WindowTitle;                                             //0xb0
    UNICODE_STRING DesktopInfo;                                             //0xc0
    UNICODE_STRING ShellInfo;                                               //0xd0
    UNICODE_STRING RuntimeData;                                             //0xe0
    RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];                          //0xf0
    ULONG64 EnvironmentSize;                                                //0x3f0
    ULONG64 EnvironmentVersion;                                             //0x3f8
    PVOID PackageDependencyData;                                            //0x400
    ULONG ProcessGroupId;                                                   //0x408
    ULONG LoaderThreads;                                                    //0x40c
    UNICODE_STRING RedirectionDllName;                                      //0x410
    UNICODE_STRING HeapPartitionName;                                       //0x420
    PULONG64 DefaultThreadpoolCpuSetMasks;                                  //0x430
    ULONG DefaultThreadpoolCpuSetMaskCount;                                 //0x438
    ULONG DefaultThreadpoolThreadMaximum;                                   //0x43c
    ULONG HeapMemoryTypeMask;                                               //0x440
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

#define RTL_USER_PROC_SECURE_PROCESS 0x80000000

#define FAST_FAIL_LEGACY_GS_VIOLATION           0
#define FAST_FAIL_STACK_COOKIE_CHECK_FAILURE    2
#define FAST_FAIL_RANGE_CHECK_FAILURE           8

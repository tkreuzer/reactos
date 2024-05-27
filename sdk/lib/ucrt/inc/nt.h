//
// nt.h
//
//      Copyright (c) 2024 Timo Kreuzer
//
// Header for generic NT things.
//
// SPDX-License-Identifier: MIT
//

#pragma once

#if defined(_M_AMD64) || defined(__x86_64__)
#define _AMD64_ 1
#endif

#include <ntstatus.h>
#define WIN32_NO_STATUS
#include <windef.h>

struct _RTL_USER_PROCESS_PARAMETERS;

typedef struct _PEB
{
#ifdef _WIN64
    UCHAR Reserved1[0x20];
#else
    UCHAR Reserved1[0x10];
#endif
    struct _RTL_USER_PROCESS_PARAMETERS *ProcessParameters; // x86: 0x10 / x64: 0x20
#ifdef _WIN64
    UCHAR Reserved2[0xbc - sizeof(PVOID) - 0x20];
#else
    UCHAR Reserved2[0x68 - sizeof(PVOID) - 0x10];
#endif
    ULONG NtGlobalFlag; // x86: 0x68 / x64: 0xbc
} PEB, *PPEB;

typedef struct _TEB
{
#ifdef _WIN64
    UCHAR Reserved1[0x60];
#else
    UCHAR Reserved1[0x30];
#endif
    PPEB ProcessEnvironmentBlock; // x86: 0x30 / x64: 0x60
} TEB, *PTEB;

#define FLG_APPLICATION_VERIFIER 0x00000001 // CHECKME

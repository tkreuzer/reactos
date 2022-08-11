/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Kernel
 * FILE:            ntoskrnl/include/ntoskrnl.h
 * PURPOSE:         Main Kernel Header
 * PROGRAMMER:      Alex Ionescu (alex@relsoft.net)
 */

#pragma once
#ifndef _RTL_KM_
#define _RTL_KM_

 /* INCLUDES ******************************************************************/

#define KeEnterCriticalRegion _KeEnterCriticalRegion
#define KeLeaveCriticalRegion _KeLeaveCriticalRegion

 /* ARM Bringup Hack */
#ifdef _M_ARM
#define DbgPrint DbgPrintEarly
#endif

/* WDK hacks */
#ifdef _M_AMD64
#define IoAllocateAdapterChannel _IoAllocateAdapterChannel
#define KeGetCurrentThread _KeGetCurrentThread
#define RtlFillMemoryUlong _RtlFillMemoryUlong
#endif

/* Version Data */
#undef __MSVCRT__
#include <psdk/ntverp.h>

/* DDK/IFS/NDK Headers */
#define _REALLY_GET_CALLERS_CALLER
#include <excpt.h>
#include <ntdef.h>
#include <ntifs.h>
#include <wdmguid.h>
#include <diskguid.h>
#include <arc/arc.h>
#include <mountmgr.h>
#undef NTHALAPI
#define NTHALAPI __declspec(dllimport)
#include <ndk/asm.h>
#include <ndk/cctypes.h>
#include <ndk/cmfuncs.h>
#include <ndk/dbgkfuncs.h>
#include <ndk/exfuncs.h>
#include <ndk/halfuncs.h>
#include <ndk/inbvfuncs.h>
#include <ndk/iofuncs.h>
#include <ndk/kdfuncs.h>
#include <ndk/kefuncs.h>
#include <ndk/ldrfuncs.h>
#include <ndk/lpcfuncs.h>
#include <ndk/mmfuncs.h>
#include <ndk/muptypes.h>
#include <ndk/obfuncs.h>
#include <ndk/pofuncs.h>
#include <ndk/psfuncs.h>
#include <ndk/rtlfuncs.h>
#include <ndk/sefuncs.h>
#include <ndk/vftypes.h>

#undef TEXT
#define TEXT(s) L##s

#define _IN_KERNEL_
#include <regstr.h>

#include <ntstrsafe.h>
#define ENABLE_INTSAFE_SIGNED_FUNCTIONS
#include <ntintsafe.h>
#undef ENABLE_INTSAFE_SIGNED_FUNCTIONS

/* C Headers */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <wchar.h>

/* SEH support with PSEH */
#include <pseh/pseh2.h>
#include <reactos/probe.h>

#ifdef _MSC_VER
# pragma section("INITDATA", read,write,discard)
#endif

extern ULONG CmNtCSDVersion;
extern KSPIN_LOCK PsLoadedModuleSpinLock;

PVOID
NTAPI
KiPcToFileHeader(
    _In_ PVOID Eip,
    _Out_ PLDR_DATA_TABLE_ENTRY * LdrEntry,
    _In_ BOOLEAN DriversOnly,
    _Out_ PBOOLEAN InKernel);

PHANDLE_TABLE
NTAPI
ExCreateHandleTable(
    _In_opt_ PEPROCESS Process);

VOID
NTAPI
ExUnlockHandleTableEntry(
    _In_ PHANDLE_TABLE HandleTable,
    _In_ PHANDLE_TABLE_ENTRY HandleTableEntry);

VOID
NTAPI
ExDestroyHandleTable(
    _In_ PHANDLE_TABLE HandleTable,
    _In_opt_ PVOID DestroyHandleProcedure);

HANDLE
NTAPI
ExCreateHandle(
    _In_ PHANDLE_TABLE HandleTable,
    _In_ PHANDLE_TABLE_ENTRY HandleTableEntry);

BOOLEAN
NTAPI
ExDestroyHandle(
    _In_ PHANDLE_TABLE HandleTable,
    _In_ HANDLE Handle,
    _In_opt_ PHANDLE_TABLE_ENTRY HandleTableEntry);

PHANDLE_TABLE_ENTRY
NTAPI
ExMapHandleToPointer(
    _In_ PHANDLE_TABLE HandleTable,
    _In_ HANDLE Handle);

typedef
BOOLEAN
(NTAPI * PEX_SWEEP_HANDLE_CALLBACK)(
    PHANDLE_TABLE_ENTRY HandleTableEntry,
    HANDLE Handle,
    PVOID Context);

VOID
NTAPI
ExSweepHandleTable(
    _In_ PHANDLE_TABLE HandleTable,
    _In_ PEX_SWEEP_HANDLE_CALLBACK EnumHandleProcedure,
    _In_ PVOID Context);

/* Run-Time Library Tags */
#define TAG_ATMT  'TotA' /* Atom table */
#define TAG_RTHL  'LHtR' /* Heap Lock */
#define TAG_USTR  'RTSU'
#define TAG_ASTR  'RTSA'
#define TAG_OSTR  'RTSO'

#endif /* _RTL_KM_ */


#include "Rtl.hpp"

extern "C" {

typedef struct _SLIST_HEADER SLIST_HEADER, *PSLIST_HEADER;
typedef struct _SLIST_ENTRY *PSLIST_ENTRY;

/*

CallingCv Function                      x86                         x64
----------------------------------------------------------------------
cdecl     InitializeSListHead           -                           RtlInitializeSListHead
cdecl     ExQueryDepthSList             -                           RtlQueryDepthSList
stdcall   FirstEntrySList               RtlFirstEntrySList          RtlFirstEntrySList

fastcall  InterlockedPushEntrySList     InterlockedPushEntrySList   -
fastcall  ExInterlockedPushEntrySList   ExInterlockedPushEntrySList 
cdecl     ExpInterlockedPushEntrySList  -                           RtlpInterlockedPushEntrySList
stdcall   RtlInterlockedPushEntrySList

fastcall  InterlockedPopEntrySList      InterlockedPopEntrySList   -
fastcall  ExInterlockedPopEntrySList    ExInterlockedPopEntrySList
cdecl     ExpInterlockedPopEntrySList   -                           RtlpInterlockedPopEntrySList
stdcall   RtlInterlockedPopEntrySList

fastcall  ExInterlockedFlushSList       ExInterlockedFlushSList                   -
cdecl     ExpInterlockedFlushSList      -                           InterlockedFlushSList
stdcall   RtlInterlockedFlushSList

fastcall  InterlockedPushListSList      InterlockedPushListSList
----------------------------------------------------------------------------
Spinlock!
fastcall  ExInterlockedPushEntrySList
fastcall  ExInterlockedPopEntrySList

*/

VOID
NTAPI
RtlInitializeSListHead (
    _Out_ PSLIST_HEADER ListHead)
{
    __debugbreak();
}

USHORT
NTAPI
RtlQueryDepthSList (
    _In_ PSLIST_HEADER ListHead)
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
PSLIST_ENTRY
NTAPI
RtlFirstEntrySList (
    _In_ const SLIST_HEADER *ListHead)
{
    __debugbreak();
    return NULL;
}

PSLIST_ENTRY
FASTCALL
InterlockedPushEntrySList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ __drv_aliasesMem PSLIST_ENTRY ListEntry)
{
    __debugbreak();
    return NULL;
}

PSLIST_ENTRY
NTAPI
RtlInterlockedPushEntrySList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ __drv_aliasesMem PSLIST_ENTRY ListEntry)
{
    return InterlockedPushEntrySList(ListHead, ListEntry);
}

PSLIST_ENTRY
FASTCALL
InterlockedPopEntrySList (
    _Inout_ PSLIST_HEADER ListHead)
{
    __debugbreak();
    return NULL;
}

PSLIST_ENTRY
NTAPI
RtlInterlockedPopEntrySList (
    _Inout_ PSLIST_HEADER ListHead)
{
    return InterlockedPopEntrySList(ListHead);
}

PSLIST_ENTRY
FASTCALL
InterlockedPushListSList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ __drv_aliasesMem PSLIST_ENTRY List,
    _Inout_ PSLIST_ENTRY ListEnd,
    _In_ ULONG Count)
{
    __debugbreak();
    return NULL;
}

// winnt.h
PSLIST_ENTRY
NTAPI
RtlInterlockedPushListSListEx (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ __drv_aliasesMem PSLIST_ENTRY List,
    _Inout_ PSLIST_ENTRY ListEnd,
    _In_ ULONG Count);

PSLIST_ENTRY
NTAPI
RtlInterlockedPushListSList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ __drv_aliasesMem PSLIST_ENTRY List,
    _Inout_ PSLIST_ENTRY ListEnd,
    _In_ ULONG Count)
{
    return InterlockedPushListSList(ListHead, List, ListEnd, Count);
}

PSLIST_ENTRY
FASTCALL
InterlockedFlushSList (
    _Inout_ PSLIST_HEADER ListHead)
{
    __debugbreak();
    return NULL;
}

PSLIST_ENTRY
NTAPI
RtlInterlockedFlushSList (
    _Inout_ PSLIST_HEADER ListHead)
{
    return InterlockedFlushSList(ListHead);
}


} // extern "C"

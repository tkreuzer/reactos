
#pragma once

#include <debug.h>

FORCEINLINE
VOID
InitializeListHead (
    _Out_ PLIST_ENTRY ListHead)
{
    ListHead->Flink = ListHead->Blink = ListHead;
}

_Must_inspect_result_
FORCEINLINE
BOOLEAN
IsListEmpty (
    _In_ const LIST_ENTRY * ListHead)
{
    return (ListHead->Flink == ListHead);
}

FORCEINLINE
BOOLEAN
RemoveEntryListUnsafe (
    _In_ PLIST_ENTRY Entry)
{
    PLIST_ENTRY OldFlink;
    PLIST_ENTRY OldBlink;

    OldFlink = Entry->Flink;
    OldBlink = Entry->Blink;
    OldFlink->Blink = OldBlink;
    OldBlink->Flink = OldFlink;
    return (OldFlink == OldBlink);
}

#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS)
FORCEINLINE
VOID
FatalListEntryError (
    _In_ PVOID P1,
    _In_ PVOID P2,
    _In_ PVOID P3)
{
    UNREFERENCED_PARAMETER(P1);
    UNREFERENCED_PARAMETER(P2);
    UNREFERENCED_PARAMETER(P3);
    __fastfail(FAST_FAIL_CORRUPT_LIST_ENTRY);
}

FORCEINLINE
VOID
RtlpCheckListEntry (
    _In_ PLIST_ENTRY Entry)
{
    if (Entry->Flink->Blink != Entry || Entry->Blink->Flink != Entry)
        FatalListEntryError(Entry->Blink, Entry, Entry->Flink);
}
#endif

FORCEINLINE
BOOLEAN
RemoveEntryList (
    _In_ PLIST_ENTRY Entry)
{
    PLIST_ENTRY OldFlink;
    PLIST_ENTRY OldBlink;

    OldFlink = Entry->Flink;
    OldBlink = Entry->Blink;
#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS)
#ifdef EXTRA_KERNEL_LIST_ENTRY_CHECKS
    if (OldFlink == Entry || OldBlink == Entry)
        FatalListEntryError(OldBlink, Entry, OldFlink);
#endif
    if (OldFlink->Blink != Entry || OldBlink->Flink != Entry)
        FatalListEntryError(OldBlink, Entry, OldFlink);
#endif
    OldFlink->Blink = OldBlink;
    OldBlink->Flink = OldFlink;
    return (OldFlink == OldBlink);
}

FORCEINLINE
PLIST_ENTRY
RemoveHeadList (
    _Inout_ PLIST_ENTRY ListHead)
{
    PLIST_ENTRY Flink;
    PLIST_ENTRY Entry;

#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS) && DBG
    RtlpCheckListEntry(ListHead);
#ifdef EXTRA_KERNEL_LIST_ENTRY_CHECKS
    if (ListHead->Flink == ListHead || ListHead->Blink == ListHead)
        FatalListEntryError(ListHead->Blink, ListHead, ListHead->Flink);
#endif
#endif
    Entry = ListHead->Flink;
    Flink = Entry->Flink;
#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS)
    if (Entry->Blink != ListHead || Flink->Blink != Entry)
        FatalListEntryError(ListHead, Entry, Flink);
#endif
    ListHead->Flink = Flink;
    Flink->Blink = ListHead;
    return Entry;
}

FORCEINLINE
PLIST_ENTRY
RemoveTailList (
    _Inout_ PLIST_ENTRY ListHead)
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Entry;

#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS) && DBG
    RtlpCheckListEntry(ListHead);
#ifdef EXTRA_KERNEL_LIST_ENTRY_CHECKS
    if (ListHead->Flink == ListHead || ListHead->Blink == ListHead)
        FatalListEntryError(ListHead->Blink, ListHead, ListHead->Flink);
#endif
#endif
    Entry = ListHead->Blink;
    Blink = Entry->Blink;
#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS)
    if (Blink->Flink != Entry || Entry->Flink != ListHead)
        FatalListEntryError(Blink, Entry, ListHead);
#endif
    ListHead->Blink = Blink;
    Blink->Flink = ListHead;
    return Entry;
}

FORCEINLINE
VOID
InsertHeadList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PLIST_ENTRY Entry)
{
    PLIST_ENTRY OldFlink;
#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS) && DBG
    RtlpCheckListEntry(ListHead);
#endif
    OldFlink = ListHead->Flink;
    Entry->Flink = OldFlink;
    Entry->Blink = ListHead;
#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS)
    if (OldFlink->Blink != ListHead)
        FatalListEntryError(ListHead, OldFlink, OldFlink->Flink);
#endif
    OldFlink->Blink = Entry;
    ListHead->Flink = Entry;
}

FORCEINLINE
VOID
InsertTailList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PLIST_ENTRY Entry)
{
    PLIST_ENTRY OldBlink;
#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS) && DBG
    RtlpCheckListEntry(ListHead);
#endif
    OldBlink = ListHead->Blink;
    Entry->Flink = ListHead;
    Entry->Blink = OldBlink;
#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS)
    if (OldBlink->Flink != ListHead)
        FatalListEntryError(OldBlink->Blink, OldBlink, ListHead);
#endif
    OldBlink->Flink = Entry;
    ListHead->Blink = Entry;
}

FORCEINLINE
VOID
AppendTailList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ PLIST_ENTRY ListToAppend)
{
    PLIST_ENTRY ListEnd = ListHead->Blink;

#if !defined(NO_KERNEL_LIST_ENTRY_CHECKS)
    RtlpCheckListEntry(ListHead);
    RtlpCheckListEntry(ListToAppend);
#endif
    ListHead->Blink->Flink = ListToAppend;
    ListHead->Blink = ListToAppend->Blink;
    ListToAppend->Blink->Flink = ListHead;
    ListToAppend->Blink = ListEnd;
}

FORCEINLINE
PSINGLE_LIST_ENTRY
PopEntryList (
    _Inout_ PSINGLE_LIST_ENTRY ListHead)
{
    PSINGLE_LIST_ENTRY FirstEntry;
    FirstEntry = ListHead->Next;
    if (FirstEntry != NULL)
    {
        ListHead->Next = FirstEntry->Next;
    }
    return FirstEntry;
}

FORCEINLINE
VOID
PushEntryList (
    _Inout_ PSINGLE_LIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PSINGLE_LIST_ENTRY Entry)
{
    Entry->Next = ListHead->Next;
    ListHead->Next = Entry;
}

#ifdef __cplusplus

class LIST_HEAD
{
    LIST_ENTRY _Head;

public:

    inline
    LIST_HEAD (
        VOID)
    {
        InitializeListHead(&_Head);
    }

    _Must_inspect_result_
    inline
    BOOLEAN
    IsEmpty (
        VOID) const
    {
        return IsListEmpty(&_Head);
    }

    inline
    VOID
    InsertHead (
        _Inout_ __drv_aliasesMem PLIST_ENTRY ListEntry)
    {
        InsertHeadList(&_Head, ListEntry);
    }

    inline
    VOID
    InsertTail (
        _Inout_ __drv_aliasesMem PLIST_ENTRY ListEntry)
    {
        InsertTailList(&_Head, ListEntry);
    }

    inline
    PLIST_ENTRY
    RemoveHead (
        VOID)
    {
        if (IsListEmpty(&_Head))
        {
            return NULL;
        }

        return RemoveHeadList(&_Head);
    }

    inline
    PLIST_ENTRY
    RemoveTail (
        VOID)
    {
        if (IsListEmpty(&_Head))
        {
            return NULL;
        }

        return RemoveTailList(&_Head);
    }

    static
    inline
    BOOLEAN
    RemoveEntry (
        _In_ PLIST_ENTRY ListEntry)
    {
        return RemoveEntryList(ListEntry);
    }



};

template<typename _T, size_t Offset>
class LINKED_LISTEX
    : public LIST_HEAD
{

    inline
    VOID
    InsertHead (
        _Inout_ __drv_aliasesMem _T *Object)
    {
        PLIST_ENTRY ListEntry = (PLIST_ENTRY)((ULONG_PTR)Object + Offset);
        LIST_HEAD::InsertHead(ListEntry);
    }

    inline
    VOID
    InsertTail (
        _Inout_ __drv_aliasesMem _T *Object)
    {
        PLIST_ENTRY ListEntry = (PLIST_ENTRY)((ULONG_PTR)Object + Offset);
        LIST_HEAD::InsertTail(ListEntry);
    }

    inline
    _T*
    RemoveHead (
        VOID)
    {
        PLIST_ENTRY ListEntry;

        if (IsEmpty())
        {
            return NULL;
        }

        ListEntry = RemoveHeadList(&_Head);
        return (_T*)((ULONG_PTR)ListEntry - Offset);
    }

    inline
    _T*
    RemoveTail (
        VOID)
    {
        PLIST_ENTRY ListEntry;

        if (IsEmpty())
        {
            return NULL;
        }

        ListEntry = RemoveTailList(&_Head);
        return (_T*)((ULONG_PTR)ListEntry - Offset);
    }

};

template<typename _T>
class LINKED_LIST
    : public LINKED_LISTEX<_T, 0>
{
};



#endif

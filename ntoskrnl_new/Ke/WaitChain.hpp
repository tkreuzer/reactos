
#pragma once

//#include "Thread.hpp"

namespace Ke {


class WAIT_CHAIN
{
    typedef union _WAIT_CHAIN_ENTRY
    {
        PSINGLE_LIST_ENTRY SListEntry;
        union _WAIT_CHAIN_ENTRY *Next;
        PVOID Ptr;
    } WAIT_CHAIN_ENTRY, *PWAIT_CHAIN_ENTRY;

    volatile WAIT_CHAIN_ENTRY _Head;

public:

    inline
    WAIT_CHAIN (
        VOID)
    {
        _Head.Ptr = NULL;
    }

    inline
    ~WAIT_CHAIN (
        VOID)
    {
        NT_ASSERT(_Head.Ptr == NULL);
    }

    VOID
    Wait (
        VOID)
    {
#if 0
        PTHREAD CurrentThread;
        WAIT_CHAIN_ENTRY OldEntry, Compare, NewEntry;

        CurrentThread = GetCurrentThread();
        CurrentThread->State = Waiting;

        NewEntry.SListEntry = CurrentThread->GetSwapListEntry();
        OldEntry.Ptr = _Head.Ptr;

        do
        {
            NewEntry.SListEntry->Next = OldEntry.SListEntry;
            Compare = OldEntry;
            OldEntry.Ptr = InterlockedCompareExchangePointer(&_Head.Ptr,
                                                             NewEntry.Ptr,
                                                             OldEntry.Ptr);
        } while (OldEntry.Ptr != Compare.Ptr);

        CurrentThread->Wait();
#endif
    }

    VOID
    WakeAll (
        VOID)
    {
#if 0
        WAIT_CHAIN_ENTRY Entry;

        if (_Head.Ptr != NULL)
        {
            Entry.Ptr = InterlockedExchangePointer(&_Head.Ptr, NULL);

            while (Entry.Ptr != NULL)
            {
                Thread = CONTAINING_RECORD(Entry.SlistEntry, THREAD, SwapListEntry);
                Entry.Next = Entry.Next->Next;
#if DBG
                InitializeListHead(Thread->WaitListEntry)
#endif
                Thread->Wake();
            }
        }
#endif
    }

};




}; // namespace Ke


#pragma once

#include "Exp.hpp"
#include <Ke/SpinLock.hpp>
#include <Ke/Semaphore.hpp>

// ntosp.h
typedef ULONG_PTR ERESOURCE_THREAD, *PERESOURCE_THREAD;

// ntosp.h
typedef struct _OWNER_ENTRY
{
    ERESOURCE_THREAD OwnerThread;
    union
    {
        struct
        {
            ULONG IoPriorityBoosted : 1;
            ULONG OwnerReferenced   : 1;
            ULONG OwnerCount        : 30;
        };
        ULONG TableSize;
    };
} OWNER_ENTRY, *POWNER_ENTRY;

// ntosp.h
typedef struct _ERESOURCE
{
    LIST_ENTRY SystemResourcesList;
    POWNER_ENTRY OwnerTable;
    SHORT ActiveCount;
    union
    {
        USHORT Flag;
        struct
        {
            UCHAR ReservedLowFlags;
            UCHAR WaiterPriority;
        };
    };
    __volatile PKSEMAPHORE SharedWaiters;
    __volatile PKEVENT ExclusiveWaiters;
    OWNER_ENTRY OwnerEntry;
    ULONG ActiveEntries;
    ULONG ContentionCount;
    ULONG NumberOfSharedWaiters;
    ULONG NumberOfExclusiveWaiters;
#if defined(_WIN64)
    PVOID Reserved2;
#endif
    union
    {
        PVOID Address;
        ULONG_PTR CreatorBackTraceIndex;
    };
    KSPIN_LOCK SpinLock;
} ERESOURCE, *PERESOURCE;


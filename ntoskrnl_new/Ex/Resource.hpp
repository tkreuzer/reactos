
#pragma once

#include "Ke/WaitChain.hpp"
#include "Ke/Gate.hpp"

namespace Ex {

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

typedef union _RESOURCE_STATE
{
    LONG Long;
    struct
    {
        SHORT ActiveCount;
        union
        {
            USHORT Flag;
            struct
            {
                UCHAR ReservedLowFlags : 3;
                UCHAR DisableResourceBoost : 1;
                UCHAR ReservedLowFlags2 : 3;
                UCHAR Exclusive : 1;
                UCHAR WaiterPriority;
            };
        };
    };
} RESOURCE_STATE;

typedef class RESOURCE *PRESOURCE;

class RESOURCE
{
private:
    LIST_ENTRY _SystemResourcesList;
    POWNER_ENTRY _OwnerTable;
    RESOURCE_STATE _State;
    Ke::WAIT_CHAIN _SharedWaiters;
    Ke::PGATE _ExclusiveWaitGate;
    OWNER_ENTRY _OwnerEntry;
    LONG _ActiveEntries;
    LONG _ContentionCount;
    LONG _NumberOfSharedWaiters;
    LONG _NumberOfExclusiveWaiters;
    union
    {
        VOID* _Address;
        ULONG _CreatorBackTraceIndex;
    };
    ULONG _SpinLock;

    BOOLEAN
    WaitExclusive (
        VOID);

    VOID
    WaitShared (
        _In_ ULONG Flags);

    VOID
    AllocateWaitGate (
        VOID);

    BOOLEAN
    CanAcquireShared (
        _In_ ULONG Flags) const;

public:

    enum
    {
        FLAG_SHARED = 0x01,
        FLAG_WAIT = 0x02,
        FLAG_WAIT_FOR_EXCLUSIVE = 0x04,
        FLAG_STARVE_EXCLUSIVE = 0x08,
    };

    RESOURCE (
        VOID);

    ~RESOURCE (
        VOID);

    _IRQL_requires_max_(DISPATCH_LEVEL)
    inline
    ULONG
    GetExclusiveWaiterCount (
        VOID) const
    {
        return _NumberOfExclusiveWaiters;
    }

    _IRQL_requires_max_(DISPATCH_LEVEL)
    inline
    ULONG
    GetSharedWaiterCount (
        VOID) const
    {
        return _NumberOfSharedWaiters;
    }

    _IRQL_requires_max_(DISPATCH_LEVEL)
    inline
    BOOLEAN
    IsAcquiredExclusiveLite (
        VOID) const
    {
        return ((_State.Exclusive != 0) &&
                (_OwnerEntry.OwnerThread == (ULONG_PTR)KeGetCurrentThread()));
    }

    _IRQL_requires_max_(DISPATCH_LEVEL)
    ULONG
    IsAcquiredSharedLite (
        VOID) const
    {
        return 0;
    }

    BOOLEAN
    AcquireExclusive (
        _In_ ULONG Flags);

    BOOLEAN
    AcquireShared (
        _In_ ULONG Flags);

    VOID
    Release (
        VOID);

};

}; // namespace Ex

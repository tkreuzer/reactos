
#pragma once

#include "Ke.hpp"
//#include "Cpu/Cpu.hpp"
//#include "KeyedEvent.hpp"

namespace Ke {

typedef enum _KOBJECTS
{
    EventNotificationObject     = 0,
    EventSynchronizationObject  = 1,
    MutantObject                = 2,
    ProcessObject               = 3,
    QueueObject                 = 4,
    SemaphoreObject             = 5,
    ThreadObject                = 6,
    GateObject                  = 7,
    TimerNotificationObject     = 8,
    TimerSynchronizationObject  = 9,
    Spare2Object                = 10,
    Spare3Object                = 11,
    Spare4Object                = 12,
    Spare5Object                = 13,
    Spare6Object                = 14,
    Spare7Object                = 15,
    Spare8Object                = 16,
    ProfileCallbackObject       = 17,
    ApcObject                   = 18,
    DpcObject                   = 19,
    DeviceQueueObject           = 20,
    PriQueueObject              = 21,
    InterruptObject             = 22,
    ProfileObject               = 23,
    Timer2NotificationObject    = 24,
    Timer2SynchronizationObject = 25,
    ThreadedDpcObject           = 26,
    MaximumKernelObject         = 27
} KOBJECTS, *PKOBJECTS;

#if 0
typedef struct _DISPATCHER_HEADER
{
    union
    {
        union
        {
            volatile LONG Lock;
            LONG LockNV;
        } DUMMYUNIONNAME;
        struct
        {
            UCHAR Type;
            UCHAR Signalling;
            UCHAR Size;
            UCHAR Reserved1;
        } DUMMYSTRUCTNAME;
        struct
        {
            UCHAR TimerType;
            union
            {
                UCHAR TimerControlFlags;
                struct
                {
                    UCHAR Absolute : 1;
                    UCHAR Wake : 1;
                    UCHAR EncodedTolerableDelay : TIMER_TOLERABLE_DELAY_BITS;
                } DUMMYSTRUCTNAME;
            };
            UCHAR Hand;
            union
            {
                UCHAR TimerMiscFlags;
                struct
                {
#if !defined(KENCODED_TIMER_PROCESSOR)
                    UCHAR Index : TIMER_EXPIRED_INDEX_BITS;
#else
                    UCHAR Index : 1;
                    UCHAR Processor : TIMER_PROCESSOR_INDEX_BITS;
#endif
                    UCHAR Inserted : 1;
                    volatile UCHAR Expired : 1;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;
        } DUMMYSTRUCTNAME2;
        struct
        {
            UCHAR Timer2Type;
            union
            {
                UCHAR Timer2Flags;
                struct
                {
                    UCHAR Timer2Inserted : 1;
                    UCHAR Timer2Expiring : 1;
                    UCHAR Timer2CancelPending : 1;
                    UCHAR Timer2SetPending : 1;
                    UCHAR Timer2Running : 1;
                    UCHAR Timer2Disabled : 1;
                    UCHAR Timer2ReservedFlags : 2;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;
            UCHAR Timer2Reserved1;
            UCHAR Timer2Reserved2;
        } DUMMYSTRUCTNAME3;
        struct
        {
            UCHAR QueueType;
            union
            {
                UCHAR QueueControlFlags;
                struct
                {
                    UCHAR Abandoned : 1;
                    UCHAR DisableIncrement : 1;
                    UCHAR QueueReservedControlFlags : 6;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;
            UCHAR QueueSize;
            UCHAR QueueReserved;
        } DUMMYSTRUCTNAME4;
        struct
        {
            UCHAR ThreadType;
            UCHAR ThreadReserved;
            union
            {
                UCHAR ThreadControlFlags;
                struct
                {
                    UCHAR CycleProfiling : 1;
                    UCHAR CounterProfiling : 1;
                    UCHAR GroupScheduling : 1;
                    UCHAR AffinitySet : 1;
                    UCHAR Tagged : 1;
                    UCHAR EnergyProfiling: 1;
#if !defined(_X86_)
                    UCHAR ThreadReservedControlFlags : 2;
#else
                    UCHAR Instrumented : 1;
                    UCHAR ThreadReservedControlFlags : 1;
#endif
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;
            union {
                UCHAR DebugActive;
#if !defined(_X86_)
                struct {
                    BOOLEAN ActiveDR7 : 1;
                    BOOLEAN Instrumented : 1;
                    BOOLEAN Minimal : 1;
                    BOOLEAN Reserved4 : 3;
                    BOOLEAN UmsScheduled : 1;
                    BOOLEAN UmsPrimary : 1;
                } DUMMYSTRUCTNAME;

#endif
            } DUMMYUNIONNAME2;
        } DUMMYSTRUCTNAME5;

        struct {
            UCHAR MutantType;
            UCHAR MutantSize;
            BOOLEAN DpcActive;
            UCHAR MutantReserved;
        } DUMMYSTRUCTNAME6;
    } DUMMYUNIONNAME;

    LONG SignalState;
    LIST_ENTRY WaitListHead;
} DISPATCHER_HEADER, *PDISPATCHER_HEADER;
#endif // 0

}; // namespace Ke


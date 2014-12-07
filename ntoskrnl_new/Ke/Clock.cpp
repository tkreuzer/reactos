
#include "Kep.hpp"

typedef struct _KSYSTEM_TIME {
    ULONG LowPart;
    LONG High1Time;
    LONG High2Time;
} KSYSTEM_TIME, *PKSYSTEM_TIME;

extern "C" {

#if defined(_X86_) || defined(_ARM_)
DECLSPEC_CACHEALIGN volatile KSYSTEM_TIME KeTickCount;
#endif

// @ stub KeClockInterruptNotify
// @ stub KeClockTimerPowerChange
// @ stub KeGetClockOwner
// @ stub KeGetClockTimerResolution
// @ stub KeGetNextClockTickDuration

// wdm.h / ntosp.h
_IRQL_requires_same_
ULONG64
NTAPI
KeQueryInterruptTimePrecise (
    _Out_ PULONG64 QpcTimeStamp)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
ULONGLONG
NTAPI
KeQueryUnbiasedInterruptTime (
    VOID)
{
    __debugbreak();
    return 0;
}

// wdm.h / ntosp.h
VOID
NTAPI
KeQuerySystemTimePrecise (
    _Out_ PLARGE_INTEGER CurrentTime)
{
    __debugbreak();
}

// wdm.h / ntosp.h
ULONG
NTAPI
KeQueryTimeIncrement (
    VOID)
{
    __debugbreak();
    return 0;
}


#undef KeQueryTickCount
VOID
NTAPI
KeQueryTickCount (
    _Out_ PLARGE_INTEGER CurrentCount)
{
    __debugbreak();
}

#if defined(_M_IX86) || defined(_M_ARM)
ULONGLONG
NTAPI
KeQueryInterruptTime (
    VOID)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KeQuerySystemTime (
    _Out_ PLARGE_INTEGER CurrentTime)
{
    __debugbreak();
}
#endif // defined(_M_IX86) || defined(_M_ARM)

}; // extern "C"

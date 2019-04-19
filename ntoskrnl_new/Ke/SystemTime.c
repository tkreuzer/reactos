
#include <ntoskrnl.h>
#include "Ke_internal.h"

LARGE_INTEGER KiLastTickPCValue;

#define _Out_

VOID
NTAPI
KeQuerySystemTimePrecise(
    _Out_ PLARGE_INTEGER CurrentTime)
{
    LARGE_INTEGER PerformanceCounter, PerformanceFrequency, TimeDiff;

    /* Query the system time based on the clock interrupt */
    KeQuerySystemTime(CurrentTime);

    /* Query the current performance counter value */
    PerformanceCounter = KeQueryPerformanceCounter(&PerformanceFrequency);

    /* Substract the value of the PC at the last clock interrupt */
    PerformanceCounter.QuadPart -= KiLastTickPCValue.QuadPart;

    /* Calculate the time since the last clock tick in 100 ns intervals */
    TimeDiff.QuadPart = (PerformanceCounter.QuadPart * 10000000) /
                                    PerformanceFrequency.QuadPart;

    /* Add the time since the last clock tick to the result */
    CurrentTime->QuadPart += TimeDiff.QuadPart;
}

ULONG
NTAPI
KeQueryTimeIncrement(void)
{
    __debugbreak();
    return 0;
}


VOID
FASTCALL
KeUpdateSystemTime(
    IN struct _KTRAP_FRAME *TrapFrame,
    IN ULONG Increment,
    IN KIRQL OldIrql)
{

    /* Save the current performance counter value */
    KiLastTickPCValue = KeQueryPerformanceCounter(NULL);

    __debugbreak();
}

VOID
NTAPI
KeUpdateSystemTimeAssist()
{
    __debugbreak();
}

VOID
NTAPI
KeSetTimeIncrement(
    IN ULONG MaxIncrement,
    IN ULONG MinIncrement)
{
    __debugbreak();
}


ULONGLONG
NTAPI
KeQueryUnbiasedInterruptTime(void)
{
    ULONGLONG InterruptTime, InterruptTimeBias;

    do
    {
        /* Get the biased interrupt time */
        InterruptTime = KeQueryInterruptTime();

        /* Get the time bias */
        InterruptTimeBias = SharedUserData->InterruptTimeBias;

        /* Repeat if the time changed */
    } while (InterruptTime != KeQueryInterruptTime());

    /* Return the system time compensated for the bias */
    return InterruptTime - InterruptTimeBias;
}


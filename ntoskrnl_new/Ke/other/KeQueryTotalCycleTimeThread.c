_IRQL_requires_same_
ULONG64
NTAPI
KeQueryTotalCycleTimeThread (
    _In_ PKTHREAD Thread,
    _Out_ PULONG64 CycleTimeStamp)
{
    PKPRCB Prcb;
    ULONG64 StartTime1, StartTime2, CycleTime1, CycleTime2, TimeStamp;

    do
    {
        CycleTime1 = Thread->CycleTime;

        Prcb = KeGetPrcbForThread(Prcb);
        if (Prcb != NULL)
        {
            StartTime1 = Prcb->StartTime;
            TimeStamp = KiReadTimeStampCounter();
            StartTime2 = Prcb->StartTime;
        }
        else
        {
            TimeStamp = KiReadTimeStampCounter();
            StartTime1 = StartTime2 = TimeStamp;
        }

        CycleTime2 = Thread->CycleTime;

    } while ((StartTime1 != StartTime2) || (CycleTime1 != CycleTime2));

    *CycleTimeStamp = TimeStamp;

    return CycleTime1 + (TimeStamp - StartTime1);
}


///

write       ... Read
---------------------------

CycleTime

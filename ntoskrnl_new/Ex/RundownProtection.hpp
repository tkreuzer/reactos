
// Should just use a pushlock!

typedef struct _RUNDOWN_WAIT_BLOCK
{
    ULONG_PTR RundownProtection;
    EVENT Event;
} RUNDOWN_WAIT_BLOCK, *PRUNDOWN_WAIT_BLOCK;

typedef union _RUNDOWN_PROTECTION_VALUE
{
    PVOID Ptr;
    LONG_PTR Long;
    PRUNDOWN_WAIT_BLOCK WaitBlock;
    struct
    {
        ULONG_PTR RundownActive : 1;
        ULONG_PTR RundownProtection : (sizeof(PVOID) * 8) - 1;
    }
} RUNDOWN_PROTECTION_VALUE, *PRUNDOWN_PROTECTION_VALUE;

class RUNDOWN_PROTECTION
{
    RUNDOWN_PROTECTION_VALUE _Value;

public:

    RUNDOWN_PROTECTION (
        VOID)
    {
        _Value.Long = 0;
    }

    BOOLEAN
    Acquire (
        VOID)
    {
        RUNDOWN_PROTECTION_VALUE Value, Compare;

        Value = _Value;
        do
        {
            if (Value.RundownActive)
            {
                return FALSE;
            }

            Compare = Value;
            Value.RundownProtection++;

            Value = InterlockedCompareExchangePointer(&_Value->Ptr,
                                                      Value.Ptr,
                                                      Compare.Ptr);
        } while (Value.Ptr != Compare.Ptr);
    }

    VOID
    Release (
        VOID)
    {
        RUNDOWN_PROTECTION_VALUE Value, Compare;

        Value = _Value;
        do
        {
            if (Value.RundownActive)
            {
                Value.RundownActive = 0;
                if (InterlockedDecrementSizeT(Value.WaitBlock->RundownProtection) == 0)
                {
                    KeSetEvent(&Value.WaitBlock->Event);
                }
                return;
            }

            Compare = Value;
            Value.RundownProtection--;

            Value = InterlockedCompareExchangePointer(&_Value->Ptr,
                                                      Value.Ptr,
                                                      Compare.Ptr);
        } while (Value.Ptr != Compare.Ptr);
    }

    VOID
    Wait (
        VOID)
    {
        RUNDOWN_PROTECTION_VALUE Value, Compare;
        RUNDOWN_WAIT_BLOCK WaitBlock(SynchronizationEvent);

        Value = _Value;
        do
        {
            WaitBlock.RundownProtection = Value.RundownProtection;

            Compare = Value;
            Value.WaitBlock = &WaitBlock;
            Value.RundownActive = 1:

            Value = InterlockedCompareExchangePointer(&_Value->Ptr,
                                                      Value.Ptr,
                                                      Compare.Ptr);
        } while (Value.Ptr != Compare.Ptr);

        WaitBlock.Event.Wait();
    }

    VOID
    Complete (
        VOID)
    {
        _Value.Long = 0;
    }

}

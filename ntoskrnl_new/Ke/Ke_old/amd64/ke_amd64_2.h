


BOOLEAN
FORCEINLINE
KxDisableInterrupts(void)
{
    ULONG64 Eflags = __readeflsg();
    __disable();
    return (Eflags & ELFAGS_INTERRUPT_MASK) != 0;
}


void
FORCEINLINE
KxEnableInterrupts(void)
{
    __enable();
}


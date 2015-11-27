
#pragma once

namespace Cpu {

enum _EFLAGS_BITS
{
    EFLAGS_INTERRUPT_MASK = 0x200,
};

FORCEINLINE
BOOLEAN
AreInterruptsEnabled (
    VOID)
{
    return (__readeflags() & EFLAGS_INTERRUPT_MASK) != 0;
}

FORCEINLINE
BOOLEAN
DisableInterrupts (
    VOID)
{
    ULONG OldEflags;

    /* Get EFLAGS */
    OldEflags = __readeflags();

    /* Disable interrupts */
    _disable();

    /* Return the previous enabled state */
    return (OldEflags & EFLAGS_INTERRUPT_MASK) != 0;
}

FORCEINLINE
VOID
RestoreInterrupts (
    _In_ BOOLEAN WasEnabled)
{
    if (WasEnabled)
    {
        _enable();
    }
}

}; // namespace Cpu


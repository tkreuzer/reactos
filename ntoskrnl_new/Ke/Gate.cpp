
#include "Kep.hpp"
#include "Gate.hpp"

FORCEINLINE
PLIST_ENTRY
RemoveHeadListUnsafe (
    _Inout_ PLIST_ENTRY ListHead)
{
    PLIST_ENTRY Flink, Entry;

    Entry = ListHead->Flink;
    Flink = Entry->Flink;
    ListHead->Flink = Flink;
    Flink->Blink = ListHead;

    return Entry;
}

namespace Ke {

VOID
GATE::Wait (
    VOID)
{
    /* Check if the gate is signaled */
    if (_Header.SignalState > 0)
    {
        /* Set the signal state to 0 */
        if (InterlockedBitTestAndReset(_Header.SignalState, 0) != 0)
        {
            return;
        }

    }

    SignalState = _Header.SignalState;

    do
    {
        /* Check if the gate is signaled */
        if (SignalState != 0)
        {
            NT_ASSERT(SignalState == 1);

            if (InterlockedCompareExchange(&_Header.SignalState, 0, 1) == 1)
            {
                return;
            }
        }

        InterlockedInsertTailWaitList();

        if (_Header.SignalState != 0)
        {
        }
    }
}

VOID
GATE::Signal (
    VOID)
{
    BOOLEAN Enabled;
    PLIST_ENTRY ListEntry;

    /* Check if the gate is already signaled */
    if (_Header.SignalState > 0)
    {
        /* Nothing to do! */
        return;
    }


    Enabled = Cpu::DisableInterrupts();
    AcquireLock();


    if (_Header.SignalState == 0)
    {

        ListEntry = RemoveHeadListUnsafe(&_Header.WaitListHead);

        if (ListEntry->Flink == &_Header.WaitListHead)
        {
            _Header.SignalState = 1;
        }
    }

    ReleaseLock();
    Cpu::RestoreInterrupts(Enabled);

    if (ListEntry != &_Header.WaitListHead)
    {
        WaitBlock = CONTAINING_RECORD(ListEntry, WAIT_BLOCK, WaitListEntry);

        NT_ASSERT(WaitBlock->WaitType == GateWate);
        NT_ASSERT(WaitBlock->BlockState == WaitBlockActive);
        NT_ASSERT(WaitBlock->WaitKey == 0);

    }

}






}; // namespace Ke

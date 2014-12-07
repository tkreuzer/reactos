
#include "Mmp.hpp"

extern "C" {

//@ stdcall -stub MmTrimAllSystemPagableMemory(long)

NTSTATUS
NTAPI
MmAdjustWorkingSetSize (
    _In_ SIZE_T WorkingSetMinimum,
    _In_ SIZE_T WorkingSetMaximum,
    _In_ ULONG SystemCache,
    _In_ BOOLEAN IncreaseOkay)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"

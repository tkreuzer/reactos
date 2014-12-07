
#include "Po.hpp"

extern "C" {

//@ stdcall -stub PoRegisterDeviceNotify(ptr long long long ptr ptr)
//@ stdcall -stub PoCancelDeviceNotify(ptr)

// ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FASTCALL
PoNotifyMediaBuffering (
    _In_ BOOLEAN Engaged)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_not_held_(PopFxSystemLatencyLock)
VOID
FASTCALL
PoNotifyVSyncChange (
    _In_ BOOLEAN Enable)
{
    __debugbreak();
}


} // extern "C"

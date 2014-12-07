
#include "Po.hpp"
#include <Ex/Ex.hpp>

extern "C" {

//@ stdcall -stub PoShutdownBugCheck(long long ptr ptr ptr ptr)

// ntosp.h
typedef
_Function_class_(POSHUTDOWNNOTIFICATIONFUNC)
VOID
NTAPI
POSHUTDOWNNOTIFICATIONFUNC (
    _Inout_opt_ PVOID Context);
typedef POSHUTDOWNNOTIFICATIONFUNC *PPOSHUTDOWNNOTIFICATIONFUNC;

// ntosp.h
typedef struct _PO_SHUTDOWN_NOTIFICATION
{
    PPOSHUTDOWNNOTIFICATIONFUNC Callback;
    PVOID Context;
} PO_SHUTDOWN_NOTIFICATION, *PPO_SHUTDOWN_NOTIFICATION;

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PoUserShutdownInitiated (
    VOID)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
PoUserShutdownCancelled (
    VOID)
{
    __debugbreak();
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PoQueueShutdownWorkItem(
    _Inout_ __drv_aliasesMem PWORK_QUEUE_ITEM WorkItem)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
NTAPI
PoRequestShutdownEvent(
    _Outptr_opt_ PVOID *Event)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"

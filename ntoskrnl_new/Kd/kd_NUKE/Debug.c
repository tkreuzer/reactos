
#include <ntoskrnl.h>

UCHAR DbgChannelConfig[DbgChannelMaximum];

typedef
void
(__cdecl *PDEBUGPRINT_CALLBACK_FUNCTION)(
    IN PANSI_STRING String,
    IN ULONG ComponentId,
    IN ULONG Level);

NTSTATUS
NTAPI
DbgSetDebugPrintCallback(
    PDEBUGPRINT_CALLBACK_FUNCTION Function,
    BOOLEAN Mode)
{
    __debugbreak();
    return 0;
}

/* Live kernel memory dump */

typedef struct _LKMD_INFORMATION *PLKMD_INFORMATION;

typedef
NTSTATUS
(NTAPI *PLKMD_CALLBACK)(
    PVOID DbgkpLkmdSnapDataRoutine,
    PVOID DbgkpLkmdIsMemoryBlockPresentFromCallbackRoutine,
    PLKMD_INFORMATION LkmdInformation,
    PVOID Context);

NTSTATUS
NTAPI
DbgkLkmdRegisterCallback(
    PLKMD_CALLBACK CallBack,
    PVOID Context,
    ULONG CallbackType)
{
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
DbgkLkmdUnregisterCallback(
    PLKMD_CALLBACK CallBack)
{
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
DbgkpLkmdFireCallbacks(
    PLKMD_INFORMATION LkmdInfomation,
    ULONG CallbackType,
    PVOID ProcessOrThreadObject);

NTSTATUS
NTAPI
NtQueryDebugFilterState(
    ULONG  	ComponentId,
    ULONG  	Level)
{
    UNIMPLEMENTED;
    __debugbreak();
    return 0;
}

NTSTATUS
NTAPI
NtSetDebugFilterState(IN ULONG ComponentId,
                      IN ULONG Level,
                      IN BOOLEAN State)
{
    UNIMPLEMENTED;
    __debugbreak();
    return 0;
}


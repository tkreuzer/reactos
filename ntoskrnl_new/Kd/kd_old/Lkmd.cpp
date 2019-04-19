
#include <ntbase.h>
#include <ntstatus.h>


/* Live kernel memory dump */

typedef struct _LKMD_INFORMATION *PLKMD_INFORMATION;

typedef
NTSTATUS
(NTAPI *PLKMD_CALLBACK) (
    PVOID DbgkpLkmdSnapDataRoutine,
    PVOID DbgkpLkmdIsMemoryBlockPresentFromCallbackRoutine,
    PLKMD_INFORMATION LkmdInformation,
    PVOID Context);

NTSTATUS
NTAPI
DbgkLkmdRegisterCallback (
    PLKMD_CALLBACK CallBack,
    PVOID Context,
    ULONG CallbackType)
{
    (void)CallBack;
    (void)Context;
    (void)CallbackType;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
DbgkLkmdUnregisterCallback (
    PLKMD_CALLBACK CallBack)
{
    (void)CallBack;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}



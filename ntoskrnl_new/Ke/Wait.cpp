
#include "Wait.hpp"

extern "C" {

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
BOOLEAN
NTAPI
KeIsWaitListEmpty (
    _In_ PVOID Object)
{
    __debugbreak();
    return FALSE;
}

// wdm.h / ntosp.h
_When_((Timeout==NULL || Timeout->QuadPart!=0), _IRQL_requires_max_(APC_LEVEL))
_When_((Timeout!=NULL && Timeout->QuadPart==0), _IRQL_requires_max_(DISPATCH_LEVEL))
NTSTATUS
NTAPI
KeWaitForMultipleObjects (
    _In_ ULONG Count,
    _In_reads_(Count) PVOID Object[],
    _In_ _Strict_type_match_ WAIT_TYPE WaitType,
    _In_ _Strict_type_match_ KWAIT_REASON WaitReason,
    _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst) KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_opt_ PKWAIT_BLOCK WaitBlockArray)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


// wdm.h / ntosp.h
_When_((Timeout==NULL || Timeout->QuadPart!=0), _IRQL_requires_max_(APC_LEVEL))
_When_((Timeout!=NULL && Timeout->QuadPart==0), _IRQL_requires_max_(DISPATCH_LEVEL))
NTSTATUS
NTAPI
KeWaitForSingleObject (
    _In_ _Points_to_data_ PVOID Object,
    _In_ _Strict_type_match_ KWAIT_REASON WaitReason,
    _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst) KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"

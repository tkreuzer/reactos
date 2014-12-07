
#include <Vf.hpp>

typedef struct _DEVICE_OBJECT *PDEVICE_OBJECT;

extern "C" {

// vffailure.h
LOGICAL
NTAPI
VfIsVerificationEnabled (
    _In_ VF_OBJECT_TYPE VfObjectType,
    _In_opt_ PVOID Object)
{
    __debugbreak();
    return FALSE;
}

// vffailure.h
VOID
__cdecl
VfFailDeviceNode (
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _In_ ULONG BugCheckMajorCode,
    _In_ ULONG BugCheckMinorCode,
    _In_ VF_FAILURE_CLASS FailureClass,
    _Inout_ PULONG AssertionControl,
    _In_ PSTR DebuggerMessageText,
    _In_ PSTR ParameterFormatString,
    ...)
{
    __debugbreak();
}

// vffailure.h
VOID
__cdecl
VfFailSystemBIOS (
    _In_ ULONG BugCheckMajorCode,
    _In_ ULONG BugCheckMinorCode,
    _In_ VF_FAILURE_CLASS FailureClass,
    _Inout_ PULONG AssertionControl,
    _In_ PSTR DebuggerMessageText,
    _In_ PSTR ParameterFormatString,
    ...)
{
    __debugbreak();
}

VOID
NTAPI
VfFailDriver (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfCheckNxPagePriority (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfCheckNxPageProtection (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfCheckNxPoolType (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfInsertContext (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfQueryDeviceContext (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfQueryDispatchTable (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfQueryDriverContext (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfQueryIrpContext (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfQueryThreadContext (
    VOID)
{
    __debugbreak();
}

VOID
NTAPI
VfRemoveContext (
    VOID)
{
    __debugbreak();
}

}; // extern "C"

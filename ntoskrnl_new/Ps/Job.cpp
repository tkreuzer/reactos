
#include "Job.hpp"
#include <Ob/Ob.hpp>

extern "C" {

POBJECT_TYPE PsJobType;

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
ULONG
NTAPI
PsGetJobSessionId (
    _In_ PEJOB Job)
{
    __debugbreak();
    return 0;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
PERESOURCE
NTAPI
PsGetJobLock (
    _In_ PEJOB Job)
{
    __debugbreak();
    return NULL;
}

// ntosp.h
_IRQL_requires_max_(APC_LEVEL)
ULONG
NTAPI
PsGetJobUIRestrictionsClass (
    _In_ PEJOB Job)
{
    __debugbreak();
    return 0;
}

#if 0 // internal? from ntosp.h
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PVOID
PsGetJobProperty(
    _In_ PEJOB Thread,
    _In_ ULONG_PTR Key);

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
ULONG
PsGetJobEffectiveFreezeCount(
    _In_ PEJOB Job);

#endif // 0

} // extern "C"

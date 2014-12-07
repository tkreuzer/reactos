
#include "Mmp.hpp"

extern "C" {

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
__drv_reportError("Caution: MmSecureVirtualMemory ensures the specified VA "
	"range protections cannot be tightened - but accesses to the memory can "
	"still fail and so they must be protected by try-except.")
HANDLE
NTAPI
MmSecureVirtualMemory (
    __in_data_source(USER_MODE) _In_reads_bytes_ (Size) PVOID Address,
    _In_  __in_data_source(USER_MODE) SIZE_T Size,
    _In_ ULONG ProbeMode)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmUnsecureVirtualMemory (
    _In_ HANDLE SecureHandle)
{
    __debugbreak();
}

}; // extern "C"

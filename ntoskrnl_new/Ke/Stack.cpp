
#include "Kep.hpp"

extern "C" {

// ntifs.h
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
BOOLEAN
NTAPI
KeSetKernelStackSwapEnable (
    _In_ BOOLEAN Enable)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"

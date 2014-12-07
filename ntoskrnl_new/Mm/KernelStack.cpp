
#include "Mmp.hpp"

extern "C" {

// not documented
NTSTATUS
NTAPI
MmGrowKernelStack (
    PVOID P)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"

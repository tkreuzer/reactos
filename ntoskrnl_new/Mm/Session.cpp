
#include "Mmp.hpp"

extern "C" {

typedef struct _EPROCESS *PEPROCESS;

// not documented, internal
ULONG
NTAPI
MmGetSessionId (
    _In_ PEPROCESS Process)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"

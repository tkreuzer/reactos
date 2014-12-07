
#include "Mmp.hpp"

extern "C" {

// ntifs.h
BOOLEAN
NTAPI
MmIsRecursiveIoFault (
    VOID)
{
    __debugbreak();
    return FALSE;
}

}; // extern "C"

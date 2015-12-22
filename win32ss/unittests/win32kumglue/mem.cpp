
#include <win32k.h>

_Must_inspect_result_
_When_(fl & FL_ZERO_MEMORY, _Ret_opt_bytecount_(cjMemSize))
_When_(!(fl & FL_ZERO_MEMORY), _Ret_opt_bytecap_(cjMemSize))
__drv_allocatesMem(Mem)
ENGAPI
PVOID
APIENTRY
EngAllocMem(
    _In_ ULONG fl,
    _In_ ULONG cjMemSize,
    _In_ ULONG ulTag)
{
    PVOID pvBuffer = malloc(cjMemSize);

    if (pvBuffer != NULL)
    {
        if (fl & FL_ZERO_MEMORY)
        {
            memset(pvBuffer, 0, cjMemSize);
        }
    }

    return pvBuffer;
}

VOID
APIENTRY
EngFreeMem(PVOID pvBaseAddress)
{
    /* Windows allows to pass NULL */
    if (pvBaseAddress)
    {
        /* Use 0 as tag, which equals a call to ExFreePool */
        free(pvBaseAddress);
    }
}

_Must_inspect_result_
_Ret_opt_bytecount_(cjMemSize)
__drv_allocatesMem(UserMem)
ENGAPI
PVOID
APIENTRY
EngAllocUserMem(
    _In_ SIZE_T cjMemSize,
    _In_ ULONG ulTag)
{
    return malloc(cjMemSize);
}

VOID
APIENTRY
EngFreeUserMem(PVOID pvBaseAddress)
{
    free(pvBaseAddress);
}

PVOID
APIENTRY
HackSecureVirtualMemory(
    IN PVOID Address,
    IN SIZE_T Size,
    IN ULONG ProbeMode,
    OUT PVOID *SafeAddress)
{
    return (PVOID)-1;
}

VOID
APIENTRY
HackUnsecureVirtualMemory(
    IN PVOID  SecureHandle)
{

}

HANDLE
APIENTRY
EngSecureMem(PVOID Address, ULONG Length)
{
    return (HANDLE)-1;
}

HANDLE
APIENTRY
EngSecureMemForRead(PVOID Address, ULONG Length)
{
    return (HANDLE)-1;
}

VOID
APIENTRY
EngUnsecureMem(HANDLE Mem)
{

}

/* EOF */


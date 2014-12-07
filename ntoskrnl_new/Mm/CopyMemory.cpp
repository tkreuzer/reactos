
#include "Mmp.hpp"
#include <Ke/Ke.hpp>

extern "C" {

typedef struct _EPROCESS *PEPROCESS;

typedef struct _MM_COPY_ADDRESS
{
    union {
        PVOID VirtualAddress;
        PHYSICAL_ADDRESS PhysicalAddress;
    };
} MM_COPY_ADDRESS, *PMMCOPY_ADDRESS;

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmCopyMemory (
    _In_ PVOID TargetAddress,
    _In_ MM_COPY_ADDRESS SourceAddress,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Flags,
    _Out_ PSIZE_T NumberOfBytesTransferred)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmCopyVirtualMemory (
    _In_ PEPROCESS FromProcess,
    _In_ CONST VOID *FromAddress,
    _In_ PEPROCESS ToProcess,
    _Out_opt_ PVOID ToAddress,
    _In_ SIZE_T BufferSize,
    _In_ KPROCESSOR_MODE PreviousMode,
    _Out_ PSIZE_T NumberOfBytesCopied)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;;
}


}; // extern "C"

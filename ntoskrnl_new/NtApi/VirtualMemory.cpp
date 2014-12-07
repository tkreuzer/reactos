
#include <ntoskrnl.h>

extern "C" {

typedef struct _IO_STATUS_BLOCK *PIO_STATUS_BLOCK;

// ntifs.h
typedef enum _MEMORY_INFORMATION_CLASS
{
    MemoryBasicInformation
} MEMORY_INFORMATION_CLASS;

_Must_inspect_result_
__drv_allocatesMem(Mem)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_ (*BaseAddress, _Readable_bytes_ (*RegionSize) _Writable_bytes_ (*RegionSize) _Post_readable_byte_size_ (*RegionSize)) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreeVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ __drv_freesMem(Mem) PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG FreeType)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(APC_LEVEL)
__kernel_entry
NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _Out_ PIO_STATUS_BLOCK IoStatus)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://www.brandonfa.lk/win8/win8_devrel_head_x86/windows.web.h
struct _WIN32_MEMORY_RANGE_ENTRY
{
    void *VirtualAddress; /*  +0x0000  */
    unsigned long  NumberOfBytes; /*  +0x0004  */
};

// correct?
typedef _WIN32_MEMORY_RANGE_ENTRY *PMEMORY_RANGE_ENTRY;

typedef enum _VIRTUAL_MEMORY_INFORMATION_CLASS
{
    VmPrefetchInformation, // ???
} VIRTUAL_MEMORY_INFORMATION_CLASS, *PVIRTUAL_MEMORY_INFORMATION_CLASS;

// https://msdn.microsoft.com/en-US/mt629134.aspx
_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtSetInformationVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_ VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
    _In_ ULONG_PTR NumberOfEntries,
    _In_reads_ (NumberOfEntries) PMEMORY_RANGE_ENTRY VirtualAddresses,
    _In_reads_bytes_ (VmInformationLength) PVOID VmInformation,
    _In_ ULONG VmInformationLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID Address,
    _In_ enum _MEMORY_INFORMATION_CLASS VirtualMemoryInformationClass,
    _Out_ PVOID VirtualMemoryInformation,
    _In_ SIZE_T Length,
    _Out_opt_ PSIZE_T ResultLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtProtectVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG NewProtect,
    _Out_ PULONG OldProtect)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtLockVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtUnlockVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID *BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
__kernel_entry
NTSTATUS
NTAPI
NtReadVirtualMemory (
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_ (BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesRead)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtWriteVirtualMemory(
    IN HANDLE ProcessHandle,
    IN PVOID BaseAddress,
    IN PVOID Buffer,
    IN SIZE_T NumberOfBytesToWrite,
    OUT PSIZE_T NumberOfBytesWritten)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"


#include <Io/Io.hpp>
#include <Se/Se.hpp>

extern "C" {

// wdm.h
typedef struct _FILE_BASIC_INFORMATION
{
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    ULONG FileAttributes;
} FILE_BASIC_INFORMATION, *PFILE_BASIC_INFORMATION;

__kernel_entry
NTSTATUS
NTAPI
NtCreateFile (
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_opt_ PLARGE_INTEGER AllocationSize,
    _In_ ULONG FileAttributes,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_reads_bytes_opt_(EaLength) PVOID EaBuffer,
    _In_ ULONG EaLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCreateMailslotFile (
    _Out_ PHANDLE FileHandle,
    _In_ ULONG DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CreateOptions,
    _In_ ULONG MailslotQuota,
    _In_ ULONG MaximumMessageSize,
    _In_ PLARGE_INTEGER ReadTimeout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCreateNamedPipeFile (
    _Out_ PHANDLE FileHandle,
    _In_ ULONG DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG CreateDisposition,
    _In_ ULONG CreateOptions,
    _In_ ULONG NamedPipeType,
    _In_ ULONG ReadMode,
    _In_ ULONG CompletionMode,
    _In_ ULONG MaximumInstances,
    _In_ ULONG InboundQuota,
    _In_ ULONG OutboundQuota,
    _In_opt_ PLARGE_INTEGER DefaultTimeout)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCreatePagingFile (
    _In_ PUNICODE_STRING PageFileName,
    _In_ PLARGE_INTEGER MinimumSize,
    _In_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtOpenFile (
    _Out_ PHANDLE FileHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG ShareAccess,
    _In_ ULONG OpenOptions)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtDeleteFile(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtReadFile (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtWriteFile (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCancelIoFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtLockFile (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PLARGE_INTEGER ByteOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ ULONG Key,
    _In_ BOOLEAN FailImmediately,
    _In_ BOOLEAN ExclusiveLock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtUnlockFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ PLARGE_INTEGER ByteOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ ULONG Key)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryInformationFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetInformationFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryVolumeInformationFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FsInformation,
    _In_ ULONG Length,
    _In_ FS_INFORMATION_CLASS FsInformationClass)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetVolumeInformationFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID FsInformation,
    _In_ ULONG Length,
    _In_ FS_INFORMATION_CLASS FsInformationClass)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryQuotaInformationFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_reads_bytes_opt_(SidListLength) PVOID SidList,
    _In_ ULONG SidListLength,
    _In_reads_bytes_opt_((8 + (4 * ((SID *)StartSid)->SubAuthorityCount)))
        PSID StartSid,
    _In_ BOOLEAN RestartScan)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtSetQuotaInformationFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryAttributesFile (
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PFILE_BASIC_INFORMATION FileInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtQueryFullAttributesFile(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Out_ PFILE_NETWORK_OPEN_INFORMATION FileInformation)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtQueryEaFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_reads_bytes_opt_(EaListLength) PVOID EaList,
    _In_ ULONG EaListLength,
    _In_opt_ PULONG EaIndex,
    _In_ BOOLEAN RestartScan)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry
NTSTATUS
NTAPI
NtSetEaFile (
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtQueryDirectoryFile (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_writes_bytes_(Length) PVOID FileInformation,
    _In_ ULONG Length,
    _In_ FILE_INFORMATION_CLASS FileInformationClass,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_opt_ PUNICODE_STRING FileName,
    _In_ BOOLEAN RestartScan)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NtFlushBuffersFile(
    _In_ HANDLE FileHandle,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtFlushBuffersFileEx (
    _In_ HANDLE FileHandle,
    _In_ ULONG Flags,
    _In_reads_bytes_(ParametersSize) PVOID Parameters,
    _In_ ULONG ParametersSize,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtNotifyChangeDirectoryFile (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _Out_ PVOID Buffer,
    _In_ ULONG BufferSize,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCancelSynchronousIoFile (
    _In_ HANDLE ThreadHandle,
    _In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtCancelIoFileEx (
    _In_ HANDLE FileHandle,
    _In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtDeviceIoControlFile (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG IoControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

__kernel_entry
NTSTATUS
NTAPI
NtFsControlFile (
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG FsControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}


}; // extern "C"

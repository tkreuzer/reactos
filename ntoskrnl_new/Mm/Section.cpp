
#include "Mmp.hpp"
#include "Mdl.hpp"

extern "C" {

typedef struct _EPROCESS *PEPROCESS;
typedef struct _OBJECT_TYPE *POBJECT_TYPE;
typedef struct _FILE_OBJECT *PFILE_OBJECT;
typedef struct _SECTION_OBJECT_POINTERS *PSECTION_OBJECT_POINTERS;

// wdm.h
typedef enum _SECTION_INHERIT
{
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

// ntifs.h
typedef enum _MMFLUSH_TYPE
{
    MmFlushForDelete,
    MmFlushForWrite
} MMFLUSH_TYPE;

typedef
VOID
(NTAPI *PBANKED_SECTION_ROUTINE) (
    _In_ ULONG ReadBank,
    _In_ ULONG WriteBank,
    _In_ PVOID Context
    );

POBJECT_TYPE MmSectionObjectType;

//@ stdcall -stub MmDisableModifiedWriteOfSection(long)
//@ stdcall -stub MmLockPagableImageSection(ptr)

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmCreateSection (
    _Outptr_ PVOID *SectionObject,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle,
    _In_opt_ PFILE_OBJECT File)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmFlushImageSection (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_ MMFLUSH_TYPE FlushType)
{
    __debugbreak();
    return FALSE;
}

// ntifs.h
_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmForceSectionClosed (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_ BOOLEAN DelayClose)
{
    __debugbreak();
    return FALSE;
}

// ntifs.h
_IRQL_requires_max_ (APC_LEVEL)
ULONGLONG
NTAPI
MmGetMaximumFileSectionSize (
    VOID)
{
    __debugbreak();
    return 0;
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
PVOID
NTAPI
MmLockPagableDataSection (
    _In_ PVOID AddressWithinSection)
{
    __debugbreak();
    return NULL;
}

_IRQL_requires_max_(APC_LEVEL)
VOID
NTAPI
MmLockPagableSectionByHandle (
    _In_ PVOID ImageSectionHandle)
{
    __debugbreak();
}

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
NTAPI
MmUnlockPagableImageSection (
    _In_ PVOID ImageSectionHandle)
{
    __debugbreak();
}

_Must_inspect_result_
_Post_satisfies_ (*CapturedViewSize >= _Old_(*CapturedViewSize))
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmMapViewOfSection (
    _In_ PVOID SectionToMap,
    _In_ PEPROCESS Process,
    _Inout_ _At_(*CapturedBase,
                   _Pre_readable_byte_size_(*CapturedViewSize)
                   _Post_readable_byte_size_(*CapturedViewSize))
         PVOID *CapturedBase,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T CapturedViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmUnmapViewOfSection (
    _In_ PEPROCESS Process,
    _In_opt_ PVOID BaseAddress)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmMapViewInSystemSpace (
    _In_ PVOID Section,
    _Outptr_result_bytebuffer_ (*ViewSize) PVOID *MappedBase,
    _Inout_ PSIZE_T ViewSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmMapViewInSystemSpaceEx (
    _In_ PVOID Section,
    _Outptr_result_bytebuffer_ (*ViewSize) PVOID *MappedBase,
    _Inout_ PSIZE_T ViewSize,
    _Inout_ PLARGE_INTEGER SectionOffset,
    _In_ ULONG_PTR Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmUnmapViewInSystemSpace (
    _In_ PVOID MappedBase)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmMapViewInSessionSpace (
    _In_ PVOID Section,
    _Outptr_result_bytebuffer_ (*ViewSize) PVOID *MappedBase,
    _Inout_ PSIZE_T ViewSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmMapViewInSessionSpaceEx (
    _In_ PVOID Section,
    _Outptr_result_bytebuffer_ (*ViewSize) PVOID *MappedBase,
    _Inout_ PSIZE_T ViewSize,
    _Inout_ PLARGE_INTEGER SectionOffset,
    _In_ ULONG_PTR Flags)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmUnmapViewInSessionSpace (
    _In_ PVOID MappedBase)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmSetBankedSection (
    _In_ HANDLE ProcessHandle,
    _In_reads_bytes_ (BankLength) PVOID VirtualAddress,
    _In_ ULONG BankLength,
    _In_ BOOLEAN ReadWriteBank,
    _In_ PBANKED_SECTION_ROUTINE BankRoutine,
    _In_ PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmCommitSessionMappedView (
    _In_reads_bytes_ (ViewSize) PVOID MappedAddress,
    _In_ SIZE_T ViewSize)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// ntifs.h
_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmCanFileBeTruncated (
    _In_ PSECTION_OBJECT_POINTERS SectionPointer,
    _In_opt_ PLARGE_INTEGER NewFileSize)
{
    __debugbreak();
    return FALSE;
}

_IRQL_requires_max_ (APC_LEVEL)
ULONG
NTAPI
MmDoesFileHaveUserWritableReferences (
    _In_ PSECTION_OBJECT_POINTERS SectionPointer)
{
    __debugbreak();
    return 0;
}

typedef enum _MM_ROTATE_DIRECTION
{
    MmToFrameBuffer,
    MmToFrameBufferNoCopy,
    MmToRegularMemory,
    MmToRegularMemoryNoCopy,
    MmMaximumRotateDirection
} MM_ROTATE_DIRECTION, *PMM_ROTATE_DIRECTION;

typedef struct _PHYSICAL_MEMORY_RANGE
{
    PHYSICAL_ADDRESS BaseAddress;
    LARGE_INTEGER NumberOfBytes;
} PHYSICAL_MEMORY_RANGE, *PPHYSICAL_MEMORY_RANGE;

typedef
NTSTATUS
(NTAPI *PMM_ROTATE_COPY_CALLBACK_FUNCTION) (
    _In_ PMDL DestinationMdl,
    _In_ PMDL SourceMdl,
    _In_ PVOID Context);

_Must_inspect_result_
_IRQL_requires_max_ (APC_LEVEL)
NTSTATUS
NTAPI
MmRotatePhysicalView (
    _In_ PVOID VirtualAddress,
    _Inout_ PSIZE_T NumberOfBytes,
    _In_opt_ PMDL NewMdl,
    _In_ MM_ROTATE_DIRECTION Direction,
    _In_ PMM_ROTATE_COPY_CALLBACK_FUNCTION CopyFunction,
    _In_opt_ PVOID Context)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

}; // extern "C"


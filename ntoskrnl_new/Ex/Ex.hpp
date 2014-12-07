
#pragma once

#include "ntoskrnl.h"

#undef EX_PUSH_LOCK
#undef PEX_PUSH_LOCK
typedef ULONG_PTR ERESOURCE_THREAD, *PERESOURCE_THREAD;
typedef struct _ERESOURCE *PERESOURCE;
typedef ULONG_PTR EX_PUSH_LOCK, *PEX_PUSH_LOCK;

extern "C" {

typedef struct _FAST_MUTEX *PFAST_MUTEX;
typedef struct _EX_RUNDOWN_REF *PEX_RUNDOWN_REF;
typedef struct _EX_RUNDOWN_REF_CACHE_AWARE *PEX_RUNDOWN_REF_CACHE_AWARE;
typedef struct _ZONE_HEADER *PZONE_HEADER;
typedef struct _EPROCESS *PEPROCESS;

typedef enum _POOL_TYPE
{
  NonPagedPool,
  PagedPool,
  NonPagedPoolMustSucceed,
  DontUseThisType,
  NonPagedPoolCacheAligned,
  PagedPoolCacheAligned,
  NonPagedPoolCacheAlignedMustS,
  MaxPoolType,
  NonPagedPoolSession = 32,
  PagedPoolSession,
  NonPagedPoolMustSucceedSession,
  DontUseThisTypeSession,
  NonPagedPoolCacheAlignedSession,
  PagedPoolCacheAlignedSession,
  NonPagedPoolCacheAlignedMustSSession
} POOL_TYPE;

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
_IRQL_requires_same_
_Function_class_(WORKER_THREAD_ROUTINE)
VOID
NTAPI
WORKER_THREAD_ROUTINE (
    _In_ PVOID Parameter);
typedef WORKER_THREAD_ROUTINE *PWORKER_THREAD_ROUTINE;

typedef struct _WORK_QUEUE_ITEM
{
    LIST_ENTRY List;
    PWORKER_THREAD_ROUTINE WorkerRoutine;
    __volatile PVOID Parameter;
} WORK_QUEUE_ITEM, *PWORK_QUEUE_ITEM;

__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) == 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) != 0,
       _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
NTKERNELAPI
PVOID
NTAPI
ExAllocatePoolWithTag (
    _In_ __drv_strictTypeMatch(__drv_typeExpr) POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag);

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
ExFreePool (
    _Pre_notnull_ __drv_freesMem(Mem) PVOID P);

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
ExFreePoolWithTag (
    _Pre_notnull_ __drv_freesMem(Mem) PVOID P,
    _In_ ULONG Tag);

__drv_preferredFunction("lookaside lists instead", "Obsolete")
DECLSPEC_DEPRECATED_DDK
NTKERNELAPI
NTSTATUS
NTAPI
ExExtendZone (
    _Inout_ PZONE_HEADER Zone,
    _Inout_ PVOID Segment,
    _In_ ULONG SegmentSize);

_IRQL_raises_(APC_LEVEL)
_IRQL_saves_global_(OldIrql, FastMutex)
NTKERNELAPI
VOID
FASTCALL
ExAcquireFastMutex (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PFAST_MUTEX FastMutex);

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExAcquireFastMutexUnsafe (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
        PFAST_MUTEX FastMutex);

_Must_inspect_result_
_Post_satisfies_(return==0 || return==1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExAcquireRundownProtection (
    _Inout_ PEX_RUNDOWN_REF RunRef);

_Must_inspect_result_
_Post_satisfies_(return==0 || return==1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExAcquireRundownProtectionCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware);

_Must_inspect_result_
_Post_satisfies_(return==0 || return==1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExAcquireRundownProtectionCacheAwareEx (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware,
    _In_ ULONG Count);

_Must_inspect_result_
_Post_satisfies_(return==0 || return==1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExAcquireRundownProtectionEx (
    _Inout_ PEX_RUNDOWN_REF RunRef,
    _In_ ULONG Count);

NTKERNELAPI
VOID
FASTCALL
ExInitializeRundownProtection (
    _Out_ PEX_RUNDOWN_REF RunRef);

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("ExAllocatePoolWithTag", "No tag interferes with debugging.")
__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) == 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) != 0,
       _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
NTKERNELAPI
PVOID
ExAllocatePool (
    __drv_strictTypeMatch(__drv_typeExpr) _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes);

// reactos: ntddk_ex.h
// http://dennisdarland.com/my_sw_projects/doxy/NARS2000_APL/html/d2/dc3/winternl_8h_source.html#l02360
// https://github.com/subTee/dementia-forensics/blob/master/Common/WinternalStructures.h
// http://alter.org.ua/docs/nt_kernel/procaddr/
typedef struct _SYSTEM_MODULE_ENTRY
{
    ULONG Unused;
    ULONG Always0;
    PVOID ModuleBaseAddress;
    ULONG ModuleSize;
    ULONG Unknown;
    ULONG ModuleEntryIndex;
    USHORT ModuleNameLength;
    USHORT ModuleNameOffset;
    CHAR ModuleName[256];
} SYSTEM_MODULE_ENTRY, * PSYSTEM_MODULE_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION
{
    ULONG Count;
    SYSTEM_MODULE_ENTRY Module[1];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

};

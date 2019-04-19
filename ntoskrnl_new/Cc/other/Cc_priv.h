
#pragma once

/* Hacks! */
#define KeNumberProcessors _KeNumberProcessors
#define IoFileObjectType _IoFileObjectType
#define PsProcessType _PsProcessType
#define KeEnterCriticalRegion _KeEnterCriticalRegion
#define KeLeaveCriticalRegion _KeLeaveCriticalRegion
#define KeEnterGuardedRegion _KeEnterGuardedRegion
#define KeLeaveGuardedRegion _KeLeaveGuardedRegion
#ifdef _M_AMD64
#define KeGetCurrentThread _KeGetCurrentThread
#endif

#include <ntifs.h>
//#include <pseh/pseh2.h>

#define ExAcquirePushLockExclusive ExfAcquirePushLockExclusive
#define ExReleasePushLock ExfReleasePushLock

/* Macro expansion helpers */
#define _EXPAND2_(x) x
#define _EXPAND_(x) _EXPAND2_(x)
#define _STREXPAND2_(x) #x
#define _STREXPAND_(x) _STREXPAND2_(x)

/* Access to architecture relative headers */
#ifdef _M_IX86
#undef i386
#define _ARCH_RELATIVE_(_file) _STREXPAND_(i386/_file)
#elif defined(_M_AMD64)
#define _ARCH_RELATIVE_(_file) _STREXPAND_(amd64/_file)
#endif

/* Useful helper macros */
#define AddToPointer(Ptr, Offset) ((PVOID)(((PUCHAR)(Ptr)) + (Offset)))
#define PointerDiff(Address1, Address2) ((PUCHAR)Address2 - (PUCHAR)Address1)
#define MinPtr(Ptr1, Ptr2) ((((ULONG_PTR)(Ptr1)) < ((ULONG_PTR)(Ptr2))) ? (Ptr1) : (Ptr2))
#define AddressToVpn(Address) (((ULONG_PTR)(Address)) >> PAGE_SHIFT)
#define VpnToAddress(Vpn)  ((PVOID)((Vpn) << PAGE_SHIFT))
#define SetPointerMask(_Pointer, _Mask) \
    ((PVOID)(((ULONG_PTR)(_Pointer)) | ((ULONG_PTR)(_Mask))))

#define ClearPointerMask(_Pointer, _Mask) \
    ((PVOID)(((ULONG_PTR)(_Pointer)) & ~((ULONG_PTR)(_Mask))))


/* Debug macros */
#define UNIMPLEMENTED DbgPrint("(%s:%d) WARNING: %s is UNIMPLEMENTED!\n", __FILE__, __LINE__, __FUNCTION__);
#define UNIMPLEMENTED_DBGBREAK __debugbreak()
#define ERR DbgPrint
#define TRACE DbgPrint
#ifdef _PREFAST_
#undef NT_ASSERT
#define NT_ASSERT(exp) ((void)NT_VERIFY(exp), __analysis_assume(exp))
#endif

#define MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
#define MmLowestUserAddress ((PVOID)0x10000)
#define INIT_FUNCTION
#define PAGES_PER_LARGE_PAGE (LARGE_PAGE_SIZE / PAGE_SIZE)


#ifdef _WIN64
#define InterlockedCompareExchangeSizeT(D, E, C) InterlockedCompareExchange64((LONG64*)D, E, C)
#define RtlFillMemoryUlongPtr RtlFillMemoryUlonglong
#else
#define InterlockedCompareExchangeSizeT(D, E, C) InterlockedCompareExchange((LONG*)D, E, C)
#define RtlFillMemoryUlongPtr RtlFillMemoryUlong
#endif

#ifdef __cplusplus

inline
void*
operator new(size_t, void *p)
{
    return p;
}

inline
void*
operator new(size_t Size, enum _POOL_TYPE PoolType, ULONG Tag)
{
    return ExAllocatePoolWithTag(PoolType, Size, Tag);
}

inline
void*
operator new(size_t Size, enum _POOL_TYPE PoolType, SIZE_T AllocSize, ULONG PoolTag)
{
    return ExAllocatePoolWithTag(PoolType, AllocSize, PoolTag);
}

inline
void operator delete(void* P)
{
    ExFreePool(P);
}

template<typename _ResultType, typename _OrigType>
_ResultType SCAST(_OrigType x)
{
    _ResultType Result = static_cast<_ResultType>(x);
    NT_ASSERT(static_cast<_OrigType>(Result) == x);
    return Result;
}

#endif

/// HACK OF HACK HACK

#define _SEH2_TRY  {
#define _SEH2_FINALLY }  {
#define _SEH2_EXCEPT(...) } if (0) {
#define _SEH2_END }
#define _SEH2_GetExceptionInformation()
#define _SEH2_GetExceptionCode() 0
#define _SEH2_AbnormalTermination()
#define _SEH2_YIELD(STMT_) STMT_
#define _SEH2_LEAVE
#define _SEH2_VOLATILE volatile

#undef PsGetCurrentProcess
#define PsGetCurrentProcess() ((PEPROCESS)(PsGetCurrentThread()->Tcb.ApcState.Process))
#define ExGetPreviousMode() KeGetCurrentPrcb()->CurrentThread->PreviousMode

extern "C"
VOID
FASTCALL
KeWaitForGate(
    _In_ PKGATE Gate,
    _In_ KWAIT_REASON WaitReason,
    _In_ KPROCESSOR_MODE WaitMode);

extern "C"
VOID
FASTCALL
KeSignalGateBoostPriority (
    PKGATE Gate);

extern "C"
NTSTATUS
NTAPI
SeInitializeProcessAuditName (
    _In_ PFILE_OBJECT FileObject,
    _In_ BOOLEAN DoAudit,
    _Out_ POBJECT_NAME_INFORMATION *AuditInfo);

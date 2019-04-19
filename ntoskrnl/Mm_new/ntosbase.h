
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

/* A path separator */
#define _C_PATHSEP_ /

/* Helper for including from architecture specific paths.
 * Architectures can be x86, amd64, arm, ppc, mips, mips64
 * Use like this: '#include _ARCH_RELATIVE_(test.h)' */
#define _ARCH_RELATIVE_(file) \
    _STREXPAND_(_EXPAND_(_ARCH_)_EXPAND_(_C_PATHSEP_)file)


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


#define PAGE_FLAGS_VALID_FROM_USER_MODE     \
    (PAGE_READONLY | \
    PAGE_READWRITE | \
    PAGE_WRITECOPY | \
    PAGE_EXECUTE | \
    PAGE_EXECUTE_READ | \
    PAGE_EXECUTE_READWRITE | \
    PAGE_EXECUTE_WRITECOPY | \
    PAGE_GUARD | \
    PAGE_NOACCESS | \
    PAGE_NOCACHE)

#define PAGE_FLAGS_VALID_FOR_SECTION \
    (PAGE_READONLY | \
     PAGE_READWRITE | \
     PAGE_WRITECOPY | \
     PAGE_EXECUTE | \
     PAGE_EXECUTE_READ | \
     PAGE_EXECUTE_READWRITE | \
     PAGE_EXECUTE_WRITECOPY | \
     PAGE_NOACCESS)

#define PAGE_IS_READABLE                    \
    (PAGE_READONLY | \
    PAGE_READWRITE | \
    PAGE_WRITECOPY | \
    PAGE_EXECUTE_READ | \
    PAGE_EXECUTE_READWRITE | \
    PAGE_EXECUTE_WRITECOPY)

#define PAGE_IS_WRITABLE                    \
    (PAGE_READWRITE | \
    PAGE_WRITECOPY | \
    PAGE_EXECUTE_READWRITE | \
    PAGE_EXECUTE_WRITECOPY)

#define PAGE_IS_EXECUTABLE                  \
    (PAGE_EXECUTE | \
    PAGE_EXECUTE_READ | \
    PAGE_EXECUTE_READWRITE | \
    PAGE_EXECUTE_WRITECOPY)

#define PAGE_IS_WRITECOPY                   \
    (PAGE_WRITECOPY | \
    PAGE_EXECUTE_WRITECOPY)

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

namespace Mm {

enum MM_PROTECT
{
    /* Base values */
    MM_INVALID            = 0,
    MM_READONLY           = 1,
    MM_EXECUTE            = 2,
    MM_EXECUTE_READ       = 3,
    MM_READWRITE          = 4,
    MM_WRITECOPY          = 5,
    MM_EXECUTE_READWRITE  = 6,
    MM_EXECUTE_WRITECOPY  = 7,
    MM_BASE_PROTECTION    = 7,

    /* Flags */
    MM_UNCACHED           = 0x08,
    MM_GUARDPAGE          = 0x10,
    MM_WRITECOMBINE       = 0x18,
    MM_CACHE_ATTRIBUTE    = 0x18,

    /* Special cases */
    MM_DECOMMIT           = MM_GUARDPAGE | MM_INVALID,
    MM_NOACCESS           = MM_WRITECOMBINE | MM_INVALID,
    MM_OUTSWAPPED_KSTACK  = MM_WRITECOMBINE | MM_EXECUTE_WRITECOPY,

    MM_PROTECTION_MASK    = 0x1F,

    /* Additional flags */
    MM_GLOBAL             = 0x20,
    MM_USER               = 0x40,
    MM_MAPPED             = 0x80,
    MM_NONPAGED           = 0x100,
    MM_LARGEPAGE          = 0x200,

    MM_INVALID_PROTECTION = 0xFFFFFFFF
};

typedef struct _PROTOTYPE
{
    ULONG64 PageFrameNumber : 36;
    ULONG64 Protection : 6;
} PROTOTYPE, *PPROTOTYPE;

}; // namespace Mm

#endif

#if 0
VOID
FASTCALL
ExfAcquirePushLockExclusive(PEX_PUSH_LOCK PushLock);

FORCEINLINE
VOID
ExAcquirePushLockExclusive(PEX_PUSH_LOCK PushLock)
{
    /* Try acquiring the lock */
    if (InterlockedBitTestAndSet((PLONG)PushLock, 0))
    {
        /* Someone changed it, use the slow path */
        ExfAcquirePushLockExclusive(PushLock);
    }
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

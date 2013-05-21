
#pragma once

/* Hacks! */
#define IoFileObjectType _IoFileObjectType
#define PsProcessType _PsProcessType
#define KeEnterCriticalRegion _KeEnterCriticalRegion
#define KeLeaveCriticalRegion _KeLeaveCriticalRegion
#ifdef _M_AMD64
#define KeGetCurrentThread _KeGetCurrentThread
#endif

#include <ntifs.h>
//#include <pseh/pseh2.h>

#define ProbeForWriteHandle(x) ProbeForWrite(x, sizeof(HANDLE), sizeof(HANDLE))

#define MmLowestUserAddress ((PVOID)0x10000)

#define UNIMPLEMENTED __debugbreak()
#define INIT_FUNCTION
#define ERR DbgPrint
#define TRACE DbgPrint
#define MI_USE_LARGE_PAGES_FOR_PFN_DATABASE
#define AddToPtr(Ptr, Offset) ((PVOID)(((PUCHAR)(Ptr)) + (Offset)))
#define AddToPointer(Ptr, Offset) ((PVOID)(((PUCHAR)(Ptr)) + (Offset)))
#define AddressToVpn(Address) (((ULONG_PTR)(Address)) >> PAGE_SHIFT)
#define VpnToAddress(Vpn)  ((PVOID)((Vpn) << PAGE_SHIFT))
#define PointerDiff(Address1, Address2) ((PUCHAR)Address2 - (PUCHAR)Address1)


#define PAGE_ANY_READ (PAGE_READONLY|PAGE_READWRITE|PAGE_WRITECOPY|PAGE_EXECUTE_READWRITE)
#define PAGE_ANY_WRITE (PAGE_READWRITE|PAGE_EXECUTE_READWRITE)
#define PAGE_ANY_EXECUTE (PAGE_EXECUTE|PAGE_EXECUTE_READ|PAGE_EXECUTE_READWRITE|PAGE_EXECUTE_WRITECOPY)

#ifdef _WIN64
#define InterlockedCompareExchangeSizeT(D, E, C) InterlockedCompareExchange64((LONG64*)D, E, C)
#define RtlFillMemoryUlongPtr RtlFillMemoryUlonglong
#else
#define InterlockedCompareExchangeSizeT(D, E, C) InterlockedCompareExchange((LONG*)D, E, C)
#define RtlFillMemoryUlongPtr RtlFillMemoryUlong
#endif

#define MinPtr(Ptr1, Ptr2) ((((ULONG_PTR)(Ptr1)) < ((ULONG_PTR)(Ptr2))) ? (Ptr1) : (Ptr2))

/* Macro expansion helpers */
#define _EXPAND2_(x) x
#define _EXPAND_(x) _EXPAND2_(x)
#define _STREXPAND2_(x) #x
#define _STREXPAND_(x) _STREXPAND2_(x)

/* A path separator */
#define _C_PATHSEP_ /

#if 0
/* Helper for including from architecture specific paths.
 * Architectures can be x86, amd64, arm, ppc, mips, mips64
 * Use like this: '#include _ARCH_RELATIVE_(test.h)' */
#define _ARCH_RELATIVE_(file) \
    _STREXPAND_(_EXPAND_(_ARCH_)_EXPAND_(_C_PATHSEP_)file)
#endif

#ifdef _M_IX86
#undef i386
#define _ARCH_RELATIVE_(_file) _STREXPAND_(i386/_file)
#elif defined(_M_AMD64)
#define _ARCH_RELATIVE_(_file) _STREXPAND_(amd64/_file)
#endif

#ifdef _WIN64

extern "C" {

typedef struct _RTL_BITMAP64
{
    ULONG64 SizeOfBitMap;
    PULONG64 Buffer;
} RTL_BITMAP64, *PRTL_BITMAP64;

VOID
NTAPI
RtlInitializeBitMap64 (
    _Out_ PRTL_BITMAP64 BitMapHeader,
    _In_ PULONG64 BitMapBuffer,
    _In_ ULONG64 SizeOfBitMap);

BOOLEAN
NTAPI
RtlTestBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 BitNumber);

VOID
NTAPI
RtlClearBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 BitNumber);

VOID
NTAPI
RtlClearBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 StartingIndex,
    _In_ ULONG64 NumberToClear);

VOID
NTAPI
RtlSetBit64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 BitNumber);

VOID
NTAPI
RtlSetBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 StartingIndex,
    _In_ ULONG64 NumberToClear);

BOOLEAN
NTAPI
RtlAreBitsSet64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 StartingIndex,
    _In_ ULONG64 Length);

ULONG64
NTAPI
RtlFindSetBits64 (
    _In_ PRTL_BITMAP64 BitMapHeader,
    _In_ ULONG64 NumberToFind,
    _In_ ULONG64 HintIndex);

};

#define RtlInitializeBitMapEx RtlInitializeBitMap64
#define RtlTestBitEx RtlTestBit64
#define RtlClearBitEx RtlClearBit64
#define RtlClearBitsEx RtlClearBits64
#define RtlSetBitEx RtlSetBit64
#define RtlSetBitsEx RtlSetBits64
#define RtlAreBitsSetEx RtlAreBitsSet64
#define RtlFindSetBitsEx RtlFindSetBits64
#define RTL_BITMAP_EX RTL_BITMAP64
#define PRTL_BITMAP_EX PRTL_BITMAP64
#else
#define RtlInitializeBitMapEx RtlInitializeBitMap
#define RtlTestBitEx RtlTestBit
#define RtlClearBitEx RtlClearBit
#define RtlClearBitsEx RtlClearBits
#define RtlSetBitEx RtlSetBit
#define RtlSetBitsEx RtlSetBits
#define RtlAreBitsSetEx RtlAreBitsSet
#define RtlFindSetBitsEx RtlFindSetBits
#define RTL_BITMAP_EX RTL_BITMAP
#define PRTL_BITMAP_EX PRTL_BITMAP
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

    /* Flags */
    MM_UNCACHED           = 0x08,
    MM_GUARDPAGE          = 0x10,
    MM_WRITECOMBINE       = 0x18,

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

#ifdef _PREFAST_
#undef NT_ASSERT
#define NT_ASSERT(exp) ((void)NT_VERIFY(exp), __analysis_assume(exp))
#endif


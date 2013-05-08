
#pragma once

/* Dependencies */
#define NT_INCLUDED
#include <excpt.h>
#include <ntdef.h>
#include <ntstatus.h>
#include <kernelspecs.h>
#include <ntiologc.h>
#include <intrin.h>
#include <pseh/pseh2.h>

#if defined(_MSC_VER)

/* Disable some warnings */
#pragma warning(disable:4115) /* Named type definition in parentheses */
#pragma warning(disable:4201) /* Nameless unions and structs */
#pragma warning(disable:4214) /* Bit fields of other types than int */
#pragma warning(disable:4820) /* Padding added, due to alignment requirement */

#endif /* _MSC_VER */

/* Hacks! */
#define IoFileObjectType _IoFileObjectType
#define PsProcessType _PsProcessType
#define KeEnterCriticalRegion _KeEnterCriticalRegion
#define KeLeaveCriticalRegion _KeLeaveCriticalRegion
#define KeGetCurrentThread _KeGetCurrentThread

#include <ntifs.h>

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
#else
#define InterlockedCompareExchangeSizeT(D, E, C) InterlockedCompareExchange((LONG*)D, E, C)
#endif

#define MinPtr(Ptr1, Ptr2) ((((ULONG_PTR)(Ptr1)) < ((ULONG_PTR)(Ptr2))) ? (Ptr1) : (Ptr2))

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

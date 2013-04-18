
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
#define TRACE(...)
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

#define MinPtr(Ptr1, Ptr2) ((((ULONG_PTR)(Ptr1)) < ((ULONG_PTR)(Ptr1))) ? (Ptr1) : (Ptr2))

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
    MM_DECOMMIT           = 0,
    MM_READONLY           = 1,
    MM_EXECUTE            = 2,
    MM_EXECUTE_READ       = 3,
    MM_READWRITE          = 4,
    MM_WRITECOPY          = 5,
    MM_EXECUTE_READWRITE  = 6,
    MM_EXECUTE_WRITECOPY  = 7,

    MM_NOCACHE            = 0x08,
    MM_NOACCESS           = 0x10,
    MM_WRITECOMBINE       = 0x18,

    MM_PROTECTION_MASK    = 0x1F,

    MM_GLOBAL             = 0x20,
    MM_USER               = 0x40, /// FIXME
    MM_MAPPED             = 0x80,
    MM_NONPAGED           = 0x100,
    MM_LARGEPAGE          = 0x200,

    MM_INVALID_PROTECTION = 0xFFFFFFFF
};


}; // namespace Mm

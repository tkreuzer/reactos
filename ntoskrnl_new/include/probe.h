
#pragma once

#include <memaccess.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern NTKERNELAPI ULONG_PTR MmUserProbeAddress;
#define MM_USER_PROBE_ADDRESS MmUserProbeAddress

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
DECLSPEC_NORETURN
VOID
NTAPI
ExRaiseDatatypeMisalignment (
    VOID);

// from ntosp.h

// My variants:
#define ProbeAlignment(Address, Alignment) \
    if (((ULONG_PTR)(Address) & ((Alignment) - 1)) != 0) { \
        ExRaiseDatatypeMisalignment(); \
    }                                                                    \

#define ProbeAddressRange(Address, Length) \
    if ((((ULONG_PTR)(Address) + (Length)) > (ULONG_PTR)MM_USER_PROBE_ADDRESS) || \
        (((ULONG_PTR)(Address) + (Length)) < (ULONG_PTR)(Address))) { \
        WriteNoFence8((volatile CHAR * const)(ULONG_PTR)MM_USER_PROBE_ADDRESS, 0); \
    }

#define CheckProbeAddress(Address) \
    (((ULONG_PTR)(Address) >= (ULONG_PTR)MM_USER_PROBE_ADDRESS) ? \
     (PVOID)(ULONG_PTR)MM_USER_PROBE_ADDRESS : (PVOID)(Address))

#if defined(_PREFAST_)

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
ProbeForRead (
    __in_data_source(USER_MODE) _In_reads_bytes_(Length) const volatile VOID *Address,
    _In_ SIZE_T Length,
    _In_ ULONG Alignment
    );

#else

#define ProbeForRead(Address, Length, Alignment) { \
    NT_ASSERT(((Alignment) & ((Alignment) - 1)) == 0); \
    if ((Length) != 0) { \
        ProbeAlignment(Address, Alignment); \
        ProbeAddressRange(Address, Length); \
    } \
}

#endif // _PREFAST_

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForReadSmallStructure (
    __in_data_source(USER_MODE) _In_reads_bytes_(Size) volatile VOID *Address,
    _In_ SIZE_T Size,
    _In_ ULONG Alignment)
{
    NT_ASSERT((Alignment == 1) || (Alignment == 2) ||
              (Alignment == 4) || (Alignment == 8) ||
              (Alignment == 16)  || (Alignment == 64));

    if ((Size == 0) || (Size >= 0x10000))
    {
        NT_ASSERT(0);
        ProbeForRead(Address, Size, Alignment);
    }
    else
    {
        ProbeAlignment(Address, Alignment);
        Address = CheckProbeAddress(Address);
        _ReadWriteBarrier();
        ReadNoFence8((PCHAR)Address);
    }
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
BOOLEAN
ProbeAndReadBoolean (
    _In_reads_bytes_(sizeof(BOOLEAN)) volatile const BOOLEAN *Address)
{
    C_ASSERT(sizeof(BOOLEAN) == sizeof(CHAR));
    Address = (const BOOLEAN *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return (ReadUCharNoFence((const UCHAR*)Address) != 0);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
CHAR
ProbeAndReadChar (
    _In_reads_bytes_(sizeof(CHAR)) volatile const CHAR *Address)
{
    Address = (const CHAR *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return ReadNoFence8(Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
UCHAR
ProbeAndReadUchar (
    _In_reads_bytes_(sizeof(UCHAR)) volatile const UCHAR *Address)
{
    Address = (const UCHAR *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return ReadUCharNoFence(Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
SHORT
ProbeAndReadShort (
    _In_reads_bytes_(sizeof(SHORT)) volatile const SHORT *Address)
{
    Address = (const SHORT *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return ReadNoFence16(Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
USHORT
ProbeAndReadUshort (
    _In_reads_bytes_(sizeof(USHORT)) volatile const USHORT *Address)
{
    Address = (const USHORT *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return ReadUShortNoFence(Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
HANDLE
ProbeAndReadHandle (
    _In_reads_bytes_(sizeof(HANDLE)) volatile const HANDLE *Address)
{
    C_ASSERT(sizeof(HANDLE) == sizeof(PVOID));
    Address = (const HANDLE *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return (HANDLE)ReadPointerNoFence((PVOID *)Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
PVOID
ProbeAndReadPointer (
    _In_reads_bytes_(sizeof(PVOID)) volatile const PVOID *Address)
{
    Address = (const PVOID *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return ReadPointerNoFence(Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
LONG
ProbeAndReadLong (
    _In_reads_bytes_(sizeof(LONG)) volatile const LONG *Address)
{
    Address = (const LONG *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return ReadNoFence(Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
ULONG
ProbeAndReadUlong (
    _In_reads_bytes_(sizeof(ULONG)) volatile const ULONG *Address)
{
    Address = (const ULONG *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return ReadULongNoFence(Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
ULONG_PTR
ProbeAndReadUlong_ptr (
    _In_reads_bytes_(sizeof(ULONG_PTR)) volatile const ULONG_PTR *Address)
{
    Address = (const ULONG_PTR *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    return ReadULongPtrNoFence(Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
LARGE_INTEGER
ProbeAndReadLargeInteger (
    _In_reads_bytes_(sizeof(LARGE_INTEGER)) volatile const LARGE_INTEGER *Address)
{
    LARGE_INTEGER Value;

    Address = (const LARGE_INTEGER *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    Value.QuadPart = ReadNoFence64(&Address->QuadPart);
    return Value;
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
ULARGE_INTEGER
ProbeAndReadUlargeInteger (
    _In_reads_bytes_(sizeof(ULARGE_INTEGER)) volatile const ULARGE_INTEGER *Address)
{
    ULARGE_INTEGER Value;

    Address = (const ULARGE_INTEGER *)CheckProbeAddress(Address);
    _ReadWriteBarrier();
    Value.QuadPart = ReadULong64NoFence(&Address->QuadPart);
    return Value;
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndReadUnicodeStringEx (
    _Out_writes_bytes_(sizeof(UNICODE_STRING)) PUNICODE_STRING Destination,
    _In_ volatile const UNICODE_STRING *Source)
{
    Source = (const UNICODE_STRING *)CheckProbeAddress(Source);

    _ReadWriteBarrier();
    *(PLONG)Destination = ReadNoFence((PLONG)Source);
    Destination->Buffer = (PWCHAR)ReadPointerNoFence((PVOID *)&Source->Buffer);
}

#if !defined(__cplusplus)

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
UNICODE_STRING
ProbeAndReadUnicodeString (
    _In_ volatile const UNICODE_STRING *Source)
{
    UNICODE_STRING Value;

    ProbeAndReadUnicodeStringEx(&Value, Source);
    return Value;
}

#endif

#define ProbeAndReadStructure(Dst, Src, STRUCTURE)                         \
    ProbeAndReadStructureWorker(Dst, Src, sizeof(STRUCTURE))

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndReadStructureWorker (
    _Out_writes_bytes_(Size) PVOID Destination,
    _In_reads_bytes_(Size) volatile const VOID *Source,
    _In_ SIZE_T Size)
{
    Source = CheckProbeAddress(Source);
    memcpy(Destination, (PVOID)Source, Size);
    _ReadWriteBarrier();
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteBoolean (
    _In_reads_bytes_(sizeof(BOOLEAN)) volatile BOOLEAN *Address)
{
    Address = (BOOLEAN *)CheckProbeAddress(Address);
    WriteUCharNoFence((UCHAR*)Address, ReadUCharNoFence((const UCHAR*)Address));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteChar (
    _In_reads_bytes_(sizeof(CHAR)) volatile CHAR *Address)
{
    Address = (CHAR *)CheckProbeAddress(Address);
    WriteNoFence8(Address, ReadNoFence8(Address));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteUchar (
    _In_reads_bytes_(sizeof(UCHAR)) PUCHAR Address)
{
    Address = (PUCHAR)CheckProbeAddress(Address);
    WriteUCharNoFence(Address, ReadUCharNoFence(Address));
}

#if 0 // FIXME IO_STATUS_BLOCK
_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteIoStatus (
    _In_reads_bytes_(sizeof(IO_STATUS_BLOCK)) volatile IO_STATUS_BLOCK *Address)
{
    Address = (IO_STATUS_BLOCK *)CheckProbeAddress(Address);
    WriteNoFence(&Address->Status, ReadNoFence(&Address->Status));
}
#endif // 0

#define ProbeForWriteIoStatusEx(Address, Cookie) ProbeForWriteIoStatus(Address)

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteShort (
    _In_reads_bytes_(sizeof(SHORT)) volatile SHORT *Address)
{
    Address = (SHORT *)CheckProbeAddress(Address);
    WriteNoFence16(Address, ReadNoFence16(Address));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteUshort (
    _In_reads_bytes_(sizeof(USHORT)) volatile USHORT *Address)
{
    Address = (USHORT *)CheckProbeAddress(Address);
    WriteUShortNoFence(Address, ReadUShortNoFence(Address));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteHandle (
    _In_reads_bytes_(sizeof(HANDLE)) volatile HANDLE *Address)
{
    Address = (HANDLE *)CheckProbeAddress(Address);
    WritePointerNoFence((PVOID *)Address, ReadPointerNoFence(Address));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndZeroHandle (
    _Out_writes_bytes_(sizeof(HANDLE)) volatile HANDLE *Address)
{
    Address = (HANDLE *)CheckProbeAddress(Address);
    WritePointerNoFence((PVOID *)Address, NULL);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWritePointer (
    _In_reads_bytes_(sizeof(PVOID)) volatile PVOID *Address)
{
    Address = (PVOID *)CheckProbeAddress(Address);
    WritePointerNoFence(Address, ReadPointerNoFence(Address));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndNullPointer (
    _Out_writes_bytes_(sizeof(PVOID)) volatile PVOID *Address)
{
    Address = (PVOID *)CheckProbeAddress(Address);
    WritePointerNoFence(Address, NULL);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteLong (
    _In_reads_bytes_(sizeof(LONG)) volatile LONG *Address)
{
    Address = (LONG *)CheckProbeAddress(Address);
    WriteNoFence(Address, ReadNoFence(Address));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteUlong (
    _In_reads_bytes_(sizeof(ULONG)) volatile ULONG *Address)
{
    Address = (ULONG *)CheckProbeAddress(Address);
    WriteULongNoFence(Address, ReadULongNoFence(Address));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteUlongAligned32 (
    _In_reads_bytes_(sizeof(ULONG)) volatile ULONG *Address)
{
    ProbeAlignment(Address, sizeof(ULONG));
    ProbeForWriteUlong(Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteUlong_ptr (
    _In_reads_bytes_(sizeof(ULONG_PTR)) volatile ULONG_PTR *Address)
{
    Address = (ULONG_PTR *)CheckProbeAddress(Address);
    WriteULongPtrNoFence(Address, ReadULongPtrNoFence(Address));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteQuad (
    _In_reads_bytes_(sizeof(QUAD)) volatile QUAD *Address)
{
    Address = (QUAD *)CheckProbeAddress(Address);
    WriteNoFence64(&Address->UseThisFieldToCopy,
                   ReadNoFence64(&Address->UseThisFieldToCopy));
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteUquad (
    _In_reads_bytes_(sizeof(UQUAD)) volatile UQUAD *Address)
{
    ProbeForWriteQuad((PQUAD)Address);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteBoolean (
    _Out_writes_bytes_(sizeof(BOOLEAN)) volatile BOOLEAN *Address,
    _In_ BOOLEAN Value)
{
    Address = (BOOLEAN *)CheckProbeAddress(Address);
    WriteUCharNoFence((UCHAR*)Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteChar (
    _Out_writes_bytes_(sizeof(CHAR)) volatile CHAR *Address,
    _In_ CHAR Value)
{
    Address = (CHAR *)CheckProbeAddress(Address);
    WriteNoFence8(Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteUchar (
    _Out_writes_bytes_(sizeof(UCHAR)) volatile UCHAR *Address,
    _In_ UCHAR Value)
{
    Address = (UCHAR *)CheckProbeAddress(Address);
    WriteUCharNoFence(Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteShort (
    _Out_writes_bytes_(sizeof(SHORT)) volatile SHORT *Address,
    _In_ SHORT Value)
{
    Address = (SHORT *)CheckProbeAddress(Address);
    WriteNoFence16(Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteUshort (
    _Out_writes_bytes_(sizeof(USHORT)) volatile USHORT *Address,
    _In_ USHORT Value)
{
    Address = (USHORT *)CheckProbeAddress(Address);
    WriteUShortNoFence(Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteHandle (
    _Out_writes_bytes_(sizeof(HANDLE)) volatile HANDLE *Address,
    _In_ HANDLE Value)
{
    Address = (HANDLE *)CheckProbeAddress(Address);
    WritePointerNoFence((PVOID *)Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteLong (
    _Out_writes_bytes_(sizeof(LONG)) volatile LONG *Address,
    _In_ LONG Value)
{
    Address = (LONG *)CheckProbeAddress(Address);
    WriteNoFence(Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteUlong (
    _Out_writes_bytes_(sizeof(ULONG)) volatile ULONG *Address,
    _In_ ULONG Value)
{
    Address = (ULONG *)CheckProbeAddress(Address);
    WriteULongNoFence(Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteUlong_ptr (
    _Out_writes_bytes_(sizeof(ULONG_PTR)) volatile ULONG_PTR *Address,
    _In_ ULONG_PTR Value)
{
    Address = (ULONG_PTR *)CheckProbeAddress(Address);
    WriteULongPtrNoFence(Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWritePointer (
    _Out_ volatile PVOID *Address,
    _In_ PVOID Value)
{
    Address = (PVOID*)CheckProbeAddress(Address);
    WritePointerNoFence(Address, Value);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteQuad (
    _Out_writes_bytes_(sizeof(QUAD)) volatile QUAD *Address,
    _In_ QUAD Value)
{
    Address = (QUAD *)CheckProbeAddress(Address);
    WriteNoFence64(&Address->UseThisFieldToCopy, Value.UseThisFieldToCopy);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteUquad (
    _Out_writes_bytes_(sizeof(UQUAD)) volatile UQUAD *Address,
    _In_ UQUAD Value)
{
    Address = (UQUAD *)CheckProbeAddress(Address);
    WriteNoFence64(&Address->UseThisFieldToCopy, Value.UseThisFieldToCopy);
}

#define ProbeAndWriteStructure(Address, Value, STRUCTURE)                    \
    ProbeAndWriteStructureWorker(Address, &(Value), sizeof(STRUCTURE))

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeAndWriteStructureWorker (
    _Out_writes_bytes_(Size) volatile VOID *Address,
    _In_reads_bytes_(Size) PVOID Value,
    _In_ SIZE_T Size)
{
    Address = CheckProbeAddress(Address);
    _ReadWriteBarrier();
    memcpy((PVOID)Address, Value, Size);
}

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
NTAPI
ProbeForWrite (
    __in_data_source(USER_MODE) _Inout_updates_bytes_(Length) volatile VOID *Address,
    _In_ SIZE_T Length,
    _In_ ULONG Alignment);

_Maybe_raises_SEH_exception_
_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
VOID
ProbeForWriteSmallStructure (
    __in_data_source(USER_MODE) _In_reads_bytes_(Size)
    PVOID Address,
    _In_ SIZE_T Size,
    _In_ ULONG Alignment)
{
#if !defined(_M_AMD64)
    PCHAR Target;
#endif

    NT_ASSERT((Size > 0) && (Size < 0x1000));
    NT_ASSERT((Alignment == 1) || (Alignment == 2) ||
              (Alignment == 4) || (Alignment == 8) ||
              (Alignment == 16) || (Alignment == 64));

    if ((Size == 0) || (Size >= 0x1000))
    {
        ProbeForWrite(Address, Size, Alignment);
    }
    else
    {
        ProbeAlignment(Address, Alignment);
        Address = CheckProbeAddress(Address);

#if defined(_M_AMD64)
        ((volatile UCHAR *)(Address))[0] = ((volatile UCHAR *)(Address))[0];
        ((volatile UCHAR *)(Address))[Size - 1] = ((volatile UCHAR *)(Address))[Size - 1];
#else
        Target = (PCHAR)Address;
        WriteNoFence8(Target, ReadNoFence8(Target));
        if (Size > Alignment)
        {
            Target += (Size - 1) & ~(SIZE_T)(Alignment - 1);
            WriteNoFence8(Target, ReadNoFence8(Target));
        }
#endif
    }
}

#ifdef __cplusplus
}; // extern "C"
#endif // __cplusplus

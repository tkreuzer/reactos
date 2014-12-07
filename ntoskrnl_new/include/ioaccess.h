
#pragma once

#include <memaccess.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_M_IX86) || defined(_M_AMD64)

__forceinline
UCHAR
NTAPI
READ_REGISTER_UCHAR (
    _In_ _Notliteral_ volatile UCHAR *Register)
{
    _ReadWriteBarrier();
    return *Register;
}

__forceinline
USHORT
NTAPI
READ_REGISTER_USHORT (
    _In_ _Notliteral_ volatile USHORT *Register)
{
    _ReadWriteBarrier();
    return *Register;
}

__forceinline
ULONG
NTAPI
READ_REGISTER_ULONG (
    _In_ _Notliteral_ volatile ULONG *Register)
{
    _ReadWriteBarrier();
    return *Register;
}

#ifdef _M_AMD64
__forceinline
ULONG64
READ_REGISTER_ULONG64 (
    _In_ _Notliteral_ volatile ULONG64 *Register)
{
    _ReadWriteBarrier();
    return *Register;
}
#endif // _M_AMD64

__forceinline
VOID
NTAPI
READ_REGISTER_BUFFER_UCHAR (
    _In_reads_(Count) _Notliteral_ volatile UCHAR *Register,
    _Out_writes_all_(Count) PUCHAR Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __movsb(Buffer, (PUCHAR)Register, Count);
}

__forceinline
VOID
NTAPI
READ_REGISTER_BUFFER_USHORT (
    _In_reads_(Count) _Notliteral_ volatile USHORT *Register,
    _Out_writes_all_(Count) PUSHORT Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __movsw(Buffer, (PUSHORT)Register, Count);
}

__forceinline
VOID
NTAPI
READ_REGISTER_BUFFER_ULONG (
    _In_reads_(Count) _Notliteral_ volatile ULONG *Register,
    _Out_writes_all_(Count) PULONG Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __movsd(Buffer, (PULONG)Register, Count);
}

#ifdef _M_AMD64
__forceinline
VOID
READ_REGISTER_BUFFER_ULONG64 (
    _In_reads_(Count) _Notliteral_ volatile ULONG64 *Register,
    _Out_writes_all_(Count) PULONG64 Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __movsq(Buffer, (PULONG64)Register, Count);
}
#endif // _M_AMD64

__forceinline
VOID
NTAPI
WRITE_REGISTER_UCHAR (
    _In_ _Notliteral_ volatile UCHAR *Register,
    _In_ UCHAR Value)
{
    *Register = Value;
    MemoryBarrier();
}

__forceinline
VOID
NTAPI
WRITE_REGISTER_USHORT (
    _In_ _Notliteral_ volatile USHORT *Register,
    _In_ USHORT Value)
{
    *Register = Value;
    MemoryBarrier();
}

__forceinline
VOID
NTAPI
WRITE_REGISTER_ULONG (
    _In_ _Notliteral_ volatile ULONG *Register,
    _In_ ULONG Value)
{
    *Register = Value;
    MemoryBarrier();
}

#ifdef _M_AMD64
__forceinline
VOID
WRITE_REGISTER_ULONG64 (
    _In_ _Notliteral_ volatile ULONG64 *Register,
    _In_ ULONG64 Value)
{
    *Register = Value;
    MemoryBarrier();
}
#endif // _M_AMD64

__forceinline
VOID
NTAPI
WRITE_REGISTER_BUFFER_UCHAR (
    _Out_writes_(Count) _Notliteral_ volatile UCHAR *Register,
    _In_reads_(Count) PUCHAR Buffer,
    _In_ ULONG Count)
{
    __movsb((PUCHAR)Register, Buffer, Count);
    MemoryBarrier();
}

__forceinline
VOID
NTAPI
WRITE_REGISTER_BUFFER_USHORT (
    _Out_writes_(Count) _Notliteral_ volatile USHORT *Register,
    _In_reads_(Count) PUSHORT Buffer,
    _In_ ULONG Count)
{
    __movsw((PUSHORT)Register, Buffer, Count);
    MemoryBarrier();
}

__forceinline
VOID
NTAPI
WRITE_REGISTER_BUFFER_ULONG (
    _Out_writes_(Count) _Notliteral_ volatile ULONG *Register,
    _In_reads_(Count) PULONG Buffer,
    _In_ ULONG Count)
{
    __movsd((PULONG)Register, Buffer, Count);
    MemoryBarrier();
}

#ifdef _M_AMD64
__forceinline
VOID
WRITE_REGISTER_BUFFER_ULONG64 (
    _Out_writes_(Count) _Notliteral_ volatile ULONG64 *Register,
    _In_reads_(Count) PULONG64 Buffer,
    _In_ ULONG Count)
{
    __movsq((PULONG64)Register, Buffer, Count);
    MemoryBarrier(); // KeMemoryBarrier
}
#endif // _M_AMD64

__forceinline
UCHAR
READ_PORT_UCHAR (
    _In_ _Notliteral_ PUCHAR Port)
{
    UCHAR Result;

    _ReadWriteBarrier();
    Result = __inbyte((USHORT)((ULONG_PTR)Port));
    _ReadWriteBarrier();
    return Result;
}

__forceinline
USHORT
READ_PORT_USHORT (
    _In_ _Notliteral_ PUSHORT Port)
{
    USHORT Result;

    _ReadWriteBarrier();
    Result = __inword((USHORT)((ULONG_PTR)Port));
    _ReadWriteBarrier();
    return Result;
}

__forceinline
ULONG
READ_PORT_ULONG (
    _In_ _Notliteral_ PULONG Port)
{
    ULONG Result;

    _ReadWriteBarrier();
    Result = __indword((USHORT)((ULONG_PTR)Port));
    _ReadWriteBarrier();
    return Result;
}

__forceinline
VOID
READ_PORT_BUFFER_UCHAR (
    _In_ _Notliteral_ PUCHAR Port,
    _Out_writes_all_(Count) PUCHAR Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __inbytestring((USHORT)((ULONG_PTR)Port), Buffer, Count);
    _ReadWriteBarrier();
}

__forceinline
VOID
READ_PORT_BUFFER_USHORT (
    _In_ _Notliteral_ PUSHORT Port,
    _Out_writes_all_(Count) PUSHORT Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __inwordstring((USHORT)((ULONG_PTR)Port), Buffer, Count);
    _ReadWriteBarrier();
}

__forceinline
VOID
READ_PORT_BUFFER_ULONG (
    _In_ _Notliteral_ PULONG Port,
    _Out_writes_all_(Count) PULONG Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __indwordstring((USHORT)((ULONG_PTR)Port), Buffer, Count);
    _ReadWriteBarrier();
}

__forceinline
VOID
WRITE_PORT_UCHAR (
    _In_ _Notliteral_ PUCHAR Port,
    _In_ UCHAR Value)
{
    _ReadWriteBarrier();
    __outbyte((USHORT)((ULONG_PTR)Port), Value);
    _ReadWriteBarrier();
}

__forceinline
VOID
WRITE_PORT_USHORT (
    _In_ _Notliteral_ PUSHORT Port,
    _In_ USHORT Value)
{
    _ReadWriteBarrier();
    __outword((USHORT)((ULONG_PTR)Port), Value);
    _ReadWriteBarrier();
}

__forceinline
VOID
WRITE_PORT_ULONG (
    _In_ _Notliteral_ PULONG Port,
    _In_ ULONG Value)
{
    _ReadWriteBarrier();
    __outdword((USHORT)((ULONG_PTR)Port), Value);
    _ReadWriteBarrier();
}

__forceinline
VOID
WRITE_PORT_BUFFER_UCHAR (
    _In_ _Notliteral_ PUCHAR Port,
    _In_reads_(Count) PUCHAR Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __outbytestring((USHORT)((ULONG_PTR)Port), Buffer, Count);
    _ReadWriteBarrier();
}

__forceinline
VOID
WRITE_PORT_BUFFER_USHORT (
    _In_ _Notliteral_ PUSHORT Port,
    _In_reads_(Count) PUSHORT Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __outwordstring((USHORT)((ULONG_PTR)Port), Buffer, Count);
    _ReadWriteBarrier();
}

__forceinline
VOID
WRITE_PORT_BUFFER_ULONG (
    _In_ _Notliteral_ PULONG Port,
    _In_reads_(Count) PULONG Buffer,
    _In_ ULONG Count)
{
    _ReadWriteBarrier();
    __outdwordstring((USHORT)((ULONG_PTR)Port), Buffer, Count);
    _ReadWriteBarrier();
}

#elif defined(_ARM_) || defined(_ARM64_)

__forceinline
UCHAR
READ_REGISTER_NOFENCE_UCHAR (
    _In_ _Notliteral_ volatile UCHAR *Register)
{
    return ReadUCharNoFence(Register);
}

__forceinline
USHORT
READ_REGISTER_NOFENCE_USHORT (
    _In_ _Notliteral_ volatile USHORT *Register)
{
    return ReadUShortNoFence(Register);
}

__forceinline
ULONG
READ_REGISTER_NOFENCE_ULONG (
    _In_ _Notliteral_ volatile ULONG *Register)
{
    return ReadULongNoFence(Register);
}

#if defined(_ARM64_)
__forceinline
ULONG64
READ_REGISTER_NOFENCE_ULONG64 (
    _In_ _Notliteral_ volatile ULONG64 *Register)
{
    return ReadULong64NoFence(Register);
}
#endif // defined(_ARM64_)

__forceinline
VOID
READ_REGISTER_NOFENCE_BUFFER_UCHAR (
    _In_reads_(Count) _Notliteral_ volatile UCHAR *Register,
    _Out_writes_all_(Count) PUCHAR Buffer,
    _In_ ULONG Count)
{
    volatile UCHAR *registerBuffer =  Register;
    PUCHAR readBuffer = Buffer;
    ULONG readCount;

    for (readCount = Count; readCount--; readBuffer++, registerBuffer++) {
        *readBuffer = ReadUCharNoFence(registerBuffer);
    }
}

__forceinline
VOID
READ_REGISTER_NOFENCE_BUFFER_USHORT (
    _In_reads_(Count) _Notliteral_ volatile USHORT *Register,
    _Out_writes_all_(Count) PUSHORT Buffer,
    _In_ ULONG Count)
{
    volatile USHORT *registerBuffer =  Register;
    PUSHORT readBuffer = Buffer;
    ULONG readCount;

    for (readCount = Count; readCount--; readBuffer++, registerBuffer++) {
        *readBuffer = ReadUShortNoFence(registerBuffer);
    }
}

__forceinline
VOID
READ_REGISTER_NOFENCE_BUFFER_ULONG (
    _In_reads_(Count) _Notliteral_ volatile ULONG *Register,
    _Out_writes_all_(Count) PULONG Buffer,
    _In_ ULONG Count)
{
    volatile ULONG *registerBuffer =  Register;
    PULONG readBuffer = Buffer;
    ULONG readCount;

    for (readCount = Count; readCount--; readBuffer++, registerBuffer++) {
        *readBuffer = ReadULongNoFence(registerBuffer);
    }
}

#if defined(_ARM64_)
__forceinline
VOID
READ_REGISTER_NOFENCE_BUFFER_ULONG64 (
    _In_reads_(Count) _Notliteral_ volatile ULONG64 *Register,
    _Out_writes_all_(Count) PULONG64 Buffer,
    _In_ ULONG Count)
{
    volatile ULONG64 *registerBuffer =  Register;
    PULONG64 readBuffer = Buffer;
    ULONG readCount;

    for (readCount = Count; readCount--; readBuffer++, registerBuffer++) {
        *readBuffer = ReadULong64NoFence(registerBuffer);
    }
}
#endif

__forceinline
VOID
WRITE_REGISTER_NOFENCE_UCHAR (
    _In_ _Notliteral_ volatile UCHAR *Register,
    _In_ UCHAR Value)
{
    WriteUCharNoFence(Register, Value);
}

__forceinline
VOID
WRITE_REGISTER_NOFENCE_USHORT (
    _In_ _Notliteral_ volatile USHORT *Register,
    _In_ USHORT Value)
{
    WriteUShortNoFence(Register, Value);
}

__forceinline
VOID
WRITE_REGISTER_NOFENCE_ULONG (
    _In_ _Notliteral_ volatile ULONG *Register,
    _In_ ULONG Value)
{
    WriteULongNoFence(Register, Value);
}

#if defined(_ARM64_)
__forceinline
VOID
WRITE_REGISTER_NOFENCE_ULONG64 (
    _In_ _Notliteral_ volatile ULONG64 *Register,
    _In_ ULONG64 Value)
{
    WriteULong64NoFence(Register, Value);
}
#endif

__forceinline
VOID
WRITE_REGISTER_NOFENCE_BUFFER_UCHAR (
    _Out_writes_(Count) _Notliteral_ volatile UCHAR *Register,
    _In_reads_(Count) PUCHAR Buffer,
    _In_ ULONG Count)
{
    volatile UCHAR *registerBuffer = Register;
    PUCHAR writeBuffer = Buffer;
    ULONG writeCount;

    for (writeCount = Count; writeCount--; writeBuffer++, registerBuffer++) {
        WriteUCharNoFence(registerBuffer, *writeBuffer);
    }
}

__forceinline
VOID
WRITE_REGISTER_NOFENCE_BUFFER_USHORT (
    _Out_writes_(Count) _Notliteral_ volatile USHORT *Register,
    _In_reads_(Count) PUSHORT Buffer,
    _In_ ULONG Count)
{
    volatile USHORT *registerBuffer = Register;
    PUSHORT writeBuffer = Buffer;
    ULONG writeCount;

    for (writeCount = Count; writeCount--; writeBuffer++, registerBuffer++) {
        WriteUShortNoFence(registerBuffer, *writeBuffer);
    }
}

__forceinline
VOID
WRITE_REGISTER_NOFENCE_BUFFER_ULONG (
    _Out_writes_(Count) _Notliteral_ volatile ULONG *Register,
    _In_reads_(Count) PULONG Buffer,
    _In_ ULONG Count)
{
    volatile ULONG *registerBuffer = Register;
    PULONG writeBuffer = Buffer;
    ULONG writeCount;

    for (writeCount = Count; writeCount--; writeBuffer++, registerBuffer++) {
        WriteULongNoFence(registerBuffer, *writeBuffer);
    }
}

#if defined(_ARM64_)
__forceinline
VOID
WRITE_REGISTER_NOFENCE_BUFFER_ULONG64 (
    _Out_writes_(Count) _Notliteral_ volatile ULONG64 *Register,
    _In_reads_(Count) PULONG64 Buffer,
    _In_ ULONG Count)
{
    volatile ULONG64 *registerBuffer = Register;
    PULONG64 writeBuffer = Buffer;
    ULONG writeCount;

    for (writeCount = Count; writeCount--; writeBuffer++, registerBuffer++) {
        WriteULong64NoFence(registerBuffer, *writeBuffer);
    }
}
#endif

__forceinline
VOID
REGISTER_FENCE (
    VOID)
{
    _DataSynchronizationBarrier();
}

__forceinline
UCHAR
READ_REGISTER_UCHAR (
    _In_ _Notliteral_ volatile UCHAR *Register)
{
    UCHAR Value;

    _DataSynchronizationBarrier();
    Value = READ_REGISTER_NOFENCE_UCHAR(Register);

    return Value;
}

__forceinline
USHORT
READ_REGISTER_USHORT (
    _In_ _Notliteral_ volatile USHORT *Register)
{
    USHORT Value;

    _DataSynchronizationBarrier();
    Value = READ_REGISTER_NOFENCE_USHORT(Register);

    return Value;
}

__forceinline
ULONG
READ_REGISTER_ULONG (
    _In_ _Notliteral_ volatile ULONG *Register)
{
    ULONG Value;

    _DataSynchronizationBarrier();
    Value = READ_REGISTER_NOFENCE_ULONG(Register);

    return Value;
}

#if defined(_ARM64_)
__forceinline
ULONG64
READ_REGISTER_ULONG64 (
    _In_ _Notliteral_ volatile ULONG64 *Register)
{
    ULONG64 Value;

    _DataSynchronizationBarrier();
    Value = READ_REGISTER_NOFENCE_ULONG64(Register);

    return Value;
}
#endif

__forceinline
VOID
READ_REGISTER_BUFFER_UCHAR (
    _In_reads_(Count) _Notliteral_ volatile UCHAR *Register,
    _Out_writes_all_(Count) PUCHAR Buffer,
    _In_ ULONG Count)
{
    _DataSynchronizationBarrier();
    READ_REGISTER_NOFENCE_BUFFER_UCHAR(Register, Buffer, Count);
}

__forceinline
VOID
READ_REGISTER_BUFFER_USHORT (
    _In_reads_(Count) _Notliteral_ volatile USHORT *Register,
    _Out_writes_all_(Count) PUSHORT Buffer,
    _In_ ULONG Count)
{
    _DataSynchronizationBarrier();
    READ_REGISTER_NOFENCE_BUFFER_USHORT(Register, Buffer, Count);
}

__forceinline
VOID
READ_REGISTER_BUFFER_ULONG (
    _In_reads_(Count) _Notliteral_ volatile ULONG *Register,
    _Out_writes_all_(Count) PULONG Buffer,
    _In_ ULONG Count)
{
    _DataSynchronizationBarrier();
    READ_REGISTER_NOFENCE_BUFFER_ULONG(Register, Buffer, Count);
}

#if defined(_ARM64_)
__forceinline
VOID
READ_REGISTER_BUFFER_ULONG64 (
    _In_reads_(Count) _Notliteral_ volatile ULONG64 *Register,
    _Out_writes_all_(Count) PULONG64 Buffer,
    _In_ ULONG Count)
{
    _DataSynchronizationBarrier();
    READ_REGISTER_NOFENCE_BUFFER_ULONG64(Register, Buffer, Count);
}
#endif

__forceinline
VOID
WRITE_REGISTER_UCHAR (
    _In_ _Notliteral_ volatile UCHAR *Register,
    _In_ UCHAR Value)
{
    _DataSynchronizationBarrier();
    WRITE_REGISTER_NOFENCE_UCHAR(Register, Value);
}

__forceinline
VOID
WRITE_REGISTER_USHORT (
    _In_ _Notliteral_ volatile USHORT *Register,
    _In_ USHORT Value)
{
    _DataSynchronizationBarrier();
    WRITE_REGISTER_NOFENCE_USHORT(Register, Value);
}

__forceinline
VOID
WRITE_REGISTER_ULONG (
    _In_ _Notliteral_ volatile ULONG *Register,
    _In_ ULONG Value)
{
    _DataSynchronizationBarrier();
    WRITE_REGISTER_NOFENCE_ULONG(Register, Value);
}

#if defined(_ARM64_)
__forceinline
VOID
WRITE_REGISTER_ULONG64 (
    _In_ _Notliteral_ volatile ULONG64 *Register,
    _In_ ULONG64 Value)
{
    _DataSynchronizationBarrier();
    WRITE_REGISTER_NOFENCE_ULONG64(Register, Value);
}
#endif

__forceinline
VOID
WRITE_REGISTER_BUFFER_UCHAR (
    _Out_writes_(Count) _Notliteral_ volatile UCHAR *Register,
    _In_reads_(Count) PUCHAR Buffer,
    _In_ ULONG Count)
{
    _DataSynchronizationBarrier();
    WRITE_REGISTER_NOFENCE_BUFFER_UCHAR(Register, Buffer, Count);
}

__forceinline
VOID
WRITE_REGISTER_BUFFER_USHORT (
    _Out_writes_(Count) _Notliteral_ volatile USHORT *Register,
    _In_reads_(Count) PUSHORT Buffer,
    _In_ ULONG Count)
{
    _DataSynchronizationBarrier();
    WRITE_REGISTER_NOFENCE_BUFFER_USHORT(Register, Buffer, Count);
}

__forceinline
VOID
WRITE_REGISTER_BUFFER_ULONG (
    _Out_writes_(Count) _Notliteral_ volatile ULONG *Register,
    _In_reads_(Count) PULONG Buffer,
    _In_ ULONG Count)
{
    _DataSynchronizationBarrier();
    WRITE_REGISTER_NOFENCE_BUFFER_ULONG(Register, Buffer, Count);
}

#if defined(_ARM64_)
__forceinline
VOID
WRITE_REGISTER_BUFFER_ULONG64 (
    _Out_writes_(Count) _Notliteral_ volatile ULONG64 *Register,
    _In_reads_(Count) PULONG64 Buffer,
    _In_ ULONG Count)
{
    _DataSynchronizationBarrier();
    WRITE_REGISTER_NOFENCE_BUFFER_ULONG64(Register, Buffer, Count);
}
#endif

NTHALAPI
UCHAR
READ_PORT_UCHAR (
    _In_ _Notliteral_ PUCHAR Port);

NTHALAPI
USHORT
READ_PORT_USHORT (
    _In_ _Notliteral_ PUSHORT Port);

NTHALAPI
ULONG
READ_PORT_ULONG (
    _In_ _Notliteral_ PULONG Port);

NTHALAPI
VOID
READ_PORT_BUFFER_UCHAR (
    _In_ _Notliteral_ PUCHAR Port,
    _Out_writes_all_(Count) PUCHAR Buffer,
    _In_ ULONG Count);

NTHALAPI
VOID
READ_PORT_BUFFER_USHORT (
    _In_ _Notliteral_ PUSHORT Port,
    _Out_writes_all_(Count) PUSHORT Buffer,
    _In_ ULONG Count);

NTHALAPI
VOID
READ_PORT_BUFFER_ULONG (
    _In_ _Notliteral_ PULONG Port,
    _Out_writes_all_(Count) PULONG Buffer,
    _In_ ULONG Count);

NTHALAPI
VOID
WRITE_PORT_UCHAR (
    _In_ _Notliteral_ PUCHAR Port,
    _In_ UCHAR Value);

NTHALAPI
VOID
WRITE_PORT_USHORT (
    _In_ _Notliteral_ PUSHORT Port,
    _In_ USHORT Value);

NTHALAPI
VOID
WRITE_PORT_ULONG (
    _In_ _Notliteral_ PULONG Port,
    _In_ ULONG Value);

NTHALAPI
VOID
WRITE_PORT_BUFFER_UCHAR (
    _In_ _Notliteral_ PUCHAR Port,
    _In_reads_(Count) PUCHAR Buffer,
    _In_ ULONG Count);

NTHALAPI
VOID
WRITE_PORT_BUFFER_USHORT (
    _In_ _Notliteral_ PUSHORT Port,
    _In_reads_(Count) PUSHORT Buffer,
    _In_ ULONG Count);

NTHALAPI
VOID
WRITE_PORT_BUFFER_ULONG (
    _In_ _Notliteral_ PULONG Port,
    _In_reads_(Count) PULONG Buffer,
    _In_ ULONG Count);

#endif // defined(_ARM_) || defined(_ARM64_)

#ifdef __cplusplus
}; // extern "C"
#endif


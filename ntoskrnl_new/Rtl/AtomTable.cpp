
#include "Rtl.hpp"

extern "C" {

typedef struct _RTL_ATOM_TABLE *PRTL_ATOM_TABLE;
typedef USHORT RTL_ATOM, *PRTL_ATOM;

// http://filelog.net/func/RtlCreateAtomTable
NTSTATUS
NTAPI
RtlCreateAtomTable (
    ULONG TableSize,
    PRTL_ATOM_TABLE* AtomTable)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// undocumented
NTSTATUS
NTAPI
RtlCreateAtomTableEx (
    PVOID P1,
    PVOID P2,
    PVOID P3)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlDestroyAtomTable
NTSTATUS
NTAPI
RtlDestroyAtomTable (
    PRTL_ATOM_TABLE AtomTable)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlAddAtomToAtomTable
NTSTATUS
NTAPI
RtlAddAtomToAtomTable (
    _Inout_ PRTL_ATOM_TABLE AtomTable,
    _In_ PWSTR AtomName,
    _In_ PRTL_ATOM Atom)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// undocumented
NTSTATUS
NTAPI
RtlAddAtomToAtomTableEx (
    PVOID P1,
    PVOID P2,
    PVOID P3,
    PVOID P4)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlLookupAtomInAtomTable
NTSTATUS
NTAPI
RtlLookupAtomInAtomTable (
    _In_ PRTL_ATOM_TABLE AtomTable,
    _In_ PWSTR AtomName,
    _Out_ PRTL_ATOM Atom)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlQueryAtomInAtomTable
NTSTATUS
NTAPI
RtlQueryAtomInAtomTable (
    _In_ PRTL_ATOM_TABLE AtomTable,
    _In_ RTL_ATOM Atom,
    PULONG RefCount,
    PULONG PinCount,
    _In_ PWSTR AtomName,
    PULONG NameLength)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlPinAtomInAtomTable
NTSTATUS
NTAPI
RtlPinAtomInAtomTable (
    _Inout_ PRTL_ATOM_TABLE AtomTable,
    _In_ RTL_ATOM Atom)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlDeleteAtomFromAtomTable
NTSTATUS
NTAPI
RtlDeleteAtomFromAtomTable (
    PRTL_ATOM_TABLE AtomTable,
    RTL_ATOM Atom)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlEmptyAtomTable
NTSTATUS
NTAPI
RtlEmptyAtomTable (
    PVOID AtomTableHandle,
    BOOLEAN IncludePinnedAtoms)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

// http://filelog.net/func/RtlGetIntegerAtom
BOOLEAN
NTAPI
RtlGetIntegerAtom (
    PWSTR AtomName,
    PUSHORT IntegerAtom)
{
    __debugbreak();
    return FALSE;
}


} // extern "C"

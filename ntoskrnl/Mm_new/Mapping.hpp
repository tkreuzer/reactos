

#pragma once

#include "ntosbase.h"

namespace Mm {

class PTE;

ULONG
ConvertProtect (
    _In_ ULONG Win32Protect);

ULONG
ConvertProtectAndCaching (
    _In_ ULONG Win32Protect,
    _In_ MEMORY_CACHING_TYPE CachingType);

ULONG
ConvertProtectToWin32 (
    _In_ ULONG Protect);

NTSTATUS
MapVirtualMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect);

NTSTATUS
ProtectVirtualMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _Out_ PULONG OldProtect);

VOID
CheckVirtualMapping (
    _In_ PVOID BaseAddress,
    _Out_ PSIZE_T OutRegionSize,
    _Out_ PULONG OutProtect);

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
MapPrototypePtes (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ class PTE* Ptototypes);

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
MapPhysicalMemory (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ PFN_NUMBER BasePageFrameNumber);

NTSTATUS
MapPfnArray (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_ PPFN_NUMBER PfnArray);


/// FIXME: should go somewhere else
PVOID
ReserveKernelMemory (
    SIZE_T Size);

VOID
ReleaseKernelMemory (
    _In_ PVOID BaseAddress);

}; // namespace Mm

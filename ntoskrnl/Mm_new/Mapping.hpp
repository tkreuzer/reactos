

#pragma once

#include "ntosbase.h"

namespace Mm {

ULONG
ConvertProtect (
    _In_ ULONG Win32Protect);

ULONG
ConvertProtectAndCaching (
    _In_ ULONG Win32Protect,
    _In_ MEMORY_CACHING_TYPE CachingType);

NTSTATUS
CreateMapping (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_opt_ PPFN_NUMBER PfnArray,
    _In_opt_ PPROTOTYPE Prototypes);

NTSTATUS
ReservePageTables (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect);

VOID
MapPrototypePtes (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ PPROTOTYPE Ptototypes,
    _In_ ULONG Protect);

VOID
MapPfnArray (
    _In_ ULONG_PTR StartingVpn,
    _In_ PPFN_NUMBER PfnArray,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect);

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
NTAPI
MapPhysicalMemory (
    _In_ PFN_NUMBER BasePageFrameNumber,
    _In_ PFN_COUNT NumberOfPages,
    _In_ ULONG Protect);


}; // namespace Mm

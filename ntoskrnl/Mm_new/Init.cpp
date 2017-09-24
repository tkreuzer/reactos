/*!

    \file Init.cpp

    \brief Implements initialization functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"
#include "AddressSpace.hpp"
#include "PfnDatabase.hpp"
#include "SectionObject.hpp"
#include "VadTable.hpp"
#include "KernelVad.hpp"
#include "CommitCharge.hpp"
#include _ARCH_RELATIVE_(MachineDependent.hpp)
#include <arc/arc.h>

#ifdef _MSC_VER
/* This is to shut up linker warnings about .CRT sections */
#pragma comment(linker, "/merge:.CRT=.rdata")
#endif

namespace Mm {

VOID
InitializePoolSupport (
    VOID);

VOID
InitializeMachineDependent (
    _In_ PLOADER_PARAMETER_BLOCK LoaderBlock);

VOID
InitializeSysLoader (
    VOID);

ULONG RandomNumberSeed;
ULONG_PTR LowestSystemVpn;
KERNEL_VAD LoaderMappingsVad;
KERNEL_VAD HalVaVad;


class MEMORY_MANAGER
{
public:

    static
    VOID
    Inititalize (
        _In_ struct _LOADER_PARAMETER_BLOCK* LoaderBlock);

};

MEMORY_MANAGER g_MemoryManager;

VOID
INIT_FUNCTION
MEMORY_MANAGER::Inititalize (
    _In_ struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    NTSTATUS Status;
    ULONG_PTR NumberOfPages;

    /* Initialize a random number seed from the interrupt time and TSC */
    RandomNumberSeed = static_cast<ULONG>(KeQueryInterruptTime() << 8);
    RandomNumberSeed ^= static_cast<ULONG>(__rdtsc());

    /* Set and initialize the kernel address space */
    g_SystemProcessAddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
    g_SystemProcessAddressSpace->Initialize();

    /* Initialize the global kernel VAD table, so that we can reserve
       virtual memory. Required for the PFN database. */
    g_KernelVadTable.Initialize(TRUE);
#ifndef __linux__
    /* Reserve the address space for the loader mappings */
    LoaderMappingsVad.Initialize();
    NumberOfPages = LoaderBlock->Extension->LoaderPagesSpanned;
    Status = g_KernelVadTable.InsertVadObjectAtVpn(&LoaderMappingsVad,
                                                   AddressToVpn(KSEG0_BASE),
                                                   NumberOfPages);
    NT_ASSERT(NT_SUCCESS(Status));

    /* Reserve the address space for HAL */
    HalVaVad.Initialize();
    NumberOfPages = AddressToVpn(MM_HAL_VA_END) - AddressToVpn(MM_HAL_VA_START);
    Status = g_KernelVadTable.InsertVadObjectAtVpn(&HalVaVad,
                                                   AddressToVpn(MM_HAL_VA_START),
                                                   NumberOfPages);
    NT_ASSERT(NT_SUCCESS(Status));
#endif
    /* Gather some basic information from the loader block's memory descriptors */
    ScanMemoryDescriptors(LoaderBlock);

    /* Initialize machine dependent parts */
    InitializeMachineDependent(LoaderBlock);

    /* Sanity checks for some variables */
    NT_ASSERT(MmSystemRangeStart != NULL);
    NT_ASSERT(MmHighestSystemAddress != NULL);

    /* Set lowest system VPN */
    LowestSystemVpn = AddressToVpn(MmSystemRangeStart);

    /* Initialize the PFN database */
    g_PfnDatabase.Initialize(LoaderBlock);

    /* Initialize the system commit limit */
    InitializeSystemCommitLimit();

    /* Initialize the pools */
    InitializePoolSupport();

    /* Initialize the section object class */
    SECTION_OBJECT::InitializeClass();

    /* Initialize the system image loader */
    InitializeSysLoader();
}


extern "C" {

BOOLEAN
NTAPI
INIT_FUNCTION
MmInitSystem(
    IN ULONG Phase,
    IN struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    return TRUE;
}

BOOLEAN
NTAPI
INIT_FUNCTION
MmArmInitSystem(
    IN ULONG Phase,
    IN struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    if (Phase == 0)
    {
        g_MemoryManager.Inititalize(LoaderBlock);
    }
    else
    {
    }

    return TRUE;
}

VOID
NTAPI
INIT_FUNCTION
MmFreeLoaderBlock (
    struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    UNIMPLEMENTED;
    // Find the VAD (which is the static loader allocation VAD)
    // decommit the page (will release the PFN)
}


}; // extern "C"
}; // namespace Mm

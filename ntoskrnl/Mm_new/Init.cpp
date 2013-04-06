

#include "ntosbase.h"
#include "AddressSpace.hpp"
#include "PfnDatabase.hpp"
#include "SectionObject.hpp"
#include "VadTable.hpp"

namespace Mm {

/// \todo HACK!!!
PADDRESS_SPACE g_KernelAddressSpace;
VAD_TABLE g_KernelVadTable;

class MEMORY_MANAGER
{
public:

    static
    VOID
    Inititalize (
        _In_ struct _LOADER_PARAMETER_BLOCK* LoaderBlock);

};

VOID
MEMORY_MANAGER::Inititalize (
    _In_ struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    /* First initialize the global kernel VAD table, so that we can reserve
       virtual memory. Required for the PFN database. */
    g_KernelVadTable.Initialize(TRUE);

    /* Initialize the PFN database */
    g_PfnDatabase.Initialize(LoaderBlock);

    /* Set and initialize the kernel address space */
    g_KernelAddressSpace = GetProcessAddressSpace(PsGetCurrentProcess());
    g_KernelAddressSpace->Initialize();

    /* Initialize the section object class */
    SECTION_OBJECT::InitializeClass();
}

MEMORY_MANAGER g_MemoryManager;

extern "C" {

BOOLEAN
NTAPI
MmInitSystem(
    IN ULONG Phase,
    IN struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
MmArmInitSystem(
    IN ULONG Phase,
    IN struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    DbgPrint("MmArmInitSystem()\n");

    g_MemoryManager.Inititalize(LoaderBlock);

    return FALSE;
}

VOID
NTAPI
//INIT_FUNCTION
MmFreeLoaderBlock (
    struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    UNIMPLEMENTED;
    // Find the VAD (which is the static loader allocation VAD)
    // decommit the page (will release the PFN)
}


}; // extern "C"
}; // namespace Mm

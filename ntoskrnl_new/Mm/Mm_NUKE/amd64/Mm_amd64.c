

#include <ntoskrnl.h>
#include "../Mm_internal.h"

#define AMD64_IDENTITY_MAPPING 0xFFFF800000000000ULL

MXPTE MxValidKernelPte;
MXPDE MxValidKernelPde;
MXPDE MxValidUserPde;

PVOID Amd64IdentityMappingStart;
PVOID Amd64IdentityMappingEnd;

VOID
INIT_FUNCTION
Amd64InitializeIdentityMappings(VOID)
{
    MXPTE PteValue = MxValidKernelPte, *PointerPte;
    SIZE_T MappingSize;

    /* Calculate the size for the entire identity mapping range */
    MappingSize = (MmHighestPhysicalPage + 1) * PAGE_SIZE;
    Amd64IdentityMappingStart = (PVOID)AMD64_IDENTITY_MAPPING;
    Amd64IdentityMappingEnd = (PVOID)(AMD64_IDENTITY_MAPPING + MappingSize);

    /* Map the page tables / directories */
    MiEarlyMapPXEs(Amd64IdentityMappingStart, Amd64IdentityMappingEnd);
    MiEarlyMapPPEs(Amd64IdentityMappingStart, Amd64IdentityMappingEnd);
    MiEarlyMapPDEs(Amd64IdentityMappingStart, Amd64IdentityMappingEnd);

    /* Start with physical page 0 */
    PteValue.Hard.PageFrameNumber = 0;

    for (PointerPte = MxAddressToPte(Amd64IdentityMappingStart);
         PointerPte <= MxAddressToPte(Amd64IdentityMappingEnd);
         PointerPte++)
    {
        *PointerPte = PteValue;
        PteValue.Hard.PageFrameNumber++;
    }
}

VOID
NTAPI
MxZeroPage(PVOID Address)
{
    // FIXME: use SSE
    RtlZeroMemory(Address, PAGE_SIZE);
}

VOID
MxZeroPhysicalPage(
    PFN_NUMBER PageFrameNumber)
{
    PVOID Address;

    Address = MxGetEphemeralMapping(PageFrameNumber);

    MxZeroPage(Address);
}

VOID
INITAPI
MxInitializeArchitectureSpecific(
    IN PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    MxValidKernelPde.Hard.Valid = 1;
    MxValidKernelPde.Hard.Write = 1;

    MxValidKernelPte.Hard.Valid = 1;
    MxValidKernelPte.Hard.Write = 1;
    MxValidKernelPte.Hard.Global = 1;

    Amd64InitializeIdentityMappings();
}


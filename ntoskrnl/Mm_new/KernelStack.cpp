
#include "ntosbase.h"

#include "KernelVad.hpp"
#include "VadTable.hpp"

namespace Mm {

NTSTATUS
CreateMapping (
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect,
    _In_opt_ PPFN_NUMBER PfnArray,
    _In_opt_ PPROTOTYPE Prototypes);

static const PVOID MmHighestSystemAddress = (PVOID)0xFFFFFFFFFFFFFFFFULL;

PVOID
ReserveKernelMemory (
    SIZE_T Size)
{
    KERNEL_VAD* VadObject;
    NTSTATUS Status;

    Status = KERNEL_VAD::CreateInstance(&VadObject);
    if (!NT_SUCCESS(Status))
    {
        return NULL;
    }

    Status = g_KernelVadTable.InsertVadObject(VadObject,
                                              BYTES_TO_PAGES(Size),
                                              AddressToVpn(MmSystemRangeStart),
                                              AddressToVpn(MmHighestSystemAddress),
                                              1);
    if (!NT_SUCCESS(Status))
    {
        return NULL;
    }

    return VadObject->GetBaseAddress();
}

VOID
ReleaseKernelMemory (
    PVOID BaseAddress)
{
    UNIMPLEMENTED;
}

extern "C" {

NTSTATUS
NTAPI
MmGrowKernelStackEx (
    IN PVOID StackPointer,
    IN ULONG GrowSize)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmGrowKernelStack (
    IN PVOID StackPointer)
{
    return MmGrowKernelStackEx(StackPointer, KERNEL_LARGE_STACK_COMMIT);
}

////////////////////////////////////////////////////////////////////////////////

PVOID
NTAPI
MmCreateKernelStack (
    _In_ BOOLEAN GuiStack,
    _In_ UCHAR Node)
{
    LONG_PTR ReservedSize, CommitSize;
    PVOID BaseAddress, StackBase;
    ULONG_PTR StartingVpn;
    NTSTATUS Status;

    if (GuiStack)
    {
        /* Reserve 64 KB stack, but only commit 12 KB */
        ReservedSize = KERNEL_LARGE_STACK_SIZE;
        CommitSize = KERNEL_LARGE_STACK_COMMIT;
    }
    else
    {
        /* Reserve and commit 12 KB */
        ReservedSize = KERNEL_STACK_SIZE;
        CommitSize = KERNEL_STACK_SIZE;
    }

    /* Reserve memory */
    BaseAddress = ReserveKernelMemory(ReservedSize);
    if (BaseAddress == NULL)
    {
        return NULL;
    }

    /* Calculate the stack base */
    StackBase = AddToPointer(BaseAddress, ReservedSize);

    /* Map the initial memory */
    StartingVpn = AddressToVpn(StackBase) - BYTES_TO_PAGES(CommitSize);
    Status = CreateMapping(StartingVpn,
                           BYTES_TO_PAGES(CommitSize),
                           MM_READWRITE | MM_MAPPED | MM_NONPAGED,
                           NULL,
                           NULL);
    if (!NT_SUCCESS(Status))
    {
        ReleaseKernelMemory(BaseAddress);
        return NULL;
    }

    /* Return pointer to the stack base */
    return StackBase;
}

VOID
NTAPI
MmDeleteKernelStack (
    PVOID Stack,
    BOOLEAN GuiStack)
{
    UNIMPLEMENTED;
}

}; // extern "C"
}; // namespace Mm


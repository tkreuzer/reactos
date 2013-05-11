
#include "ntosbase.h"

#include "KernelVad.hpp"
#include "VadTable.hpp"
#include "Mapping.hpp"
#include _ARCH_RELATIVE_(MachineDependent.hpp)


namespace Mm {


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
                                              1,
                                              TRUE);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to insert VAD object into VAD table: %x\n", Status);
        VadObject->Release();
        return NULL;
    }

    return VadObject->GetBaseAddress();
}

VOID
ReleaseKernelMemory (
    PVOID BaseAddress)
{
    PVAD_OBJECT VadObject;

    /* Reference the VAD object */
    VadObject = g_KernelVadTable.ReferenceVadObjectByAddress(BaseAddress);
    NT_ASSERT(VadObject != NULL);
    NT_ASSERT(VadObject->GetBaseAddress() == BaseAddress);

    /* Remove the VAD object from the table */
    g_KernelVadTable.RemoveVadObject(VadObject);
    VadObject->Release();
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
        ERR("Failed to reserve kernel memory\n");
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
        ERR("Failed to create a mapping: %lx\n", Status);
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


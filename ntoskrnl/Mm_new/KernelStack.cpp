/*!

    \file KernelStack.cpp

    \brief Implements kernel stack managing functions

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"

#include "AddressSpace.hpp"
#include "KernelVad.hpp"
#include "VadTable.hpp"
#include "Mapping.hpp"
#include _ARCH_RELATIVE_(MachineDependent.hpp)


namespace Mm {

extern "C" {

/*! \fn MmGrowKernelStackEx
 *
 *  \brief Increases the size of a kernel stack by the specified size.
 *
 *  \param [in] StackPointer - Pointer to the base of the stack.
 *
 *  \param [in] GrowSize -
 *
 *  \return STATUS_SUCCESS on success, an appropriate error code otherwise.
 */
NTSTATUS
NTAPI
MmGrowKernelStackEx (
    _In_ PVOID StackPointer,
    _In_ ULONG GrowSize)
{
    UNIMPLEMENTED_DBGBREAK;
    return STATUS_NOT_IMPLEMENTED;
}

/*! \fn MmGrowKernelStack
 *
 *  \brief ...
 *
 *  \param [in] StackPointer -
 *
 *  \return STATUS_SUCCESS on success, an appropriate error code otherwise.
 */
NTSTATUS
NTAPI
MmGrowKernelStack (
    _In_ PVOID StackPointer)
{
    /* Pass the request to the extended version */
    return MmGrowKernelStackEx(StackPointer, KERNEL_LARGE_STACK_COMMIT);
}

/*! \fn MmCreateKernelStack
 *
 *  \brief Allocates a new kernel stack.
 *
 *  \param [in] GuiStack - Specifies whether a large GUI stack shall be created.
 *
 *  \param [in] Node - Not handled yet.
 *
 *  \return Base address (top) of the new kernel stack.
 *
 *  \todo Handle Node parameter.
 */
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
    Status = MapVirtualMemory(StartingVpn,
                              BYTES_TO_PAGES(CommitSize),
                              MM_READWRITE | MM_MAPPED | MM_NONPAGED);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to create a mapping: %lx\n", Status);
        ReleaseKernelMemory(BaseAddress);
        return NULL;
    }

    /* Return pointer to the stack base */
    return StackBase;
}

/*! \fn MmDeleteKernelStack
 *
 *  \brief Deletes a kernel stack
 *
 *  \param [in] Stack - Pointer to the base of the stack
 *
 *  \param [in] GuiStack - Specifies whether the stack is a large GUI stack.
 */
VOID
NTAPI
MmDeleteKernelStack (
    _In_ __drv_freesMem(Mem) PVOID Stack,
    _In_ BOOLEAN GuiStack)
{
    UNIMPLEMENTED;
}

}; // extern "C"
}; // namespace Mm


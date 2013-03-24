
#include "ntosbase.h"

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
    BOOLEAN GuiStack,
    UCHAR Node)
{
    UNIMPLEMENTED;
    return NULL;
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


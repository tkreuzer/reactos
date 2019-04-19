
IKernelDebugger* g_KernelDebugger;

namespace Kd {

VOID
InitializeKernelDebugger (
    PLOADER_BLOCK LoaderBlock)
{
    NTSTATUS status;

    // Loop loaded module list
        // Look for export QueryInterface()
            status = queryInterface(IID_KernelDebugger, &g_KernelDebugger);
            if (!NT_SUCCESS(status))
            {
                g_KernelDebugger = &KernelDebuggerDummy;
            }

}



} // namespace Kd

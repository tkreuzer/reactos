
#include <ntbase.h>
#include <LoaderBlock.hpp>
#include "VCpu.hpp"
#include "Kernel.hpp"

extern "C"
UINT
RawDbgPrint(const char *Format, ...);

extern "C" __declspec(dllimport) PUCHAR KdComPortInUse;

extern "C" __declspec(dllimport) void NTAPI KdLoadSymbols(int p1, int p2, int p3, int p4);

extern "C"
VOID
NTAPI
KiKernelEntryPoint (
    _Inout_ PLOADER_BLOCK LoaderBlock)
{
    (void)LoaderBlock;
    RawDbgPrint("KdLoadSymbols is %p, 0x%lx\n", KdLoadSymbols, *(DWORD*)KdLoadSymbols);
#if 0
    ULONG CpuNumber;


    CpuNumber = g_CurrentCpu.Initialize(LoaderBlock->GetPcrAddress());

    if (CpuNumber == 0)
    {

        Kd::g_KernelDebugger.Initialize();

        g_Kernel.Initialize(LoaderBlock);

    }

#endif

    for (;;);
}




#pragma once

#define _NTHAL_
#define _NTHALDLL_
#define _NTSYSTEM_
#define _IN_KERNEL_

/* CRT headers */
#include <stdio.h>
#include <stdarg.h>

/* Public header */
#include <xdk/xdk.h>
#include <arc/arc.h>
#include <reactos/arch/arch.h>

//#include "include/debug.h"

#define INIT_FUNCTION

VOID
FASTCALL
HalpAcquireSpinLockNoIrql(
    IN PKSPIN_LOCK SpinLock);

VOID
FASTCALL
HalpReleaseSpinLockNoIrql(
    IN PKSPIN_LOCK SpinLock);


/* Internal interface */
#include "include/pic.h"
#include "include/pit.h"
#include "include/cmos.h"

#ifdef CONFIG_SMP
#define HAL_BUILD_TYPE (DBG ? PRCB_BUILD_DEBUG : 0)
#else
#define HAL_BUILD_TYPE ((DBG ? PRCB_BUILD_DEBUG : 0) | PRCB_BUILD_UNIPROCESSOR)
#endif

extern char __ImageBase;

#define PRIMARY_VECTOR_BASE 0x30
#define IDT_INTERNAL 0x11
#define INITIAL_STALL_COUNT 100
#define HAL_INITIALIZATION_FAILED 0x5C

/* For MSVC, this is required before using DATA_SEG (used in pcidata) */
#ifdef _MSC_VER
# pragma section("INIT", read,execute,discard)
# pragma section("INITDATA", read,discard)
#endif

#define HalAddressToPteNumber(Address) ((((ULONG_PTR)Address) >> PTI_SHIFT) & 0xFFFFFFFFF)
#define HalAddressToPte(Address) &(((PHARDWARE_PTE)PTE_BASE)[HalAddressToPteNumber(Address)])

#ifdef _M_AMD64
#define HalpGetIdtEntry(Pcr, Vector) &(((PAMD64_IDTENTRY)((Pcr)->IdtBase))[Vector])
#define HalpRegisterInterruptHandler(v,h) Amd64RegisterInterruptHandler(KeGetPcr()->IdtBase,v,h)
#define KfLowerIrql KeLowerIrql
#define KiEnterInterruptTrap(TrapFrame) /* We do all neccessary in asm code */
#define KiEoiHelper(TrapFrame) return /* Just return to the caller */
#define HalBeginSystemInterrupt(Irql, Vector, OldIrql) (*OldIrql = 0, TRUE)
typedef AMD64_IDTENTRY HAL_IDTENTRY;
#else
#define HalpGetIdtEntry(Pcr, Vector) &(((PX86_IDTENTRY)((Pcr)->IDT))[Vector])
#define HalpRegisterInterruptHandler(v,h) x86RegisterInterruptHandler(KeGetPcr()->IdtBase,v,h)
#define HalAddressToPte(Address) &(((PHARDWARE_PTE)PTE_BASE)[x86AddressToPti(Address)])
#endif // _M_AMD64

void HalpClockInterrupt(void);

VOID
NTAPI
INIT_FUNCTION
HalpRegisterVector(
    IN UCHAR Flags,
    IN ULONG BusVector,
    IN ULONG SystemVector,
    IN KIRQL Irql);
NTAPI
INIT_FUNCTION
HalpRegisterVector(
    IN UCHAR Flags,
    IN ULONG BusVector,
    IN ULONG SystemVector,
    IN KIRQL Irql);

VOID
NTAPI
INIT_FUNCTION
HalpEnableInterruptHandler(
    IN UCHAR Flags,
    IN ULONG BusVector,
    IN ULONG SystemVector,
    IN KIRQL Irql,
    IN PVOID Handler,
    IN KINTERRUPT_MODE Mode);

BOOLEAN
NTAPI
HalpBiosDisplayReset(VOID);

VOID
NTAPI
HalpInitDma(VOID);

VOID
NTAPI
HalpInitProcessor(
    IN ULONG ProcessorNumber,
    IN PLOADER_PARAMETER_BLOCK LoaderBlock);

PHARDWARE_PTE
NTAPI
HalpAllocatePtes(
    ULONG PageCount);

VOID
NTAPI
HalpInitializeCpuBootstrap(
    PLOADER_PARAMETER_BLOCK LoaderBlock);

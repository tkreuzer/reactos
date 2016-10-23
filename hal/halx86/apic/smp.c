/*
 * PROJECT:         ReactOS HAL
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            hal/halx86/amd64/processor.c
 * PURPOSE:         HAL smp processor routines
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES ******************************************************************/

#include <hal.h>
#define NDEBUG
#include <debug.h>
#include "apic.h"

#define IDD_BOOTSTRAP_CODE 1

// FIXME: this is amd64 specific
#define HalPteToAddress(Pte) (PVOID)(((LONG64)Pte << 25) >> 16)

HARDWARE_PTE HalpTemplatePte;


typedef struct
{
    UCHAR JmpInstruction[4];
    ULONG OffsetLongModeEntryPoint;
    ULONG StartupCr3;
} BOOTSTRAPDATABLOCK, *PBOOTSTRAPDATABLOCK;

PBOOTSTRAPDATABLOCK HalpBootStrapCode;

VOID
NTAPI
HalpInitializeCpuBootstrap(
    PLOADER_PARAMETER_BLOCK LoaderBlock)
{
    PMEMORY_ALLOCATION_DESCRIPTOR Descriptor;
    PLIST_ENTRY ListEntry;
    LDR_RESOURCE_INFO ResourceInfo;
    PIMAGE_RESOURCE_DATA_ENTRY ResourceDataEntry;
    PVOID CodeResource;
    ULONG CodeSize, Offset;
    HARDWARE_PTE TemplatePte, *BootStrapPte;
    NTSTATUS Status;

    /* Get the 2nd entry in the memory descriptor list */
    ListEntry = LoaderBlock->MemoryDescriptorListHead.Flink->Flink;

    /* Get the memory descriptor itself */
    Descriptor = CONTAINING_RECORD(ListEntry,
                                   MEMORY_ALLOCATION_DESCRIPTOR,
                                   ListEntry);

    /* Make sure it is what we expect */
    ASSERT(Descriptor->BasePage == 1);
    ASSERT(Descriptor->PageCount > 1);
    ASSERT(Descriptor->MemoryType == LoaderFirmwareTemporary);

    /* Remove the first page (PFN 1) */
    Descriptor->BasePage++;
    Descriptor->PageCount--;

    /* Allocate a PTE from the hal VA space */
    BootStrapPte = HalpAllocatePtes(1);
    ASSERT(BootStrapPte != NULL);
    HalpBootStrapCode = HalPteToAddress(BootStrapPte);

    /* Map the page */
    TemplatePte = HalpTemplatePte;
    TemplatePte.PageFrameNumber = 1;
    TemplatePte.Valid = 1;
    TemplatePte.Write = 1;
    *BootStrapPte = TemplatePte;

    /* Find the resource containing the bootstrap code */
    ResourceInfo.Type = (ULONG_PTR)L"BINARY";
    ResourceInfo.Name = IDD_BOOTSTRAP_CODE;
    ResourceInfo.Language = 0;
    Status = LdrFindResource_U(&__ImageBase,
                               &ResourceInfo,
                               RESOURCE_DATA_LEVEL,
                               &ResourceDataEntry);
    ASSERT(NT_SUCCESS(Status));

    /* Get a pointer to the resource data */
    Status = LdrAccessResource(&__ImageBase,
                               ResourceDataEntry,
                               &CodeResource,
                               &CodeSize);
    ASSERT(NT_SUCCESS(Status));

    /* Copy the bootstrap code to physical address 0x1000 */
    RtlCopyMemory(HalpBootStrapCode, CodeResource, CodeSize);

    /* Get the relative offset of the long mode entry point address */
    Offset = HalpBootStrapCode->OffsetLongModeEntryPoint - 0x1000;

    /* Set the long mode entry point */
    ((ULONG*)HalpBootStrapCode)[Offset / sizeof(ULONG)] = 0;

    /* Set the startup cr3 to the one we use */
    HalpBootStrapCode->StartupCr3 = (ULONG)__readcr3();


}

VOID
NTAPI
HalRequestIpi(
    KAFFINITY TargetProcessors)
{
    UNIMPLEMENTED;
    __debugbreak();
}

VOID
NTAPI
HalRequestIpiSpecifyVector(
    ULONG Unknown1,
    struct _KAFFINITY_EX *TargetProcessors,
    ULONG Unknown3)
{
    UNIMPLEMENTED;
    __debugbreak();
}

BOOLEAN
NTAPI
HalStartNextProcessor(
    IN PLOADER_PARAMETER_BLOCK LoaderBlock,
    IN struct _KPROCESSOR_STATE *ProcessorState)
{
    UNIMPLEMENTED;
    __debugbreak();
    return FALSE;
}

VOID
NTAPI
HalStartDynamicProcessor(
    ULONG Unknown1,
    ULONG Unknwon2,
    ULONG Unknown3,
    ULONG Unknown4)
{
    UNIMPLEMENTED;
    __debugbreak();
}

BOOLEAN
NTAPI
HalAllProcessorsStarted(VOID)
{
    UNIMPLEMENTED;
    __debugbreak();
    return FALSE;
}


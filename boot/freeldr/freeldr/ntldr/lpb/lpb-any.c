
// DO NOT ADD THIS FILE TO CMakeLists.txt!

#ifndef NTLDR_VERSION
#error Must define NTLDR_VERSION
#endif

#include <freeldr.h>

#define MAKE_VERSIONED_NAME(Name, Verson) Name ## _ ## Version

NTSTATUS
NTAPI
MAKE_VERSIONED_NAME(CreateLpb, NTLDR_VERSION)(
    _In_ PLOADER_INFORMATION LoaderInfo,
    _Out_ PVOID* OutLoaderBlock)
{
    PLOADER_PARAMETER_BLOCK LoaderBlock;
    PLOADER_PARAMETER_EXTENSION Extension;

    LoaderBlock = FrLdrHeapAlloc(sizeof(*LoaderBlock), ' bpL');
    if (LoaderBlock == NULL)
    {
        return STATUS_NO_MEMORY;
    }

    RtlZeroMemory(LoaderBlock, sizeof(*LoaderBlock));

    Extension = FrLdrHeapAlloc(sizeof(*Extension), ' epL');
    if (Extension == NULL)
    {
        return STATUS_NO_MEMORY;
    }

    RtlZeroMemory(Extension, sizeof(*Extension));

#if (NTLDR_VERSION >= NTDDI_WIN7)
    LoaderBlock->OsMajorVersion = NTLDR_VERSION >> 24;
    LoaderBlock->OsMinorVersion = NTLDR_VERSION >> 16 & 0xFF;
    LoaderBlock->Size = sizeof(*LoaderBlock);
#endif
#if (NTLDR_VERSION >= NTDDI_WIN10_TH2)
    LoaderBlock->OsLoaderSecurityVersion = 1; // ???
#endif
    LoaderBlock->LoadOrderListHead = LoaderInfo->LoadOrderListHead;
    LoaderBlock->MemoryDescriptorListHead = LoaderInfo->MemoryDescriptorListHead;
    LoaderBlock->BootDriverListHead = LoaderInfo->BootDriverListHead;
    // ...
    LoaderBlock->Extension = Extension;
    // ...

    Extension->Size = sizeof(*Extension);
    //Extension->Profile = NULL; // ???
#if (NTLDR_VERSION < NTDDI_WIN7)
    Extension->MajorVersion = NTLDR_VERSION >> 24;
    Extension->MinorVersion = NTLDR_VERSION >> 16 & 0xFF;
#endif
#if (NTLDR_VERSION < NTDDI_WIN8)
    Extension->LoaderPagesSpanned = LoaderInfo->LoaderPagesSpanned;
#endif
    // ...

    return STATUS_SUCCESS;
}

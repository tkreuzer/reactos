/*
* COPYRIGHT:       See COPYING in the top level directory
* PROJECT:         ReactOS NT User-Mode Library
* FILE:            dll/ntdll/ldr/appcompat.c
* PURPOSE:         
* PROGRAMMERS:     Timo Kreuzer <timo.kreuzer@reactos.org>
*/

/* INCLUDES *****************************************************************/

#include <ntdll.h>
#include <compat_undoc.h>
#include <compatguid_undoc.h>

#define NDEBUG
#include <debug.h>


typedef enum _APPCOMPAT_VERSION_BIT
{
    APPCOMPAT_VERSION_BIT_NT4,
    APPCOMPAT_VERSION_BIT_WIN2K,
    APPCOMPAT_VERSION_BIT_WINXP,
    APPCOMPAT_VERSION_BIT_WS03,
    APPCOMPAT_VERSION_BIT_VISTA,
    //APPCOMPAT_VERSION_BIT_VISTASP1,
    //APPCOMPAT_VERSION_BIT_VISTASP2,
    APPCOMPAT_VERSION_BIT_WIN7,
    APPCOMPAT_VERSION_BIT_WIN8,
    APPCOMPAT_VERSION_BIT_WIN81,
    APPCOMPAT_VERSION_BIT_WIN10,
    //APPCOMPAT_VERSION_BIT_WIN10TH1,
    //APPCOMPAT_VERSION_BIT_WIN10TH2,
    //APPCOMPAT_VERSION_BIT_WIN10RS1,
    //APPCOMPAT_VERSION_BIT_WIN10RS2,
    //APPCOMPAT_VERSION_BIT_WIN10RS3,
    //APPCOMPAT_VERSION_BIT_WIN10RS4,
    //APPCOMPAT_VERSION_BIT_WIN10RS5,
} APPCOMPAT_VERSION_BIT;

typedef struct _LDRP_APPCOMPAT_DESCRIPTOR
{
    unsigned int *ExportNameBitmaps; // Array with size NumberOfNames
    unsigned int NumberOfExportNames;
} LDRP_APPCOMPAT_DESCRIPTOR, *PLDRP_APPCOMPAT_DESCRIPTOR;

//typedef struct _APPCOMAT_EXPORT_ENTRY
//{
//    ULONG VersionMask;
//    USHORT NameOrdinal;
//} APPCOMAT_EXPORT_ENTRY, *PAPPCOMAT_EXPORT_ENTRY;

DWORD
NTAPI
RosGetProcessCompatVersion(VOID)
{
    static DWORD g_CompatVersion = 0xffffffff;
    if (g_CompatVersion == 0xffffffff)
    {
        ReactOS_ShimData* pShimData = (ReactOS_ShimData*)NtCurrentPeb()->pShimData;
        if (pShimData && pShimData->dwMagic == REACTOS_SHIMDATA_MAGIC &&
            pShimData->dwSize == sizeof(ReactOS_ShimData))
        {
            g_CompatVersion = pShimData->dwRosProcessCompatVersion;
        }
    }
    return g_CompatVersion != 0xffffffff ? g_CompatVersion : 0;
}

static
APPCOMPAT_VERSION_BIT
TranslateAppcompatVersionToVersionBit(
    _In_ DWORD AppcompatVersion)
{
    switch (AppcompatVersion)
    {
        case _WIN32_WINNT_NT4:
            return APPCOMPAT_VERSION_BIT_NT4;
        case _WIN32_WINNT_WIN2K:
            return APPCOMPAT_VERSION_BIT_WIN2K;
        case _WIN32_WINNT_WINXP:
            return APPCOMPAT_VERSION_BIT_WINXP;
        case _WIN32_WINNT_WS03:
            return APPCOMPAT_VERSION_BIT_WS03;
        case _WIN32_WINNT_VISTA:
            return APPCOMPAT_VERSION_BIT_VISTA;
        //case 0x500:
        //    return APPCOMPAT_VERSION_BIT_VISTASP1;
        //case 0x500:
        //    return APPCOMPAT_VERSION_BIT_VISTASP2;
        case _WIN32_WINNT_WIN7:
            return APPCOMPAT_VERSION_BIT_WIN7;
        case _WIN32_WINNT_WIN8:
            return APPCOMPAT_VERSION_BIT_WIN8;
        case _WIN32_WINNT_WINBLUE:
            return APPCOMPAT_VERSION_BIT_WIN81;
        case _WIN32_WINNT_WIN10:
            return APPCOMPAT_VERSION_BIT_WIN10;
        //case 0x500:
        //    return APPCOMPAT_VERSION_BIT_WIN10TH1;
        //case 0x500:
        //    return APPCOMPAT_VERSION_BIT_WIN10TH2;
        //case 0x500:
        //    return APPCOMPAT_VERSION_BIT_WIN10RS1;
        //case 0x500:
        //    return APPCOMPAT_VERSION_BIT_WIN10RS2;
        //case 0x500:
        //    return APPCOMPAT_VERSION_BIT_WIN10RS3;
        //case 0x500:
        //    return APPCOMPAT_VERSION_BIT_WIN10RS4;
        //case 0x500:
        //    return APPCOMPAT_VERSION_BIT_WIN10RS5;
        default:
            ASSERT(FALSE);
    }

    return APPCOMPAT_VERSION_BIT_WS03;
}



PIMAGE_SECTION_HEADER
LdrpFindSectionByName(
    PVOID ImageBase,
    PSTR SectionName
    )
{
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_SECTION_HEADER SectionHeaders;
    ULONG i;

    NtHeaders = RtlImageNtHeader(ImageBase);
    if (NtHeaders == NULL)
    {
        return NULL;
    }

    SectionHeaders = IMAGE_FIRST_SECTION(NtHeaders);

    for (i = 0; i < NtHeaders->FileHeader.NumberOfSections; i++)
    {
        if (strncmp(SectionHeaders[i].Name, SectionName, IMAGE_SIZEOF_SHORT_NAME) == 0)
        {
            return &SectionHeaders[i];
        }
    }

    return NULL;
}

PVOID
LdrpSectionHeaderToVAAndSize(
    _In_ PVOID ImageBase,
    _In_ PIMAGE_SECTION_HEADER SectionHeader,
    _Out_ PSIZE_T SectionSize)
{
    *SectionSize = SectionHeader->SizeOfRawData;
    return (PVOID)((PUCHAR)ImageBase + SectionHeader->VirtualAddress);
}

PLDRP_APPCOMPAT_DESCRIPTOR
FindAppCompatDescriptor(
    _In_ PVOID ImageBase)
{
    PIMAGE_SECTION_HEADER SectionHeader;

    SectionHeader = LdrpFindSectionByName(ImageBase, ".expvers");
    if (SectionHeader == NULL)
    {
        return NULL;
    }

    return (PLDRP_APPCOMPAT_DESCRIPTOR)((PUCHAR)ImageBase + SectionHeader->VirtualAddress);
}

static
NTSTATUS
GetExportNameVersionTable(
    _In_ PVOID ImageBase,
    _Out_ PULONG *Table,
    _Out_ PULONG NumberOfEntries)
{
    PLDRP_APPCOMPAT_DESCRIPTOR AppcompatDescriptor;

    AppcompatDescriptor = FindAppCompatDescriptor(ImageBase);
    if (AppcompatDescriptor == NULL)
    {
        return STATUS_NOT_FOUND;
    }

    *NumberOfEntries = AppcompatDescriptor->NumberOfExportNames;
    *Table = AppcompatDescriptor->ExportNameBitmaps;

    return STATUS_SUCCESS;
}

__inline
BOOLEAN IsPowerOfTwo(unsigned int x)
{
    return ((x != 0) && !(x & (x - 1)));
}

NTSTATUS
PatchExportTable(
    _In_ PVOID DllBase,
    _In_ PLDRP_APPCOMPAT_DESCRIPTOR AppCompatDescriptor,
    _In_ ULONG VersionMask
)
{
    PIMAGE_EXPORT_DIRECTORY ExportDirectory;
    ULONG ExportDirectorySize, i, j, OldProtect;
    PVOID ProtectAddress;
    SIZE_T ProtectSize;
    PULONG NameTable, FunctionTable;
    PUSHORT OrdinalTable;
    NTSTATUS Status;
    ASSERT(IsPowerOfTwo(VersionMask));

    /* Get export directory */
    ExportDirectory = RtlImageDirectoryEntryToData(DllBase,
                                                   TRUE,
                                                   IMAGE_DIRECTORY_ENTRY_EXPORT,
                                                   &ExportDirectorySize);
    if (ExportDirectory == NULL)
    {
        return STATUS_INVALID_IMAGE_FORMAT;
    }

    ASSERT(AppCompatDescriptor->NumberOfExportNames == ExportDirectory->NumberOfNames);

    /* Unprotect the export directory */
    ProtectAddress = ExportDirectory;
    ProtectSize = ExportDirectorySize;
    Status = NtProtectVirtualMemory(NtCurrentProcess(),
                                    &ProtectAddress,
                                    &ProtectSize,
                                    PAGE_READWRITE,
                                    &OldProtect);
    if (!NT_SUCCESS(Status))
    {
        /* Fail */
        //DbgPrint("LDR: Unable to unprotect IAT for %wZ (Status %x)\n",
        //         &ImportLdrEntry->BaseDllName,
        //         Status);
        return Status;
    }


    /* Get the VA of the name table */
    NameTable = (PULONG)((ULONG_PTR)DllBase +
        (ULONG_PTR)ExportDirectory->AddressOfNames);

    OrdinalTable = (PUSHORT)((ULONG_PTR)DllBase +
        (ULONG_PTR)ExportDirectory->AddressOfNameOrdinals);

    /* Strip unused entries from the name and ordinal table */
    for (i = 0, j = 0; i < AppCompatDescriptor->NumberOfExportNames; i++)
    {
        //DbgPrint("    0x%08x, // %s\n",
        //         AppCompatDescriptor->ExportNameBitmaps[i],
        //         (char*)DllBase + NameTable[i]);
            
        if (AppCompatDescriptor->ExportNameBitmaps[i] & VersionMask)
        {
            NameTable[j] = NameTable[i];
            OrdinalTable[j] = OrdinalTable[i];
            j++;
        }
    }

    ExportDirectory->NumberOfNames = j;

    FunctionTable = (PULONG)((ULONG_PTR)DllBase +
        (ULONG_PTR)ExportDirectory->AddressOfFunctions);

    /* Unprotect the export directory */
    ProtectSize = ExportDirectorySize;
    Status = NtProtectVirtualMemory(NtCurrentProcess(),
                                    (PVOID*)&ExportDirectory,
                                    &ProtectSize,
                                    OldProtect,
                                    &OldProtect);
    if (!NT_SUCCESS(Status))
    {
        /* Fail */
        //DbgPrint("LDR: Unable to unprotect export table for %wZ (Status %x)\n",
        //         &ImportLdrEntry->BaseDllName,
        //         Status);
        return Status;
    }

    /* Also flush out the cache */
    NtFlushInstructionCache(NtCurrentProcess(), ExportDirectory, ProtectSize);

    return STATUS_SUCCESS;
}

/*

    OriginalExportDir
        -> Names[x]
        -> Ordinals[x]
        -> Functions[y]

    - Names are sorted
        -> strip unused ones
    - Ordinals can have different order
        -> need to reorder
        -> create

*/

NTSTATUS
NTAPI
RosApplyAppcompatExportHacks(PVOID DllBase)
{
    DWORD AppcompatVersion;
    APPCOMPAT_VERSION_BIT VersionBit;
    PLDRP_APPCOMPAT_DESCRIPTOR AppCompatDescriptor;

    //__debugbreak();
    /* Get the AppCompat version */
    AppcompatVersion = RosGetProcessCompatVersion();
    if (AppcompatVersion == 0)
    {
        /* Default to WS 2003 */
        AppcompatVersion = _WIN32_WINNT_WS03;
    }

    /* Get the appcompat descriptor */
    AppCompatDescriptor = FindAppCompatDescriptor(DllBase);
    if (AppCompatDescriptor == NULL)
    {
        return STATUS_NOT_FOUND;
    }

    // translate to appcompat bit
    VersionBit = TranslateAppcompatVersionToVersionBit(AppcompatVersion);

    PatchExportTable(DllBase, AppCompatDescriptor, 1 << VersionBit);

    return STATUS_SUCCESS;
}

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
#include <roscompat.h>

#define NDEBUG
#include <debug.h>

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
ROSCOMPAT_VERSION_BIT
TranslateAppcompatVersionToVersionBit(
    _In_ DWORD AppcompatVersion)
{
    switch (AppcompatVersion)
    {
        case _WIN32_WINNT_NT4:
            return ROSCOMPAT_VERSION_BIT_NT4;
        case _WIN32_WINNT_WIN2K:
            return ROSCOMPAT_VERSION_BIT_WIN2K;
        case _WIN32_WINNT_WINXP:
            return ROSCOMPAT_VERSION_BIT_WINXP;
        case _WIN32_WINNT_WS03:
            return ROSCOMPAT_VERSION_BIT_WS03;
        case _WIN32_WINNT_VISTA:
            return ROSCOMPAT_VERSION_BIT_VISTA;
        case _WIN32_WINNT_WIN7:
            return ROSCOMPAT_VERSION_BIT_WIN7;
        case _WIN32_WINNT_WIN8:
            return ROSCOMPAT_VERSION_BIT_WIN8;
        case _WIN32_WINNT_WINBLUE:
            return ROSCOMPAT_VERSION_BIT_WIN81;
        case _WIN32_WINNT_WIN10:
            return ROSCOMPAT_VERSION_BIT_WIN10;
        default:
            ASSERT(FALSE);
    }

    return ROSCOMPAT_VERSION_BIT_WS03;
}

PIMAGE_SECTION_HEADER
LdrpFindSectionByName(
    PVOID ImageBase,
    PSTR SectionName)
{
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_SECTION_HEADER SectionHeaders;
    SIZE_T NameLength;
    ULONG i;

    /* Get the NT headers */
    NtHeaders = RtlImageNtHeader(ImageBase);
    if (NtHeaders == NULL)
    {
        return NULL;
    }

    SectionHeaders = IMAGE_FIRST_SECTION(NtHeaders);

    /* Check for long section name */
    NameLength = strlen(SectionName);
    if (NameLength <= IMAGE_SIZEOF_SHORT_NAME)
    {
        /* Loop the sections until we found the requested one */
        for (i = 0; i < NtHeaders->FileHeader.NumberOfSections; i++)
        {
            /* Directly compare names */
            if (strncmp(SectionHeaders[i].Name, SectionName, IMAGE_SIZEOF_SHORT_NAME) == 0)
            {
                return &SectionHeaders[i];
            }
        }
    }
    else
    {
        // FIXME: support long section names
        ASSERT(FALSE);
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

PROSCOMPAT_DESCRIPTOR
FindRosCompatDescriptor(
    _In_ PVOID ImageBase)
{
    PIMAGE_SECTION_HEADER SectionHeader;

    SectionHeader = LdrpFindSectionByName(ImageBase, ".expvers");
    if (SectionHeader == NULL)
    {
        return NULL;
    }

    return (PROSCOMPAT_DESCRIPTOR)((PUCHAR)ImageBase + SectionHeader->VirtualAddress);
}

static
NTSTATUS
GetExportNameVersionTable(
    _In_ PVOID ImageBase,
    _Out_ PULONG *Table,
    _Out_ PULONG NumberOfEntries)
{
    PROSCOMPAT_DESCRIPTOR RosCompatDescriptor;

    RosCompatDescriptor = FindRosCompatDescriptor(ImageBase);
    if (RosCompatDescriptor == NULL)
    {
        return STATUS_NOT_FOUND;
    }

    *NumberOfEntries = RosCompatDescriptor->NumberOfExportNames;
    *Table = RosCompatDescriptor->ExportNameMasks;

    return STATUS_SUCCESS;
}

__inline
BOOLEAN IsPowerOfTwo(unsigned int x)
{
    return ((x != 0) && !(x & (x - 1)));
}

static
VOID
LdrpPatchExportNameTable(
    _In_ PVOID DllBase,
    _In_ PROSCOMPAT_DESCRIPTOR RosCompatDescriptor,
    _Inout_ PIMAGE_EXPORT_DIRECTORY ExportDirectory,
    _In_ DWORD AppCompatVersion)
{
    ULONG VersionMask;
    PULONG NameTable;
    PUSHORT OrdinalTable;
    ULONG i, j;
    ULONG OldName;
    USHORT OldOrd;

    /* Translate to version mask */
    VersionMask = 1 << TranslateAppcompatVersionToVersionBit(AppCompatVersion);
    ASSERT(IsPowerOfTwo(VersionMask));

    /* Get the VA of the name table */
    NameTable = (PULONG)((ULONG_PTR)DllBase +
        (ULONG_PTR)ExportDirectory->AddressOfNames);

    OrdinalTable = (PUSHORT)((ULONG_PTR)DllBase +
        (ULONG_PTR)ExportDirectory->AddressOfNameOrdinals);

    /* Strip unused entries from the name and ordinal table */
    for (i = 0, j = 0; i < RosCompatDescriptor->NumberOfExportNames; i++)
    {

        //DbgPrint("    0x%08x, // %s\n",
        //         RosCompatDescriptor->ExportNameMasks[i],
        //         (char*)DllBase + NameTable[i]);

        /* Exchange both fields. This algorithm results in moving the
           patched functions in sorted order to the end */
        OldName = NameTable[j];
        NameTable[j] = NameTable[i];
        NameTable[i] = OldName;

        OldOrd = OrdinalTable[j];
        OrdinalTable[j] = OrdinalTable[i];
        OrdinalTable[i] = OldOrd;

        if (RosCompatDescriptor->ExportNameMasks[i] & VersionMask)
        {
            j++;
        }
    }

    /* Finally patch the number of exports */
    ExportDirectory->NumberOfNames = j;
}

static
NTSTATUS
LdrpPatchExportTable(
    _In_ PVOID DllBase,
    _In_ PROSCOMPAT_DESCRIPTOR RosCompatDescriptor,
    _In_ DWORD AppCompatVersion
    )
{
    PIMAGE_EXPORT_DIRECTORY ExportDirectory;
    ULONG ExportDirectorySize, OldProtect;
    PVOID ProtectAddress;
    SIZE_T ProtectSize;
    PULONG FunctionTable;
    NTSTATUS Status;

    //__debugbreak();

    /* Get export directory */
    ExportDirectory = RtlImageDirectoryEntryToData(DllBase,
                                                   TRUE,
                                                   IMAGE_DIRECTORY_ENTRY_EXPORT,
                                                   &ExportDirectorySize);
    if (ExportDirectory == NULL)
    {
        return STATUS_INVALID_IMAGE_FORMAT;
    }

    ASSERT(RosCompatDescriptor->NumberOfExportNames == ExportDirectory->NumberOfNames);

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

    /* Patch the export name and ordinal table */
    LdrpPatchExportNameTable(DllBase, RosCompatDescriptor, ExportDirectory, AppCompatVersion);

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

BOOLEAN
NTAPI
RosApplyAppcompatExportHacks(PLDR_DATA_TABLE_ENTRY LdrEntry)
{
    DWORD AppcompatVersion;
    PROSCOMPAT_DESCRIPTOR RosCompatDescriptor;
    NTSTATUS Status;

    /* Get the appcompat descriptor */
    RosCompatDescriptor = FindRosCompatDescriptor(LdrEntry->DllBase);
    if (RosCompatDescriptor == NULL)
    {
        return FALSE;
    }

    /* Get the AppCompat version */
    AppcompatVersion = RosGetProcessCompatVersion();
    if (AppcompatVersion == 0)
    {
        /* Default to WS 2003 */
        AppcompatVersion = _WIN32_WINNT_WS03;
    }

    /* Save the descriptor in the PatchInformation field, which is otherwise
       unused in user-mode */
    LdrEntry->PatchInformation = RosCompatDescriptor;

    /* Now patch the export table */
    Status = LdrpPatchExportTable(LdrEntry->DllBase,
                                  RosCompatDescriptor,
                                  AppcompatVersion);
    if (!NT_SUCCESS(Status))
    {
        __debugbreak();
        return FALSE;
    }

    return TRUE;
}

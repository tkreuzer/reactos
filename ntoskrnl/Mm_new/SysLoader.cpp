/*!

    \file SysLoader.cpp

    \brief Implements the system image loader

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "SysLoader.hpp"
#include <ntimage.h>
#include <ldrtypes.h>
#include <rtlfuncs.h>
#include <mmfuncs.h>
#include <obfuncs.h>
#include "Mapping.hpp"
#include "MmData.hpp"
#include "AddressSpace.hpp"
#include "SectionObject.hpp"
#include <arc/arc.h>

#define TAG_MODULE_OBJECT 'ommM'

namespace Mm {

ERESOURCE PsLoadedModuleResource;
KMUTEX SystemLoaderLock;
PLDR_DATA_TABLE_ENTRY NtOsLdrEntry, HalLdrEntry;
extern "C" LIST_ENTRY PsLoadedModuleList;
extern "C" BOOLEAN PsImageNotifyEnabled;

VOID
PatchLoadedSystemImage(
    PUNICODE_STRING ImageName,
    PVOID ImageBase);

static
PLDR_DATA_TABLE_ENTRY
FindLoaderEntry (
    _In_ PUNICODE_STRING FileName,
    _In_opt_ PUNICODE_STRING BaseName);

VOID
InitializeSysLoader (
    VOID)
{
    UNICODE_STRING ModuleName;// = RTL_CONSTANT_STRING(L"ntoskrnl.exe");
    PLIST_ENTRY ListEntry;
    PLDR_DATA_TABLE_ENTRY LdrEntry, NewEntry;
    ULONG Size;
    PWCHAR Buffer;

    KeInitializeMutex(&SystemLoaderLock, 0);
    InitializeListHead(&PsLoadedModuleList);

    /* Loop all entries on the loader block's module list */
    for (ListEntry = KeLoaderBlock->LoadOrderListHead.Flink;
         ListEntry != &KeLoaderBlock->LoadOrderListHead;
         ListEntry = ListEntry->Flink)
    {
        /* Get the loader entry */
        LdrEntry = CONTAINING_RECORD(ListEntry,
                                     LDR_DATA_TABLE_ENTRY,
                                     InLoadOrderLinks);

        /* Calculate the size for a full entry */
        Size = sizeof(LDR_DATA_TABLE_ENTRY) + 
               LdrEntry->BaseDllName.Length + sizeof(WCHAR) +
               LdrEntry->FullDllName.Length + sizeof(WCHAR);

        /* Allocate a new entry from non paged pool */
        //NewEntry = new(NonPagedPool, Size, TAG_MODULE_OBJECT) LDR_DATA_TABLE_ENTRY;
        NewEntry = (PLDR_DATA_TABLE_ENTRY)ExAllocatePoolWithTag(NonPagedPool, Size, TAG_MODULE_OBJECT);
        NT_ASSERT(NewEntry != NULL);

        /* Copy the entry */
        *NewEntry = *LdrEntry;

        /* Copy the base dll name */
        Buffer = reinterpret_cast<PWCHAR>(NewEntry + 1);
        NewEntry->BaseDllName.Buffer = Buffer;
        NewEntry->BaseDllName.MaximumLength = LdrEntry->BaseDllName.Length + sizeof(WCHAR);
        RtlCopyMemory(Buffer, LdrEntry->BaseDllName.Buffer, LdrEntry->BaseDllName.Length);
        Buffer[NewEntry->BaseDllName.Length / sizeof(WCHAR)] = L'\0';

        /* Copy the full dll name */
        Buffer = (PWCHAR)AddToPointer(Buffer, NewEntry->BaseDllName.MaximumLength);
        NewEntry->FullDllName.Buffer = Buffer;
        NewEntry->FullDllName.MaximumLength = LdrEntry->FullDllName.Length + sizeof(WCHAR);
        RtlCopyMemory(Buffer, LdrEntry->FullDllName.Buffer, LdrEntry->FullDllName.Length);
        Buffer[NewEntry->FullDllName.Length / sizeof(WCHAR)] = L'\0';

        /* Reset load count to 0, unmapping is owned by the kernel */
        NewEntry->LoadCount = 0;
        NewEntry->Flags |= LDRP_COR_IMAGE | LDR_COR_OWNS_UNMAP;

        /* Insert the entry into the module list */
        InsertTailList(&PsLoadedModuleList, &NewEntry->InLoadOrderLinks);
    }

    RtlInitUnicodeString(&ModuleName, L"ntoskrnl.exe");
    NtOsLdrEntry = FindLoaderEntry(NULL, &ModuleName);
    NT_ASSERT(NtOsLdrEntry != NULL);
    NtOsLdrEntry->LoadCount = 1;

    PsNtosImageBase = (ULONG_PTR)NtOsLdrEntry->DllBase;
    NT_ASSERT(PsNtosImageBase != 0);

    RtlInitUnicodeString(&ModuleName, L"hal.dll");
    HalLdrEntry = FindLoaderEntry(NULL, &ModuleName);
    NT_ASSERT(HalLdrEntry != NULL);
    HalLdrEntry->LoadCount = 1;
}

VOID
FORCEINLINE
AcquireLoaderLock (
    VOID)
{
    KeEnterCriticalRegion();
    KeWaitForMutexObject(&SystemLoaderLock, WrVirtualMemory, KernelMode, FALSE, NULL);
}

VOID
FORCEINLINE
ReleaseLoaderLock (
    VOID)
{
    KeReleaseMutex(&SystemLoaderLock, FALSE);
    KeLeaveCriticalRegion();
}

static
VOID
SeperatePath (
    _In_ PUNICODE_STRING FullName,
    _Out_ PUNICODE_STRING PathName,
    _Out_ PUNICODE_STRING FileName)
{
    PWCHAR StringEnd = FullName->Buffer + FullName->Length / sizeof(WCHAR);
    PWCHAR Current = StringEnd - 1;

    while ((Current >= FullName->Buffer) && (*Current != L'\\'))
        Current--;

    FileName->Buffer = Current + 1;
    FileName->Length = (USHORT)(StringEnd - FileName->Buffer) * sizeof(WCHAR);
    FileName->MaximumLength = FileName->Length;

    PathName->Buffer = FullName->Buffer;
    PathName->Length = (USHORT)(Current + 1 - PathName->Buffer) * sizeof(WCHAR);
    PathName->MaximumLength = PathName->Length;
}

static
PLDR_DATA_TABLE_ENTRY
FindLoaderEntry (
    _In_opt_ PUNICODE_STRING FileName,
    _In_opt_ PUNICODE_STRING BaseName)
{
    PLDR_DATA_TABLE_ENTRY LdrEntry, FoundEntry = NULL;
    PLIST_ENTRY ListEntry;
    BOOLEAN Found;

    /* Scan the module list */
    for (ListEntry = PsLoadedModuleList.Flink;
         ListEntry != &PsLoadedModuleList;
         ListEntry = ListEntry->Flink)
    {
        /* Get the loader entry */
        LdrEntry = CONTAINING_RECORD(ListEntry,
                                     LDR_DATA_TABLE_ENTRY,
                                     InLoadOrderLinks);

        /* Do we have a base name */
        if (BaseName != NULL)
        {
            /* Compare the base name */
            Found = RtlEqualUnicodeString(&LdrEntry->BaseDllName, BaseName, TRUE);
        }
        else
        {
            /* Compare the full path name */
            Found = RtlEqualUnicodeString(&LdrEntry->FullDllName, FileName, TRUE);
        }

        /* Do we have a match? */
        if (Found)
        {
            /* We found it, increment load count */
            FoundEntry = LdrEntry;
            break;
        }
    }

    /* Return the entry or NULL, if it was not found */
    return FoundEntry;
}

static
PLDR_DATA_TABLE_ENTRY
CreateLdrEntry (
    _In_ PUNICODE_STRING FullName,
    _In_ PUNICODE_STRING LoadedName,
    _In_ PVOID ImageBase,
    _In_ SIZE_T SizeOfImage)
{
    PLDR_DATA_TABLE_ENTRY LdrEntry;
    SIZE_T EntrySize;
    NTSTATUS Status;
    PIMAGE_NT_HEADERS NtHeader;

    /* Calculate the size we'll need for the entry and allocate it */
    EntrySize = sizeof(LDR_DATA_TABLE_ENTRY) +
                LoadedName->Length + sizeof(WCHAR) +
                FullName->Length + sizeof(WCHAR);

    /* Allocate the entry */
    LdrEntry = new(NonPagedPool, EntrySize, TAG_MODULE_OBJECT) LDR_DATA_TABLE_ENTRY;
    if (!LdrEntry)
    {
        /* Fail */
        Status = STATUS_INSUFFICIENT_RESOURCES;
        return NULL;
    }

    /* Initialize BaseDllName and copy the string */
    LdrEntry->BaseDllName.Buffer = (PWSTR)(LdrEntry + 1);
    LdrEntry->BaseDllName.Length = LoadedName->Length;
    LdrEntry->BaseDllName.MaximumLength = LoadedName->Length + sizeof(WCHAR);
    RtlCopyUnicodeString(&LdrEntry->BaseDllName, LoadedName);

    /* Initialize FullDllName and copy the string */
    LdrEntry->FullDllName.Buffer = LdrEntry->BaseDllName.Buffer +
                                   LdrEntry->BaseDllName.MaximumLength / sizeof(WCHAR);
    LdrEntry->FullDllName.Length = FullName->Length;
    LdrEntry->FullDllName.MaximumLength = FullName->Length + sizeof(WCHAR);
    RtlCopyUnicodeString(&LdrEntry->FullDllName, FullName);

    NtHeader = RtlImageNtHeader(ImageBase);
    NT_ASSERT(NtHeader != NULL);

    LdrEntry->DllBase = ImageBase;
    LdrEntry->EntryPoint = AddToPointer(ImageBase,
                                        NtHeader->OptionalHeader.AddressOfEntryPoint);
    LdrEntry->SizeOfImage = (ULONG)SizeOfImage;
    LdrEntry->Flags = LDRP_SYSTEM_MAPPED | LDRP_ENTRY_PROCESSED | LDRP_MM_LOADED;
    LdrEntry->LoadCount = 0;
    LdrEntry->TlsIndex = 0;
    LdrEntry->SectionPointer = NULL;
    LdrEntry->CheckSum = NtHeader->OptionalHeader.CheckSum;
    LdrEntry->LoadedImports = NULL;
    LdrEntry->EntryPointActivationContext = NULL;
    LdrEntry->PatchInformation = NULL;

    /* Check the version */
    if ((NtHeader->OptionalHeader.MajorOperatingSystemVersion >= 5) &&
            (NtHeader->OptionalHeader.MajorImageVersion >= 5))
    {
        /* Mark this image as a native image */
        LdrEntry->Flags |= LDRP_ENTRY_NATIVE;
    }

    return LdrEntry;
}

static
NTSTATUS
LoadSystemImageInternal (
    _Out_ PLDR_DATA_TABLE_ENTRY* OutLdrEntry,
    _In_ PUNICODE_STRING FileName,
    _In_ PUNICODE_STRING LoadedName,
    _In_ ULONG Flags)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    HANDLE FileHandle;
    LARGE_INTEGER SectionSize, SectionOffset;
    PVOID SectionObject;
    PVOID MappingBase, DriverBase;
    NTSTATUS Status;
    KAPC_STATE ApcState;
    PLDR_DATA_TABLE_ENTRY LdrEntry = NULL;
    ULONG_PTR NumberOfPages;
    SIZE_T SizeOfImage;
    PADDRESS_SPACE AddressSpace;

    /* Initialize object attributes */
    InitializeObjectAttributes(&ObjectAttributes,
                               FileName,
                               OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
                               NULL,
                               NULL);

    /* Open the image file */
    Status = ZwOpenFile(&FileHandle,
                        FILE_EXECUTE,
                        &ObjectAttributes,
                        &IoStatusBlock,
                        FILE_SHARE_READ | FILE_SHARE_DELETE,
                        0);
    if (!NT_SUCCESS(Status))
    {
        ERR("ZwOpenFile failed for '%wZ', status 0x%x\n", FileName, Status);
        return Status;
    }

    /* Create a section */
    SectionSize.QuadPart = 0;
    Status = MmCreateSection(&SectionObject,
                             SECTION_MAP_EXECUTE,
                             NULL,
                             &SectionSize,
                             PAGE_EXECUTE_READWRITE,
                             SEC_IMAGE,
                             FileHandle,
                             NULL);

    /* Close the file handle already */
    ObCloseHandle(FileHandle, KernelMode);

    if (!NT_SUCCESS(Status))
    {
        ERR("MmCreateSection failed, status 0x%x\n", Status);
        return Status;
    }

    /* Attach to the system process */
    KeStackAttachProcess(&PsInitialSystemProcess->Pcb, &ApcState);

    /* Map the section into the system process address space */
    SectionOffset.QuadPart = 0;
    SizeOfImage = 0;
    MappingBase = NULL;
    Status = MmMapViewOfSection(SectionObject,
                                PsGetCurrentProcess(),
                                &MappingBase,
                                0,
                                0,
                                &SectionOffset,
                                &SizeOfImage,
                                ViewUnmap,
                                0,
                                PAGE_EXECUTE);

    /* Dereference the section */
    ObDereferenceObject(SectionObject);

    /* Check if mapping succeeded, but the image is not our architecture */
    if (Status == STATUS_IMAGE_MACHINE_TYPE_MISMATCH)
    {
        /* Return failure */
        Status = STATUS_INVALID_IMAGE_FORMAT;
    }

    if (!NT_SUCCESS(Status))
    {
        ERR("MmMapViewOfSection failed with status 0x%x\n", Status);
        goto Cleanup;
    }

    /* Calculate how many pages we need */
    NumberOfPages = BYTES_TO_PAGES(SizeOfImage);

    /* Get the base address from the section */
    DriverBase = reinterpret_cast<PSECTION_OBJECT>(SectionObject)->GetBaseAddress();

    /* Check if this is a session load */
    if (Flags & 1)
    {
        /// FIXME, we should use the session address space!
        AddressSpace = &g_KernelAddressSpace;
    }
    else
    {
        AddressSpace = &g_KernelAddressSpace;
    }

    /* Reserve virtual address space */
    Status = AddressSpace->ReserveVirtualMemory(&DriverBase,
                                                NumberOfPages,
                                                MM_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        /* Try with a different address */
        DriverBase = NULL;
        Status = AddressSpace->ReserveVirtualMemory(&DriverBase,
                                                    NumberOfPages,
                                                    MM_READWRITE);
        if (!NT_SUCCESS(Status))
        {
            goto Cleanup;
        }
    }

    /// FIXME we need to prepare the mapping range

    Status = MapNonPagedMemory(AddressToVpn(DriverBase), NumberOfPages, MM_EXECUTE_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        /* Cleanup and return failure */
        goto Cleanup;
    }

    /* Copy the image to the new location */
    RtlCopyMemory(DriverBase, MappingBase, SizeOfImage);

    /// MiCheckSystemImage

    /* Create the loader entry */
    LdrEntry = CreateLdrEntry(FileName,
                              LoadedName,
                              DriverBase,
                              SizeOfImage);

    DbgPrint("LoadSystemImageInternal MappingBase=%p, DllBase = %p\n", MappingBase, LdrEntry->DllBase);

    /* Set result status */
    Status = (LdrEntry == NULL) ? STATUS_INSUFFICIENT_RESOURCES : STATUS_SUCCESS;

Cleanup:

    /* Did we map the image? */
    if (MappingBase != NULL)
    {
        /* Unmap the image */
        Status = MmUnmapViewOfSection(PsGetCurrentProcess(), MappingBase);
        DbgPrint("Status = 0x%lx\n", Status);
        NT_ASSERT(NT_SUCCESS(Status));
    }

    /* Detach from the system process */
    KeUnstackDetachProcess(&ApcState);

    if (!NT_SUCCESS(Status))
    {
        /* Check if we mapped memory for the driver */
        if (DriverBase != NULL)
        {
            UnmapSystemMappingRange(DriverBase, NumberOfPages);
            ReleaseSystemMappingRange(DriverBase);
        }
    }

    *OutLdrEntry = LdrEntry;
    return Status;
}

VOID
ReleaseImportedModules (
    PVOID ImportDirectory)
{
    UNIMPLEMENTED;
}

VOID
UnloadSystemImageInternal (
    PLDR_DATA_TABLE_ENTRY LdrEntry)
{
    PVOID ImportDirectory;
    ULONG ImportSize;

    /* Get the import descriptor */
    ImportDirectory = RtlImageDirectoryEntryToData(LdrEntry->DllBase,
                                                   TRUE,
                                                   IMAGE_DIRECTORY_ENTRY_IMPORT,
                                                   &ImportSize);
    if (ImportDirectory != NULL)
    {
        return ReleaseImportedModules(ImportDirectory);
    }

    DbgPrint("Releasing driver mapping, DllBase = %p\n", LdrEntry->DllBase);
    ReleaseSystemMappingRange(LdrEntry->DllBase);

    ExFreePoolWithTag(LdrEntry, TAG_MODULE_OBJECT);
}

static
PVOID
FindExportByName (
    _In_ PVOID DllBase,
    _In_ PIMAGE_EXPORT_DIRECTORY ExportDirectory,
    _In_ USHORT Hint,
    _In_ PCHAR Name)
{
    PULONG NameTable, ExportTable;
    PUSHORT OrdinalTable;
    LONG IndexLow, IndexMid, IndexHigh, Result;
    USHORT Ordinal;

    /* Get the export tables */
    NameTable = (PULONG)AddToPointer(DllBase, ExportDirectory->AddressOfNames);
    OrdinalTable = (PUSHORT)AddToPointer(DllBase, ExportDirectory->AddressOfNameOrdinals);
    ExportTable = (PULONG)AddToPointer(DllBase, ExportDirectory->AddressOfFunctions);

    /* Check if we got a valid hint */
    if ((Hint < ExportDirectory->NumberOfNames) &&
        !strcmp((PCHAR)DllBase + NameTable[Hint], Name))
    {
        /* We have a match, get the ordinal number from here */
        Ordinal = OrdinalTable[Hint];
    }
    else
    {
        /* Do a binary search */
        //IndexMid = BinarySearch<ULONG, >(NameTable,
        //                        ExportDirectory->NumberOfNames,
        //                        Name);
        IndexLow = 0;
        IndexHigh = ExportDirectory->NumberOfNames;
        while (IndexLow < IndexHigh)
        {
            /* Get new middle value */
            IndexMid = (IndexLow + IndexHigh) / 2;

            /* Compare name */
            //DbgPrint("Comparing '%s' and '%s' (%lu)\n", Name, (PCHAR)DllBase + NameTable[IndexMid], IndexMid);
            Result = strcmp(Name, (PCHAR)DllBase + NameTable[IndexMid]);
            if (Result < 0)
            {
                /* Update high */
                IndexHigh = IndexMid;
            }
            else if (Result > 0)
            {
                /* Update low */
                IndexLow = IndexMid + 1;
            }
            else
            {
                /* We got it */
                break;
            }
        }

        /* Check if we couldn't find it */
        if (IndexHigh <= IndexLow)
        {
            return NULL;
        }

        /* Otherwise, this is the ordinal */
        Ordinal = OrdinalTable[IndexMid];
    }

    NT_ASSERT(Ordinal < ExportDirectory->NumberOfFunctions);

    /* Resolve the address and return it */
    return AddToPointer(DllBase, ExportTable[Ordinal]);
}

static
NTSTATUS
CallDllInitialize (
    _In_ PLDR_DATA_TABLE_ENTRY LdrEntry)
{
    UNIMPLEMENTED;
    return STATUS_SUCCESS;
}

/// FIXME: make this a template for 32/64 bit
static
NTSTATUS
ProcessImportDescriptor (
    _In_ PVOID ImageBase,
    _In_ PIMAGE_IMPORT_DESCRIPTOR ImportDescriptor,
    _In_ PVOID DllBase)
{
    PIMAGE_EXPORT_DIRECTORY ExportDirectory;
    PIMAGE_THUNK_DATA NameThunk, AddressThunk;
    PULONG ExportTable;
    ULONG ExportSize;
    ULONG_PTR Ordinal;
    PVOID Function;
    PIMAGE_IMPORT_BY_NAME NameImport;

    NT_ASSERT(ImportDescriptor->OriginalFirstThunk != 0);
    NT_ASSERT(ImportDescriptor->FirstThunk != 0);

    /* Get the export directory */
    ExportDirectory = static_cast<PIMAGE_EXPORT_DIRECTORY>(
                      RtlImageDirectoryEntryToData(DllBase,
                                                   TRUE,
                                                   IMAGE_DIRECTORY_ENTRY_EXPORT,
                                                   &ExportSize));
    if (ExportDirectory == NULL)
    {
        return STATUS_UNSUCCESSFUL;
    }

    /* Get the tables */
    NameThunk = static_cast<PIMAGE_THUNK_DATA>(
        AddToPointer(ImageBase, ImportDescriptor->OriginalFirstThunk));
    AddressThunk = static_cast<PIMAGE_THUNK_DATA>(
        AddToPointer(ImageBase, ImportDescriptor->FirstThunk));
    ExportTable = static_cast<PULONG>(
        AddToPointer(DllBase, ExportDirectory->AddressOfFunctions));

    /* Loop all import thunks */
    while (NameThunk->u1.Ordinal != 0)
    {
        /* Is this an import by ordinal? */
        if (IMAGE_SNAP_BY_ORDINAL(NameThunk->u1.Ordinal))
        {
            /* Calculate the ordinal */
            Ordinal = IMAGE_ORDINAL(NameThunk->u1.Ordinal) - ExportDirectory->Base;

            /* Check if the ordinal is invalid */
            if (Ordinal >= ExportDirectory->NumberOfFunctions)
            {
                /* Fail */
                return STATUS_DRIVER_ORDINAL_NOT_FOUND;
            }

            /* Store the function address */
            AddressThunk->u1.Function = (ULONG_PTR)DllBase + ExportTable[Ordinal];
        }
        else
        {
            /* Get the name import data */
            NameImport = static_cast<PIMAGE_IMPORT_BY_NAME>(
                AddToPointer(ImageBase, NameThunk->u1.AddressOfData));

            /* Find the export by name or hint */
            Function = FindExportByName(DllBase,
                                        ExportDirectory,
                                        NameImport->Hint,
                                        (PCHAR)NameImport->Name);
            if (Function == NULL)
            {
                ERR("Failed to find export '%s' in DLL '%s'\n",
                    NameImport->Name, AddToPointer(DllBase, ExportDirectory->Name));
                return STATUS_UNSUCCESSFUL;
            }

            /* Store the function address */
            AddressThunk->u1.Function = (ULONG_PTR)Function;
        }

        /* Check if the function is actually a forwarder */
        if ((AddressThunk->u1.Function > (ULONG_PTR)ExportDirectory) &&
            (AddressThunk->u1.Function < ((ULONG_PTR)ExportDirectory + ExportSize)))
        {
            /* It is, fail */
            UNIMPLEMENTED_DBGBREAK;
            return 0;
        }

        /* Next thunks */
        NameThunk++;
        AddressThunk++;
    }

    return STATUS_SUCCESS;
}


static
NTSTATUS
ResolveImageReferences (
    _Inout_ PVOID ImageBase,
    _In_ PUNICODE_STRING BaseDirectory)
{
    PVOID ImportDirectory;
    ULONG ImportSize;
    PIMAGE_IMPORT_DESCRIPTOR CurrentImport;
    WCHAR StringBuffer[MAX_PATH];
    UNICODE_STRING FullPathName, DllName;
    ANSI_STRING DllNameAnsi;
    PLDR_DATA_TABLE_ENTRY DllLdrEntry;
    PVOID DllBase;
    NTSTATUS Status;

    /* Fill the string buffer with the base directory */
    RtlInitEmptyUnicodeString(&FullPathName, StringBuffer, sizeof(StringBuffer));
    RtlCopyUnicodeString(&FullPathName, BaseDirectory);

    /* Initialize the DllName string to start after the base directory */
    DllName.Buffer = &StringBuffer[FullPathName.Length / sizeof(WCHAR)];
    DllName.MaximumLength = sizeof(StringBuffer) - FullPathName.Length;
    DllName.Length = 0;

    /* Get the import descriptor */
    ImportDirectory = RtlImageDirectoryEntryToData(ImageBase,
                                                   TRUE,
                                                   IMAGE_DIRECTORY_ENTRY_IMPORT,
                                                   &ImportSize);
    if (ImportDirectory == NULL)
    {
        /* No import directory means no work to do. */
        return STATUS_SUCCESS;
    }

    /* Loop all imports */
    CurrentImport = static_cast<PIMAGE_IMPORT_DESCRIPTOR>(ImportDirectory);
    while ((CurrentImport->Name) && (CurrentImport->OriginalFirstThunk))
    {
        /* Get the DLL name */
        PSTR ImportName = (PCHAR)ImageBase + CurrentImport->Name;
        RtlInitAnsiString(&DllNameAnsi, ImportName);

        /* Check for buffer overflow */
        if (BaseDirectory->Length + DllNameAnsi.Length > sizeof(StringBuffer))
        {
            Status = STATUS_NAME_TOO_LONG;
            break;
        }

        /* Convert the name to unicode, appending it after the path */
        Status = RtlAnsiStringToUnicodeString(&DllName, &DllNameAnsi, FALSE);
        NT_ASSERT(NT_SUCCESS(Status));
        if (!NT_SUCCESS(Status))
        {
            break;
        }

        /* Create a full path name */
        FullPathName.Length = BaseDirectory->Length + DllName.Length;

        /* Recursively load the DLL */
        Status = MmLoadSystemImage(&FullPathName,
                                   NULL,
                                   &DllName,
                                   LDRP_DRIVER_DEPENDENT_DLL,
                                   (PVOID*)&DllLdrEntry,
                                   &DllBase);
        if (Status == STATUS_IMAGE_ALREADY_LOADED)
        {
            DllLdrEntry->LoadCount++;
            Status = STATUS_SUCCESS;
        }
        else if (!NT_SUCCESS(Status))
        {
            break;
        }
        else
        {
            NT_ASSERT(DllLdrEntry->LoadCount == 1);
        }

        /* Check if we still need to call the init routine */
        if (DllLdrEntry->LoadCount == 1)
        {
            /* Call the DLL entry point */
            Status = CallDllInitialize(DllLdrEntry);
            if (!NT_SUCCESS(Status))
            {
                /* Go ahead, since we loaded the image */
                CurrentImport++;
                break;
            }
        }

        DllLdrEntry->Flags |= LDRP_DRIVER_DEPENDENT_DLL;


        Status = ProcessImportDescriptor(ImageBase,
                                         CurrentImport,
                                         DllLdrEntry->DllBase);

        /* Go ahead, since we loaded the image */
        CurrentImport++;

        if (!NT_SUCCESS(Status))
        {
            break;
        }
    }

    if (!NT_SUCCESS(Status))
    {
        CurrentImport->OriginalFirstThunk = 0;
        ReleaseImportedModules(ImportDirectory);
    }

    return Status;
}

VOID
WriteProtectSystemImage (
    PVOID ImageBase)
{
}


extern "C" {

/*! \fn MiResolveImageReferences
 *
 *  \brief ...
 *
 *  \param [in] ImageBase -
 *
 *  \param [in] ImageFileDirectory -
 *
 *  \param [in] NamePrefix -
 *
 *  \param [in] MissingApi -
 *
 *  \param [in] MissingDriver -
 *
 *  \param [in] LoadImports -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MiResolveImageReferences (
    _In_ PVOID ImageBase,
    _In_ PUNICODE_STRING ImageFileDirectory,
    _Reserved_ PUNICODE_STRING NamePrefix,
    _Out_ PCHAR *MissingApi,
    _Out_ PWCHAR *MissingDriver,
    _Out_ struct _LOAD_IMPORTS** LoadImports)
{
    return ResolveImageReferences(ImageBase, ImageFileDirectory);
}

/*! \fn MmLoadSystemImage
 *
 *  \brief ...
 *
 *  \param [in] FileName -
 *
 *  \param [in] NamePrefix -
 *
 *  \param [in] LoadedName -
 *
 *  \param [in] Flags -
 *
 *  \param [out] ModuleObject -
 *
 *  \param [out] ImageBaseAddress -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmLoadSystemImage (
    _In_ PUNICODE_STRING FileName,
    _Reserved_ PUNICODE_STRING NamePrefix,
    _In_opt_ PUNICODE_STRING LoadedName,
    _In_ ULONG Flags,
    _Out_ PVOID *ModuleObject,
    _Out_ PVOID *ImageBaseAddress)
{
    PLDR_DATA_TABLE_ENTRY LdrEntry, FoundLdrEntry;
    UNICODE_STRING BaseDirectory, BaseName;
    NTSTATUS Status;
    ERR("MmLoadSystemImage('%wZ')\n", FileName);

    /* A name prefix is not supported! */
    NT_ASSERT(NamePrefix == NULL);

    /* Acquire the loader lock */
    AcquireLoaderLock();

    /* Try to find an entry with the name */
    LdrEntry = FindLoaderEntry(FileName, LoadedName);

    /* Did we find it? */
    if (LdrEntry == NULL)
    {
        /* Release the loader lock */
        ReleaseLoaderLock();

        /* Separate the path into directory and file name */
        SeperatePath(FileName, &BaseDirectory, &BaseName);

        /* If we have a LoadedName, use that instead */
        if (LoadedName != NULL)
        {
            BaseName = *LoadedName;
        }

        /* Load the image into memory */
        Status = LoadSystemImageInternal(&LdrEntry, FileName, &BaseName, Flags);
        if (!NT_SUCCESS(Status))
        {
            ERR("LoadSystemImageInternal failed with status 0x%lx\n", Status);
            return Status;
        }

        /* Relocate the image */
        Status = LdrRelocateImageWithBias(LdrEntry->DllBase,
                                          0,
                                          "SYSLDR",
                                          STATUS_SUCCESS,
                                          STATUS_CONFLICTING_ADDRESSES,
                                          STATUS_INVALID_IMAGE_FORMAT);
        if (!NT_SUCCESS(Status))
        {
            ERR("LdrRelocateImageWithBias failed with status 0x%x\n", Status);
            UnloadSystemImageInternal(LdrEntry);
            return Status;
        }

        /* Patch the image */
        PatchLoadedSystemImage(FileName, LdrEntry->DllBase);

        /* Acquire the loader lock again */
        AcquireLoaderLock();

        /* Search for the entry again and check if it's still not there */
        FoundLdrEntry = FindLoaderEntry(FileName, LoadedName);
        if (FoundLdrEntry == NULL)
        {
            /// We could call the DLL initialize routine here. Or we could also
            /// call it for already loaded modules (which would be more logical)
            /// but that would mean, we would call it for ntoskrnl/hal as well

            /* Mark the entry as in progress */
            LdrEntry->Flags |= LDRP_LOAD_IN_PROGRESS;

            /* Acquire the module list lock */
            ExAcquireResourceExclusiveLite(&PsLoadedModuleResource, TRUE);

            /* Insert the new entry */
            InsertTailList(&PsLoadedModuleList, &LdrEntry->InLoadOrderLinks);

            /* Release the module list lock */
            ExReleaseResource(&PsLoadedModuleResource);

            /* Resolve imports (still need to hold the loader lock!) */
            Status = ResolveImageReferences(LdrEntry->DllBase, &BaseDirectory);
            if (!NT_SUCCESS(Status))
            {
                ERR("ResolveImageReferences failed with status 0x%x\n", Status);

                /* Release the loader lock */
                ReleaseLoaderLock();

                /* Unload the image and return the failure code */
                MmUnloadSystemImage(LdrEntry);
                return Status;
            }

            /* Loading this image is finished, remove the flag */
            LdrEntry->Flags &= ~LDRP_LOAD_IN_PROGRESS;
        }
        else
        {
            /* Someone else raced us, unload our newly created entry */
            UnloadSystemImageInternal(LdrEntry);
            LdrEntry = FoundLdrEntry;
        }
    }

    /* Check if the image was already completely loaded */
    if (LdrEntry->LoadCount > 0)
    {
        /* Return the correspronding status code */
        Status = STATUS_IMAGE_ALREADY_LOADED;
    }
    else
    {
        LdrEntry->LoadCount = 1;
        Status = STATUS_SUCCESS;
    }

    /* Release the loader lock */
    ReleaseLoaderLock();

    /* Check if the image was already loaded */
    if (Status == STATUS_IMAGE_ALREADY_LOADED)
    {
        /* Check if this is a session load */
        if (Flags & 1)
        {
            UNIMPLEMENTED;
            __debugbreak(); __debugbreak();
            return STATUS_NOT_IMPLEMENTED;
        }
    }
    else
    {
        DbgPrint("=====> Loaded image at %p\n", LdrEntry->DllBase);

        /* Write-protect the system image */
        WriteProtectSystemImage(LdrEntry->DllBase);

        /* Check if notifications are enabled */
        if (PsImageNotifyEnabled)
        {
            IMAGE_INFO ImageInfo;

            /* Fill out the notification data */
            ImageInfo.Properties = 0;
            ImageInfo.ImageAddressingMode = IMAGE_ADDRESSING_MODE_32BIT;
            ImageInfo.SystemModeImage = TRUE;
            ImageInfo.ImageSize = LdrEntry->SizeOfImage;
            ImageInfo.ImageBase = LdrEntry->DllBase;
            ImageInfo.ImageSectionNumber = ImageInfo.ImageSelector = 0;

            /* Send the notification */
            //PspRunLoadImageNotifyRoutines(FileName, NULL, &ImageInfo);
        }
    }

    /* Return the data */
    *ModuleObject = LdrEntry;
    *ImageBaseAddress = LdrEntry->DllBase;

DbgPrint("MmLoadSystemImage: entry %p, file '%wZ' count = %u\n", LdrEntry, &LdrEntry->BaseDllName, LdrEntry->LoadCount);
//__debugbreak();__debugbreak();

    return Status;
}


/*! \fn MmUnloadSystemImage
 *
 *  \brief ...
 *
 *  \param [in] ImageHandle -
 *
 *  \return ...
 */
NTSTATUS
NTAPI
MmUnloadSystemImage (
    _In_ PVOID ImageHandle)
{
    PLDR_DATA_TABLE_ENTRY LdrEntry = (PLDR_DATA_TABLE_ENTRY)ImageHandle;

    /* Acquire the loader lock */
    AcquireLoaderLock();

    /* Dereference the loader entry */
    LdrEntry->LoadCount--;
    if ((LdrEntry->LoadCount == 0) && !(LdrEntry->Flags & LDR_COR_OWNS_UNMAP))
    {
        /* Remove the entry from the module list */
        RemoveEntryList(&LdrEntry->InLoadOrderLinks);

        UnloadSystemImageInternal(LdrEntry);
    }

    /* Release the loader lock */
    ReleaseLoaderLock();

    return STATUS_SUCCESS;
}

/*! \fn MmGetSystemRoutineAddress
 *
 *  \brief ...
 *
 *  \param [in] SystemRoutineName -
 *
 *  \return ...
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
PVOID
NTAPI
MmGetSystemRoutineAddress (
    _In_ PUNICODE_STRING SystemRoutineName)
{
    CHAR NameBuffer[64];
    ANSI_STRING AnsiName;
    PIMAGE_EXPORT_DIRECTORY ExportDirectory;
    ULONG ExportSize;
    NTSTATUS Status;
    PVOID RoutineAddress;

    TRACE("MmGetSystemRoutineAddress(%wZ)\n", SystemRoutineName);

    /* Initialize an ansi string for the name */
    RtlInitEmptyAnsiString(&AnsiName, NameBuffer, sizeof(NameBuffer));

    /* Convert the unicode name to ansi */
    Status = RtlUnicodeStringToAnsiString(&AnsiName, SystemRoutineName, FALSE);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to convert unicode string name '%wZ' to ansi\n", SystemRoutineName);
        return NULL;
    }

    /* Get the export directory */
    ExportDirectory = static_cast<PIMAGE_EXPORT_DIRECTORY>(
                      RtlImageDirectoryEntryToData((PVOID)PsNtosImageBase,
                                                   TRUE,
                                                   IMAGE_DIRECTORY_ENTRY_EXPORT,
                                                   &ExportSize));
    if (ExportDirectory == NULL)
    {
        ERR("Failed to get NT export directory %p\n", PsNtosImageBase);
        return NULL;
    }

    /* Find the address */
    RoutineAddress = FindExportByName((PVOID)PsNtosImageBase,
                                      ExportDirectory,
                                      -1,
                                      NameBuffer);
    if (RoutineAddress == NULL)
    {
        ERR("Couldn't locate routine '%Z' in the kernel\n", &AnsiName);
        __debugbreak();
        __debugbreak();
    }

    return RoutineAddress;
}


PVOID
NTAPI
MmFindModuleImport (
    PWCHAR ModuleName,
    PCHAR RoutineName)
{
    UNICODE_STRING ModuleNameU;
    PVOID RoutineAddress;
    PIMAGE_EXPORT_DIRECTORY ExportDirectory;
    ULONG ExportSize;
    PLDR_DATA_TABLE_ENTRY LdrEntry;

    RtlInitUnicodeString(&ModuleNameU, ModuleName);

    LdrEntry = FindLoaderEntry(NULL, &ModuleNameU);
    if (LdrEntry == NULL)
    {
        ERR("Failed to locate module '%wZ'\n", &ModuleNameU);
        return NULL;
    }

    /* Get the export directory */
    ExportDirectory = static_cast<PIMAGE_EXPORT_DIRECTORY>(
                      RtlImageDirectoryEntryToData(LdrEntry->DllBase,
                                                   TRUE,
                                                   IMAGE_DIRECTORY_ENTRY_EXPORT,
                                                   &ExportSize));
    if (ExportDirectory == NULL)
    {
        ERR("Failed to get NT export directory %p\n", PsNtosImageBase);
        return NULL;
    }

    /* Find the address */
    RoutineAddress = FindExportByName(LdrEntry->DllBase,
                                      ExportDirectory,
                                      -1,
                                      RoutineName);
    if (RoutineAddress == NULL)
    {
        ERR("Couldn't locate routine '%s' in module '%s'\n", RoutineName, ModuleName);
        __debugbreak();
        __debugbreak();
    }

    return RoutineAddress;
}

}; // extern "C"
}; // namespace Mm



/*!

    \file SysLoader.cpp

    \brief Implements the system image loader

    \copyright Distributed under the terms of the GNU GPL v2.
               http://www.gnu.org/licenses/gpl-2.0.html

    \author Timo Kreuzer

*/

#include "ntosbase.h"
#include <ntimage.h>
#include <ldrtypes.h>
#include <rtlfuncs.h>
#include <mmfuncs.h>
#include <obfuncs.h>
#include "Mapping.hpp"

#define TAG_MODULE_OBJECT 0

namespace Mm {

ERESOURCE PsLoadedModuleResource;
KMUTANT SystemLoaderLock;
extern "C" LIST_ENTRY PsLoadedModuleList;
extern "C" BOOLEAN PsImageNotifyEnabled;

extern "C"
NTSTATUS
NTAPI
MmLoadSystemImage (
    _In_ PUNICODE_STRING FileName,
    _Reserved_ PUNICODE_STRING NamePrefix,
    _In_opt_ PUNICODE_STRING LoadedName,
    _In_ ULONG Flags,
    _Out_ PVOID *ModuleObject,
    _Out_ PVOID *ImageBaseAddress);

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
    PathName->Length = (USHORT)(Current - PathName->Buffer);
    PathName->MaximumLength = PathName->Length;
}

static
PLDR_DATA_TABLE_ENTRY
ReferenceLoaderEntry (
    _In_ PUNICODE_STRING FileName,
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
            FoundEntry->LoadCount++;
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
    LdrEntry->LoadCount = 1;
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


NTSTATUS
LoadSystemImageInternal (
    _In_ PUNICODE_STRING FileName,
    _In_ PUNICODE_STRING LoadedName,
    _Out_ PLDR_DATA_TABLE_ENTRY* OutLdrEntry)
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

    /* Close the file handle */
    ObCloseHandle(FileHandle, KernelMode);

    if (!NT_SUCCESS(Status))
    {
        ERR("MmCreateSection failed, status 0x%x\n", Status);
        return Status;
    }

    /* Calculate how many bytes we need */
    NumberOfPages = BYTES_TO_PAGES(SectionSize.QuadPart);

    /* Allocate a mapping range */
    DriverBase = ReserveSystemMappingRange(NumberOfPages);
    if (DriverBase == NULL)
    {
        /* Dereference the section and return failure */
        ObDereferenceObject(SectionObject);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = MapNonPagedMemory(AddressToVpn(DriverBase), NumberOfPages, MM_EXECUTE_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        /* Cleanup and return failure */
        ObDereferenceObject(SectionObject);
        ReleaseSystemMappingRange(DriverBase);
        return Status;
    }

    /* Attach to the system process */
    KeStackAttachProcess(&PsInitialSystemProcess->Pcb, &ApcState);

    /* Map the section into the system process address space */
    SectionOffset.QuadPart = 0;
    SizeOfImage = 0;
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
        /* Unmap the image */
        Status = MmUnmapViewOfSection(PsGetCurrentProcess(), MappingBase);
        NT_ASSERT(NT_SUCCESS(Status));

        /* Return failure */
        Status = STATUS_INVALID_IMAGE_FORMAT;
    }

    if (NT_SUCCESS(Status))
    {
        /* Copy the image to the new location */
        RtlCopyMemory(DriverBase, MappingBase, SizeOfImage);

        Status = MmUnmapViewOfSection(PsGetCurrentProcess(), MappingBase);
        NT_ASSERT(NT_SUCCESS(Status));
    }

    /* Detach from the system process */
    KeUnstackDetachProcess(&ApcState);

    if (!NT_SUCCESS(Status))
    {
        ERR("MmMapViewOfSection failed with status 0x%x\n", Status);
        goto Cleanup;
    }

    /// MiCheckSystemImage

    /* Create the loader entry */
    LdrEntry = CreateLdrEntry(FileName,
                              LoadedName,
                              DriverBase,
                              SizeOfImage);

    /* Set result status */
    Status = (LdrEntry == NULL) ? STATUS_INSUFFICIENT_RESOURCES : STATUS_SUCCESS;

Cleanup:


    if (!NT_SUCCESS(Status))
    {
        /* Check if we mapped memory for the driver */
        if (DriverBase != NULL)
        {
            //Unmap,,,
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

    ReleaseSystemMappingRange(LdrEntry->DllBase);

    ExFreePoolWithTag(LdrEntry, TAG_MODULE_OBJECT);
}

static
NTSTATUS
CallDllInitialize (
    _In_ PLDR_DATA_TABLE_ENTRY LdrEntry)
{
    UNIMPLEMENTED_DBGBREAK;
    return STATUS_NOT_IMPLEMENTED;
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

        Status = RtlAnsiStringToUnicodeString(&DllName, &DllNameAnsi, FALSE);
        NT_ASSERT(NT_SUCCESS(Status));
        if (!NT_SUCCESS(Status))
        {
            break;
        }

        /* Create a full path name */
        FullPathName.Length = BaseDirectory->Length + DllName.Length;

        /* Acquire the loader lock. This is needed to
           synchronize the call to the DLL init routine! */
        AcquireLoaderLock();

        /* Recursively load the DLL */
        Status = MmLoadSystemImage(&FullPathName,
                                   NULL,
                                   &DllName,
                                   LDRP_DRIVER_DEPENDENT_DLL,
                                   (PVOID*)&DllLdrEntry,
                                   &DllBase);
        if (NT_SUCCESS(Status))
        {
            /* Go ahead, since we loaded the image */
            CurrentImport++;

            /* Check if we still need to call the init routine */
            if (DllLdrEntry->LoadCount == 1)
            {
                /* Call the DLL entry point */
                Status = CallDllInitialize(DllLdrEntry);
            }

            DllLdrEntry->Flags |= LDRP_DRIVER_DEPENDENT_DLL;
        }

        /* Release the loader lock */
        ReleaseLoaderLock();

        /* Check for failure above */
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

    /* A name prefix is not supported! */
    NT_ASSERT(NamePrefix == NULL);

    /* Acquire the loader lock */
    AcquireLoaderLock();

    /* Find an entry with the name */
    FoundLdrEntry = ReferenceLoaderEntry(FileName, LoadedName);

    /* Release the loader lock */
    ReleaseLoaderLock();

    /* Did we find the entry? */
    if (FoundLdrEntry != NULL)
    {
        /* Check if this is a session load */
        if (Flags & 1)
        {
            UNIMPLEMENTED;
            return STATUS_NOT_IMPLEMENTED;
        }

        /* Return the data */
        *ModuleObject = FoundLdrEntry;
        *ImageBaseAddress = FoundLdrEntry->DllBase;
        return STATUS_IMAGE_ALREADY_LOADED;
    }

    /* Separate the path into directory and file name */
    SeperatePath(FileName, &BaseDirectory, &BaseName);

    /* If we have a LoadedName, use that instead */
    if (LoadedName != NULL)
    {
        BaseName = *LoadedName;
    }

    /* We don't have the entry yet, so load the image */
    Status = LoadSystemImageInternal(FileName, &BaseName, &LdrEntry);
    if (!NT_SUCCESS(Status))
    {
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

    /* Resolve imports */
    Status = ResolveImageReferences(LdrEntry->DllBase, &BaseDirectory);
    if (!NT_SUCCESS(Status))
    {
        ERR("ResolveImageReferences failed with status 0x%x\n", Status);
        UnloadSystemImageInternal(LdrEntry);
        return Status;
    }

    /* Write-protect the system image */
    WriteProtectSystemImage(LdrEntry->DllBase);

    /* Acquire the loader lock */
    AcquireLoaderLock();

    /* Search for the entry again and check if it's still not there */
    FoundLdrEntry = ReferenceLoaderEntry(FileName, LoadedName);

    /* Did we find an entry? */
    if (FoundLdrEntry == NULL)
    {
        /// We could call the DLL initialize routine here. Or we could also
        /// call it for already loaded modules (which would be more logical)
        /// but that would mean, we would call it for ntoskrnl/hal as well

        /* Acquire the module list lock */
        ExAcquireResourceExclusiveLite(&PsLoadedModuleResource, TRUE);

        /* Insert the new entry */
        InsertTailList(&PsLoadedModuleList, &LdrEntry->InLoadOrderLinks);

        /* Release the module list lock */
        ExReleaseResource(&PsLoadedModuleResource);
    }

    /* Release the loader lock */
    ReleaseLoaderLock();

    /* Did we find an entry? */
    if (FoundLdrEntry != NULL)
    {
        /* Someone else raced us, unload our newly created entry */
        UnloadSystemImageInternal(LdrEntry);

        /* Use the entry we found instead */
        LdrEntry = FoundLdrEntry;
    }

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

    return STATUS_SUCCESS;
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

    /* Remove the entry from the module list */
    RemoveEntryList(&LdrEntry->InLoadOrderLinks);

    UnloadSystemImageInternal(LdrEntry);

    /* Release the loader lock */
    ReleaseLoaderLock();


    return STATUS_SUCCESS;
}

}; // extern "C"
}; // namespace Mm





#include "PhysicalSection.hpp"
#include "ntintsafe.h"
#include <ndk/pstypes.h>

#define DPRINT(...)

#define AslrEnabled(NtHeaders) 0 /// For now disable ASLR
    // (NtHeaders->OptionalHeader.DllCharacteristics & IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE)

namespace Mm {

extern ULONG RandomNumberSeed;

PSECTION_IMAGE_INFORMATION_EX
GetSectionImageInformation (
    _In_ PIMAGE_NT_HEADERS NtHeaders)
{
    PSECTION_IMAGE_INFORMATION_EX ImageInfo;

    /* Allocate image information from paged pool */
    ImageInfo = static_cast<PSECTION_IMAGE_INFORMATION_EX>(
        ExAllocatePoolWithTag(PagedPool, sizeof(*ImageInfo), 'iImM'));
    if (ImageInfo == NULL)
    {
        return NULL;
    }

    /* Fill in the fields */
    ImageInfo->ImageCharacteristics = NtHeaders->FileHeader.Characteristics;
    ImageInfo->Machine = NtHeaders->FileHeader.Machine;
    ImageInfo->SubSystemType = NtHeaders->OptionalHeader.Subsystem;
    ImageInfo->SubSystemMinorVersion = NtHeaders->OptionalHeader.MinorSubsystemVersion;
    ImageInfo->SubSystemMajorVersion = NtHeaders->OptionalHeader.MajorSubsystemVersion;
    ImageInfo->DllCharacteristics = NtHeaders->OptionalHeader.DllCharacteristics;
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    ImageInfo->CheckSum = NtHeaders->OptionalHeader.CheckSum;
#endif
    ImageInfo->SizeOfHeaders = NtHeaders->OptionalHeader.SizeOfHeaders;
    ImageInfo->SizeOfImage = NtHeaders->OptionalHeader.SizeOfImage;

    if (NtHeaders->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        PIMAGE_OPTIONAL_HEADER64 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER64>(&NtHeaders->OptionalHeader);

        ImageInfo->TransferAddress = reinterpret_cast<PVOID>(
            NtHeaders->OptionalHeader.ImageBase +
            NtHeaders->OptionalHeader.AddressOfEntryPoint);
        ImageInfo->MaximumStackSize = (ULONG_PTR)OptionalHeader->SizeOfStackReserve;
        ImageInfo->CommittedStackSize = (ULONG_PTR)OptionalHeader->SizeOfStackCommit;
        ImageInfo->LoaderFlags = OptionalHeader->LoaderFlags;
    }
    else
    {
        PIMAGE_OPTIONAL_HEADER32 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER32>(&NtHeaders->OptionalHeader);

        ImageInfo->TransferAddress = reinterpret_cast<PVOID>(
            NtHeaders->OptionalHeader.ImageBase +
            NtHeaders->OptionalHeader.AddressOfEntryPoint);
        ImageInfo->MaximumStackSize = OptionalHeader->SizeOfStackReserve;
        ImageInfo->CommittedStackSize = OptionalHeader->SizeOfStackCommit;
        ImageInfo->LoaderFlags = OptionalHeader->LoaderFlags;
    }

    ImageInfo->ZeroBits = 0; /// \todo
    ImageInfo->ImageFileSize = 0; /// \todo
    ImageInfo->GpValue = 0; /// \todo
    ImageInfo->ImageContainsCode = TRUE; /// \todo
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
    ImageInfo->ImageFlags = 0; /// \todo
#endif

    return ImageInfo;
}

static
NTSTATUS
PageReadHelper (
    _In_ PFILE_OBJECT FileObject,
    _In_ SIZE_T FileOffset,
    _In_ PULONG Size,
    _Out_ PVOID* Buffer)
{
    PMDL Mdl;
    KEVENT Event;
    IO_STATUS_BLOCK IoStatusBlock;
    LARGE_INTEGER Offset;
    struct
    {
        MDL Mdl;
        PFN_NUMBER PfnArray[5];
    } MdlBuffer;
    NTSTATUS Status;

    /* Align the size up to pages */
    *Size = ALIGN_UP_BY(*Size, PAGE_SIZE);

    Offset.QuadPart = FileOffset;

    /* Allocate a page for the file header */
    *Buffer = ExAllocatePoolWithTag(NonPagedPool, *Size, TAG_TEMP);
    if (*Buffer == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Check if the request fits within the stack MDL */
    if (*Size < 5 * PAGE_SIZE)
    {
        /* Use the MDL on the stack */
        Mdl = &MdlBuffer.Mdl;
        MmInitializeMdl(Mdl, *Buffer, *Size); /// move into if
    }
    else
    {
        /* Allocate a new MDL */
        Mdl = IoAllocateMdl(*Buffer, *Size, FALSE, FALSE, NULL);
    }

    /* Build an MDL from the pool allocation */
    MmBuildMdlForNonPagedPool(Mdl);

    /* Initialize the event */
    KeInitializeEvent(&Event, NotificationEvent, FALSE);

    /* Read the first page */
    Status = IoPageRead(FileObject, Mdl, &Offset, &Event, &IoStatusBlock);
    if (Status == STATUS_PENDING)
    {
        KeWaitForSingleObject(&Event, WrPageIn, 0, 0, 0);
        Status = IoStatusBlock.Status;
    }

    if (!NT_SUCCESS(Status))
    {
        /// FIXME handle failure
        __debugbreak();
    }

    /* Return the actual read size */
    *Size = static_cast<ULONG>(IoStatusBlock.Information);

    return IoStatusBlock.Status;
}

static
NTSTATUS
VerifyNtHeaders (
    _In_ PIMAGE_NT_HEADERS NtHeaders)
{
    /* Check the signature */
    if (NtHeaders->Signature != IMAGE_NT_SIGNATURE)
    {
        return STATUS_INVALID_IMAGE_FORMAT;
    }

    /* Check if this is a 32 or 64 bit PE header */
    if (NtHeaders->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR_MAGIC)
    {
        PIMAGE_OPTIONAL_HEADER32 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER32>(&NtHeaders->OptionalHeader);

        /* Check if we have a valid optional header size */
        if (NtHeaders->FileHeader.SizeOfOptionalHeader < sizeof(*OptionalHeader))
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }
    }
#ifdef _Win64
    else if (NtHeaders->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        PIMAGE_OPTIONAL_HEADER64 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER64>(&NtHeaders->OptionalHeader);

        /* Check if we have a valid optional header size */
        if (NtHeaders->FileHeader.SizeOfOptionalHeader < sizeof(*OptionalHeader))
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }
    }
#endif /* _WIN64 */
    else
    {
        return STATUS_INVALID_IMAGE_FORMAT;
    }

    return STATUS_SUCCESS;
}

static
NTSTATUS
VerifySectionHeaders (
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PIMAGE_SECTION_HEADER SectionHeaders,
    _In_ ULONG FullHeaderSize,
    _In_ ULONG FileSize)
{
    ULONG NextRva, NumberOfSections, RawDataEnd, VirtualSize;
    NTSTATUS Status;

    NumberOfSections = NtHeaders->FileHeader.NumberOfSections;

    /* Calculate the required start of the next section */
    NextRva = ALIGN_UP_BY(FullHeaderSize, PAGE_SIZE);

    /* Loop all section headers */
    for (ULONG i = 0; i < NumberOfSections; i++)
    {
        /* Check if the RVA is page aligned */
        if (SectionHeaders[i].VirtualAddress & (PAGE_SIZE - 1))
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }

        /* Check if the RVAs are contiguous */
        if (SectionHeaders[i].VirtualAddress != NextRva)
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }

        /* Calculate the end of the data */
        Status = RtlULongAdd(SectionHeaders[i].PointerToRawData,
                             SectionHeaders[i].SizeOfRawData,
                             &RawDataEnd);

        /* Check if the data is inside the file */
        if (!NT_SUCCESS(Status) || (RawDataEnd > FileSize))
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }

        /* Calculate the virtual size of the section */
        VirtualSize = ALIGN_UP_BY(SectionHeaders[i].Misc.VirtualSize, PAGE_SIZE);

        /* Check if the raw size exceeds the virtual size */
        if (SectionHeaders[i].SizeOfRawData > VirtualSize)
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }

        /* Calculate the next section's RVA */
        NextRva += VirtualSize;
    }

    return STATUS_SUCCESS;
}

NTSTATUS
PHYSICAL_SECTION::CreateImageFileSection (
    _Out_ PPHYSICAL_SECTION* OutPhysicalSection,
    _In_ PFILE_OBJECT FileObject)
{
    PVOID DosHeaderBuffer, NtHeadersBuffer;
    PIMAGE_DOS_HEADER DosHeader;
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_SECTION_HEADER SectionHeaders;
    NTSTATUS Status;
    LARGE_INTEGER FileSize;
    PPHYSICAL_SECTION Section;
    ULONG NtHeaderOffset, Offset, ByteOffset, NumberOfPages, NumberOfSections;
    ULONG Size, SectorSize; //, AvailableHeaderSize;
    ULONG SizeOfSectionHeaders, NtHeaderSize, HeaderSize, FullHeaderSize;
    PVOID BaseAddress;
    SCHAR AslrOffset;
    UINT32 CommitSize;

//__debugbreak();

    DosHeaderBuffer = NULL;
    NtHeadersBuffer = NULL;
    BaseAddress = NULL;
    Section = NULL;

    /* Get the file size */
    Status = FsRtlGetFileSize(FileObject, &FileSize);
    if (!NT_SUCCESS(Status))
    {
        if (Status == STATUS_FILE_IS_A_DIRECTORY)
        {
            Status = STATUS_INVALID_FILE_FOR_SECTION;
        }
        goto Cleanup;
    }

    /* Check if the file is larger than 4GB */
    if (FileSize.HighPart != 0)
    {
        Status = STATUS_INVALID_FILE_FOR_SECTION;
        goto Cleanup;
    }

    /* Read the first page of the file */
    Size = PAGE_SIZE;
    Status = PageReadHelper(FileObject, 0, &Size, &DosHeaderBuffer);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Check if the file is large enough */
    if (Size < sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS))
    {
        Status = STATUS_INVALID_IMAGE_FORMAT;
        goto Cleanup;
    }

    /* DOS-Header is accessible, get a pointer to it */
    DosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(DosHeaderBuffer);

    /* Check DOS-Header signature */
    if (DosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        Status = STATUS_INVALID_IMAGE_NOT_MZ;
        goto Cleanup;
    }

    /* Get the offset to the NT-Headers and check if it's large enough */
    NtHeaderOffset = DosHeader->e_lfanew;
    if (NtHeaderOffset < sizeof(IMAGE_DOS_HEADER))
    {
        Status = STATUS_INVALID_IMAGE_FORMAT;
        goto Cleanup;
    }

    /* Check if the NT-Headers are fully inside the page. The subtraction
       cannot overflow due to the size check above. */
    if (NtHeaderOffset <= Size - sizeof(IMAGE_NT_HEADERS))
    {
        /* We can safely access the NT-Headers inside the first page */
        NtHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(
                                    AddToPointer(DosHeader, NtHeaderOffset));
        //AvailableHeaderSize = Size - NtHeaderOffset;
    }
    else
    {
        /* Check if the header offset overflows */
        if ((NtHeaderOffset + sizeof(IMAGE_NT_HEADERS)) < NtHeaderOffset)
        {
            Status = STATUS_INVALID_IMAGE_FORMAT;
            goto Cleanup;
        }

        ByteOffset = NtHeaderOffset & (PAGE_SIZE - 1);
        Offset = ALIGN_DOWN_BY(NtHeaderOffset, PAGE_SIZE);

        /* Read the NT-Headers (2 pages to be sure we get them completely) */
        Size = 2 * PAGE_SIZE;
        Status = PageReadHelper(FileObject, Offset, &Size, &NtHeadersBuffer);
        if (!NT_SUCCESS(Status))
        {
            goto Cleanup;
        }

        /* Check if we read enough data */
        if (Size < (ByteOffset + sizeof(IMAGE_NT_HEADERS)))
        {
            Status = STATUS_INVALID_IMAGE_FORMAT;
            goto Cleanup;
        }

        /* Get the NT-Headers and calculate the available size */
        NtHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(
            AddToPointer(NtHeadersBuffer, NtHeaderOffset & (PAGE_SIZE - 1)));
        //AvailableHeaderSize = Size - ByteOffset;
    }

    /* Verify that the NT-Headers are valid */
    Status = VerifyNtHeaders(NtHeaders);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Get the number of pages and the number of sections */
    NumberOfPages = BYTES_TO_PAGES(NtHeaders->OptionalHeader.SizeOfImage);
    NumberOfSections = NtHeaders->FileHeader.NumberOfSections;

    /* Create an empty section */
    Status = PHYSICAL_SECTION::CreateInstance(&Section,
                                              NumberOfSections + 1,
                                              NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Mark the section as an image section */
    Section->m_ControlArea.Flags.Image = TRUE;
    Section->m_ControlArea.FileObject = FileObject;

    /* Calculate the section header size */
    Status = RtlULongMult(NumberOfSections,
                          sizeof(IMAGE_SECTION_HEADER),
                          &SizeOfSectionHeaders);
    if (!NT_SUCCESS(Status))
    {
        Status = STATUS_INVALID_IMAGE_FORMAT;
        goto Cleanup;
    }

    /* Calculate the size of the full NT-Header (This cannot overflow, since
       SizeOfOptionalHeader is an USHORT. The field offset is the same for
       the 32 and 64 bit IMAGE_NT_HEADERS structure.) */
    NtHeaderSize = NtHeaders->FileHeader.SizeOfOptionalHeader +
                   FIELD_OFFSET(IMAGE_NT_HEADERS, OptionalHeader);

    /* Calculate the size of the headers including the section headers */
    Status = RtlULongAdd(NtHeaderSize, SizeOfSectionHeaders, &HeaderSize);
    if (!NT_SUCCESS(Status))
    {
        Status = STATUS_INVALID_IMAGE_FORMAT;
        goto Cleanup;
    }

    /* Calculate the full header size including offset and section headers
       and make sure it won't overflow when aligning up */
    Status = RtlULongAdd(NtHeaderOffset, HeaderSize, &FullHeaderSize);
    if (!NT_SUCCESS(Status) || (FullHeaderSize > (ULONG_MAX - PAGE_SIZE + 1)))
    {
        Status = STATUS_INVALID_IMAGE_FORMAT;
        goto Cleanup;
    }

    /* Align the full size up to pages (overflow was checked above) */
    FullHeaderSize = ALIGN_UP_BY(FullHeaderSize, PAGE_SIZE);

    /* Get the sector size */
    SectorSize = FileObject->DeviceObject->SectorSize;

    /* Check if this is a 32 or 64 bit PE header */
    if (NtHeaders->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        PIMAGE_OPTIONAL_HEADER64 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER64>(&NtHeaders->OptionalHeader);

        /* Set Image base */
        Section->m_ControlArea.BaseAddress = reinterpret_cast<PVOID>(OptionalHeader->ImageBase);
    }
    else if (NtHeaders->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR_MAGIC)
    {
        PIMAGE_OPTIONAL_HEADER32 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER32>(&NtHeaders->OptionalHeader);

        /* Set Image base */
        Section->m_ControlArea.BaseAddress = reinterpret_cast<PVOID>(OptionalHeader->ImageBase);
    }

    /* Check if ASLR is enabled */
    if (AslrEnabled(NtHeaders))
    {
        /* Check if this is a DLL */
        if (NtHeaders->FileHeader.Characteristics & IMAGE_FILE_DLL)
        {
            /* Use the constant ASLR offset */
            AslrOffset = PHYSICAL_SECTION::DllImageBias;
        }
        else
        {
            /* Use new random ASLR offset */
            AslrOffset = RtlRandomEx(&RandomNumberSeed) & 0xFF;
        }

        /* Adjust base address by ASLR offset */
        Section->m_ControlArea.BaseAddress = AddToPointer(Section->m_ControlArea.BaseAddress,
                                                          AslrOffset * 16 * PAGE_SIZE);
    }

    /* Initialize the first subsection, which represents the file headers */
    Section->m_Subsections[0].StartingSector = 0;
    Section->m_Subsections[0].NumberOfFullSectors = FullHeaderSize / SectorSize;
    Section->m_Subsections[0].NumberOfPages = FullHeaderSize / PAGE_SIZE;
    Section->m_Subsections[0].Protect = MM_READONLY;

    /* Get a mapping for the full header */
    Status = Section->GetMapping(&BaseAddress, 0, FullHeaderSize / PAGE_SIZE);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Copy the contents of page 0 */
    RtlCopyMemory(BaseAddress, DosHeaderBuffer, PAGE_SIZE);

    /* Check if the header is larger than 1 page (rare case) */
    if (FullHeaderSize > PAGE_SIZE)
    {
        __debugbreak();

        /// we may need to read more stuff in between!

        /* If we read the NT headers, populate those 2 pages as well */
        if (NtHeadersBuffer != NULL)
        {
            NtHeaders = 0;//AddToPointer(BaseAddress, NtHeaderOffset);
            RtlCopyMemory(ALIGN_DOWN_POINTER_BY(NtHeaders, PAGE_SIZE),
                          NtHeadersBuffer,
                          2 * PAGE_SIZE);
        }

        /* Prefetch the rest of the pages for the file header */
        Status = Section->PrefetchPages(0, FullHeaderSize / PAGE_SIZE);
        if (!NT_SUCCESS(Status))
        {
            goto Cleanup;
        }
    }

    /* Get the address of the Section headers in the header mapping */
    SectionHeaders = reinterpret_cast<PIMAGE_SECTION_HEADER>(
        AddToPointer(BaseAddress, NtHeaderOffset + NtHeaderSize));
    Section->m_ControlArea.SectionHeaders = SectionHeaders;

    /* Verify the section headers */
    Status = VerifySectionHeaders(NtHeaders,
                                  SectionHeaders,
                                  FullHeaderSize,
                                  FileSize.LowPart);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Loop all image sections */
    for (ULONG i = 0; i < NumberOfSections; i++)
    {
        /* Initialize the related subsection from the section header */
        Section->m_Subsections[i + 1].StartingSector =
            SectionHeaders[i].PointerToRawData / SectorSize;
        Section->m_Subsections[i + 1].NumberOfFullSectors =
            ((SectionHeaders[i].SizeOfRawData + SectorSize - 1) / SectorSize) +
            ((SectionHeaders[i].PointerToRawData & (SectorSize - 1)) ? 1 : 0);
        Section->m_Subsections[i + 1].NumberOfPages =
            BYTES_TO_PAGES(SectionHeaders[i].Misc.VirtualSize);
        Section->m_Subsections[i + 1].RelativeStartingVpn =
            SectionHeaders[i].VirtualAddress / PAGE_SIZE;
//        Section->m_Subsections[i + 1].SectionHeader =
//            SectionHeadersOffset + i * sizeof(IMAGE_SECTION_HEADER);

        /// FIXME this is pretty simplified
        if (SectionHeaders[i].Characteristics & IMAGE_SCN_MEM_WRITE)
            Section->m_Subsections[i + 1].Protect = MM_READWRITE;
        else
            Section->m_Subsections[i + 1].Protect = MM_READONLY;

        DPRINT("Image subsection #%u, sect 0x%x, sectors %u, pages %u, vpn %u\n",
                 i + 1,
                 Section->m_Subsections[i + 1].StartingSector,
                 Section->m_Subsections[i + 1].NumberOfFullSectors,
                 Section->m_Subsections[i + 1].NumberOfPages,
                 Section->m_Subsections[i + 1].RelativeStartingVpn);
    }

    /* The section is now complete, commit the pages */
    CommitSize = NtHeaders->OptionalHeader.SizeOfImage - FullHeaderSize;
    Status = Section->CommitPages(FullHeaderSize / PAGE_SIZE,
                                  BYTES_TO_PAGES(CommitSize),
                                  -1);

    /* Get the section image information */
    Section->m_ImageInformation = GetSectionImageInformation(NtHeaders);
    if (Section->m_ImageInformation == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto Cleanup;
    }

//    GetSectionImageInformation(Section->m_ControlArea.Segment->ImageInformation,
//                               NtHeaders);
//    Section->m_ControlArea.Segment->GetSectionImageInformation(NtHeaders);

    /// \todo we should probably do this as well, when we reference an
    /// existing section
    /* Check if we have a machine type mismatch */
    if (NtHeaders->FileHeader.Machine != IMAGE_FILE_MACHINE_NATIVE)
    {
        /* Note: this is a success code */
        Status = STATUS_IMAGE_MACHINE_TYPE_MISMATCH;
    }
    else
    {
        Status = STATUS_SUCCESS;
    }

Cleanup:
    if (BaseAddress != NULL)
    {
        NT_ASSERT(Section != NULL);
        Section->RemoveMapping(BaseAddress, FullHeaderSize);
    }

    if (NtHeadersBuffer != NULL)
    {
        ExFreePoolWithTag(NtHeadersBuffer, TAG_TEMP);
    }

    if (DosHeaderBuffer != NULL)
    {
        ExFreePoolWithTag(DosHeaderBuffer, TAG_TEMP);
    }

    if (!NT_SUCCESS(Status))
    {
        if (Section != NULL)
            Section->Release();
    }

    *OutPhysicalSection = Section;
    return Status;
}


#if 0
NTSTATUS
SECTION::RelocateImagePage (
    _In_ ULONG RelativeVpn,
    _In_ PVOID MappedPage)
{

    //NT_ASSERT(m_ControlArea.Flags.Image != 0);

    /* Find the subsection */
    Index = RelativeVpnToSubsectionIndex(RelativeVpn);
    if (Index == ULONG_MAX)
    {
        return STATUS_UNSUCCESSFUL;
    }

    m_Subsections[Index].

    // Find the pages of the reloc section that belong to the desired page
        // page entry could point to the base relocation, which stores it's size


}
#endif

extern "C" {

_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmFlushImageSection (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_ MMFLUSH_TYPE FlushType)
{
    // NT File system internals p. 238
    UNIMPLEMENTED;
    return FALSE;
}

}; // extern "C"
}; // namespace Mm


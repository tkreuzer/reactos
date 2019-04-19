
namespace Mm {

static const ULONG TAG_TEMP = 'xxmM';
static const ULONG TAG_SECTION = 'tSmM';

struct SECTION_IMAGE_INFORMATION_EX : SECTION_IMAGE_INFORMATION
{
    ULONG SizeOfHeaders;
    ULONG SizeOfImage;
};

typedef SECTION_IMAGE_INFORMATION_EX *PSECTION_IMAGE_INFORMATION_EX;

PSECTION_IMAGE_INFORMATION_EX
GetSectionImageInformation (
    _Out_ PSECTION_IMAGE_INFORMATION_EX ImageInfo,
    _In_ PIMAGE_NT_HEADERS NtHeaders)
{
    /* Fill in the fields */
    ImageInfo->ImageCharacteristics = NtHeaders->FileHeader.Characteristics;
    ImageInfo->Machine = NtHeaders->FileHeader.Machine;
    ImageInfo->TransferAddress = NtHeaders->OptionalHeader.AddressOfEntryPoint;
    ImageInfo->SubSystemType = NtHeaders->OptionalHeader.Subsystem;
    ImageInfo->SubSystemMinorVersion = NtHeaders->OptionalHeader.MinorSubsystemVersion;
    ImageInfo->SubSystemMajorVersion = NtHeaders->OptionalHeader.MajorSubsystemVersion;
    ImageInfo->DllCharacteristics = NtHeaders->OptionalHeader.DllCharacteristics;
    ImageInfo->CheckSum = NtHeaders->OptionalHeader.CheckSum;
    ImageInfo->SizeOfHeaders = NtHeaders->OptionalHeader.SizeOfHeaders;
    ImageInfo->SizeOfImage = NtHeaders->OptionalHeader.SizeOfImage;

    if (NtHeaders->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        PIMAGE_OPTIONAL_HEADER64 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER64>(NtHeaders->OptionalHeader);

        ImageInfo->MaximumStackSize = OptionalHeader->SizeOfStackReserve;
        ImageInfo->CommittedStackSize = OptionalHeader->SizeOfStackCommit;
        ImageInfo->LoaderFlags = OptionalHeader->LoaderFlags;
    }
    else
    {
        PIMAGE_OPTIONAL_HEADER32 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER32>(NtHeaders->OptionalHeader);

        ImageInfo->MaximumStackSize = OptionalHeader->SizeOfStackReserve;
        ImageInfo->CommittedStackSize = OptionalHeader->SizeOfStackCommit;
        ImageInfo->LoaderFlags = OptionalHeader->LoaderFlags;
    }

    ImageInfo->ZeroBits = 0; /// \todo
    ImageInfo->ImageFileSize = 0; /// \todo
    ImageInfo->GpValue = 0; /// \todo
    ImageInfo->ImageFlags = 0; /// \todo
    ImageInfo->ImageContainsCode = TRUE; /// \todo

}

static
NTSTATUS
PageReadHelper (
    _In_ PFILE_OBJECT FileObject,
    _In_ SIZE_T FileOffset,
    _In_ PSIZE_T Size,
    _Out_ PVOID* Buffer,
    _In_ BOOLEAN Cached)
{
    PMDL Mdl;
    KEVENT Event;
    IO_STATUS_BLOCK IoStatusBlock;
    LARGE_INTEGER Offset;
    struct
    {
        MDL Mld;
        PFN_NUMBER PfnArray[5];
    } MdlBuffer;

    /* Align the size up to pages */
    *Size = (ALIGN_UP_BY(*Size, PAGE_SIZE);

    Offset.QuadPart = FileOffset;

    if (Cached)
    {
        Buffer = ReadPageCached(FileObject, &Offset, Size);
    }

    if (Buffer == NULL)
    {
        /* Allocate a page for the file header */
        Buffer = ExAllocatePoolWithTag(NonPagedPool, *Size, TAG_TEMP);
        if (Buffer == NULL)
        {
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        /* Check if the request fits within the stack MDL */
        if (*Size < 5 * PAGE_SIZE)
        {
            /* Use the MDL on the stack */
            Mdl = &MdlBuffer.Mdl;
        }
        else
        {
            /* Allocate a new MDL */
            Mdl = IoAllocateMdl(Buffer, *Size, FALSE, FALSE, NULL);
        }

        /* Build an MDL for the file header */
        MmInitializeMdl(Mdl, Buffer, Size);
        MmBuildMdlForNonPagedPool(Mdl);

        /* Read the first page */
        Status = IoPageRead(FileObject,
                            Mdl,
                            &Offset,
                            &Event,
                            &IoStatusBlock);
        if (Status == STATUS_PENDING)
        {
            KeWaitForSingleObject(&Event, WrPageIn, 0, 0, 0);
            Status = IoStatusBlock.Status;
        }

        if (!NT_SUCCESS(Status))
        {
            /// FIXME handle failure
        }

        /* Return the actual read size */
        *Size = IoStatusBlock.Information;
    }

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
    if (NtHeaders->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        PIMAGE_OPTIONAL_HEADER64 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER64>(NtHeaders->OptionalHeader);

        /* Check if we have a valid optional header size */
        if (NtHeaders->FileHeader.SizeOfOptionalHeader < sizeof(*OptionalHeader))
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }

    }
    else
    {
        PIMAGE_OPTIONAL_HEADER32 OptionalHeader =
            reinterpret_cast<PIMAGE_OPTIONAL_HEADER32>(NtHeaders->OptionalHeader);

        /* Check if we have a valid optional header size */
        if (NtHeaders->FileHeader.SizeOfOptionalHeader < sizeof(*OptionalHeader))
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }
    }
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
    _In_ ULONG FullHeaderSize)
{
    ULONG NextRva, NumberOfSections;

    /* Calculate the required start of the next section */
    NextRva = BYTES_TO_PAGES(FullHeaderSize);

    /* Loop all section headers */
    for (ULONG i = 0; i < NumberOfSections; i++)
    {
        /* Check if the RVA and size are page aligned */
        if ((SectionHeaders[i].VirtualAddress & (PAGE_SIZE - 1)) ||
            (SectionHeaders[i].Misc.VirtualSize & (PAGE_SIZE - 1)))
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }

        /* Check if the RVAs are contiguous */
        if (SectionHeaders[i].VirtualAddress != NextRva)
        {
            return STATUS_INVALID_IMAGE_FORMAT;
        }

        /* Calculate the next section's RVA */
        NextRva += SectionHeaders[i].Misc.VirtualSize;
    }

    return STATUS_SUCCESS;
}


NTSTATUS
SECTION::CreateImageFileSection (
    _Out_ PVOID* FileHeader)
{
    PVOID DosHeaderBuffer, NtHeadersBuffer, SectionHeadersBuffer;
    NTSTATUS Status;
    LARGE_INTEGER FileSize;
    SIZE_T Size;

    NtHeadersBuffer = NULL;
    SectionHeadersBuffer = NULL;
    SectionControl = NULL;

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
    Status = PageReadHelper(FileObject, 0, &Size, &DosHeaderBuffer, TRUE);
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
                                    AddToPtr(DosHeader, NtHeaderOffset));
        AvailableHeaderSize = Size - NtHeaderOffset;
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
        Status = PageReadHelper(FileObject, Offset, &Size, &NtHeadersBuffer, FALSE);
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
        NtHeaders = AddToPtr(NtHeadersBuffer, NtHeaderOffset & (PAGE_SIZE - 1));
        AvailableHeaderSize = Size - ByteOffset;
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
    Status = SECTION::CreateInstance(&Section,
                                     NumberOfSections + 1,
                                     NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

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
    if (!NT_SUCCESS(Status) || (FullHeaderSize > (MAX_ULONG - PAGE_SIZE + 1)))
    {
        Status = STATUS_INVALID_IMAGE_FORMAT;
        goto Cleanup;
    }

    /* Align the full size up to pages (overflow was checked above) */
    FullHeaderSize = ALIGN_UP_BY(FullHeaderSize, PAGE_SIZE);

    /* Initialize the first subsection, which represents the file headers */
    Section->m_Subsections[0].StartingSector = 0;
    Section->m_Subsections[0].NumberOfFullSectors = FullHeaderSize / SectorSize;
    Section->m_Subsections[0].PtesInSubsection = FullHeaderSize / PAGE_SIZE;

    /* Set the contents of page 0 */
    Section->SetPageContent(0, 1, DosHeaderBuffer);

    /* If we read the NT headers, populate those 2 pages as well */
    if (NtHeaderBuffer != NULL)
    {
        Section->SetPageContent(NtHeaderOffset / PAGE_SIZE, 2, NtHeaderBuffer);
    }

    /* Prefetch the rest of the pages for the file header */
    Status = Section->PrefetchPages(0, FullHeaderSize);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Get a mapping for the full header */
    Status = Section->GetMapping(&BaseAddress, 0, FullHeaderSize / SectorSize);
    if (!NT_SUCCESS(Status))
    {
        goto Cleanup;
    }

    /* Get the address of the Section headers in the header mapping */
    SectionHeaders = reinterpret_cast<PIMAGE_SECTION_HEADER>(
        AddToPtr(BaseAddress, NtHeaderOffset + NtHeaderSize));
    Section->m_ControlArea.SectionHeaders = SectionHeaders;

    /* Verify the section headers */
    Status = VerifySectionHeaders(NtHeaders, SectionHeaders, FullHeaderSize);
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
        Section->m_Subsections[i + 1].PtesInSubsection =
            SectionHeaders[i].Misc.VirtualSize / PAGE_SIZE;
        Section->m_Subsections[i + 1].RelativeStartingVpn =
            SectionHeaders[i].VirtualAddress / PAGE_SIZE;
        Section->m_Subsections[i + 1].SectionHeader =
            SectionHeadersOffset + i * sizeof(IMAGE_SECTION_HEADER);
            //PointerToRelocations
            //NumberOfRelocations
    }

    /* Get the section image information */
    GetSectionImageInformation(Segment->ImageInformation, NtHeaders);

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
    if (NtHeadersBuffer != NULL)
    {
        ExFreePoolWithTag(NtHeadersBuffer, TAG_TEMP);
    }

    if (SectionHeadersBuffer != NULL)
    {
        ExFreePoolWithTag(SectionHeadersBuffer, TAG_TEMP);
    }

    if (!NT_SUCCESS(Status))
    {
        if (DosHeaderBuffer != NULL)
        {
            ExFreePoolWithTag(DosHeaderBuffer, TAG_TEMP);
        }

        SectionControl->Release();
    }


    return Status;
}

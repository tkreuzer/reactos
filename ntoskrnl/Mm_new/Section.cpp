
#include "Section.hpp"
#include "Segment.hpp"
#include "Mapping.hpp"

namespace Mm {

static const ULONG NUMBER_OF_IMAGE_BITMAP_BITS = 0x2800;

static ULONG ImageLoadBitmapBuffer[NUMBER_OF_IMAGE_BITMAP_BITS / sizeof(ULONG)];
const RTL_BITMAP SECTION::ImageLoadBitMap =
    {NUMBER_OF_IMAGE_BITMAP_BITS, ImageLoadBitmapBuffer};
UCHAR SECTION::DllImageBias;
extern ULONG RandomNumberSeed;

VOID
SECTION::InitializeClass (
    VOID)
{

    /* Initialize the random DLL load address offset */
    DllImageBias = RtlRandomEx(&RandomNumberSeed) & 0xFF;


}

SECTION::SECTION (
    VOID)
{
    // nothing for now
}

SECTION::~SECTION (
    VOID)
{
    if (m_ControlArea.Segment != NULL)
        m_ControlArea.Segment->Release();
}

NTSTATUS
SECTION::CreateInstance (
    _Out_ PSECTION* OutSection,
    _In_ ULONG NumberOfSubsections,
    _In_ ULONG_PTR NumberOfPages)
{
    PSECTION Section;
    PSEGMENT Segment;
    SIZE_T Size;
    NTSTATUS Status;

    /* Calculate the size of the SECTION with all SUBSECTIONs */
    //Size = FIELD_OFFSET(SECTION, m_Subsections[NumberOfSubsections]);
    Size = sizeof(SECTION) + (NumberOfSubsections - 1) * sizeof(SUBSECTION);

    /* Allocate the SECTION */
    Section = new(Size) SECTION;
    if (Section == NULL)
    {
        ERR("Could not allocate a SECTION\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Allocate a SEGMENT */
    Status = SEGMENT::CreateInstance(&Segment, NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        ERR("Could not allocate a SEGMENT\n");
        Section->Release();
        return Status;
    }

    /* Initialize the section */
    RtlZeroMemory(Section, Size);
    Section->m_ControlArea.NumberOfSubsections = NumberOfSubsections;
    Section->m_ControlArea.Segment = Segment;
    Section->m_ControlArea.SizeInPages = NumberOfPages;

    *OutSection = Section;
    return STATUS_SUCCESS;
}

NTSTATUS
SECTION::CreatePageFileSection (
    _Out_ PSECTION* OutSection,
    _In_ ULONG64 SizeInBytes,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes)
{
    NTSTATUS Status;
    PSECTION Section;
    ULONG NumberOfPages;

    // check max size of SizeInBytes

    NumberOfPages = (ULONG)BYTES_TO_PAGES(SizeInBytes);

    /* Create a SECTION with one subsection */
    Status = SECTION::CreateInstance(&Section, 1, NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to allocate a SECTION: 0x%lx\n", Status);
        return Status;
    }

    /* Initialize the subsection */
    Section->m_Subsections[0].RelativeStartingVpn = 0;
    Section->m_Subsections[0].NumberOfPages = NumberOfPages;
    Section->m_Subsections[0].BaseSegmentIndex = 0;

    /* Check if committing is requested */
    if (AllocationAttributes & SEC_COMMIT)
    {
        /* Remember this fact */
        Section->m_ControlArea.Flags.Commit = TRUE;

        /* Commit all pages in the segment */
        Status = Section->m_ControlArea.Segment->CommitDemandZeroPages(0,
                                                                       NumberOfPages,
                                                                       SectionPageProtection);
        if (!NT_SUCCESS(Status))
        {
            ERR("Failed to commit pages for segment: 0x%lx\n", Status);
            Section->Release();
            return Status;
        }
    }

    *OutSection = Section;
    return STATUS_SUCCESS;
}


NTSTATUS
SECTION::CommitPages (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    // Charge system commit

    /* Check if we have a file-backed section */
    if (m_ControlArea.FilePointer != NULL)
    {
        UNIMPLEMENTED;
    }
    else
    {
        /* Commit demand zero pages */
        m_ControlArea.Segment->CommitDemandZeroPages(RelativeStartingVpn,
                                                     NumberOfPages,
                                                     Protect);
    }

    return 0;
}

/// \todo Use binary search
ULONG
SECTION::RelativeVpnToSubsectionIndex (
    _In_ ULONG_PTR RelativeVpn)
{
    /* Loop all subsections */
    for (ULONG i = 0; i < m_ControlArea.NumberOfSubsections; i++)
    {
        /* Check if the requested VPN is inside the subsection */
        if ((m_Subsections[i].RelativeStartingVpn <= RelativeVpn) &&
            ((m_Subsections[i].RelativeStartingVpn +
                 m_Subsections[i].NumberOfPages) > RelativeVpn))
        {
            return i;
        }
    }

    return MAXULONG;
}

#if 1
// This much simpler variant can be used, if the prototypes are created with
// a protection according to the subsection protection
NTSTATUS
SECTION::CreateMapping (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    /* Make sure everything we map is inside this section */
    NT_ASSERT((RelativeStartingVpn + NumberOfPages) <= m_ControlArea.SizeInPages);

    /* If this is an image, use the protection from the prototype */
    if (m_ControlArea.Flags.Image)
        Protect = -1;

    return m_ControlArea.Segment->MapPages(BaseAddress,
                                           RelativeStartingVpn,
                                           NumberOfPages,
                                           Protect);
}
#else
NTSTATUS
SECTION::CreateMapping (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    ULONG_PTR MappingVpn, StartingPageIndex, MaxPageCount, CurrentPageCount;
    PSUBSECTION Subsection;
    ULONG SubsectionIndex;
    NTSTATUS Status;
    NT_ASSERT(NumberOfPages != 0);

    /* Make sure everything we map is inside this section */
    if ((RelativeStartingVpn + NumberOfPages) > m_ControlArea.SizeInPages)
    {
        ERR("Exceeding section size\n");
        return STATUS_INVALID_PARAMETER;
    }

    /* Calculate the starting VPN for the mapping */
    MappingVpn = AddressToVpn(BaseAddress);

    /* First reserve the page tables */
    Status = ReservePageTables(MappingVpn, NumberOfPages, Protect);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to reserve page tables for section mapping: 0x%lx\n", Status);
        return Status;
    }

    /* Find the first relevant subsection */
    SubsectionIndex = RelativeVpnToSubsectionIndex(RelativeStartingVpn);
    Subsection = &m_Subsections[SubsectionIndex];

    /* If this happens, there's something seriously wrong! */
    NT_ASSERT((SubsectionIndex != MAXULONG) &&
              (SubsectionIndex < m_ControlArea.NumberOfSubsections));

    /* Calculate the subsection relative starting page index */
    NT_ASSERT(RelativeStartingVpn >= Subsection->RelativeStartingVpn);
    StartingPageIndex = RelativeStartingVpn - Subsection->RelativeStartingVpn;
    NT_ASSERT(StartingPageIndex < Subsection->NumberOfPages);

    /* Loop until all pages are mapped */
    do
    {
        /* Make sure we do not leave the range */
        NT_ASSERT(Subsection < &m_Subsections[m_ControlArea.NumberOfSubsections]);

        /* If this is an image, use the subsection protection */
        if (m_ControlArea.Flags.Image)
            Protect = Subsection->Protect;

        /* Calculate how many pages we can map from this subsection */
        MaxPageCount = Subsection->NumberOfPages - StartingPageIndex;
        CurrentPageCount = min(NumberOfPages, MaxPageCount);

        /* Map the prototype PTEs of this subsection */
        m_ControlArea.Segment->MapPages(MappingVpn,
                                        RelativeStartingVpn,
                                        CurrentPageCount,
                                        Protect);

        /* Update mapping location and relative VPN */
        MappingVpn += CurrentPageCount;
        RelativeStartingVpn += CurrentPageCount;
        NumberOfPages -= CurrentPageCount;

        /* Go to the next subsection */
        Subsection++;
        StartingPageIndex = 0;
    }
    while (NumberOfPages > 0);

    return STATUS_SUCCESS;
}
#endif

NTSTATUS
SECTION::GetMapping (
    _Out_ PVOID* BaseAddress,
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

VOID
SECTION::SetPageContent (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ PVOID Buffer)
{
    // find the subsection for the vpn
    // get the page index
    // Status = Segment->SetPageContent(BasePageIndex, NumberOfPages, Buffer);
    UNIMPLEMENTED;
}

NTSTATUS
SECTION::PrefetchPages (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


extern "C" {

_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmCanFileBeTruncated (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_opt_ PLARGE_INTEGER NewFileSize)
{
    UNIMPLEMENTED;
    return FALSE;
}

}; // extern "C"
}; // namespace Mm

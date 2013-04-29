
#include "Section.hpp"

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
    // nothing for now
}

NTSTATUS
SECTION::CreateInstance (
    _Out_ PSECTION* OutSection,
    _In_ ULONG NumberOfSubsections,
    _In_ ULONG NumberOfPtes)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
SECTION::CreatePageFileSection (
    _Out_ PSECTION* OutSection,
    _In_ ULONG64 MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes)
{
    UNIMPLEMENTED;
    return 0;
}

VOID
SECTION::SetPageContent (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ PVOID Buffer)
{
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


NTSTATUS
SECTION::CreateMapping (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    // loop through all SUBSECTIONs
        // skip subsections outside the range
        // break when beyond the range
        // Map the prototype PTEs of the section
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS
SECTION::GetMapping (
    _Out_ PVOID* BaseAddress,
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}


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


}; // namespace Mm

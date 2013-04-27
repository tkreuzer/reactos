
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

NTSTATUS
SECTION::CreateInstance (
    _Out_ PSECTION* OutSection,
    _In_ ULONG NumberOfSubsections,
    _In_ ULONG NumberOfPtes)
{
    return STATUS_NOT_IMPLEMENTED;
}

VOID
SECTION::SetPageContent (
    _In_ ULONG RelativeStartingVpn,
    _In_ ULONG NumberOfPages,
    _In_ PVOID Buffer)
{
}

NTSTATUS
SECTION::PrefetchPages (
    _In_ ULONG RelativeStartingVpn,
    _In_ ULONG NumberOfPages)
{
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
SECTION::GetMapping (
    _Out_ PVOID* BaseAddress,
    _In_ ULONG RelativeStartingVpn,
    _In_ ULONG NumberOfPages)
{
    return STATUS_NOT_IMPLEMENTED;
}

VOID
SECTION::Release (
    VOID)
{
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

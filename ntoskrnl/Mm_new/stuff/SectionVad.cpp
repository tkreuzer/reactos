

#include "SectionVad.hpp"

namespace Mm {

const char SectionVadType[] = "SectionVad";


NTSTATUS
NTAPI
MapViewOfSection (
    _In_ PSECTION_OBJECT SectionObject,
    _In_ VA_TYPE VaType,
    _Inout_ PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect)
{
    PADDRESS_SPACE AddressSpace;
    ULONG_PTR StartingVpn, LowestStartingVpn, HighestEndingVpn, RelativeStartingVpn;
    ULONG_PTR BoundaryPageMultiple, ViewSizeInPages;
    SECTION_VIEW* SectionView;
    NTSTATUS Status;
    PVAD_TABLE VadTable;
    PSECTION Section;

__debugbreak();


    StartingVpn = AddressToVpn(*BaseAddress);

#if 0
    // maybe move it to NtMapViewOfSection / MmMapViewOfSection
    if ((*BaseAddress != NULL) &&
        (*BaseAddress != ALIGN_DOWN_POINTER_BY(BoundaryPageMultiple * PAGE_SIZE)))
    {
        return STATUS_MAPPED_ALIGNMENT;
    }
#endif

    /* Check if the range is OK */
    if (((StartingVpn != 0) && (StartingVpn < LowestStartingVpn)) ||
        ((StartingVpn + ViewSizeInPages) > HighestEndingVpn) ||
        ((StartingVpn + ViewSizeInPages) < StartingVpn))
    {
        ERR("Invalid parameters: StartingVpn
        Section->Release();
        return STATUS_INVALID_PARAMETER;
    }




    VadTable = AddressSpace->GetVadTable();

    /* Check if a base address was specified */
    if (StartingVpn != 0)
    {
        /* Try to insert the VAD at the corresponding VPN */
        Status = VadTable->InsertVadObjectAtVpn(SectionView,
                                                StartingVpn,
                                                ViewSizeInPages);
        if (!NT_SUCCESS(Status))
        {
            /* Check if the base address was caller specified */
            if (*BaseAddress != NULL)
            {
                delete SectionView;
                return Status;
            }

            /* Fall back to auto-base */
            StartingVpn = 0;
        }
    }

    if (StartingVpn == 0)
    {
        /* Insert the VAD into the VAD table */
        Status = VadTable->InsertVadObject(SectionView,
                                           ViewSizeInPages,
                                           LowestStartingVpn,
                                           HighestEndingVpn,
                                           BoundaryPageMultiple,
                                           (AllocationType & MEM_TOP_DOWN) != 0);
    }

    if (!NT_SUCCESS(Status))
    {
        //SectionView->Release();
        delete SectionView;
        return Status;
    }


}




}; // namespace Mm

NTSTATUS
SECTION::CreateMapping (
    _In_ PVOID BaseAddress,
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    ULONG_PTR MappingVpn, MaxPages, SubsectionIndex, SegmentIndex, CurrentPageCount;
    ULONG i;
    NTSTATUS Status;

    /* Make sure everything we map is inside this section */
    NT_ASSERT((RelativeStartingVpn + NumberOfPages) <= m_ControlArea.SizeInPages);

    /* Calculate the starting VPN for the mapping */
    MappingVpn = AddressToVpn(BaseAddress);

    /* Start at first subsection */
    i = 0;

    /* Skip subsections completely below the commit range */
    while ((m_Subsections[i].RelativeStartingVpn + m_Subsections[i].NumberOfPages)
            <= RelativeStartingVpn)
    {
        i++;

        /* Stop after last subsection */
        if (i == m_ControlArea.NumberOfSubsections)
        {
            return STATUS_SUCCESS;
        }
    }

    /* Loop through the rest of the subsections */
    for (; i < m_ControlArea.NumberOfSubsections; i++)
    {
        /* Break out when beyond the range */
        if (m_Subsections[i].RelativeStartingVpn >= (RelativeStartingVpn + NumberOfPages))
        {
            break;
        }

        /* Calculate the starting page index inside this subsection */
        NT_ASSERT(RelativeStartingVpn >= m_Subsections[i].RelativeStartingVpn);
        SubsectionIndex = RelativeStartingVpn - m_Subsections[i].RelativeStartingVpn;

        /* Calculate how many pages we can map from this subsection */
        MaxPages = m_Subsections[i].NumberOfPages - SubsectionIndex;
        CurrentPageCount = min(NumberOfPages, MaxPages);

        /* Calculate the page index into the segment */
        SegmentIndex = m_Subsections[i].BaseSegmentIndex + SubsectionIndex;

        Status = m_ControlArea.Segment->MapPages(MappingVpn,
                                                 CurrentPageCount,
                                                 SegmentIndex,
                                                 Protect);

        /* Update mapping location and relative VPN */
        MappingVpn += CurrentPageCount;
        RelativeStartingVpn += CurrentPageCount;
        NumberOfPages -= CurrentPageCount;
    }

    /* Make sure we handled everything */
    NT_ASSERT(NumberOfPages == 0);

    return STATUS_SUCCESS;
}

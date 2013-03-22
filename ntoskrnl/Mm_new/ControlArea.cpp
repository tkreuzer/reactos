
#include "ControlArea.hpp"
#include "SegmentObject.hpp"

namespace Mm {

CONTROL_AREA::CONTROL_AREA (
    VOID)
{
    m_Segment = NULL;
}

CONTROL_AREA::~CONTROL_AREA (
    VOID)
{
    if (m_Segment != NULL)
    {
        m_Segment->Release();
    }
}

NTSTATUS
CONTROL_AREA::CreateInstance (
    _Out_ PCONTROL_AREA* OutControlArea)
{
    PCONTROL_AREA ControlArea;

    ControlArea = new CONTROL_AREA;
    if (ControlArea == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    *OutControlArea = ControlArea;

    return STATUS_SUCCESS;
}

NTSTATUS
CONTROL_AREA::ReferenceOrCreateControlArea (
    _Out_ PCONTROL_AREA* OutControlArea,
    _In_ PFILE_OBJECT FileObject,
    _In_ BOOLEAN AsImage)
{
    PSECTION_OBJECT_POINTERS SectionObjectPointers;
    PFSRTL_COMMON_FCB_HEADER FcbHeader;
    PVOID* ControlAreaPointer, *OtherControlAreaPointer;
    PCONTROL_AREA ControlArea, OtherControlArea;
    PSEGMENT_OBJECT Segment;
    NTSTATUS Status;

    /* Assume success */
    Status = STATUS_SUCCESS;

    /* Get the Fcb header */
    FcbHeader = static_cast<PFSRTL_COMMON_FCB_HEADER>(FileObject->FsContext);
    if (FcbHeader == NULL)
    {
        return STATUS_UNSUCCESSFUL;
    }

    SectionObjectPointers = FileObject->SectionObjectPointer;

    /* Use the right control area for this section */
    if (AsImage)
    {
        ControlAreaPointer = &SectionObjectPointers->ImageSectionObject;
        OtherControlAreaPointer = &SectionObjectPointers->DataSectionObject;
    }
    else
    {
        ControlAreaPointer = &SectionObjectPointers->DataSectionObject;
        OtherControlAreaPointer = &SectionObjectPointers->ImageSectionObject;
    }

    /* Disable APCs */
    KeEnterCriticalRegion();

    /* Lock the FCB for read access */
    ExAcquireResourceSharedLite(FcbHeader->Resource, TRUE);

    /* Check if there is already a control area */
    ControlArea = static_cast<PCONTROL_AREA>(*ControlAreaPointer);
    if (ControlArea != NULL)
    {
        NT_ASSERT(ControlArea->m_Segment != NULL);

        /* There is, so reference it */
        ControlArea->AddRef();

        /* Release the FCB lock again */
        ExReleaseResource(FcbHeader->Resource);

        /* We're done */
        goto Done;
    }

    /* Check if the other control area is already there */
    OtherControlArea = static_cast<PCONTROL_AREA>(*OtherControlAreaPointer);
    if (OtherControlArea != NULL)
    {
        /* Get it's segment and reference it */
        Segment = OtherControlArea->m_Segment;
        NT_ASSERT(Segment != NULL);
        Segment->AddRef();
    }

    /* Release the FCB lock again */
    ExReleaseResourceLite(FcbHeader->Resource);

    /* Do we need a new segment? */
    if (Segment == NULL)
    {
        /* Yes, so create one */
        Status = SEGMENT_OBJECT::CreateInstance(&Segment);
        if (!NT_SUCCESS(Status))
        {
            goto Done;
        }
    }

    /* Now create the control area */
    Status = CONTROL_AREA::CreateInstance(&ControlArea);
    if (!NT_SUCCESS(Status))
    {
        goto Done;
    }

    /* Set the segment member and set the Segment variable to NULL to
       prevent it from being dereferenced later */
    ControlArea->m_Segment = Segment;
    Segment = NULL;

    /* To set the control area pointer we need to get an exclusive lock */
    ExAcquireResourceExclusiveLite(FcbHeader->Resource, TRUE);

    /* Check if the other control area is there now */
    OtherControlArea = static_cast<PCONTROL_AREA>(*OtherControlAreaPointer);
    if (OtherControlArea != NULL)
    {
        /* Check if the segment matches what we have */
        if (OtherControlArea->m_Segment != Segment)
        {
            /* In this case another thread was faster, so we drop our segment
               and use the one already there */
            Segment = ControlArea->m_Segment;
            OtherControlArea->m_Segment->AddRef();
            ControlArea->m_Segment = OtherControlArea->m_Segment;
        }
    }

    /* Release the FCB lock again */
    ExReleaseResourceLite(FcbHeader->Resource);

Done:

    /* Enable APCs again */
    KeLeaveCriticalRegion();

    /* Check if we need to release our segment */
    if (Segment != NULL)
    {
        Segment->Release();
    }

    /* Check if the function failed */
    if (!NT_SUCCESS(Status))
    {
        /* Release the control area, it's segment will be dereferenced as well */
        if (ControlArea != NULL)
        {
            ControlArea->Release();
        }
    }

    return Status;
}

} // namespace Mm


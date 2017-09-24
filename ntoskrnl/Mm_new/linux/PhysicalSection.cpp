
#include "PhysicalSection.hpp"
#include "Segment.hpp"
#include "../Mapping.hpp"
#include "../AddressSpace.hpp"
#include <eal.h>
#include <ndk/obfuncs.h>

namespace Mm {

static const ULONG NUMBER_OF_IMAGE_BITMAP_BITS = 0x2800;

static ULONG ImageLoadBitmapBuffer[NUMBER_OF_IMAGE_BITMAP_BITS / sizeof(ULONG)];
const RTL_BITMAP PHYSICAL_SECTION::ImageLoadBitMap =
    {NUMBER_OF_IMAGE_BITMAP_BITS, ImageLoadBitmapBuffer};
UCHAR PHYSICAL_SECTION::DllImageBias;
extern ULONG RandomNumberSeed;

VOID
CommitPagesInBitmap (
    ULONG StartingVpn,
    ULONG NumberOfPages);

VOID
PHYSICAL_SECTION::InitializeClass (
    VOID)
{

    /* Initialize the random DLL load address offset */
    DllImageBias = RtlRandomEx(&RandomNumberSeed) & 0xFF;


}

PHYSICAL_SECTION::PHYSICAL_SECTION (
    VOID)
{
    // nothing for now
}

PHYSICAL_SECTION::~PHYSICAL_SECTION (
    VOID)
{
    if (m_ControlArea.Segment != NULL)
        m_ControlArea.Segment->Release();
}

NTSTATUS
PHYSICAL_SECTION::CreateInstance (
    _Out_ PPHYSICAL_SECTION* OutSection,
    _In_ ULONG NumberOfSubsections,
    _In_ ULONG_PTR NumberOfPages)
{
    PPHYSICAL_SECTION Section;
    PSEGMENT Segment;
    SIZE_T Size;
    NTSTATUS Status;

    /* Calculate the size of the PHYSICAL_SECTION with all SUBSECTIONs */
    //Size = FIELD_OFFSET(PHYSICAL_SECTION, m_Subsections[NumberOfSubsections]);
    Size = sizeof(PHYSICAL_SECTION) + (NumberOfSubsections - 1) * sizeof(SUBSECTION);

    /* Allocate the PHYSICAL_SECTION */
    Section = new(Size) PHYSICAL_SECTION;
    if (Section == NULL)
    {
        ERR("Could not allocate a PHYSICAL_SECTION\n");
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
PHYSICAL_SECTION::CreatePageFileSection (
    _Out_ PPHYSICAL_SECTION* OutSection,
    _In_ ULONG64 SizeInBytes,
    _In_ ULONG AllocationAttributes)
{
    NTSTATUS Status;
    PPHYSICAL_SECTION Section;
    ULONG NumberOfPages;

    // check max size of SizeInBytes
    if (SizeInBytes == 0)
    {
        /* This is not allowed */
        return STATUS_INVALID_PARAMETER;
    }

    NumberOfPages = (ULONG)BYTES_TO_PAGES(SizeInBytes);

    /* Create a PHYSICAL_SECTION with one subsection */
    Status = PHYSICAL_SECTION::CreateInstance(&Section, 1, NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to allocate a PHYSICAL_SECTION: 0x%lx\n", Status);
        return Status;
    }

    /* Initialize the subsection */
    Section->m_Subsections[0].RelativeStartingVpn = 0;
    Section->m_Subsections[0].NumberOfPages = NumberOfPages;
    Section->m_Subsections[0].BaseSegmentIndex = 0;

    /* Create the shared memory object */
    Section->m_FileDescriptorIndex = EalCreateSharedMemoryObject();
    if (Section->m_FileDescriptorIndex == 0)
    {
        ERR("Failed to allocate a PHYSICAL_SECTION: 0x%lx\n", Status);
        Section->Release();
        return Status;
    }

    /* Check if committing is requested */
    if (1 || AllocationAttributes & SEC_COMMIT) /// \todo FIXME HUGE HACK
    {
        /* truncate the section to the full size */
        Status = EalSetSectionSize(Section->m_FileDescriptorIndex, SizeInBytes);
        if (!NT_SUCCESS(Status))
        {
            ERR("Failed to commit pages for segment: 0x%lx\n", Status);
            __debugbreak();
            Section->Release();
            return Status;
        }

        Section->m_TruncatedSize = SizeInBytes;
    }

    *OutSection = Section;
    return STATUS_SUCCESS;
}

NTSTATUS
PHYSICAL_SECTION::CreateDataFileSection (
    _Out_ PPHYSICAL_SECTION* OutPhysicalSection,
    _In_ PFILE_OBJECT FileObject,
    _Inout_ PLARGE_INTEGER MaximumSize)
{
    NTSTATUS Status;
    ULONG NumberOfPages;
    LARGE_INTEGER FileSize;
    ULONG64 SizeInBytes;
    PPHYSICAL_SECTION Section;

    /* Get the file size */
    Status = FsRtlGetFileSize(FileObject, &FileSize);
    if (!NT_SUCCESS(Status))
    {
        if (Status == STATUS_FILE_IS_A_DIRECTORY)
        {
            Status = STATUS_INVALID_FILE_FOR_SECTION;
        }
        return Status;
    }

    /* Start with the file length */
    SizeInBytes = FileSize.QuadPart;

    /* Check if non-zero maximum length was passed */
    if (MaximumSize->QuadPart != 0)
    {
        /* Use the maximum allowed */
        SizeInBytes = min(SizeInBytes, MaximumSize->QuadPart);
    }


    NumberOfPages = (ULONG)BYTES_TO_PAGES(SizeInBytes);

    /* Create a PHYSICAL_SECTION with one subsection */
    Status = PHYSICAL_SECTION::CreateInstance(&Section, 1, NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to allocate a PHYSICAL_SECTION: 0x%lx\n", Status);
        return Status;
    }

    ObReferenceObject(FileObject);
    Section->m_ControlArea.FileObject = FileObject;

    /* Initialize the subsection */
    Section->m_Subsections[0].RelativeStartingVpn = 0;
    Section->m_Subsections[0].NumberOfPages = NumberOfPages;
    Section->m_Subsections[0].BaseSegmentIndex = 0;
    Section->m_Subsections[0].Protect = MM_READONLY;

    /// \todo FIXME: we should use the actual file descriptor!

    /* Create the shared memory object */
    Section->m_FileDescriptorIndex = EalCreateSharedMemoryObject();
    if (Section->m_FileDescriptorIndex == 0)
    {
        ERR("Failed to allocate a PHYSICAL_SECTION: 0x%lx\n", Status);
        Section->Release();
        return Status;
    }

    /* truncate the section to the full size */
    Status = EalSetSectionSize(Section->m_FileDescriptorIndex, SizeInBytes);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to commit pages for segment: 0x%lx\n", Status);
        __debugbreak();
        Section->Release();
        return Status;
    }

    Section->m_TruncatedSize = SizeInBytes;

    /// HACK
    Status = Section->CommitPages(0, NumberOfPages, 0);
    if (!NT_SUCCESS(Status))
    {
        ERR("Failed to commit data section pages: 0x%lx\n", Status);
        Section->Release();
        return Status;
    }

    *OutPhysicalSection = Section;
    return STATUS_SUCCESS;
}

NTSTATUS
PHYSICAL_SECTION::ReferenceOrCreateFileSection (
    _Out_ PPHYSICAL_SECTION* OutPhysicalSection,
    _Inout_ PLARGE_INTEGER MaximumSize,
    _Inout_ PFILE_OBJECT FileObject,
    _In_ ULONG AllocationAttributes)
{
    PSECTION_OBJECT_POINTERS SectionObjectPointers;
    PVOID* SectionPointer;
    PVOID Previous;
    PPHYSICAL_SECTION PhysicalSection, PrevSection;
    NTSTATUS Status;
    SECTION_WAIT_BLOCK WaitBlock, *WaitBlockPointer;

    /* Check if we have section pointers */
    SectionObjectPointers = FileObject->SectionObjectPointer;
    if (SectionObjectPointers == NULL)
    {
        return STATUS_INVALID_FILE_FOR_SECTION;
    }

    if (AllocationAttributes & SEC_IMAGE)
    {
        SectionPointer = &SectionObjectPointers->ImageSectionObject;
    }
    else
    {
        SectionPointer = &SectionObjectPointers->DataSectionObject;
    }

    /* Start looping */
    for (;;)
    {
        /* Get the current value of the pointer and check what we have */
        PhysicalSection = static_cast<PPHYSICAL_SECTION>(*SectionPointer);
        if (PhysicalSection == NULL)
        {
            /* There is no section yet and noone is creating it currently.
               Mark the pointer to express that creation is in progress. */
            Previous = InterlockedCompareExchangePointer(SectionPointer,
                                                         NULL,
                                                         (PVOID)1);
            if (Previous != NULL)
            {
                continue;
            }

            PhysicalSection = NULL;

            /* Check if we need an image section or data section */
            if (AllocationAttributes & SEC_IMAGE)
            {
                /* Create an image file section */
                Status = PHYSICAL_SECTION::CreateImageFileSection(&PhysicalSection,
                                                                  FileObject,
                                                                  MaximumSize);
            }
            else
            {
                /* Create a data file section */
                Status = PHYSICAL_SECTION::CreateDataFileSection(&PhysicalSection,
                                                                 FileObject,
                                                                 MaximumSize);
            }

            if (!NT_SUCCESS(Status))
            {
                return Status;
            }

            /* Exchange with the newly created section and check for waiters */
            Previous = InterlockedExchangePointer(SectionPointer, PhysicalSection);
            WaitBlockPointer = static_cast<PSECTION_WAIT_BLOCK>(ClearPointerMask(Previous, 1));

            /* Loop while we have waiters */
            while (WaitBlockPointer != NULL)
            {
                /* Wake up the waiter */
                KeSignalGateBoostPriority(&WaitBlockPointer->Gate);
                WaitBlockPointer = WaitBlockPointer->Next;
            }

            break;
        }
        else if (reinterpret_cast<ULONG_PTR>(PhysicalSection) & 1)
        {
            /* Section creation is in progress, enqueue a wait block */
            WaitBlock.Next = static_cast<PSECTION_WAIT_BLOCK>(ClearPointerMask(PhysicalSection, 1));
            Previous = InterlockedCompareExchangePointer(SectionPointer,
                                                            PhysicalSection,
                                                            SetPointerMask(&WaitBlock, 1));
            if (Previous == PhysicalSection)
            {
                /* Exchange succeeded, wait on the wait block */
                KeWaitForGate(&WaitBlock.Gate, Executive, KernelMode);
            }
        }
        else if (reinterpret_cast<ULONG_PTR>(PhysicalSection) & 2)
        {
            /* There is a section, but it is locked, spin until it get's released */
            KIRQL OldIrql = KfRaiseIrql(DISPATCH_LEVEL);

            while (reinterpret_cast<ULONG_PTR>(*SectionPointer) & 2)
                YieldProcessor();

            KfLowerIrql(OldIrql);
        }
        else
        {
            /* There is a section. We need to acquire a spinlock to synchronize
               with section deletion */
            Previous = InterlockedCompareExchangePointer(SectionPointer,
                                                         PhysicalSection,
                                                         SetPointerMask(PhysicalSection, 2));
            if (Previous == PhysicalSection)
            {
                /* Exchange succeeded, reference the section */
                PhysicalSection->AddRef();
                InterlockedExchangePointer(SectionPointer, Previous);
                Status = STATUS_SUCCESS;
                break;
            }
        }
    }

    /* Return the result */
    *OutPhysicalSection = PhysicalSection;
    return Status;
}

NTSTATUS
NTAPI
IoPageRead2 (
    IN PFILE_OBJECT FileObject,
    IN PVOID ReadAddress,
    IN ULONG ReadLength,
    IN PLARGE_INTEGER Offset)
{
    PIRP Irp;
    PIO_STACK_LOCATION StackPtr;
    PDEVICE_OBJECT DeviceObject;
    IO_STATUS_BLOCK IoStatusBlock;

    /* Get the Device Object */
    DeviceObject = IoGetRelatedDeviceObject(FileObject);

    /* Allocate IRP */
    Irp = IoAllocateIrp(DeviceObject->StackSize, FALSE);
    if (!Irp) return STATUS_INSUFFICIENT_RESOURCES;

    /* Get the Stack */
    StackPtr = IoGetNextIrpStackLocation(Irp);

    /* Create the IRP Settings */
    Irp->MdlAddress = NULL;
    Irp->UserBuffer = ReadAddress;
    Irp->UserIosb = &IoStatusBlock;
    Irp->UserEvent = NULL;
    Irp->RequestorMode = KernelMode;
    Irp->Flags = IRP_PAGING_IO |
                 IRP_NOCACHE |
                 IRP_SYNCHRONOUS_PAGING_IO |
                 IRP_INPUT_OPERATION;
    Irp->Tail.Overlay.OriginalFileObject = FileObject;
    Irp->Tail.Overlay.Thread = PsGetCurrentThread();

    /* Set the Stack Settings */
    StackPtr->Parameters.Read.Length = ReadLength;
    StackPtr->Parameters.Read.ByteOffset = *Offset;
    StackPtr->MajorFunction = IRP_MJ_READ;
    StackPtr->FileObject = FileObject;

    /* Call the Driver */
    return IoCallDriver(DeviceObject, Irp);
}

/// Might unify this with the one in ImageSection, for now I don't care
static
NTSTATUS
PageReadHelper2 (
    _In_ PFILE_OBJECT FileObject,
    _In_ SIZE_T FileOffset,
    _In_ PULONG Size,
    _Out_ PVOID ReadAddress)
{
    NTSTATUS Status;
    PIRP Irp;
    PIO_STACK_LOCATION StackPtr;
    PDEVICE_OBJECT DeviceObject;
    IO_STATUS_BLOCK IoStatusBlock;
    KEVENT Event;

    /* Initialize the event */
    KeInitializeEvent(&Event, NotificationEvent, FALSE);

    /* Get the Device Object */
    DeviceObject = IoGetRelatedDeviceObject(FileObject);

    /* Allocate IRP */
    Irp = IoAllocateIrp(DeviceObject->StackSize, FALSE);
    if (!Irp) return STATUS_INSUFFICIENT_RESOURCES;

    /* Get the Stack */
    StackPtr = IoGetNextIrpStackLocation(Irp);

    /* Create the IRP Settings */
    Irp->MdlAddress = NULL;
    Irp->UserBuffer = ReadAddress;
    Irp->UserIosb = &IoStatusBlock;
    Irp->UserEvent = &Event;
    Irp->RequestorMode = KernelMode;
    Irp->Flags = IRP_PAGING_IO |
                 IRP_NOCACHE |
                 IRP_SYNCHRONOUS_PAGING_IO |
                 IRP_INPUT_OPERATION;
    Irp->Tail.Overlay.OriginalFileObject = FileObject;
    Irp->Tail.Overlay.Thread = PsGetCurrentThread();

    /* Set the Stack Settings */
    StackPtr->Parameters.Read.Length = *Size;
    StackPtr->Parameters.Read.ByteOffset.QuadPart = FileOffset;
    StackPtr->MajorFunction = IRP_MJ_READ;
    StackPtr->FileObject = FileObject;

    /* Call the Driver */
    Status = IoCallDriver(DeviceObject, Irp);
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

NTSTATUS
ReadFileData (
    PPHYSICAL_SECTION Section,
    PFILE_OBJECT FileObject,
    SIZE_T FileOffset,
    ULONG Size,
    ULONG_PTR RelativeStartingVpn)
{
    NTSTATUS Status;
    ULONG NumberOfPages;
    PVOID Address;

    NumberOfPages = BYTES_TO_PAGES(Size);

    Status = Section->GetMapping(&Address, RelativeStartingVpn, NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        __debugbreak();
        return Status;
    }


    Status = PageReadHelper2(FileObject, FileOffset, &Size, Address);


    Section->RemoveMapping(Address, Size);

    if (!NT_SUCCESS(Status))
    {
        __debugbreak();
    }
    

    return Status;
}

NTSTATUS
PHYSICAL_SECTION::CommitPages (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ ULONG Protect)
{
    NTSTATUS Status;
    ULONG SectorSize = 512; /// \todo HACK, should probably save the byte offset in the subsections
    // Charge system commit

    /* Check if we have a file-backed section */
    if (m_ControlArea.FileObject != NULL)
    {
        /* Is this an image mapping? */
        if (m_ControlArea.Flags.Image)
        {
            //__debugbreak();

            /// Alternative approach: map the whole section, read individ. sections, relocate!

            /* Loop all subsections, skip subsection 0 (headers) */
            for (ULONG i = 1; i < m_ControlArea.NumberOfSubsections; i++)
            {
                /// read the contents from the file
                Status = ReadFileData(this,
                                      m_ControlArea.FileObject,
                                      m_Subsections[i].StartingSector * SectorSize,
                                      m_Subsections[i].NumberOfFullSectors * SectorSize,
                                      m_Subsections[i].RelativeStartingVpn);
                if (!NT_SUCCESS(Status))
                {
                    __debugbreak();
                }
            }
        }
        else
        {
            Status = ReadFileData(this,
                                  m_ControlArea.FileObject,
                                  m_Subsections[0].StartingSector * SectorSize,
                                  m_Subsections[0].NumberOfPages * PAGE_SIZE,
                                  m_Subsections[0].RelativeStartingVpn);
            if (!NT_SUCCESS(Status))
            {
                __debugbreak();
            }
        }
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
PHYSICAL_SECTION::RelativeVpnToSubsectionIndex (
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

#if 0
// This much simpler variant can be used, if the prototypes are created with
// a protection according to the subsection protection
NTSTATUS
PHYSICAL_SECTION::CreateMapping (
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
PHYSICAL_SECTION::CreateMapping (
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
        ERR("Exceeding section size %lx\n", m_ControlArea.SizeInPages);
        return STATUS_INVALID_PARAMETER;
    }

    /* Check if we have only one subsection (non-image) */
    if (m_ControlArea.NumberOfSubsections == 1)
    {
        /* Map the sections shared memory object */
        Status = EalMapSharedMemoryObject(m_FileDescriptorIndex,
                                          BaseAddress,
                                          NumberOfPages * PAGE_SIZE,
                                          RelativeStartingVpn * PAGE_SIZE,
                                          Protect);
        if (NT_SUCCESS(Status))
        {
            /* Check for user mode memory */
            if (BaseAddress < MmHighestUserAddress)
            {
                /* Mark the pages as committed */
                CommitPagesInBitmap(AddressToVpn(BaseAddress), NumberOfPages);
            }
        }
    }
    else if (m_ControlArea.Flags.Image)
    {
        //__debugbreak();

//        Status = EalMapSharedMemoryObject(m_FileDescriptorIndex,
//                                          BaseAddress,
//                                          NumberOfPages * PAGE_SIZE,
//                                          RelativeStartingVpn * PAGE_SIZE,
//                                          MM_READONLY);

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

        /* Loop until the whole range is mapped */
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

            /* Check if this is a read only page */
            if (Subsection->Protect == MM_READONLY)
            {
                /* Map the shared memory as read only */
                Status = EalMapSharedMemoryObject(m_FileDescriptorIndex,
                                                  BaseAddress,
                                                  CurrentPageCount * PAGE_SIZE,
                                                  RelativeStartingVpn * PAGE_SIZE,
                                                  MM_READONLY);

            }
            else
            {
                /// FIXME: it should be shared for kernel mode, but in a
                /// special section (anonymous shared memory object)
                /// maybe implement custom copy-on-write
                /* Map the shared memory as copy-on-write */
                Status = EalMapSharedMemoryObject(m_FileDescriptorIndex,
                                                  BaseAddress,
                                                  CurrentPageCount * PAGE_SIZE,
                                                  RelativeStartingVpn * PAGE_SIZE,
                                                  0x80000000 | Subsection->Protect);
            }

            /* Map the prototype PTEs of this subsection */
//            m_ControlArea.Segment->MapPages(MappingVpn,
//                                            RelativeStartingVpn,
//                                            CurrentPageCount,
//                                            Protect);

            /* Check for user mode memory */
            if (NT_SUCCESS(Status) && (BaseAddress < MmHighestUserAddress))
            {
                /* Mark the pages as committed */
                CommitPagesInBitmap(AddressToVpn(BaseAddress), NumberOfPages);
            }

            /* Update mapping location and relative VPN */
            MappingVpn += CurrentPageCount;
            RelativeStartingVpn += CurrentPageCount;
            NumberOfPages -= CurrentPageCount;
            BaseAddress = AddToPointer(BaseAddress, CurrentPageCount * PAGE_SIZE);

            /* Go to the next subsection */
            Subsection++;
            StartingPageIndex = 0;
        }
        while (NumberOfPages > 0);
    }
    else
    {
        __debugbreak();
        /// use a linux file mapping directly
    }

    return Status;
}
#endif

NTSTATUS
PHYSICAL_SECTION::GetMapping (
    _Out_ PVOID* BaseAddress,
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages)
{
    NTSTATUS Status;

    /* Check if the actual section has been created */
    if (m_FileDescriptorIndex == 0)
    {
        /* Create the shared memory object */
        m_FileDescriptorIndex = EalCreateSharedMemoryObject();
        if (m_FileDescriptorIndex == 0)
        {
            ERR("Failed to create a shared memory object\n");
            __debugbreak();
            return STATUS_UNSUCCESSFUL;
        }

        m_TruncatedSize = m_ControlArea.SizeInPages * PAGE_SIZE;
        EalSetSectionSize(m_FileDescriptorIndex, m_TruncatedSize);
    }

    /* Reserve address range */
    *BaseAddress = NULL;
    Status = g_KernelAddressSpace.ReserveVirtualMemory(BaseAddress,
                                                       NumberOfPages,
                                                       MM_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        __debugbreak();
        return Status;
    }

    /* Map the section pages to the reserved memory */
    Status = EalMapSharedMemoryObject(m_FileDescriptorIndex,
                                      *BaseAddress,
                                      NumberOfPages * PAGE_SIZE,
                                      RelativeStartingVpn * PAGE_SIZE,
                                      MM_READWRITE);
    if (!NT_SUCCESS(Status))
    {
        /// detele reserved address space
        __debugbreak();
        return Status;
    }

    return Status;
}

VOID
PHYSICAL_SECTION::RemoveMapping (
    _In_ PVOID BaseAddress,
    _In_ SIZE_T Size)
{
    EalUnmapVirtualMemory(BaseAddress, Size);
    g_KernelAddressSpace.ReleaseVirtualMemory(BaseAddress);
}

NTSTATUS
PHYSICAL_SECTION::SetPageContent (
    _In_ ULONG_PTR RelativeStartingVpn,
    _In_ ULONG_PTR NumberOfPages,
    _In_ PVOID Buffer)
{
    NTSTATUS Status;
    PVOID BaseAddress;

    if (m_FileDescriptorIndex == 0)
    {
        /* Create the shared memory object */
        m_FileDescriptorIndex = EalCreateSharedMemoryObject();
        if (m_FileDescriptorIndex == 0)
        {
            ERR("Failed to create a shared memory object\n");
            __debugbreak();
            return STATUS_UNSUCCESSFUL;
        }

        m_TruncatedSize = m_ControlArea.SizeInPages * PAGE_SIZE;
        EalSetSectionSize(m_FileDescriptorIndex, m_TruncatedSize);
    }

    /* Check if the size is already big anough */
    //if (

    /* Get a system space mapping */
    Status = GetMapping(&BaseAddress, RelativeStartingVpn, NumberOfPages);
    if (!NT_SUCCESS(Status))
    {
        __debugbreak();
        return Status;
    }

    /* Copy the data */
    RtlCopyMemory(BaseAddress, Buffer, NumberOfPages * PAGE_SIZE);

    /* Remove the mapping again */
    RemoveMapping(BaseAddress, NumberOfPages * PAGE_SIZE);

    return STATUS_SUCCESS;
}

NTSTATUS
PHYSICAL_SECTION::PrefetchPages (
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
    // NT File system internsla p. 240
    UNIMPLEMENTED;
    return FALSE;
}

_IRQL_requires_max_ (APC_LEVEL)
BOOLEAN
NTAPI
MmForceSectionClosed (
  _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
  _In_ BOOLEAN DelayClose)
{
    UNIMPLEMENTED;
    return FALSE;
}

BOOLEAN
NTAPI
MmDisableModifiedWriteOfSection (
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer)
{
    UNIMPLEMENTED;
    return FALSE;
}

}; // extern "C"
}; // namespace Mm

/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Kernel Streaming
 * FILE:            drivers/wdm/audio/backpln/portcls/irpstream.cpp
 * PURPOSE:         IRP Stream handling
 * PROGRAMMER:      Johannes Anderwald
 */

#include "private.hpp"


class CIrpQueue : public IIrpQueue
{
public:
    STDMETHODIMP QueryInterface( REFIID InterfaceId, PVOID* Interface);

    STDMETHODIMP_(ULONG) AddRef()
    {
        InterlockedIncrement(&m_Ref);
        return m_Ref;
    }
    STDMETHODIMP_(ULONG) Release()
    {
        InterlockedDecrement(&m_Ref);

        if (!m_Ref)
        {
            delete this;
            return 0;
        }
        return m_Ref;
    }
    IMP_IIrpQueue;
    CIrpQueue(IUnknown *OuterUnknown){}
    virtual ~CIrpQueue(){}

protected:
    volatile ULONG m_CurrentOffset;
    LONG m_NumMappings;
    ULONG m_NumDataAvailable;
    PKSPIN_CONNECT m_ConnectDetails;
    KSPIN_LOCK m_IrpListLock;
    LIST_ENTRY m_IrpList;
    LIST_ENTRY m_FreeIrpList;
    PIRP m_Irp;
    PVOID m_SilenceBuffer;

    ULONG m_OutOfMapping;
    ULONG m_MaxFrameSize;
    ULONG m_Alignment;

    LONG m_Ref;

};

#define OFFSET_HEADERINDEX  (0)
#define OFFSET_STREAMHEADER (2)
#define OFFSET_HEADERCOUNT  (3)


#define STREAMHEADER_INDEX(Irp)   (PtrToUlong(Irp->Tail.Overlay.DriverContext[OFFSET_HEADERINDEX]))
#define STREAMHEADER_COUNT(Irp)   (PtrToUlong(Irp->Tail.Overlay.DriverContext[OFFSET_HEADERCOUNT]))
#define STREAMHEADER_CURRENT(Irp) (Irp->Tail.Overlay.DriverContext[OFFSET_STREAMHEADER])


NTSTATUS
NTAPI
CIrpQueue::QueryInterface(
    IN  REFIID refiid,
    OUT PVOID* Output)
{
    if (IsEqualGUIDAligned(refiid, IID_IUnknown))
    {
        *Output = PVOID(PUNKNOWN(this));
        PUNKNOWN(*Output)->AddRef();
        return STATUS_SUCCESS;
    }

    return STATUS_UNSUCCESSFUL;
}

NTSTATUS
NTAPI
CIrpQueue::Init(
    IN KSPIN_CONNECT *ConnectDetails,
    IN ULONG FrameSize,
    IN ULONG Alignment,
    IN PVOID SilenceBuffer)
{
    m_ConnectDetails = ConnectDetails;
    m_MaxFrameSize = FrameSize;
    m_SilenceBuffer = SilenceBuffer;
    m_Alignment = Alignment;

    InitializeListHead(&m_IrpList);
    InitializeListHead(&m_FreeIrpList);
    KeInitializeSpinLock(&m_IrpListLock);

    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
CIrpQueue::AddMapping(
    IN PIRP Irp,
    OUT PULONG Data)
{
    PKSSTREAM_HEADER Header;
    NTSTATUS Status = STATUS_SUCCESS;
    PIO_STACK_LOCATION IoStack;
    ULONG NumHeaders, NumData, Index;
    PMDL Mdl;

    PC_ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);

    // get current irp stack location
    IoStack = IoGetCurrentIrpStackLocation(Irp);

    if (!Irp->MdlAddress)
    {
        // ioctl from KsStudio
        // Wdmaud already probes buffers, therefore no need to probe it again
        // probe the stream irp
        if (IoStack->Parameters.DeviceIoControl.IoControlCode == IOCTL_KS_WRITE_STREAM)
            Status = KsProbeStreamIrp(Irp, KSSTREAM_WRITE | KSPROBE_ALLOCATEMDL | KSPROBE_PROBEANDLOCK | KSPROBE_SYSTEMADDRESS, 0);
        else if (IoStack->Parameters.DeviceIoControl.IoControlCode == IOCTL_KS_READ_STREAM)
            Status = KsProbeStreamIrp(Irp, KSSTREAM_READ  | KSPROBE_ALLOCATEMDL | KSPROBE_PROBEANDLOCK | KSPROBE_SYSTEMADDRESS, 0);
        else 
            PC_ASSERT(0);

        // check for success
        if (!NT_SUCCESS(Status))
        {
            DPRINT("KsProbeStreamIrp failed with %x\n", Status);
            return Status;
        }
    }

    // get first stream header

   if (Irp->RequestorMode == UserMode)
       Header = (PKSSTREAM_HEADER)Irp->AssociatedIrp.SystemBuffer;
   else
       Header = (PKSSTREAM_HEADER)Irp->UserBuffer;

    // sanity check
    PC_ASSERT(Header);

    // calculate num headers
    NumHeaders = IoStack->Parameters.DeviceIoControl.OutputBufferLength / Header->Size;

    // assume headers of same length
    PC_ASSERT(IoStack->Parameters.DeviceIoControl.OutputBufferLength % Header->Size == 0);


    // get first audio buffer
    Mdl = Irp->MdlAddress;
    // sanity check
    PC_ASSERT(Mdl);

    // store the current stream header
    Irp->Tail.Overlay.DriverContext[OFFSET_STREAMHEADER] = (PVOID)Header;
    // store header count
    Irp->Tail.Overlay.DriverContext[OFFSET_HEADERCOUNT] = UlongToPtr(NumHeaders);

    // store current header index
    Irp->Tail.Overlay.DriverContext[OFFSET_HEADERINDEX] = UlongToPtr(0);

    NumData = 0;
    // prepare all headers
    for(Index = 0; Index < NumHeaders; Index++)
    {
        // sanity checks
        PC_ASSERT(Header);
        PC_ASSERT(Mdl);

        if (Irp->RequestorMode == UserMode)
        {
            Header->Data = MmGetSystemAddressForMdlSafe(Mdl, NormalPagePriority);
        }

        if (!Header->Data)
        {
            // insufficient resources
            ExFreePool(Irp->AssociatedIrp.SystemBuffer);
            Irp->AssociatedIrp.SystemBuffer = NULL;
            // complete and forget request
            Irp->IoStatus.Status = STATUS_INSUFFICIENT_RESOURCES;
            Irp->IoStatus.Information = 0;

            IoCompleteRequest(Irp, IO_NO_INCREMENT); 
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        // increment num mappings
        InterlockedIncrement(&m_NumMappings);

        // increment available data
        InterlockedExchangeAdd((PLONG)&m_NumDataAvailable, 
                                      (max(Header->DataUsed, Header->FrameExtent)));

        NumData += max(Header->DataUsed, Header->FrameExtent);

        // move to next header
        Header = (PKSSTREAM_HEADER)((ULONG_PTR)Header + Header->Size);
        
        // move to next mdl
        Mdl = Mdl->Next;
    }

    DPRINT("StreamHeaders %u NumData %u FrameSize %u NumDataAvailable %u\n", NumHeaders, NumData, m_MaxFrameSize, m_NumDataAvailable);
    *Data = NumData;

    // mark irp as pending
    IoMarkIrpPending(Irp);

    // add irp to cancelable queue
    KsAddIrpToCancelableQueue(&m_IrpList, &m_IrpListLock, Irp, KsListEntryTail, NULL);

    // disable mapping failed status
    m_OutOfMapping = FALSE;

    // done
    return Status;
}

NTSTATUS
NTAPI
CIrpQueue::GetMapping(
    OUT PUCHAR * Buffer,
    OUT PULONG BufferSize)
{
    PIRP Irp;
    ULONG Offset;
    //PIO_STACK_LOCATION IoStack;
    PKSSTREAM_HEADER StreamHeader;

    // check if there is an irp in the partially processed
    if (m_Irp)
    {
        // use last irp
        if (m_Irp->Cancel == FALSE)
        {
            Irp = m_Irp;
            Offset = m_CurrentOffset;
        }
        else
        {
            // irp has been cancelled
            m_Irp->IoStatus.Status = STATUS_CANCELLED;
            IoCompleteRequest(m_Irp, IO_NO_INCREMENT);
            m_Irp = Irp = NULL;
        }
    }
    else
    {
        // get a fresh new irp from the queue
        m_Irp = Irp = KsRemoveIrpFromCancelableQueue(&m_IrpList, &m_IrpListLock, KsListEntryHead, KsAcquireAndRemoveOnlySingleItem);
        m_CurrentOffset = Offset = 0;
    }

    if (!Irp && m_SilenceBuffer && m_MaxFrameSize)
    {
        DPRINT("NoIrp\n");
        // no irp available, use silence buffer
        *Buffer = (PUCHAR)m_SilenceBuffer;
        *BufferSize = m_MaxFrameSize;
        return STATUS_SUCCESS;
    }

    if (!Irp)
    {
        // no irp buffer available
        return STATUS_UNSUCCESSFUL;
    }


    // get stream header
    StreamHeader = (PKSSTREAM_HEADER)Irp->Tail.Overlay.DriverContext[2];

    // sanity check
    PC_ASSERT(StreamHeader);

    // store buffersize
    if (StreamHeader->DataUsed)
        *BufferSize = StreamHeader->DataUsed - Offset;
    else
        *BufferSize = StreamHeader->FrameExtent - Offset;

    PC_ASSERT(*BufferSize);

    // store buffer
    *Buffer = &((PUCHAR)StreamHeader->Data)[Offset];

    // unset flag that no irps are available
    m_OutOfMapping = FALSE;

    return STATUS_SUCCESS;
}

VOID
NTAPI
CIrpQueue::UpdateMapping(
    IN ULONG BytesWritten)
{
    PKSSTREAM_HEADER StreamHeader;
    ULONG Size, NumData, Index;

    if (!m_Irp)
    {
        // silence buffer was used
        return;
    }

    // get stream header
    StreamHeader = (PKSSTREAM_HEADER)STREAMHEADER_CURRENT(m_Irp);

    // sanity check
   // ASSERT(StreamHeader);

    // add to current offset
    InterlockedExchangeAdd((volatile PLONG)&m_CurrentOffset, (LONG)BytesWritten);

    // decrement available data counter
    m_NumDataAvailable -= BytesWritten;

    if (StreamHeader->DataUsed)
        Size = StreamHeader->DataUsed;
    else
        Size = StreamHeader->FrameExtent;

    PC_ASSERT(Size);

    if (m_CurrentOffset >= Size)
    {
        if (STREAMHEADER_INDEX(m_Irp) + 1 < STREAMHEADER_COUNT(m_Irp))
        {
            // the irp has at least one more stream header
            m_Irp->Tail.Overlay.DriverContext[OFFSET_HEADERINDEX] = UlongToPtr(STREAMHEADER_INDEX(m_Irp) + 1);

            // get next stream header         
            StreamHeader = (PKSSTREAM_HEADER)((ULONG_PTR)StreamHeader + StreamHeader->Size);

            // store next stream header
            STREAMHEADER_CURRENT(m_Irp) = (PVOID)StreamHeader;

            // reset current offset
            m_CurrentOffset = 0;

            // done
            return;
        }

       // irp has been processed completly

        NumData = 0;
        if (m_Irp->RequestorMode == KernelMode)
            StreamHeader = (PKSSTREAM_HEADER)m_Irp->UserBuffer;
        else
            StreamHeader = (PKSSTREAM_HEADER)m_Irp->AssociatedIrp.SystemBuffer;

        // loop all stream headers
        for(Index = 0; Index < STREAMHEADER_COUNT(m_Irp); Index++)
        {
            PC_ASSERT(StreamHeader);

            // add size of buffer
            // depends on if the buffer is input / output
            if (StreamHeader->DataUsed)
                Size = StreamHeader->DataUsed;
            else
                Size = StreamHeader->FrameExtent;

            // increment size
            NumData += Size;

            // get next stream header
            StreamHeader = (PKSSTREAM_HEADER)((ULONG_PTR)StreamHeader + StreamHeader->Size);
        }

        if (m_ConnectDetails->Interface.Id == KSINTERFACE_STANDARD_LOOPED_STREAMING)
        {
            // looped streaming repeat the buffers untill
            // the caller decides to stop the streams

            // reset stream header index
            m_Irp->Tail.Overlay.DriverContext[OFFSET_HEADERINDEX] = UlongToPtr(0);
            // re-insert irp
            KsAddIrpToCancelableQueue(&m_IrpList, &m_IrpListLock, m_Irp, KsListEntryTail, NULL);
            // clear current irp
            m_Irp = NULL;
            // reset offset
            m_CurrentOffset = 0;
            // increment available data
            InterlockedExchangeAdd((PLONG)&m_NumDataAvailable, NumData);
            // done
            return;
        }

        m_Irp->IoStatus.Status = STATUS_SUCCESS;
        m_Irp->IoStatus.Information = NumData;

        // complete the request
        IoCompleteRequest(m_Irp, IO_SOUND_INCREMENT);
        // remove irp as it is complete
        m_Irp = NULL;
        m_CurrentOffset = 0;
    }
}

ULONG
NTAPI
CIrpQueue::NumData()
{
    // returns the amount of audio stream data available
    return m_NumDataAvailable;
}

BOOL
NTAPI
CIrpQueue::CancelBuffers()
{
    // is there an active irp
    if (m_Irp)
    {
        // re-insert it to cancelable queue
        KsAddIrpToCancelableQueue(&m_IrpList, &m_IrpListLock, m_Irp, KsListEntryTail, NULL);
        //set it to zero
        m_Irp = NULL;
    }

    // cancel all irps
    KsCancelIo(&m_IrpList, &m_IrpListLock);
    // reset number of mappings
    m_NumMappings = 0;
    // reset number of data available
    m_NumDataAvailable = 0;

    // done
    return TRUE;
}

NTSTATUS
NTAPI
CIrpQueue::GetMappingWithTag(
    IN PVOID Tag,
    OUT PPHYSICAL_ADDRESS  PhysicalAddress,
    OUT PVOID  *VirtualAddress,
    OUT PULONG  ByteCount,
    OUT PULONG  Flags)
{
    PKSSTREAM_HEADER StreamHeader;
    PIRP Irp;

    *Flags = 0;
    PC_ASSERT(Tag != NULL);

    // get an irp from the queue
    Irp = KsRemoveIrpFromCancelableQueue(&m_IrpList, &m_IrpListLock, KsListEntryHead, KsAcquireAndRemoveOnlySingleItem);

    // check if there is an irp
    if (!Irp)
    {
        // no irp available
        m_OutOfMapping = TRUE;
        return STATUS_NOT_FOUND;
    }

    //FIXME support more than one stream header
    PC_ASSERT(STREAMHEADER_COUNT(Irp) == 1);

    // HACK get stream header
    StreamHeader = (PKSSTREAM_HEADER)Irp->Tail.Overlay.DriverContext[2];

    // store mapping in the free list
    ExInterlockedInsertTailList(&m_FreeIrpList, &Irp->Tail.Overlay.ListEntry, &m_IrpListLock);

    // return mapping
    *PhysicalAddress = MmGetPhysicalAddress(StreamHeader->Data);
    *VirtualAddress = StreamHeader->Data;
    *ByteCount = StreamHeader->DataUsed;

    // decrement mapping count
    InterlockedDecrement(&m_NumMappings);
    // decrement num data available
    m_NumDataAvailable -= StreamHeader->DataUsed;

    // store tag in irp
    Irp->Tail.Overlay.DriverContext[3] = Tag;

    // done
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
CIrpQueue::ReleaseMappingWithTag(
    IN PVOID Tag)
{
    PIRP Irp;
    PLIST_ENTRY CurEntry;
    PKSSTREAM_HEADER StreamHeader;

    DPRINT("CIrpQueue::ReleaseMappingWithTag Tag %p\n", Tag);

    // remove irp from used list
    CurEntry = ExInterlockedRemoveHeadList(&m_FreeIrpList, &m_IrpListLock);
    // sanity check
    PC_ASSERT(CurEntry);

    // get irp from list entry
    Irp = (PIRP)CONTAINING_RECORD(CurEntry, IRP, Tail.Overlay.ListEntry);

    // HACK get stream header
    StreamHeader = (PKSSTREAM_HEADER)Irp->Tail.Overlay.DriverContext[2];

    // driver must release items in the same order
    PC_ASSERT(Irp->Tail.Overlay.DriverContext[3] == Tag);

    // irp has been processed completly
    Irp->IoStatus.Status = STATUS_SUCCESS;

    // frame extend contains the original request size, DataUsed contains the real buffer size
    // is different when kmixer performs channel conversion, upsampling etc
    
    Irp->IoStatus.Information = StreamHeader->FrameExtent;

    // complete the request
    IoCompleteRequest(Irp, IO_SOUND_INCREMENT);

    return STATUS_SUCCESS;
}

BOOLEAN
NTAPI
CIrpQueue::HasLastMappingFailed()
{
    return m_OutOfMapping;
}

ULONG
NTAPI
CIrpQueue::GetCurrentIrpOffset()
{

    return m_CurrentOffset;
}

BOOLEAN
NTAPI
CIrpQueue::GetAcquiredTagRange(
    IN PVOID * FirstTag,
    IN PVOID * LastTag)
{
    KIRQL OldLevel;
    BOOLEAN Ret = FALSE;
    PIRP Irp;
    PLIST_ENTRY CurEntry;

    KeAcquireSpinLock(&m_IrpListLock, &OldLevel);

    if (!IsListEmpty(&m_FreeIrpList))
    {
        // get first entry
        CurEntry = RemoveHeadList(&m_FreeIrpList);
        // get irp from list entry
        Irp = (PIRP)CONTAINING_RECORD(CurEntry, IRP, Tail.Overlay.ListEntry);

        // get tag of first acquired buffer
        *FirstTag = Irp->Tail.Overlay.DriverContext[3];

        // put back irp
        InsertHeadList(&m_FreeIrpList, &Irp->Tail.Overlay.ListEntry);

        // get last entry
        CurEntry = RemoveTailList(&m_FreeIrpList);
        // get irp from list entry
        Irp = (PIRP)CONTAINING_RECORD(CurEntry, IRP, Tail.Overlay.ListEntry);

        // get tag of first acquired buffer
        *LastTag = Irp->Tail.Overlay.DriverContext[3];

        // put back irp
        InsertTailList(&m_FreeIrpList, &Irp->Tail.Overlay.ListEntry);

        // indicate success
        Ret = TRUE;
    }

    // release lock
    KeReleaseSpinLock(&m_IrpListLock, OldLevel);
    // done
    return Ret;
}

NTSTATUS
NTAPI
NewIrpQueue(
    IN IIrpQueue **Queue)
{
    CIrpQueue *This = new(NonPagedPool, TAG_PORTCLASS)CIrpQueue(NULL);
    if (!This)
        return STATUS_INSUFFICIENT_RESOURCES;

    This->AddRef();

    *Queue = (IIrpQueue*)This;
    return STATUS_SUCCESS;
}

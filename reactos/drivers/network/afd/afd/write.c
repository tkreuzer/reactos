/*
 * COPYRIGHT:        See COPYING in the top level directory
 * PROJECT:          ReactOS kernel
 * FILE:             drivers/net/afd/afd/write.c
 * PURPOSE:          Ancillary functions driver
 * PROGRAMMER:       Art Yerkes (ayerkes@speakeasy.net)
 * UPDATE HISTORY:
 * 20040708 Created
 */
#include "afd.h"
#include "tdi_proto.h"
#include "tdiconn.h"
#include "debug.h"

static NTSTATUS NTAPI SendComplete
( PDEVICE_OBJECT DeviceObject,
  PIRP Irp,
  PVOID Context ) {
    NTSTATUS Status = Irp->IoStatus.Status;
    PAFD_FCB FCB = (PAFD_FCB)Context;
    PLIST_ENTRY NextIrpEntry;
    PIRP NextIrp = NULL;
    PIO_STACK_LOCATION NextIrpSp;
    PAFD_SEND_INFO SendReq = NULL;
    PAFD_MAPBUF Map;
    UINT TotalBytesCopied = 0, SpaceAvail, i, CopySize = 0;

    /*
     * The Irp parameter passed in is the IRP of the stream between AFD and
     * TDI driver. It's not very usefull to us. We need the IRPs of the stream
     * between usermode and AFD. Those are chained from
     * FCB->PendingIrpList[FUNCTION_SEND] and you'll see them in the code
     * below as "NextIrp" ('cause they are the next usermode IRP to be
     * processed).
     */

    AFD_DbgPrint(MID_TRACE,("Called, status %x, %d bytes used\n",
							Irp->IoStatus.Status,
							Irp->IoStatus.Information));

    if( !SocketAcquireStateLock( FCB ) )
        return STATUS_FILE_CLOSED;

    FCB->SendIrp.InFlightRequest = NULL;
    /* Request is not in flight any longer */

    if( FCB->State == SOCKET_STATE_CLOSED ) {
        /* Cleanup our IRP queue because the FCB is being destroyed */
        while( !IsListEmpty( &FCB->PendingIrpList[FUNCTION_SEND] ) ) {
	       NextIrpEntry = RemoveHeadList(&FCB->PendingIrpList[FUNCTION_SEND]);
	       NextIrp = CONTAINING_RECORD(NextIrpEntry, IRP, Tail.Overlay.ListEntry);
	       NextIrpSp = IoGetCurrentIrpStackLocation( NextIrp );
	       SendReq = NextIrpSp->Parameters.DeviceIoControl.Type3InputBuffer;
	       NextIrp->IoStatus.Status = STATUS_FILE_CLOSED;
	       NextIrp->IoStatus.Information = 0;
	       UnlockBuffers(SendReq->BufferArray, SendReq->BufferCount, FALSE);
	       if( NextIrp->MdlAddress ) UnlockRequest( NextIrp, IoGetCurrentIrpStackLocation( NextIrp ) );
               (void)IoSetCancelRoutine(NextIrp, NULL);
	       IoCompleteRequest( NextIrp, IO_NETWORK_INCREMENT );
        }
	SocketStateUnlock( FCB );
	return STATUS_FILE_CLOSED;
    }

    if( !NT_SUCCESS(Status) ) {
		/* Complete all following send IRPs with error */

		while( !IsListEmpty( &FCB->PendingIrpList[FUNCTION_SEND] ) ) {
			NextIrpEntry =
				RemoveHeadList(&FCB->PendingIrpList[FUNCTION_SEND]);
			NextIrp =
				CONTAINING_RECORD(NextIrpEntry, IRP, Tail.Overlay.ListEntry);
			NextIrpSp = IoGetCurrentIrpStackLocation( NextIrp );
			SendReq = NextIrpSp->Parameters.DeviceIoControl.Type3InputBuffer;

			UnlockBuffers( SendReq->BufferArray,
						   SendReq->BufferCount,
						   FALSE );

			NextIrp->IoStatus.Status = Status;
			NextIrp->IoStatus.Information = 0;

			if ( NextIrp->MdlAddress ) UnlockRequest( NextIrp, IoGetCurrentIrpStackLocation( NextIrp ) );
                        (void)IoSetCancelRoutine(NextIrp, NULL);
			IoCompleteRequest( NextIrp, IO_NETWORK_INCREMENT );
		}

		SocketStateUnlock( FCB );

		return STATUS_SUCCESS;
    }

    RtlMoveMemory( FCB->Send.Window,
				   FCB->Send.Window + FCB->Send.BytesUsed,
				   FCB->Send.BytesUsed - Irp->IoStatus.Information );
    FCB->Send.BytesUsed -= Irp->IoStatus.Information;

    if( !FCB->Send.BytesUsed &&
		!IsListEmpty( &FCB->PendingIrpList[FUNCTION_SEND] ) ) {
		NextIrpEntry =
			RemoveHeadList(&FCB->PendingIrpList[FUNCTION_SEND]);
		NextIrp =
			CONTAINING_RECORD(NextIrpEntry, IRP, Tail.Overlay.ListEntry);
		NextIrpSp = IoGetCurrentIrpStackLocation( NextIrp );
		SendReq = NextIrpSp->Parameters.DeviceIoControl.Type3InputBuffer;
		Map = (PAFD_MAPBUF)(SendReq->BufferArray + SendReq->BufferCount);

		AFD_DbgPrint(MID_TRACE,("SendReq @ %x\n", SendReq));

		SpaceAvail = FCB->Send.Size - FCB->Send.BytesUsed;

		for( i = 0; i < SendReq->BufferCount; i++ ) {
			Map[i].BufferAddress =
				MmMapLockedPages( Map[i].Mdl, KernelMode );

			CopySize = MIN( SpaceAvail,
							SendReq->BufferArray[i].len );

			RtlCopyMemory( FCB->Send.Window + FCB->Send.BytesUsed,
						   Map[i].BufferAddress,
						   CopySize );

			MmUnmapLockedPages( Map[i].BufferAddress, Map[i].Mdl );

			FCB->Send.BytesUsed += CopySize;
			TotalBytesCopied += CopySize;
			SpaceAvail -= CopySize;
		}
    }

    /* Some data is still waiting */
    if( FCB->Send.BytesUsed ) {
		FCB->PollState &= ~AFD_EVENT_SEND;

		Status = TdiSend( &FCB->SendIrp.InFlightRequest,
						  FCB->Connection.Object,
						  0,
						  FCB->Send.Window,
						  FCB->Send.BytesUsed,
						  &FCB->SendIrp.Iosb,
						  SendComplete,
						  FCB );
    } else {
		FCB->PollState |= AFD_EVENT_SEND;
		FCB->PollStatus[FD_WRITE_BIT] = STATUS_SUCCESS;
		PollReeval( FCB->DeviceExt, FCB->FileObject );
    }

    if( TotalBytesCopied > 0 ) {
		UnlockBuffers( SendReq->BufferArray, SendReq->BufferCount, FALSE );

		if( Status == STATUS_PENDING )
			Status = STATUS_SUCCESS;

		AFD_DbgPrint(MID_TRACE,("Dismissing request: %x\n", Status));

		return UnlockAndMaybeComplete( FCB, Status, NextIrp, TotalBytesCopied );
    } else if( NextIrp ) {
		AFD_DbgPrint(MID_TRACE,("Could not do any more with Irp %x\n",
								NextIrp));
		InsertHeadList( &FCB->PendingIrpList[FUNCTION_SEND],
						&NextIrp->Tail.Overlay.ListEntry );
    }

    SocketStateUnlock( FCB );

    return STATUS_SUCCESS;
}

static NTSTATUS NTAPI PacketSocketSendComplete
( PDEVICE_OBJECT DeviceObject,
  PIRP Irp,
  PVOID Context ) {
    PAFD_FCB FCB = (PAFD_FCB)Context;
    PLIST_ENTRY NextIrpEntry;
    PIRP NextIrp;

    AFD_DbgPrint(MID_TRACE,("Called, status %x, %d bytes used\n",
							Irp->IoStatus.Status,
							Irp->IoStatus.Information));

    if( !SocketAcquireStateLock( FCB ) )
        return STATUS_FILE_CLOSED;

    FCB->SendIrp.InFlightRequest = NULL;
    /* Request is not in flight any longer */

    FCB->PollState |= AFD_EVENT_SEND;
    FCB->PollStatus[FD_WRITE_BIT] = STATUS_SUCCESS;
    PollReeval( FCB->DeviceExt, FCB->FileObject );

    if( FCB->State == SOCKET_STATE_CLOSED ) {
        /* Cleanup our IRP queue because the FCB is being destroyed */
        while( !IsListEmpty( &FCB->PendingIrpList[FUNCTION_SEND] ) ) {
	       NextIrpEntry = RemoveHeadList(&FCB->PendingIrpList[FUNCTION_SEND]);
	       NextIrp = CONTAINING_RECORD(NextIrpEntry, IRP, Tail.Overlay.ListEntry);
	       NextIrp->IoStatus.Status = STATUS_FILE_CLOSED;
	       NextIrp->IoStatus.Information = 0;
	       if( NextIrp->MdlAddress ) UnlockRequest( NextIrp, IoGetCurrentIrpStackLocation( NextIrp ) );
               (void)IoSetCancelRoutine(NextIrp, NULL);
	       IoCompleteRequest( NextIrp, IO_NETWORK_INCREMENT );
        }
	SocketStateUnlock( FCB );
	return STATUS_FILE_CLOSED;
    }

    SocketStateUnlock( FCB );

    return STATUS_SUCCESS;
}

NTSTATUS NTAPI
AfdConnectedSocketWriteData(PDEVICE_OBJECT DeviceObject, PIRP Irp,
							PIO_STACK_LOCATION IrpSp, BOOLEAN Short) {
    NTSTATUS Status = STATUS_SUCCESS;
    PFILE_OBJECT FileObject = IrpSp->FileObject;
    PAFD_FCB FCB = FileObject->FsContext;
    PAFD_SEND_INFO SendReq;
	ULONG Information;
    UINT TotalBytesCopied = 0, i, CopySize = 0,
		SpaceAvail = 0, TotalBytesEncountered = 0;

    AFD_DbgPrint(MID_TRACE,("Called on %x\n", FCB));

    if( !SocketAcquireStateLock( FCB ) ) return LostSocket( Irp );

    if( FCB->Flags & AFD_ENDPOINT_CONNECTIONLESS )
    {
        PAFD_SEND_INFO_UDP SendReq;
        PTDI_CONNECTION_INFORMATION TargetAddress;

        /* Check that the socket is bound */
        if( FCB->State != SOCKET_STATE_BOUND || !FCB->RemoteAddress )
            return UnlockAndMaybeComplete( FCB, STATUS_INVALID_PARAMETER, Irp,
                                           0 );

        if( !(SendReq = LockRequest( Irp, IrpSp )) )
            return UnlockAndMaybeComplete( FCB, STATUS_NO_MEMORY, Irp, 0 );

        /* Must lock buffers before handing off user data */
        SendReq->BufferArray = LockBuffers( SendReq->BufferArray,
                                            SendReq->BufferCount,
                                            NULL, NULL,
                                            FALSE, FALSE );

		if( !SendReq->BufferArray ) {
			return UnlockAndMaybeComplete( FCB, STATUS_ACCESS_VIOLATION,
                                           Irp, 0 );
		}

        Status = TdiBuildConnectionInfo( &TargetAddress, FCB->RemoteAddress );

		if( NT_SUCCESS(Status) ) {
            Status = TdiSendDatagram
                ( &FCB->SendIrp.InFlightRequest,
                  FCB->AddressFile.Object,
                  SendReq->BufferArray[0].buf,
                  SendReq->BufferArray[0].len,
                  TargetAddress,
                  &FCB->SendIrp.Iosb,
                  PacketSocketSendComplete,
                  FCB );

			ExFreePool( TargetAddress );
		}

        if( Status == STATUS_PENDING ) Status = STATUS_SUCCESS;

        AFD_DbgPrint(MID_TRACE,("Dismissing request: %x\n", Status));

		/* Even if we were pended, we're done with the user buffer at this
		 * point. */
		Information = SendReq->BufferArray[0].len;
		UnlockBuffers(SendReq->BufferArray, SendReq->BufferCount, FALSE);
        return UnlockAndMaybeComplete( FCB, Status, Irp, Information );
    }

    if( !(SendReq = LockRequest( Irp, IrpSp )) )
		return UnlockAndMaybeComplete
			( FCB, STATUS_NO_MEMORY, Irp, TotalBytesCopied );

    SendReq->BufferArray = LockBuffers( SendReq->BufferArray,
										SendReq->BufferCount,
										NULL, NULL,
										FALSE, FALSE );

    if( !SendReq->BufferArray ) {
        return UnlockAndMaybeComplete( FCB, STATUS_ACCESS_VIOLATION,
                                       Irp, 0 );
    }

    AFD_DbgPrint(MID_TRACE,("Socket state %d\n", FCB->State));

    if( FCB->State != SOCKET_STATE_CONNECTED ) {
		if( SendReq->AfdFlags & AFD_IMMEDIATE ) {
			AFD_DbgPrint(MID_TRACE,("Nonblocking\n"));
			UnlockBuffers( SendReq->BufferArray, SendReq->BufferCount, FALSE );
			return UnlockAndMaybeComplete
				( FCB, STATUS_CANT_WAIT, Irp, 0 );
		} else {
			AFD_DbgPrint(MID_TRACE,("Queuing request\n"));
			return LeaveIrpUntilLater( FCB, Irp, FUNCTION_SEND );
		}
    }

    AFD_DbgPrint(MID_TRACE,("FCB->Send.BytesUsed = %d\n",
							FCB->Send.BytesUsed));

    if( !FCB->Send.BytesUsed ) {
		SpaceAvail = FCB->Send.Size - FCB->Send.BytesUsed;

		AFD_DbgPrint(MID_TRACE,("We can accept %d bytes\n",
								SpaceAvail));

		for( i = 0; FCB->Send.BytesUsed < FCB->Send.Size &&
				 i < SendReq->BufferCount; i++ ) {
			CopySize = MIN( SpaceAvail,
							SendReq->BufferArray[i].len );

			TotalBytesEncountered += SendReq->BufferArray[i].len;

			AFD_DbgPrint(MID_TRACE,("Copying Buffer %d, %x:%d to %x\n",
									i,
									SendReq->BufferArray[i].buf,
									CopySize,
									FCB->Send.Window + FCB->Send.BytesUsed));

			RtlCopyMemory( FCB->Send.Window + FCB->Send.BytesUsed,
						   SendReq->BufferArray[i].buf,
						   CopySize );

			FCB->Send.BytesUsed += CopySize;
			TotalBytesCopied += CopySize;
			SpaceAvail -= CopySize;
		}

		if( TotalBytesEncountered == 0 ) {
			UnlockBuffers( SendReq->BufferArray, SendReq->BufferCount, FALSE );

			AFD_DbgPrint(MID_TRACE,("Empty send\n"));
			return UnlockAndMaybeComplete
				( FCB, Status, Irp, TotalBytesCopied );
		}

		AFD_DbgPrint(MID_TRACE,("Completed %d bytes\n", TotalBytesCopied));

		if( TotalBytesCopied > 0 ) {
			UnlockBuffers( SendReq->BufferArray, SendReq->BufferCount, FALSE );

			Status = TdiSend( &FCB->SendIrp.InFlightRequest,
							  FCB->Connection.Object,
							  0,
							  FCB->Send.Window,
							  FCB->Send.BytesUsed,
							  &FCB->SendIrp.Iosb,
							  SendComplete,
							  FCB );

			if( Status == STATUS_PENDING )
				Status = STATUS_SUCCESS;

			AFD_DbgPrint(MID_TRACE,("Dismissing request: %x (%d)\n",
									Status, TotalBytesCopied));

			return UnlockAndMaybeComplete
				( FCB, Status, Irp, TotalBytesCopied );
		}
    }

    if( SendReq->AfdFlags & AFD_IMMEDIATE ) {
		AFD_DbgPrint(MID_TRACE,("Nonblocking\n"));
		UnlockBuffers( SendReq->BufferArray, SendReq->BufferCount, FALSE );
		return UnlockAndMaybeComplete
			( FCB, STATUS_CANT_WAIT, Irp, 0 );
    } else {
		AFD_DbgPrint(MID_TRACE,("Queuing request\n"));
		return LeaveIrpUntilLater( FCB, Irp, FUNCTION_SEND );
    }
}

NTSTATUS NTAPI
AfdPacketSocketWriteData(PDEVICE_OBJECT DeviceObject, PIRP Irp,
						 PIO_STACK_LOCATION IrpSp) {
    NTSTATUS Status = STATUS_SUCCESS;
    PTDI_CONNECTION_INFORMATION TargetAddress;
    PFILE_OBJECT FileObject = IrpSp->FileObject;
    PAFD_FCB FCB = FileObject->FsContext;
    PAFD_SEND_INFO_UDP SendReq;
	ULONG Information;

    AFD_DbgPrint(MID_TRACE,("Called on %x\n", FCB));

    if( !SocketAcquireStateLock( FCB ) ) return LostSocket( Irp );

    /* Check that the socket is bound */
    if( FCB->State != SOCKET_STATE_BOUND )
		return UnlockAndMaybeComplete
			( FCB, STATUS_INVALID_PARAMETER, Irp, 0 );
    if( !(SendReq = LockRequest( Irp, IrpSp )) )
		return UnlockAndMaybeComplete
			( FCB, STATUS_NO_MEMORY, Irp, 0 );

    SendReq->BufferArray = LockBuffers( SendReq->BufferArray,
                                        SendReq->BufferCount,
                                        NULL, NULL,
                                        FALSE, FALSE );

    if( !SendReq->BufferArray )
		return UnlockAndMaybeComplete( FCB, STATUS_ACCESS_VIOLATION,
                                       Irp, 0 );

    AFD_DbgPrint
		(MID_TRACE,("RemoteAddress #%d Type %d\n",
					((PTRANSPORT_ADDRESS)SendReq->TdiConnection.RemoteAddress)->
					TAAddressCount,
					((PTRANSPORT_ADDRESS)SendReq->TdiConnection.RemoteAddress)->
					Address[0].AddressType));

    Status = TdiBuildConnectionInfo( &TargetAddress,
							((PTRANSPORT_ADDRESS)SendReq->TdiConnection.RemoteAddress) );

    /* Check the size of the Address given ... */

    if( NT_SUCCESS(Status) ) {
		FCB->PollState &= ~AFD_EVENT_SEND;

		Status = TdiSendDatagram
			( &FCB->SendIrp.InFlightRequest,
			  FCB->AddressFile.Object,
			  SendReq->BufferArray[0].buf,
			  SendReq->BufferArray[0].len,
			  TargetAddress,
			  &FCB->SendIrp.Iosb,
			  PacketSocketSendComplete,
			  FCB );

		ExFreePool( TargetAddress );
    }

    if( Status == STATUS_PENDING ) Status = STATUS_SUCCESS;

    AFD_DbgPrint(MID_TRACE,("Dismissing request: %x\n", Status));

	/* Even if we were pended, we're done with the user buffer at this
	 * point. */
	Information = SendReq->BufferArray[0].len;
	UnlockBuffers(SendReq->BufferArray, SendReq->BufferCount, FALSE);
    return UnlockAndMaybeComplete( FCB, Status, Irp, Information );
}

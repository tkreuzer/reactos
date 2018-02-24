
static
NSTATUS
NpfsReferenceFcbByPipeName(
    PNPFS_VCB Vcb,
    PUNICODE_STRING PipeName,
    PNAMED_PIPE_CREATE_PARAMETERS CreateParams,
    PNPFS_FCB *FcbPointer)
{
    PLIST_ENTRY ListEntry;
    PNPFS_FCB Fcb;

    NpfsAcquireMutex(&Vcb->PipeListLock);

    /* Loop all FCBs in the list */
    for (ListEntry = Vcb->PipeListHead.Flink;
         ListEntry != &Vcb->PipeListHead;
         ListEntry = ListEntry->Flink)
    {
        Fcb = CONTAINING_RECORD(ListEntry, NPFS_FCB, PipeListEntry);

        /* Compare the names */
        if (RtlCompareUnicodeString(PipeName, &Fcb->PipeName, TRUE) == 0)
        {
            /* Found it, break out of the loop */
            DPRINT("Found pipe '%wZ'\n", PipeName);
            break;
        }
    }

    /* Check if we had success */
    if (ListEntry == &Vcb->PipeListHead)
    {
        DPRINT("Pipe '%wZ' not found\n", PipeName);
        NpfsReleaseMutex(&Vcb->PipeListLock);
        return STATUS_OBJECT_NAME_NOT_FOUND;
    }

    /* Check if this is a pipe creation */
    if (CreateParams != NULL)
    {
        /* Check if there are instances left. */
        if (Fcb->CurrentInstances >= Fcb->MaximumInstances)
        {
            DPRINT("Out of instances.\n");
            return STATUS_INSTANCE_NOT_AVAILABLE;
        }

        /* Check if the create parameter match what we found */
        if (Fcb->MaximumInstances != CreateParams->MaximumInstances ||
            Fcb->TimeOut.QuadPart != CreateParams->DefaultTimeout.QuadPart ||
            Fcb->PipeType != CreateParams->NamedPipeType)
        {
            DPRINT("Asked for invalid pipe mode.\n");
            return STATUS_ACCESS_DENIED;
        }

        /* Increase number of instances */
        Fcb->CurrentInstances++;
    }



    NpfsReleaseMutex(&Vcb->PipeListLock);

    *FcbPointer = Fcb;
    return STATUS_SUCCESS;
}


static
PNPFS_CCB
NpfsAllocateCcb(CCB_TYPE Type, PNPFS_FCB Fcb)
{
    PNPFS_CCB Ccb;

    Ccb = ExAllocatePoolWithTag(NonPagedPool, sizeof(NPFS_CCB), TAG_NPFS_CCB);
    if (!Ccb)
    {
        return NULL;
    }

    RtlZeroMemory(Ccb, sizeof(NPFS_CCB));

    Ccb->RefCount = 1;
    Ccb->Type = Type;
    Ccb->Fcb = Fcb;
    Ccb->OtherSide = NULL;

    return Ccb;
}

static
NTSTATUS
NpfsOpenFileSystem(
    PNPFS_VCB Vcb,
    PFILE_OBJECT FileObject)
{
    PNPFS_CCB Ccb;

    DPRINT("NpfsOpenFileSystem()\n");

    /* Allocate a new CCB */
    Ccb = NpfsAllocateCcb(CCB_DEVICE, Fcb);
    if (Ccb == NULL)
    {
        return STATUS_NO_MEMORY;
    }

    FileObject->FsContext = Vcb->DeviceFcb;
    FileObject->FsContext2 = Ccb;

    return STATUS_SUCCESS;
}

static
NTSTATUS
NpfsOpenRootDirectory
    PNPFS_VCB Vcb,
    PFILE_OBJECT FileObject)
{
    PNPFS_CCB Ccb;

    DPRINT("NpfsOpenRootDirectory()\n");

    /* Allocate a new CCB */
    Ccb = NpfsAllocateCcb(CCB_DIRECTORY, Fcb);
    if (Ccb == NULL)
    {
        return STATUS_NO_MEMORY;
    }

    FileObject->FsContext = Vcb->RootFcb;
    FileObject->FsContext2 = Ccb;

    return STATUS_SUCCESS;
}

static
NTSTATUS
NpfsOpenPipe(
    PNPFS_VCB Vcb,
    PFILE_OBJECT FileObject)
{
    PNPFS_FCB Fcb;

    /* Find the pipe we're trying to open. */
    Status = NpfsReferenceFcbByPipeName(Vcb, &FileObject->FileName, NULL, &Fcb);
    if (NT_SUCCESS(Status))
    {
        /* Not found, bail out with error. */
        return Status;
    }

    /* Allocate the client CCB. */
    ClientCcb = NpfsAllocateCcb(CCB_PIPE, Fcb);
    if (ClientCcb == NULL)
    {
        NpfsDereferenceFcb(Fcb);
        return STATUS_NO_MEMORY;
    }

    /* Initialize the CCB */
    InitializeListHead(&ClientCcb->ReadRequestListHead);
    ClientCcb->Thread = Irp->Tail.Overlay.Thread;
    ClientCcb->PipeEnd = FILE_PIPE_CLIENT_END;
#ifndef USING_PROPER_NPFS_WAIT_SEMANTICS
    ClientCcb->PipeState = SpecialAccess ? 0 : FILE_PIPE_DISCONNECTED_STATE;
#else
    ClientCcb->PipeState = FILE_PIPE_DISCONNECTED_STATE;
#endif



}

static
ULONG
NpfsGetFileObjectType(
    PFILE_OBJECT FileObject)
{
    PUNICODE_STRING FileName = &FileObject->FileName;
    PFILE_OBJECT RelatedFileObject = FileObject->RelatedFileObject;

    if ((FileName->Length == 2) && (FileName->Buffer[0] == L'\\'))
    {
        if (!RelatedFileObject) return TYPE_ROOTDIRECTORY;
    }


    if (FileName->Length == 0)
    {
        if (!RelatedFileObject) return TYPE_FILESYSTEM;

        RelatedCcb = (PNPFS_CCB)RelatedFileObject->FsContext2;

        if (RelatedCcb->Type == CCB_DEVICE) return TYPE_FILESYSTEM;
        if (RelatedCcb->Type == CCB_DIRECTORY) return TYPE_ROOTDIRECTORY;
    }

    return TYPE_PIPE;
}

NTSTATUS
NTAPI
NpfsCreate(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    PNPFS_VCB Vcb = (PNPFS_VCB)DeviceObject->DeviceExtension;
    NTSTATUS Status;

    IoStack = (PEXTENDED_IO_STACK_LOCATION)IoGetCurrentIrpStackLocation(Irp);
    FileObject = IoStack->FileObject;

    FileObjectType = NpfsGetFileObjectType(FileObject);

    switch (FileObjectType)
    {
        case TYPE_FILESYSTEM:
            /* Open the file system */
            Status = NpfsOpenFileSystem(Vcb, FileObject);
            break;

        case TYPE_ROOTDIRECTORY:
            /* Open the root directory */
            Status = NpfsOpenRootDirectory(Vcb, FileObject);
            break;

        default:
            /* Open a pipe */
            Status = NpfsOpenPipe(Vcb, Irp);
    }

    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = NT_SUCCESS(Status) ? FILE_OPENED : 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return Status;
}

NTSTATUS
NTAPI
NpfsCreateNamedPipe(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    PNPFS_VCB Vcb = (PNPFS_VCB)DeviceObject->DeviceExtension;
    PNAMED_PIPE_CREATE_PARAMETERS CreateParameters;
    NTSTATUS Status;
    ULONG ShareAccess;

    /* Get the access mode and verify it */
    ShareAccess = IoStack->Parameters.CreatePipe.ShareAccess;
    if (!(ShareAccess & (FILE_SHARE_READ|FILE_SHARE_WRITE)) ||
        (ShareAccess & ~(FILE_SHARE_READ|FILE_SHARE_WRITE)))
    {
        return STATUS_INVALID_PARAMETER;
    }

    CreateParameters = IoStack->Parameters.CreatePipe.Parameters;

    /* First search for existing Pipe with the same name. */
    Status = NpfsReferenceFcbByPipeName(Vcb,
                                        &FileObject->FileName,
                                        CreateParameters,
                                        &Fcb);
    if (NT_SUCCESS(Status))
    {
    }
}


NTSTATUS
NTAPI
NpfsCleanup(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    NTSTATUS Status = STATUS_SUCCESS;
    PIO_STACK_LOCATION IoStackLocation;

    if (Ccb == NULL)
    {
        DPRINT("Success!\n");
        goto Done;
    }

    if (Ccb->Type == CCB_DEVICE)
    {
        DPRINT("Cleanup the file system!\n");
        goto Done;
    }

    if (Ccb->Type == CCB_DIRECTORY)
    {
        DPRINT("Cleanup the root directory!\n");
        goto Done;
    }

    // There are no pending irps to cancel

    // cancel all queued irps

Done:
    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Status;
}



NTSTATUS
NTAPI
NpfsClose(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    PFILE_OBJECT FileObject;
    PNPFS_FCB Fcb;
    PNPFS_CCB Ccb;
    NTSTATUS Status = STATUS_SUCCESS;

    Fcb = FileObject->FsContext;
    Ccb = FileObject->FsContext2;

    if (Ccb == NULL)
    {
        /* Nothing to do */
        DPRINT("Success!\n");
        goto Done;
    }

    if (Ccb->Type == CCB_DEVICE)
    {
        DPRINT("Closing the file system!\n");

        FileObject->FsContext = NULL;
        NpfsDereferenceFcb(Fcb);

        FileObject->FsContext2 = NULL;
        NpfsDereferenceCcb(Ccb);

        goto Done;
    }



Done:
    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Status;
}


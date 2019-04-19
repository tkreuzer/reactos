

NTSTATUS
NTAPI
ObCreateObject(
    IN KPROCESSOR_MODE ObjectAttributesAccessMode OPTIONAL,
    IN POBJECT_TYPE ObjectType,
    IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
    IN KPROCESSOR_MODE AccessMode,
    IN OUT PVOID ParseContext OPTIONAL,
    IN ULONG ObjectSize,
    IN ULONG PagedPoolCharge OPTIONAL,
    IN ULONG NonPagedPoolCharge OPTIONAL,
    OUT PVOID *Object)
{
    OBJECT_ATTRIBUTES ObjectAttributesCopy;
    OBP_HEADER_OFFSET_INFO HeaderInfoOffsets;

    PVOID SecurityDescriptor = NULL;
    SECURITY_QUALITY_OF_SERVICE SecurityQoS;
    ULONG Attributes;
    PUNICODE_STRING ObjectName;

    __debugbreak();

    ULONG Tag;



    if (ObjectAttributesAccessMode != KernelMode)
    {
        _SEH2_TRY
        {
            /* Probe and copy the object attributes */
            ProbeForRead(ObjectAttributes, sizeof(OBJECT_ATTRIBUTES), 1);
            ObjectAttributesCopy = *ObjectAttributes;
            ObjectAttributes = &ObjectAttributesCopy;

            /* Check if SecurityQualityOfService is given */
            if (ObjectAttributes->SecurityQualityOfService)
            {
                /* Probe and copy SecurityQualityOfService */
                ProbeForRead(ObjectAttributes->SecurityQualityOfService,
                             sizeof(SECURITY_QUALITY_OF_SERVICE),
                             sizeof(ULONG));
                SecurityQoS = *ObjectAttributes->SecurityQualityOfService;
            }
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
        }
        _SEH2_END
    }

    if (ObjectAttributes->SecurityDescriptor)
    {
        Status = SeCaptureSecurityDescriptor(ObjectAttributes->SecurityDescriptor,
                                             ObjectAttributesAccessMode,
                                             ObjectType->TypeInfo.PooType,
                                             TRUE,
                                             &SecurityDescriptor);
    }

    /* Check if a name is given (check length > 0?) */
    if (ObjectAttributes->ObjectName)
    {
        InfoMask |= OBJECT_HEADER_NAME_INFO_MASK;

        /* Duplicate the name (pass pool type?) */
        Status = ObpDuplicateString(&ObjectName,
                                    ObjectAttributes->ObjectName,
                                    ObjectAttributesAccessMode);


        if (ObjectAttributes->RootDirectory)
        {
            Status = ObReferenceObjectByHandle(ObjectAttributes->RootDirectory,
                                               desireAccess,
                                               ObpDirectoryObjectType,
                                               AccessMode,
                                               &RootDirectory,
                                               NULL);

            Status = ObReferenceObjectByName(&ObjectName,
                                             Attributes,
                                             PassedAccessState  	OPTIONAL,
                                             DesiredAccess  	OPTIONAL,
                                             ObpDirectoryObjectType,
                                             KernelMode,
                                             ParseContext  	OPTIONAL,
                                             &ParentDirectory);

        }
        else
        {
            RootDirectory = ObpRootDirectoryObject;
        }
    }

    if (ObjectType->TypeInfo.MaintainTypeList)
        InfoMask |= OBJECT_HEADER_CREATOR_INFO_MASK;
    if (ObjectType->TypeInfo.MaintainHandleCount)
        InfoMask |= OBJECT_HEADER_HANDLE_INFO_MASK;
    if (PagedPoolCharge || NonPagedPoolCharge)
        InfoMask |= OBJECT_HEADER_QUOTA_INFO_MASK;


    /* Use default values, for values not passed */
    if (ObjectSize == 0)
        ObjectSize = ObjectType->TypeInfo.Length;
    if (PagedPoolCharge == 0)
        PagedPoolCharge = ObjectType->TypeInfo.DefaultPagedPoolCharge;
    if (NonPagedPoolCharge == 0)
        NonPagedPoolCharge = ObjectType->TypeInfo.DefaultNonPagedPoolCharge;


    ObpGetHeaderInfoOffsets(&HeaderInfoOffsets, InfoMask);

    Status = ObpAllocateObject(ObjectType,
                               ObjectSize,
                               &HeaderInfoOffsets,




    Status = ObpInsertInDirectory(ParentDirectory,


    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS
NTAPI
ObCreateObjectType(
    IN PUNICODE_STRING TypeName,
    IN POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    IN PVOID Reserved,
    OUT POBJECT_TYPE *ResultObjectType)
{
    POBJECT_TYPE ObjectType;
    PHEADER_NAME_INFO HeaderNameInfo;
    ULONG Key = 0;

    /* Allocate a type object */
    Status = ObpAllocateObject(ObpTypeObjectType,
                               sizeof(OBJECT_TYPE),
                               OBJECT_HEADER_CREATOR_INFO_MASK |
                                   OBJECT_HEADER_NAME_INFO_MASK,
                               TypeName,
                               (PVOID*)&ObjectType);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Get the header and name info */
    ObjectHeader = CONTAINING_RECORD(ObjectType, OBJECT_HEADER, Body);
    HeaderNameInfo = ObpGetHeaderNameInfo(ObjectHeader);

    /* Construct a key / pooltag from the type name */
    ((PCHAR)&Key)[0] = (CHAR)TypeName->Buffer[0];
    if (TypeName->Length > 2) ((PCHAR)&Key)[1] = (CHAR)Name->Buffer[1];
    if (TypeName->Length > 4) ((PCHAR)&Key)[2] = (CHAR)TypeName->Buffer[2];
    if (TypeName->Length > 6) ((PCHAR)&Key)[3] = (CHAR)TypeName->Buffer[3];

    /* Initialize the basic type fields */
    InitializeListHead(&ObjectType->TypeList);
    InitializeListHead(&ObjectType->CallbackList);
    ExInitializePushLock(&ObjectType->TypeLock);
    ObjectType->Key = Key;
    ObjectType->Name = HeaderNameInfo->Name;;
    ObjectType->Index = TypeIndex;
    ObjectType->DefaultObject = 0; // FIXME
    ObjectType->TotalNumberOfObjects = 0;
    ObjectType->HighWaterNumberOfObjects = 0;
    ObjectType->TotalNumberOfHandles = 0;
    ObjectType->HighWaterNumberOfHandles = 0;

    /* Copy the type initializer */
    ObjectType->TypeInfo = *ObjectTypeInitializer;

    // insert it into the Type object directory
    Status = ObpInsertDirectoryEntry(ObpObjectTypeDirectoryObject, ObjectType);
    if (!NT_SUCCESS(Status))
    {
        ObDereferenceObject(ObjectType);
    }


}


NTSTATUS
NTAPI
ObCreateObjectType(
    IN PUNICODE_STRING TypeName,
    IN POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    IN PVOID Reserved,
    OUT POBJECT_TYPE *ResultObjectType)
{
    POBJECT_TYPE ObjectType;
    POBJECT_HEADER ObjectHeader;
    POBJECT_HEADER_CREATOR_INFO CreatorInfo;
    POBJECT_HEADER_NAME_INFO NameInfo;
    PVOID Pointer;
    ULONG AllocSize;
    NTSTATUS Status;
    UCHAR TypeIndex;

    /* Calculate the full size we need for this object */
    AllocSize = sizeof(OBJECT_TYPE) +
                sizeof(OBJECT_HEADER) +
                sizeof(OBJECT_HEADER_CREATOR_INFO) +
                sizeof(OBJECT_HEADER_NAME_INFO);

    /* Now allocate the structure */
    Pointer = ExAllocatePoolWithTag(NonPagedPool, AllocSize, 'TjbO');
    if (!Pointer)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Get pointers to the structures */
    NameInfo = Pointer;
    CreatorInfo = (POBJECT_HEADER_CREATOR_INFO)(NameInfo + 1);
    ObjectHeader = (POBJECT_HEADER)(CreatorInfo + 1);
    ObjectType = (POBJECT_TYPE)(ObjectHeader + 1);

    /* Now create a name */
    Status = ObpDuplicateString(&NameInfo->Name, TypeName, KernelMode);
    if (!NT_SUCCESS(Status))
    {
        ExFreePool(Pointer);
        return Status;
    }

    /* We don't have any directories yet */
    NameInfo->Directory = NULL;
    NameInfo->ReferenceCount = 0;

    /* Get an object type index */
    TypeIndex = (UCHAR)InterlockedIncrement(&ObpLastObjectIndex);

    /* Initialize the object header */
    ExInitializePushLock(&ObjectHeader->Lock);
    ObjectHeader->PointerCount = 0;
    ObjectHeader->HandleCount = 0;
    ObjectHeader->ObjectCreateInfo = NULL;
    ObjectHeader->QuotaBlockCharged = NULL;
    ObjectHeader->SecurityDescriptor = NULL;
    ObjectHeader->TypeIndex = TypeIndex;
    ObjectHeader->TraceFlags = 0;
    ObjectHeader->Flags = OB_FLAG_PERMANENT |
                          OB_FLAG_KERNEL_MODE |
                          OB_FLAG_CREATE_INFO;
    ObjectHeader->InfoMask = OBJECT_HEADER_CREATOR_INFO_MASK  |
                             OBJECT_HEADER_NAME_INFO_MASK;

    /* Initialize the creator info */
    CreatorInfo->CreatorUniqueProcess = NULL;
    CreatorInfo->CreatorBackTraceIndex = 0;
    CreatorInfo->Reserved = 0;

    /* Initialize the basic type fields */
    InitializeListHead(&ObjectType->TypeList);
    InitializeListHead(&ObjectType->CallbackList);
    ExInitializePushLock(&ObjectType->TypeLock);
    ObjectType->Key = 'TjbO';
    ObjectType->Name = NameInfo->Name;
    ObjectType->Index = TypeIndex;
    ObjectType->DefaultObject = 0; // FIXME

    /* We have one object of this type: this object */
    ObjectType->TotalNumberOfObjects = 1;
    ObjectType->HighWaterNumberOfObjects = 1;
    ObjectType->TotalNumberOfHandles = 0;
    ObjectType->HighWaterNumberOfHandles = 0;

    /* Initialize the TypeInfo */
    ObjectType->TypeInfo = ObjectTypeInitializer;

    /* Return a pointer to the object type */
    *ResultObjectType = ObjectType;

    /* Insert the object into the type list */
    InsertTailList(&ObpTypeObjectType->TypeList, &CreatorInfo->TypeList);

    /* Set the global object type table entry */
    ObpObjectType[TypeIndex] = ObjectType;

// insert into the "\Types" directory

    /* Return success */
    return STATUS_SUCCESS;
}

/////////////////////////////////////////////////////////////
    OBJECT_ATTRIBUTES ObjectAttributes;

    __debugbreak();

    InitializeObjectAttributes(&ObjectAttributes,
                               TypeName,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = ObCreateObject(KernelMode,
                            ObpTypeObjectType,
                            &ObjectAttributes,
                            KernelMode,
                            NULL,
                            sizeof(OBJECT_TYPE),
                            0,
                            0,
                            ObjectType);
    if (!NT_SUCCESS(Status));
    {
        return Status;
    }


    return STATUS_NOT_IMPLEMENTED;
}


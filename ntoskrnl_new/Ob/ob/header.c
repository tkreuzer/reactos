
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
    UCHAR HeaderInfoMask = 0;
    ULONG FullObjectSize;
    BP_HEADER_OFFSET_INFO HeaderOffsetInfo;

    /* We start with this size */
    FullObjectSize = ObjectSize + sizeof(OBJECT_HEADER);


    /* Check if we have any quota information */
    if (PagedPoolCharge || NonPagedPoolCharge)
    {
        /* Set the bit for header quota information */
        HeaderInfoMask |= OBJECT_HEADER_QUOTA_INFO_MASK;
    }

    /* */
    ObpGetHeaderInfoOffsets(HeaderOffsetInfo, HeaderInfoMask);


    FullObjectSize += HeaderOffsetInfo.Size;

    /* Now allocate the object */
    ObjectHeader = ObpAllocateObject(ObjectType, ObjectSize, HeaderInfoSize);
    if (!ObjectHeader)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    if (ObjectAttributes)
    {
        // FIXME: ObjectAttributesAccessMode!
        ObjectHeader->SecurityDescriptor = ObjectAttributes->SecurityDescriptor;

        // Check for name
        if (ObjectAttributes->Name)
        {
            // Copy name to paged pool buffer
        }

        if (ObjectAttributes->RootDiretory)
        {
            // Do we need to support that?
            ASSERT(FALSE);
        }
    }

    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
ObCreateObjectType(
    IN PUNICODE_STRING TypeName,
    IN POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    IN PVOID Reserved,
    OUT POBJECT_TYPE *ObjectType)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    POBJECT_TYPE ObjectTypeObject;
    POBJECT_HEADER ObjectHeader;

    InitializeObjectAttributes(&ObjectAttributes,
                               TypeName,
                               Attributes,
                               ObpObjectTypesRootDirectory,
                               NULL);

    Status = ObCreateObject(KernelMode,
                            ObpObjectTypeObjectType,
                            &ObjectAttributes,
                            KernelMode,
                            NULL,
                            sizeof(OBJECT_TYPE),
                            0,
                            0,
                            (PVOID*)&ObjectTypeObject)
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Copy the initializer data */
    ObjectTypeObject->TypeInfo = *ObjectTypeInitializer;

    ObjectTypeObject->Index = (UCHAR)InterlockedIncrement(ObpNumberObjectTypes);

    ObjectTypeObject->TypeList;
    //ObjectTypeObject->Name; just copy or allocate new?
    ObjectTypeObject->DefaultObject;
    ObjectTypeObject->TotalNumberOfObjects = 0;
    ObjectTypeObject->TotalNumberOfHandles = 0;
    ObjectTypeObject->HighWaterNumberOfObjects = 0;
    ObjectTypeObject->HighWaterNumberOfHandles = 0;
    ExInitializePushLock(&ObjectTypeObject->TypeLock);
    ObjectTypeObject->Key = 'TjbO';
    InitializeListHead(&ObjectTypeObject->CallbackList);

    ObjectHeader = ((POBJECT_HEADER)ObjectTypeObject) - 1;
    ASSERT(ObjectHeader->InfoMask == 0x03);
    HeaderCreatorInfo = ((POBJECT_HEADER_CREATOR_INFO)ObjectTypeObject) - 1;
    HeaderNameInfo = ((POBJECT_HEADER_NAME_INFO)HeaderCreatorInfo) - 1;

    return STATUS_NOT_IMPLEMENTED;
}



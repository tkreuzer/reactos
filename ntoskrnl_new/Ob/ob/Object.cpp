

void*
OBJECT::operator new (
    _In_ size_t DefaultSize,
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T ObjectSize,
    _In_ ULONG PoolTag,
    _In_ UCHAR InfoMask)
{
    SIZE_T HeaderSize;
    PVOID Base, Object;

    /* Calculate the size of the headers */
    HeaderSize = ObjectHeaderInfoSize[InfoMask];
    HeaderSize += FIELD_OFFSET(OBJECT_HEADER, Body);

    /* Allocate the object */
    Base = ExAllocatePoolWithTag(PoolType, ObjectSize + HeaderSize, PoolTag);
    if (Base == NULL)
    {
        return NULL;
    }

    /* Return the pointer to the object body! */
    return reinterpret_cast<void*>(reinterpret_cast<PUCHAR>(Base) + HeaderSize);
}

void*
OBJECT::operator new (
    _In_ size_t DefaultSize,
    _In_ POBJECT_TYPE ObjectType)
{

}


OBJECT::OBJECT (
    VOID)
{
    ObjectHeader = CONTAINING_RECORD(*ResultObject, OBJECT_HEADER, Body);

    /* Initialize the object header */
    ExInitializePushLock(&ObjectHeader->Lock);
    ObjectHeader->PointerCount = 0;
    ObjectHeader->HandleCount = 0;
    ObjectHeader->TypeIndex = ObjectType->Index;
    ObjectHeader->TraceFlags = 0;
    ObjectHeader->Flags = 0;
    ObjectHeader->InfoMask = InfoMask;
    ObjectHeader->ObjectCreateInfo = NULL;
    ObjectHeader->SecurityDescriptor = NULL;

}

OBJECT::~OBJECT (
    VOID)
{
}

static const ULONG TAG_OBJTYPE = 'TjbO';



/*! \name OBJECT::AllocateObject
 *
 *  \brief Allocates an object including requested headers and initializes
 *      the headers.
 *
 *  \param [in] ObjectType
 *      Pointer to the object type for the new object.
 *
 *  \param [in] ObjectSize
 *      Size of the object body in bytes.
 *
 *  \param [in] InfoMask
 *      A mask that describes what headers are to use. The value can be a
 *      combination of the OBJECT_HEADER_*_INFO_MASK constants.
 *
 *  \param [in] ObjectName
 *      Pointer to a unicode string that contains the name for the new object.
 *      Only relevant when OBJECT_HEADER_NAME_INFO_MASK is set in InfoMask.
 *
 *  \param [in] NameProbeMode
 *      Specifies the mode for probing / checking access to the name parameter.
 *      Can be either KernelMode or UserMode. The latter indicates that both
 *      The UNICODE_STRING structure, as well as the Buffer are user mode data.
 *
 *  \param [out] ResultObject
 *      Pointer to variable reveives the pointer to the object body.
 *
 *  \return
 *      NTSTATUS value, describing the status of the operation.
 *      In case of a failure, *ResultObject is undefined.
 */
NTSTATUS
NTAPI
OBJECT::AllocateObject (
    _In_ POOL_TYPE PoolType,
    _In_ ULONG ObjectSize,
    _In_ ULONG PoolTag,
    _In_ UCHAR InfoMask,
    _In_opt_ PUNICODE_STRING ObjectName,
    _In_opt_ KPROCESSOR_MODE NameProbeMode,
    _Out_ PVOID *ResultObject)
{
    POBJECT_HEADER ObjectHeader;
    UCHAR HeaderSize;
    PUCHAR Pointer;
    NTSTATUS Status;

    /* Calculate the size of the headers */
    HeaderSize =  ObpObjectHeaderInfoSize[InfoMask];
    HeaderSize += FIELD_OFFSET(OBJECT_HEADER, Body);

    /* Allocate the structure */
    Pointer = ExAllocatePoolWithTag(ObjectType->TypeInfo.PoolType,
                                    ObjectSize + HeaderSize,
                                    PoolTag);
    if (!Pointer)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Calculate the pointers for body and header */
    *ResultObject = (PVOID)(Pointer + HeaderSize);
    ObjectHeader = CONTAINING_RECORD(*ResultObject, OBJECT_HEADER, Body);

    /* Initialize the object header */
    ExInitializePushLock(&ObjectHeader->Lock);
    ObjectHeader->PointerCount = 0;
    ObjectHeader->HandleCount = 0;
    ObjectHeader->TypeIndex = ObjectType->Index;
    ObjectHeader->TraceFlags = 0;
    ObjectHeader->Flags = 0;
    ObjectHeader->InfoMask = InfoMask;
    ObjectHeader->ObjectCreateInfo = NULL;
    ObjectHeader->SecurityDescriptor = NULL;

    /* Check if there is a creator info */
    if (InfoMask & OBJECT_HEADER_CREATOR_INFO_MASK)
    {
        POBJECT_HEADER_CREATOR_INFO CreatorInfo;

        CreatorInfo = ObpGetHeaderCreatorInfo(ObjectHeader);
        CreatorInfo->CreatorUniqueProcess = 0;
        CreatorInfo->CreatorBackTraceIndex = 0;

        /* Check if a type list is to be maintained */
        if (ObjectType->TypeInfo.MaintainTypeList)
        {
            /* Insert the header into the object type's list */
            ExAcquirePushLockExclusive(&ObjectType->TypeLock);
            InsertTailList(&ObjectType->TypeList, &CreatorInfo->TypeList);
            ExReleasePushLockExclusive(&ObjectType->TypeLock);
        }
    }

    /* Check if there is a name info */
    if (InfoMask & OBJECT_HEADER_NAME_INFO_MASK)
    {
        POBJECT_HEADER_NAME_INFO NameInfo;

        NameInfo = ObpGetHeaderNameInfo(ObjectHeader);
        NameInfo->Directory = NULL;
        NameInfo->ReferenceCount = 0;

        /* Make a copy of the object name */
        Status = ObpDuplicateString(&NameInfo->Name, ObjectName, NameProbeMode);
        if (!NT_SUCCESS(Status))
        {
            /* Free the allocation and return the failure status */
            ExFreePool(Pointer);
            *ResultObject = NULL;
            return Status;
        }
    }

    /* Check if there is a process info */
    if (InfoMask & OBJECT_HEADER_PROCESS_INFO_MASK)
    {
        __debugbreak();
    }

    /* Check if there is a quota info */
    if (InfoMask & OBJECT_HEADER_QUOTA_INFO_MASK)
    {
        __debugbreak();
    }

    /* Check if there is a handle info */
    if (InfoMask & OBJECT_HEADER_HANDLE_INFO_MASK)
    {
        __debugbreak();
    }

    /* All done, return success */
    return STATUS_SUCCESS;
}

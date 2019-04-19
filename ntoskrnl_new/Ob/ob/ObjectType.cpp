

OBJECT_TYPE::InitializeClass (
    VOID)
{
    UCHAR InfoMask;

    ObjectType = new(NonPagedPool, TAG_OBJTYPE, InfoMask) OBJECT_TYPE;


}

void*
OBJECT_TYPE::operator new (
    _In_ size_t Size,
    )
{
    POBJECT Object;
    ULONG InfoMask;

    InfoMask = OBJECT_HEADER_CREATOR_INFO_MASK | OBJECT_HEADER_NAME_INFO_MASK;
    Object = new(NonPagedPool, Size, 'TjbO', InfoMask) OBJECT;

    return static_cast<void*>(Object);
}

OBJECT_TYPE::OBJECT_TYPE (
    _In_ PUNICODE_STRING TypeName,
    _In_ POBJECT_TYPE_INITIALIZER ObjectTypeInitializer)
{
    ULONG TypeIndex;
    ULONG Key;

    /* First get a type index */
    TypeIndex = InterlockedIncrement(&g_NextObjectTypeIndex);
    ASSERT(TypeIndex < MAX_OBJECT_TYPES);

    /* Get the name info */
    HeaderNameInfo = OBJECT::GetHeaderNameInfo();

    /* Construct a key / pooltag from the type name */
    ((PCHAR)&Key)[0] = (CHAR)TypeName->Buffer[0];
    if (TypeName->Length > 2) ((PCHAR)&Key)[1] = (CHAR)TypeName->Buffer[1];
    if (TypeName->Length > 4) ((PCHAR)&Key)[2] = (CHAR)TypeName->Buffer[2];
    if (TypeName->Length > 6) ((PCHAR)&Key)[3] = (CHAR)TypeName->Buffer[3];

    /* Initialize the basic type fields */
    InitializeListHead(&this->TypeList);
    InitializeListHead(&this->CallbackList);
    ExInitializePushLock(&this->TypeLock);
    this->Key = Key;
    this->Name = HeaderNameInfo->Name;
    this->Index = (UCHAR)TypeIndex;
    this->DefaultObject = 0; // FIXME
    this->TotalNumberOfObjects = 0;
    this->HighWaterNumberOfObjects = 0;
    this->TotalNumberOfHandles = 0;
    this->HighWaterNumberOfHandles = 0;

    /* Copy the type initializer */
    this->TypeInfo = *ObjectTypeInitializer;
}

extern "C"
NTSTATUS
NTAPI
ObCreateObjectType(
    _In_ PUNICODE_STRING TypeName,
    _In_ POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    _Reserved_ PVOID Reserved,
    _Out_ POBJECT_TYPE *ResultObjectType)
{
}

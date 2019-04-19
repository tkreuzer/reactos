
#include "Obp.hpp"

#include "Rtl/Rtl.hpp"
#include "FastRef.hpp"

namespace Ob {

extern "C" {

POBJECT_TYPE ObpDirectoryObjectType;
POBJECT_DIRECTORY ObpRootDirectoryObject;
POBJECT_DIRECTORY ObpTypeDirectoryObject;

};

UCHAR OBJECT_DIRECTORY::DirectoryObjectTypeIndex;

/*!
    \brief String hash based on FNV hash

    \see http://isthe.com/chongo/tech/comp/fnv/
 */
ULONG
CalculateStringHash (
    _In_ PUNICODE_STRING String)
{
    ULONG i, Hash;

    Hash = 2166136261;

    for (i = 0; i < String->Length / sizeof(WCHAR); i++)
    {
        Hash ^= String->Buffer[i];
        Hash *= 16777619;
    }

    return Hash;
}

DIRECTORY_ENTRY::DIRECTORY_ENTRY (
    _In_ POBJECT Object)
{
    POBJECT_HEADER_NAME_INFO NameInfo;

    /* Initialize the new entry */
    Object->AddRef();
    _Object = Object;
    _ChainLink = nullptr;

    /* Get the name header and make sure the object is not inserted */
    NameInfo = Object->GetNameInfo();
    NT_ASSERT(NameInfo != NULL);
    NT_ASSERT(NameInfo->Directory == NULL);

    /* Calculate the hash value for the name */
    _HashValue = CalculateStringHash(&NameInfo->Name);
}

DIRECTORY_ENTRY::~DIRECTORY_ENTRY (
    VOID)
{
    NT_ASSERT(_Object != nullptr);
    _Object->Release();
}

VOID
OBJECT_DIRECTORY::InitializeClass (
    VOID)
{
    static const UNICODE_STRING DirTypeName = RTL_CONSTANT_STRING(L"Directory");
    static const UNICODE_STRING RootDirName = RTL_CONSTANT_STRING(L"");
    static const UNICODE_STRING TypeDirName = RTL_CONSTANT_STRING(L"Types");
    OBJECT_TYPE_INITIALIZER TypeInitializer;
    ULONG PoolCharge;
    NTSTATUS Status;

    /* Calculate the full size for the directory object */
    PoolCharge = sizeof(OBJECT_DIRECTORY) +
                 sizeof(OBJECT_HEADER) +
                 sizeof(OBJECT_HEADER_CREATOR_INFO) +
                 sizeof(OBJECT_HEADER_NAME_INFO);

    /* Setup the type initializer */
    RtlZeroMemory(&TypeInitializer, sizeof(TypeInitializer));
    TypeInitializer.Length = sizeof(OBJECT_TYPE_INITIALIZER);
    TypeInitializer.CaseInsensitive = 1;
    TypeInitializer.UseDefaultObject = 1;
    TypeInitializer.SecurityRequired = 1;
    TypeInitializer.InvalidAttributes = 0x100;
    TypeInitializer.GenericMapping.GenericRead =
        READ_CONTROL | DIRECTORY_TRAVERSE | DIRECTORY_QUERY;
    TypeInitializer.GenericMapping.GenericWrite =
        READ_CONTROL | DIRECTORY_CREATE_SUBDIRECTORY | DIRECTORY_CREATE_OBJECT;
    TypeInitializer.GenericMapping.GenericExecute =
        READ_CONTROL | DIRECTORY_TRAVERSE | DIRECTORY_QUERY;
    TypeInitializer.GenericMapping.GenericAll = DIRECTORY_ALL_ACCESS;
    TypeInitializer.ValidAccessMask = DIRECTORY_ALL_ACCESS;
    TypeInitializer.PoolType = PagedPool;
    TypeInitializer.DefaultPagedPoolCharge = PoolCharge;//0x58;
    TypeInitializer.DefaultNonPagedPoolCharge = 0x150;
    TypeInitializer.DumpProcedure = NULL;
    TypeInitializer.OpenProcedure = NULL;
    TypeInitializer.CloseProcedure = CloseProcedure;
    TypeInitializer.DeleteProcedure = NULL;
    TypeInitializer.ParseProcedure = NULL;
    TypeInitializer.SecurityProcedure = SeDefaultObjectMethodEx;
    TypeInitializer.QueryNameProcedure = NULL;
    TypeInitializer.OkayToCloseProcedure = NULL;

    /* Create the directory object type */
    ObpDirectoryObjectType = new OBJECT_TYPE(&DirTypeName, &TypeInitializer);
    if (ObpDirectoryObjectType == NULL)
    {
        NT_ASSERT(FALSE);
    }

    /* Create the root directory */
    ObpRootDirectoryObject = new OBJECT_DIRECTORY(&RootDirName);
    if (ObpRootDirectoryObject == NULL)
    {
        NT_ASSERT(FALSE);
    }

    /* Create the '\Types' directory */
    ObpTypeDirectoryObject = new OBJECT_DIRECTORY(&TypeDirName);
    if (ObpTypeDirectoryObject == NULL)
    {
        NT_ASSERT(FALSE);
    }

    /* Insert the Types directory into the root directory */
    Status = ObpRootDirectoryObject->InsertObject(ObpTypeDirectoryObject);
    if (!NT_SUCCESS(Status))
    {
        NT_ASSERT(FALSE);
    }

    /* Insert the type object type into the object type directory */
    Status = ObpTypeDirectoryObject->InsertObject(ObpTypeObjectType);
    if (!NT_SUCCESS(Status))
    {
        NT_ASSERT(FALSE);
    }

    /* Insert the directory object type into the object type directory */
    Status = ObpTypeDirectoryObject->InsertObject(ObpDirectoryObjectType);
    if (!NT_SUCCESS(Status))
    {
        NT_ASSERT(FALSE);
    }

}

void*
OBJECT_DIRECTORY::operator new (
    _In_ size_t Size) throw()
{
    NTSTATUS Status;
    PVOID Object;

    Status = ObpDirectoryObjectType->CreateObject(&Object,
                                                  Size,
                                                  NULL,
                                                  0, // PagedPoolCharge,
                                                  0); // NonPagedPoolCharge
    if (!NT_SUCCESS(Status))
    {
        return NULL;
    }

    return Object;
}

OBJECT_DIRECTORY::OBJECT_DIRECTORY (
    _In_ PCUNICODE_STRING Name)
    : OBJECT(Name)
{
    /* Copy the type name to the object */
    GetNameInfo()->Name = *Name; /// \todo Think about using an OBJECT constructor

    RtlZeroMemory(_HashBuckets, sizeof(_HashBuckets));
    ExInitializePushLock(&_Lock);
    _DeviceMap = NULL;
    _SessionId = MmGetSessionId(PsGetCurrentProcess());
    _NamespaceEntry = NULL;
    _Flags = 0;
}

OBJECT_DIRECTORY::~OBJECT_DIRECTORY (
    VOID)
{
}

VOID
NTAPI
OBJECT_DIRECTORY::CloseProcedure (
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ ULONG_PTR ProcessHandleCount,
    _In_ ULONG_PTR SystemHandleCount)
{
    __debugbreak();
}

BOOLEAN
OBJECT_DIRECTORY::FindChainLink (
    _In_ PUNICODE_STRING ObjectName,
    _In_ ULONG HashValue,
    _Outptr_ PDIRECTORY_ENTRY** OutChainLink)
{
    PDIRECTORY_ENTRY CurrentEntry, *Bucket, *ChainLink;
    POBJECT_HEADER_NAME_INFO NameInfo;

    /* Get the hash bucket for the new entry */
    Bucket = &_HashBuckets[HashValue % NUMBER_HASH_BUCKETS];

    /* Loop all ChainLinks in this bucket */
    for (ChainLink = Bucket;
         *ChainLink != NULL;
         ChainLink = &(*ChainLink)->ChainLink)
    {
        /* Check if we are beyond the given hash value */
        CurrentEntry = *ChainLink;
        if (CurrentEntry->HashValue > HashValue)
        {
            /* Not found */
            break;
        }

        /* Check if the hash value matches */
        if (CurrentEntry->HashValue == HashValue)
        {
            /* Compare the full object name */
            NameInfo = CurrentEntry->Object->GetNameInfo();
            if (RtlEqualUnicodeString(&NameInfo->Name, ObjectName, TRUE))
            {
                /* Name matches, found the entry */
                *OutChainLink = ChainLink;
                return TRUE;
            }
        }
    }

    /* Not found */
    *OutChainLink = ChainLink;
    return FALSE;
}

/// FIXME: Do we even need this?
/*! \name OBJECT_DIRECTORY::LookupEntry
 *
 *  \brief Searches for a directory entry corresponding with the given object name.
 *
 *  \remarks
 *      The MRU optimization that is described in "Undocumented Windows 2000
 *      Secrets" is not used, since it would require an exclusive lock and is
 *      generally assumed to be uneffective.
 *
 *  \ref
 *      - http://i-web.i.u-tokyo.ac.jp/edu/training/ss/lecture/new-documents/Lectures/01-ObjectManager/ObjectManager.ppt
 *      - http://undocumented.rawol.com/sbs-w2k-7-windows-2000-object-management.pdf
 */
POBJECT_DIRECTORY_ENTRY
NTAPI
OBJECT_DIRECTORY::LookupEntry (
    _In_ PUNICODE_STRING Name)
{
    POBJECT_DIRECTORY_ENTRY Entry;
    ULONG HashValue;

    Entry = NULL;

    /* Calculate the hash value for the name */
    HashValue = CalculateStringHash(Name);

    ExAcquirePushLockShared(&_Lock);

    /* Find the chain link for the object name */
    if (FindChainLink(Name, HashValue, &ChainLink) != FALSE)
    {
        Entry = *ChainLink;
    }

    ExReleasePushLockShared(&_Lock);

    return Entry;
}


/*! \name OBJECT_DIRECTORY::InsertObject
 *
 *  \brief Inserts a named object into an object directory.
 *
 *  \param [in] Object
 *      The object that is to be inserted into the directory.
 *
 *  \remarks
 *      The caller is responsible for making sure that the object has a header
 *      name info and is not already inserted into a directory.
 */
NTSTATUS
OBJECT_DIRECTORY::InsertObject (
    _In_ POBJECT Object)
{
    PDIRECTORY_ENTRY NewEntry, *ChainLink;
    POBJECT_HEADER_NAME_INFO NameInfo;
    ULONG HashValue;

    /* Get the name header and make sure the object is not inserted */
    NameInfo = Object->GetNameInfo();
    if ((NameInfo == NULL) || (NameInfo->Directory != NULL))
    {
        NT_ASSERT(NameInfo->Directory == NULL);
        return STATUS_UNSUCCESSFUL;
    }

    /* Allocate a directory entry */
    NewEntry = new DIRECTORY_ENTRY(Object);
    if (NewEntry == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Lock the directory */
    ExAcquirePushLockExclusive(&_Lock);

    /* Check for conflicting name and search for a location to insert */
    if (FindChainLink(&NameInfo->Name, NewEntry->_HashValue, &ChainLink) != FALSE)
    {
        /* Name conflict, fail */
        ExReleasePushLockExclusive(&_Lock);
        delete NewEntry;
        return STATUS_DUPLICATE_NAME;
    }

    /* Set this as the directory for the object */
    NameInfo->Directory = this;

    /* Insert the new entry */
    NewEntry->ChainLink = *ChainLink;
    *ChainLink = NewEntry;

    /* Release the directory lock */
    ExReleasePushLockExclusive(&_Lock);

    return STATUS_SUCCESS;
}

NTSTATUS
OBJECT_DIRECTORY::RemoveObject (
    _In_ POBJECT Object)
{
    PDIRECTORY_ENTRY CurrentEntry, *Bucket, *ChainLink;
    POBJECT_HEADER_NAME_INFO NameInfo;
    ULONG HashValue;
    NTSTATUS Status;

    /* Get the name header and make sure the object is inserted */
    NameInfo = Object->GetNameInfo();
    if ((NameInfo == NULL) || (NameInfo->Directory == NULL))
    {
        NT_ASSERT(NameInfo->Directory != NULL);
        return STATUS_UNSUCCESSFUL;
    }

    /* Calculate the hash value for the name */
    HashValue = CalculateStringHash(&NameInfo->Name);

    /* Lock the directory */
    ExAcquirePushLockExclusive(&_Lock);

    /* Get the hash bucket for the new entry */
    Bucket = &_HashBuckets[HashValue % NUMBER_HASH_BUCKETS];

    /* Default to failure */
    Status = STATUS_UNSUCCESSFUL;

    /* Loop all ChainLinks in this bucket */
    for (ChainLink = Bucket;
         *ChainLink != NULL;
         ChainLink = &(*ChainLink)->ChainLink)
    {
        /* Get the directory entry and check if it's the one we want */
        CurrentEntry = *ChainLink;
        if (CurrentEntry->Object == Object)
        {
            /* Found the directory entry, remove it */
            *ChainLink = CurrentEntry->ChainLink;
            delete CurrentEntry;
            Status = STATUS_SUCCESS;
            break;
        }
    }

    /* Release the directory lock */
    ExReleasePushLockExclusive(&_Lock);

    return Status;
}

}; // namespace Ob

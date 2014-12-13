
#include "Obp.hpp"

#include "Rtl/Rtl.hpp"

extern "C" {

POBJECT_TYPE ObpRootDirectoryObject;

};

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

#if 0
NTSTATUS
OBJECT_DIRECTORY::InsertObject (
    POBJECT Object)
{
    PDIRECTORY_ENTRY NewEntry, *Bucket;
    POBJECT_HEADER_NAME_INFO NameInfo;
    ULONG HashValue;

    /* Get the name header and make sure the object is not inserted */
    NameInfo = Object->GetNameInfo();
    if (NameInfo->Directory != NULL)
    {
        NT_ASSERT(NameInfo->Directory == NULL);
        return STATUS_UNSUCCESSFUL;
    }

    /* Allocate a directory entry */
    NewEntry = new DIRECTORY_ENTRY;
    if (NewEntry == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    /* Set the parent directory for the object */
    NameInfo->Directory = this;

    /* Calculate the hash value for the name */
    HashValue = CalculateStringHash(&NameInfo->Name);

    /* Initialize the new entry */
    NewEntry->HashValue = HashValue;
    NewEntry->Object = Object;

    /* Get the hash bucket for the new entry */
    Bucket = &_HashBuckets[HashValue % NUMBER_HASH_BUCKETS];

    // FIXME: prevent from inserting an object with the same name twice

    /* Lock the directory and insert the new entry */
    ExAcquirePushLockExclusive(&_Lock);
    NewEntry->ChainLink = *Bucket;
    *Bucket = NewEntry;
    ExReleasePushLockExclusive(&_Lock);

    return STATUS_SUCCESS;
}
#endif


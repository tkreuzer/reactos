
#pragma once

#include <Ex/Ex.hpp>
#include "FastRef.hpp"

namespace Ob {

typedef class OBJECT_DIRECTORY *POBJECT_DIRECTORY;

class OBJECT_DIRECTORY : public OBJECT
{
private:

    typedef struct _DIRECTORY_ENTRY
    {
        struct _DIRECTORY_ENTRY* ChainLink;
        POBJECT Object;
        ULONG HashValue;

        /// FIXME: inherit from POOL_OBJECT / PAGED_POOL_OBJECT<Tag>
        inline
        void*
        operator new (
            _In_ size_t Size)
        {
            return ExAllocatePoolWithTag(PagedPool, Size, 'iDbO');
        }

        inline
        void
        operator delete (
            _In_ void* Object)
        {
            ExFreePoolWithTag(Object, 'iDbO');
        }
    } DIRECTORY_ENTRY, *PDIRECTORY_ENTRY;

    static const ULONG NUMBER_HASH_BUCKETS = 37;
    static UCHAR DirectoryObjectTypeIndex;

    PDIRECTORY_ENTRY _HashBuckets[NUMBER_HASH_BUCKETS];
    EX_PUSH_LOCK _Lock;
    union
    {
        struct _DEVICE_MAP* _DeviceMap;
        class OBJECT_DIRECTORY* _ShadowDirectory;
    };
    ULONG _SessionId;
    PVOID _NamespaceEntry;
    ULONG _Flags;

    FAST_REF _FastRef;

    static
    VOID
    NTAPI
    CloseProcedure (
        _In_opt_ PEPROCESS Process,
        _In_ PVOID Object,
        _In_ ULONG_PTR ProcessHandleCount,
        _In_ ULONG_PTR SystemHandleCount);

    BOOLEAN
    FindChainLink (
        _In_ PUNICODE_STRING ObjectName,
        _In_ ULONG HashValue,
        _Outptr_ PDIRECTORY_ENTRY** OutChainLink);

public:

    static
    VOID
    InitializeClass (
        VOID);

    void*
    operator new (
        _In_ size_t Size) throw();

    OBJECT_DIRECTORY (
        _In_ PCUNICODE_STRING Name);

    ~OBJECT_DIRECTORY (
        VOID);

    NTSTATUS
    InsertObject (
        _In_ POBJECT Object);

    NTSTATUS
    RemoveObject (
        _In_ POBJECT Object);

};

}; // namespace Ob

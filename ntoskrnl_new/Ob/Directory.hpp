
#pragma once

#include <Ex/Ex.hpp>
#include "FastRef.hpp"

namespace Ob {

typedef class OBJECT_DIRECTORY *POBJECT_DIRECTORY;

class OBJECT_DIRECTORY : public OBJECT
{
private:

    class DIRECTORY_ENTRY : public PAGED_POOL_OBJECT<'iDbO'>
    {
        struct _DIRECTORY_ENTRY* _ChainLink;
        POBJECT _Object;
        ULONG _HashValue;

        DIRECTORY_ENTRY (
            _In_ POBJECT Object);

        ~DIRECTORY_ENTRY (
            VOID);

        friend class OBJECT_DIRECTORY;
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

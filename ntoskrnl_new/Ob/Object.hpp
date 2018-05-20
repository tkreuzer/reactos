
#pragma once

#include <Ex/Ex.hpp>

typedef ULONG_PTR EX_PUSH_LOCK;

namespace Ob {

typedef class OBJECT *POBJECT;

class OBJECT
{
protected:

    enum INFO_INDEX
    {
        CREATOR_INFO = 0,
        NAME_INFO = 1,
        PROCESS_INFO = 2,
        QUOTA_INFO = 3,
        HANDLE_INFO = 4, // FIXME: check this value
        MAX_INFO = 4
    };

    enum INFO_MASK
    {
        CREATOR_INFO_MASK = 0x01,
        NAME_INFO_MASK = 0x02,
        PROCESS_INFO_MASK = 0x04,
        QUOTA_INFO_MASK = 0x08,
        HANDLE_INFO_MASK = 0x10, // FIXME: check this value
        MAX_INFO_MASK = 0x1F
    };

protected: /// FIXME: can we make these private?
    typedef struct _OBJECT_HEADER_AUDIT_INFO
    {
        PVOID SecurityDescriptor;
        ULONG64 Reserved;
    } OBJECT_HEADER_AUDIT_INFO, *POBJECT_HEADER_AUDIT_INFO;

    typedef struct _OBJECT_HEADER_CREATOR_INFO
    {
        LIST_ENTRY TypeList;
        PVOID CreatorUniqueProcess;
        USHORT CreatorBackTraceIndex;
        USHORT Reserved;
    } OBJECT_HEADER_CREATOR_INFO, *POBJECT_HEADER_CREATOR_INFO;

    typedef struct _OBJECT_HANDLE_COUNT_ENTRY
    {
        struct _EPROCESS* Process;
        struct
        {
            ULONG HandleCount : 24;
            ULONG LockCount : 8;
        };
    } OBJECT_HANDLE_COUNT_ENTRY, *POBJECT_HANDLE_COUNT_ENTRY;

    typedef struct _OBJECT_HANDLE_COUNT_DATABASE
    {
        ULONG CountEntries;
        OBJECT_HANDLE_COUNT_ENTRY HandleCountEntries[1];
    } OBJECT_HANDLE_COUNT_DATABASE, *POBJECT_HANDLE_COUNT_DATABASE;

    typedef struct _OBJECT_HEADER_HANDLE_INFO
    {
        union
        {
            POBJECT_HANDLE_COUNT_DATABASE HandleCountDataBase;
            OBJECT_HANDLE_COUNT_ENTRY SingleEntry;
        };
    } OBJECT_HEADER_HANDLE_INFO, *POBJECT_HEADER_HANDLE_INFO;

    typedef struct _OBJECT_HEADER_NAME_INFO
    {
        class OBJECT_DIRECTORY* Directory;
        UNICODE_STRING Name;
        LONG ReferenceCount;
    } OBJECT_HEADER_NAME_INFO, *POBJECT_HEADER_NAME_INFO;

    typedef struct _OBJECT_HEADER_PROCESS_INFO
    {
        struct _EPROCESS* ExclusiveProcess;
        ULONG64 Reserved;
    } OBJECT_HEADER_PROCESS_INFO, *POBJECT_HEADER_PROCESS_INFO;

    typedef struct _OBJECT_HEADER_QUOTA_INFO
    {
        ULONG PagedPoolCharge;
        ULONG NonPagedPoolCharge;
        ULONG SecurityDescriptorCharge;
        PVOID SecurityDescriptorQuotaBlock;
        ULONG64 Reserved;
    } OBJECT_HEADER_QUOTA_INFO, *POBJECT_HEADER_QUOTA_INFO;

    /* Make sure all info sizes together don't overflow an UCHAR */
    static_assert((sizeof(OBJECT_HEADER_CREATOR_INFO) +
                   sizeof(OBJECT_HEADER_NAME_INFO) +
                   sizeof(OBJECT_HEADER_PROCESS_INFO) +
                   sizeof(OBJECT_HEADER_QUOTA_INFO) +
                   sizeof(OBJECT_HEADER_AUDIT_INFO) +
                   sizeof(OBJECT_HEADER_HANDLE_INFO)) < 255,
                  "Info sizes are too big!");

    typedef struct _OBJECT_HEADER
    {
        LONG_PTR PointerCount;
        union
        {
            LONG_PTR HandleCount;
            PVOID NextToFree;
        };
        EX_PUSH_LOCK Lock;
        UCHAR TypeIndex;
        union
        {
            UCHAR TraceFlags;
            struct
            {
                UCHAR DbgRefTrace : 1;
                UCHAR DbgTracePermanent : 1;
            };
        };
        UCHAR InfoMask;
        union
        {
            UCHAR Flags;
            struct
            {
                UCHAR NewObject : 1;
                UCHAR KernelObject : 1;
                UCHAR KernelOnlyAccess : 1;
                UCHAR ExclusiveObject : 1;
                UCHAR PermanentObject : 1;
                UCHAR DefaultSecurityQuota : 1;
                UCHAR SingleHandleEntry : 1;
                UCHAR DeletedInline : 1;
            };
        };
    #ifdef _WIN64
        ULONG Spare;
    #endif
        union
        {
            struct _OBJECT_CREATE_INFORMATION* ObjectCreateInfo;
            PVOID QuotaBlockCharged;
        };
        PVOID SecurityDescriptor;
        QUAD Body;
    } OBJECT_HEADER, *POBJECT_HEADER;

private:

    // FIXME: WinDbg looks for ObpInfoMaskToOffset!
    static UCHAR HeaderInfoSize[MAX_INFO_MASK + 1];

protected:

    OBJECT (
        _In_ PCUNICODE_STRING ObjectName);

    ~OBJECT (
        VOID);


public:

    void
    operator delete (
        void *Object);

    static
    VOID
    InitializeClass (
        VOID);

    static
    PVOID
    Allocate (
        _In_ POOL_TYPE PoolType,
        _In_ SIZE_T ObjectSize,
        _In_ ULONG PoolTag,
        _In_ UCHAR TypeIndex,
        _In_ UCHAR InfoMask);

    inline
    POBJECT_HEADER
    GetObjectHeader (
        VOID)
    {
        /* Return the pointer to the object header */
        return CONTAINING_RECORD(this, OBJECT_HEADER, Body);
    }

    PVOID
    GetHeaderInfo (
        _In_ INFO_INDEX InfoIndex);

    inline
    POBJECT_HEADER_CREATOR_INFO
    GetCreatorInfo (
        VOID)
    {
        return reinterpret_cast<POBJECT_HEADER_CREATOR_INFO>(
            GetHeaderInfo(CREATOR_INFO));
    }

    inline
    POBJECT_HEADER_NAME_INFO
    GetNameInfo (
        VOID)
    {
        return reinterpret_cast<POBJECT_HEADER_NAME_INFO>(
            GetHeaderInfo(NAME_INFO));
    }

    inline
    POBJECT_HEADER_PROCESS_INFO
    GetProcessInfo (
        VOID)
    {
        return reinterpret_cast<POBJECT_HEADER_PROCESS_INFO>(
            GetHeaderInfo(PROCESS_INFO));
    }

    inline
    POBJECT_HEADER_QUOTA_INFO
    GetQuotaInfo (
        VOID)
    {
        return reinterpret_cast<POBJECT_HEADER_QUOTA_INFO>(
            GetHeaderInfo(QUOTA_INFO));
    }

    inline
    POBJECT_HEADER_HANDLE_INFO
    GetHandleInfo (
        VOID)
    {
        return reinterpret_cast<POBJECT_HEADER_HANDLE_INFO>(
            GetHeaderInfo(HANDLE_INFO));
    }

    inline
    VOID
    AddRef (
        _In_ LONG Increment)
    {
        NT_ASSERT(Increment > 0);
        POBJECT_HEADER ObjectHeader = GetObjectHeader();
        InterlockedExchangeAddLongPtr(&ObjectHeader->PointerCount, Increment);
    }

    inline
    VOID
    AddRef (
        VOID)
    {
        AddRef(1);
    }

    VOID
    Release (
        _In_ LONG Decrement)
    {
        __debugbreak();
    }

    inline
    VOID
    Release (
        VOID)
    {
        Release(1);
    }

    VOID
    InitializeStackObjectHeader (
        _In_ class OBJECT_TYPE *ObjectType,
        _In_ LONG_PTR PointerCount);

};


}; // namespace Ob


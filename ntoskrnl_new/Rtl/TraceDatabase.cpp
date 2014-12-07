
#include "Rtl.hpp"

extern "C" {

/// HACK!
typedef PVOID RTL_CRITICAL_SECTION;

// http://undoc.airesoft.co.uk/ntdll.dll/RtlTraceDatabaseCreate.php
typedef
ULONG
NTAPI
RTL_TRACE_HASH_FUNCTION (
    PVOID* ppFrames,
    ULONG numFrames);
typedef RTL_TRACE_HASH_FUNCTION *PRTL_TRACE_HASH_FUNCTION;

// http://terminus.rewolf.pl/terminus/structures/ntdll/_RTL_TRACE_DATABASE_x86.html
// http://terminus.rewolf.pl/terminus/structures/ntdll/_RTL_TRACE_DATABASE_x64.html
typedef struct _RTL_TRACE_DATABASE
{
    ULONG Magic;
    ULONG Flags;
    ULONG Tag;
    struct _RTL_TRACE_SEGMENT *SegmentList;
    ULONG_PTR MaximumSize;
    ULONG_PTR CurrentSize;
    PVOID Owner;
    RTL_CRITICAL_SECTION Lock;
    ULONG NoOfBuckets;
    struct _RTL_TRACE_BLOCK **Buckets;
    PRTL_TRACE_HASH_FUNCTION HashFunction;
    ULONG_PTR NoOfTraces;
    ULONG_PTR NoOfHits;
    ULONG HashCounter[16];
} RTL_TRACE_DATABASE, *PRTL_TRACE_DATABASE;

// http://terminus.rewolf.pl/terminus/structures/ntdll/_RTL_TRACE_BLOCK_combined.html
typedef struct _RTL_TRACE_BLOCK
{
    ULONG Magic;
    ULONG Count;
    ULONG Size;
    ULONG_PTR UserCount;
    ULONG_PTR UserSize;
    PVOID UserContext;
    struct _RTL_TRACE_BLOCK *Next;
    PVOID *Trace;
} RTL_TRACE_BLOCK, *PRTL_TRACE_BLOCK;

// http://undoc.airesoft.co.uk/ntdll.dll/RtlTraceDatabaseEnumerate.php
typedef struct _RTL_TRACE_ENUM
{
    PRTL_TRACE_DATABASE pDatabase;
    ULONG bucketIndex;
    PRTL_TRACE_BLOCK pStartingBlock;
} RTL_TRACE_ENUM, *PRTL_TRACE_ENUM;

// http://undoc.airesoft.co.uk/ntdll.dll/RtlTraceDatabaseCreate.php
// http://filelog.net/func/RtlTraceDatabaseCreate
// On success return NotEqual 0
PRTL_TRACE_DATABASE
NTAPI
RtlTraceDatabaseCreate (
    ULONG buckets,
    SIZE_T maximumSize,
    ULONG flags,
    ULONG tag,
    PRTL_TRACE_HASH_FUNCTION pfnHash)
{
    __debugbreak();
    return NULL;
}

// http://filelog.net/func/RtlTraceDatabaseDestroy
BOOLEAN
NTAPI
RtlTraceDatabaseDestroy (
    PRTL_TRACE_DATABASE pDatabase)
{
    __debugbreak();
    return FALSE;
}

// http://filelog.net/func/RtlTraceDatabaseValidate
BOOLEAN
NTAPI
RtlTraceDatabaseValidate (
    PRTL_TRACE_DATABASE pDatabase)
{
    __debugbreak();
    return FALSE;
}

// http://filelog.net/func/RtlTraceDatabaseLock
BOOLEAN
NTAPI
RtlTraceDatabaseLock (
    PRTL_TRACE_DATABASE pDatabase)
{
    __debugbreak();
    return FALSE;
}

// http://filelog.net/func/RtlTraceDatabaseUnlock
BOOLEAN
NTAPI
RtlTraceDatabaseUnlock (
    PRTL_TRACE_DATABASE pDatabase)
{
    __debugbreak();
    return FALSE;
}

// http://filelog.net/func/RtlTraceDatabaseAdd
BOOLEAN
NTAPI
RtlTraceDatabaseAdd (
    PRTL_TRACE_DATABASE pDatabase,
    ULONG numFrames,
    PVOID* ppFrames,
    PRTL_TRACE_BLOCK* ppBlock)
{
    __debugbreak();
    return FALSE;
}

// http://filelog.net/func/RtlTraceDatabaseFind
BOOLEAN
NTAPI
RtlTraceDatabaseFind (
    PRTL_TRACE_DATABASE pDatabase,
    ULONG numFrames,
    PVOID* ppFrames,
    PRTL_TRACE_BLOCK* ppBlock)
{
    __debugbreak();
    return FALSE;
}

// http://undoc.airesoft.co.uk/ntdll.dll/RtlTraceDatabaseEnumerate.php
// http://filelog.net/func/RtlTraceDatabaseEnumerate
BOOLEAN
NTAPI
RtlTraceDatabaseEnumerate (
    PRTL_TRACE_DATABASE pDatabase,
    PRTL_TRACE_ENUM pEnumData,
    PRTL_TRACE_BLOCK* ppBlock)
{
    __debugbreak();
    return FALSE;
}

} // extern "C"

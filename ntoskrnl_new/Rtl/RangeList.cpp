
#include "Rtl.hpp"

extern "C" {

// Windows symbols
typedef struct _RTL_RANGE_LIST
{
     LIST_ENTRY ListHead;
     ULONG Flags;
     ULONG Count;
     ULONG Stamp;
} RTL_RANGE_LIST, *PRTL_RANGE_LIST;

// Windows symbols
typedef struct _RTLP_RANGE_LIST_ENTRY
{
    ULONG64 Start;
    ULONG64 End;
    union
    {
        struct
        {
            PVOID UserData;
            PVOID Owner;
        } Allocated;
        struct
        {
            LIST_ENTRY ListHead;
        } Merged;
    };
    UCHAR Attributes;
    UCHAR PublicFlags;
    USHORT PrivateFlags;
    LIST_ENTRY ListEntry;
} RTLP_RANGE_LIST_ENTRY, *PRTLP_RANGE_LIST_ENTRY;

VOID
NTAPI
RtlInitializeRangeList (
    PRTL_RANGE_LIST RangeList)
{
    __debugbreak();
}

VOID
NTAPI
RtlFreeRangeList (
    PRTL_RANGE_LIST RangeList)
{
    __debugbreak();
}

VOID
NTAPI
RtlCopyRangeList (
    PRTL_RANGE_LIST RangeList1,
    PRTL_RANGE_LIST RangeList2)
{
    __debugbreak();
}

VOID
NTAPI
RtlMergeRangeLists (
    PRTL_RANGE_LIST RangeList1,
    PRTL_RANGE_LIST RangeList2,
    PRTL_RANGE_LIST RangeList3,
    ULONG P4)
{
    __debugbreak();
}

VOID
NTAPI
RtlInvertRangeList (
    PRTL_RANGE_LIST RangeList1,
    PRTL_RANGE_LIST RangeList2)
{
    __debugbreak();
}

VOID
NTAPI
RtlInvertRangeListEx (
    PRTL_RANGE_LIST RangeList1,
    PRTL_RANGE_LIST RangeList2,
    ULONG P3)
{
    __debugbreak();
}

VOID
NTAPI
RtlAddRange (
    PRTL_RANGE_LIST RangeList,
    ULONG P2,
    ULONG P3,
    ULONG P4,
    ULONG P5,
    ULONG P6,
    ULONG P7,
    ULONG P8,
    ULONG P9)
{
    __debugbreak();
}

VOID
NTAPI
RtlDeleteRange (
    PRTL_RANGE_LIST RangeList,
    ULONG P2,
    ULONG P3,
    ULONG P4,
    ULONG P5,
    ULONG P6)
{
    __debugbreak();
}

VOID
NTAPI
RtlGetFirstRange (
    PRTL_RANGE_LIST RangeList,
    ULONG P2,
    ULONG P3)
{
    __debugbreak();
}

VOID
NTAPI
RtlGetLastRange (
    PRTL_RANGE_LIST RangeList,
    ULONG P2,
    ULONG P3)
{
    __debugbreak();
}

VOID
NTAPI
RtlGetNextRange (
    PRTL_RANGE_LIST RangeList,
    ULONG P2,
    ULONG P3)
{
    __debugbreak();
}

VOID
NTAPI
RtlFindRange (
    PRTL_RANGE_LIST RangeList,
    ULONG P2,
    ULONG P3,
    ULONG P4,
    ULONG P5,
    ULONG P6,
    ULONG P7,
    ULONG P8,
    ULONG P9,
    ULONG P10,
    ULONG P11)
{
    __debugbreak();
}

VOID
NTAPI
RtlIsRangeAvailable (
    PRTL_RANGE_LIST RangeList,
    ULONG P2,
    ULONG P3,
    ULONG P4,
    ULONG P5,
    ULONG P6,
    ULONG P7,
    ULONG P8,
    ULONG P9,
    ULONG P10)
{
    __debugbreak();
}

VOID
NTAPI
RtlDeleteOwnersRanges (
    PRTL_RANGE_LIST RangeList,
    ULONG P2)
{
    __debugbreak();
}

} // extern "C"

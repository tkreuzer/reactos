
/*
A   Bs  Bu  A-B UC  XC  ZSCO    >u  >x
0   0   0   0   ==  ==  +---
0   1   1   15  <   <
0   7   7   9   <   <   -++-
0   -7  9   7   <   >   --+-        *
0   -8  8   8   <   >   --++        *
7   0   0   7   >   >   ----    *   *
7   7   7   0   ==  ==  +---
7   -7  9   14  <   >   -+++        *
15  0   0   15  >   >   -+--    *   *
15  7   7   8   >   >   -+--    *   *
14  7   7   7   >   >   -+-+    *   *
15  -7  9   6   >   >   ----    *   *

>u: if ((C == 0) && (Z == 0))
>x:

All:
    - Type: ? Bits
    - CacheAttribute : 2
    - ReferenceCount ? Bits

Valid (Private):
    - Flink (26 / 36 Bits)
    - Blink (26 / 36 Bits)
    - MappedVpn (26 / 36 Bits)
    - ProcessId

Valid (Shared):
    - Flink (26 / 36 Bits)
    - Blink (26 / 36 Bits)
    - ProtoPteAddress (29 /  Bits)
    - ShareCount (? Bits)

PageTable
    - ValidPteCount (10/9 bits) // if == 0, can be paged out
    - UsedPteCount  (10/9 bits) // if == 0, will be unmapped

Free
    - Flink (26 / 36 Bits)

Transition:
    - MappedVpn (26 / 36 Bits)
    - ProcessId (0 for
    - Pointer to Event

Bad:
    - Flink (26 / 36 Bits)
    - Blink (26 / 36 Bits)
    - BadReason


*/

union _PFNLISTHEAD
{
    struct
    {
#ifdef _WIN64
        ULONG64 FirstPfn : 36;
        ULONG64 Lock : 1;
        ULONG64 Sequence : 27;
#else
        ULONG FirstPfn;
        ULONG Lock : 1;
        ULONG Sequence : 31;
#endif
    };
    ULONG64 Long64;
};

/*

typedef enum _MEMORY_CACHING_TYPE { 
  MmNonCached               = 0,
  MmCached                  = 1,
  MmWriteCombined           = 2,
  MmHardwareCoherentCached  = 3,
  MmNonCachedUnordered      = 4,
  MmUSWCCached              = 5,
  MmMaximumCacheType        = 6
} MEMORY_CACHING_TYPE;

0 = 000 -> 0 = 00
1 = 001 -> 1 = 01
2 = 010 -> 2 = 10
3 = 011 -> 1
4 = 100 -> 0
5 = 101 -> 1
 
  pfnCacheing = (CachingType * 0x3) 

*/
inline
PFN_CACHE_ATTRIBUTE
CachingTypeToCacheAttribute (
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    static const UCHAR Table[MmMaximumCacheType] =
        {PfnNonCached, PfnCached, PfnWriteCombined, PfnCached, PfnNonCached, PfnCached};
    ULONG Index = static_cast<ULONG>(CachingType);
    return static_cast<PFN_CACHE_ATTRIBUTE>(Table[Index]);
}

inline
bool
IsCachingCompatible (
    _In_ PFN_CACHE_ATTRIBUTE CacheAttribute,
    _In_ MEMORY_CACHING_TYPE CachingType)
{
    return ((CacheAttribute == PfnNotMapped) ||
            (CacheAttribute == CachingTypeToCacheAttribute(CachingType)));
}

struct PFN_ENTRY_CORE
{
    PFN_STATE State : 4;
    PFN_CACHE_ATTRIBUTE CacheAttribute : 2;
    ULONG ReferenceCount : 27;
};


static_assert(sizeof(PFN_ENTRY_CORE) == sizeof(ULONG), "PFN_ENTRY_CORE too large");

struct PFN_ENTRY_FREE
{
    ULONG64 Flink : 36;
};

struct PFN_ENTRY_VALID
{
    ULONG ShareCount;
    ULONG64 Flink : 36;
    ULONG64 Blink : 36;
    PPTE PteAddress;
};

struct PFN_ENTRY_PAGETABLE
{
    ULONG UsedPteCount : 9;
    ULONG ValidPteCount : 9;
    ULONG64 Flink : 36;
    ULONG64 Blink : 36;
    PPTE PteAddress;
};

struct PFN_ENTRY_TRANSITION
{
    PKEVENT Event;
    PPTE PteAddress;
};

struct PFN_ENTRY : PFN_ENTRY_CORE
{
    union
    {
        PFN_ENTRY_VALID Valid;
        PFN_ENTRY_FREE Free;
        PFN_ENTRY_PAGETABLE PageTable;
    };
};

struct PFN_ENTRY
{
    struct
    {
        PFN_STATE State : 4;
        PFN_CACHE_ATTRIBUTE CacheAttribute : 2;
        ULONG ReferenceCount : 27;
    };

    union
    {
        struct /* For shared PFNs */
        {
            ULONG ShareCount;
        };
        struct /* For page-table PFNs */
        {
            ULONG UsedPteCount : 9;
            ULONG ValidPteCount : 9;
        };
        ULONG NumberOfContiguousPages;
    } u1;

    union
    {
        ULONG_PTR Flink;
        struct _KEVENT* Event;
    } u2;

    union
    {
        ULONG_PTR Blink;
    } u3;

    ULONG_PTR PteAddressAndLock;

};

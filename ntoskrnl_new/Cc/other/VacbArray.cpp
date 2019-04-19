
typedef struct _VACB
{
    PVOID BaseAddress;
    PSHARED_CACHE_MAP SharedCacheMap;
    union
    {
        LARGE_INTEGER FileOffset;
        USHORT ActiveCount;
        LIST_ENTRY Links;
    } Overlay;
    VACB_ARRAY_HEADER* ArrayHead;
} VACB, *PVACB;


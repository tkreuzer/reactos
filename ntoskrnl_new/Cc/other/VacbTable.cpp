
// VACB_MAPPING_GRANULARITY = 256k

typedef struct _VACB_ARRAY_HEADER
{
    ULONG VacbArrayIndex;
    ULONG MappingCount;
    ULONG HighestMappedIndex;
    ULONG Reserved;
} VACB_ARRAY_HEADER, *PVACB_ARRAY_HEADER;

typedef struct _VACB
{
    PVOID BaseAddress;
    class SHARED_CACHE_MAP* SharedCacheMap;
    union
    {
        LARGE_INTEGER FileOffset;
        USHORT ActiveCount;
        LIST_ENTRY Links;
    } Overlay;
    PVACB_ARRAY_HEADER ArrayHead;
} VACB, *PVACB;

/* This number is such, that a VACB_ARRAY is one page in size */
static const ULONG NUMBER_VACB_SLOTS = (PAGE_SIZE - sizeof(VACB_ARRAY_HEADER)) / sizeof(PVOID); /// nonono

class VACB_ARRAY
{
private:
    VACB_ARRAY_HEADER m_Header;
    union
    {
        PVACB m_VacbPointers[NUMBER_VACB_SLOTS];
        VACB_ARRAY* m_VacbArrayPointers[NUMBER_VACB_SLOTS];
    };

public:
    PVACB*
    GetVacbPointerForFileSlotIndex (
        ULONG FileSlotIndex);

};

static_assert(sizeof(VACB_ARRAY) == PAGE_SIZE);

NTSTATUS
VACB_ARRAY::CreateInstance (
    VOID)
{

}

PVACB*
VACB_ARRAY::GetVacbForFileSlotIndex (
    _In_ ULONG FileSizeInSlots,
    _In_ ULONG FileSlotIndex,
    _In_ BOOLEAN Allocate)
{
    PVACB* CurrentArray;
    ULONG Index, HighestBit, BitCount, NumberOfLevels;

    /* Sanity checks */
    NT_ASSERT(FileSizeInSlots > 0);
    NT_ASSERT(FileSlotIndex < FileSizeInSlots);

    /* Get the number of slot index bits required for the file */
    if (!BitScanReverse(&HighestBit, (FileSizeInSlots - 1)))
    {
        /* If we have only 1 slot, in theory we need 0 bits, use 1 instead */
        HighestBit = 0;
    }

    /* Calculate the number of levels required */
    NumberOfLevels = (HighestBit / 7) + 1;

    /* Make sure our math is right */
    NT_ASSERT(((FileSizeInSlots - 1) >> (NumberOfLevels * 7)) == 0);

    /* Start with our own array */
    CurrentArray = m_VacbPointerArray;

    /* Loop while we have levels */
    while (--NumberOfLevels)
    {
        /* Extract the index from the file location */
        Index = (FileSlotIndex >> (NumberOfLevels * 7)) & (NUMBER_VACB_SLOTS - 1);

        /* Check if the slot is empty */
        if (CurrentArray[Index] == NULL)
        {
            if (!Allocate)
            {
                return NULL;
            }

            /* Allocate a new array */
            CurrentArray[Index] = new(NonPagedPool, 'aVcC') VACB_ARRAY;
            if (CurrentArray[Index] == NULL)
            {
                return NULL;
            }
        }

        /* Get the next pointer */
        CurrentArray = reinterpret_cast<PVACB*>(CurrentArray[Index]);
    }

    /* Extract the last index from the file location */
    Index = FileSlotIndex & (NUMBER_VACB_SLOTS - 1);

    /* Return a pointer to the VACB pointer */
    return &CurrentArray[Index];
}

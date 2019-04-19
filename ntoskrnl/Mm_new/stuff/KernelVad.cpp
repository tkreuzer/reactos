

class KERNEL_VAD
{
};


class RESERVED_MAPPING_VAD : KERNEL_VAD
{
private:
    ULONG m_Tag;
    ULONG m_NumberOfMappedPages;
    RTL_BITMAP m_MappingBitmap;

public:

    NTSTATUS
    CreateInstance (
        _Out_ RESERVED_MAPPING_VAD** OutVad,
        _In_ ULONG NumberOfPages,
        _In_ ULONG Tag);


};

NTSTATUS
RESERVED_MAPPING_VAD::CreateInstance (
    _Out_ RESERVED_MAPPING_VAD** OutVad,
    _In_ ULONG NumberOfPages,
    _In_ ULONG Tag)
{
    SIZE_T Size;
    RESERVED_MAPPING_VAD* Vad;

    Size = sizeof(RESERVED_MAPPING_VAD) +
          ((NumberOfPages + 31) / 32) * sizeof(ULONG);

    /* Allocate the Vad from non-paged pool */
    Vad = new(NonPagedPool, Size, TAG_..) RESERVED_MAPPING_VAD;
    if (Vad == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    m_Tag = Tag;
    m_NumberOfMappedPages = 0;

    /* Initialize the bitmap. The buffer is after the object */
    RtlInitializeBitmap(&m_MappingBitmap, reinterpret_cast<PULONG>(Vad + 1));
    RtlClearAllBits(&m_MappingBitmap);

    return STATUS_SUCCESS;
}


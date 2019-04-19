
#define VACB_SLOT_SIZE 256 *


class VACB
{
private:
    ULONG m_MappedSlot;
    ULONG m_FileSlot;
    USHORT m_ArrayIndex;
    USHORT m_RefCount;

public:

    inline
    PVOID
    GetBaseAddress()
    {
        if (m_MappedSlot == 0)
            return NULL;
        return AddToPointer(MmSystemRangeStart,
                            static_cast<ULONG_PTR>(m_MappedSlot) * VACB_SLOT_SIZE);
    }

    inline
    P

}

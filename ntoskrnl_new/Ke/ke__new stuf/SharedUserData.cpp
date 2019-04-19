

VOID
SHARED_USER_DATA::Initialize (
    VOID)
{
    /* This structure must be page aligned */
    NT_ASSERT(POINTER_IS_ALIGNED(this, PAGE_SIZE));

    /* Zero out the full page */
    Rtl::ZeroMemory(this, PAGE_SIZE);

#ifdef _M_AMD64
    Reserved1 = MM_HIGHEST_USER_ADDRESS_WOW64;
    Reserved3 = MM_SYSTEM_RANGE_START_WOW64;
#else
    Reserved1 = (ULONG_PTR)MmHighestUserAddress;
    Reserved3 = (ULONG_PTR)MmSystemRangeStart;
#endif



}


typedef UINT32 POOL_TAG;

template<POOL_TYPE PoolType, POOL_TAG Tag>
class POOL_OBJECT
{
protected:

    inline
    void*
    operator new (
        _In_ size_t Size)
    {
        return ExAllocatePoolWithTag(PoolType, Size, Tag);
    }

    inline
    void
    operator delete (
        _In_ void* Object)
    {
        ExFreePoolWithTag(Object, Tag);
    }

}

template<POOL_TAG Tag>
class NON_PAGED_POOL_OBJECT : POOL_OBJECT<NonPagedPool, Tag>
{
}

template<POOL_TAG Tag>
class PAGED_POOL_OBJECT : POOL_OBJECT<PagedPool, Tag>
{
}

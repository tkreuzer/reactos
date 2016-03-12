
#pragma once

#include "Exp.hpp"

namespace Ex {

typedef union _PUSH_LOCK_VALUE
{
    struct
    {
        ULONG_PTR Locked : 1;
        ULONG_PTR Waiting : 1;
        ULONG_PTR Waking : 1;
        ULONG_PTR MultipleShared : 1;
        ULONG_PTR Shared : sizeof(ULONG_PTR) * 8 - 4;
    };
    volatile ULONG_PTR Long;
    volatile PVOID Ptr;
} PUSH_LOCK_VALUE, *PPUSH_LOCK_VALUE;

typedef class PUSH_LOCK *PPUSH_LOCK;

class PUSH_LOCK
{
private:

    PUSH_LOCK_VALUE _Value;

public:

    inline
    PUSH_LOCK (
        VOID) :
        _Value({{0}})
    {
    }

    _IRQL_requires_max_(APC_LEVEL)
    _Requires_lock_held_(_Global_critical_region_)
    VOID
    AcquireExclusive (
        VOID);

    _Must_inspect_result_
    _IRQL_requires_max_(DISPATCH_LEVEL)
    _Requires_lock_held_(_Global_critical_region_)
    _Post_satisfies_(return == 0 || return == 1)
    bool
    TryAcquireExclusive (
        VOID);

};

#if 0
/// experimente

#define ReadPointerNoFence(Ptr) (*(void**)(Ptr))

template<class LOCK_IMPL>
class LOCK : public LOCK_IMPL
{
public:

    inline
    bool
    TryAcquireExclusive (
        VOID)
    {
        return !InterlockedBitTestAndSetLongPtrAcquire(&_Value.Long, BIT_Lock);
    }

    inline
    bool
    TryAcquireShared (
        VOID)
    {
        LOCK_VALUE OldValue, NewValue;

        NewValue.Ptr = ReadPointerNoFence(&_Value.Ptr);

        do
        {
            if (NewValue.Long == BIT_Lock)
            {
                return FALSE;
            }

            OldValue = NewValue;

            NewValue.Locked = 1;
            NewValue.Shared++;
            NewValue.Ptr = InterlockedCompareExchangePointerAcquire(&_Value.Ptr,
                                                                    NewValue.Ptr,
                                                                    OldValue.Ptr);
        } while (NewValue.Ptr == OldValue.Ptr);

#if DBG
        OldValue.Ptr = ReadPointerNoFence(&_Value.Ptr);
        NT_ASSERT(OldValue.Locked);
        NT_ASSERT(OldValue.Waiting || OldValue.Shared > 0);
#endif

        return TRUE;
    }

    VOID
    AcquireExclusive (
        VOID)
    {
        _Value.Long = 1;

    }

};

class PUSHLOCK_IMPL
{
protected:

    typedef union _LOCK_VALUE
    {
        struct
        {
            ULONG_PTR Locked : 1;
            ULONG_PTR Waiting : 1;
            ULONG_PTR Waking : 1;
            ULONG_PTR MultipleShared : 1;
            ULONG_PTR Shared : sizeof(ULONG_PTR) * 8 - 4;
        };
        volatile LONG_PTR Long;
        volatile PVOID Ptr;
    } LOCK_VALUE, *PLOCK_VALUE;

    enum LOCK_BITS
    {
        BIT_Lock = 0
    };

    LOCK_VALUE _Value;

};

typedef class LOCK<PUSHLOCK_IMPL> PUSHLOCK;

void test()
{
    PUSHLOCK lock;

    lock.TryAcquireShared();
}
#endif // 0

}; // namespace Ex

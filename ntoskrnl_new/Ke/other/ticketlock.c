
#ifdef _WIN64
#pragma warning(disable:4820)
#pragma warning(disable:4711)
#endif
#include <ntifs.h>

#define KeGetCurrentPrcb() 0

void _mm_mfence(void);
#pragma intrinsic(_mm_mfence)

typedef struct
{
    PVOID ZeroAddress;
} KPRCB, *PKPRCB;

PVOID
NTAPI
KiGetNewZeroPage(VOID)
{
    return NULL;
}

#if 0

typedef union _KTICKET_LOCK
{
    LONG Long;
    struct
    {
        USHORT Turn;
        USHORT Ticket;
    };
} KTICKET_LOCK, *PKTICKET_LOCK;

VOID
NTAPI
KiSpinOnTicketLock(PKTICKET_LOCK Lock, USHORT MyTicket)
{
    PKPRCB Prcb = KeGetCurrentPrcb();
    register PULONG_PTR ZeroAddress = Prcb->ZeroAddress;

    /* Spin while the ticket is not ours */
    while (Lock->Turn != MyTicket)
    {
        /* Do something useful: Zero out 16/32 bytes of memory */
        ZeroAddress[0] = 0;
        ZeroAddress[1] = 0;
        ZeroAddress[2] = 0;
        ZeroAddress[3] = 0;

        /* Increase ZeroAddress and check for page margin */
        ZeroAddress += 4;
        if (((ULONG_PTR)ZeroAddress & (PAGE_SIZE - 1)) == 0)
        {
            /* Request a new page to be mapped */
            ZeroAddress = KiGetNewZeroPage();
        }

        /* Memory barrier to achieve that the Ticket is read again */
        KeMemoryBarrierWithoutFence();
    }

    Prcb->ZeroAddress = ZeroAddress;
}

VOID
FASTCALL
KeAcquireTicketLock(PKTICKET_LOCK Lock)
{
    USHORT MyTicket;

    /* Get a ticket */
#ifdef _HAS_XADD16
    MyTicket = InterlockedIncrement16(&Lock->Ticket);
#else
    MyTicket = InterlockedExchangeAdd(&Lock->Long, 0x10000) >> 16;
#endif

    /* Check if it's already our turn */
    if (Lock->Turn != MyTicket)
    {
        /* It's not, spin until it is. */
        KiSpinOnTicketLock(Lock, MyTicket);
    }
}

VOID
FASTCALL
KeReleaseTicketLock(PKTICKET_LOCK Lock)
{
    /* Make sure all previous memory accesses are completed
       and globally visible */
#if defined(_M_IX86) || defined(_M_AMD64)
    _mm_mfence();
#else
	KeMemoryBarrier();
#endif

    /* Set new value. Note: The assignment is an atomic operation,
       and since we are the only one modifying it, this is SMP safe. */
	Lock->Turn = (Lock->Turn + 1);
}

BOOLEAN
FASTCALL
KeTryAcquireTicketLock(PKTICKET_LOCK Lock)
{
	KTICKET_LOCK New, Current;

    /* Read the current lock value */
	Current = *Lock;
	KeMemoryBarrierWithoutFence();

    /* Check if its busy */
    if (Current.Ticket != Current.Turn) return FALSE;

    /* Try to get the next ticket */
    New = Current;
    New.Ticket++;

    /* Try an atomic exchange, save the value before the excahnge in New.Long */
    New.Long = InterlockedCompareExchange(&Lock->Long, New.Long, Current.Long);

    /* Check if the value before the exchange matches, what we had */
    return (New.Long == Current.Long);
}

BOOLEAN
FASTCALL
KeCheckTicketLock(PKTICKET_LOCK Lock)
{
	KTICKET_LOCK Current;

    /* Read the current lock value */
	Current = *Lock;
	KeMemoryBarrierWithoutFence();

    /* Return TRUE if the lock is free */
	return (Current.Ticket == Current.Next);
}

#else

// Geht nicht, denn shared - exclusive - shared blockt für immer

typedef union _KTICKET_LOCK
{
    LONG_PTR Long;
    struct
    {
#ifdef _WIN64
        USHORT Turn;
        USHORT Unused;
        USHORT ShareCount;
        USHORT Ticket;
#else
        UCHAR Turn;
        UCHAR Unused;
        UCHAR ShareCount;
        UCHAR Ticket;
#endif
    };
} KTICKET_LOCK, *PKTICKET_LOCK;

#define TL_TURN_BITS  10
#define TL_TURN_INC   0x00000001
#define TL_SHARE_INC  0x00000800
#define TL_TICKET_INC 0x00400000
#define TL_MAX_TURN   ((1 << TL_TURN_BITS) - 1)

PULONG_PTR
FORCEINLINE
KiDoZeroWork(register PULONG_PTR ZeroAddress)
{
    /* Do something useful: Zero out 16/32 bytes of memory */
    ZeroAddress[0] = 0;
    ZeroAddress[1] = 0;
    ZeroAddress[2] = 0;
    ZeroAddress[3] = 0;

    /* Increase ZeroAddress and check for page margin */
    ZeroAddress += 4;
    if (((ULONG_PTR)ZeroAddress & (PAGE_SIZE - 1)) == 0)
    {
        /* Request a new page to be mapped */
        ZeroAddress = KiGetNewZeroPage();
    }

    return ZeroAddress;
}

VOID
NTAPI
KiSpinOnTicketLockAcquireShared(PKTICKET_LOCK Lock, ULONG MyTicket)
{
    PKPRCB Prcb = KeGetCurrentPrcb();
    register PULONG_PTR ZeroAddress = Prcb->ZeroAddress;

    /* Spin while its not our turn */
    while (Lock->Turn != MyTicket)
    {
        /* Do something useful: Zero out 16/32 bytes of memory */
        ZeroAddress = KiDoZeroWork(ZeroAddress);

        /* Memory barrier to achieve that the turn is read again */
        KeMemoryBarrierWithoutFence();
    }

    /* Update the ZeroAddress */
    Prcb->ZeroAddress = ZeroAddress;
}

VOID
NTAPI
KiSpinOnTicketLock(PKTICKET_LOCK Lock, ULONG MyTicket)
{
    PKPRCB Prcb = KeGetCurrentPrcb();
    register PULONG_PTR ZeroAddress = Prcb->ZeroAddress;

    /* Spin while the ticket is not ours */
    while ((Lock->Turn != MyTicket) || (Lock->ShareCount != 0))
    {
        /* Do something useful: Zero out some memory */
        ZeroAddress = KiDoZeroWork(ZeroAddress);

        /* Memory barrier to achieve that the turn is read again */
        KeMemoryBarrierWithoutFence();
    }

    /* Update the ZeroAddress */
    Prcb->ZeroAddress = ZeroAddress;
}

VOID
FASTCALL
KeAcquireTicketLock(PKTICKET_LOCK Lock)
{
    KTICKET_LOCK MyTicket;

    /* Get a ticket */
    MyTicket.Long = InterlockedExchangeAdd(&Lock->Long, TL_TICKET_INC);

    /* Check if it's already our turn */
    if ((MyTicket.Ticket != MyTicket.Turn) && (MyTicket.ShareCount == 0))
    {
        /* It's not, spin until it is. */
        KiSpinOnTicketLock(Lock, MyTicket.Ticket);
    }
}

VOID
FASTCALL
KeReleaseTicketLock(PKTICKET_LOCK Lock)
{
    KTICKET_LOCK Current;
    LONG Inrement;

#if defined(_M_AMD64)// || defined(_IA64_) ?
    _InterlockedIncrement16(&Lock->Turn);
#elif defined(_M_IX86)
    _InterlockedIncrement8(&Lock->Turn);
#else
    /* Read the current lock value */
    Current = *Lock;

    /* Use the right turn increment to prevent overflow */
    if (Current.Turn == TL_MAX_TURN) Inrement = - TL_MAX_TURN;
    else Inrement = 1;

    /* Update the turn */
    InterlockedExchangeAdd(&Lock->Long, Inrement);
#endif
}

VOID
FASTCALL
KeAcquireTicketLockShared(PKTICKET_LOCK Lock)
{
    KTICKET_LOCK MyTicket;

    /* Get a ticket and increment share count */
    MyTicket.Long = InterlockedExchangeAdd(&Lock->Long,
                                           TL_SHARE_INC|TL_TICKET_INC);

    /* Check if it's already our turn */
    if (MyTicket.Ticket != MyTicket.Turn)
    {
        /* It's not, spin until it is. */
        KiSpinOnTicketLockAcquireShared(Lock, MyTicket.Ticket);
    }

    /* Now allow following shared acquisition */
    Lock->Turn = MyTicket.Ticket + 1;
}

VOID
FASTCALL
KeReleaseTicketLockShared(PKTICKET_LOCK Lock)
{
    /* Decrement the share count */
    InterlockedExchangeAdd(&Lock->Long, -TL_SHARE_INC);
}

#endif

#if 0

#define MAXIMUM_SLOTS_PER_LOCK sizeof(PVOID)

#define SLOT_OPEN    0x00
#define SLOT_SHARED  0x01
#define SLOT_BUSY    0x02
#define SLOT_CLOSED  0xFF


typedef struct
{
    LONG Turn;
    ULONG NumberOfSlots;
    UCHAR Slots[MAXIMUM_SLOTS_PER_LOCK]; //dynamic size
} KSLOT_LOCK, *PKSLOT_LOCK;

VOID
NTAPI
KeInitializeSlotLock(PKSLOT_LOCK Lock)
{
    /* Unlock slot 0 */
    Lock->Turn = 0;
    Lock->Slots[0] = SLOT_OPEN;

    /* Lock all other slots */
    for (i = 1; i < Lock->NumberOfSlots; i++) Lock->Slots[i] = SLOT_CLOSED;
}

ULONG
NTAPI
KeAcquireSlotLock(PKSLOT_LOCK Lock)
{
    ULONG Turn, Slot;

    Turn = InterlockedIncrement(&Lock->Turn);

    Slot = Turn % Lock->NumberOfSlots;

    if (Lock->Slots[Slot] != SLOT_OPEN)
    {
        Spin()
    }

    /* Mark it as busy */
    Lock->Slots[Slot] = SLOT_BUSY;

    return Turn;
}

VOID
NTAPI
KeReleaseSlotLock(PKSLOT_LOCK Lock, ULONG Turn)
{
    ULONG Slot, NextSlot;

    Slot = Turn % Lock->NumberOfSlots;
    NextSlot = (Turn + 1) % Lock->NumberOfSlots;

    /* */
    Lock->Slots[Slot] = SLOT_BLOCKED;

    Lock->Slots[NextSlot] = SLOT_FREE;
}

#endif

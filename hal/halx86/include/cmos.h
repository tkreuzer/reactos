
/* CMOS Registers and Ports */
#define CMOS_CONTROL_PORT       (PUCHAR)0x70
#define CMOS_DATA_PORT          (PUCHAR)0x71
#define RTC_REGISTER_A          0x0A
#define   RTC_REG_A_UIP         0x80
#define RTC_REGISTER_B          0x0B
#define   RTC_REG_B_PI          0x40
#define RTC_REGISTER_C          0x0C
#define RTC_REGISTER_D          0x0D
#define RTC_REGISTER_CENTURY    0x32

extern KSPIN_LOCK HalpSystemHardwareLock;
extern ULONG_PTR HalpSystemHardwareFlags;

UCHAR
FORCEINLINE
HalpReadCmos(IN UCHAR Reg)
{
    /* Select the register */
    WRITE_PORT_UCHAR(CMOS_CONTROL_PORT, Reg);

    /* Query the value */
    return READ_PORT_UCHAR(CMOS_DATA_PORT);
}

VOID
FORCEINLINE
HalpWriteCmos(IN UCHAR Reg,
              IN UCHAR Value)
{
    /* Select the register */
    WRITE_PORT_UCHAR(CMOS_CONTROL_PORT, Reg);

    /* Write the value */
    WRITE_PORT_UCHAR(CMOS_DATA_PORT, Value);
}

VOID
FORCEINLINE
HalpAcquireCmosSpinLock(VOID)
{
    ULONG_PTR EFlags;

    /* Get flags and disable interrupts */
    EFlags = __readeflags();
    _disable();

    /* Acquire the lock */
    HalpAcquireSpinLockNoIrql(&HalpSystemHardwareLock);

    /* We have the lock, save the flags now */
    HalpSystemHardwareFlags = EFlags;
}

VOID
FORCEINLINE
HalpReleaseCmosSpinLock(VOID)
{
    ULONG_PTR EFlags;

    /* Get the flags */
    EFlags = HalpSystemHardwareFlags;

    /* Release the lock */
    HalpAcquireSpinLockNoIrql(&HalpSystemHardwareLock);

    /* Restore the flags */
    __writeeflags(EFlags);
}




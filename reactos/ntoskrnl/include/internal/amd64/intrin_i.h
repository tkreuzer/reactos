#ifndef _INTRIN_INTERNAL_
#define _INTRIN_INTERNAL_

VOID
FORCEINLINE
KeSetCurrentIrql(KIRQL Irql)
{
    __writecr8(Irql);
}

PKGDTENTRY64
FORCEINLINE
KiGetGdtEntry(PVOID pGdt, USHORT Selector)
{
    return (PKGDTENTRY64)((ULONG64)pGdt + (Selector & ~RPL_MASK));
}

PVOID
FORCEINLINE
KiGetGdtDescriptorBase(PKGDTENTRY Entry)
{
    return (PVOID)((ULONG64)Entry->BaseLow |
                   (ULONG64)Entry->Bytes.BaseMiddle << 16 |
                   (ULONG64)Entry->Bytes.BaseHigh << 24 |
                   (ULONG64)Entry->BaseUpper << 32);
}

VOID
FORCEINLINE
KiSetGdtDescriptorBase(PKGDTENTRY Entry, ULONG64 Base)
{
    Entry->BaseLow = Base & 0xffff;
    Entry->Bits.BaseMiddle = (Base >> 16) & 0xff;
    Entry->Bits.BaseHigh = (Base >> 24) & 0xff;
    Entry->BaseUpper = Base >> 32;
}

PVOID
FORCEINLINE
KiSetGdtDescriptorLimit(PKGDTENTRY Entry, ULONG Limit)
{
    Entry->LimitLow = Limit & 0xffff;
    Entry->Bits.LimitHigh = Limit >> 16;
}

VOID
FORCEINLINE
KiInitGdtEntry(PKGDTENTRY64 Entry, ULONG64 Base, ULONG Size, UCHAR Type, UCHAR Dpl)
{
    KiSetGdtDescriptorBase(Entry, Base);
    KiSetGdtDescriptorLimit(Entry, Size - 1);
    Entry->Bits.Type = Type;
    Entry->Bits.Dpl = Dpl;
    Entry->Bits.Present = 1;
    Entry->Bits.System = 0;
    Entry->Bits.LongMode = 0;
    Entry->Bits.DefaultBig = 0;
    Entry->Bits.Granularity = 0;
    Entry->MustBeZero = 0;
}

#if defined(__GNUC__)

#define Ke386SetInterruptDescriptorTable(X) \
    __asm__("lidt %0\n\t" \
    : /* no outputs */ \
    : "m" (X));

#define Ke386GetInterruptDescriptorTable(X) \
    __asm__("sidt %0\n\t" \
    : /* no outputs */ \
    : "m" (X));

static __inline__ __attribute__((always_inline)) void __lldt(unsigned short Value)
{
	__asm__ __volatile__("lldt %0" : : "rm"(Value));
}

#define Ke386GetGlobalDescriptorTable(X) \
    __asm__("sgdt %0\n\t" \
    : /* no outputs */ \
    : "m" (X));


#elif defined(_MSC_VER)

#define UNIMPLEMENTED DbgPrint("%s is unimplemented!!!\n", __FUNCTION__);

void FORCEINLINE __lgdt(void *Source)
{
	UNIMPLEMENTED;
}

void FORCEINLINE __sgdt(void *Destination)
{
	UNIMPLEMENTED;
}

void FORCEINLINE __lldt(unsigned short Value)
{
	UNIMPLEMENTED;
}

void FORCEINLINE __sldt(void *Destination)
{
	UNIMPLEMENTED;
}

void FORCEINLINE __ltr(unsigned short Source)
{
	UNIMPLEMENTED;
}

void FORCEINLINE __str(unsigned short *Destination)
{
	UNIMPLEMENTED;
}



#else
#error Unknown compiler for inline assembler
#endif

#endif

/* EOF */

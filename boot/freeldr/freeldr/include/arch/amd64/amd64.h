/*
 *  FreeLoader
 *
 *  Copyright (C) 2003  Eric Kohl
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __ASM__
#pragma once
#endif

// This is needed because headers define wrong one for ReactOS
#undef KIP0PCRADDRESS
#define KIP0PCRADDRESS                      0xFFFFF78000001000ULL /* FIXME!!! */

#define VA_MASK 0x0000FFFFFFFFFFFFUL

#define PtrToPfn(p) \
    ((((ULONGLONG)p) >> PAGE_SHIFT) & 0xfffffffULL)

#define VAtoPXI(va) ((((ULONG64)(va)) >> PXI_SHIFT) & 0x1FF)
#define VAtoPPI(va) ((((ULONG64)(va)) >> PPI_SHIFT) & 0x1FF)
#define VAtoPDI(va) ((((ULONG64)(va)) >> PDI_SHIFT) & 0x1FF)
#define VAtoPTI(va) ((((ULONG64)(va)) >> PTI_SHIFT) & 0x1FF)

#ifndef ASM

VOID FrLdrSetupGdtIdt(VOID);
#endif

#define AMD64_GDTENTRY KGDTENTRY64
#define PAMD64_GDTENTRY PKGDTENTRY64

PAMD64_GDTENTRY
FORCEINLINE
Amd64GetGdtEntry(PVOID pGdt, USHORT Selector)
{
    return (PAMD64_GDTENTRY)((UINT64)pGdt + (Selector & ~3));
}

PVOID
FORCEINLINE
Amd64GetGdtDescriptorBase(PAMD64_GDTENTRY Entry)
{
    return (PVOID)((UINT64)Entry->BaseLow |
                   (UINT64)Entry->Bytes.BaseMiddle << 16 |
                   (UINT64)Entry->Bytes.BaseHigh << 24 |
                   (UINT64)Entry->BaseUpper << 32);
}

VOID
FORCEINLINE
Amd64SetGdtDescriptorBase(PAMD64_GDTENTRY Entry, UINT64 Base)
{
    Entry->BaseLow = Base & 0xffff;
    Entry->Bits.BaseMiddle = (Base >> 16) & 0xff;
    Entry->Bits.BaseHigh = (Base >> 24) & 0xff;
    Entry->BaseUpper = Base >> 32;
}

VOID
FORCEINLINE
Amd64SetGdtDescriptorLimit(PAMD64_GDTENTRY Entry, ULONG Limit)
{
    Entry->LimitLow = Limit & 0xffff;
    Entry->Bits.LimitHigh = Limit >> 16;
}

VOID
FORCEINLINE
Amd64InitGdtEntry(PAMD64_GDTENTRY Entry, UINT64 Base, ULONG Size, UCHAR Type, UCHAR Dpl)
{
    Amd64SetGdtDescriptorBase(Entry, Base);
    Amd64SetGdtDescriptorLimit(Entry, Size - 1);
    Entry->Bits.Type = Type;
    Entry->Bits.Dpl = Dpl;
    Entry->Bits.Present = 1;
    Entry->Bits.System = 0;
    Entry->Bits.LongMode = 0;
    Entry->Bits.DefaultBig = 0;
    Entry->Bits.Granularity = 0;
    Entry->MustBeZero = 0;
}

#define KiInitGdtEntry Amd64InitGdtEntry
#define KiGetGdtEntry Amd64GetGdtEntry


/* EOF */

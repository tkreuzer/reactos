/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * FILE:        hal/halx86/include/smp.h
 * PURPOSE:     Header File for SMP
 * PROGRAMMERS:  Copyright 2021 Justin Miller <justinmiller100@gmail.com>
 */

/* MADT information */
#pragma once

#define LOCAL_APIC_VERSION_MAX 0x1F
#define MAX_IOAPICS      64

/* SMP Specfic Delivery Modes */
#define APIC_DM_FIXED	  (0x0 << 8)
#define APIC_DM_LOWEST    (0x1 << 8)
#define APIC_DM_SMI       (0x2 << 8)
#define APIC_DM_REMRD     (0x3 << 8)
#define APIC_DM_NMI       (0x4 << 8)
#define APIC_DM_INIT      (0x5 << 8)
#define APIC_DM_STARTUP   (0x6 << 8)
#define APIC_DM_EXTINT	  (0x7 << 8)

#define APIC_ICR0_VECTOR   (0xFF << 0)    /* Vector */
#define APIC_ICR0_DM       (0x7 << 8)     /* Delivery Mode */
#define APIC_ICR0_DESTM    (0x1 << 11)    /* Destination Mode */
#define APIC_ICR0_DS       (0x1 << 12)    /* Delivery Status */
#define APIC_ICR0_LEVEL    (0x1 << 14)    /* Level */
#define APIC_ICR0_TM       (0x1 << 15)    /* Trigger Mode */
#define APIC_ICR0_DESTS    (0x3 << 18)    /* Destination Shorthand */

/* SMP Specific Targets */
#define APIC_TARGET_SELF         0x100
#define APIC_TARGET_ALL          0x200
#define APIC_TARGET_ALL_BUT_SELF 0x300

#define APIC_ICR0_LEVEL_DEASSERT (0x0 << 14) /* Deassert level */
#define APIC_ICR0_LEVEL_ASSERT   (0x1 << 14) /* Assert level */


/* This table is filled for each physical processor on system */
#include <pshpack1.h>
typedef struct _PROCESSOR_IDENTITY
{
    UCHAR ProcessorId;
    UCHAR LapicId;
    UCHAR NTProcessorNumber;
    BOOLEAN ProcessorStarted;
    BOOLEAN BSPStatus;

} PROCESSOR_IDENTITY, *PPROCESSOR_IDENTITY;
#define LOCAL_APIC_SIZE sizeof(PROCESSOR_IDENTITY)
#include <poppack.h>

BOOLEAN
HalpStartNextProcessor(IN PLOADER_PARAMETER_BLOCK LoaderBlock, IN PKPROCESSOR_STATE ProcessorState);

BOOLEAN
HaliStartApplicationProcessor(ULONG NTProcessorCount);

VOID __cdecl HaliAPBootSpinup(VOID);
VOID __cdecl HaliAPBootSpinupEnd(VOID);
VOID __cdecl KiApplicationProcessorSpinup(VOID);

DECLSPEC_NORETURN
CODE_SEG("INIT")
VOID
NTAPI
KiSystemStartup(
    IN PLOADER_PARAMETER_BLOCK LoaderBlock
);

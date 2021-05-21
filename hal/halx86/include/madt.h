/*
 * PROJECT:     ReactOS Kernel
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * FILE:        hal/halx86/include/madt.h
 * PURPOSE:     Header File for management of madt tables
 * PROGRAMMERS:  Copyright 2021 Justin Miller <justinmiller100@gmail.com>
 */


/* ACPI Specification constants */

#define MAX_IOAPICS      64

/* Names within the namespace are 4 bytes long */
#define ACPI_NAMESEG_SIZE               4     // Fixed by ACPI spec

/* Sizes for ACPI table headers */
#define ACPI_OEM_ID_SIZE                6
#define ACPI_OEM_TABLE_ID_SIZE          8

/* Table Entry Headers */

/* Generic subtable header (used in MADT, SRAT, etc.) */
typedef struct _ACPI_SUBTABLE_HEADER
{
    UCHAR Type;
    UCHAR Length;

} ACPI_SUBTABLE_HEADER, *PACPI_SUBTABLE_HEADER;

/* Master ACPI Table Header.
   This common header is used by all ACPI tables except the RSDP and FACS.
*/
typedef struct _ACPI_TABLE_HEADER
{
    CHAR Signature[ACPI_NAMESEG_SIZE];        // ASCII table signature
    ULONG Length;                             // Length of table in bytes, including this header
    UCHAR Revision;                           // ACPI Specification minor version number
    UCHAR Checksum;                           // To make sum of entire table == 0
    CHAR OemId[ACPI_OEM_ID_SIZE];             // ASCII OEM identification
    CHAR OemTableId[ACPI_OEM_TABLE_ID_SIZE];  // ASCII OEM table identification
    ULONG OemRevision;                        // OEM revision number
    CHAR AslCompilerId[ACPI_NAMESEG_SIZE];    // ASCII ASL compiler vendor ID
    ULONG AslCompilerRevision;                // ASL compiler version

} ACPI_TABLE_HEADER, *PACPI_TABLE_HEADER;

/* 0: Processor Local APIC */
typedef struct _ACPI_MADT_LOCAL_APIC
{
    ACPI_SUBTABLE_HEADER Header;
    UCHAR ProcessorId;          // ACPI processor id
    UCHAR Id;                   // Processor's local APIC id
    ULONG LapicFlags;

} ACPI_MADT_LOCAL_APIC, *PACPI_MADT_LOCAL_APIC;

/* 1: IO APIC */
typedef struct _ACPI_MADT_IO_APIC
{
    ACPI_SUBTABLE_HEADER Header;
    UCHAR Id;                   // I/O APIC ID
    UCHAR Reserved;             // Reserved - must be zero
    ULONG Address;              // APIC physical address
    ULONG GlobalIrqBase;        // Global system interrupt where INTI lines start

} ACPI_MADT_IO_APIC, *PACPI_MADT_IO_APIC;

/* This table is counter of the overall APIC constants acquired from madt */
typedef struct _HALP_APIC_INFO_TABLE
{
    ULONG ApicMode;
    ULONG ProcessorCount; /* Count of all physical cores, This includes BSP */
    ULONG IOAPICCount;
    ULONG LocalApicPA;                // The 32-bit physical address at which each processor can access its local interrupt controller
    ULONG IoApicVA[MAX_IOAPICS];
    ULONG IoApicPA[MAX_IOAPICS];
    ULONG IoApicIrqBase[MAX_IOAPICS]; // Global system interrupt base 

} HALP_APIC_INFO_TABLE, *PHALP_APIC_INFO_TABLE;

/* 
 *          ACPI constant Tables 
 *  TODO: These three could technically be acquired from ACPICA but it seems more trouble then it's worth...
*/


typedef struct _ACPI_TABLE_MADT
{
    ACPI_TABLE_HEADER Header;   // Common ACPI table header
    ULONG Address;              // Physical address of local APIC
    ULONG Flags;

} ACPI_TABLE_MADT, *PACPI_TABLE_MADT;




/* Values for MADT subtable type in ACPI_SUBTABLE_HEADER */

enum AcpiMadtType
{
    ACPI_MADT_TYPE_LOCAL_APIC               = 0,
    ACPI_MADT_TYPE_IO_APIC                  = 1,
    ACPI_MADT_TYPE_INTERRUPT_OVERRIDE       = 2,
    ACPI_MADT_TYPE_NMI_SOURCE               = 3,
    ACPI_MADT_TYPE_LOCAL_APIC_NMI           = 4,
    ACPI_MADT_TYPE_LOCAL_APIC_OVERRIDE      = 5,
    ACPI_MADT_TYPE_IO_SAPIC                 = 6,
    ACPI_MADT_TYPE_LOCAL_SAPIC              = 7,
    ACPI_MADT_TYPE_INTERRUPT_SOURCE         = 8,
    ACPI_MADT_TYPE_LOCAL_X2APIC             = 9,
    ACPI_MADT_TYPE_LOCAL_X2APIC_NMI         = 10,
    ACPI_MADT_TYPE_GENERIC_INTERRUPT        = 11,
    ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR      = 12,
    ACPI_MADT_TYPE_GENERIC_MSI_FRAME        = 13,
    ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR    = 14,
    ACPI_MADT_TYPE_GENERIC_TRANSLATOR       = 15,
    ACPI_MADT_TYPE_RESERVED                 = 16    /* 16 and greater are reserved */
};


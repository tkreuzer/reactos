
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int ULONG;
typedef int LONG;

#define IMAGE_DOS_SIGNATURE                 0x5A4D
#define IMAGE_NT_SIGNATURE                  0x00004550
#define IMAGE_FILE_MACHINE_I386       0x14c
#define IMAGE_NT_OPTIONAL_HDR32_MAGIC      0x10b

#include <pshpack2.h>
typedef struct _IMAGE_DOS_HEADER
{
  USHORT e_magic;
  USHORT e_cblp;
  USHORT e_cp;
  USHORT e_crlc;
  USHORT e_cparhdr;
  USHORT e_minalloc;
  USHORT e_maxalloc;
  USHORT e_ss;
  USHORT e_sp;
  USHORT e_csum;
  USHORT e_ip;
  USHORT e_cs;
  USHORT e_lfarlc;
  USHORT e_ovno;
  USHORT e_res[4];
  USHORT e_oemid;
  USHORT e_oeminfo;
  USHORT e_res2[10];
  LONG e_lfanew;
} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;
#include <poppack.h>

#include <pshpack4.h>
#define IMAGE_SIZEOF_SHORT_NAME              8
typedef struct _IMAGE_EXPORT_DIRECTORY {
  ULONG Characteristics;
  ULONG TimeDateStamp;
  USHORT MajorVersion;
  USHORT MinorVersion;
  ULONG Name;
  ULONG Base;
  ULONG NumberOfFunctions;
  ULONG NumberOfNames;
  ULONG AddressOfFunctions;
  ULONG AddressOfNames;
  ULONG AddressOfNameOrdinals;
} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;

typedef struct _IMAGE_SECTION_HEADER {
  UCHAR Name[IMAGE_SIZEOF_SHORT_NAME];
  union {
    ULONG PhysicalAddress;
    ULONG VirtualSize;
  } Misc;
  ULONG VirtualAddress;
  ULONG SizeOfRawData;
  ULONG PointerToRawData;
  ULONG PointerToRelocations;
  ULONG PointerToLinenumbers;
  USHORT NumberOfRelocations;
  USHORT NumberOfLinenumbers;
  ULONG Characteristics;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

typedef struct _IMAGE_FILE_HEADER {
  USHORT Machine;
  USHORT NumberOfSections;
  ULONG TimeDateStamp;
  ULONG PointerToSymbolTable;
  ULONG NumberOfSymbols;
  USHORT SizeOfOptionalHeader;
  USHORT Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
  ULONG VirtualAddress;
  ULONG Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16
typedef struct _IMAGE_OPTIONAL_HEADER {
  USHORT Magic;
  UCHAR MajorLinkerVersion;
  UCHAR MinorLinkerVersion;
  ULONG SizeOfCode;
  ULONG SizeOfInitializedData;
  ULONG SizeOfUninitializedData;
  ULONG AddressOfEntryPoint;
  ULONG BaseOfCode;
  ULONG BaseOfData;
  ULONG ImageBase;
  ULONG SectionAlignment;
  ULONG FileAlignment;
  USHORT MajorOperatingSystemVersion;
  USHORT MinorOperatingSystemVersion;
  USHORT MajorImageVersion;
  USHORT MinorImageVersion;
  USHORT MajorSubsystemVersion;
  USHORT MinorSubsystemVersion;
  ULONG Win32VersionValue;
  ULONG SizeOfImage;
  ULONG SizeOfHeaders;
  ULONG CheckSum;
  USHORT Subsystem;
  USHORT DllCharacteristics;
  ULONG SizeOfStackReserve;
  ULONG SizeOfStackCommit;
  ULONG SizeOfHeapReserve;
  ULONG SizeOfHeapCommit;
  ULONG LoaderFlags;
  ULONG NumberOfRvaAndSizes;
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_NT_HEADERS {
  ULONG Signature;
  IMAGE_FILE_HEADER FileHeader;
  IMAGE_OPTIONAL_HEADER32 OptionalHeader;
} IMAGE_NT_HEADERS32;

#include <poppack.h>

#define NUMBER_OF_SECTIONS 3

#ifndef _EXPORT_LIST_FILE
#define _EXPORT_LIST_FILE "exportlist.h"
#endif

#define _EXPORT(_Name) _EXPORT2(_Name, _Name)
#define FIELD_OFFSET(t,f) ((int)&(((t*) 0)->f))
#define FIELD_SIZE(type, field) (sizeof(((type *)0)->field))
#define RVA(_Symbol) (((ULONG_PTR)(_Symbol)) - ((ULONG_PTR)&PeHeader))

#ifdef _EXPORT_LIST_FILE

typedef struct _EXPORT_THUNK_TABLE
{
#define _EXPORT2(_Name, _Target) unsigned int _Name;
#include _EXPORT_LIST_FILE
#undef _EXPORT2
    unsigned int Terminator;
} EXPORT_THUNK_TABLE;

#define NUMBER_OF_EXPORTS ((sizeof(EXPORT_THUNK_TABLE) / sizeof(unsigned int)) - 1)

typedef struct _EXPORT_NAMES
{
#define _EXPORT2(_Name, _Target) char _Name[sizeof(#_Name)];
#include _EXPORT_LIST_FILE
#undef _EXPORT2
    char Terminator;
} EXPORT_NAMES;

typedef struct _FULL_EXPORT_DIRECTORY
{
    IMAGE_EXPORT_DIRECTORY Header;
    EXPORT_THUNK_TABLE OrdinalTable;
    EXPORT_THUNK_TABLE FunctionTable;
    EXPORT_NAMES Names;
} FULL_EXPORT_DIRECTORY;

#endif /* _EXPORT_LIST_FILE */

/* The full data structure */
typedef struct _PE_HEADER
{
    IMAGE_DOS_HEADER DosHeader;
    UCHAR DosStubCode[0xE8 - sizeof(IMAGE_DOS_HEADER)];
    IMAGE_NT_HEADERS32 NtHeaders;
    IMAGE_SECTION_HEADER SectionHeaders[NUMBER_OF_SECTIONS];

#ifdef _EXPORT_LIST_FILE
    FULL_EXPORT_DIRECTORY ExportDirectory;
#endif
} PE_HEADER;

#define _EXPORT2(_Name, _Target) extern char _Target[];
#include _EXPORT_LIST_FILE
#undef _EXPORT2


PE_HEADER PeHeader =
{
    // IMAGE_DOS_HEADER DosHeader;
    {
        IMAGE_DOS_SIGNATURE, // WORD e_magic;
        0x90, // WORD e_cblp;
        0x03, // WORD e_cp;
        0, // WORD e_crlc;
        0x04, // WORD e_cparhdr;
        0, // WORD e_minalloc;
        0xffff, // WORD e_maxalloc;
        0, // WORD e_ss;
        0xb8, // WORD e_sp;
        0, // WORD e_csum;
        0, // WORD e_ip;
        0, // WORD e_cs;
        0x40, // WORD e_lfarlc;
        0, // WORD e_ovno;
        0, // WORD e_res[4];
        0, // WORD e_oemid;
        0, // WORD e_oeminfo;
        0, // WORD e_res2[10];
        FIELD_OFFSET(PE_HEADER, NtHeaders) // LONG e_lfanew;
    },

    // CHAR DosStubCode[0xE8 - sizeof(IMAGE_DOS_HEADER)];
    { 0 },

    // IMAGE_NT_HEADERS NtHeaders;
    {
        IMAGE_NT_SIGNATURE, // DWORD Signature;

        // IMAGE_FILE_HEADER FileHeader;
        {
            IMAGE_FILE_MACHINE_I386, // WORD Machine;
            NUMBER_OF_SECTIONS, // WORD NumberOfSections;
            0, // DWORD TimeDateStamp;
            0, // DWORD PointerToSymbolTable;
            0, // DWORD NumberOfSymbols;
            sizeof(IMAGE_OPTIONAL_HEADER32), // WORD SizeOfOptionalHeader;
            0x010E, // WORD Characteristics;
        },

        // IMAGE_OPTIONAL_HEADER OptionalHeader;
        {
            IMAGE_NT_OPTIONAL_HDR32_MAGIC, // WORD Magic;
            7, // BYTE MajorLinkerVersion;
            10, // BYTE MinorLinkerVersion;
            0, // DWORD SizeOfCode;
            0, // DWORD SizeOfInitializedData;
            0, // DWORD SizeOfUninitializedData;
            0, // DWORD AddressOfEntryPoint;
            0, // DWORD BaseOfCode;
            0, // DWORD BaseOfData;
            0, // DWORD ImageBase;
            4096, // DWORD SectionAlignment;
            512, // DWORD FileAlignment;
            5, // WORD MajorOperatingSystemVersion;
            2, // WORD MinorOperatingSystemVersion;
            5, // WORD MajorImageVersion;
            2, // WORD MinorImageVersion;
            5, // WORD MajorSubsystemVersion;
            2, // WORD MinorSubsystemVersion;
            0, // DWORD Win32VersionValue;
            0x40000000, // DWORD SizeOfImage;
            0x400, // DWORD SizeOfHeaders;
            0, // DWORD CheckSum;
            1, //IMAGE_SUBSYSTEM_NATIVE, // WORD Subsystem;
            0, // WORD DllCharacteristics;
            0x40000, // DWORD SizeOfStackReserve;
            0x1000, // DWORD SizeOfStackCommit;
            0x100000, // DWORD SizeOfHeapReserve;
            0x1000, // DWORD SizeOfHeapCommit;
            0, // DWORD LoaderFlags;
            IMAGE_NUMBEROF_DIRECTORY_ENTRIES, // DWORD NumberOfRvaAndSizes;

            // IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
            {
#ifdef _EXPORT_LIST_FILE
                { FIELD_OFFSET(PE_HEADER, ExportDirectory), FIELD_SIZE(PE_HEADER, ExportDirectory)}, // IMAGE_DIRECTORY_ENTRY_EXPORT    0
#else
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_EXPORT    0
#endif
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_IMPORT    1
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_RESOURCE  2
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_EXCEPTION 3
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_SECURITY  4
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_BASERELOC 5
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_DEBUG 6
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_COPYRIGHT 7
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_GLOBALPTR 8
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_TLS   9
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG   10
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT  11
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_IAT   12
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT  13
                { 0, 0 }, // IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR    14
                { 0, 0 }  // metadata 15
            }
        }
    },

    // IMAGE_SECTION_HEADER SectionHeaders[NUMBER_OF_SECTIONS];
    {
        { 0 },
        { 0 },
        { 0 }
    },

#ifdef _EXPORT_LIST_FILE
    // FULL_EXPORT_DIRECTORY ExportDirectory;
    {
        // IMAGE_EXPORT_DIRECTORY Header;
        {
            0, // DWORD Characteristics;
            0, // DWORD TimeDateStamp;
            0, // WORD MajorVersion;
            0, // WORD MinorVersion;
            0, // DWORD Name;
            0, // DWORD Base;
            0, // DWORD NumberOfFunctions;
            0, // DWORD NumberOfNames;
            0, // DWORD AddressOfFunctions;
            0, // DWORD AddressOfNames;
            0  // DWORD AddressOfNameOrdinals;        },
        },

        // EXPORT_THUNK_TABLE OrdinalTable;
        {
#define _EXPORT2(_Name, _Target) FIELD_OFFSET(PE_HEADER, ExportDirectory.Names._Name),
#include _EXPORT_LIST_FILE
#undef _EXPORT2
            0 // Terminator
        },

        // EXPORT_THUNK_TABLE FunctionTable;
        {
#define _EXPORT2(_Name, _Target) ((ULONG)&_Target[2]),
#include _EXPORT_LIST_FILE
#undef _EXPORT2
            0 // Terminator
        },

        // EXPORT_NAMES Names;
        {
#define _EXPORT2(_Name, _Target) #_Target,
#include _EXPORT_LIST_FILE
#undef _EXPORT2
            0 // Terminator
        }
    }
#endif
};


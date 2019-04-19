          typedef struct _IMAGE_DATA_DIRECTORY // 2 elements, 0x8 bytes (sizeof)
          {
/*0x000*/     ULONG32      VirtualAddress;
/*0x004*/     ULONG32      Size;
          }IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

          typedef struct _IMAGE_DEBUG_DIRECTORY // 8 elements, 0x1C bytes (sizeof)
          {
/*0x000*/     ULONG32      Characteristics;
/*0x004*/     ULONG32      TimeDateStamp;
/*0x008*/     UINT16       MajorVersion;
/*0x00A*/     UINT16       MinorVersion;
/*0x00C*/     ULONG32      Type;
/*0x010*/     ULONG32      SizeOfData;
/*0x014*/     ULONG32      AddressOfRawData;
/*0x018*/     ULONG32      PointerToRawData;
          }IMAGE_DEBUG_DIRECTORY, *PIMAGE_DEBUG_DIRECTORY;

          typedef struct _IMAGE_DOS_HEADER // 19 elements, 0x40 bytes (sizeof)
          {
/*0x000*/     UINT16       e_magic;
/*0x002*/     UINT16       e_cblp;
/*0x004*/     UINT16       e_cp;
/*0x006*/     UINT16       e_crlc;
/*0x008*/     UINT16       e_cparhdr;
/*0x00A*/     UINT16       e_minalloc;
/*0x00C*/     UINT16       e_maxalloc;
/*0x00E*/     UINT16       e_ss;
/*0x010*/     UINT16       e_sp;
/*0x012*/     UINT16       e_csum;
/*0x014*/     UINT16       e_ip;
/*0x016*/     UINT16       e_cs;
/*0x018*/     UINT16       e_lfarlc;
/*0x01A*/     UINT16       e_ovno;
/*0x01C*/     UINT16       e_res[4];
/*0x024*/     UINT16       e_oemid;
/*0x026*/     UINT16       e_oeminfo;
/*0x028*/     UINT16       e_res2[10];
/*0x03C*/     LONG32       e_lfanew;
          }IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

          typedef struct _IMAGE_FILE_HEADER      // 7 elements, 0x14 bytes (sizeof)
          {
/*0x000*/     UINT16       Machine;
/*0x002*/     UINT16       NumberOfSections;
/*0x004*/     ULONG32      TimeDateStamp;
/*0x008*/     ULONG32      PointerToSymbolTable;
/*0x00C*/     ULONG32      NumberOfSymbols;
/*0x010*/     UINT16       SizeOfOptionalHeader;
/*0x012*/     UINT16       Characteristics;
          }IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

          typedef struct _IMAGE_NT_HEADERS64                  // 3 elements, 0x108 bytes (sizeof)
          {
/*0x000*/     ULONG32      Signature;
/*0x004*/     struct _IMAGE_FILE_HEADER FileHeader;           // 7 elements, 0x14 bytes (sizeof)
/*0x018*/     struct _IMAGE_OPTIONAL_HEADER64 OptionalHeader; // 30 elements, 0xF0 bytes (sizeof)
          }IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;

          typedef struct _IMAGE_OPTIONAL_HEADER64             // 30 elements, 0xF0 bytes (sizeof)
          {
/*0x000*/     UINT16       Magic;
/*0x002*/     UINT8        MajorLinkerVersion;
/*0x003*/     UINT8        MinorLinkerVersion;
/*0x004*/     ULONG32      SizeOfCode;
/*0x008*/     ULONG32      SizeOfInitializedData;
/*0x00C*/     ULONG32      SizeOfUninitializedData;
/*0x010*/     ULONG32      AddressOfEntryPoint;
/*0x014*/     ULONG32      BaseOfCode;
/*0x018*/     UINT64       ImageBase;
/*0x020*/     ULONG32      SectionAlignment;
/*0x024*/     ULONG32      FileAlignment;
/*0x028*/     UINT16       MajorOperatingSystemVersion;
/*0x02A*/     UINT16       MinorOperatingSystemVersion;
/*0x02C*/     UINT16       MajorImageVersion;
/*0x02E*/     UINT16       MinorImageVersion;
/*0x030*/     UINT16       MajorSubsystemVersion;
/*0x032*/     UINT16       MinorSubsystemVersion;
/*0x034*/     ULONG32      Win32VersionValue;
/*0x038*/     ULONG32      SizeOfImage;
/*0x03C*/     ULONG32      SizeOfHeaders;
/*0x040*/     ULONG32      CheckSum;
/*0x044*/     UINT16       Subsystem;
/*0x046*/     UINT16       DllCharacteristics;
/*0x048*/     UINT64       SizeOfStackReserve;
/*0x050*/     UINT64       SizeOfStackCommit;
/*0x058*/     UINT64       SizeOfHeapReserve;
/*0x060*/     UINT64       SizeOfHeapCommit;
/*0x068*/     ULONG32      LoaderFlags;
/*0x06C*/     ULONG32      NumberOfRvaAndSizes;
/*0x070*/     struct _IMAGE_DATA_DIRECTORY DataDirectory[16];
          }IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;

          typedef struct _IMAGE_ROM_OPTIONAL_HEADER // 13 elements, 0x38 bytes (sizeof)
          {
/*0x000*/     UINT16       Magic;
/*0x002*/     UINT8        MajorLinkerVersion;
/*0x003*/     UINT8        MinorLinkerVersion;
/*0x004*/     ULONG32      SizeOfCode;
/*0x008*/     ULONG32      SizeOfInitializedData;
/*0x00C*/     ULONG32      SizeOfUninitializedData;
/*0x010*/     ULONG32      AddressOfEntryPoint;
/*0x014*/     ULONG32      BaseOfCode;
/*0x018*/     ULONG32      BaseOfData;
/*0x01C*/     ULONG32      BaseOfBss;
/*0x020*/     ULONG32      GprMask;
/*0x024*/     ULONG32      CprMask[4];
/*0x034*/     ULONG32      GpValue;
          }IMAGE_ROM_OPTIONAL_HEADER, *PIMAGE_ROM_OPTIONAL_HEADER;

          typedef struct _IMAGE_SECTION_HEADER   // 10 elements, 0x28 bytes (sizeof)
          {
/*0x000*/     UINT8        Name[8];
              union                              // 2 elements, 0x4 bytes (sizeof)
              {
/*0x008*/         ULONG32      PhysicalAddress;
/*0x008*/         ULONG32      VirtualSize;
              }Misc;
/*0x00C*/     ULONG32      VirtualAddress;
/*0x010*/     ULONG32      SizeOfRawData;
/*0x014*/     ULONG32      PointerToRawData;
/*0x018*/     ULONG32      PointerToRelocations;
/*0x01C*/     ULONG32      PointerToLinenumbers;
/*0x020*/     UINT16       NumberOfRelocations;
/*0x022*/     UINT16       NumberOfLinenumbers;
/*0x024*/     ULONG32      Characteristics;
          }IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;



#pragma once

#include "Mmp.hpp"

typedef
    _Struct_size_bytes_(_Inexpressible_(sizeof(struct _MDL) +
       (ByteOffset + ByteCount + PAGE_SIZE-1) / PAGE_SIZE * sizeof(PFN_NUMBER)))
struct _MDL
{
    struct _MDL *Next;
    CSHORT Size;
    CSHORT MdlFlags;
#if defined(_WIN64)
    USHORT AllocationProcessorNumber;
    USHORT Reserved;
#endif
    struct _EPROCESS *Process;
    PVOID MappedSystemVa;
    PVOID StartVa;
    ULONG ByteCount;
    ULONG ByteOffset;
} MDL, *PMDL;

typedef struct _MM_PHYSICAL_ADDRESS_LIST
{
    PHYSICAL_ADDRESS PhysicalAddress;
    SIZE_T NumberOfBytes;
} MM_PHYSICAL_ADDRESS_LIST, *PMM_PHYSICAL_ADDRESS_LIST;



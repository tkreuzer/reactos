


#include "amd64/Mm_amd64.h"

#include "MmAvlTree.h"
#include "PfnDatabase.h"

enum
{
    MM_PAGE_NOACCESS = 0x00,
    MM_PAGE_READ = 0x01,
    MM_PAGE_WRITE = 0x02,
    MM_PAGE_READ_WRITE = 0x03,
    MM_PAGE_EXECUTE = 0x04,
    MM_PAGE_EXECUTE_READ = 0x05,
    MM_PAGE_EXECUTE_WRITE = 0x06,
    MM_PAGE_EXECUTE_READ_WRITE = 0x07,
    MM_PAGE_WRITECOPY = 0x08,
};

typedef struct _MIVAD
{
    MM_AVL_NODE Node;
    ULONG_PTR StartingVpn;
    ULONG_PTR EndingVpn;
    KSPIN_LOCK Lock;
    const struct _MIVADTYPE *Type;
    PVOID Context;
    struct _MMVAD *NextVad; // list of VADs for a section (maybe use LIST_ENTRY)
//    MXPTE TemplatePte;
//    struct
//    {
//        ULONG_PTR Type : 3;

//    };
//    ...
#if DBG
    CHAR Name[8];
#endif
} MIVAD, *PMIVAD;

VOID
NTAPI
MiModifyVad(
    _Inout_ PMIVAD Vad,
    _In_ ULONG_PTR Vpn,
    _In_ ULONG PageCount,
    _In_ ULONG Action);

NTSTATUS
NTAPI
MiCreateVirtualMapping(
    _In_ PVOID Address,
    _In_ ULONG PageCount,
    _In_ ULONG Protection);

extern PMEMORY_ALLOCATION_DESCRIPTOR MiLargestDescriptor;;
extern PFN_NUMBER MiEarlyAllocBasePage;
extern PFN_NUMBER MiEarlyAllocPageCount;

BOOLEAN
FORCEINLINE
MiIsMemoryTypeFree(TYPE_OF_MEMORY MemoryType)
{
    return ((MemoryType == LoaderFree) ||
            (MemoryType == LoaderLoadedProgram) ||
            (MemoryType == LoaderFirmwareTemporary) ||
            (MemoryType == LoaderOsloaderStack));
}

BOOLEAN
FORCEINLINE
MiIsMemoryTypeInvisible(TYPE_OF_MEMORY MemoryType)
{
    return ((MemoryType == LoaderFirmwarePermanent) ||
            (MemoryType == LoaderSpecialMemory) ||
            (MemoryType == LoaderHALCachedMemory) ||
            (MemoryType == LoaderBBTMemory));
}

VOID
INITAPI
MiEarlyMapPTEs(
    PVOID StartAddress,
    PVOID EndAddress);

VOID
INITAPI
MiEarlyMapPDEs(
    PVOID StartAddress,
    PVOID EndAddress);

VOID
INITAPI
MiEarlyMapPPEs(
    PVOID StartAddress,
    PVOID EndAddress);

VOID
INITAPI
MiEarlyMapPXEs(
    PVOID StartAddress,
    PVOID EndAddress);

PFN_NUMBER
INITAPI
MiEarlyAllocPage(VOID);

VOID
INITAPI
MxInitializeArchitectureSpecific(
    IN PLOADER_PARAMETER_BLOCK LoaderBlock);

VOID
NTAPI
MxZeroPage(PVOID Address);

VOID
NTAPI
MiZeroPhysicalPage(PFN_NUMBER PageFrameNumber);

PMXPTE
NTAPI
MxReservePtes(
    _In_ ULONG_PTR StartingVpn,
    _In_ ULONG PageCount);


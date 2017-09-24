
#include "../ntosbase.h"
#include "../VadTable.hpp"
#include "../KernelVad.hpp"
#include <arc/arc.h>
#include <ndk/pstypes.h>
#include <eal.h>

#undef KI_USER_SHARED_DATA
#define KI_USER_SHARED_DATA     0x80010000

extern "C" {
extern LCID PsDefaultThreadLocaleId;
}

namespace Mm {

KERNEL_VAD g_KernelVads[16];

VOID
InitializeMemoryMap(_In_ struct _LOADER_PARAMETER_BLOCK* LoaderBlock)
{
    ULONG i;
    NTSTATUS Status;
    PLIST_ENTRY ListEntry;
    PMEMORY_ALLOCATION_DESCRIPTOR Mad;

    for (i = 0; g_MemoryMap[i].StartAddress != 0; i++)
    {
        ULONG_PTR StartingVpn = g_MemoryMap[i].StartAddress / PAGE_SIZE;
        ULONG_PTR EndingVpn = (g_MemoryMap[i].EndAddress + PAGE_SIZE - 1) / PAGE_SIZE;
        ULONG NumberOfPages = EndingVpn - StartingVpn;

        NT_ASSERT(i < sizeof(g_MemoryMap) / sizeof(g_MemoryMap[0]));
        g_KernelVads[i].Initialize();
        DbgPrint("# Added memory %p - %p\n", VpnToAddress(StartingVpn), VpnToAddress(StartingVpn + NumberOfPages));
        Status = g_KernelVadTable.InsertVadObjectAtVpn(&g_KernelVads[i],
                                                       StartingVpn,
                                                       NumberOfPages);
        if (!NT_SUCCESS(Status))
        {
            DbgPrint("Failed to reserve mem: %p - %p\n", StartingVpn, EndingVpn);
        }
        NT_ASSERT(NT_SUCCESS(Status));
        //DbgPrint("# Added memory %p - %p\n", VpnToAddress(StartingVpn), VpnToAddress(StartingVpn + NumberOfPages));
    }
}

extern "C" PKPRCB KiProcessorBlock[];

PLDR_DATA_TABLE_ENTRY
NTAPI
FindUserModeModule (
    _In_ PVOID Address)
{
    PEPROCESS CurrentProcess;
    PPEB Peb;
    PPEB_LDR_DATA LdrData;
    PLIST_ENTRY ListEntry;
    PLDR_DATA_TABLE_ENTRY LdrEntry;
    
    NT_ASSERT(KiProcessorBlock[0] != 0);
    CurrentProcess = (PEPROCESS)KiProcessorBlock[0]->CurrentThread->ApcState.Process;

    Peb = CurrentProcess->Peb;
    if (Peb == NULL)
    {
        ERR("process has no TEB\n");
        return NULL;
    }

    LdrData = Peb->Ldr;
    if (LdrData == NULL)
    {
        ERR("process has no LdrData\n");
        return NULL;
    }

    for (ListEntry = LdrData->InLoadOrderModuleList.Flink;
         ListEntry != &LdrData->InLoadOrderModuleList;
         ListEntry = ListEntry->Flink)
    {
        /* Get the loader entry */
        LdrEntry = CONTAINING_RECORD(ListEntry,
                                     LDR_DATA_TABLE_ENTRY,
                                     InLoadOrderLinks);

        //DbgPrint("Checking %p - %p\n", LdrEntry->DllBase, (PCHAR)LdrEntry->DllBase + LdrEntry->SizeOfImage);
        if (((ULONG_PTR)Address >= (ULONG_PTR)LdrEntry->DllBase) &&
            ((ULONG_PTR)Address <= (ULONG_PTR)LdrEntry->DllBase + LdrEntry->SizeOfImage))
        {
            return LdrEntry;
        }
    }
    
    return NULL;
}

extern "C"
BOOLEAN
NTAPI
GetUserModeModuleName (
    _In_ PVOID Address,
    _Out_ PVOID* ImageBase,
    _Out_ PCHAR NameBuffer,
    _In_ ULONG BufferLength)
{
    PLDR_DATA_TABLE_ENTRY LdrEntry;
    ULONG i, Length;

    *ImageBase = NULL;
    strncpy(NameBuffer, "<unknown>", BufferLength);
    NameBuffer[BufferLength - 1] = 0;

    LdrEntry = FindUserModeModule(Address);
    if (LdrEntry == NULL)
    {
        return FALSE;
    }
    
    *ImageBase = LdrEntry->DllBase;

    Length = min(BufferLength - 1, LdrEntry->FullDllName.Length);
    
    for (i = 0; i < Length; i++)
    {
        NameBuffer[i] = (CHAR)LdrEntry->FullDllName.Buffer[i];
    }

    NameBuffer[i] = 0;
    return TRUE;
}

VOID
InitializeMappingSupport (
    VOID);

extern "C" PVOID MmPfnDatabase;

VOID
InitializeMachineDependent(struct _LOADER_PARAMETER_BLOCK *LoaderBlock)
{

    InitializeMemoryMap(LoaderBlock);
    InitializeMappingSupport();

    MmPfnDatabase = (PVOID)0x82000000;
    //MmUserProbeAddress = (PVOID)0x7c
}

typedef struct
{
    ULONG Va;
    ULONG OldValue;
    ULONG NewValue;
} PATCHDATA;

#define WIN32K_IMAGE_BASE 0xbf800000

VOID
PatchWin32k(
    PVOID ImageBase)
{
    ULONG i;
    static PATCHDATA PatchTable[] =
    {
#if 1 // CHECKED BUILD
        {0xBF8AAA84 + 1, 0xFFDF02D0, KI_USER_SHARED_DATA + 0x2D0},
        {0xbf8ab2e6 + 1, 0xFFDF02D0, KI_USER_SHARED_DATA + 0x2D0},
        {0xbfa85046 + 1, 0xFFDF02D0, KI_USER_SHARED_DATA + 0x2D0},
        {0xBFA71440 + 0, 0x00000000, 0x000000FF}, // gWarningLevel
        {0xBFA71438 + 0, 0x00000000, 0xFFFFFFFF}, // GreTraceDisplayDriverLoad

#else
        {0xbf808CA7 + 1, 0xFFDF02D0, KI_USER_SHARED_DATA + 0x2D0},
        {0xbf9BA852 + 1, 0xFFDF02D0, KI_USER_SHARED_DATA + 0x2D0},
#endif        
    };

    static PATCHDATA BreakpointTable[] =
    {
        {0xBF81F1A4 + 0, 0, 0}, // GreGetTextExtentW
        //{0xBF962232 + 0, 0, 0}, // RFONTOBJ::bTextExtent
        {0xBF962232 + 0, 0x850fc63b  , 0x850fCCCC}, // RFONTOBJ::bTextExtent
    };



    for (i = 0; i < RTL_NUMBER_OF(PatchTable); i++)
    {
        PULONG Address = (PULONG)((PUCHAR)ImageBase + PatchTable[i].Va - WIN32K_IMAGE_BASE);
        
        if (*Address != PatchTable[i].OldValue)
        {
            DbgPrint("Wrong Value at %p (org 0x%lx): expected 0x%lx, got 0x%lx\n",
                     Address, PatchTable[i].Va, PatchTable[i].OldValue, *Address);
            __debugbreak();
        }
        
        *Address = PatchTable[i].NewValue;
    }

    for (i = 0; i < RTL_NUMBER_OF(BreakpointTable); i++)
    {
        PSHORT Address = (PSHORT)((PUCHAR)ImageBase + BreakpointTable[i].Va - WIN32K_IMAGE_BASE);
        *Address = 0xCCCC;
    }
}


VOID
PatchLoadedSystemImage(
    PUNICODE_STRING ImageName,
    PVOID ImageBase)
{
    if (wcsstr(ImageName->Buffer, L"win32k.sys"))
    {
        PatchWin32k(ImageBase);
    }
}

extern "C" {

PVOID MmHighestSystemAddress = (PVOID)0xc0000000;

static const
USHORT ProtectToWin32Protect[32] =
{
    PAGE_NOACCESS, // MM_INVALID
    PAGE_READONLY, // MM_READONLY
    PAGE_EXECUTE_READ, // MM_EXECUTE
    PAGE_EXECUTE_READ, // MM_EXECUTE_READ
    PAGE_READWRITE, // MM_READWRITE
    PAGE_WRITECOPY, // MM_WRITECOPY
    PAGE_EXECUTE_READWRITE, // MM_EXECUTE_READWRITE
    PAGE_EXECUTE_WRITECOPY, // MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_UNCACHED | MM_INVALID
    PAGE_NOCACHE | PAGE_READONLY, // MM_UNCACHED | MM_READONLY
    PAGE_NOCACHE | PAGE_EXECUTE_READ, // MM_UNCACHED | MM_EXECUTE
    PAGE_NOCACHE | PAGE_EXECUTE_READ, // MM_UNCACHED | MM_EXECUTE_READ
    PAGE_NOCACHE | PAGE_READWRITE, // MM_UNCACHED | MM_READWRITE
    PAGE_NOCACHE | PAGE_WRITECOPY, // MM_UNCACHED | MM_WRITECOPY
    PAGE_NOCACHE | PAGE_EXECUTE_READWRITE, // MM_UNCACHED | MM_EXECUTE_READWRITE
    PAGE_NOCACHE | PAGE_EXECUTE_WRITECOPY, // MM_UNCACHED | MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_GUARDPAGE | MM_INVALID
    PAGE_GUARD | PAGE_READONLY, // MM_GUARDPAGE | MM_READONLY
    PAGE_GUARD | PAGE_EXECUTE_READ, // MM_GUARDPAGE | MM_EXECUTE
    PAGE_GUARD | PAGE_EXECUTE_READ, // MM_GUARDPAGE | MM_EXECUTE_READ
    PAGE_GUARD | PAGE_READWRITE, // MM_GUARDPAGE | MM_READWRITE
    PAGE_GUARD | PAGE_WRITECOPY, // MM_GUARDPAGE | MM_WRITECOPY
    PAGE_GUARD | PAGE_EXECUTE_READWRITE, // MM_GUARDPAGE | MM_EXECUTE_READWRITE
    PAGE_GUARD | PAGE_EXECUTE_WRITECOPY, // MM_GUARDPAGE | MM_EXECUTE_WRITECOPY

    PAGE_NOACCESS, // MM_WRITECOMBINE | MM_INVALID
    PAGE_WRITECOMBINE | PAGE_READONLY, // MM_WRITECOMBINE | MM_READONLY
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ, // MM_WRITECOMBINE | MM_EXECUTE
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READ, // MM_WRITECOMBINE | MM_EXECUTE_READ
    PAGE_WRITECOMBINE | PAGE_READWRITE, // MM_WRITECOMBINE | MM_READWRITE
    PAGE_WRITECOMBINE | PAGE_WRITECOPY, // MM_WRITECOMBINE | MM_WRITECOPY
    PAGE_WRITECOMBINE | PAGE_EXECUTE_READWRITE, // MM_WRITECOMBINE | MM_EXECUTE_READWRITE
    PAGE_WRITECOMBINE | PAGE_EXECUTE_WRITECOPY, // MM_WRITECOMBINE | MM_EXECUTE_WRITECOPY
};

MM_SYSTEMSIZE
NTAPI
MmQuerySystemSize(VOID)
{
    /* Return the low, medium or high memory system type */
    return MmLargeSystem;
}

void
MmZeroPageThread()
{
    UNIMPLEMENTED;
    __debugbreak();
}

VOID
NTAPI
MmProbeAndLockPages(
    PMDLX MemoryDescriptorList,
    KPROCESSOR_MODE AccessMode,
    LOCK_OPERATION Operation)
{
    UNIMPLEMENTED;
    __debugbreak();
}

VOID
NTAPI
MmUnlockPages(
    PMDLX MemoryDescriptorList)
{
    UNIMPLEMENTED;
    __debugbreak();
}

NTSTATUS
NTAPI
MmSessionCreate (
    OUT PULONG SessionId)
{
    *SessionId = 0;
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
MmSessionDelete (
    IN ULONG SessionId)
{
    UNIMPLEMENTED;
    return STATUS_SUCCESS;
}

ULONG
NTAPI
MmGetSessionId(
    IN PEPROCESS Process)
{
    //UNIMPLEMENTED;
    return 0;
}

ULONG
NTAPI
MmGetSessionIdEx(IN PEPROCESS Process)
{
    //UNIMPLEMENTED;
    return 0;
}

ULONG
NTAPI
MmGetSessionLocaleId(VOID)
{
    PEPROCESS Process;
    PAGED_CODE();

    /* Get the current process and check if it's the session leader */
    Process = PsGetCurrentProcess();
    if ((Process->Session != NULL) && Process->Vm.Flags.SessionLeader)
    {
        /* return the session Locale ID */
        __debugbreak();
        //return ((PMM_SESSION_SPACE)Process->Session)->LocaleId;
    }

    /* Not a session leader, return the default locate */
    return PsDefaultThreadLocaleId;
}

PVOID
NTAPI
MmAllocateContiguousMemory(
    _In_ SIZE_T NumberOfBytes,
    _In_ PHYSICAL_ADDRESS HighestAcceptableAddress)
{
    UNIMPLEMENTED;
    __debugbreak();
    return NULL;
}

VOID
NTAPI
MmFreeContiguousMemory(
    _In_ PVOID BaseAddress)
{
    UNIMPLEMENTED;
    __debugbreak();
}

NTSTATUS
NTAPI
MmAccessFault(
    IN BOOLEAN StoreInstruction,
    IN PVOID Address,
    IN KPROCESSOR_MODE Mode,
    IN PVOID TrapInformation)
{
    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_ACCESS_VIOLATION;
}

ULONG
NTAPI
MmGetPageProtect (
    _In_ PEPROCESS Process,
    _In_ PVOID Address)
{
    UNIMPLEMENTED;
    return 0;
}

VOID
NTAPI
MmBuildMdlForNonPagedPool (
    IN PMDL Mdl)
{
    PPFN_NUMBER MdlPages, EndPage;
    ULONG Vpn, PageCount;
    PVOID Base;

    // Sanity checks
    ASSERT(Mdl->ByteCount != 0);
    ASSERT((Mdl->MdlFlags & (MDL_PAGES_LOCKED |
                             MDL_MAPPED_TO_SYSTEM_VA |
                             MDL_SOURCE_IS_NONPAGED_POOL |
                             MDL_PARTIAL)) == 0);

    // We know the MDL isn't associated to a process now
    Mdl->Process = NULL;

    // Get page and VA information
    MdlPages = (PPFN_NUMBER)(Mdl + 1);
    Base = Mdl->StartVa;

    // Set the system address and now get the page count
    Mdl->MappedSystemVa = (PVOID)((ULONG_PTR)Base + Mdl->ByteOffset);
    PageCount = ADDRESS_AND_SIZE_TO_SPAN_PAGES(Mdl->MappedSystemVa,
                                               Mdl->ByteCount);
    ASSERT(PageCount != 0);
    EndPage = MdlPages + PageCount;

    // Loop the pages
    Vpn = AddressToVpn(Base);
    do
    {
        // Write the VPN
        *MdlPages++ = Vpn;
    } while (MdlPages < EndPage);

    // Set the nonpaged pool flag
    Mdl->MdlFlags |= MDL_SOURCE_IS_NONPAGED_POOL;

    // Check if this is an I/O mapping
    //if (!MiGetPfnEntry(Pfn)) Mdl->MdlFlags |= MDL_IO_SPACE;
}

NTSTATUS
NTAPI
MmAdjustWorkingSetSize(IN SIZE_T WorkingSetMinimumInBytes,
                       IN SIZE_T WorkingSetMaximumInBytes,
                       IN ULONG SystemCache,
                       IN BOOLEAN IncreaseOkay)
{
    UNIMPLEMENTED;
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS
NTAPI
MmCommitSessionMappedView(IN PVOID MappedBase,
                          IN SIZE_T ViewSize)
{
    UNIMPLEMENTED;
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS 
NTAPI
NtCreatePagingFile(
    IN PUNICODE_STRING FileName,
    IN PLARGE_INTEGER InitialSize,
    IN PLARGE_INTEGER MaximumSize,
    IN ULONG Reserved)
{
    UNIMPLEMENTED;
    return STATUS_SUCCESS;
}

extern unsigned int __i386_virtual_cr3;

void __hack_writecr3(const unsigned int Value)
{
    //DbgPrint("__hack_writecr3: %p -> %p\n", (PVOID)__i386_virtual_cr3, (PVOID)Value);
    if (Value != __i386_virtual_cr3)
    {
        EalDbgPrint("__hack_writecr3: %p -> %p\n", (PVOID)__i386_virtual_cr3, (PVOID)Value);
        EalSwitchProcessAddressSpace((PVOID)__i386_virtual_cr3, (PVOID)Value);
        __i386_virtual_cr3 = Value;
    }
}


// for GCC, invoked when a pure virtual function is called
void
__cxa_pure_virtual ()
{
    KeBugCheck(0);
}

// Versions of gcc/g++ after 3.0 (approx.), when configured for Linux
// native development (specifically, --with-__cxa_enable), have
// additional dependencies related to the destructors for static
// objects. When compiling C++ code with static objects the compiler
// inserts a call to __cxa_atexit() with __dso_handle as one of the
// arguments. __cxa_atexit() would normally be provided by glibc, and
// __dso_handle is part of crtstuff.c. Synthetic target applications
// are linked rather differently, so either a differently-configured
// compiler is needed or dummy versions of these symbols should be
// provided. If these symbols are not actually used then providing
// them is still harmless, linker garbage collection will remove them.

void
__cxa_atexit(void (*arg1)(void*), void* arg2, void* arg3)
{
//    KeBugCheck(0);
}

void*   __dso_handle = (void*) &__dso_handle;

void * __gxx_personality_v0 = 0;
void * _Unwind_Resume = 0;

}; // extern "C"
}; // namespace Mm

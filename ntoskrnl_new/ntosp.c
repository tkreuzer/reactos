
#define PEProcessToPKProcess(P) ((PKPROCESS)P)

#if defined(_M_AMD64)

#ifdef __cplusplus
extern "C" {
#endif

__forceinline
PKTHREAD
KeGetCurrentThread (
    VOID
    )
{
    return (struct _KTHREAD *)__readgsqword(0x188);
}

#ifdef __cplusplus
}
#endif

#endif // defined(_M_AMD64)

#if defined(_M_IX86) || defined(_M_ARM) || defined(_M_ARM64)
NTSYSAPI
PKTHREAD
NTAPI
KeGetCurrentThread(
    VOID
    );
#endif // defined(_M_IX86) || defined(_M_ARM) || defined(_M_ARM64)


_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryElevationFlags (
    _Out_ PRTL_ELEVATION_FLAGS Flags
    );

__drv_maxIRQL(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlStringFromGUIDEx(
    __in REFGUID Guid,
    __inout PUNICODE_STRING GuidString,
    __in BOOLEAN Allocate
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryPackageIdentity (
    _In_ PVOID TokenObject,
    _Out_writes_bytes_to_(*PackageSize, *PackageSize) PWSTR PackageFullName,
    _Inout_ PSIZE_T PackageSize,
    _Out_writes_bytes_to_opt_(*AppIdSize, *AppIdSize) PWSTR AppId,
    _Inout_opt_ PSIZE_T AppIdSize,
    _Out_opt_ PBOOLEAN Packaged
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryPackageIdentityEx (
    _In_ PVOID TokenObject,
    _Out_writes_bytes_to_(*PackageSize, *PackageSize) PWSTR PackageFullName,
    _Inout_ PSIZE_T PackageSize,
    _Out_writes_bytes_to_opt_(*AppIdSize, *AppIdSize) PWSTR AppId,
    _Inout_opt_ PSIZE_T AppIdSize,
    _Out_opt_ LPGUID DynamicId,
    _Out_opt_ PULONG64 Flags
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryPackageClaims (
    _In_ PVOID TokenObject,
    _Out_writes_bytes_to_opt_(*PackageSize, *PackageSize) PWSTR PackageFullName,
    _Inout_opt_ PSIZE_T PackageSize,
    _Out_writes_bytes_to_opt_(*AppIdSize, *AppIdSize) PWSTR AppId,
    _Inout_opt_ PSIZE_T AppIdSize,
    _Out_opt_ LPGUID DynamicId,
    _Out_opt_ PPS_PKG_CLAIM PkgClaim
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlIsUntrustedObject (
    _In_opt_ HANDLE Handle,
    _In_opt_ PVOID Object,
    _Out_ PBOOLEAN UntrustedObject
    );

NTSYSAPI
ULONG
NTAPI
RtlQueryValidationRunlevel (
    _In_opt_ PCUNICODE_STRING ComponentName
    );

typedef enum _EMULATOR_PORT_ACCESS_TYPE {
    Uchar,
    Ushort,
    Ulong
} EMULATOR_PORT_ACCESS_TYPE, *PEMULATOR_PORT_ACCESS_TYPE;

#define EMULATOR_READ_ACCESS    0x01
#define EMULATOR_WRITE_ACCESS   0x02

typedef struct _EMULATOR_ACCESS_ENTRY {
    ULONG BasePort;
    ULONG NumConsecutivePorts;
    EMULATOR_PORT_ACCESS_TYPE AccessType;
    UCHAR AccessMode;
    UCHAR StringSupport;
    PVOID Routine;
} EMULATOR_ACCESS_ENTRY, *PEMULATOR_ACCESS_ENTRY;

typedef
NTSTATUS
(*PDRIVER_IO_PORT_UCHAR ) (
    IN ULONG_PTR Context,
    IN ULONG Port,
    IN UCHAR AccessMode,
    IN OUT PUCHAR Data
    );

typedef
NTSTATUS
(*PDRIVER_IO_PORT_UCHAR_STRING ) (
    IN ULONG_PTR Context,
    IN ULONG Port,
    IN UCHAR AccessMode,
    IN OUT PUCHAR Data,
    IN ULONG DataLength
    );

typedef
NTSTATUS
(*PDRIVER_IO_PORT_USHORT ) (
    IN ULONG_PTR Context,
    IN ULONG Port,
    IN UCHAR AccessMode,
    IN OUT PUSHORT Data
    );

typedef
NTSTATUS
(*PDRIVER_IO_PORT_USHORT_STRING ) (
    IN ULONG_PTR Context,
    IN ULONG Port,
    IN UCHAR AccessMode,
    IN OUT PUSHORT Data,
    IN ULONG DataLength
    );

typedef
NTSTATUS
(*PDRIVER_IO_PORT_ULONG ) (
    IN ULONG_PTR Context,
    IN ULONG Port,
    IN UCHAR AccessMode,
    IN OUT PULONG Data
    );

typedef
NTSTATUS
(*PDRIVER_IO_PORT_ULONG_STRING ) (
    IN ULONG_PTR Context,
    IN ULONG Port,
    IN UCHAR AccessMode,
    IN OUT PULONG Data,
    IN ULONG DataLength
    );

struct _NPAGED_LOOKASIDE_LIST;

typedef struct _PP_LOOKASIDE_LIST {
    struct _GENERAL_LOOKASIDE *P;
    struct _GENERAL_LOOKASIDE *L;
} PP_LOOKASIDE_LIST, *PPP_LOOKASIDE_LIST;

#define POOL_SMALL_LISTS 32

#define POOL_TAGGING 1

#if DBG
#define IF_DEBUG if (TRUE)
#else
#define IF_DEBUG if (FALSE)
#endif

#if DEVL
extern ULONG NtGlobalFlag;
#define IF_NTOS_DEBUG(FlagName) \
    if (NtGlobalFlag & (FLG_ ## FlagName))
#else
#define IF_NTOS_DEBUG(FlagName) if(FALSE)
#endif

typedef _Enum_is_bitflag_ enum _POOL_TYPE POOL_TYPE;

typedef
_IRQL_requires_same_
_Function_class_(ALLOCATE_FUNCTION)
PVOID
ALLOCATE_FUNCTION (
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag
    );
typedef ALLOCATE_FUNCTION *PALLOCATE_FUNCTION;

typedef
_IRQL_requires_same_
_Function_class_(FREE_FUNCTION)
VOID
FREE_FUNCTION (
    _In_ __drv_freesMem(Mem) PVOID Buffer
    );
typedef FREE_FUNCTION *PFREE_FUNCTION;

typedef struct _LOOKASIDE_LIST_EX *PLOOKASIDE_LIST_EX;

typedef
_IRQL_requires_same_
_Function_class_(ALLOCATE_FUNCTION_EX)
PVOID
ALLOCATE_FUNCTION_EX (
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag,
    _Inout_ PLOOKASIDE_LIST_EX Lookaside
    );
typedef ALLOCATE_FUNCTION_EX *PALLOCATE_FUNCTION_EX;

typedef
_IRQL_requires_same_
_Function_class_(FREE_FUNCTION_EX)
VOID
FREE_FUNCTION_EX (
    _In_ __drv_freesMem(Mem) PVOID Buffer,
    _Inout_ PLOOKASIDE_LIST_EX Lookaside
    );
typedef FREE_FUNCTION_EX *PFREE_FUNCTION_EX;

#if !defined(_WIN64) && (defined(_NTDDK_) || defined(_NTIFS_) || defined(_NDIS_))
#define LOOKASIDE_ALIGN
#else
#define LOOKASIDE_ALIGN DECLSPEC_CACHEALIGN
#endif

typedef struct LOOKASIDE_ALIGN _GENERAL_LOOKASIDE {
    GENERAL_LOOKASIDE_LAYOUT
} GENERAL_LOOKASIDE;

typedef GENERAL_LOOKASIDE *PGENERAL_LOOKASIDE;

typedef struct _GENERAL_LOOKASIDE_POOL {
    GENERAL_LOOKASIDE_LAYOUT
} GENERAL_LOOKASIDE_POOL, *PGENERAL_LOOKASIDE_POOL;

#define LOOKASIDE_CHECK(f)  \
    C_ASSERT(FIELD_OFFSET(GENERAL_LOOKASIDE,f)==FIELD_OFFSET(GENERAL_LOOKASIDE_POOL,f))

LOOKASIDE_CHECK(TotalFrees);
LOOKASIDE_CHECK(Tag);
LOOKASIDE_CHECK(Future);

struct _KAPC;

typedef
_Function_class_(KNORMAL_ROUTINE)
_IRQL_requires_max_(PASSIVE_LEVEL)
_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
VOID
KNORMAL_ROUTINE (
    _In_opt_ PVOID NormalContext,
    _In_opt_ PVOID SystemArgument1,
    _In_opt_ PVOID SystemArgument2
    );
typedef KNORMAL_ROUTINE *PKNORMAL_ROUTINE;

typedef
_Function_class_(KKERNEL_ROUTINE)
_IRQL_requires_max_(APC_LEVEL)
_IRQL_requires_min_(APC_LEVEL)
_IRQL_requires_(APC_LEVEL)
_IRQL_requires_same_
VOID
KKERNEL_ROUTINE (
    _In_ struct _KAPC *Apc,
    _Inout_ PKNORMAL_ROUTINE *NormalRoutine,
    _Inout_ PVOID *NormalContext,
    _Inout_ PVOID *SystemArgument1,
    _Inout_ PVOID *SystemArgument2
    );
typedef KKERNEL_ROUTINE *PKKERNEL_ROUTINE;

typedef
_Function_class_(KRUNDOWN_ROUTINE)
_IRQL_requires_max_(PASSIVE_LEVEL)
_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
VOID
KRUNDOWN_ROUTINE (
    _In_ struct _KAPC *Apc
    );
typedef KRUNDOWN_ROUTINE *PKRUNDOWN_ROUTINE;

#define ASSERT_APC(E) NT_ASSERT((E)->Type == ApcObject)

typedef struct _KAPC {
    UCHAR Type;
    UCHAR SpareByte0;
    UCHAR Size;
    UCHAR SpareByte1;
    ULONG SpareLong0;
    struct _KTHREAD *Thread;
    LIST_ENTRY ApcListEntry;
    union
    {
        struct
        {
            PKKERNEL_ROUTINE KernelRoutine;
            PKRUNDOWN_ROUTINE RundownRoutine;
            PKNORMAL_ROUTINE NormalRoutine;
        };
        PVOID Reserved[3];
    };
    PVOID NormalContext;
    PVOID SystemArgument1;
    PVOID SystemArgument2;
    CCHAR ApcStateIndex;
    KPROCESSOR_MODE ApcMode;
    BOOLEAN Inserted;
} KAPC, *PKAPC, *PRKAPC;

struct _KDPC;

#define DPC_NORMAL 0
#define DPC_THREADED 1

#define ASSERT_DPC(Object)                                                   \
    NT_ASSERT(((Object)->Type == 0) ||                                       \
              ((Object)->Type == DpcObject) ||                               \
              ((Object)->Type == ThreadedDpcObject))

typedef struct _KDPC
{
    union
    {
        ULONG TargetInfoAsUlong;
        struct
        {
            UCHAR Type;
            UCHAR Importance;
            volatile USHORT Number;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    SINGLE_LIST_ENTRY DpcListEntry;
    KAFFINITY ProcessorHistory;
    PKDEFERRED_ROUTINE DeferredRoutine;
    PVOID DeferredContext;
    PVOID SystemArgument1;
    PVOID SystemArgument2;
    __volatile PVOID DpcData;
} KDPC, *PKDPC, *PRKDPC;

typedef PVOID PKIPI_CONTEXT;

typedef
_Function_class_(KIPI_WORKER)
_IRQL_requires_same_
VOID
KIPI_WORKER (
    _Inout_ PKIPI_CONTEXT PacketContext,
    _In_opt_ PVOID Parameter1,
    _In_opt_ PVOID Parameter2,
    _In_opt_ PVOID Parameter3
    );

typedef KIPI_WORKER *PKIPI_WORKER;

typedef struct _KIPI_COUNTS {
    ULONG Freeze;
    ULONG Packet;
    ULONG DPC;
    ULONG APC;
    ULONG FlushSingleTb;
    ULONG FlushMultipleTb;
    ULONG FlushEntireTb;
    ULONG GenericCall;
    ULONG ChangeColor;
    ULONG SweepDcache;
    ULONG SweepIcache;
    ULONG SweepIcacheRange;
    ULONG FlushIoBuffers;
    ULONG GratuitousDPC;
} KIPI_COUNTS, *PKIPI_COUNTS;

typedef struct _KREQUEST_PACKET {
    PVOID CurrentPacket[3];
    PKIPI_WORKER WorkerRoutine;
} KREQUEST_PACKET, *PKREQUEST_PACKET;

typedef struct _REQUEST_MAILBOX {
    struct _REQUEST_MAILBOX *Next;
    ULONG_PTR RequestSummary;
    KREQUEST_PACKET RequestPacket;
    LONG volatile *NodeTargetCountAddr;
    volatile LONG NodeTargetCount;
} REQUEST_MAILBOX, *PREQUEST_MAILBOX;

C_ASSERT(sizeof(REQUEST_MAILBOX) <= SYSTEM_CACHE_ALIGNMENT_SIZE);

#if defined(_X86_)
#define PAGE_SIZE 0x1000
#define PAGE_SHIFT 12L
#elif defined(_AMD64_)
#define PAGE_SIZE 0x1000
#define PAGE_SHIFT 12L
#elif defined(_ARM64_)
#define PAGE_SIZE 0x1000
#define PAGE_SHIFT 12L
#elif defined(_ARM_)
#define PAGE_SIZE 0x1000
#define PAGE_SHIFT 12L
#endif


typedef _Readable_bytes_(_Inexpressible_(polymorphism)) MDL *PMDLX;

#define MDL_MAPPED_TO_SYSTEM_VA     0x0001
#define MDL_PAGES_LOCKED            0x0002
#define MDL_SOURCE_IS_NONPAGED_POOL 0x0004
#define MDL_ALLOCATED_FIXED_SIZE    0x0008
#define MDL_PARTIAL                 0x0010
#define MDL_PARTIAL_HAS_BEEN_MAPPED 0x0020
#define MDL_IO_PAGE_READ            0x0040
#define MDL_WRITE_OPERATION         0x0080
#define MDL_LOCKED_PAGE_TABLES      0x0100
#define MDL_PARENT_MAPPED_SYSTEM_VA MDL_LOCKED_PAGE_TABLES
#define MDL_FREE_EXTRA_PTES         0x0200
#define MDL_DESCRIBES_AWE           0x0400
#define MDL_IO_SPACE                0x0800
#define MDL_NETWORK_HEADER          0x1000
#define MDL_MAPPING_CAN_FAIL        0x2000
#define MDL_PAGE_CONTENTS_INVARIANT 0x4000
#define MDL_ALLOCATED_MUST_SUCCEED  MDL_PAGE_CONTENTS_INVARIANT
#define MDL_INTERNAL                0x8000

#define MDL_MAPPING_FLAGS (MDL_MAPPED_TO_SYSTEM_VA     | \
                           MDL_PAGES_LOCKED            | \
                           MDL_SOURCE_IS_NONPAGED_POOL | \
                           MDL_PARTIAL_HAS_BEEN_MAPPED | \
                           MDL_PARENT_MAPPED_SYSTEM_VA | \
                           MDL_SYSTEM_VA               | \
                           MDL_IO_SPACE )

#if defined(_PREFAST_)

_IRQL_requires_max_(APC_LEVEL)
void __PREfastPagedCode(void);

void __PREfastPagedCodeLocked(void);
#define PAGED_CODE()        __PREfastPagedCode();
#define PAGED_CODE_LOCKED() __PREfastPagedCodeLocked();

#elif DBG

#if (NTDDI_VERSION >= NTDDI_VISTA)
#define PAGED_ASSERT( exp ) NT_ASSERT( exp )
#else
#define PAGED_ASSERT( exp ) ASSERT( exp )
#endif

#define PAGED_CODE() PAGED_ASSERT(KeGetCurrentIrql() <= APC_LEVEL);

#define PAGED_CODE_LOCKED() NOP_FUNCTION;

#else

#define PAGED_CODE()        NOP_FUNCTION;
#define PAGED_CODE_LOCKED() NOP_FUNCTION;

#endif

typedef struct _SECURITY_CLIENT_CONTEXT {
    SECURITY_QUALITY_OF_SERVICE SecurityQos;
    PACCESS_TOKEN ClientToken;
    BOOLEAN DirectlyAccessClientToken;
    BOOLEAN DirectAccessEffectiveOnly;
    BOOLEAN ServerIsRemote;
    TOKEN_CONTROL ClientTokenControl;
    } SECURITY_CLIENT_CONTEXT, *PSECURITY_CLIENT_CONTEXT;

#if defined(_NTSYSTEM_)
#define NTKERNELAPI
#else
#define NTKERNELAPI DECLSPEC_IMPORT     // wdm ntddk nthal ntndis ntifs
#endif

#if defined(_X86_) && !defined(_NTHAL_)
#define _DECL_HAL_KE_IMPORT  DECLSPEC_IMPORT
#elif defined(_X86_)
#define _DECL_HAL_KE_IMPORT
#else
#define _DECL_HAL_KE_IMPORT NTKERNELAPI
#endif

#define NTHALAPI DECLSPEC_IMPORT

#if defined(_X86_)
#define KENCODED_TIMER_PROCESSOR        1       // Timer processor is encoded in header
#endif

#define TIMER_TOLERABLE_DELAY_BITS      6
#define TIMER_EXPIRED_INDEX_BITS        6
#define TIMER_PROCESSOR_INDEX_BITS      5

typedef struct _DISPATCHER_HEADER
{
    union
    {
        union
        {
            volatile LONG Lock;
            LONG LockNV;
        } DUMMYUNIONNAME;

        struct
        {                            // Events, Semaphores, Gates, etc.
            UCHAR Type;                     // All (accessible via KOBJECT_TYPE)
            UCHAR Signalling;
            UCHAR Size;
            UCHAR Reserved1;
        } DUMMYSTRUCTNAME;

        struct
        {                            // Timer
            UCHAR TimerType;
            union
            {
                UCHAR TimerControlFlags;
                struct
                {
                    UCHAR Absolute : 1;
                    UCHAR Wake : 1;
                    UCHAR EncodedTolerableDelay : TIMER_TOLERABLE_DELAY_BITS;
                } DUMMYSTRUCTNAME;
            };

            UCHAR Hand;
            union
            {
                UCHAR TimerMiscFlags;
                struct
                {
#if !defined(KENCODED_TIMER_PROCESSOR)
                    UCHAR Index : TIMER_EXPIRED_INDEX_BITS;
#else
                    UCHAR Index : 1;
                    UCHAR Processor : TIMER_PROCESSOR_INDEX_BITS;
#endif
                    UCHAR Inserted : 1;
                    volatile UCHAR Expired : 1;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;
        } DUMMYSTRUCTNAME2;

        struct
        {
            UCHAR Timer2Type;
            union
            {
                UCHAR Timer2Flags;
                struct
                {
                    UCHAR Timer2Inserted : 1;
                    UCHAR Timer2Expiring : 1;
                    UCHAR Timer2CancelPending : 1;
                    UCHAR Timer2SetPending : 1;
                    UCHAR Timer2Running : 1;
                    UCHAR Timer2Disabled : 1;
                    UCHAR Timer2ReservedFlags : 2;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;

            UCHAR Timer2Reserved1;
            UCHAR Timer2Reserved2;
        } DUMMYSTRUCTNAME3;

        struct
        {
            UCHAR QueueType;
            union
            {
                UCHAR QueueControlFlags;
                struct
                {
                    UCHAR Abandoned : 1;
                    UCHAR DisableIncrement : 1;
                    UCHAR QueueReservedControlFlags : 6;
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;

            UCHAR QueueSize;
            UCHAR QueueReserved;
        } DUMMYSTRUCTNAME4;

        struct
        {
            UCHAR ThreadType;
            UCHAR ThreadReserved;
            union
            {
                UCHAR ThreadControlFlags;
                struct
                {
                    UCHAR CycleProfiling : 1;
                    UCHAR CounterProfiling : 1;
                    UCHAR GroupScheduling : 1;
                    UCHAR AffinitySet : 1;
                    UCHAR Tagged : 1;
                    UCHAR EnergyProfiling: 1;
#if !defined(_X86_)
                    UCHAR ThreadReservedControlFlags : 2;
#else
                    UCHAR Instrumented : 1;
                    UCHAR ThreadReservedControlFlags : 1;
#endif
                } DUMMYSTRUCTNAME;
            } DUMMYUNIONNAME;

            union
            {
                UCHAR DebugActive;
#if !defined(_X86_)
                struct
                {
                    BOOLEAN ActiveDR7 : 1;
                    BOOLEAN Instrumented : 1;
                    BOOLEAN Minimal : 1;
                    BOOLEAN Reserved4 : 3;
                    BOOLEAN UmsScheduled : 1;
                    BOOLEAN UmsPrimary : 1;
                } DUMMYSTRUCTNAME;
#endif
            } DUMMYUNIONNAME2;
        } DUMMYSTRUCTNAME5;

        struct
        {
            UCHAR MutantType;
            UCHAR MutantSize;
            BOOLEAN DpcActive;
            UCHAR MutantReserved;
        } DUMMYSTRUCTNAME6;
    } DUMMYUNIONNAME;

    LONG SignalState;                   // Object lock
    LIST_ENTRY WaitListHead;            // Object lock
} DISPATCHER_HEADER, *PDISPATCHER_HEADER;

#define DEBUG_ACTIVE_RESERVED_BIT       5   // Offset chosen due to x86 debug mask


typedef struct _KGATE
{
    DISPATCHER_HEADER Header;
} KGATE, *PKGATE;

typedef struct _KTIMER
{
    DISPATCHER_HEADER Header;
    ULARGE_INTEGER DueTime;
    LIST_ENTRY TimerListEntry;
    struct _KDPC *Dpc;
#if !defined(KENCODED_TIMER_PROCESSOR)
    ULONG Processor;
#endif
    ULONG Period;
} KTIMER, *PKTIMER, *PRKTIMER;

#define KTIMER_ACTUAL_LENGTH                                                \
    (FIELD_OFFSET(KTIMER, Period) + sizeof(LONG))

typedef struct _FAST_MUTEX
{
    LONG Count;
    PVOID Owner;
    ULONG Contention;
    KEVENT Event;
    ULONG OldIrql;
} FAST_MUTEX, *PFAST_MUTEX, KGUARDED_MUTEX, *PKGUARDED_MUTEX;


/#if defined(_X86_)
#define IMAGE_FILE_MACHINE_NATIVE   0x014c

#define SANITIZE_SEG(segCS, mode) (\
    ((mode) == KernelMode ? \
        ((0x00000000L) | ((segCS) & 0xfffc)) : \
        ((0x00000003L) | ((segCS) & 0xffff))))

#define SANITIZE_FLAGS(eFlags, mode) (\
    ((mode) == KernelMode ? \
        ((0x00000000L) | ((eFlags) & 0x003f0fd7)) : \
        ((EFLAGS_INTERRUPT_MASK) | ((eFlags) & EFLAGS_USER_SANITIZE))))

#define DR6_LEGAL   0x0000e00f
#define DR7_LEGAL   0xffff0155
#define DR7_OVERRIDE_V 0x04
#define DR_MASK(Bit) (((UCHAR)(1UL << (Bit))))
#define DR_REG_MASK (DR_MASK(0) | DR_MASK(1) | DR_MASK(2) | DR_MASK(3) | DR_MASK(6))
#define DR_RESERVED_BITS (DR_MASK (DEBUG_ACTIVE_RESERVED_BIT))
C_ASSERT ((DR_RESERVED_BITS & DR_REG_MASK) == 0);
#define DR_VALID_MASK (DR_REG_MASK | DR_MASK (7) | DR_MASK (DR7_OVERRIDE_V) | DR_RESERVED_BITS)
#define DR7_MASK_SHIFT 16
#define DR7_OVERRIDE_MASK ((0x0FUL) << DR7_MASK_SHIFT)
#define DR7_RESERVED_MASK 0x0000DC00    // Bits 10-12, 14-15 are reserved
#define DR7_ACTIVE  0x00000055          // If any of these bits are set, a Dr is active

C_ASSERT (sizeof(BOOLEAN) == sizeof(UCHAR));
C_ASSERT ((((ULONG)DR_VALID_MASK) & ~((ULONG)((UCHAR)0xFF))) == 0);
C_ASSERT ((DR7_ACTIVE & DR7_OVERRIDE_MASK) == 0);
C_ASSERT ((DR7_RESERVED_MASK & DR7_OVERRIDE_MASK) == 0);
C_ASSERT ((DR7_OVERRIDE_MASK & DR7_LEGAL) == DR7_OVERRIDE_MASK);
C_ASSERT ((DR7_RESERVED_MASK & DR7_LEGAL) == 0);

#define SANITIZE_DR6(Dr6, mode) (((Dr6) & DR6_LEGAL))
#define SANITIZE_DR7(Dr7, mode) (((Dr7) & DR7_LEGAL))
#define SANITIZE_DRADDR(DrReg, mode) (          \
    (mode) == KernelMode ?                      \
        (DrReg) :                               \
        (((PVOID)DrReg <= MM_HIGHEST_USER_ADDRESS) ?   \
            (DrReg) :                           \
            (0)                                 \
        )                                       \
    )

extern ULONG KiMxCsrMask;

#define SANITIZE_MXCSR(_mxcsr_) ((_mxcsr_) & KiMxCsrMask)

typedef struct _KNONVOLATILE_CONTEXT_POINTERS {
    ULONG   Junk;
} KNONVOLATILE_CONTEXT_POINTERS,  *PKNONVOLATILE_CONTEXT_POINTERS;

typedef struct _KSTACK_SWITCH_FRAME {
    ULONG Edi;
    ULONG Esi;
    ULONG Ebx;
    ULONG Ebp;
} KSTACK_SWITCH_FRAME, *PKSTACK_SWITCH_FRAME;

typedef struct _KCALLOUT_FRAME
{
    ULONG   InStk;          // saved initial stack address
    ULONG   TrFr;           // saved callback trap frame
    ULONG   CbStk;          // saved callback stack address
    ULONG   Edi;            // saved nonvolatile registers
    ULONG   Esi;            //
    ULONG   Ebx;            //
    ULONG   Ebp;            //
    ULONG   Ret;            // saved return address
    ULONG   OutBf;          // address to store output buffer
    ULONG   OutLn;          // address to store output length
} KCALLOUT_FRAME;

typedef KCALLOUT_FRAME *PKCALLOUT_FRAME;

typedef struct _KSWITCHFRAME
{
    ULONG   ExceptionList;
    ULONG   ApcBypassDisable;
    ULONG   RetAddr;
} KSWITCHFRAME, *PKSWITCHFRAME;

#define I386_80387_NP_VECTOR    0x07    // trap 7 when hardware not present

typedef struct _PROCESS_IO_PORT_HANDLER_INFORMATION
{
    BOOLEAN Install;            // true if handlers to be installed
    ULONG NumEntries;
    ULONG Context;
    PEMULATOR_ACCESS_ENTRY EmulatorAccessEntries;
} PROCESS_IO_PORT_HANDLER_INFORMATION, *PPROCESS_IO_PORT_HANDLER_INFORMATION;

typedef struct _VDM_IO_HANDLER_FUNCTIONS
{
    PDRIVER_IO_PORT_ULONG  UlongIo;
    PDRIVER_IO_PORT_ULONG_STRING UlongStringIo;
    PDRIVER_IO_PORT_USHORT UshortIo[2];
    PDRIVER_IO_PORT_USHORT_STRING UshortStringIo[2];
    PDRIVER_IO_PORT_UCHAR UcharIo[4];
    PDRIVER_IO_PORT_UCHAR_STRING UcharStringIo[4];
} VDM_IO_HANDLER_FUNCTIONS, *PVDM_IO_HANDLER_FUNCTIONS;

typedef struct _VDM_IO_HANDLER {
    struct _VDM_IO_HANDLER *Next;
    ULONG PortNumber;
    VDM_IO_HANDLER_FUNCTIONS IoFunctions[2];
} VDM_IO_HANDLER, *PVDM_IO_HANDLER;

typedef ULONG PFN_COUNT;

typedef LONG SPFN_NUMBER, *PSPFN_NUMBER;
typedef ULONG PFN_NUMBER, *PPFN_NUMBER;

_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
_DECL_HAL_KE_IMPORT
KIRQL
KeRaiseIrqlToDpcLevel (
    VOID
    );

_IRQL_saves_
_DECL_HAL_KE_IMPORT
KIRQL
KeRaiseIrqlToSynchLevel (
    VOID
    );

#define MODE_MASK    1

#define KeGetDcacheFillSize() 1L

#define ExAcquireSpinLock(Lock, OldIrql) KeAcquireSpinLock((Lock), (OldIrql))
#define ExReleaseSpinLock(Lock, OldIrql) KeReleaseSpinLock((Lock), (OldIrql))
#define ExAcquireSpinLockAtDpcLevel(Lock) KeAcquireSpinLockAtDpcLevel(Lock)
#define ExReleaseSpinLockFromDpcLevel(Lock) KeReleaseSpinLockFromDpcLevel(Lock)

typedef struct _HARDWARE_PTE
{
    union
    {
        struct
        {
            ULONGLONG Valid : 1;
            ULONGLONG Write : 1;
            ULONGLONG Owner : 1;
            ULONGLONG WriteThrough : 1;
            ULONGLONG CacheDisable : 1;
            ULONGLONG Accessed : 1;
            ULONGLONG Dirty : 1;
            ULONGLONG LargePage : 1;
            ULONGLONG Global : 1;
            ULONGLONG CopyOnWrite : 1;
            ULONGLONG Prototype : 1;
            ULONGLONG reserved0 : 1;
            ULONGLONG PageFrameNumber : 26;
            ULONGLONG reserved1 : 26;
        };
        struct
        {
            ULONG LowPart;
            ULONG HighPart;
        };
    };
} HARDWARE_PTE, *PHARDWARE_PTE;

typedef struct _KGDTENTRY
{
    USHORT  LimitLow;
    USHORT  BaseLow;
    union
    {
        struct
        {
            UCHAR   BaseMid;
            UCHAR   Flags1;     // Declare as bytes to avoid alignment
            UCHAR   Flags2;     // Problems.
            UCHAR   BaseHi;
        } Bytes;
        struct
        {
            ULONG   BaseMid : 8;
            ULONG   Type : 5;
            ULONG   Dpl : 2;
            ULONG   Pres : 1;
            ULONG   LimitHi : 4;
            ULONG   Sys : 1;
            ULONG   Reserved_0 : 1;
            ULONG   Default_Big : 1;
            ULONG   Granularity : 1;
            ULONG   BaseHi : 8;
        } Bits;
    } HighWord;
} KGDTENTRY, *PKGDTENTRY;

typedef struct _KIDTENTRY
{
   USHORT Offset;
   USHORT Selector;
   USHORT Access;
   USHORT ExtendedOffset;
} KIDTENTRY;

typedef KIDTENTRY *PKIDTENTRY;

#define INT_DIRECTION_MAP_SIZE   32
typedef UCHAR   KINT_DIRECTION_MAP[INT_DIRECTION_MAP_SIZE];

#define IOPM_COUNT      1
#define IO_ACCESS_MAP_NONE 0
#define IOPM_SIZE           8192
#define PIOPM_SIZE          8196

typedef UCHAR   KIO_ACCESS_MAP[IOPM_SIZE];

typedef KIO_ACCESS_MAP *PKIO_ACCESS_MAP;

typedef struct _KiIoAccessMap
{
    KINT_DIRECTION_MAP DirectionMap;
    UCHAR IoMap[PIOPM_SIZE];
} KIIO_ACCESS_MAP;

typedef struct _KTSS
{
    USHORT  Backlink;
    USHORT  Reserved0;
    ULONG   Esp0;
    USHORT  Ss0;
    USHORT  Reserved1;
    ULONG   NotUsed1[4];
    ULONG   CR3;
    ULONG   Eip;
    ULONG   EFlags;
    ULONG   Eax;
    ULONG   Ecx;
    ULONG   Edx;
    ULONG   Ebx;
    ULONG   Esp;
    ULONG   Ebp;
    ULONG   Esi;
    ULONG   Edi;
    USHORT  Es;
    USHORT  Reserved2;
    USHORT  Cs;
    USHORT  Reserved3;
    USHORT  Ss;
    USHORT  Reserved4;
    USHORT  Ds;
    USHORT  Reserved5;
    USHORT  Fs;
    USHORT  Reserved6;
    USHORT  Gs;
    USHORT  Reserved7;
    USHORT  LDT;
    USHORT  Reserved8;
    USHORT  Flags;
    USHORT  IoMapBase;
    KIIO_ACCESS_MAP IoMaps[IOPM_COUNT];
    KINT_DIRECTION_MAP IntDirectionMap;
} KTSS, *PKTSS;

#define KiComputeIopmOffset(MapNumber)          \
    (MapNumber == IO_ACCESS_MAP_NONE) ?         \
        (USHORT)(sizeof(KTSS)) :                    \
        (USHORT)(FIELD_OFFSET(KTSS, IoMaps[MapNumber-1].IoMap))

typedef struct _DESCRIPTOR
{
    USHORT  Pad;
    USHORT  Limit;
    ULONG   Base;
} KDESCRIPTOR, *PKDESCRIPTOR;

#include <pshpack4.h>
typedef struct _KSPECIAL_REGISTERS
{
    ULONG Cr0;
    ULONG Cr2;
    ULONG Cr3;
    ULONG Cr4;
    ULONG KernelDr0;
    ULONG KernelDr1;
    ULONG KernelDr2;
    ULONG KernelDr3;
    ULONG KernelDr6;
    ULONG KernelDr7;
    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;
    USHORT Tr;
    USHORT Ldtr;
    ULONG64 Xcr0;
    ULONG ExceptionList;
    ULONG Reserved[3];
} KSPECIAL_REGISTERS, *PKSPECIAL_REGISTERS;
#include <poppack.h>

typedef struct _KPROCESSOR_STATE
{
    struct _CONTEXT ContextFrame;
    struct _KSPECIAL_REGISTERS SpecialRegisters;
} KPROCESSOR_STATE, *PKPROCESSOR_STATE;

typedef enum
{
    CPU_NONE,                // 0
    CPU_INTEL,               // 1
    CPU_AMD,                 // 2
    CPU_CYRIX,               // 3
    CPU_TRANSMETA,           // 4
    CPU_VIA,                 // 5
    CPU_CENTAUR = CPU_VIA,   // 5 (alias for CPU_VIA)
    CPU_RISE,                // 6
    CPU_UNKNOWN              // 7
} CPU_VENDORS;

#define MAXIMUM_CACHES 5

typedef struct _KPRCB
{
    USHORT MinorVersion;
    USHORT MajorVersion;
    struct _KTHREAD *CurrentThread;
    struct _KTHREAD *NextThread;
    struct _KTHREAD *IdleThread;
    UCHAR LegacyNumber;
    UCHAR NestingLevel;
    USHORT BuildType;
    CCHAR CpuType;
    CCHAR CpuID;
    union
    {
        USHORT CpuStep;
        struct
        {
            UCHAR CpuStepping;
            UCHAR CpuModel;
        };
    };
    struct _KPROCESSOR_STATE ProcessorState;
    struct _KNODE *ParentNode;
    PSCHAR PriorityState;
    ULONG KernelReserved[14];
    ULONG HalReserved[16];
    ULONG CFlushSize;
    UCHAR CoresPerPhysicalProcessor;
    UCHAR LogicalProcessorsPerCore;
    UCHAR CpuVendor;
    UCHAR PrcbPad0[1];
    ULONG MHz;
    UCHAR GroupIndex;
    UCHAR Group;
    UCHAR PrcbPad05[2];
    KAFFINITY GroupSetMember;
    ULONG Number;
    BOOLEAN ClockOwner;
    union
    {
        UCHAR PendingTickFlags;
        struct
        {
            UCHAR PendingTick:1;
            UCHAR PendingBackupTick:1;
        };
    };
    UCHAR PrcbPad10[6 + 64];
    KSPIN_LOCK_QUEUE LockQueue[LockQueueMaximumLock];
} KPRCB, *PKPRCB, *RESTRICTED_POINTER PRKPRCB;

#define PCR_MINOR_VERSION 1
#define PCR_MAJOR_VERSION 1

typedef struct _KPCR
{
    union
    {
        NT_TIB  NtTib;
        struct
        {
            struct _EXCEPTION_REGISTRATION_RECORD *Used_ExceptionList;
            PVOID Used_StackBase;
            ULONG MxCsr;
            PVOID TssCopy;
            ULONG ContextSwitches;
            KAFFINITY SetMemberCopy;
            PVOID Used_Self;
        };
    };
    struct _KPCR *SelfPcr;              // flat address of this PCR
    struct _KPRCB *Prcb;                // pointer to Prcb
    KIRQL   Irql;                       // do not use 3 bytes after this as
                                        // HALs assume they are zero.
    ULONG   IRR;
    ULONG   IrrActive;
    ULONG   IDR;
    PVOID   KdVersionBlock;
    struct _KIDTENTRY *IDT;
    struct _KGDTENTRY *GDT;
    struct _KTSS      *TSS;
    USHORT  MajorVersion;
    USHORT  MinorVersion;
    KAFFINITY SetMember;
    ULONG   StallScaleFactor;
    UCHAR   SpareUnused;
    UCHAR   Number;
} KPCR, *PKPCR;

#define INTERRUPT_FRAME    0
#define EXCEPTION_FRAME    1
#define SYSCALL_FRAME      2

#define TRAP_FRAME_TYPE(TrapFrame)  (TrapFrame->FrameType)

typedef struct _KTRAP_FRAME
{
    ULONG   DbgEbp;
    ULONG   DbgEip;
    ULONG   DbgArgMark;
    USHORT  TempSegCs;
    UCHAR   Logging;
    UCHAR   FrameType;
    ULONG   TempEsp;
    ULONG   Dr0;
    ULONG   Dr1;
    ULONG   Dr2;
    ULONG   Dr3;
    ULONG   Dr6;
    ULONG   Dr7;
    ULONG   SegGs;
    ULONG   SegEs;
    ULONG   SegDs;
    ULONG   Edx;
    ULONG   Ecx;
    ULONG   Eax;
    UCHAR   PreviousPreviousMode;
    UCHAR   EntropyQueueDpc;
    UCHAR   Reserved[2];
    ULONG   MxCsr;
    PEXCEPTION_REGISTRATION_RECORD ExceptionList;
    ULONG   SegFs;
    ULONG   Edi;
    ULONG   Esi;
    ULONG   Ebx;
    ULONG   Ebp;
    ULONG   ErrCode;
    ULONG   Eip;
    ULONG   SegCs;
    ULONG   EFlags;
    ULONG   HardwareEsp;
    ULONG   HardwareSegSs;
    ULONG   V86Es;
    ULONG   V86Ds;
    ULONG   V86Fs;
    ULONG   V86Gs;
} KTRAP_FRAME;

typedef KTRAP_FRAME *PKTRAP_FRAME;
typedef KTRAP_FRAME *PKEXCEPTION_FRAME;

typedef struct _KXMM_FRAME
{
    M128A Xmm[8];
} KXMM_FRAME, *PKXMM_FRAME;

typedef struct _KFLOATING_SAVE
{
    ULONG   ControlWord;
    ULONG   StatusWord;
    ULONG   ErrorOffset;
    ULONG   ErrorSelector;
    ULONG   DataOffset;
    ULONG   DataSelector;
    ULONG   Spare0;
    ULONG   Spare1;
} KFLOATING_SAVE, *PKFLOATING_SAVE;

typedef union _AMD_L1_CACHE_INFO
{
    ULONG Ulong;
    struct {
        UCHAR LineSize;
        UCHAR LinesPerTag;
        UCHAR Associativity;
        UCHAR Size;
    };
} AMD_L1_CACHE_INFO, *PAMD_L1_CACHE_INFO;

typedef union _AMD_L2_CACHE_INFO
{
    ULONG Ulong;
    struct {
        UCHAR  LineSize;
        UCHAR  LinesPerTag   : 4;
        UCHAR  Associativity : 4;
        USHORT Size;
    };
} AMD_L2_CACHE_INFO, *PAMD_L2_CACHE_INFO;

typedef union _AMD_L3_CACHE_INFO
{
    ULONG Ulong;
    struct {
        UCHAR  LineSize;
        UCHAR  LinesPerTag   : 4;
        UCHAR  Associativity : 4;
        USHORT Reserved : 2;
        USHORT Size : 14;
    };
} AMD_L3_CACHE_INFO, *PAMD_L3_CACHE_INFO;

typedef enum _INTEL_CACHE_TYPE
{
    IntelCacheNull,
    IntelCacheData,
    IntelCacheInstruction,
    IntelCacheUnified,
    IntelCacheRam,
    IntelCacheTrace
} INTEL_CACHE_TYPE;

typedef union INTEL_CACHE_INFO_EAX
{
    ULONG Ulong;
    struct {
        INTEL_CACHE_TYPE Type : 5;
        ULONG Level : 3;
        ULONG SelfInitializing : 1;
        ULONG FullyAssociative : 1;
        ULONG Reserved : 4;
        ULONG ThreadsSharing : 12;
        ULONG ProcessorCores : 6;
    };
} INTEL_CACHE_INFO_EAX, *PINTEL_CACHE_INFO_EAX;

typedef union INTEL_CACHE_INFO_EBX
{
    ULONG Ulong;
    struct {
        ULONG LineSize      : 12;
        ULONG Partitions    : 10;
        ULONG Associativity : 10;
    };
} INTEL_CACHE_INFO_EBX, *PINTEL_CACHE_INFO_EBX;

#define MM_HIGHEST_USER_ADDRESS MmHighestUserAddress
#define MM_SYSTEM_RANGE_START MmSystemRangeStart

#if defined(_LOCAL_COPY_USER_PROBE_ADDRESS_)

#define MM_USER_PROBE_ADDRESS _LOCAL_COPY_USER_PROBE_ADDRESS_

#if defined(__CONVERGED_WIN32K_DRIVER__)
extern DLLBASEEXPORT ULONG _LOCAL_COPY_USER_PROBE_ADDRESS_;
#else
extern ULONG _LOCAL_COPY_USER_PROBE_ADDRESS_;
#endif

#else

#define MM_USER_PROBE_ADDRESS MmUserProbeAddress

#endif

#define MM_KSEG0_BASE       MM_SYSTEM_RANGE_START
#define MM_SYSTEM_SPACE_END 0xFFFFFFFF




#if !defined(MIDL_PASS) && defined(_M_IX86)

FORCEINLINE
PKPRCB
NTAPI
KeGetCurrentPrcb (VOID)
{
    PKPRCB Prcb;
    Prcb = (PKPRCB) (ULONG_PTR) __readfsdword (FIELD_OFFSET (KPCR, Prcb));
    __assume(Prcb != NULL);
    return Prcb;
}

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_saves_
NTHALAPI
KIRQL
NTAPI
KeGetCurrentIrql(
    VOID
    );

#pragma pack(push,2)
typedef struct _FAR_JMP_16
{
    UCHAR  OpCode;  // = 0xe9
    USHORT Offset;
} FAR_JMP_16;
#pragma pack(pop)

#define PROCESSOR_START_FLAG_FORCE_ENABLE_NX 0x1

typedef struct _PROCESSOR_START_BLOCK *PPROCESSOR_START_BLOCK;
typedef struct _PROCESSOR_START_BLOCK
{
    FAR_JMP_16 Jmp;
    ULONG CompletionFlag;
    ULONG Flags;
    ULONG64 TiledMemoryMap;
    PPROCESSOR_START_BLOCK SelfMap;
    KPROCESSOR_STATE ProcessorState;
} PROCESSOR_START_BLOCK;

FORCEINLINE
ULONG
NTAPI
KeGetCurrentProcessorNumber(VOID)
{
    return (ULONG) __readfsbyte (FIELD_OFFSET (KPCR, Number));
}

FORCEINLINE
ULONG
NTAPI
KeGetCurrentProcessorIndex (
    VOID
    )
{
    return (ULONG)__readfsbyte(0x51);
}

#endif // !defined(MIDL_PASS) && defined(_M_IX86)

FORCEINLINE
VOID
KeMemoryBarrier (
    VOID)
{
    LONG Barrier;
    InterlockedOr(&Barrier, 0);
    return;
}


/#endif // defined(_X86_)

#define INIT_BOOTDEVICE_LINKNAME L"\\Device\\BootDevice"
#define INIT_SYSTEMROOT_LINKNAME L"\\SystemRoot"
#define INIT_SYSTEMROOT_DLLPATH  "\\SystemRoot\\System32"
#define INIT_SYSTEMROOT_BINPATH  "\\SystemRoot\\System32"
extern const ULONG NtBuildNumber;

/#if defined(_M_AMD64)

VOID
KeCompactServiceTable (
    _Inout_ PVOID Table,
    _In_ PVOID Arguments,
    _In_ ULONG limit,
    _In_ BOOLEAN Win32k
    );

VOID
KiLockServiceTable (
    _Inout_ PVOID Table,
    _In_ PVOID Arguments,
    _In_ ULONG limit,
    _In_ BOOLEAN Win32k
    );

VOID
KePersistMemory (
    _In_ PVOID VirtualAddress,
    _In_ SIZE_T NumberOfBytes
    );

#define IMAGE_FILE_MACHINE_NATIVE   0x8664

typedef ULONG PFN_COUNT;
typedef LONG64 SPFN_NUMBER, *PSPFN_NUMBER;
typedef ULONG64 PFN_NUMBER, *PPFN_NUMBER;

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(KeGetDcacheFillSize)
#endif

#define KeGetDcacheFillSize() 1L

#define ExAcquireSpinLock(Lock, OldIrql) KeAcquireSpinLock((Lock), (OldIrql))
#define ExReleaseSpinLock(Lock, OldIrql) KeReleaseSpinLock((Lock), (OldIrql))
#define ExAcquireSpinLockAtDpcLevel(Lock) KeAcquireSpinLockAtDpcLevel(Lock)
#define ExReleaseSpinLockFromDpcLevel(Lock) KeReleaseSpinLockFromDpcLevel(Lock)

#define _HARDWARE_PTE_WORKING_SET_BITS  11

typedef struct _HARDWARE_PTE
{
    ULONG64 Valid : 1;
    ULONG64 Write : 1;                // UP version
    ULONG64 Owner : 1;
    ULONG64 WriteThrough : 1;
    ULONG64 CacheDisable : 1;
    ULONG64 Accessed : 1;
    ULONG64 Dirty : 1;
    ULONG64 LargePage : 1;
    ULONG64 Global : 1;
    ULONG64 CopyOnWrite : 1;          // software field
    ULONG64 Prototype : 1;            // software field
    ULONG64 reserved0 : 1;            // software field
    ULONG64 PageFrameNumber : 36;
    ULONG64 reserved1 : 16 - (_HARDWARE_PTE_WORKING_SET_BITS+1);
    ULONG64 SoftwareWsIndex : _HARDWARE_PTE_WORKING_SET_BITS;
    ULONG64 NoExecute : 1;
} HARDWARE_PTE, *PHARDWARE_PTE;

#define INITIALIZE_DIRECTORY_TABLE_BASE(dirbase,pfn) \
     *((PULONG64)(dirbase)) = (((ULONG64)(pfn)) << PAGE_SHIFT)

#define TYPE_LDT 0x02                     // 00010 = system ldt
#define TYPE_CODE 0x1B                  // 11011 = code, read only, accessed
#define TYPE_DATA 0x13                  // 10011 = data, read and write, accessed
#define TYPE_TSS64 0x09                 // 01001 = task state segment

#define DPL_USER 3
#define DPL_SYSTEM 0

#define GRANULARITY_BYTE 0
#define GRANULARITY_PAGE 1

#define KGDT_LEGACY_LIMIT_SHIFT 14
#define KGDT_LIMIT_ENCODE_MASK (0xf << 10)

#define SELECTOR_TABLE_INDEX 0x04

typedef union _KGDTENTRY64
{
    struct {
        USHORT LimitLow;
        USHORT BaseLow;
        union {
            struct {
                UCHAR BaseMiddle;
                UCHAR Flags1;
                UCHAR Flags2;
                UCHAR BaseHigh;
            } Bytes;

            struct {
                ULONG BaseMiddle : 8;
                ULONG Type : 5;
                ULONG Dpl : 2;
                ULONG Present : 1;
                ULONG LimitHigh : 4;
                ULONG System : 1;
                ULONG LongMode : 1;
                ULONG DefaultBig : 1;
                ULONG Granularity : 1;
                ULONG BaseHigh : 8;
            } Bits;
        };

        ULONG BaseUpper;
        ULONG MustBeZero;
    };

    struct {
        LONG64 DataLow;
        LONG64 DataHigh;
    };

} KGDTENTRY64, *PKGDTENTRY64;

typedef struct _KLDTENTRY
{
    USHORT LimitLow;
    USHORT BaseLow;
    union {
        struct {
            UCHAR BaseMid;
            UCHAR Flags1;
            UCHAR Flags2;
            UCHAR BaseHi;
        } Bytes;

        struct {
            ULONG BaseMid : 8;
            ULONG Type : 5;
            ULONG Dpl : 2;
            ULONG Pres : 1;
            ULONG LimitHi : 4;
            ULONG Sys : 1;
            ULONG Reserved_0 : 1;
            ULONG Default_Big : 1;
            ULONG Granularity : 1;
            ULONG BaseHi : 8;
        } Bits;
    } HighWord;
} KLDTENTRY, *PKLDTENTRY;

C_ASSERT((sizeof(KLDTENTRY) % sizeof(PVOID)) == 0);

#define KLDT_MAX_LENGTH (8192)
#define KLDT_MAX_SIZE (sizeof(KLDTENTRY) * KLDT_MAX_LENGTH)

typedef union _KIDTENTRY64 {
   struct {
       USHORT OffsetLow;
       USHORT Selector;
       USHORT IstIndex : 3;
       USHORT Reserved0 : 5;
       USHORT Type : 5;
       USHORT Dpl : 2;
       USHORT Present : 1;
       USHORT OffsetMiddle;
       ULONG OffsetHigh;
       ULONG Reserved1;
   };

   ULONG64 Alignment;
} KIDTENTRY64, *PKIDTENTRY64;

typedef union _KGDT_BASE {
    struct {
        USHORT BaseLow;
        UCHAR BaseMiddle;
        UCHAR BaseHigh;
        ULONG BaseUpper;
    };

    ULONG64 Base;
} KGDT_BASE, *PKGDT_BASE;

C_ASSERT(sizeof(KGDT_BASE) == sizeof(ULONG64));

typedef union _KGDT_LIMIT {
    struct {
        USHORT LimitLow;
        USHORT LimitHigh : 4;
        USHORT MustBeZero : 12;
    };

    ULONG Limit;
} KGDT_LIMIT, *PKGDT_LIMIT;

C_ASSERT(sizeof(KGDT_LIMIT) == sizeof(ULONG));

#pragma pack(push, 4)
typedef struct _KTSS64 {
    ULONG Reserved0;
    ULONG64 Rsp0;
    ULONG64 Rsp1;
    ULONG64 Rsp2;
    ULONG64 Ist[8];
    ULONG64 Reserved1;
    USHORT Reserved2;
    USHORT IoMapBase;
} KTSS64, *PKTSS64;
#pragma pack(pop)

C_ASSERT((sizeof(KTSS64) % sizeof(PVOID)) == 0);

#define TSS_IST_RESERVED 0
#define TSS_IST_PANIC 1
#define TSS_IST_MCA 2
#define TSS_IST_NMI 3

#define IO_ACCESS_MAP_NONE FALSE

#define KiComputeIopmOffset(Enable)  (sizeof(KTSS64))

typedef struct _KDESCRIPTOR {
    USHORT Pad[3];
    USHORT Limit;
    PVOID Base;
} KDESCRIPTOR, *PKDESCRIPTOR;

typedef struct _KDESCRIPTOR32 {
    USHORT Pad[3];
    USHORT Limit;
    ULONG Base;
} KDESCRIPTOR32, *PKDESCRIPTOR32;

typedef struct _KSPECIAL_REGISTERS {
    ULONG64 Cr0;
    ULONG64 Cr2;
    ULONG64 Cr3;
    ULONG64 Cr4;
    ULONG64 KernelDr0;
    ULONG64 KernelDr1;
    ULONG64 KernelDr2;
    ULONG64 KernelDr3;
    ULONG64 KernelDr6;
    ULONG64 KernelDr7;
    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;
    USHORT Tr;
    USHORT Ldtr;
    ULONG MxCsr;
    ULONG64 DebugControl;
    ULONG64 LastBranchToRip;
    ULONG64 LastBranchFromRip;
    ULONG64 LastExceptionToRip;
    ULONG64 LastExceptionFromRip;
    ULONG64 Cr8;
    ULONG64 MsrGsBase;
    ULONG64 MsrGsSwap;
    ULONG64 MsrStar;
    ULONG64 MsrLStar;
    ULONG64 MsrCStar;
    ULONG64 MsrSyscallMask;
    ULONG64 Xcr0;
} KSPECIAL_REGISTERS, *PKSPECIAL_REGISTERS;

typedef struct _KPROCESSOR_STATE {
    KSPECIAL_REGISTERS SpecialRegisters;
    CONTEXT ContextFrame;
} KPROCESSOR_STATE, *PKPROCESSOR_STATE;

typedef enum
{
    CPU_UNKNOWN,
    CPU_AMD,
    CPU_INTEL,
    CPU_VIA
} CPU_VENDORS;

#define PRCB_MAJOR_VERSION 1
#define PRCB_MINOR_VERSION 1

#define PRCB_BUILD_DEBUG 0x1
#define PRCB_BUILD_UNIPROCESSOR 0x2

#define MAXIMUM_CACHES 5

typedef struct _KPRCB
{
    ULONG MxCsr;
    UCHAR LegacyNumber;
    UCHAR ReservedMustBeZero;
    BOOLEAN InterruptRequest;
    BOOLEAN IdleHalt;
    struct _KTHREAD *CurrentThread;
    struct _KTHREAD *NextThread;
    struct _KTHREAD *IdleThread;
    UCHAR NestingLevel;
    BOOLEAN ClockOwner;
    union
    {
        UCHAR PendingTickFlags;
        struct
        {
            UCHAR PendingTick : 1;
            UCHAR PendingBackupTick : 1;
        };
    };
    UCHAR IdleState;
    ULONG Number;
    ULONG64 RspBase;
    KSPIN_LOCK PrcbLock;
    PSCHAR PriorityState;
    KPROCESSOR_STATE ProcessorState;
    CCHAR CpuType;
    CCHAR CpuID;
    union
    {
        USHORT CpuStep;
        struct
        {
            UCHAR CpuStepping;
            UCHAR CpuModel;
        };
    };
    ULONG MHz;
    ULONG64 HalReserved[8];
    USHORT MinorVersion;
    USHORT MajorVersion;
    UCHAR BuildType;
    UCHAR CpuVendor;
    UCHAR CoresPerPhysicalProcessor;
    UCHAR LogicalProcessorsPerCore;
    struct _KNODE *ParentNode;
    KAFFINITY GroupSetMember;
    UCHAR Group;
    UCHAR GroupIndex;
    UCHAR PrcbPad05[2];
    ULONG InitialApicId;
    ULONG ScbOffset;
    ULONG ApicMask;
    PVOID AcpiReserved;
    ULONG CFlushSize;
    ULONG PrcbPad10;
} KPRCB, *PKPRCB, *RESTRICTED_POINTER PRKPRCB;

C_ASSERT(FIELD_OFFSET(KPRCB, HalReserved) == 0x5F8);  // Do not move field
C_ASSERT(FIELD_OFFSET(KPRCB, AcpiReserved) == 0x660); // Do not move field

#define PCR_MINOR_VERSION 1
#define PCR_MAJOR_VERSION 1

typedef struct _KPCR
{
    union
    {
        NT_TIB NtTib;
        struct
        {
            union _KGDTENTRY64 *GdtBase;
            struct _KTSS64 *TssBase;
            ULONG64 UserRsp;
            struct _KPCR *Self;
            struct _KPRCB *CurrentPrcb;
            PKSPIN_LOCK_QUEUE LockArray;
            PVOID Used_Self;
        };
    };
    union _KIDTENTRY64 *IdtBase;
    ULONG64 Unused[2];
    KIRQL Irql;
    UCHAR SecondLevelCacheAssociativity;
    UCHAR ObsoleteNumber;
    UCHAR Fill0;
    ULONG Unused0[3];
    USHORT MajorVersion;
    USHORT MinorVersion;
    ULONG StallScaleFactor;
    PVOID Unused1[3];
    ULONG KernelReserved[15];
    ULONG SecondLevelCacheSize;
    ULONG HalReserved[16];
    ULONG Unused2;
    PVOID KdVersionBlock;
    PVOID Unused3;
    ULONG PcrAlign1[24];
    KPRCB Prcb;
} KPCR, *PKPCR;

#define FSW_INVALID_OPERATION 0x1
#define FSW_DENORMAL 0x2
#define FSW_ZERO_DIVIDE 0x4
#define FSW_OVERFLOW 0x8
#define FSW_UNDERFLOW 0x10
#define FSW_PRECISION 0x20
#define FSW_STACK_FAULT 0x40
#define FSW_ERROR_SUMMARY 0x80
#define FSW_CONDITION_CODE_0 0x100
#define FSW_CONDITION_CODE_1 0x200
#define FSW_CONDITION_CODE_2 0x400
#define FSW_CONDITION_CODE_3 0x4000

#define FSW_ERROR_MASK (FSW_INVALID_OPERATION | FSW_DENORMAL |              \
                        FSW_ZERO_DIVIDE | FSW_OVERFLOW | FSW_UNDERFLOW |    \
                        FSW_PRECISION)

#define XSW_INVALID_OPERATION 0x1
#define XSW_DENORMAL 0x2
#define XSW_ZERO_DIVIDE 0x4
#define XSW_OVERFLOW 0x8
#define XSW_UNDERFLOW 0x10
#define XSW_PRECISION 0x20

#define XSW_ERROR_MASK (XSW_INVALID_OPERATION |  XSW_DENORMAL |             \
                        XSW_ZERO_DIVIDE | XSW_OVERFLOW | XSW_UNDERFLOW |    \
                        XSW_PRECISION)

#define XSW_ERROR_SHIFT 7

#define XCW_DAZ 0x40
#define XCW_INVALID_OPERATION 0x80
#define XCW_DENORMAL 0x100
#define XCW_ZERO_DIVIDE 0x200
#define XCW_OVERFLOW 0x400
#define XCW_UNDERFLOW 0x800
#define XCW_PRECISION 0x1000
#define XCW_ROUND_CONTROL 0x6000
#define XCW_FLUSH_ZERO 0x8000

#define EFLAGS_CF_MASK 0x00000001       // carry flag
#define EFLAGS_PF_MASK 0x00000004       // parity flag
#define EFLAGS_AF_MASK 0x00000010       // auxiliary carry flag
#define EFLAGS_ZF_MASK 0x00000040       // zero flag
#define EFLAGS_SF_MASK 0x00000080       // sign flag
#define EFLAGS_TF_MASK 0x00000100       // trap flag
#define EFLAGS_IF_MASK 0x00000200       // interrupt flag
#define EFLAGS_DF_MASK 0x00000400       // direction flag
#define EFLAGS_OF_MASK 0x00000800       // overflow flag
#define EFLAGS_IOPL_MASK 0x00003000     // I/O privilege level
#define EFLAGS_NT_MASK 0x00004000       // nested task
#define EFLAGS_RF_MASK 0x00010000       // resume flag
#define EFLAGS_VM_MASK 0x00020000       // virtual 8086 mode
#define EFLAGS_AC_MASK 0x00040000       // alignment check
#define EFLAGS_VIF_MASK 0x00080000      // virtual interrupt flag
#define EFLAGS_VIP_MASK 0x00100000      // virtual interrupt pending
#define EFLAGS_ID_MASK 0x00200000       // identification flag

#define EFLAGS_TF_SHIFT 8               // trap
#define EFLAGS_IF_SHIFT 9               // interrupt enable

#define EFLAGS_SYSCALL_CLEAR (EFLAGS_IF_MASK | EFLAGS_DF_MASK |              \
                              EFLAGS_TF_MASK | EFLAGS_NT_MASK)

typedef union _AMD_L1_CACHE_INFO
{
    ULONG Ulong;
    struct {
        UCHAR LineSize;
        UCHAR LinesPerTag;
        UCHAR Associativity;
        UCHAR Size;
    };
} AMD_L1_CACHE_INFO, *PAMD_L1_CACHE_INFO;

typedef union _AMD_L2_CACHE_INFO
{
    ULONG Ulong;
    struct {
        UCHAR  LineSize;
        UCHAR  LinesPerTag   : 4;
        UCHAR  Associativity : 4;
        USHORT Size;
    };
} AMD_L2_CACHE_INFO, *PAMD_L2_CACHE_INFO;

typedef union _AMD_L3_CACHE_INFO
{
    ULONG Ulong;
    struct
    {
        UCHAR  LineSize;
        UCHAR  LinesPerTag   : 4;
        UCHAR  Associativity : 4;
        USHORT Reserved : 2;
        USHORT Size : 14;
    };
} AMD_L3_CACHE_INFO, *PAMD_L3_CACHE_INFO;

typedef union _VIA_L1_CACHE_INFO
{
    ULONG Ulong;
    struct
    {
        UCHAR LineSize;
        UCHAR LinesPerTag;
        UCHAR Associativity;
        UCHAR Size;
    };
} VIA_L1_CACHE_INFO, *PVIA_L1_CACHE_INFO;

typedef union _VIA_L2_CACHE_INFO
{
    ULONG Ulong;
    struct
    {
        UCHAR LineSize;
        UCHAR LinesPerTag   : 4;
        UCHAR Associativity : 4;
        USHORT Size;
    };
} VIA_L2_CACHE_INFO, *PVIA_L2_CACHE_INFO;

typedef enum _INTEL_CACHE_TYPE
{
    IntelCacheNull,
    IntelCacheData,
    IntelCacheInstruction,
    IntelCacheUnified,
    IntelCacheRam,
    IntelCacheTrace
} INTEL_CACHE_TYPE;

typedef union INTEL_CACHE_INFO_EAX
{
    ULONG Ulong;
    struct {
        INTEL_CACHE_TYPE Type : 5;
        ULONG Level : 3;
        ULONG SelfInitializing : 1;
        ULONG FullyAssociative : 1;
        ULONG Reserved : 4;
        ULONG ThreadsSharing : 12;
        ULONG ProcessorCores : 6;
    };
} INTEL_CACHE_INFO_EAX, *PINTEL_CACHE_INFO_EAX;

typedef union INTEL_CACHE_INFO_EBX
{
    ULONG Ulong;
    struct {
        ULONG LineSize      : 12;
        ULONG Partitions    : 10;
        ULONG Associativity : 10;
    };
} INTEL_CACHE_INFO_EBX, *PINTEL_CACHE_INFO_EBX;

typedef struct _KEXCEPTION_FRAME
{
    ULONG64 P1Home;
    ULONG64 P2Home;
    ULONG64 P3Home;
    ULONG64 P4Home;
    ULONG64 P5;
    ULONG64 Spare1;
    M128A Xmm6;
    M128A Xmm7;
    M128A Xmm8;
    M128A Xmm9;
    M128A Xmm10;
    M128A Xmm11;
    M128A Xmm12;
    M128A Xmm13;
    M128A Xmm14;
    M128A Xmm15;
    ULONG64 TrapFrame;
    ULONG64 OutputBuffer;
    ULONG64 OutputLength;
    ULONG64 Spare2;
    ULONG64 MxCsr;
    ULONG64 Rbp;
    ULONG64 Rbx;
    ULONG64 Rdi;
    ULONG64 Rsi;
    ULONG64 R12;
    ULONG64 R13;
    ULONG64 R14;
    ULONG64 R15;
    ULONG64 Return;
} KEXCEPTION_FRAME, *PKEXCEPTION_FRAME;

#define KEXCEPTION_FRAME_LENGTH sizeof(KEXCEPTION_FRAME)

C_ASSERT((sizeof(KEXCEPTION_FRAME) & STACK_ROUND) == 0);
C_ASSERT(FIELD_OFFSET(KEXCEPTION_FRAME, Return) == KEXCEPTION_FRAME_LENGTH - 8);

#define EXCEPTION_RECORD_LENGTH ((sizeof(EXCEPTION_RECORD) + STACK_ROUND) & ~STACK_ROUND)

typedef struct _MACHINE_FRAME
{
    ULONG64 Rip;
    USHORT SegCs;
    USHORT Fill1[3];
    ULONG EFlags;
    ULONG Fill2;
    ULONG64 Rsp;
    USHORT SegSs;
    USHORT Fill3[3];
} MACHINE_FRAME, *PMACHINE_FRAME;

#define MACHINE_FRAME_LENGTH sizeof(MACHINE_FRAME)

C_ASSERT((sizeof(MACHINE_FRAME) & STACK_ROUND) == 8);

typedef struct _KSWITCH_FRAME
{
    ULONG64 P1Home;
    ULONG64 P2Home;
    ULONG64 P3Home;
    ULONG64 P4Home;
    ULONG64 P5Home;
    KIRQL ApcBypass;
    UCHAR Fill1[7];
    ULONG64 Rbp;
    ULONG64 Return;
} KSWITCH_FRAME, *PKSWITCH_FRAME;

#define KSWITCH_FRAME_LENGTH sizeof(KSWITCH_FRAME)

C_ASSERT((sizeof(KSWITCH_FRAME) & STACK_ROUND) == 0);

typedef struct _KSTART_FRAME
{
    ULONG64 P1Home;
    ULONG64 P2Home;
    ULONG64 P3Home;
    ULONG64 P4Home;
    ULONG64 Reserved;
    ULONG64 Return;
} KSTART_FRAME, *PKSTART_FRAME;

#define KSTART_FRAME_LENGTH sizeof(KSTART_FRAME)

C_ASSERT((sizeof(KSTART_FRAME) & STACK_ROUND) == 0);

typedef struct _KTRAP_FRAME
{
    ULONG64 P1Home;
    ULONG64 P2Home;
    ULONG64 P3Home;
    ULONG64 P4Home;
    ULONG64 P5;
    KPROCESSOR_MODE PreviousMode;
    KIRQL PreviousIrql;
    UCHAR FaultIndicator;
    UCHAR ExceptionActive;
    ULONG MxCsr;
    ULONG64 Rax;
    ULONG64 Rcx;
    ULONG64 Rdx;
    ULONG64 R8;
    ULONG64 R9;
    ULONG64 R10;
    ULONG64 R11;
    union
    {
        ULONG64 GsBase;
        ULONG64 GsSwap;
    };
    M128A Xmm0;
    M128A Xmm1;
    M128A Xmm2;
    M128A Xmm3;
    M128A Xmm4;
    M128A Xmm5;
    union
    {
        ULONG64 FaultAddress;
        ULONG64 ContextRecord;
        ULONG64 TimeStampCKCL;
    };
    ULONG64 Dr0;
    ULONG64 Dr1;
    ULONG64 Dr2;
    ULONG64 Dr3;
    ULONG64 Dr6;
    ULONG64 Dr7;
    struct
    {
        ULONG64 DebugControl;
        ULONG64 LastBranchToRip;
        ULONG64 LastBranchFromRip;
        ULONG64 LastExceptionToRip;
        ULONG64 LastExceptionFromRip;
    };
    USHORT SegDs;
    USHORT SegEs;
    USHORT SegFs;
    USHORT SegGs;
    ULONG64 TrapFrame;
    ULONG64 Rbx;
    ULONG64 Rdi;
    ULONG64 Rsi;
    ULONG64 Rbp;
    union
    {
        ULONG64 ErrorCode;
        ULONG64 ExceptionFrame;
        ULONG64 TimeStampKlog;
    };
    ULONG64 Rip;
    USHORT SegCs;
    UCHAR Fill0;
    UCHAR Logging;
    USHORT Fill1[2];
    ULONG EFlags;
    ULONG Fill2;
    ULONG64 Rsp;
    USHORT SegSs;
    USHORT Fill3;
    ULONG Fill4;
} KTRAP_FRAME, *PKTRAP_FRAME;

typedef struct _KUMS_CONTEXT_HEADER {
    ULONG64 P1Home;
    ULONG64 P2Home;
    ULONG64 P3Home;
    ULONG64 P4Home;
    PVOID StackTop;
    ULONG64 StackSize;
    ULONG64 RspOffset;
    ULONG64 Rip;
    PXMM_SAVE_AREA32 FltSave;
#define KUMS_UCH_VOLATILE_BIT (0)
#define KUMS_UCH_VOLATILE_MASK (1ULL << KUMS_UCH_VOLATILE_BIT)
    union {
        struct {
            ULONG64 Volatile : 1;
            ULONG64 Reserved : 63;
        };
        ULONG64 Flags;
    };
    PKTRAP_FRAME TrapFrame;
    PKEXCEPTION_FRAME ExceptionFrame;
    struct _KTHREAD *SourceThread;
    ULONG64 Return;
} KUMS_CONTEXT_HEADER, *PKUMS_CONTEXT_HEADER;

#define KEXCEPTION_ACTIVE_INTERRUPT_FRAME 0
#define KEXCEPTION_ACTIVE_EXCEPTION_FRAME 1
#define KEXCEPTION_ACTIVE_SERVICE_FRAME   2

#define KTRAP_FRAME_LENGTH sizeof(KTRAP_FRAME)

C_ASSERT((sizeof(KTRAP_FRAME) & STACK_ROUND) == 0);

C_ASSERT(RTL_SIZEOF_THROUGH_FIELD(KTRAP_FRAME, Fill4) == sizeof(KTRAP_FRAME));

#define KUMS_CONTEXT_HEADER_LENGTH sizeof(KUMS_CONTEXT_HEADER)

C_ASSERT((sizeof(KUMS_CONTEXT_HEADER) & STACK_ROUND) == 0);

NTKERNELAPI
VOID
KeProfileInterruptWithSource (
    _In_ PKTRAP_FRAME TrapFrame,
    _In_ KPROFILE_SOURCE ProfileSource
    );

typedef KEXCEPTION_FRAME KCALLOUT_FRAME;
typedef PKEXCEPTION_FRAME PKCALLOUT_FRAME;

typedef struct _UCALLOUT_FRAME
{
    ULONG64 P1Home;
    ULONG64 P2Home;
    ULONG64 P3Home;
    ULONG64 P4Home;
    PVOID Buffer;
    ULONG Length;
    ULONG ApiNumber;
    MACHINE_FRAME MachineFrame;
} UCALLOUT_FRAME, *PUCALLOUT_FRAME;

C_ASSERT((sizeof(UCALLOUT_FRAME) & STACK_ROUND) == 8);

typedef struct _KFLOATING_SAVE
{
    ULONG Dummy;
} KFLOATING_SAVE, *PKFLOATING_SAVE;

#define PXE_BASE          0xFFFFF6FB7DBED000UI64
#define PXE_SELFMAP       0xFFFFF6FB7DBEDF68UI64
#define PPE_BASE          0xFFFFF6FB7DA00000UI64
#define PDE_BASE          0xFFFFF6FB40000000UI64
#define PTE_BASE          0xFFFFF68000000000UI64

#define PXE_TOP           0xFFFFF6FB7DBEDFFFUI64
#define PPE_TOP           0xFFFFF6FB7DBFFFFFUI64
#define PDE_TOP           0xFFFFF6FB7FFFFFFFUI64
#define PTE_TOP           0xFFFFF6FFFFFFFFFFUI64

#define PDE_KTBASE_AMD64  PPE_BASE

#define PTI_SHIFT 12
#define PDI_SHIFT 21
#define PPI_SHIFT 30
#define PXI_SHIFT 39

#define PTE_PER_PAGE 512
#define PDE_PER_PAGE 512
#define PPE_PER_PAGE 512
#define PXE_PER_PAGE 512

#define PTI_MASK_AMD64 (PTE_PER_PAGE - 1)
#define PDI_MASK_AMD64 (PDE_PER_PAGE - 1)
#define PPI_MASK (PPE_PER_PAGE - 1)
#define PXI_MASK (PXE_PER_PAGE - 1)

#define MM_HIGHEST_USER_ADDRESS MmHighestUserAddress
#define MM_SYSTEM_RANGE_START MmSystemRangeStart

#if defined(_LOCAL_COPY_USER_PROBE_ADDRESS_)

#define MM_USER_PROBE_ADDRESS _LOCAL_COPY_USER_PROBE_ADDRESS_

#if defined(__CONVERGED_WIN32K_DRIVER__)
extern DLLBASEEXPORT ULONG64 _LOCAL_COPY_USER_PROBE_ADDRESS_;
#else
extern ULONG64 _LOCAL_COPY_USER_PROBE_ADDRESS_;
#endif

#else

#define MM_USER_PROBE_ADDRESS MmUserProbeAddress

#endif

#define MM_LOWEST_USER_ADDRESS (PVOID)(LONG_PTR)0x10000

#define MmGetProcedureAddress(Address) (Address)
#define MmLockPagableCodeSection(Address) MmLockPagableDataSection(Address)

#define EFLAGS_SANITIZE 0x00210fd5L

__forceinline
ULONG
SANITIZE_EFLAGS(ULONG eFlags, MODE mode)
{
    return ((mode) == KernelMode ?
                ((eFlags) & EFLAGS_SANITIZE) :
                (((eFlags) & EFLAGS_SANITIZE) | EFLAGS_IF_MASK));
}

#define DR7_LEGAL 0xffff0355
#define DR7_ACTIVE 0x0355
#define DR7_TRACE_BRANCH 0x200
#define DR7_LAST_BRANCH 0x100

#define SANITIZE_DR7(Dr7, mode) ((Dr7) & DR7_LEGAL)

__forceinline
ULONGLONG
SANITIZE_DRADDR(ULONGLONG DrReg, MODE mode)
{
    return ((mode) == KernelMode ?
                 (DrReg) :
                 (((PVOID)(DrReg) <= MM_HIGHEST_USER_ADDRESS) ? (DrReg) : 0));
}

#define SANITIZE_MXCSR(_mxcsr_) ((_mxcsr_) & KiMxCsrMask)
#define SANITIZE_FCW(_fcw_) ((_fcw_) & 0x1f3f)

#if defined(_M_AMD64) && !defined(RC_INVOKED)  && !defined(MIDL_PASS)

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExInterlockedIncrementLong)      // Use InterlockedIncrement
#pragma deprecated(ExInterlockedDecrementLong)      // Use InterlockedDecrement
#pragma deprecated(ExInterlockedExchangeUlong)      // Use InterlockedExchange
#endif

#define RESULT_ZERO 0
#define RESULT_NEGATIVE 1
#define RESULT_POSITIVE 2

typedef enum _INTERLOCKED_RESULT {
    ResultNegative = RESULT_NEGATIVE,
    ResultZero = RESULT_ZERO,
    ResultPositive = RESULT_POSITIVE
} INTERLOCKED_RESULT;

#define ExInterlockedDecrementLong(Addend, Lock)                            \
    _ExInterlockedDecrementLong(Addend)

_Post_satisfies_(return >= 0 && return <= 2)
__forceinline
LONG
_ExInterlockedDecrementLong (
    _Inout_ _Interlocked_operand_ PLONG Addend)
{
    LONG Result;

    Result = InterlockedDecrement(Addend);
    if (Result < 0) {
        return ResultNegative;

    } else if (Result > 0) {
        return ResultPositive;

    } else {
        return ResultZero;
    }
}

#define ExInterlockedIncrementLong(Addend, Lock)                            \
    _ExInterlockedIncrementLong(Addend)

_Post_satisfies_(return >= 0 && return <= 2)
__forceinline
LONG
_ExInterlockedIncrementLong (
    _Inout_ _Interlocked_operand_ PLONG Addend)
{
    LONG Result;

    Result = InterlockedIncrement(Addend);
    if (Result < 0) {
        return ResultNegative;

    } else if (Result > 0) {
        return ResultPositive;

    } else {
        return ResultZero;
    }
}

#define ExInterlockedExchangeUlong(Target, Value, Lock)                     \
    _ExInterlockedExchangeUlong(Target, Value)

__forceinline
ULONG
_ExInterlockedExchangeUlong (
    _Inout_ _Interlocked_operand_ PULONG Target,
    _In_ ULONG Value)
{
    return (ULONG)InterlockedExchange((PLONG)Target, (LONG)Value);
}

#endif // defined(_M_AMD64) && !defined(RC_INVOKED)  && !defined(MIDL_PASS)


#if !defined(MIDL_PASS) && defined(_M_AMD64)

__forceinline
PKPCR
KeGetPcr (
    VOID)
{
    return (PKPCR)__readgsqword(FIELD_OFFSET(KPCR, Self));
}

CFORCEINLINE
PKPRCB
KeGetCurrentPrcb (
    VOID)
{
    PKPRCB Prcb;

    Prcb = (PKPRCB)(PVOID)__readgsqword(FIELD_OFFSET(KPCR, CurrentPrcb));
    __assume(Prcb != NULL);
    return Prcb;
}

#if (NTDDI_VERSION < NTDDI_WIN7) || !defined(NT_PROCESSOR_GROUPS)
__forceinline
ULONG
KeGetCurrentProcessorNumber (
    VOID)
{
    return (ULONG)__readgsbyte(0x184);
}

#endif

__forceinline
ULONG
KeGetCurrentProcessorIndex (
    VOID)
{
    return __readgsdword(0x1a4);
}


#endif // !defined(MIDL_PASS) && defined(_M_AMD64)


#if !defined(_CROSS_PLATFORM_)
CFORCEINLINE
VOID
KeMemoryBarrier (
    VOID)
{
    FastFence();
    return;
}

#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()

#else

#define KeMemoryBarrier()
#define KeMemoryBarrierWithoutFence()

#endif


_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_(return>=0, _Kernel_float_saved_)
_At_(*FloatSave, _When_(return>=0, _Kernel_acquires_resource_(FloatState)))
__forceinline
NTSTATUS
KeSaveFloatingPointState (
    _Out_ PKFLOATING_SAVE FloatSave)
#pragma warning (suppress:28104 28161 6001 6101) // PFD can't recognize the implementation
{

    UNREFERENCED_PARAMETER(FloatSave);

    return STATUS_SUCCESS;
}

_Success_(1)
_IRQL_requires_max_(DISPATCH_LEVEL)
_Kernel_float_restored_
_At_(*FloatSave, _Kernel_requires_resource_held_(FloatState) _Kernel_releases_resource_(FloatState))
__forceinline
NTSTATUS
KeRestoreFloatingPointState (
    _In_ PKFLOATING_SAVE FloatSave)
#pragma warning (suppress:28103 28162) // PFD can't recognize the implementation
{
    UNREFERENCED_PARAMETER(FloatSave);
    return STATUS_SUCCESS;
}

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_saves_
CFORCEINLINE
KIRQL
KeGetCurrentIrql (
    VOID)
{
    return (KIRQL)ReadCR8();
}

#define KeRaiseIrql(a,b) *(b) = KfRaiseIrql(a)

#if ((NTDDI_VERSION >= NTDDI_WIN8) && \
     (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_) || defined(_BLDR_)))

_IRQL_requires_max_(HIGH_LEVEL)
NTKERNELAPI
VOID
KeLowerIrql (
    _In_ _Notliteral_ _IRQL_restores_ KIRQL NewIrql
   );

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_raises_(NewIrql)
_IRQL_saves_
NTKERNELAPI
KIRQL
KfRaiseIrql (
    _In_ KIRQL NewIrql
    );

#else

_IRQL_requires_max_(HIGH_LEVEL)
CFORCEINLINE
VOID
KzLowerIrql (
    _In_ _Notliteral_ _IRQL_restores_ KIRQL NewIrql)
{
    NT_ASSERT(KeGetCurrentIrql() >= NewIrql);
    WriteCR8(NewIrql);
    return;
}

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_raises_(NewIrql)
_IRQL_saves_
CFORCEINLINE
KIRQL
KzRaiseIrql (
    _In_ KIRQL NewIrql)
{
    KIRQL OldIrql;

    OldIrql = KeGetCurrentIrql();
    NT_ASSERT(OldIrql <= NewIrql);
    WriteCR8(NewIrql);
    return OldIrql;
}

#define KeLowerIrql KzLowerIrql
#define KfRaiseIrql KzRaiseIrql

#endif


_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
__forceinline
KIRQL
KeRaiseIrqlToDpcLevel (
    VOID)
{
    return KfRaiseIrql(DISPATCH_LEVEL);
}

_IRQL_saves_
_IRQL_raises_(12)
__forceinline
KIRQL
KeRaiseIrqlToSynchLevel (
    VOID)
{
    return KfRaiseIrql(12);
}

#define KF_MMX                      0x0000000000000100ui64
#define KF_XMMI                     0x0000000000002000ui64
#define KF_3DNOW                    0x0000000000004000ui64
#define KF_XMMI64                   0x0000000000010000ui64
#define KF_SSE3                     0x0000000000080000ui64

/#endif // defined(_AMD64_)


#if defined(_ARM_)

typedef ULONG PFN_COUNT;
typedef LONG SPFN_NUMBER, *PSPFN_NUMBER;
typedef ULONG PFN_NUMBER, *PPFN_NUMBER;

#define MAX_EVENT_COUNTERS 31
#define FLUSH_MULTIPLE_MAXIMUM 32
#define ALLOC_PRAGMA 1
#define ALLOC_DATA_PRAGMA 1

#define CPSRM_USER 0x10
#define CPSRM_FIQ  0x11
#define CPSRM_INT  0x12
#define CPSRM_SVC  0x13
#define CPSRM_ABT  0x17
#define CPSRM_UDF  0x1B
#define CPSRM_SYS  0x1F

#define CPSRM_MASK 0x1F

#define CPSRC_ABORT 0x100
#define CPSRC_INT   0x80
#define CPSRC_THUMB 0x20

#define CPSRF_N 0x80000000
#define CPSRF_Z 0x40000000
#define CPSRF_C 0x20000000
#define CPSRF_V 0x10000000
#define CPSRF_Q 0x08000000

#define CPSR_IT_MASK 0x0600fc00

#define FPSCRF_N  0x80000000
#define FPSCRF_Z  0x40000000
#define FPSCRF_C  0x20000000
#define FPSCRF_V  0x10000000
#define FPSCRF_QC 0x08000000

#define FPSCRM_AHP        0x04000000
#define FPSCRM_DN         0x02000000
#define FPSCRM_FZ         0x01000000

#define FPSCRM_RMODE_MASK 0x00c00000
#define FPSCRM_RMODE_RN   0x00000000
#define FPSCRM_RMODE_RP   0x00400000
#define FPSCRM_RMODE_RM   0x00800000
#define FPSCRM_RMODE_RZ   0x00c00000

#define FPSCRM_DEPRECATED 0x00370000

#define FPSCR_IDE 0x00008000
#define FPSCR_IXE 0x00001000
#define FPSCR_UFE 0x00000800
#define FPSCR_OFE 0x00000400
#define FPSCR_DZE 0x00000200
#define FPSCR_IOE 0x00000100

#define FPSCR_IDC 0x00000080
#define FPSCR_IXC 0x00000010
#define FPSCR_UFC 0x00000008
#define FPSCR_OFC 0x00000004
#define FPSCR_DZC 0x00000002
#define FPSCR_IOC 0x00000001

#define CP15_MIDR              15, 0,  0,  0, 0         // Main ID Register
#define CP15_CTR               15, 0,  0,  0, 1         // Cache Type Register
#define CP15_TCMTR             15, 0,  0,  0, 2         // TCM Type Register
#define CP15_TLBTR             15, 0,  0,  0, 3         // TLB Type Register
#define CP15_MPIDR             15, 0,  0,  0, 5         // Multiprocessor Affinity Register
#define CP15_PFR0              15, 0,  0,  1, 0         // Processor Feature Register 0
#define CP15_PFR1              15, 0,  0,  1, 1         // Processor Feature Register 1
#define CP15_DFR0              15, 0,  0,  1, 2         // Debug Feature Register 0
#define CP15_AFR0              15, 0,  0,  1, 3         // Auxiliary Feature Register 0
#define CP15_MMFR0             15, 0,  0,  1, 4         // Memory Model Feature Register 0
#define CP15_MMFR1             15, 0,  0,  1, 5         // Memory Model Feature Register 1
#define CP15_MMFR2             15, 0,  0,  1, 6         // Memory Model Feature Register 2
#define CP15_MMFR3             15, 0,  0,  1, 7         // Memory Model Feature Register 3
#define CP15_ISAR0             15, 0,  0,  2, 0         // Instruction Set Attribute Register 0
#define CP15_ISAR1             15, 0,  0,  2, 1         // Instruction Set Attribute Register 1
#define CP15_ISAR2             15, 0,  0,  2, 2         // Instruction Set Attribute Register 2
#define CP15_ISAR3             15, 0,  0,  2, 3         // Instruction Set Attribute Register 3
#define CP15_ISAR4             15, 0,  0,  2, 4         // Instruction Set Attribute Register 4
#define CP15_ISAR5             15, 0,  0,  2, 5         // Instruction Set Attribute Register 5
#define CP15_ISAR6             15, 0,  0,  2, 6
#define CP15_ISAR7             15, 0,  0,  2, 7

#define CP15_SCTLR             15, 0,  1,  0, 0         // System Control Register
#define CP15_ACTLR             15, 0,  1,  0, 1         // Auxiliary Control Register
#define CP15_CPACR             15, 0,  1,  0, 2         // Coprocessor Access Control Register
#define CP15_SCR               15, 0,  1,  1, 0         // Secure Configuration Register
#define CP15_SDER              15, 0,  1,  1, 1         // Secure Debug Enable Register
#define CP15_NSACR             15, 0,  1,  1, 2         // Non-Secure Access Control Register

#define CP15_TTBR0             15, 0,  2,  0, 0         // Translation Table Base Register 0
#define CP15_TTBR1             15, 0,  2,  0, 1         // Translation Table Base Register 1
#define CP15_TTBCR             15, 0,  2,  0, 2         // Translation Table Base Control Register
#define CP15_DACR              15, 0,  3,  0, 0         // Domain Access Control Register
#define CP15_DFSR              15, 0,  5,  0, 0         // Data Fault Status Register
#define CP15_IFSR              15, 0,  5,  0, 1         // Instruction Fault Status Register
#define CP15_DFAR              15, 0,  6,  0, 0         // Data Fault Address Register
#define CP15_IFAR              15, 0,  6,  0, 2         // Instruction Fault Address Register

#define CP15_ICIALLUIS         15, 0,  7,  1, 0         // Invalidate all instruction caches to PoU Inner Shareable
#define CP15_BPIALLIS          15, 0,  7,  1, 6         // Invalidate entire branch predictor array Inner Shareable
#define CP15_ICIALLU           15, 0,  7,  5, 0         // Invalidate all instruction caches to PoU
#define CP15_ICIMVAU           15, 0,  7,  5, 1         // Invalidate all instruction caches by MVA to PoU
#define CP15_BPIALL            15, 0,  7,  5, 6         // Invalidate entire branch predictor array
#define CP15_BPIMVA            15, 0,  7,  5, 7         // Invalidate MVA from branch predictor array
#define CP15_DCIMVAC           15, 0,  7,  6, 1         // Invalidate data cache line by MVA to PoC
#define CP15_DCISW             15, 0,  7,  6, 2         // Invalidate data cache line by set/way
#define CP15_DCCMVAC           15, 0,  7, 10, 1         // Clean data cache line by MVA to PoC
#define CP15_DCCSW             15, 0,  7, 10, 2         // Clean data cache line by set/way
#define CP15_DCCMVAU           15, 0,  7, 11, 1         // Clean data cache line by MVA to PoU
#define CP15_DCCIMVAC          15, 0,  7, 14, 1         // Clean and invalidate data cache line by MVA to PoC
#define CP15_DCCISW            15, 0,  7, 14, 2         // Clean and invalidate data cache line by set/way

#define CP15_PAR               15, 0,  7,  4, 0         // Physical Address Register (Translation Result)
#define CP15_ATS1CPR           15, 0,  7,  8, 0         // PL1 stage 1 read translation, current state
#define CP15_ATS1CPW           15, 0,  7,  8, 1         // PL1 stage 1 write translation, current state
#define CP15_ATS1CUR           15, 0,  7,  8, 2         // Unprivileged stage 1 read translation, current state
#define CP15_ATS1CUW           15, 0,  7,  8, 3         // Unprivileged stage 1 write translation, current state

#define CP15_ISB               15, 0,  7,  5, 4         // Instruction Synchronization Barrier operation
#define CP15_DSB               15, 0,  7, 10, 4         // Data Synchronization Barrier operation
#define CP15_DMB               15, 0,  7, 10, 5         // Data Memory Barrier operation

#define CP15_TLBIALLIS         15, 0,  8,  3, 0         // Invalidate entire TLB Inner Shareable
#define CP15_TLBIMVAIS         15, 0,  8,  3, 1         // Invalidate unified TLB entry by MVA Inner Shareable
#define CP15_TLBIASIDIS        15, 0,  8,  3, 2         // Invalidate unified TLB by ASID match Inner Shareable
#define CP15_TLBIMVAAIS        15, 0,  8,  3, 3         // Invalidate unified TLB entry by MVA all ASID Inner Shareable
#define CP15_TLBIALL           15, 0,  8,  7, 0         // Invalidate unified TLB
#define CP15_TLBIMVA           15, 0,  8,  7, 1         // Invalidate unified TLB entry by MVA
#define CP15_TLBIASID          15, 0,  8,  7, 2         // Invalidate unified TLB by ASID match
#define CP15_TLBIMVAA          15, 0,  8,  7, 3         // Invalidate unified TLB entries by MVA all ASID

#define CP15_PMCR              15, 0,  9, 12, 0         // Performance Monitor Control Register
#define CP15_PMCNTENSET        15, 0,  9, 12, 1         // Count Enable Set Register
#define CP15_PMCNTENCLR        15, 0,  9, 12, 2         // Count Enable Clear Register
#define CP15_PMOVSR            15, 0,  9, 12, 3         // Overflow Flag Status Register
#define CP15_PSWINC            15, 0,  9, 12, 4         // Software Increment Register
#define CP15_PMSELR            15, 0,  9, 12, 5         // Event Counter Selection Register
#define CP15_PMCCNTR           15, 0,  9, 13, 0         // Cycle Count Register
#define CP15_PMXEVTYPER        15, 0,  9, 13, 1         // Event Type Select Register
#define CP15_PMXEVCNTR         15, 0,  9, 13, 2         // Event Count Register
#define CP15_PMUSERENR         15, 0,  9, 14, 0         // User Enable Register
#define CP15_PMINTENSET        15, 0,  9, 14, 1         // Interrupt Enable Set Register
#define CP15_PMINTENCLR        15, 0,  9, 14, 2         // Interrupt Enable Clear Register

#define CP15_PRRR              15, 0, 10,  2, 0         // Primary Region Remap Register
#define CP15_NMRR              15, 0, 10,  2, 1         // Normal Memory Remap Register

#define CP15_VBAR              15, 0, 12,  0, 0         // Vector Base Address Register
#define CP15_MVBAR             15, 0, 12,  0, 1         // Monitor Vector Base Address Register
#define CP15_ISR               15, 0, 12,  1, 0         // Interrupt Status Register

#define CP15_CONTEXTIDR        15, 0, 13,  0, 1         // Context ID Register
#define CP15_TPIDRURW          15, 0, 13,  0, 2         // Software Thread ID Register, User Read/Write
#define CP15_TPIDRURO          15, 0, 13,  0, 3         // Software Thread ID Register, User Read Only
#define CP15_TPIDRPRW          15, 0, 13,  0, 4         // Software Thread ID Register, Privileged Only

#define CP15_CCSIDR            15, 1,  0,  0, 0         // Cache Size ID Register
#define CP15_CLIDR             15, 1,  0,  0, 1         // Cache Level ID Register
#define CP15_AIDR              15, 1,  0,  0, 7         // Auxiliary ID Register
#define CP15_CSSELR            15, 2,  0,  0, 0         // Cache Size Selection Register

#define CP15_CNTVCT            15, 1, 14                // Virtual counter

#define CP14_DBGDIDR           14, 0,  0,  0, 0         //   0: Debug ID Register
#define CP14_DBGDSCRint        14, 0,  0,  1, 0         //   1: Debug Status and Control Register (internal view)
#define CP14_DBGDTRRXint       14, 0,  0,  5, 0         //   5: Host to Target Data Transfer Register (internal view)
#define CP14_DBGDTRTXint       CP14_DBGDTRRXint         //   5: Target to Host Data Transfer Register (internal view)
#define CP14_DBGWFAR           14, 0,  0,  6, 0         //   6: Watchpoint Fault Address Register
#define CP14_DBGVCR            14, 0,  0,  7, 0         //   7: Vector Catch Register
#define CP14_DBGECR            14, 0,  0,  9, 0         //   9: Event Catch Register
#define CP14_DBGDSCCR          14, 0,  0, 10, 0         //  10: Debug State Cache Control Register
#define CP14_DBGDSMCR          14, 0,  0, 11, 0         //  11: Debug State MMU Control Register
#define CP14_DBGDTRRX          14, 0,  0,  0, 2         //  32: Host to Target Data Transfer Register
#define CP14_DBGPCSR           14, 0,  0,  1, 2         //  33: Program Counter Sampling Register
#define CP14_DBGITR            CP14_DBGPCSR             //  33: Instruction Transfer Register
#define CP14_DBGDSCR           14, 0,  0,  2, 2         //  34: Debug Status and Control Register (external view)
#define CP14_DBGDTRTX          14, 0,  0,  3, 2         //  35: Target to Host Data Transfer Register
#define CP14_DBGDRCR           14, 0,  0,  4, 2         //  36: Debug Run Control Register
#define CP14_DBGCIDSR          14, 0,  0,  9, 2         //  41: Context ID Sampling Register
#define CP14_DBGBVR0           14, 0,  0,  0, 4         //  64: Breakpoint Value Register 0
#define CP14_DBGBVR1           14, 0,  0,  1, 4         //  65: Breakpoint Value Register 1
#define CP14_DBGBVR2           14, 0,  0,  2, 4         //  66: Breakpoint Value Register 2
#define CP14_DBGBVR3           14, 0,  0,  3, 4         //  67: Breakpoint Value Register 3
#define CP14_DBGBVR4           14, 0,  0,  4, 4         //  68: Breakpoint Value Register 4
#define CP14_DBGBVR5           14, 0,  0,  5, 4         //  69: Breakpoint Value Register 5
#define CP14_DBGBVR6           14, 0,  0,  6, 4         //  70: Breakpoint Value Register 6
#define CP14_DBGBVR7           14, 0,  0,  7, 4         //  71: Breakpoint Value Register 7
#define CP14_DBGBVR8           14, 0,  0,  8, 4         //  72: Breakpoint Value Register 8
#define CP14_DBGBVR9           14, 0,  0,  9, 4         //  73: Breakpoint Value Register 9
#define CP14_DBGBVR10          14, 0,  0, 10, 4         //  74: Breakpoint Value Register 10
#define CP14_DBGBVR11          14, 0,  0, 11, 4         //  75: Breakpoint Value Register 11
#define CP14_DBGBVR12          14, 0,  0, 12, 4         //  76: Breakpoint Value Register 12
#define CP14_DBGBVR13          14, 0,  0, 13, 4         //  77: Breakpoint Value Register 13
#define CP14_DBGBVR14          14, 0,  0, 14, 4         //  78: Breakpoint Value Register 14
#define CP14_DBGBVR15          14, 0,  0, 15, 4         //  79: Breakpoint Value Register 15
#define CP14_DBGBCR0           14, 0,  0,  0, 5         //  80: Breakpoint Control Register 0
#define CP14_DBGBCR1           14, 0,  0,  1, 5         //  81: Breakpoint Control Register 1
#define CP14_DBGBCR2           14, 0,  0,  2, 5         //  82: Breakpoint Control Register 2
#define CP14_DBGBCR3           14, 0,  0,  3, 5         //  83: Breakpoint Control Register 3
#define CP14_DBGBCR4           14, 0,  0,  4, 5         //  84: Breakpoint Control Register 4
#define CP14_DBGBCR5           14, 0,  0,  5, 5         //  85: Breakpoint Control Register 5
#define CP14_DBGBCR6           14, 0,  0,  6, 5         //  86: Breakpoint Control Register 6
#define CP14_DBGBCR7           14, 0,  0,  7, 5         //  87: Breakpoint Control Register 7
#define CP14_DBGBCR8           14, 0,  0,  8, 5         //  88: Breakpoint Control Register 8
#define CP14_DBGBCR9           14, 0,  0,  9, 5         //  89: Breakpoint Control Register 9
#define CP14_DBGBCR10          14, 0,  0, 10, 5         //  90: Breakpoint Control Register 10
#define CP14_DBGBCR11          14, 0,  0, 11, 5         //  91: Breakpoint Control Register 11
#define CP14_DBGBCR12          14, 0,  0, 12, 5         //  92: Breakpoint Control Register 12
#define CP14_DBGBCR13          14, 0,  0, 13, 5         //  93: Breakpoint Control Register 13
#define CP14_DBGBCR14          14, 0,  0, 14, 5         //  94: Breakpoint Control Register 14
#define CP14_DBGBCR15          14, 0,  0, 15, 5         //  95: Breakpoint Control Register 15
#define CP14_DBGWVR0           14, 0,  0,  0, 6         //  96: Watchpoint Value Register 0
#define CP14_DBGWVR1           14, 0,  0,  1, 6         //  97: Watchpoint Value Register 1
#define CP14_DBGWVR2           14, 0,  0,  2, 6         //  98: Watchpoint Value Register 2
#define CP14_DBGWVR3           14, 0,  0,  3, 6         //  99: Watchpoint Value Register 3
#define CP14_DBGWVR4           14, 0,  0,  4, 6         // 100: Watchpoint Value Register 4
#define CP14_DBGWVR5           14, 0,  0,  5, 6         // 101: Watchpoint Value Register 5
#define CP14_DBGWVR6           14, 0,  0,  6, 6         // 102 Watchpoint Value Register 6
#define CP14_DBGWVR7           14, 0,  0,  7, 6         // 103: Watchpoint Value Register 7
#define CP14_DBGWVR8           14, 0,  0,  8, 6         // 104: Watchpoint Value Register 8
#define CP14_DBGWVR9           14, 0,  0,  9, 6         // 105: Watchpoint Value Register 9
#define CP14_DBGWVR10          14, 0,  0, 10, 6         // 106: Watchpoint Value Register 10
#define CP14_DBGWVR11          14, 0,  0, 11, 6         // 107: Watchpoint Value Register 11
#define CP14_DBGWVR12          14, 0,  0, 12, 6         // 108: Watchpoint Value Register 12
#define CP14_DBGWVR13          14, 0,  0, 13, 6         // 109: Watchpoint Value Register 13
#define CP14_DBGWVR14          14, 0,  0, 14, 6         // 110: Watchpoint Value Register 14
#define CP14_DBGWVR15          14, 0,  0, 15, 6         // 111: Watchpoint Value Register 15
#define CP14_DBGWCR0           14, 0,  0,  0, 7         // 112: Watchpoint Control Register 0
#define CP14_DBGWCR1           14, 0,  0,  1, 7         // 113: Watchpoint Control Register 1
#define CP14_DBGWCR2           14, 0,  0,  2, 7         // 114: Watchpoint Control Register 2
#define CP14_DBGWCR3           14, 0,  0,  3, 7         // 115: Watchpoint Control Register 3
#define CP14_DBGWCR4           14, 0,  0,  4, 7         // 116: Watchpoint Control Register 4
#define CP14_DBGWCR5           14, 0,  0,  5, 7         // 117: Watchpoint Control Register 5
#define CP14_DBGWCR6           14, 0,  0,  6, 7         // 118: Watchpoint Control Register 6
#define CP14_DBGWCR7           14, 0,  0,  7, 7         // 119: Watchpoint Control Register 7
#define CP14_DBGWCR8           14, 0,  0,  8, 7         // 120: Watchpoint Control Register 8
#define CP14_DBGWCR9           14, 0,  0,  9, 7         // 121: Watchpoint Control Register 9
#define CP14_DBGWCR10          14, 0,  0, 10, 7         // 122: Watchpoint Control Register 10
#define CP14_DBGWCR11          14, 0,  0, 11, 7         // 123: Watchpoint Control Register 11
#define CP14_DBGWCR12          14, 0,  0, 12, 7         // 124: Watchpoint Control Register 12
#define CP14_DBGWCR13          14, 0,  0, 13, 7         // 125: Watchpoint Control Register 13
#define CP14_DBGWCR14          14, 0,  0, 14, 7         // 126: Watchpoint Control Register 14
#define CP14_DBGWCR15          14, 0,  0, 15, 7         // 127: Watchpoint Control Register 15
#define CP14_DBGOSLAR          14, 0,  1,  0, 4         // 192: OS Lock Access Register
#define CP14_DBGOSLSR          14, 0,  1,  1, 4         // 193: OS Lock Status Register
#define CP14_DBGOSDLR          14, 0,  1,  3, 4         // 195: OS Double Lock Register
#define CP14_DBGPRSR           14, 0,  1,  5, 4         // 197: Device Power-dow and Reset Status Registers
#define CP14_DBGAUTHSTATUS     14, 0,  7, 14, 6         // 1006: Authentication Status
#define CP14_DBGDEVID2         14, 0,  7,  0, 7         // 1008: Debug Device ID Register 2
#define CP14_DBGDEVID1         14, 0,  7,  1, 7         // 1008: Debug Device ID Register 1
#define CP14_DBGDEVID          14, 0,  7,  2, 7         // 1008: Debug Device ID Register

#define CP14_DBGOSLSR_LOCK_IMP 0x1
#define CP14_DBGOSLSR_LOCKED   0x2

#define CP14_DBGPRSR_STICKYPD  0x2

#define CP14_DBGAUTHSTATUS_NSE  0x01                    // Non-secure invasive debug enabled
#define CP14_DBGAUTHSTATUS_NSI  0x02                    // Non-secure invasive debug features implemented
#define CP14_DBGAUTHSTATUS_NSNE 0x04                    // Non-secure non-invasive debug enabled
#define CP14_DBGAUTHSTATUS_NSNI 0x08                    // Non-secure non-invasive debug features implemented

#define CPVFP_FPSID            10, 7,  0,  0, 0         // Floating-point System ID register
#define CPVFP_FPSCR            10, 7,  1,  0, 0         // Floating-point Status and Control Register
#define CPVFP_MVFR2            10, 7,  5,  0, 0         // Media and VFP Feature Register 2
#define CPVFP_MVFR1            10, 7,  6,  0, 0         // Media and VFP Feature Register 1
#define CPVFP_MVFR0            10, 7,  7,  0, 0         // Media and VFP Feature Register 0
#define CPVFP_FPEXC            10, 7,  8,  0, 0         // Floating-Point Exception Register
#define CPVFP_FPINST           10, 7,  9,  0, 0         // Floating-Point Instruction Register
#define CPVFP_FPINST2          10, 7, 10,  0, 0         // Floating-Point Instruction Register 2

#define PFR1_SECURITY          1
#define PFR1_SECURITY_TZONE    1

#define DFR0_MMAP_DEBUG        2
#define DFR0_MMAP_DEBUG_V7     4

#define DFR0_CP14_DEBUG        0
#define DFR0_CP14_DEBUG_V7     4


#define ISAR0_BITCOUNT         1
#define ISAR0_BITCOUNT_CLZ     1

#define ISAR0_BITFIELD         2
#define ISAR0_BITFIELD_BFC_ETC 1

#define ISAR0_CMPBRANCH        3
#define ISAR0_CLZ              1

#define ISAR0_DIVIDE           6
#define ISAR0_DIVIDE_DIV       1

#define ISAR1_EXCEPT           1
#define ISAR1_EXCEPT_LDM_STM   1

#define ISAR1_EXCEPT_AR        2
#define ISAR1_EXCEPT_AR_SRS    1

#define ISAR1_EXTEND           3
#define ISAR1_EXTEND_BASIC     1
#define ISAR1_EXTEND_16        2

#define ISAR1_IFTHEN           4
#define ISAR1_IFTHEN_IT        1

#define ISAR1_IMMEDIATE        5
#define ISAR1_IMMEDIATE_MOVT   1

#define ISAR1_INTERWORK        6
#define ISAR1_INTERWORK_BX     1
#define ISAR1_INTERWORK_BLX    2
#define ISAR1_INTERWORK_THUMB2 3

#define ISAR2_LOADSTORE        0
#define ISAR2_LOADSTORE_LDRD   1
#define ISAR2_LOADSTORE_ACQREL 2

#define ISAR2_MEMHINT          1
#define ISAR2_MEMHINT_PLD      1
#define ISAR2_MEMHINT_PLD2     2
#define ISAR2_MEMHINT_PLI      3
#define ISAR2_MEMHINT_PLDW     4

#define ISAR2_MULT             3
#define ISAR2_MULT_MLA         1
#define ISAR2_MULT_MLS         2

#define ISAR2_MULTS            4
#define ISAR2_MULTS_SMULL      1
#define ISAR2_MULTS_SMLABB     2
#define ISAR2_MULTS_SMLAD      3

#define ISAR2_MULTU            5
#define ISAR2_UMULL            1
#define ISAR2_UMAAL            2

#define ISAR2_PSR_AR           6
#define ISAR2_PSR_AR_MRS_MSR   1

#define ISAR2_REVERSAL         7
#define ISAR2_REVERSAL_REV     1
#define ISAR2_REVERSAL_RBIT    2

#define ISAR3_SATURATE         0
#define ISAR3_SATURATE_QADD    1

#define ISAR3_SIMD             1
#define ISAR3_SIMD_SSAT        1
#define ISAR3_SIMD_PKHBT       3

#define ISAR3_SVC              2
#define ISAR3_SVC_SVC          1

#define ISAR3_SYNCHPRIM        3
#define ISAR3_SYNCHPRIM_LDREX  1
#define ISAR3_SYNCHPRIM_LDREXD 2

#define ISAR3_TABBRANCH        4
#define ISAR3_TABBRANCH_TBB    1

#define ISAR3_THUMBCOPY        5
#define ISAR3_THUMBCOPY_MOV    1

#define ISAR3_TRUENOP          6
#define ISAR3_TRUENOP_NOP      1

#define ISAR4_UNPRIV           0
#define ISAR4_UNPRIV_LDRT      1
#define ISAR4_UNPRIV_LDRHT     2

#define ISAR4_WITHSHIFTS       1
#define ISAR4_WITHSHIFTS_LDSTR 1
#define ISAR4_WITHSHIFTS_CONST 3
#define ISAR4_WITHSHIFTS_REG   4

#define ISAR4_WRITEBACK        2
#define ISAR4_WRITEBACK_FULL   1

#define ISAR4_SMC              3
#define ISAR4_SMC_SMC          1

#define ISAR4_BARRIER          4
#define ISAR4_BARRIER_DMB      1

#define ISAR4_SYNCHPRIM_FRAC   5
#define ISAR4_SYNCHPRIM_FRAC_CLREX 3

#define ISAR5_SEVL             0
#define ISAR5_SEVL_IMP         1

#define ISAR5_AES              1
#define ISAR5_AES_AESE         1
#define ISAR5_AES_PMULL        2

#define ISAR5_SHA1             2
#define ISAR5_SHA1_SHA1C       1

#define ISAR5_SHA2             3
#define ISAR5_SHA2_SHA256H     1

#define ISAR5_CRC32            4
#define ISAR5_CRC32_IMP        1


#define MMFR0_VMSA             0
#define MMFR0_VMSA_V7PXN       4
#define MMFR0_VMSA_LPAE        5

#define MMFR0_L1SHARED         2
#define MMFR0_L1SHARED_L1      1

#define MMFR1_L1HVRD           4
#define MMFR1_L1HVRD_REQ       2

#define MMFR1_L1UNIFIED        5
#define MMFR1_L1UNIFIED_REQ    2

#define MMFR2_UTLB             4
#define MMFR2_UTLB_VA_ALL      3

#define MMFR3_BCAST            3
#define MMFR3_BCAST_ALL        2

#define MMFR3_HPW              5
#define MMFR3_HPW_COHERENT     1

#define MMFR3_L1HIER_CACHE     0

#define READ_ARM_FEATURE(_FeatureRegister, _Index) \
        (((ULONG)_MoveFromCoprocessor(_FeatureRegister) >> ((_Index) * 4)) & 0xF)

#define MVFR0_VFPRND            7
#define MVFR0_VFPRND_ALL        1

#define MVFR0_VFPVEC            6
#define MVFR0_VFPVEC_SUPPORTED  1

#define MVFR0_FSQRT             5
#define MVFR0_FSQRT_SUPPORTED   1

#define MVFR0_FDIV              4
#define MVFR0_FDIV_SUPPORTED    1

#define MVFR0_FPEX              3
#define MVFR0_FPEX_SUPPORTED    1

#define MVFR0_VDPREC            2
#define MVFR0_VDPREC_V3         2

#define MVFR0_VSPREC            1
#define MVFR0_VSPREC_V3         2

#define MVFR0_AREGS             0
#define MVFR0_AREGS_16          1
#define MVFR0_AREGS_32          2

#define MVFR1_ASFMAC            7
#define MVFR1_ASFMAC_SUPPORTED  1

#define MVFR1_VHPREC            6
#define MVFR1_VHPREC_SUPPORTED  1

#define MVFR1_AHPREC            5
#define MVFR1_AHPREC_SUPPORTED  1

#define MVFR1_ASPREC            4
#define MVFR1_ASPREC_SUPPORTED  1

#define MVFR1_AINT              3
#define MVFR1_AINT_SUPPORTED    1

#define MVFR1_ALDSTR            2
#define MVFR1_ALDSTR_SUPPORTED  1

#define MVFR1_VDNAN             1
#define MVFR1_VDNAN_SUPPORTED   1

#define MVFR1_VFTZ              0
#define MVFR1_VFTZ_SUPPORTED    1

#define MVFR2_FPMISC            1
#define MVFR2_FPMISC_FPSEL      1
#define MVFR2_FPMISC_ROUNDING   2
#define MVFR2_FPMISC_RINT       3
#define MVFR2_FPMISC_MINMAX     4

#define MVFR2_SIMDMISC          0
#define MVFR2_SIMDMISC_ROUNDING 1
#define MVFR2_SIMDMISC_RINT     2
#define MVFR2_SIMDMISC_MINMAX   3

#define CPVFP_FPSID_SW                  0x00800000      // Software-only floating-point

#define CPVFP_FPEXC_EX                  0x80000000      // Extra state required for context save
#define CPVFP_FPEXC_EN                  0x40000000      // VFP/Advanced SIMD enable
#define CPVFP_FPEXC_DEX                 0x20000000      // synchronous exception flag
#define CPVFP_FPEXC_FP2V                0x10000000      // FPINST2 is valid

#define CP15_CPACR_D32DIS               0x80000000      // Disable d16-d31 (support optional)
#define CP15_CPACR_ASEDIS               0x40000000      // Disable Advanced SIMD (support optional)
#define CP15_CPACR_VFP_MASK             0x00f00000      // Mask for enabling/disabling VFP/NEON access

#define CP15_NSACR_NSASEDIS             0x00008000      // Disable non-secure Advanced SIMD functionality
#define CP15_NSACR_NSD32DIS             0x00004000      // Disable non-secure use of d16-d31
#define CP15_NSACR_VFP_USERMODE         0x00000c00      // Enable CP10/CP11 in user mode

#define ARM_MPIDR_MPEXT                0x80000000
#define ARM_MPIDR_UP                   0x40000000
#define ARM_MPIDR_MT                   0x01000000
                                                  // ARMv7 ARMv7VE ARMv8
#define CP15_SCTLR_M                    0x00000001  //   x      x      x
#define CP15_SCTLR_A                    0x00000002  //   x      x      x
#define CP15_SCTLR_C                    0x00000004  //   x      x      x
                                     // 0x00000008  //   1      1      1
                                     // 0x00000010  //   1      1      1
#define CP15_SCTLR_CP15BEN              0x00000020  //   x      x      x  (was _D)
#define CP15_SCTLR_THEE                 0x00000040  //   1      1      x
#define CP15_SCTLR_ITD                  0x00000080  //   0      0      x
#define CP15_SCTLR_SED                  0x00000100  //   0      0      x
                                     // 0x00000200  //   0      0      0
#define CP15_SCTLR_SW                   0x00000400  //   x      x      0  (was _F)
#define CP15_SCTLR_Z                    0x00000800  //   x      x      1
#define CP15_SCTLR_I                    0x00001000  //   x      x      x
#define CP15_SCTLR_V                    0x00002000  //   x      x      x
#define CP15_SCTLR_RR                   0x00004000  //   x      x      0
                                     // 0x00008000  //   0      0      0
#define CP15_SCTLR_nTWI                 0x00010000  //   1      1      x
#define CP15_SCTLR_HA                   0x00020000  //   x      x      0
#define CP15_SCTLR_nTWE                 0x00040000  //   1      1      x
#define CP15_SCTLR_WXN                  0x00080000  //   0      x      x
#define CP15_SCTLR_UWXN                 0x00100000  //   0      x      x
#define CP15_SCTLR_FI                   0x00200000  //   x      x      0
                                     // 0x00400000  //   1      1      1
                                     // 0x00800000  //   1      1      1
#define CP15_SCTLR_VE                   0x01000000  //   x      x      0
#define CP15_SCTLR_EE                   0x02000000  //   x      x      x
                                     // 0x04000000  //   0      0      0
#define CP15_SCTLR_NMFI                 0x08000000  //   x      0      0
#define CP15_SCTLR_TRE                  0x10000000  //   x      x      x
#define CP15_SCTLR_AFE                  0x20000000  //   x      x      x
#define CP15_SCTLR_TE                   0x40000000  //   x      x      x
                                     // 0x80000000  //   0      0      0

#define CP15_RES1_MASK                  0x00c00018

#define CP15_TTBRx_PD_MASK              0xffffc000

#define CP15_TTBRx_INNER_CACHED         0x01
#define CP15_TTBRx_INNER_SHARED         0x02
#define CP15_TTBRx_ECC                  0x04
#define CP15_TTBRx_OUTER_CACHED         0x08
#define CP15_TTBRx_OUTER_UNSHARED       0x20

#define CP15_TTBRx_VALID_NOMP_MASK      0x3f

#define CP15_TTBRx_VALID_MASK           0x1f

#define CP15_TTBRx_MPEXT_INNER_NC       0x00
#define CP15_TTBRx_MPEXT_INNER_WBWA     0x40
#define CP15_TTBRx_MPEXT_INNER_WT       0x01
#define CP15_TTBRx_MPEXT_INNER_WB       0x41

#define CP15_TTBRx_MPEXT_OUTER_NC       0x00
#define CP15_TTBRx_MPEXT_OUTER_WBWA     0x08
#define CP15_TTBRx_MPEXT_OUTER_WT       0x10
#define CP15_TTBRx_MPEXT_OUTER_WB       0x18

#define CP15_TTBRx_MPEXT_INNER_CACHED   CP15_TTBRx_MPEXT_INNER_WBWA
#define CP15_TTBRx_MPEXT_OUTER_CACHED   CP15_TTBRx_MPEXT_OUTER_WBWA

#define CP15_TTBRx_VALID_MPEXT_MASK     0x7f

#define CP15_xFSR_FS_LOW                0x0000000f
#define CP15_xFSR_FS_HIGH               0x00000400
#define CP15_DFSR_WnR                   0x00000800

#define CP15_PMCR_DP                    0x00000020
#define CP15_PMCR_X                     0x00000010
#define CP15_PMCR_CLKCNT_DIV            0x00000008
#define CP15_PMCR_CLKCNT_RST            0x00000004
#define CP15_PMCR_CNT_RST               0x00000002
#define CP15_PMCR_ENABLE                0x00000001

#define CP15_PMCNTEN_PMCCNT             0x80000000

#define CP15_PMUSERENR_EN               0x00000001

#define CP15_CONTEXTIDR_ASID_MASK       0x000000ff
#define CP15_CONTEXTIDR_CONTEXT_MASK    0xffffff00

CFORCEINLINE
VOID
_SyncPte (
    VOID)
{
    _DataSynchronizationBarrier();
    _InstructionSynchronizationBarrier();
}

#define SWFS_WRITE                      0x01
#define SWFS_EXECUTE                    0x08
#define SWFS_PAGE_FAULT                 0x10
#define SWFS_ALIGN_FAULT                0x20
#define SWFS_HWERR_FAULT                0x40
#define SWFS_DEBUG_FAULT                0x80

#define CP15_PRRR_MEMTYPE_STRONG        0
#define CP15_PRRR_MEMTYPE_DEVICE        1
#define CP15_PRRR_MEMTYPE_NORMAL        2

#define CP15_PRRR_NOS7                  0x80000000
#define CP15_PRRR_NOS6                  0x40000000
#define CP15_PRRR_NOS5                  0x20000000
#define CP15_PRRR_NOS4                  0x10000000
#define CP15_PRRR_NOS3                  0x08000000
#define CP15_PRRR_NOS2                  0x04000000
#define CP15_PRRR_NOS1                  0x02000000
#define CP15_PRRR_NOS0                  0x01000000
#define CP15_PRRR_NS1                   0x00080000
#define CP15_PRRR_NS0                   0x00040000
#define CP15_PRRR_DS1                   0x00020000
#define CP15_PRRR_DS0                   0x00010000

#define CP15_CR10_PRRR_UNSHARED \
         ((CP15_PRRR_MEMTYPE_NORMAL << 0) | (CP15_PRRR_MEMTYPE_NORMAL << 8) | \
          (CP15_PRRR_MEMTYPE_STRONG << 2) | (CP15_PRRR_MEMTYPE_STRONG << 10) | \
          (CP15_PRRR_MEMTYPE_NORMAL << 4) | (CP15_PRRR_MEMTYPE_NORMAL << 12) | \
          (CP15_PRRR_MEMTYPE_NORMAL << 6) | (CP15_PRRR_MEMTYPE_NORMAL << 14) | \
          CP15_PRRR_DS0 | CP15_PRRR_DS1 | \
          CP15_PRRR_NOS0 | CP15_PRRR_NOS1 | CP15_PRRR_NOS2 | CP15_PRRR_NOS3 | \
          CP15_PRRR_NOS4 | CP15_PRRR_NOS5 | CP15_PRRR_NOS6 | CP15_PRRR_NOS7)

#define CP15_CR10_PRRR_SHARED (CP15_CR10_PRRR_UNSHARED | CP15_PRRR_NS0 | CP15_PRRR_NS1)

#define CP15_NMRR_CACHE_NC              0
#define CP15_NMRR_CACHE_WBWA            1
#define CP15_NMRR_CACHE_WTNA            2

#define CP15_NMRR_DEFAULT \
        (ULONG) ((CP15_NMRR_CACHE_WBWA << 0) | \
                 (CP15_NMRR_CACHE_WBWA << 2) | \
                 (CP15_NMRR_CACHE_WTNA << 4) | \
                 (CP15_NMRR_CACHE_NC   << 6) | \
                 (CP15_NMRR_CACHE_WBWA << 8) | \
                 (CP15_NMRR_CACHE_WBWA << 10) | \
                 (CP15_NMRR_CACHE_WTNA << 12) | \
                 (CP15_NMRR_CACHE_NC   << 14) | \
                 (CP15_NMRR_CACHE_WBWA << 16) | \
                 (CP15_NMRR_CACHE_WBWA << 18) | \
                 (CP15_NMRR_CACHE_WBWA << 20) | \
                 (CP15_NMRR_CACHE_NC   << 22) | \
                 (CP15_NMRR_CACHE_WBWA << 24) | \
                 (CP15_NMRR_CACHE_WBWA << 26) | \
                 (CP15_NMRR_CACHE_WBWA << 28) | \
                 (CP15_NMRR_CACHE_NC   << 30))

#define CP14_DBGBCR_MISMATCH_BIT        0x00400000
#define CP14_DBGBCR_SECURITY_BITS       0x0000c000
#define   CP14_DBGBCR_ANY_SECURE        0x00000000
#define   CP14_DBGBCR_NONSECURE_ONLY    0x00004000
#define   CP14_DBGBCR_SECURE_ONLY       0x00008000
#define CP14_DBGBCR_PRIVILEGE_BITS      0x00000006
#define   CP14_DBGBCR_USER_SYS_SUPER    0x00000000
#define   CP14_DBGBCR_PRIVILEGED_ONLY   0x00000002
#define   CP14_DBGBCR_USER_ONLY         0x00000004
#define   CP14_DBGBCR_ANY_PRIVILEGE     0x00000006
#define CP14_DBGBCR_ENABLE_BIT          0x00000001

#define CP14_DBGDSCR_MOE_MASK           0x0000003c
#define CP14_DBGDSCR_MOE_SHIFT          2
#define CP14_DBGDSCR_MOE_HALT           0x00000000
#define CP14_DBGDSCR_MOE_BP             0x00000001
#define CP14_DBGDSCR_MOE_WPASYNC        0x00000002
#define CP14_DBGDSCR_MOE_BKPT           0x00000003
#define CP14_DBGDSCR_MOE_EXTERNAL       0x00000004
#define CP14_DBGDSCR_MOE_VECTOR         0x00000005
#define CP14_DBGDSCR_MOE_WPSYNC         0x0000000a

#define CP14_DBGDSCR_UDCCdis            0x00001000
#define CP14_DBGDSCR_RXfull             0x40000000
#define CP14_DBGDSCR_TXfull             0x20000000

int
_ReadStatusReg (
    int Cpsr);

#pragma intrinsic(_ReadStatusReg)

#define KeGetDcacheFillSize() 1L


VOID
KeFlushIoRectangle (
    _In_ PMDL Mdl,
    _In_ PVOID Start,
    _In_ ULONG Width,
    _In_ ULONG Height,
    _In_ ULONG Stride,
    _In_ BOOLEAN ReadOperation);

#define ExAcquireSpinLock(Lock, OldIrql) KeAcquireSpinLock((Lock), (OldIrql))
#define ExReleaseSpinLock(Lock, OldIrql) KeReleaseSpinLock((Lock), (OldIrql))
#define ExAcquireSpinLockAtDpcLevel(Lock) KeAcquireSpinLockAtDpcLevel(Lock)
#define ExReleaseSpinLockFromDpcLevel(Lock) KeReleaseSpinLockFromDpcLevel(Lock)

#if defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_)
#define KeQueryTickCount(CurrentCount) { \
    KSYSTEM_TIME volatile *_TickCount = *((PKSYSTEM_TIME *)(&KeTickCount)); \
    for (;;) {                                                              \
        (CurrentCount)->HighPart = _TickCount->High1Time;                   \
        (CurrentCount)->LowPart = _TickCount->LowPart;                      \
        if ((CurrentCount)->HighPart == _TickCount->High2Time) break;       \
        YieldProcessor();                                                   \
    }                                                                       \
}
#else
VOID
NTAPI
KeQueryTickCount (
    OUT PLARGE_INTEGER CurrentCount);
#endif // defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_)

typedef struct _HARDWARE_PTE {
    ULONG Valid : 2;            // Bit 0 is NX only if bit 1 is true
    ULONG CacheType : 2;
    ULONG Accessed : 1;
    ULONG Owner : 1;
    ULONG TypeExtension : 1;    // always zero
    ULONG Writable : 1;         // OS managed
    ULONG CopyOnWrite : 1;      // OS managed
    ULONG ReadOnly : 1;         // Inverse of Dirty
    ULONG LargePage : 1;        // OS managed
    ULONG NonGlobal : 1;
    ULONG PageFrameNumber : 20;
} HARDWARE_PTE, *PHARDWARE_PTE;

typedef struct _HARDWARE_PDE {
    ULONG Valid : 2;        // 1 == valid "coarse" 4k pde.  0 == invalid.
                            // 2 == section (large).
                            // 3 == fine pde (not used by Mm)

    ULONG ImplementationDefined : 3;
    ULONG Domain : 4;       // 0 == kernel, 1 == user, other 14 unused
    ULONG MustBeZero : 1;   // as per the ARM spec
    ULONG PageFrameNumberLower : 2;
    ULONG PageFrameNumber : 20;
} HARDWARE_PDE, *PHARDWARE_PDE;

#define INITIALIZE_DIRECTORY_TABLE_BASE(dirbase,pfn) \
     *((PULONG)(dirbase)) = (((ULONG)(pfn)) << PAGE_SHIFT)

typedef struct _KSPECIAL_REGISTERS {

    ULONG Reserved[7];
    ULONG Cp15_Cr13_UsrRW;
    ULONG Cp15_Cr13_UsrRO;
    ULONG Cp15_Cr13_SvcRW;
    ULONG KernelBvr[ARM_MAX_BREAKPOINTS];
    ULONG KernelBcr[ARM_MAX_BREAKPOINTS];
    ULONG KernelWvr[ARM_MAX_WATCHPOINTS];
    ULONG KernelWcr[ARM_MAX_WATCHPOINTS];
    ULONG Fpexc;
    ULONG Fpinst;
    ULONG Fpinst2;
    ULONG UserSp;
    ULONG UserLr;
    ULONG AbortSp;
    ULONG AbortLr;
    ULONG AbortSpsr;
    ULONG UdfSp;
    ULONG UdfLr;
    ULONG UdfSpsr;
    ULONG IrqSp;
    ULONG IrqLr;
    ULONG IrqSpsr;
} KSPECIAL_REGISTERS, *PKSPECIAL_REGISTERS;

typedef struct _KARM_ARCH_STATE
{
    ULONG Cp15_Cr0_CpuId;
    ULONG Cp15_Cr1_Control;
    ULONG Cp15_Cr1_AuxControl;
    ULONG Cp15_Cr1_Cpacr;
    ULONG Cp15_Cr2_TtbControl;
    ULONG Cp15_Cr2_Ttb0;
    ULONG Cp15_Cr2_Ttb1;
    ULONG Cp15_Cr3_Dacr;
    ULONG Cp15_Cr5_Dfsr;
    ULONG Cp15_Cr5_Ifsr;
    ULONG Cp15_Cr6_Dfar;
    ULONG Cp15_Cr6_Ifar;
    ULONG Cp15_Cr9_PmControl;
    ULONG Cp15_Cr9_PmCountEnableSet;
    ULONG Cp15_Cr9_PmCycleCounter;
    ULONG Cp15_Cr9_PmEventCounter[MAX_EVENT_COUNTERS];
    ULONG Cp15_Cr9_PmEventType[MAX_EVENT_COUNTERS];
    ULONG Cp15_Cr9_PmInterruptSelect;
    ULONG Cp15_Cr9_PmOverflowStatus;
    ULONG Cp15_Cr9_PmSelect;
    ULONG Cp15_Cr9_PmUserEnable;
    ULONG Cp15_Cr10_PrimaryMemoryRemap;
    ULONG Cp15_Cr10_NormalMemoryRemap;
    ULONG Cp15_Cr12_VBARns;
    ULONG Cp15_Cr13_ContextId;
} KARM_ARCH_STATE, *PKARM_ARCH_STATE;

typedef struct _KPROCESSOR_STATE {
    KSPECIAL_REGISTERS SpecialRegisters;
    KARM_ARCH_STATE ArchState;
    CONTEXT ContextFrame;
} KPROCESSOR_STATE, *PKPROCESSOR_STATE;

typedef struct __declspec(align(16)) _KARM_MINI_STACK {
    ULONG Pc;
    ULONG Cpsr;
    ULONG R4;
    ULONG R5;
    ULONG R6;
    ULONG R7;
    ULONG Reserved[2];
} KARM_MINI_STACK, *PKARM_MINI_STACK;

typedef enum {
    CPU_UNKNOWN,
    CPU_ARM,
    CPU_QUALCOMM
} CPU_VENDORS;

#define PRCB_MAJOR_VERSION 1
#define PRCB_MINOR_VERSION 1

#define PRCB_BUILD_DEBUG 0x1
#define PRCB_BUILD_UNIPROCESSOR 0x2

#define MAXIMUM_CACHES 6

typedef struct _KPRCB
{
    UCHAR LegacyNumber;
    UCHAR ReservedMustBeZero;
    BOOLEAN IdleHalt;
    struct _KTHREAD *CurrentThread;
    struct _KTHREAD *NextThread;
    struct _KTHREAD *IdleThread;
    UCHAR NestingLevel;
    BOOLEAN ClockOwner;
    union {
        UCHAR PendingTickFlags;

        struct {
            UCHAR PendingTick:1;
            UCHAR PendingBackupTick:1;
        };
    };

    UCHAR IdleState;
    ULONG Number;
    KSPIN_LOCK PrcbLock;
    PSCHAR PriorityState;
    KPROCESSOR_STATE ProcessorState;
    USHORT ProcessorModel;
    USHORT ProcessorRevision;
    ULONG MHz;
    ULONG64 CycleCounterFrequency;
    ULONG HalReserved[15];
    USHORT MinorVersion;
    USHORT MajorVersion;
    UCHAR BuildType;
    UCHAR CpuVendor;
    UCHAR CoresPerPhysicalProcessor;
    UCHAR LogicalProcessorsPerCore;
    PVOID AcpiReserved;
    KAFFINITY GroupSetMember;
    UCHAR Group;
    UCHAR GroupIndex;
} KPRCB, *PKPRCB, *RESTRICTED_POINTER PRKPRCB;

C_ASSERT(FIELD_OFFSET(KPRCB, HalReserved) == 0x3D0);  // Do not move field
C_ASSERT(FIELD_OFFSET(KPRCB, AcpiReserved) == 0x414); // Do not move field

#define PCR_MINOR_VERSION 1
#define PCR_MAJOR_VERSION 1

typedef struct _KPCR
{
    union {
        NT_TIB NtTib;
        struct {
            ULONG TibPad0[2];
            PVOID Spare1;
            struct _KPCR *Self;
            struct _KPRCB *CurrentPrcb;
            PKSPIN_LOCK_QUEUE LockArray;
            PVOID Used_Self;
        };
    };

    KIRQL CurrentIrql;
    UCHAR SecondLevelCacheAssociativity;
    ULONG Unused0[3];
    USHORT MajorVersion;
    USHORT MinorVersion;
    ULONG StallScaleFactor;
    PVOID Unused1[3];

    ULONG KernelReserved[15];
    ULONG SecondLevelCacheSize;
    union {
        USHORT SoftwareInterruptPending;
        struct {
            UCHAR ApcInterrupt;
            UCHAR DispatchInterrupt;
        };
    };

    USHORT InterruptPad;
    ULONG HalReserved[32];
    PVOID KdVersionBlock;
    PVOID Unused3;
    ULONG PcrAlign1[8];

    PVOID Idt[256];
    PVOID *IdtExt;

    ULONG PcrAlign2[19];

    KPRCB Prcb;

} KPCR, *PKPCR;

typedef union _ARM_IDCODE {
    ULONG Ulong;
    struct {
        ULONG MinorRevision :  4;
        ULONG Model         : 12;
        ULONG Architecture  :  4;
        ULONG Revision      :  4;
        ULONG Implementer   :  8;
    };
} ARM_IDCODE, *PARM_IDCODE;

C_ASSERT(sizeof(ARM_IDCODE) == 4);

#define CP15_CR0_HARVARD_CACHE (1 << 24)

#define ARM_L1_ICACHE_UNKNOWN 0
#define ARM_L1_ICACHE_VIVT    1
#define ARM_L1_ICACHE_VIPT    2
#define ARM_L1_ICACHE_PIPT    3

typedef union _ARM_CACHE_TYPE {
    ULONG Ulong;
    struct {
        ULONG IMinLine               : 4;
        ULONG Reserved               : 10;
        ULONG IPolicy                : 2;
        ULONG DMinLine               : 4;
        ULONG Reserved2              : 12;
    };
} ARM_CACHE_TYPE, *PARM_CACHE_TYPE;

C_ASSERT(sizeof(ARM_CACHE_TYPE) == 4);

#define ARM_CACHE_NONE        0
#define ARM_CACHE_INSTRUCTION 1
#define ARM_CACHE_DATA        2
#define ARM_CACHE_HARVARD     3
#define ARM_CACHE_UNIFIED     4

typedef union _ARM_CACHE_LEVEL_ID {
    ULONG Ulong;
    struct {
        ULONG Level1 : 3;
        ULONG Level2 : 3;
        ULONG Level3 : 3;
        ULONG Level4 : 3;
        ULONG Level5 : 3;
        ULONG Level6 : 3;
        ULONG Level7 : 3;
        ULONG LoUIS  : 3;
        ULONG LoC    : 3;
        ULONG LoU    : 3;
    };
} ARM_CACHE_LEVEL_INFO;

C_ASSERT(sizeof(ARM_CACHE_LEVEL_INFO) == 4);

#define ARM_CACHE_SELECT_DATA_OR_UNIFIED 0
#define ARM_CACHE_SELECT_INSTRUCTION     1

typedef union _ARM_CACHE_INFO_SELECTOR {
    ULONG Ulong;
    struct {
        ULONG Select : 1;
        ULONG Level  : 3;
    };
} ARM_CACHE_INFO_SELECTOR;

C_ASSERT(sizeof(ARM_CACHE_INFO_SELECTOR) == 4);

typedef union _ARM_CACHE_INFO {
    ULONG Ulong;
    struct {
        ULONG LineSize           : 3;
        ULONG Associativity      : 10;
        ULONG NumberOfSets       : 15;
        ULONG WriteThrough       : 1;
        ULONG WriteBack          : 1;
        ULONG ReadAllocate       : 1;
        ULONG WriteAllocate      : 1;
    };
} ARM_CACHE_INFO;

C_ASSERT(sizeof(ARM_CACHE_INFO) == 4);

#define THUMB_BREAKPOINT                0xDEFE
#define THUMB_DEBUG_SERVICE             0xDEFD
#define THUMB_ASSERT                    0xDEFC
#define THUMB_FASTFAIL                  0xDEFB
#define THUMB_READ_CYCLES               0xDEFA
#define THUMB_DIVIDE_BY_0               0xDEF9
#define THUMB_EXIT_32BIT_MODE           0xDEF8

typedef struct _KEXCEPTION_FRAME
{
    ULONG Param5;
    ULONG TrapFrame;
    ULONG OutputBuffer;
    ULONG OutputLength;
    ULONG Pad;
    ULONG R4;
    ULONG R5;
    ULONG R6;
    ULONG R7;
    ULONG R8;
    ULONG R9;
    ULONG R10;
    ULONG R11;
    ULONG Return;
} KEXCEPTION_FRAME, *PKEXCEPTION_FRAME;

#define KEXCEPTION_FRAME_LENGTH sizeof(KEXCEPTION_FRAME)

C_ASSERT((sizeof(KEXCEPTION_FRAME) & STACK_ROUND) == 0);
C_ASSERT((FIELD_OFFSET(KEXCEPTION_FRAME, Return) + sizeof(ULONG)) == sizeof(KEXCEPTION_FRAME));

#define EXCEPTION_RECORD_LENGTH ((sizeof(EXCEPTION_RECORD) + STACK_ROUND - 1) & ~STACK_ROUND)

typedef struct _MACHINE_FRAME {
    ULONG Sp;
    ULONG Pc;
} MACHINE_FRAME, *PMACHINE_FRAME;

#define MACHINE_FRAME_LENGTH sizeof(MACHINE_FRAME)

C_ASSERT((sizeof(MACHINE_FRAME) & STACK_ROUND) == 0);

typedef struct _KSWITCH_FRAME
{
    KIRQL ApcBypass;
    UCHAR Fill[7];
    ULONG R11;
    ULONG Return;
} KSWITCH_FRAME, *PKSWITCH_FRAME;

#define KSWITCH_FRAME_LENGTH sizeof(KSWITCH_FRAME)

C_ASSERT((sizeof(KSWITCH_FRAME) & STACK_ROUND) == 0);

typedef struct _KSTART_FRAME
{
    ULONG R0;
    ULONG R1;
    ULONG R2;
    ULONG Return;
} KSTART_FRAME, *PKSTART_FRAME;

#define KSTART_FRAME_LENGTH sizeof(KSTART_FRAME)

C_ASSERT((sizeof(KSTART_FRAME) & STACK_ROUND) == 0);

typedef struct _KARM_VFP_STATE
{
    struct _KARM_VFP_STATE *Link;           // link to next state entry
    ULONG Fpscr;                            // FPSCR register
    ULONG Reserved;                         // reserved for future use
    ULONG Reserved2;                        // reserved for future use
    ULONGLONG VfpD[32];                     // All D registers (0-31)
} KARM_VFP_STATE, *PKARM_VFP_STATE;

#define KTRAP_FRAME_ARGUMENTS (14 * 4)       // up to 14 in-memory syscall args

typedef struct _KTRAP_FRAME
{
    ULONG Arg3;                         // page faults only
    ULONG FaultStatus;                  // page faults only
    union {
        ULONG FaultAddress;             // page faults only
        ULONG TrapFrame;                // system services only
    };
    ULONG Reserved;                     // always valid, internal use
    UCHAR ExceptionActive;              // always valid
    UCHAR ContextFromKFramesUnwound;    // set if KeContextFromKFrames created this frame
    UCHAR DebugRegistersValid;          // always valid
    union
    {
        KPROCESSOR_MODE PreviousMode;   // system services only
        KIRQL PreviousIrql;             // interrupts only
    };

    PKARM_VFP_STATE VfpState;
    ULONG Bvr[ARM_MAX_BREAKPOINTS];
    ULONG Bcr[ARM_MAX_BREAKPOINTS];
    ULONG Wvr[ARM_MAX_WATCHPOINTS];
    ULONG Wcr[ARM_MAX_WATCHPOINTS];
    ULONG R0;
    ULONG R1;
    ULONG R2;
    ULONG R3;
    ULONG R12;
    ULONG Sp;
    ULONG Lr;
    ULONG R11;
    ULONG Pc;
    ULONG Cpsr;

} KTRAP_FRAME, *PKTRAP_FRAME;

#define KEXCEPTION_ACTIVE_INTERRUPT_FRAME 0
#define KEXCEPTION_ACTIVE_EXCEPTION_FRAME 1
#define KEXCEPTION_ACTIVE_SERVICE_FRAME   2

#define KTRAP_FRAME_LENGTH sizeof(KTRAP_FRAME)

C_ASSERT((sizeof(KTRAP_FRAME) & STACK_ROUND) == 0);

#define ARM_RED_ZONE_BYTES      8


NTKERNELAPI
NTSTATUS
KiConnectHalInterrupt (
    _Inout_ PVOID Interrupt
    );

NTKERNELAPI
VOID
KiReplayInterrupt (
    _In_ ULONG Vector,
    _In_ KIRQL Irql,
    _In_ KIRQL PreviousIrql,
    _In_ ULONG OpaqueToken
    );

NTKERNELAPI
VOID
KeProfileInterruptWithSource (
    _In_ PKTRAP_FRAME TrapFrame,
    _In_ KPROFILE_SOURCE ProfileSource
    );

typedef KEXCEPTION_FRAME KCALLOUT_FRAME;
typedef PKEXCEPTION_FRAME PKCALLOUT_FRAME;

typedef struct _UCALLOUT_FRAME {
    PVOID Buffer;
    ULONG Length;
    ULONG ApiNumber;
    ULONG OriginalLr;
    MACHINE_FRAME MachineFrame;
} UCALLOUT_FRAME, *PUCALLOUT_FRAME;

C_ASSERT((sizeof(UCALLOUT_FRAME) & STACK_ROUND) == 0);

typedef struct _KFLOATING_SAVE {
    ULONG Dummy;
} KFLOATING_SAVE, *PKFLOATING_SAVE;

#define PDE_BASE 0xC0300000
#define PTE_BASE 0xC0000000

#define PTE_TOP  0xC03FFFFF
#define PDE_TOP  0xC0300FFF

#define PDI_SHIFT 22
#define PTI_SHIFT 12

#define PTE_PER_PAGE (PAGE_SIZE / sizeof(ULONG))
#define PDE_PER_PAGE (PAGE_SIZE / sizeof(ULONG))

#define MM_HIGHEST_USER_ADDRESS MmHighestUserAddress
#define MM_SYSTEM_RANGE_START MmSystemRangeStart

#if defined(_LOCAL_COPY_USER_PROBE_ADDRESS_)

#define MM_USER_PROBE_ADDRESS _LOCAL_COPY_USER_PROBE_ADDRESS_

#if defined(__CONVERGED_WIN32K_DRIVER__)
extern DLLBASEEXPORT ULONG _LOCAL_COPY_USER_PROBE_ADDRESS_;
#else
extern ULONG _LOCAL_COPY_USER_PROBE_ADDRESS_;
#endif

#else

#define MM_USER_PROBE_ADDRESS MmUserProbeAddress

#endif

#define MM_KSEG0_BASE       MM_SYSTEM_RANGE_START
#define MM_SYSTEM_SPACE_END 0xFFFFFFFF

#define MM_LOWEST_USER_ADDRESS (PVOID)(LONG_PTR)0x10000

#define MmGetProcedureAddress(Address) (Address)
#define MmLockPagableCodeSection(Address) MmLockPagableDataSection(Address)

#define CPSR_KERNEL_SANITIZE 0xFF0FFCE0

#define CPSR_USER_SANITIZE   0xFF0FFC20

#define SANITIZE_CPSR(cpsr, mode) (                                      \
    ((mode) == KernelMode ?                                              \
        (((cpsr) & CPSR_KERNEL_SANITIZE) | CPSRM_SVC | CPSRC_THUMB) :    \
        (((cpsr) & CPSR_USER_SANITIZE) | CPSRM_USER)))

__forceinline
ULONG
SANITIZE_DEBUG_ADDR(ULONG DebugReg, MODE mode)
{
    return ((mode) == KernelMode ?
                 (DebugReg) :
                 (((PVOID)(DebugReg) <= MM_HIGHEST_USER_ADDRESS) ? (DebugReg) : 0));
}

__forceinline
ULONG
SANITIZE_DEBUG_CTRL(ULONG DebugReg, MODE mode)
{
    return ((mode) == KernelMode ?
                 (DebugReg) :
                 (((DebugReg) & ~(CP14_DBGBCR_SECURITY_BITS | CP14_DBGBCR_PRIVILEGE_BITS)) |
                                    (CP14_DBGBCR_ANY_SECURE | CP14_DBGBCR_USER_ONLY)));
}

#define INITIAL_KERNEL_CPSR (CPSRM_SVC | CPSRC_THUMB | CPSRC_INT | CPSRC_ABORT)

#define SYSCALL_PSR         (CPSRM_USER | CPSRC_THUMB)

#if defined(_M_ARM) && !defined(RC_INVOKED)  && !defined(MIDL_PASS)

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExInterlockedIncrementLong)      // Use InterlockedIncrement
#pragma deprecated(ExInterlockedDecrementLong)      // Use InterlockedDecrement
#pragma deprecated(ExInterlockedExchangeUlong)      // Use InterlockedExchange
#endif

#define RESULT_ZERO 0
#define RESULT_NEGATIVE 1
#define RESULT_POSITIVE 2

typedef enum _INTERLOCKED_RESULT {
    ResultNegative = RESULT_NEGATIVE,
    ResultZero = RESULT_ZERO,
    ResultPositive = RESULT_POSITIVE
} INTERLOCKED_RESULT;

#define ExInterlockedDecrementLong(Addend, Lock)                            \
    _ExInterlockedDecrementLong(Addend)

_Post_satisfies_(return >= 0 && return <= 2)
__forceinline
LONG
_ExInterlockedDecrementLong (
    _Inout_ _Interlocked_operand_ PLONG Addend)
{
    LONG Result;

    Result = InterlockedDecrement(Addend);
    if (Result < 0) {
        return ResultNegative;

    } else if (Result > 0) {
        return ResultPositive;

    } else {
        return ResultZero;
    }
}

#define ExInterlockedIncrementLong(Addend, Lock)                            \
    _ExInterlockedIncrementLong(Addend)

_Post_satisfies_(return >= 0 && return <= 2)
__forceinline
LONG
_ExInterlockedIncrementLong (
    _Inout_ _Interlocked_operand_ PLONG Addend)
{
    LONG Result;

    Result = InterlockedIncrement(Addend);
    if (Result < 0) {
        return ResultNegative;

    } else if (Result > 0) {
        return ResultPositive;

    } else {
        return ResultZero;
    }
}

#define ExInterlockedExchangeUlong(Target, Value, Lock)                     \
    _ExInterlockedExchangeUlong(Target, Value)

__forceinline
ULONG
_ExInterlockedExchangeUlong (
    _Inout_ _Interlocked_operand_ PULONG Target,
    _In_ ULONG Value)
{
    return (ULONG)InterlockedExchange((PLONG)Target, (LONG)Value);
}

#endif // defined(_M_ARM) && !defined(RC_INVOKED)  && !defined(MIDL_PASS)


#define CP15_PCR_RESERVED_MASK 0xFFF
#define KIPCR() ((ULONG_PTR)(_MoveFromCoprocessor(CP15_TPIDRPRW)) & ~CP15_PCR_RESERVED_MASK)

#if !defined(MIDL_PASS) && defined(_M_ARM)

CFORCEINLINE
PKPCR
KeGetPcr (
    VOID)
{
    return (PKPCR)(ULONG_PTR)KIPCR();
}

CFORCEINLINE
PKPRCB
KeGetCurrentPrcb (
    VOID)
{
    PKPRCB Prcb;

    Prcb = (PKPRCB)(KIPCR() + 0x580);
    __assume(Prcb != NULL);
    return Prcb;
}

#if (NTDDI_VERSION < NTDDI_WIN7) || !defined(NT_PROCESSOR_GROUPS)
__forceinline
ULONG
KeGetCurrentProcessorNumber (
    VOID)
{
    return *(PUCHAR)(KIPCR() + 0x580);
}
#endif

CFORCEINLINE
ULONG
KeGetCurrentProcessorIndex (
    VOID)
{
    return *(PULONG)(KIPCR() + 0x594);
}

NTKERNELAPI
PKPRCB
KeQueryPrcbAddress (
    _In_ ULONG Number);

#endif // !defined(MIDL_PASS) && defined(_M_ARM)

#if !defined(_CROSS_PLATFORM_)

CFORCEINLINE
VOID
KeMemoryBarrier (
    VOID)
{
    _ReadWriteBarrier();
    MemoryBarrier();
}

#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()

ULONG64
ReadTimeStampCounter (
    VOID);

#else

#define KeMemoryBarrier()
#define KeMemoryBarrierWithoutFence()

#endif


_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_(return>=0, _Kernel_float_saved_)
_At_(*FloatSave, _When_(return>=0, _Kernel_acquires_resource_(FloatState)))
__forceinline
NTSTATUS
KeSaveFloatingPointState (
    _Out_ PKFLOATING_SAVE FloatSave)
#pragma warning (suppress:28104 28161 6001 6101) // PFD can't recognize the implementation
{
    UNREFERENCED_PARAMETER(FloatSave);
    return STATUS_SUCCESS;
}

_Success_(1)
_IRQL_requires_max_(DISPATCH_LEVEL)
_Kernel_float_restored_
_At_(*FloatSave, _Kernel_requires_resource_held_(FloatState) _Kernel_releases_resource_(FloatState))
__forceinline
NTSTATUS
KeRestoreFloatingPointState (
    _In_ PKFLOATING_SAVE FloatSave)
#pragma warning (suppress:28103 28162) // PFD can't recognize the implementation
{
    UNREFERENCED_PARAMETER(FloatSave);
    return STATUS_SUCCESS;
}

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_saves_
NTHALAPI
KIRQL
KeGetCurrentIrql (
    VOID
    );

_IRQL_requires_max_(HIGH_LEVEL)
NTHALAPI
VOID
KfLowerIrql (
    _In_ _IRQL_restores_ _Notliteral_ KIRQL NewIrql
    );

#define KeLowerIrql(a) KfLowerIrql(a)
#define KeRaiseIrql(a,b) *(b) = KfRaiseIrql(a)

NTHALAPI
KIRQL
_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_raises_(NewIrql)
_IRQL_saves_
KfRaiseIrql (
    _In_ KIRQL NewIrql);

_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
__forceinline
KIRQL
KeRaiseIrqlToDpcLevel (
    VOID)
{
    return KfRaiseIrql(DISPATCH_LEVEL);
}

_IRQL_saves_
_IRQL_raises_(12)
__forceinline
KIRQL
KeRaiseIrqlToSynchLevel (
    VOID)
{
    return KfRaiseIrql(12);
}

VOID
KeCompactServiceTable (
    _Inout_ PVOID Table,
    _In_ PVOID Arguments,
    _In_ ULONG Limit,
    _In_ BOOLEAN Win32k);

VOID
KiLockServiceTable (
    _Inout_ PVOID Table,
    _In_ PVOID Arguments,
    _In_ ULONG limit,
    _In_ BOOLEAN Win32k);

PKARM_VFP_STATE
KiGetVfpStatePointer(
    _In_ PKTRAP_FRAME TrapFrame);

#define ARM_VFP_ALWAYSON                0
#define ARM_VFP_LAZY_ONEWAY             1
// Not yet fully implemented:
#define ARM_VFP_LAZY_WITH_DEMOTION      2

#define ARM_VFP_MANAGEMENT              ARM_VFP_LAZY_ONEWAY

#define ARM_VFP_ENABLE_STATISTICS       0

#if ARM_VFP_ENABLE_STATISTICS
typedef struct _ARM_VFP_STATS
{
    ULONG64 TrapsEnabled;
    ULONG64 TrapsDisabled;
    ULONG64 ContextSwitchesToEnabled;
    ULONG64 ContextSwitchesToDisabled;
    ULONG64 AttemptedDemotions;
    ULONG64 FailedDemotions;
    ULONG64 MissedDemotions;
    ULONG EnableLogIndex;
    ULONG EnableLog[256];
} ARM_VFP_STATS;
#endif

typedef struct _TRAPFRAME_LOG_ENTRY {
    ULONG Thread;
    UCHAR CpuNumber;
    UCHAR TrapType;
    USHORT Padding;
    ULONG R0;
    ULONG R1;
    ULONG R2;
    ULONG R3;
    ULONG R12;
    ULONG Sp;
    ULONG Lr;
    ULONG R11;
    ULONG Pc;
    ULONG Cpsr;
} TRAPFRAME_LOG_ENTRY, *PTRAPFRAME_LOG_ENTRY;

#define TRAP_TYPE_INTERRUPT 1
#define TRAP_TYPE_SYSCALL 2
#define TRAP_TYPE_UNDEFINED 3
#define TRAP_TYPE_DATA_ABORT 4
#define TRAP_TYPE_PREFETCH_ABORT 5
#define TRAP_TYPE_RESET 6
#define TRAP_TYPE_FIQ 7

#define IMAGE_FILE_MACHINE_NATIVE   0x01C4

char
InterlockedAnd8 (
    _Inout_ char volatile *Destination,
    _In_ char Value);

char
InterlockedOr8 (
    _Inout_ char volatile *Destination,
    _In_ char Value);

#endif


#if defined(_ARM64_)

typedef ULONG PFN_COUNT;
typedef LONG64 SPFN_NUMBER, *PSPFN_NUMBER;
typedef ULONG64 PFN_NUMBER, *PPFN_NUMBER;

#define MAX_EVENT_COUNTERS 31

#define FLUSH_MULTIPLE_MAXIMUM 32

#define ALLOC_PRAGMA 1
#define ALLOC_DATA_PRAGMA 1

#define CPSRM_EL3h 0xd
#define CPSRM_EL3t 0xc
#define CPSRM_EL2h 0x9
#define CPSRM_EL2t 0x8
#define CPSRM_EL1h 0x5
#define CPSRM_EL1t 0x4
#define CPSRM_EL0t 0x0
#define CPSRM_MASK 0x0f

#define CPSREL_3 0xc
#define CPSREL_2 0x8
#define CPSREL_1 0x4
#define CPSREL_0 0x0
#define CPSREL_MASK 0x0c

#define DAIF_DEBUG 0x200
#define DAIF_ABORT 0x100
#define DAIF_INT   0x80
#define DAIF_FIQ   0x40

#define NZCV_N 0x80000000
#define NZCV_Z 0x40000000
#define NZCV_C 0x20000000
#define NZCV_V 0x10000000

#define CPSRM_T 0x00000020
#define CPSRM_AA32 0x00000010
#define CPSR_IL 0x00100000
#define CPSR_SS 0x00200000
#define CPSR_IT_MASK 0x0600fc00

#define FPCRM_AHP        0x04000000
#define FPCRM_DN         0x02000000
#define FPCRM_FZ         0x01000000

#define FPCRM_RMODE_MASK 0x00c00000
#define FPCRM_RMODE_RN   0x00000000
#define FPCRM_RMODE_RP   0x00400000
#define FPCRM_RMODE_RM   0x00800000
#define FPCRM_RMODE_RZ   0x00c00000

#define FPCR_IDE 0x00008000
#define FPCR_IXE 0x00001000
#define FPCR_UFE 0x00000800
#define FPCR_OFE 0x00000400
#define FPCR_DZE 0x00000200
#define FPCR_IOE 0x00000100

#define FPSR_IDC 0x00000080
#define FPSR_IXC 0x00000010
#define FPSR_UFC 0x00000008
#define FPSR_OFC 0x00000004
#define FPSR_DZC 0x00000002
#define FPSR_IOC 0x00000001

#define ARM64_SPSR_EL1          ARM64_SYSREG(3,0, 4, 0,0)   // Saved processor status register (EL1)
#define ARM64_SPSR_EL2          ARM64_SYSREG(3,4, 4, 0,0)   // Saved processor status register (EL2)
#define ARM64_ELR_EL1           ARM64_SYSREG(3,0, 4, 0,1)   // Exception return address (EL1)
#define ARM64_ELR_EL2           ARM64_SYSREG(3,4, 4, 0,1)   // Exception return address (EL2)
#define ARM64_SP_EL0            ARM64_SYSREG(3,0, 4, 1,0)   // User mode stack pointer (EL1)
#define ARM64_SP_EL1            ARM64_SYSREG(3,4, 4, 1,0)   // Kernel mode stack pointer (EL1)
#define ARM64_SP_EL2            ARM64_SYSREG(3,6, 4, 1,0)   // Hypervisor mode stack pointer (EL2)
#define ARM64_SPSel             ARM64_SYSREG(3,0, 4, 2,0)   // SP select (EL1)
#define ARM64_DAIF              ARM64_SYSREG(3,3, 4, 2,1)   // Interrupt Masks (EL0)
#define ARM64_CurrentEL         ARM64_SYSREG(3,0, 4, 2,2)   // Current Exception Level (ReadOnly, EL1)
#define ARM64_NZCV              ARM64_SYSREG(3,3, 4, 2,0)   // Flags (EL0)
//#define ARM64_FPCR            ARM64_SYSREG(3,3, 4, 4,0)   // Floating point control register (EL0)
//#define ARM64_FPSR            ARM64_SYSREG(3,3, 4, 4,1)   // Floating point status register (EL0)
#define ARM64_DSPSR             ARM64_SYSREG(3,3, 4, 5,0)   // ??? (EL0)
#define ARM64_DLR               ARM64_SYSREG(3,3, 4, 5,1)   // ??? (EL0)
#define ARM64_MIDR_EL1          ARM64_SYSREG(3,0, 0, 0,0)   // Main ID Register [CP15_MIDR]
#define ARM64_VPIDR_EL2         ARM64_SYSREG(3,4, 0, 0,0)   // Virtualized Main ID Register [CP15_VPIDR]
#define ARM64_REVIDR_EL1        ARM64_SYSREG(3,0, 0, 0,6)   // Revision ID Register [CP15_REVIDR]
#define ARM64_CTR_EL0           ARM64_SYSREG(3,3, 0, 0,1)   // Cache Type Register [CP15_CTR]
#define ARM64_MPIDR_EL1         ARM64_SYSREG(3,0, 0, 0,5)   // Multiprocessor Affinity Register [CP15_MPIDR]
#define ARM64_VMPIDR_EL2        ARM64_SYSREG(3,4, 0, 0,5)   // Virtualized Multiprocessor Affinity Register [CP15_VMPIDR]
#define ARM64_ID_AA64PFR0_EL1   ARM64_SYSREG(3,0, 0, 4,0)   // Processor Feature Register 0
#define ARM64_ID_AA64PFR1_EL1   ARM64_SYSREG(3,0, 0, 4,1)   // Processor Feature Register 1
#define ARM64_ID_AA64DFR0_EL1   ARM64_SYSREG(3,0, 0, 5,0)   // Debug Feature Register 0
#define ARM64_ID_AA64DFR1_EL1   ARM64_SYSREG(3,0, 0, 5,1)   // Debug Feature Register 1
#define ARM64_ID_AA64AFR0_EL1   ARM64_SYSREG(3,0, 0, 5,4)   //
#define ARM64_ID_AA64AFR1_EL1   ARM64_SYSREG(3,0, 0, 5,5)   //
#define ARM64_ID_AA64ISAR0_EL1  ARM64_SYSREG(3,0, 0, 6,0)   // ISA Feature Register 0
#define ARM64_ID_AA64ISAR1_EL1  ARM64_SYSREG(3,0, 0, 6,1)   // ISA Feature Register 1
#define ARM64_ID_AA64MMFR0_EL1  ARM64_SYSREG(3,0, 0, 7,0)   // Memory Management Feature Register 0
#define ARM64_ID_AA64MMFR1_EL1  ARM64_SYSREG(3,0, 0, 7,1)   // Memory Management Feature Register 1
#define ARM64_SCTLR_EL1         ARM64_SYSREG(3,0, 1, 0,0)   // System Control Register [CP15_SCTLR]
#define ARM64_SCTLR_EL2         ARM64_SYSREG(3,4, 1, 0,0)   // System Control Register [CP15_HSCTLR]
#define ARM64_HCR_EL2           ARM64_SYSREG(3,4, 1, 1,0)   // Hypervisor Configuration Register (EL2)
#define ARM64_HSTR_EL2          ARM64_SYSREG(3,4, 1, 1,3)   // Hypervisor System Trap Configuration Register (EL2)
#define ARM64_HACR_EL2          ARM64_SYSREG(3,4, 1, 1,7)   // Hypervisor Auxiliary Configuration Register (EL2)
#define ARM64_ACTLR_EL1         ARM64_SYSREG(3,0, 1, 0,1)   // Auxiliary Control Register [CP15_ACTLR]
#define ARM64_ACTLR_EL2         ARM64_SYSREG(3,4, 1, 0,1)   // Auxiliary Control Register [CP15_HACTLR]
#define ARM64_CPACR_EL1         ARM64_SYSREG(3,0, 1, 0,2)   // Coprocessor Access Control Register [CP15_CPACR]
#define ARM64_SCR_EL3           ARM64_SYSREG(3,6, 1, 1,0)   // Secure Configuration Register [CP15_SCR]
#define ARM64_CPTR_EL3          ARM64_SYSREG(3,6, 1, 1,2)   // Non-Secure Access Control Register [CP15_NSACR]
#define ARM64_CPTR_EL2          ARM64_SYSREG(3,4, 1, 1,2)   // Hypervisor Access Control Register [CP15_HCPTR]
#define ARM64_TTBR0_EL1         ARM64_SYSREG(3,0, 2, 0,0)   // Translation Table Base Register 0 [CP15_TTBR0]
#define ARM64_TTBR0_EL2         ARM64_SYSREG(3,4, 2, 0,0)   // Translation Table Base Register 0 [CP15_HTTBR]
#define ARM64_TTBR1_EL1         ARM64_SYSREG(3,0, 2, 0,1)   // Translation Table Base Register 1 [CP15_TTBR1]
#define ARM64_VTTBR_EL2         ARM64_SYSREG(3,4, 2, 1,0)   // Virtualization Translation Table Base Register 1 [CP15_VTTBR]
#define ARM64_TCR_EL1           ARM64_SYSREG(3,0, 2, 0,2)   // Translation Control Register [CP15_TTBCR]
#define ARM64_TCR_EL2           ARM64_SYSREG(3,4, 2, 0,2)   // Translation Control Register [CP15_HTCR]
#define ARM64_VTCR_EL2          ARM64_SYSREG(3,4, 2, 1,2)   // Virtualization Translation Control Register [CP15_VTCR]
#define ARM64_ESR_EL1           ARM64_SYSREG(3,0, 5, 2,0)   // Exception Status Register [CP15_DFSR/CP15_IFSR]
#define ARM64_ESR_EL2           ARM64_SYSREG(3,4, 5, 2,0)   // Exception Status Register [CP15_HSR]
#define ARM64_FAR_EL1           ARM64_SYSREG(3,0, 6, 0,0)   // Fault Address Registers [CP15_DFAR/CP15_IFAR]
#define ARM64_FAR_EL2           ARM64_SYSREG(3,4, 6, 0,0)   // Fault Address Registers [CP15_HDFAR/CP15_HIFAR]
#define ARM64_HPFAR_EL2         ARM64_SYSREG(3,4, 6, 0,4)   // Hypervisor IPA Fault Address Registers [CP15_HPFAR]
#define ARM64_AFSR0_EL1         ARM64_SYSREG(3,0, 5, 1,0)   // Auxiliary Fault Status Register 0 [CP15_ADFSR]
#define ARM64_AFSR0_EL2         ARM64_SYSREG(3,4, 5, 1,0)   // Auxiliary Fault Status Register 0 [CP15_HDFSR]
#define ARM64_AFSR1_EL1         ARM64_SYSREG(3,0, 5, 1,1)   // Auxiliary Fault Status Register 1 [CP15_AIFSR]
#define ARM64_AFSR1_EL2         ARM64_SYSREG(3,4, 5, 1,1)   // Auxiliary Fault Status Register 1 [CP15_HAIFSR]
#define ARM64_DCZID_EL0         ARM64_SYSREG(3,3, 0, 0,7)   // Data Cache Zero ID Register
#define ARM64_IC_IALLUIS        ARM64_SYSREG(2,0, 7, 1,0)   // Invalidate all instruction caches to PoU Inner Shareable [CP15_ICIALLUIS]
#define ARM64_IC_IALLU          ARM64_SYSREG(2,0, 7, 5,0)   // Invalidate all instruction caches to PoU [CP15_ICIALLU]
#define ARM64_IC_IVAU           ARM64_SYSREG(2,3, 7, 5,1)   // Invalidate all instruction caches by MVA to PoU [CP15_ICIMVAU]
#define ARM64_DC_ZVA            ARM64_SYSREG(2,3, 7, 4,1)   // Zero cache line at VA
#define ARM64_DC_IVAC           ARM64_SYSREG(2,0, 7, 6,1)   // Invalidate data cache line by VA to PoC [CP15_DCIMVAC]
#define ARM64_DC_ISW            ARM64_SYSREG(2,0, 7, 6,2)   // Invalidate data cache line by set/way [CP15_DCISW]
#define ARM64_DC_CVAC           ARM64_SYSREG(2,3, 7,10,1)   // Clean data cache line by VA to PoC [CP15_DCCMVAC]
#define ARM64_DC_CSW            ARM64_SYSREG(2,0, 7,10,2)   // Clean data cache line by set/way [CP15_DCCSW]
#define ARM64_DC_CVAU           ARM64_SYSREG(2,3, 7,11,1)   // Clean data cache line by VA to PoU [CP15_DCCMVAU]
#define ARM64_DC_CIVAC          ARM64_SYSREG(2,3, 7,14,1)   // Clean and invalidate data cache line by VA to PoC [CP15_DCCIMVAC]
#define ARM64_DC_CISW           ARM64_SYSREG(2,0, 7,14,2)   // Clean and invalidate data cache line by set/way [CP15_DCCISW]
#define ARM64_PAR_EL1           ARM64_SYSREG(3,0, 7, 4,0)   // Physical Address Register (Translation Result) [CP15_PAR]
#define ARM64_AT_S1E2R          ARM64_SYSREG(2,4, 7, 8,0)   // Translate Stage1, EL2, read
#define ARM64_AT_S1E2W          ARM64_SYSREG(2,4, 7, 8,1)   // Translate Stage1, EL2, write
#define ARM64_AT_S1E1R          ARM64_SYSREG(2,0, 7, 8,0)   // Translate Stage1, EL1, read
#define ARM64_AT_S1E1W          ARM64_SYSREG(2,0, 7, 8,1)   // Translate Stage1, EL1, write
#define ARM64_AT_S1E0R          ARM64_SYSREG(2,0, 7, 8,2)   // Translate Stage1, EL0, read
#define ARM64_AT_S1E0W          ARM64_SYSREG(2,0, 7, 8,3)   // Translate Stage1, EL0, write
#define ARM64_AT_S12E1R         ARM64_SYSREG(2,4, 7, 8,4)   // Translate Stage12, EL1, read
#define ARM64_AT_S12E1W         ARM64_SYSREG(2,4, 7, 8,5)   // Translate Stage12, EL1, write
#define ARM64_AT_S12E0R         ARM64_SYSREG(2,4, 7, 8,6)   // Translate Stage12, EL0, read
#define ARM64_AT_S12E0W         ARM64_SYSREG(2,4, 7, 8,7)   // Translate Stage12, EL0, write
#define ARM64_CNTFRQ_EL0        ARM64_SYSREG(3,3,14, 0,0)   // Holds the clock frequency of the system counter
#define ARM64_CNTPCT_EL0        ARM64_SYSREG(3,3,14, 0,1)   // Holds the 64bit physical count value
#define ARM64_CNTVCT_EL0        ARM64_SYSREG(3,3,14, 0,2)   // Holds the 64bit virtual count value
#define ARM64_CNTV_OFF_EL2      ARM64_SYSREG(3,4,14, 0,3)   // Holds the 64bit virtual count offset value
#define ARM64_CNTP_TVAL_EL0     ARM64_SYSREG(3,3,14, 2,0)   // Holds the timer value for the El1 physical timer
#define ARM64_CNTP_CTL_EL0      ARM64_SYSREG(3,3,14, 2,1)   // Control register for the El1 physical timer
#define ARM64_CNTP_CVAL_EL0     ARM64_SYSREG(3,3,14, 2,2)   // Holds the compare value for the El1 physical timer
#define ARM64_CNTV_TVAL_EL0     ARM64_SYSREG(3,3,14, 3,0)   // Holds the timer value for the virtual timer
#define ARM64_CNTV_CTL_EL0      ARM64_SYSREG(3,3,14, 3,1)   // Control register for the virtual timer
#define ARM64_CNTV_CVAL_EL0     ARM64_SYSREG(3,3,14, 3,2)   // Holds the compare value for the virtual timer
#define ARM64_CNTK_CTL_EL1      ARM64_SYSREG(3,0,14, 1,0)   // Controls the generation of an event stream from the virtual counter, and access from EL0 to the physical counter, virtual counter, EL1 physical timers, and the virtual timer.
#define ARM64_CNT_HCTL_EL2      ARM64_SYSREG(3,4,14, 1,0)   // Counter-timer Hypervisor Control register
#define ARM64_CNTHP_TVAL_EL2    ARM64_SYSREG(3,4,14, 2,0)   // Counter-timer Hypervisor Physical Timer TimerValue register
#define ARM64_CNTHP_CTL_EL2     ARM64_SYSREG(3,4,14, 2,1)   // Counter-timer Hypervisor Physical Timer Control register
#define ARM64_CNTHP_CVAL_EL2    ARM64_SYSREG(3,4,14, 2,2)   // 64-bit, Counter-timer Hypervisor Physical Timer CompareValue register

#define ARM64_CNT_HCTL_EL1PCTEN    0x00000001
#define ARM64_CNT_HCTL_EL1PCEN     0x00000002
#define ARM64_CNT_HCTL_EVNTEN      0x00000004
#define ARM64_CNT_HCTL_EVNTDIR     0x00000008
#define ARM64_CNT_HCTL_EVNTI_MASK  0x000000F0
#define ARM64_CNT_HCTL_EVNTI_SHIFT 4

#define ARM64_CNT_CTL_ENABLE      0x00000001
#define ARM64_CNT_CTL_IMASK       0x00000002
#define ARM64_CNT_CTL_ISTATUS     0x00000004

#define ARM64_CNTK_CTL_EL0PCTEN   0x00000001 // Controls whether the physical counter, CNTPCT_EL0, and the frequency register CNTFRQ_EL0, are accessible from EL0 modes
#define ARM64_CNTK_CTL_EL0VCTEN   0x00000002 // Controls whether the virtual counter, CNTVCT_EL0, and the frequency register CNTFRQ_EL0, are accessible from EL0 modes
#define ARM64_CNTK_CTL_EVNTEN     0x00000004 // Enables the generation of an event stream from the corresponding counter
#define ARM64_CNTK_CTL_EVNTDIR    0x00000008 // Controls which transition of the counter register (CNTPCT_EL0 or CNTVCT_EL0) trigger bit, defined by EVNTI, generates an event when the event stream is enabled
#define ARM64_CNTK_CTL_EVNTI_MASK 0x000000F0 // Selects which bit (0 to 15) of the corresponding counter register (CNTPCT_EL0 or CNTVCT_EL0) is the trigger for the event stream generated from that counter, when that stream is enabled.
#define ARM64_CNTK_CTL_EL0VTEN    0x00000100 // Controls whether the virtual timer registers are accessible from EL0 modes
#define ARM64_CNTK_CTL_EL0PTEN    0x00000200 // Controls whether the physical timer registers are accessible from EL0 modes

typedef union _ARM64_PAR {
    ULONG64 Ulong;
    struct {
        ULONG64 Fault         :  1;
        ULONG64 FaultStatus   :  6;
        ULONG64 Shareability  :  2;
        ULONG64 Stage         :  1;
        ULONG64 ImplDefined   :  1;
        ULONG64 Res1          :  1;
        ULONG64 Pfn           : 36;
        ULONG64 Res0          :  8;
        ULONG64 Mair          :  8;
    };
} ARM64_PAR;

#define ARM64_TLBI_VMALLE1      ARM64_SYSREG(2,0, 8, 7,0)   // Invalidate unified TLB [CP15_TLBIALL]
#define ARM64_TLBI_VAE1         ARM64_SYSREG(2,0, 8, 7,1)   // Invalidate unified TLB entry by VA [CP15_TLBIMVA]
#define ARM64_TLBI_ASIDE1       ARM64_SYSREG(2,0, 8, 7,2)   // Invalidate unified TLB by ASID match [CP15_TLBIASID]
#define ARM64_TLBI_VAAE1        ARM64_SYSREG(2,0, 8, 7,3)   // Invalidate unified TLB entries by VA all ASID [CP15_TLBIMVAA]
#define ARM64_TLBI_VALE1        ARM64_SYSREG(2,0, 8, 7,5)   //
#define ARM64_TLBI_VAALE1       ARM64_SYSREG(2,0, 8, 7,7)   //
#define ARM64_TLBI_VMALLE1IS    ARM64_SYSREG(2,0, 8, 3,0)   // Invalidate entire TLB Inner Shareable [CP15_TLBIALLIS]
#define ARM64_TLBI_VAE1IS       ARM64_SYSREG(2,0, 8, 3,1)   // Invalidate unified TLB entry by VA Inner Shareable [CP15_TLBIMVAIS]
#define ARM64_TLBI_ASIDE1IS     ARM64_SYSREG(2,0, 8, 3,2)   // Invalidate unified TLB by ASID match Inner Shareable [CP15_TLBIASIDIS]
#define ARM64_TLBI_VAAE1IS      ARM64_SYSREG(2,0, 8, 3,3)   // Invalidate unified TLB entries by VA all ASID Inner Shareable [CP15_TLBIMVAAIS]
#define ARM64_TLBI_VALE1IS      ARM64_SYSREG(2,0, 8, 3,5)   //
#define ARM64_TLBI_VAALE1IS     ARM64_SYSREG(2,0, 8, 3,7)   //
#define ARM64_TLBI_ALLE2        ARM64_SYSREG(2,4, 8, 7,0)   // Invalidate unified TLB EL2
#define ARM64_TLBI_VAE2         ARM64_SYSREG(2,4, 8, 7,1)   // Invalidate EL2 regime stage 1 TLB entries for the given VA.
#define ARM64_TLBI_ALLE1        ARM64_SYSREG(2,4, 8, 7,4)   // Invalidate unified TLB EL1 (Stage 1 and 2)
#define ARM64_TLBI_VMALLS12E1IS ARM64_SYSREG(2,4, 8, 3,6)   // Invalidate by VMID, All entries at Stage 1 and 2, EL1, Inner Shareable

#define ARM64_TLBI_ASID_SHIFT   48
#define ARM64_TLBI_VA_MASK      0x00fffffffffff000ULL

#define ARM64_PMCCFILTR_EL0     ARM64_SYSREG(3,3,14,15,7)  // Performance Monitors Cycle Count Filter Register [CP15_PMCCFILTR]
#define ARM64_MDCR_EL2          ARM64_SYSREG(3,4, 1, 1,1)  // Monitor Debug Configuration Register (EL2) [CP15_HDCR]
#define ARM64_PMCR_EL0          ARM64_SYSREG(3,3, 9,12,0)  // Performance Monitor Control Register [CP15_PMCR]
#define ARM64_PMCNTENSET_EL0    ARM64_SYSREG(3,3, 9,12,1)  // Count Enable Set Register [CP15_PMCNTENSET]
#define ARM64_PMCNTENCLR_EL0    ARM64_SYSREG(3,3, 9,12,2)  // Count Enable Clear Register [CP15_PMCNTENCLR]
#define ARM64_PMOVSCLR_EL0      ARM64_SYSREG(3,3, 9,12,3)  // Overflow Flag Status Register [CP15_PMOVSR]
#define ARM64_PMSWINC_EL0       ARM64_SYSREG(3,3, 9,12,4)  // Software Increment Register [CP15_PSWINC]
#define ARM64_PMSELR_EL0        ARM64_SYSREG(3,3, 9,12,5)  // Event Counter Selection Register [CP15_PMSELR]
#define ARM64_PMCCNTR_EL0       ARM64_SYSREG(3,3, 9,13,0)  // Cycle Count Register [CP15_PMCCNTR]
#define ARM64_PMXEVTYPER_EL0    ARM64_SYSREG(3,3, 9,13,1)  // Event Type Select Register [CP15_PMXEVTYPER]
#define ARM64_PMXEVTYPERn_EL0(n) ARM64_SYSREG(3,3,14, 12+((n)/8), (n)%8)    // Direct Event Type Select Register [n/a]
#define ARM64_PMXEVCNTR_EL0     ARM64_SYSREG(3,3, 9,13,2)  // Event Count Register [CP15_PMXEVCNTR]
#define ARM64_PMXEVCNTRn_EL0(n) ARM64_SYSREG(3,3,14, 8+((n)/8), (n)%8)    // Direct Event Count Register [n/a]
#define ARM64_PMUSERENR_EL0     ARM64_SYSREG(3,3, 9,14,0)  // User Enable Register [CP15_PMUSERENR]
#define ARM64_PMINTENSET_EL1    ARM64_SYSREG(3,0, 9,14,1)  // Interrupt Enable Set Register [CP15_PMINTENSET]
#define ARM64_PMINTENCLR_EL1    ARM64_SYSREG(3,0, 9,14,2)  // Interrupt Enable Clear Register [CP15_PMINTENCLR]

#define ARM64_MAIR_EL1          ARM64_SYSREG(3,0,10, 2,0)  // Primary Region Remap Register [CP15_PRRR/CP15_NMRR]
#define ARM64_AMAIR_EL1         ARM64_SYSREG(3,0,10, 3,0)  // Auxiliary Region Remap Register [CP15_AMAIR0/CP15_AMAIR1]
#define ARM64_MAIR_EL2          ARM64_SYSREG(3,4,10, 2,0)  // Primary Region Remap Register [CP15_HMAIR0/CP15_HMAIR1]
#define ARM64_AMAIR_EL2         ARM64_SYSREG(3,4,10, 3,0)  // Auxiliary Region Remap Register [CP15_HAMAIR0/CP15_HAMAIR1]

#define ARM64_VBAR_EL1          ARM64_SYSREG(3,0,12, 0,0)  // Vector Base Address Register [CP15_VBAR]
#define ARM64_VBAR_EL2          ARM64_SYSREG(3,4,12, 0,0)  // Vector Base Address Register [CP15_HVBAR]
#define ARM64_ISR_EL1           ARM64_SYSREG(3,0,12, 1,0)  // Interrupt Status Register [CP15_ISR]

#define ARM64_TPIDR_EL0         ARM64_SYSREG(3,3,13, 0,2)  // Thread ID Register, User Read/Write [CP15_TPIDRURW]
#define ARM64_TPIDRRO_EL0       ARM64_SYSREG(3,3,13, 0,3)  // Thread ID Register, User Read Only [CP15_TPIDRURO]
#define ARM64_TPIDR_EL1         ARM64_SYSREG(3,0,13, 0,4)  // Thread ID Register, Privileged Only [CP15_TPIDRPRW]
#define ARM64_TPIDR_EL2         ARM64_SYSREG(3,4,13, 0,2)  // Thread ID Register, Hypervisor Only [CP15_HTPIDR]
#define ARM64_CONTEXTIDR_EL1    ARM64_SYSREG(3,0,13, 0,1)  // Context ID Register

#define ARM64_CCSIDR_EL1        ARM64_SYSREG(3,1, 0, 0,0)  // Cache Size ID Register [CP15_CCSIDR]
#define ARM64_CLIDR_EL1         ARM64_SYSREG(3,1, 0, 0,1)  // Cache Level ID Register [CP15_CLIDR]
#define ARM64_AIDR_EL1          ARM64_SYSREG(3,1, 0, 0,7)  // Auxiliary ID Register [CP15_AIDR]
#define ARM64_CSSELR_EL1        ARM64_SYSREG(3,2, 0, 0,0)  // Cache Size Selection Register [CP15_CSSELR]

#define ARM64_CNTVCT            ARM64_SYSREG(3,3,14, 0,2)
#define ARM64_CNTKCTL           ARM64_SYSREG(3,0,14, 1,0)
#define ARM64_CNTV_CTL          ARM64_SYSREG(3,3,14, 3,1)
#define ARM64_CNTV_CVAL         ARM64_SYSREG(3,3,14, 3,2)

#define ARM64_MDCCSR_EL0        ARM64_SYSREG(2,3, 0, 1,0)  // Debug Comms Channel Status Register (internal view) [CP14_DBGDSCRint]
#define ARM64_DBGDTRRX_EL0      ARM64_SYSREG(2,3, 0, 5,0)  // Host to Target Data Transfer Register (internal view) [CP14_DBGDTRRXint]
#define ARM64_DBGDTRTX_EL0      ARM64_DBGDTRRX_EL0         // Target to Host Data Transfer Register (internal view) [CP14_DBGDTRTXint]
#define ARM64_OSDTRRX_EL1       ARM64_SYSREG(2,0, 0, 0,2)  // Host to Target Data Transfer Register [CP14_DBGDTRRX]
#define ARM64_MDSCR_EL1         ARM64_SYSREG(2,0, 0, 2,2)  // Debug Status and Control Register (external view) [CP14_DBGDSCR]
#define ARM64_OSDTRTX_EL1       ARM64_SYSREG(2,0, 0, 3,2)  // Target to Host Data Transfer Register [CP14_DBGDTRTX]
#define ARM64_DBGBVR0_EL1       ARM64_SYSREG(2,0, 0, 0,4)  // Breakpoint Value Register 0 [CP14_DBGBVRn]
#define ARM64_DBGBVR1_EL1       ARM64_SYSREG(2,0, 0, 1,4)  // ...
#define ARM64_DBGBVR2_EL1       ARM64_SYSREG(2,0, 0, 2,4)  // ...
#define ARM64_DBGBVR3_EL1       ARM64_SYSREG(2,0, 0, 3,4)  // ...
#define ARM64_DBGBVR4_EL1       ARM64_SYSREG(2,0, 0, 4,4)  // ...
#define ARM64_DBGBVR5_EL1       ARM64_SYSREG(2,0, 0, 5,4)  // ...
#define ARM64_DBGBVR6_EL1       ARM64_SYSREG(2,0, 0, 6,4)  // ...
#define ARM64_DBGBVR7_EL1       ARM64_SYSREG(2,0, 0, 7,4)  // ...
#define ARM64_DBGBVR8_EL1       ARM64_SYSREG(2,0, 0, 8,4)  // ...
#define ARM64_DBGBVR9_EL1       ARM64_SYSREG(2,0, 0, 9,4)  // ...
#define ARM64_DBGBVR10_EL1      ARM64_SYSREG(2,0, 0,10,4)  // ...
#define ARM64_DBGBVR11_EL1      ARM64_SYSREG(2,0, 0,11,4)  // ...
#define ARM64_DBGBVR12_EL1      ARM64_SYSREG(2,0, 0,12,4)  // ...
#define ARM64_DBGBVR13_EL1      ARM64_SYSREG(2,0, 0,13,4)  // ...
#define ARM64_DBGBVR14_EL1      ARM64_SYSREG(2,0, 0,14,4)  // ...
#define ARM64_DBGBVR15_EL1      ARM64_SYSREG(2,0, 0,15,4)  // ...
#define ARM64_DBGBCR0_EL1       ARM64_SYSREG(2,0, 0, 0,5)  // Breakpoint Value Register 0 [CP14_DBGBCRn]
#define ARM64_DBGBCR1_EL1       ARM64_SYSREG(2,0, 0, 1,5)  // ...
#define ARM64_DBGBCR2_EL1       ARM64_SYSREG(2,0, 0, 2,5)  // ...
#define ARM64_DBGBCR3_EL1       ARM64_SYSREG(2,0, 0, 3,5)  // ...
#define ARM64_DBGBCR4_EL1       ARM64_SYSREG(2,0, 0, 4,5)  // ...
#define ARM64_DBGBCR5_EL1       ARM64_SYSREG(2,0, 0, 5,5)  // ...
#define ARM64_DBGBCR6_EL1       ARM64_SYSREG(2,0, 0, 6,5)  // ...
#define ARM64_DBGBCR7_EL1       ARM64_SYSREG(2,0, 0, 7,5)  // ...
#define ARM64_DBGBCR8_EL1       ARM64_SYSREG(2,0, 0, 8,5)  // ...
#define ARM64_DBGBCR9_EL1       ARM64_SYSREG(2,0, 0, 9,5)  // ...
#define ARM64_DBGBCR10_EL1      ARM64_SYSREG(2,0, 0,10,5)  // ...
#define ARM64_DBGBCR11_EL1      ARM64_SYSREG(2,0, 0,11,5)  // ...
#define ARM64_DBGBCR12_EL1      ARM64_SYSREG(2,0, 0,12,5)  // ...
#define ARM64_DBGBCR13_EL1      ARM64_SYSREG(2,0, 0,13,5)  // ...
#define ARM64_DBGBCR14_EL1      ARM64_SYSREG(2,0, 0,14,5)  // ...
#define ARM64_DBGBCR15_EL1      ARM64_SYSREG(2,0, 0,15,5)  // ...
#define ARM64_DBGWVR0_EL1       ARM64_SYSREG(2,0, 0, 0,6)  // Watchpoint Value Register 0 [CP14_DBGWVRn]
#define ARM64_DBGWVR1_EL1       ARM64_SYSREG(2,0, 0, 1,6)  // ...
#define ARM64_DBGWVR2_EL1       ARM64_SYSREG(2,0, 0, 2,6)  // ...
#define ARM64_DBGWVR3_EL1       ARM64_SYSREG(2,0, 0, 3,6)  // ...
#define ARM64_DBGWVR4_EL1       ARM64_SYSREG(2,0, 0, 4,6)  // ...
#define ARM64_DBGWVR5_EL1       ARM64_SYSREG(2,0, 0, 5,6)  // ...
#define ARM64_DBGWVR6_EL1       ARM64_SYSREG(2,0, 0, 6,6)  // ...
#define ARM64_DBGWVR7_EL1       ARM64_SYSREG(2,0, 0, 7,6)  // ...
#define ARM64_DBGWVR8_EL1       ARM64_SYSREG(2,0, 0, 8,6)  // ...
#define ARM64_DBGWVR9_EL1       ARM64_SYSREG(2,0, 0, 9,6)  // ...
#define ARM64_DBGWVR10_EL1      ARM64_SYSREG(2,0, 0,10,6)  // ...
#define ARM64_DBGWVR11_EL1      ARM64_SYSREG(2,0, 0,11,6)  // ...
#define ARM64_DBGWVR12_EL1      ARM64_SYSREG(2,0, 0,12,6)  // ...
#define ARM64_DBGWVR13_EL1      ARM64_SYSREG(2,0, 0,13,6)  // ...
#define ARM64_DBGWVR14_EL1      ARM64_SYSREG(2,0, 0,14,6)  // ...
#define ARM64_DBGWVR15_EL1      ARM64_SYSREG(2,0, 0,15,6)  // ...
#define ARM64_DBGWCR0_EL1       ARM64_SYSREG(2,0, 0, 0,7)  // Watchpoint Value Register 0 [CP14_DBGWCRn]
#define ARM64_DBGWCR1_EL1       ARM64_SYSREG(2,0, 0, 1,7)  // ...
#define ARM64_DBGWCR2_EL1       ARM64_SYSREG(2,0, 0, 2,7)  // ...
#define ARM64_DBGWCR3_EL1       ARM64_SYSREG(2,0, 0, 3,7)  // ...
#define ARM64_DBGWCR4_EL1       ARM64_SYSREG(2,0, 0, 4,7)  // ...
#define ARM64_DBGWCR5_EL1       ARM64_SYSREG(2,0, 0, 5,7)  // ...
#define ARM64_DBGWCR6_EL1       ARM64_SYSREG(2,0, 0, 6,7)  // ...
#define ARM64_DBGWCR7_EL1       ARM64_SYSREG(2,0, 0, 7,7)  // ...
#define ARM64_DBGWCR8_EL1       ARM64_SYSREG(2,0, 0, 8,7)  // ...
#define ARM64_DBGWCR9_EL1       ARM64_SYSREG(2,0, 0, 9,7)  // ...
#define ARM64_DBGWCR10_EL1      ARM64_SYSREG(2,0, 0,10,7)  // ...
#define ARM64_DBGWCR11_EL1      ARM64_SYSREG(2,0, 0,11,7)  // ...
#define ARM64_DBGWCR12_EL1      ARM64_SYSREG(2,0, 0,12,7)  // ...
#define ARM64_DBGWCR13_EL1      ARM64_SYSREG(2,0, 0,13,7)  // ...
#define ARM64_DBGWCR14_EL1      ARM64_SYSREG(2,0, 0,14,7)  // ...
#define ARM64_DBGWCR15_EL1      ARM64_SYSREG(2,0, 0,15,7)  // ...
#define ARM64_OSLAR_EL1         ARM64_SYSREG(2,0, 1, 0,4)  // OS Lock Access Register [CP14_DBGOSLAR]
#define ARM64_OSLSR_EL1         ARM64_SYSREG(2,0, 1, 1,4)  // OS Lock Status Register [CP14_DBGOSLSR]
#define ARM64_OSDLR_EL1         ARM64_SYSREG(2,0, 1, 3,4)  // OS Double Lock Register [CP14_DBGOSDLR]
#define ARM64_DBGPRCR_EL1       ARM64_SYSREG(2,0, 1, 4,4)  // Debug Power/Reset Control Register

#define ARM64_OSLSR_LOCK_IMP    0x1
#define ARM64_OSLSR_LOCKED      0x2

#define READ_ARM64_FEATURE(_FeatureRegister, _Index) \
        (((ULONG64)_ReadStatusReg(_FeatureRegister) >> ((_Index) * 4)) & 0xF)

#define AFR0_EL0_EXCEPTIONS         0
#define AFR0_EL1_EXCEPTIONS         1
#define AFR0_EL2_EXCEPTIONS         2
#define AFR0_EL3_EXCEPTIONS         3
#define AFR0_ELn_EXCEPTIONS_NI      0
#define AFR0_ELn_EXCEPTIONS_64ONLY  1
#define AFR0_ELn_EXCEPTIONS_64OR32  2

#define AFR0_FLOATING_POINT         4
#define AFR0_FLOATING_POINT_IMP     0
#define AFR0_FLOATING_POINT_NI      15

#define AFR0_ADVANCED_SIMD          5
#define AFR0_ADVANCED_SIMD_IMP      0
#define AFR0_ADVANCED_SIMD_NI       15

#define DFR0_ARCH_VERSION           0
#define DFR0_ARCH_VERSION_V8A       6

#define DFR0_TRACE_VERSION          1
#define DFR0_TRACE_VERSION_NI       0
#define DFR0_TRACE_VERSION_IMP      1

#define DFR0_PERFMON_VERSION        2
#define DFR0_PERFMON_VERSION_NI     0
#define DFR0_PERFMON_VERSION_V3     1
#define DFR0_PERFMON_VERSION_UNK    15

#define DFR0_BREAKPOINT_COUNT       3

#define DFR0_WATCHPOINT_COUNT       5

#define DFR0_CONTEXT_BP_COUNT       7

#define MMFR0_ADDRESS_BITS          0
#define MMFR0_ADDRESS_BITS_32       0
#define MMFR0_ADDRESS_BITS_36       1
#define MMFR0_ADDRESS_BITS_40       2
#define MMFR0_ADDRESS_BITS_42       3
#define MMFR0_ADDRESS_BITS_44       4
#define MMFR0_ADDRESS_BITS_48       5

#define MMFR0_ASID_BITS             1
#define MMFR0_ASID_BITS_8           0
#define MMFR0_ASID_BITS_16          2

#define MMFR0_MIXED_ENDIAN          2
#define MMFR0_MIXED_ENDIAN_NI       0
#define MMFR0_MIXED_ENDIAN_IMP      1

#define MMFR0_SECURE_MEMORY         3
#define MMFR0_SECURE_MEMORY_NI      0
#define MMFR0_SECURE_MEMORY_IMP     1

#define MMFR0_MIXED_ENDIAN_EL0      4
#define MMFR0_MIXED_ENDIAN_EL0_NI   0
#define MMFR0_MIXED_ENDIAN_EL0_IMP  1

#define ISAR0_AES                   1
#define ISAR0_AES_NI                0
#define ISAR0_AES_INSTRUCTIONS      1
#define ISAR0_AES_PLUS_PMULL64      2

#define ISAR0_SHA1                  2
#define ISAR0_SHA1_NI               0
#define ISAR0_SHA1_INSTRUCTIONS     1

#define ISAR0_SHA2                  3
#define ISAR0_SHA2_NI               0
#define ISAR0_SHA2_INSTRUCTIONS     1

#define ISAR0_CRC32                 4
#define ISAR0_CRC32_NI              0
#define ISAR0_CRC32_INSTRUCTIONS    1

/*
#define CPVFP_FPSID_SW                  0x00800000      // Software-only floating-point

#define CPVFP_FPEXC_EX                  0x80000000      // Extra state required for context save
#define CPVFP_FPEXC_EN                  0x40000000      // VFP/Advanced SIMD enable
#define CPVFP_FPEXC_DEX                 0x20000000      // synchronous exception flag
#define CPVFP_FPEXC_FP2V                0x10000000      // FPINST2 is valid
*/
#define ARM64_CPACR_VFP_MASK            0x00300000      // Mask for enabling/disabling VFP/NEON access
#define ARM64_CPACR_VFP_MASK_BIT        20              // Index of low bit for TBNZ purposes

#define ARM64_CPTR_VFP_USERMODE         0x00000400      // Enable CP10/CP11 in user mode

#define ARM64_CPTR_TFP                  0x00000400      // Trap Floating Point instructions from EL0/1 to EL2 that are not trapped to EL1.
#define ARM64_CPTR_TTA                  0x00100000      // Trap Trace functionality to EL2 when executed from EL0/1
#define ARM64_CPTR_CPAC                 0x80000000      // Trap direct access to CPACR or CPACR_EL1 from EL1 to EL2
#define ARM64_CPTR_RES1_BITS            0x000033FF      // Bits in CPTR_ELx that are RES1

#define ARM_MPIDR_U                   0x40000000
#define ARM_MPIDR_MT                  0x01000000

#define ARM64_SCTLR_M                    0x00000001
#define ARM64_SCTLR_A                    0x00000002
#define ARM64_SCTLR_C                    0x00000004
#define ARM64_SCTLR_SA                   0x00000008 /* ARMv7: was W */
#define ARM64_SCTLR_SA0                  0x00000010 /* ARMv7: was P */
#define ARM64_SCTLR_CP15BEN              0x00000020 /* ARMv7: was D */
#define ARM64_SCTLR_THEE                 0x00000040 /* ARMv7: was L */
#define ARM64_SCTLR_ITD                  0x00000080 /* ARMv7: was B */
#define ARM64_SCTLR_SED                  0x00000100 /* ARMv7: was S */
#define ARM64_SCTLR_UMA                  0x00000200 /* ARMv7: was R */
#define ARM64_SCTLR_RES0_10              0x00000400 /* ARMv7: was F */
#define ARM64_SCTLR_RES1_11              0x00000800 /* ARMv7: was Z */
#define ARM64_SCTLR_I                    0x00001000
#define ARM64_SCTLR_RES0_13              0x00002000 /* ARMv7: was V */
#define ARM64_SCTLR_DZE                  0x00004000 /* ARMv7: was RR */
#define ARM64_SCTLR_UCT                  0x00008000 /* ARMv7: was L4 */
#define ARM64_SCTLR_nTWI                 0x00010000 /* ARMv7: was DT */
#define ARM64_SCTLR_RES0_17              0x00020000
#define ARM64_SCTLR_nTWE                 0x00040000 /* ARMv7: was IT */
#define ARM64_SCTLR_WXN                  0x00080000
#define ARM64_SCTLR_RES1_20              0x00100000
#define ARM64_SCTLR_RES0_21              0x00200000 /* ARMv7: was FI */
#define ARM64_SCTLR_RES1_22              0x00400000 /* ARMv7: was U */
#define ARM64_SCTLR_RES1_23              0x00800000 /* ARMv7: was XP */
#define ARM64_SCTLR_E0E                  0x01000000 /* ARMv7: was VE */
#define ARM64_SCTLR_EE                   0x02000000
#define ARM64_SCTLR_UCI                  0x04000000 /* ARMv7: was L2 */
#define ARM64_SCTLR_RES0_27              0x08000000 /* ARMv7: was NM */
#define ARM64_SCTLR_RES1_28              0x10000000 /* ARMv7: was TR */
#define ARM64_SCTLR_RES1_29              0x20000000 /* ARMv7: was AF */
#define ARM64_SCTLR_RES0_30              0x40000000 /* ARMv7: was TE */
#define ARM64_SCTLR_RES0_31              0x80000000 /* ARMv7: was X3 */

#define ARM64_PFR0_EL1_EL0_MASK          0x000000000000000F
#define ARM64_PFR0_EL1_EL1_MASK          0x00000000000000F0
#define ARM64_PFR0_EL1_EL2_MASK          0x0000000000000F00
#define ARM64_PFR0_EL1_EL3_MASK          0x000000000000F000
#define ARM64_PFR0_EL1_FP_MASK           0x00000000000F0000
#define ARM64_PFR0_EL1_ADVSIMD_MASK      0x0000000000F00000
#define ARM64_PFR0_EL1_GIC_MASK          0x000000000F000000

#define ARM64_TTBRx_BADDR_MASK     0x0000ffffffffffffULL
#define ARM64_TTBRx_ASID_MASK      0xffff000000000000ULL
#define ARM64_TTBRx_ASID_SHIFT     48

#define ARM64_HCR_EL2_VM                0x000000000000001ULL
#define ARM64_HCR_EL2_SWIO              0x000000000000002ULL
#define ARM64_HCR_EL2_PTW               0x000000000000004ULL
#define ARM64_HCR_EL2_FMO               0x000000000000008ULL
#define ARM64_HCR_EL2_IMO               0x000000000000010ULL
#define ARM64_HCR_EL2_AMO               0x000000000000020ULL
#define ARM64_HCR_EL2_VF                0x000000000000040ULL
#define ARM64_HCR_EL2_VI                0x000000000000080ULL
#define ARM64_HCR_EL2_VSE               0x000000000000100ULL
#define ARM64_HCR_EL2_FB                0x000000000000200ULL
#define ARM64_HCR_EL2_BSU_NONE          0x000000000000000ULL
#define ARM64_HCR_EL2_BSU_ISH           0x000000000000400ULL
#define ARM64_HCR_EL2_BSU_OSH           0x000000000000800ULL
#define ARM64_HCR_EL2_BSU_FS            0x000000000000C00ULL
#define ARM64_HCR_EL2_BSU_MASK          0x000000000000C00ULL
#define ARM64_HCR_EL2_DC                0x000000000001000ULL
#define ARM64_HCR_EL2_TWI               0x000000000002000ULL
#define ARM64_HCR_EL2_TWE               0x000000000004000ULL
#define ARM64_HCR_EL2_TID0              0x000000000008000ULL
#define ARM64_HCR_EL2_TID1              0x000000000010000ULL
#define ARM64_HCR_EL2_TID2              0x000000000020000ULL
#define ARM64_HCR_EL2_TID3              0x000000000040000ULL
#define ARM64_HCR_EL2_TSC               0x000000000080000ULL
#define ARM64_HCR_EL2_TIDCP             0x000000000100000ULL
#define ARM64_HCR_EL2_TACR              0x000000000200000ULL
#define ARM64_HCR_EL2_TSW               0x000000000400000ULL
#define ARM64_HCR_EL2_TPC               0x000000000800000ULL
#define ARM64_HCR_EL2_TPU               0x000000001000000ULL
#define ARM64_HCR_EL2_TTLB              0x000000002000000ULL
#define ARM64_HCR_EL2_TVM               0x000000004000000ULL
#define ARM64_HCR_EL2_TGE               0x000000008000000ULL
#define ARM64_HCR_EL2_TDZ               0x000000010000000ULL
#define ARM64_HCR_EL2_HCD               0x000000020000000ULL
#define ARM64_HCR_EL2_TRVM              0x000000040000000ULL
#define ARM64_HCR_EL2_RW                0x000000080000000ULL
#define ARM64_HCR_EL2_CD                0x000000100000000ULL
#define ARM64_HCR_EL2_ID                0x000000200000000ULL

#define ARM64_TCR_T0SZ_MASK             0x000000000000003fULL
#define ARM64_TCR_RES0_1                0x0000000000000040ULL
#define ARM64_TCR_EPD0                  0x0000000000000080ULL
#define ARM64_TCR_IRGN0_NC              0x0000000000000000ULL
#define ARM64_TCR_IRGN0_WBWA            0x0000000000000100ULL
#define ARM64_TCR_IRGN0_WT              0x0000000000000200ULL
#define ARM64_TCR_IRGN0_WB              0x0000000000000300ULL
#define ARM64_TCR_IRGN0_MASK            0x0000000000000300ULL
#define ARM64_TCR_ORGN0_NC              0x0000000000000000ULL
#define ARM64_TCR_ORGN0_WBWA            0x0000000000000400ULL
#define ARM64_TCR_ORGN0_WT              0x0000000000000800ULL
#define ARM64_TCR_ORGN0_WB              0x0000000000000c00ULL
#define ARM64_TCR_ORGN0_MASK            0x0000000000000c00ULL
#define ARM64_TCR_SH0_NON_SHARED        0x0000000000000000ULL
#define ARM64_TCR_SH0_OUTER_SHARED      0x0000000000002000ULL
#define ARM64_TCR_SH0_INNER_SHARED      0x0000000000003000ULL
#define ARM64_TCR_SH0_MASK              0x0000000000003000ULL
#define ARM64_TCR_TG0_4K                0x0000000000000000ULL
#define ARM64_TCR_TG0_16K               0x0000000000008000ULL
#define ARM64_TCR_TG0_64K               0x0000000000004000ULL
#define ARM64_TCR_TG0_RESERVED          0x000000000000c000ULL
#define ARM64_TCR_TG0_MASK              0x000000000000c000ULL

#define ARM64_TCR_T1SZ_MASK             0x00000000003f0000ULL
#define ARM64_TCR_A1                    0x0000000000400000ULL
#define ARM64_TCR_EPD1                  0x0000000000800000ULL
#define ARM64_TCR_IRGN1_NC              0x0000000000000000ULL
#define ARM64_TCR_IRGN1_WBWA            0x0000000001000000ULL
#define ARM64_TCR_IRGN1_WT              0x0000000002000000ULL
#define ARM64_TCR_IRGN1_WB              0x0000000003000000ULL
#define ARM64_TCR_IRGN1_MASK            0x0000000003000000ULL
#define ARM64_TCR_ORGN1_NC              0x0000000000000000ULL
#define ARM64_TCR_ORGN1_WBWA            0x0000000004000000ULL
#define ARM64_TCR_ORGN1_WT              0x0000000008000000ULL
#define ARM64_TCR_ORGN1_WB              0x000000000c000000ULL
#define ARM64_TCR_ORGN1_MASK            0x000000000c000000ULL
#define ARM64_TCR_SH1_NON_SHARED        0x0000000000000000ULL
#define ARM64_TCR_SH1_OUTER_SHARED      0x0000000020000000ULL
#define ARM64_TCR_SH1_INNER_SHARED      0x0000000030000000ULL
#define ARM64_TCR_SH1_MASK              0x0000000030000000ULL
#define ARM64_TCR_TG1_4K                0x0000000080000000ULL
#define ARM64_TCR_TG1_16K               0x0000000040000000ULL
#define ARM64_TCR_TG1_64K               0x00000000c0000000ULL
#define ARM64_TCR_TG1_RESERVED          0x0000000000000000ULL
#define ARM64_TCR_TG1_MASK              0x00000000c0000000ULL

#define ARM64_TCR_IPASize_4G            0x0000000000000000ULL
#define ARM64_TCR_IPASize_64G           0x0000000100000000ULL
#define ARM64_TCR_IPASize_1T            0x0000000200000000ULL
#define ARM64_TCR_IPASize_4T            0x0000000300000000ULL
#define ARM64_TCR_IPASize_16T           0x0000000400000000ULL
#define ARM64_TCR_IPASize_256T          0x0000000500000000ULL
#define ARM64_TCR_IPASize_MASK          0x0000000700000000ULL
#define ARM64_TCR_RES0_35               0x0000000800000000ULL
#define ARM64_TCR_AS                    0x0000001000000000ULL
#define ARM64_TCR_TBI0                  0x0000002000000000ULL
#define ARM64_TCR_TBI1                  0x0000004000000000ULL

#define ARM64_TCR_T0SZ_SHIFT            0
#define ARM64_TCR_T1SZ_SHIFT            16
#define ARM64_TCR_IPASize_SHIFT         32

#define ARM64_TCR_PASize_4G             0x00000000
#define ARM64_TCR_PASize_64G            0x00010000
#define ARM64_TCR_PASize_1T             0x00020000
#define ARM64_TCR_PASize_4T             0x00030000
#define ARM64_TCR_PASize_16T            0x00040000
#define ARM64_TCR_PASize_256T           0x00050000
#define ARM64_TCR_PASize_MASK           0x00070000

#define ARM64_TCR_EL2_TBI               0x00100000
#define ARM64_TCR_EL2_PASize_SHIFT      16

/*
#define CP15_xFSR_FS_LOW                0x0000000f
#define CP15_xFSR_FS_HIGH               0x00000400
#define CP15_DFSR_WnR                   0x00000800
*/

#define ARM64_PMCR_N_MASK               0x0000f800
#define ARM64_PMCR_N_SHIFT              11
#define ARM64_PMCR_LC                   0x00000040
#define ARM64_PMCR_DP                   0x00000020
#define ARM64_PMCR_X                    0x00000010
#define ARM64_PMCR_D                    0x00000008
#define ARM64_PMCR_C                    0x00000004
#define ARM64_PMCR_P                    0x00000002
#define ARM64_PMCR_E                    0x00000001

#define ARM64_PMCNTEN_PMCCNT            0x80000000

#define ARM64_PMUSERENR_EN              0x00000001
#define ARM64_PMUSERENR_SW              0x00000002
#define ARM64_PMUSERENR_CR              0x00000004
#define ARM64_PMUSERENR_ER              0x00000008

#define ARM64_PMCCFILTR_M               0x04000000
#define ARM64_PMCCFILTR_NSH             0x08000000
#define ARM64_PMCCFILTR_NSU             0x10000000
#define ARM64_PMCCFILTR_NSK             0x20000000
#define ARM64_PMCCFILTR_U               0x40000000
#define ARM64_PMCCFILTR_P               0x80000000

#define ARM64_MDCR_HPMN_MASK            0x0000001F
#define ARM64_MDCR_TPMCR                0x00000020
#define ARM64_MDCR_TPM                  0x00000040
#define ARM64_MDCR_HPME                 0x00000080
#define ARM64_MDCR_TDE                  0x00000100
#define ARM64_MDCR_TDA                  0x00000200
#define ARM64_MDCR_TDOSA                0x00000400
#define ARM64_MDCR_TDRA                 0x00000800

CFORCEINLINE
VOID
_SyncPte (
    VOID)
{
    _DataSynchronizationBarrier();
    _InstructionSynchronizationBarrier();
}

#define SWFS_WRITE                      0x01
#define SWFS_EXECUTE                    0x08
#define SWFS_PAGE_FAULT                 0x10
#define SWFS_ALIGN_FAULT                0x20
#define SWFS_HWERR_FAULT                0x40
#define SWFS_DEBUG_FAULT                0x80

#define ARM64_MAIR_CACHE_WBWA       0xff
#define ARM64_MAIR_CACHE_NC         0x00
#define ARM64_MAIR_CACHE_WTNA       0xaa
#define ARM64_MAIR_CACHE_WC         0x44

#define ARM64_MAIR_DEFAULT \
    (((ULONG64) ARM64_MAIR_CACHE_WBWA <<  0) | \
     ((ULONG64) ARM64_MAIR_CACHE_NC   <<  8) | \
     ((ULONG64) ARM64_MAIR_CACHE_WTNA << 16) | \
     ((ULONG64) ARM64_MAIR_CACHE_WC   << 24) | \
     ((ULONG64) ARM64_MAIR_CACHE_WBWA << 32) | \
     ((ULONG64) ARM64_MAIR_CACHE_NC   << 40) | \
     ((ULONG64) ARM64_MAIR_CACHE_WTNA << 48) | \
     ((ULONG64) ARM64_MAIR_CACHE_WC   << 56))

#define ARM64_DBGBCR_MISMATCH_BIT        0x00400000
#define ARM64_DBGBCR_SECURITY_BITS       0x0000c000
#define   ARM64_DBGBCR_ANY_SECURE        0x00000000
#define   ARM64_DBGBCR_NONSECURE_ONLY    0x00004000
#define   ARM64_DBGBCR_SECURE_ONLY       0x00008000
#define ARM64_DBGBCR_PRIVILEGE_BITS      0x00000006
#define   ARM64_DBGBCR_USER_SYS_SUPER    0x00000000
#define   ARM64_DBGBCR_PRIVILEGED_ONLY   0x00000002
#define   ARM64_DBGBCR_USER_ONLY         0x00000004
#define   ARM64_DBGBCR_ANY_PRIVILEGE     0x00000006
#define ARM64_DBGBCR_ENABLE_BIT          0x00000001

#define ARM64_MDSCR_RXfull               0x40000000
#define ARM64_MDSCR_TXfull               0x20000000
#define ARM64_MDSCR_MDE                  0x00008000
#define ARM64_MDSCR_HDE                  0x00004000
#define ARM64_MDSCR_KDE                  0x00002000
#define ARM64_MDSCR_TDCC                 0x00001000
#define ARM64_MDSCR_SS                   0x00000001

#define PASSIVE_LEVEL 0                 // Passive release level
#define LOW_LEVEL 0                     // Lowest interrupt level
#define APC_LEVEL 1                     // APC interrupt level
#define DISPATCH_LEVEL 2                // Dispatcher level

#define CLOCK_LEVEL 13                  // Interval clock level
#define IPI_LEVEL 14                    // Interprocessor interrupt level
#define DRS_LEVEL 14                    // Deferred Recovery Service level
#define POWER_LEVEL 14                  // Power failure level
#define PROFILE_LEVEL 15                // timer used for profiling.
#define HIGH_LEVEL 15                   // Highest interrupt level

#define SYNCH_LEVEL (IPI_LEVEL-2)

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(KeGetDcacheFillSize)      // Use GetDmaAlignment
#endif

#define KeGetDcacheFillSize() 1L

VOID
KeFlushIoBuffers(
    _In_ PMDL  Mdl,
    _In_ BOOLEAN  ReadOperation,
    _In_ BOOLEAN  DmaOperation
    );

VOID
KeFlushIoRectangle (
    _In_ PMDL Mdl,
    _In_ PVOID Start,
    _In_ ULONG Width,
    _In_ ULONG Height,
    _In_ ULONG Stride,
    _In_ BOOLEAN ReadOperation
    );

#define ExAcquireSpinLock(Lock, OldIrql) KeAcquireSpinLock((Lock), (OldIrql))
#define ExReleaseSpinLock(Lock, OldIrql) KeReleaseSpinLock((Lock), (OldIrql))
#define ExAcquireSpinLockAtDpcLevel(Lock) KeAcquireSpinLockAtDpcLevel(Lock)
#define ExReleaseSpinLockFromDpcLevel(Lock) KeReleaseSpinLockFromDpcLevel(Lock)

typedef struct _HARDWARE_PTE {
    ULONGLONG Valid : 1;
    ULONGLONG NotLargePage : 1;         // ARM Large page bit is inverted !
    ULONGLONG CacheType : 2;            // Lower 2 bits for cache type encoding
    ULONGLONG OsAvailable2 : 1;         // Memory Attribute Index (can be Mm usage)
    ULONGLONG NonSecure : 1;
    ULONGLONG Owner : 1;                // 0 == kernel, 1 = user
    ULONGLONG NotDirty : 1;             // 0 == modified (written), 1 == clean (ronly)
    ULONGLONG Shareability : 2;
    ULONGLONG Accessed : 1;
    ULONGLONG NonGlobal : 1;
    ULONGLONG PageFrameNumber : 36;
    ULONGLONG reserved1 : 4;
    ULONGLONG ContiguousBit : 1;
    ULONGLONG PrivilegedNoExecute : 1;
    ULONGLONG UserNoExecute : 1;
    ULONGLONG Writable : 1;             // OS managed
    ULONGLONG CopyOnWrite : 1;          // OS managed
    ULONGLONG OsAvailable : 2;          // 2 bits available for Mm usage
    ULONGLONG PxnTable : 1;
    ULONGLONG UxnTable : 1;
    ULONGLONG ApTable : 2;
    ULONGLONG NsTable : 1;
} HARDWARE_PTE, *PHARDWARE_PTE;

#define INITIALIZE_DIRECTORY_TABLE_BASE(dirbase,pfn) \
     *((PULONG64)(dirbase)) = (((ULONG64)(pfn)) << PAGE_SHIFT)

typedef struct _KSPECIAL_REGISTERS {

    ULONG64 Elr_El1;
    ULONG32 Spsr_El1;
    ULONG64 Tpidr_El0;
    ULONG64 Tpidrro_El0;
    ULONG64 Tpidr_El1;
    ULONG64 KernelBvr[ARM64_MAX_BREAKPOINTS];
    ULONG KernelBcr[ARM64_MAX_BREAKPOINTS];
    ULONG64 KernelWvr[ARM64_MAX_WATCHPOINTS];
    ULONG KernelWcr[ARM64_MAX_WATCHPOINTS];
} KSPECIAL_REGISTERS, *PKSPECIAL_REGISTERS;

typedef struct _KARM64_ARCH_STATE
{
    ULONG64 Midr_El1;
    ULONG64 Sctlr_El1;
    ULONG64 Actlr_El1;
    ULONG64 Cpacr_El1;
    ULONG64 Tcr_El1;
    ULONG64 Ttbr0_El1;
    ULONG64 Ttbr1_El1;
    ULONG64 Esr_El1;
    ULONG64 Far_El1;
    ULONG64 Pmcr_El0;
    ULONG64 Pmcntenset_El0;
    ULONG64 Pmccntr_El0;
    ULONG64 Pmxevcntr_El0[MAX_EVENT_COUNTERS];
    ULONG64 Pmxevtyper_El0[MAX_EVENT_COUNTERS];
    ULONG64 Pmovsclr_El0;
    ULONG64 Pmselr_El0;
    ULONG64 Pmuserenr_El0;
    ULONG64 Mair_El1;
    ULONG64 Vbar_El1;
} KARM64_ARCH_STATE, *PKARM64_ARCH_STATE;

typedef struct _KPROCESSOR_STATE {
    KSPECIAL_REGISTERS SpecialRegisters;
    KARM64_ARCH_STATE ArchState;
    CONTEXT ContextFrame;
} KPROCESSOR_STATE, *PKPROCESSOR_STATE;

typedef enum {
    CPU_UNKNOWN,
    CPU_ARM,
    CPU_QUALCOMM,
    CPU_AMD
} CPU_VENDORS;

#define PRCB_MAJOR_VERSION 1
#define PRCB_MINOR_VERSION 1

#define PRCB_BUILD_DEBUG 0x1
#define PRCB_BUILD_UNIPROCESSOR 0x2

#define MAXIMUM_CACHES 6

typedef struct _KPRCB {

    UCHAR LegacyNumber;             // +000/+980
    UCHAR ReservedMustBeZero;       // +001/+981
    BOOLEAN IdleHalt;               // +002/+982
    struct _KTHREAD *CurrentThread; // +008/+988
    struct _KTHREAD *NextThread;    // +010/+990
    struct _KTHREAD *IdleThread;    // +018/+998
    UCHAR NestingLevel;             // +020/+9A0
    BOOLEAN ClockOwner;             // +021/+9A1
    union {                         // +022/+9A2
        UCHAR PendingTickFlags;

        struct {
            UCHAR PendingTick:1;
            UCHAR PendingBackupTick:1;
        };
    };

    UCHAR IdleState;                // +023/+9A3
    ULONG Number;                   // +024/+9A4
    KSPIN_LOCK PrcbLock;
    PSCHAR PriorityState;
    KPROCESSOR_STATE ProcessorState;
    USHORT ProcessorModel;
    USHORT ProcessorRevision;
    ULONG MHz;
    ULONG64 CycleCounterFrequency;
    ULONG64 HalReserved[10];
    USHORT MinorVersion;
    USHORT MajorVersion;
    UCHAR BuildType;
    UCHAR CpuVendor;
    UCHAR CoresPerPhysicalProcessor;
    UCHAR LogicalProcessorsPerCore;
    PVOID AcpiReserved;
    KAFFINITY GroupSetMember;
    UCHAR Group;
    UCHAR GroupIndex;
} KPRCB, *PKPRCB, *RESTRICTED_POINTER PRKPRCB;

C_ASSERT(FIELD_OFFSET(KPRCB, HalReserved) == 0x700);  // Do not move field
C_ASSERT(FIELD_OFFSET(KPRCB, AcpiReserved) == 0x758); // Do not move field

#define PCR_MINOR_VERSION 1
#define PCR_MAJOR_VERSION 1

typedef struct _KPCR {
    union {
        NT_TIB NtTib;                   // +000
        struct {
            PVOID TibPad0[2];           // +000
            PVOID Spare1;               // +010
            struct _KPCR *Self;         // +018
            PVOID PcrReserved0;         // +020
            PKSPIN_LOCK_QUEUE LockArray;// +028
            PVOID Used_Self;            // +030
        };
    };

    KIRQL CurrentIrql;                  // +038
    UCHAR SecondLevelCacheAssociativity;// +039
    UCHAR Pad1[2];                      // +03A
    USHORT MajorVersion;                // +03C
    USHORT MinorVersion;                // +03E
    ULONG StallScaleFactor;             // +040

    ULONG SecondLevelCacheSize;         // +044
    union {
        USHORT SoftwareInterruptPending;// +048 -- Software Interrupt Pending Flag
        struct {
            UCHAR ApcInterrupt;         // +048 -- 0x01 if APC int pending
            UCHAR DispatchInterrupt;    // +049 -- 0x01 if dispatch int pending
        };
    };
    USHORT InterruptPad;                // +04A

    ULONG64 PanicStorage[6];            // +050 -- Must be 16-byte aligned
    PVOID KdVersionBlock;               // +080
    PVOID HalReserved[15];              // +088
    PVOID Idt[256];                     // +100
    PVOID *IdtExt;                      // +900
    PVOID PcrAlign[15];                 // +908

    KPRCB Prcb;                         // +980

} KPCR, *PKPCR;

typedef union _ARM64_IDCODE {
    ULONG64 Ulong;
    struct {
        ULONG64 MinorRevision :  4;
        ULONG64 Model         : 12;
        ULONG64 Architecture  :  4;
        ULONG64 Revision      :  4;
        ULONG64 Implementer   :  8;
        ULONG64 Reserved      : 32;
    };
} ARM64_IDCODE, *PARM64_IDCODE;

C_ASSERT(sizeof(ARM64_IDCODE) == 8);

/*
#define CP15_CR0_HARVARD_CACHE (1 << 24)
*/

#define ARM64_L1_ICACHE_UNKNOWN 0
#define ARM64_L1_ICACHE_VIVT    1
#define ARM64_L1_ICACHE_VIPT    2
#define ARM64_L1_ICACHE_PIPT    3

typedef union _ARM64_CACHE_TYPE {
    ULONG64 Ulong;
    struct {
        ULONG64 IMinLine               : 4;
        ULONG64 Reserved               : 10;
        ULONG64 IPolicy                : 2;
        ULONG64 DMinLine               : 4;
        ULONG64 Reserved2              : 12;
    };
} ARM64_CACHE_TYPE, *PARM64_CACHE_TYPE;

C_ASSERT(sizeof(ARM64_CACHE_TYPE) == 8);

#define ARM64_CACHE_NONE        0
#define ARM64_CACHE_INSTRUCTION 1
#define ARM64_CACHE_DATA        2
#define ARM64_CACHE_HARVARD     3
#define ARM64_CACHE_UNIFIED     4

typedef union _ARM64_CACHE_LEVEL_ID {
    ULONG64 Ulong;
    struct {
        ULONG64 Level1 : 3;
        ULONG64 Level2 : 3;
        ULONG64 Level3 : 3;
        ULONG64 Level4 : 3;
        ULONG64 Level5 : 3;
        ULONG64 Level6 : 3;
        ULONG64 Level7 : 3;
        ULONG64 LoUIS  : 3;
        ULONG64 LoC    : 3;
        ULONG64 LoU    : 3;
    };
} ARM64_CACHE_LEVEL_INFO;

C_ASSERT(sizeof(ARM64_CACHE_LEVEL_INFO) == 8);

#define ARM64_CACHE_SELECT_DATA_OR_UNIFIED 0
#define ARM64_CACHE_SELECT_INSTRUCTION     1

typedef union _ARM64_CACHE_INFO_SELECTOR {
    ULONG64 Ulong;
    struct {
        ULONG64 Select : 1;
        ULONG64 Level  : 3;
    };
} ARM64_CACHE_INFO_SELECTOR;

C_ASSERT(sizeof(ARM64_CACHE_INFO_SELECTOR) == 8);

typedef union _ARM64_CACHE_INFO {
    ULONG64 Ulong;
    struct {
        ULONG64 LineSize           : 3;
        ULONG64 Associativity      : 10;
        ULONG64 NumberOfSets       : 15;
        ULONG64 WriteThrough       : 1;
        ULONG64 WriteBack          : 1;
        ULONG64 ReadAllocate       : 1;
        ULONG64 WriteAllocate      : 1;
    };
} ARM64_CACHE_INFO;

C_ASSERT(sizeof(ARM64_CACHE_INFO) == 8);

#define ARM64_BREAK_DEBUG_BASE          0xf000
#define ARM64_BREAKPOINT                (ARM64_BREAK_DEBUG_BASE + 0)
#define ARM64_ASSERT                    (ARM64_BREAK_DEBUG_BASE + 1)
#define ARM64_DEBUG_SERVICE             (ARM64_BREAK_DEBUG_BASE + 2)
#define ARM64_FASTFAIL                  (ARM64_BREAK_DEBUG_BASE + 3)
#define ARM64_DIVIDE_BY_0               (ARM64_BREAK_DEBUG_BASE + 4)

typedef struct _KEXCEPTION_FRAME
{
    ULONG64 X19;
    ULONG64 X20;
    ULONG64 X21;
    ULONG64 X22;
    ULONG64 X23;
    ULONG64 X24;
    ULONG64 X25;
    ULONG64 X26;
    ULONG64 X27;
    ULONG64 X28;
    ULONG64 Fp;
    ULONG64 Return;
} KEXCEPTION_FRAME, *PKEXCEPTION_FRAME;

#define KEXCEPTION_FRAME_LENGTH sizeof(KEXCEPTION_FRAME)

C_ASSERT((sizeof(KEXCEPTION_FRAME) & STACK_ROUND) == 0);
C_ASSERT((FIELD_OFFSET(KEXCEPTION_FRAME, Return) + sizeof(ULONG64)) == sizeof(KEXCEPTION_FRAME));

#define EXCEPTION_RECORD_LENGTH ((sizeof(EXCEPTION_RECORD) + STACK_ROUND - 1) & ~STACK_ROUND)

typedef struct _MACHINE_FRAME {
    ULONG64 Sp;
    ULONG64 Pc;
} MACHINE_FRAME, *PMACHINE_FRAME;

#define MACHINE_FRAME_LENGTH sizeof(MACHINE_FRAME)

C_ASSERT((sizeof(MACHINE_FRAME) & STACK_ROUND) == 0);

typedef struct _KSWITCH_FRAME {
    KIRQL ApcBypass;
    UCHAR Fill[7];
    ULONG64 Tpidr;
    ULONG64 Fp;
    ULONG64 Return;
} KSWITCH_FRAME, *PKSWITCH_FRAME;

#define KSWITCH_FRAME_LENGTH sizeof(KSWITCH_FRAME)

C_ASSERT((sizeof(KSWITCH_FRAME) & STACK_ROUND) == 0);

typedef struct _KSTART_FRAME {
    ULONG64 X0;
    ULONG64 X1;
    ULONG64 X2;
    ULONG64 Return;
} KSTART_FRAME, *PKSTART_FRAME;

#define KSTART_FRAME_LENGTH sizeof(KSTART_FRAME)

C_ASSERT((sizeof(KSTART_FRAME) & STACK_ROUND) == 0);

typedef struct _KARM64_VFP_STATE
{
    struct _KARM64_VFP_STATE *Link;         // link to next state entry
    ULONG Fpcr;                             // FPCR register
    ULONG Fpsr;                             // FPSR register
    NEON128 V[32];                          // All V registers (0-31)
} KARM64_VFP_STATE, *PKARM64_VFP_STATE;

#define KTRAP_FRAME_ARGUMENTS (10 * 8)       // up to 10 in-memory syscall args

typedef struct _KTRAP_FRAME {

    /* +0x000 */ UCHAR ExceptionActive;              // always valid
    /* +0x001 */ UCHAR ContextFromKFramesUnwound;    // set if KeContextFromKFrames created this frame
    /* +0x002 */ UCHAR DebugRegistersValid;          // always valid
    /* +0x003 */ union {
                     KPROCESSOR_MODE PreviousMode;   // system services only
                     KIRQL PreviousIrql;             // interrupts only
                 };

    /* +0x004 */ ULONG FaultStatus;                      // page faults only
    /* +0x008 */ union {
                     ULONG64 FaultAddress;             // page faults only
                     ULONG64 TrapFrame;                // system services only
                 };

    /* +0x010 */ PKARM64_VFP_STATE VfpState;
    /* +0x018 */ ULONG Bcr[ARM64_MAX_BREAKPOINTS];
    /* +0x038 */ ULONG64 Bvr[ARM64_MAX_BREAKPOINTS];
    /* +0x078 */ ULONG Wcr[ARM64_MAX_WATCHPOINTS];
    /* +0x080 */ ULONG64 Wvr[ARM64_MAX_WATCHPOINTS];
    /* +0x090 */ ULONG Spsr;
    /* +0x094 */ ULONG Esr;
    /* +0x098 */ ULONG64 Sp;
    /* +0x0A0 */ ULONG64 X[19];
    /* +0x138 */ ULONG64 Lr;
    /* +0x140 */ ULONG64 Fp;
    /* +0x148 */ ULONG64 Pc;
    /* +0x150 */

} KTRAP_FRAME, *PKTRAP_FRAME;

#define KEXCEPTION_ACTIVE_INTERRUPT_FRAME 0
#define KEXCEPTION_ACTIVE_EXCEPTION_FRAME 1
#define KEXCEPTION_ACTIVE_SERVICE_FRAME   2

#define KTRAP_FRAME_LENGTH sizeof(KTRAP_FRAME)

C_ASSERT((sizeof(KTRAP_FRAME) & STACK_ROUND) == 0);

#define ARM64_RED_ZONE_BYTES      16

_IRQL_requires_(IPI_LEVEL);
NTKERNELAPI
BOOLEAN
KiIpiServiceRoutine (
    _In_ PVOID Interrupt,
    _In_ PVOID Context
    );

NTKERNELAPI
NTSTATUS
KiConnectHalInterrupt (
    _Inout_ PVOID Interrupt
    );

NTKERNELAPI
VOID
KiReplayInterrupt (
    _In_ ULONG Vector,
    _In_ KIRQL Irql,
    _In_ KIRQL PreviousIrql,
    _In_ ULONG OpaqueToken
    );

NTKERNELAPI
VOID
KeProfileInterruptWithSource (
    _In_ PKTRAP_FRAME TrapFrame,
    _In_ KPROFILE_SOURCE ProfileSource
    );

typedef struct _UCALLOUT_FRAME {
    PVOID Buffer;
    ULONG Length;
    ULONG ApiNumber;
    ULONG64 Reserved;
    ULONG64 OriginalLr;
    MACHINE_FRAME MachineFrame;
} UCALLOUT_FRAME, *PUCALLOUT_FRAME;

C_ASSERT((sizeof(UCALLOUT_FRAME) & STACK_ROUND) == 0);

typedef struct _KFLOATING_SAVE {
    ULONG Dummy;
} KFLOATING_SAVE, *PKFLOATING_SAVE;

#define PXE_BASE          0xFFFFF6FB7DBED000UI64
#define PXE_SELFMAP       0xFFFFF6FB7DBEDF68UI64
#define PPE_BASE          0xFFFFF6FB7DA00000UI64
#define PDE_BASE          0xFFFFF6FB40000000UI64
#define PTE_BASE          0xFFFFF68000000000UI64

#define PXE_TOP           0xFFFFF6FB7DBEDFFFUI64
#define PPE_TOP           0xFFFFF6FB7DBFFFFFUI64
#define PDE_TOP           0xFFFFF6FB7FFFFFFFUI64
#define PTE_TOP           0xFFFFF6FFFFFFFFFFUI64

#define PDE_KTBASE_ARM64  PPE_BASE

#define PTI_SHIFT 12
#define PDI_SHIFT 21
#define PPI_SHIFT 30
#define PXI_SHIFT 39

#define PTE_PER_PAGE 512
#define PDE_PER_PAGE 512
#define PPE_PER_PAGE 512
#define PXE_PER_PAGE 512

#define PTI_MASK_ARM64 (PTE_PER_PAGE - 1)
#define PDI_MASK_ARM64 (PDE_PER_PAGE - 1)
#define PPI_MASK (PPE_PER_PAGE - 1)
#define PXI_MASK (PXE_PER_PAGE - 1)

#define MM_HIGHEST_USER_ADDRESS MmHighestUserAddress
#define MM_SYSTEM_RANGE_START MmSystemRangeStart

#if defined(_LOCAL_COPY_USER_PROBE_ADDRESS_)

#define MM_USER_PROBE_ADDRESS _LOCAL_COPY_USER_PROBE_ADDRESS_

#if defined(__CONVERGED_WIN32K_DRIVER__)
extern DLLBASEEXPORT ULONG_PTR _LOCAL_COPY_USER_PROBE_ADDRESS_;
#else
extern ULONG_PTR _LOCAL_COPY_USER_PROBE_ADDRESS_;
#endif

#else

#define MM_USER_PROBE_ADDRESS MmUserProbeAddress

#endif

#define MM_LOWEST_USER_ADDRESS (PVOID)(LONG_PTR)0x10000

#define MmGetProcedureAddress(Address) (Address)
#define MmLockPagableCodeSection(Address) MmLockPagableDataSection(Address)

#define CPSR_KERNEL_SANITIZE (NZCV_N | NZCV_Z | NZCV_C | NZCV_V | \
                              CPSR_SS | \
                              DAIF_INT)

#define CPSR_USER_SANITIZE   (NZCV_N | NZCV_Z | NZCV_C | NZCV_V | \
                              CPSR_SS)

#define CPSR_USER_SANITIZE32 (NZCV_N | NZCV_Z | NZCV_C | NZCV_V | \
                              CPSR_SS | CPSRM_AA32 | CPSRM_T | CPSR_IT_MASK)

__forceinline
ULONG
SANITIZE_CPSR(ULONG Cpsr, MODE mode)
{
    return ((mode == KernelMode) ?
            ((Cpsr & CPSR_KERNEL_SANITIZE) | CPSRM_EL1t | DAIF_FIQ) :
            ((Cpsr & CPSRM_AA32) ?
             ((Cpsr & CPSR_USER_SANITIZE32) | CPSRM_EL0t | DAIF_FIQ) :
             ((Cpsr & CPSR_USER_SANITIZE) | CPSRM_EL0t | DAIF_FIQ)));
}

__forceinline
ULONG64
SANITIZE_DEBUG_ADDR(ULONG64 DebugReg, MODE mode)
{
    return ((mode == KernelMode) ?
            (DebugReg) :
            (((PVOID)(DebugReg) <= MM_HIGHEST_USER_ADDRESS) ?
             (DebugReg) :
             (0)));
}

__forceinline
ULONG
SANITIZE_DEBUG_CTRL(ULONG DebugReg, MODE mode)
{
    return ((mode == KernelMode) ?
            (DebugReg) :
            ((DebugReg & ~(ARM64_DBGBCR_SECURITY_BITS | ARM64_DBGBCR_PRIVILEGE_BITS)) |
                          (ARM64_DBGBCR_ANY_SECURE | ARM64_DBGBCR_USER_ONLY)));
}

#define INITIAL_KERNEL_CPSR (CPSRM_EL1t | DAIF_FIQ | DAIF_INT | DAIF_ABORT)

#define SYSCALL_PSR         (CPSRM_EL0t)

#if defined(_M_ARM64) && !defined(RC_INVOKED)  && !defined(MIDL_PASS)

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExInterlockedIncrementLong)      // Use InterlockedIncrement
#pragma deprecated(ExInterlockedDecrementLong)      // Use InterlockedDecrement
#pragma deprecated(ExInterlockedExchangeUlong)      // Use InterlockedExchange
#endif

#define RESULT_ZERO 0
#define RESULT_NEGATIVE 1
#define RESULT_POSITIVE 2

typedef enum _INTERLOCKED_RESULT {
    ResultNegative = RESULT_NEGATIVE,
    ResultZero = RESULT_ZERO,
    ResultPositive = RESULT_POSITIVE
} INTERLOCKED_RESULT;

#define ExInterlockedDecrementLong(Addend, Lock)                            \
    _ExInterlockedDecrementLong(Addend)

_Post_satisfies_(return >= 0 && return <= 2)
__forceinline
LONG
_ExInterlockedDecrementLong (
    _Inout_ _Interlocked_operand_ PLONG Addend)
{
    LONG Result;

    Result = InterlockedDecrement(Addend);
    if (Result < 0) {
        return ResultNegative;

    } else if (Result > 0) {
        return ResultPositive;

    } else {
        return ResultZero;
    }
}

#define ExInterlockedIncrementLong(Addend, Lock)                            \
    _ExInterlockedIncrementLong(Addend)

_Post_satisfies_(return >= 0 && return <= 2)
__forceinline
LONG
_ExInterlockedIncrementLong (
    _Inout_ _Interlocked_operand_ PLONG Addend)
{
    LONG Result;

    Result = InterlockedIncrement(Addend);
    if (Result < 0) {
        return ResultNegative;

    } else if (Result > 0) {
        return ResultPositive;

    } else {
        return ResultZero;
    }
}

#define ExInterlockedExchangeUlong(Target, Value, Lock)                     \
    _ExInterlockedExchangeUlong(Target, Value)

__forceinline
ULONG
_ExInterlockedExchangeUlong (
    _Inout_ _Interlocked_operand_ PULONG Target,
    _In_ ULONG Value)
{
    return (ULONG)InterlockedExchange((PLONG)Target, (LONG)Value);
}

#endif // defined(_M_ARM64) && !defined(RC_INVOKED)  && !defined(MIDL_PASS)


#define ARM64_PCR_RESERVED_MASK 0xFFF
#define KIPCR() ((ULONG_PTR)(_ReadStatusReg(ARM64_TPIDR_EL1)) & ~ARM64_PCR_RESERVED_MASK)

#if !defined(MIDL_PASS) && defined(_M_ARM64)

CFORCEINLINE
PKPCR
KeGetPcr (
    VOID)
{
    return (PKPCR)__getReg(18);
}

CFORCEINLINE
PKPRCB
KeGetCurrentPrcb (
    VOID)
{
    PKPRCB Prcb;

    Prcb = (PKPRCB)((ULONG_PTR)__getReg(18) + 0x980);
    return Prcb;
}

#if (NTDDI_VERSION < NTDDI_WIN7) || !defined(NT_PROCESSOR_GROUPS)

__forceinline
ULONG
KeGetCurrentProcessorNumber (
    VOID)
{
    return (ULONG)__readx18byte(0x980);
}

#endif

CFORCEINLINE
ULONG
KeGetCurrentProcessorIndex (
    VOID)
{
    return __readx18dword(0x9a4);
}

NTKERNELAPI
PKPRCB
KeQueryPrcbAddress (
    _In_ ULONG Number);

#endif // !defined(MIDL_PASS) && defined(_M_ARM64)

#if !defined(_CROSS_PLATFORM_)

CFORCEINLINE
VOID
KeMemoryBarrier (
    VOID)
{
    _ReadWriteBarrier();
    MemoryBarrier();
}

#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()

ULONG64
ReadTimeStampCounter (
    VOID);

#else

#define KeMemoryBarrier()
#define KeMemoryBarrierWithoutFence()

#endif

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_When_(return>=0, _Kernel_float_saved_)
_At_(*FloatSave, _When_(return>=0, _Kernel_acquires_resource_(FloatState)))
__forceinline
NTSTATUS
KeSaveFloatingPointState (
    _Out_ PKFLOATING_SAVE FloatSave)
#pragma warning (suppress:28104 28161 6001 6101) // PFD can't recognize the implementation
{
    UNREFERENCED_PARAMETER(FloatSave);
    return STATUS_SUCCESS;
}

_Success_(1)
_IRQL_requires_max_(DISPATCH_LEVEL)
_Kernel_float_restored_
_At_(*FloatSave, _Kernel_requires_resource_held_(FloatState) _Kernel_releases_resource_(FloatState))
__forceinline
NTSTATUS
KeRestoreFloatingPointState (
    _In_ PKFLOATING_SAVE FloatSave)
#pragma warning (suppress:28103 28162) // PFD can't recognize the implementation
{
    UNREFERENCED_PARAMETER(FloatSave);
    return STATUS_SUCCESS;
}

_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_saves_
NTHALAPI
KIRQL
KeGetCurrentIrql (
    VOID);

_IRQL_requires_max_(HIGH_LEVEL)
NTHALAPI
VOID
KfLowerIrql (
    _In_ _IRQL_restores_ _Notliteral_ KIRQL NewIrql);

#define KeLowerIrql(a) KfLowerIrql(a)
#define KeRaiseIrql(a,b) *(b) = KfRaiseIrql(a)

NTHALAPI
KIRQL
_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_raises_(NewIrql)
_IRQL_saves_
KfRaiseIrql (
    _In_ KIRQL NewIrql);

_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
__forceinline
KIRQL
KeRaiseIrqlToDpcLevel (
    VOID)
{
    return KfRaiseIrql(DISPATCH_LEVEL);
}

_IRQL_saves_
_IRQL_raises_(12)
__forceinline
KIRQL
KeRaiseIrqlToSynchLevel (
    VOID)
{
    return KfRaiseIrql(12);
}

VOID
KeCompactServiceTable (
    _Inout_ PVOID Table,
    _In_ PVOID Arguments,
    _In_ ULONG Limit,
    _In_ BOOLEAN Win32k);

VOID
KiLockServiceTable (
    _Inout_ PVOID Table,
    _In_ PVOID Arguments,
    _In_ ULONG limit,
    _In_ BOOLEAN Win32k);

__forceinline
PKARM64_VFP_STATE
KiGetVfpStatePointer(
    _In_ PKTRAP_FRAME TrapFrame
    )
{
    if (TrapFrame->VfpState == NULL) {
        NT_ASSERT(TrapFrame->ExceptionActive == KEXCEPTION_ACTIVE_SERVICE_FRAME);

        TrapFrame->VfpState = (PKARM64_VFP_STATE)(TrapFrame + 1);
        RtlZeroMemory(TrapFrame->VfpState, sizeof(*TrapFrame->VfpState));
    }
    return TrapFrame->VfpState;
}

typedef struct _TRAPFRAME_LOG_ENTRY {
    ULONG_PTR Thread;
    UCHAR CpuNumber;
    UCHAR TrapType;
    USHORT Padding;
    ULONG Cpsr;
    ULONG_PTR X0;
    ULONG_PTR X1;
    ULONG_PTR X2;
    ULONG_PTR X3;
    ULONG_PTR X4;
    ULONG_PTR X5;
    ULONG_PTR X6;
    ULONG_PTR X7;
    ULONG_PTR Fp;
    ULONG_PTR Lr;
    ULONG_PTR Sp;
    ULONG_PTR Pc;
    ULONG_PTR Reserved1;
    ULONG_PTR Reserved2;
} TRAPFRAME_LOG_ENTRY, *PTRAPFRAME_LOG_ENTRY;

#define TRAP_TYPE_INTERRUPT 1
#define TRAP_TYPE_SYSCALL 2
#define TRAP_TYPE_UNDEFINED 3
#define TRAP_TYPE_DATA_ABORT 4
#define TRAP_TYPE_PREFETCH_ABORT 5
#define TRAP_TYPE_RESET 6
#define TRAP_TYPE_FIQ 7

#define IMAGE_FILE_MACHINE_NATIVE   0xaa64

char
InterlockedAnd8 (
    _Inout_ char volatile *Destination,
    _In_ char Value);

char
InterlockedOr8 (
    _Inout_ char volatile *Destination,
    _In_ char Value);

#endif // _ARM64_



#ifndef _NTLSA_IFS_

#ifndef _NTLSA_AUDIT_
#define _NTLSA_AUDIT_

typedef enum _SE_ADT_PARAMETER_TYPE {

    SeAdtParmTypeNone = 0,
    SeAdtParmTypeString,
    SeAdtParmTypeFileSpec,
    SeAdtParmTypeUlong,
    SeAdtParmTypeSid,
    SeAdtParmTypeLogonId,
    SeAdtParmTypeNoLogonId,
    SeAdtParmTypeAccessMask,
    SeAdtParmTypePrivs,
    SeAdtParmTypeObjectTypes,
    SeAdtParmTypeHexUlong,
    SeAdtParmTypePtr,
    SeAdtParmTypeTime,
    SeAdtParmTypeGuid,
    SeAdtParmTypeLuid,
    SeAdtParmTypeHexInt64,
    SeAdtParmTypeStringList,
    SeAdtParmTypeSidList,
    SeAdtParmTypeDuration,
    SeAdtParmTypeUserAccountControl,
    SeAdtParmTypeNoUac,
    SeAdtParmTypeMessage,
    SeAdtParmTypeDateTime,
    SeAdtParmTypeSockAddr,
    SeAdtParmTypeSD,
    SeAdtParmTypeLogonHours,
    SeAdtParmTypeLogonIdNoSid,
    SeAdtParmTypeUlongNoConv,
    SeAdtParmTypeSockAddrNoPort,
    SeAdtParmTypeAccessReason,
    SeAdtParmTypeStagingReason,
    SeAdtParmTypeResourceAttribute,
    SeAdtParmTypeClaims,
    SeAdtParmTypeLogonIdAsSid,
    SeAdtParmTypeMultiSzString,
    SeAdtParmTypeLogonIdEx,
} SE_ADT_PARAMETER_TYPE, *PSE_ADT_PARAMETER_TYPE;

typedef struct _SE_ADT_OBJECT_TYPE {
    GUID ObjectType;
    USHORT Flags;
#define SE_ADT_OBJECT_ONLY 0x1
    USHORT Level;
    ACCESS_MASK AccessMask;
} SE_ADT_OBJECT_TYPE, *PSE_ADT_OBJECT_TYPE;

typedef struct _SE_ADT_PARAMETER_ARRAY_ENTRY
{
    SE_ADT_PARAMETER_TYPE Type;
    ULONG Length;
    ULONG_PTR Data[2];
    PVOID Address;
} SE_ADT_PARAMETER_ARRAY_ENTRY, *PSE_ADT_PARAMETER_ARRAY_ENTRY;

typedef struct _SE_ADT_ACCESS_REASON
{
    ACCESS_MASK AccessMask;
    ULONG  AccessReasons[32];
    ULONG  ObjectTypeIndex;
    ULONG AccessGranted;
    PSECURITY_DESCRIPTOR SecurityDescriptor;
} SE_ADT_ACCESS_REASON, *PSE_ADT_ACCESS_REASON;

typedef struct _SE_ADT_CLAIMS
{
    ULONG Length;
    PCLAIMS_BLOB Claims;
} SE_ADT_CLAIMS, *PSE_ADT_CLAIMS;

#define SE_MAX_AUDIT_PARAMETERS 32
#define SE_MAX_GENERIC_AUDIT_PARAMETERS 28

typedef struct _SE_ADT_PARAMETER_ARRAY
{
    ULONG CategoryId;
    ULONG AuditId;
    ULONG ParameterCount;
    ULONG Length;
    USHORT FlatSubCategoryId;
    USHORT Type;
    ULONG Flags;
    SE_ADT_PARAMETER_ARRAY_ENTRY Parameters[ SE_MAX_AUDIT_PARAMETERS ];
} SE_ADT_PARAMETER_ARRAY, *PSE_ADT_PARAMETER_ARRAY;

#define SE_ADT_PARAMETERS_SELF_RELATIVE     0x00000001
#define SE_ADT_PARAMETERS_SEND_TO_LSA       0x00000002
#define SE_ADT_PARAMETER_EXTENSIBLE_AUDIT   0x00000004
#define SE_ADT_PARAMETER_GENERIC_AUDIT      0x00000008
#define SE_ADT_PARAMETER_WRITE_SYNCHRONOUS  0x00000010

#define LSAP_SE_ADT_PARAMETER_ARRAY_TRUE_SIZE(AuditParameters)    \
     ( sizeof(SE_ADT_PARAMETER_ARRAY) -                           \
       sizeof(SE_ADT_PARAMETER_ARRAY_ENTRY) *                     \
       (SE_MAX_AUDIT_PARAMETERS - AuditParameters->ParameterCount) )

#endif // _NTLSA_AUDIT_

#endif // _NTLSA_IFS_

typedef enum _KAPC_ENVIRONMENT
{
    OriginalApcEnvironment,
    AttachedApcEnvironment,
    CurrentApcEnvironment,
    InsertApcEnvironment
} KAPC_ENVIRONMENT;

typedef
_IRQL_requires_same_
_Function_class_(KENUM_ROUTINE)
VOID
NTAPI
KENUM_ROUTINE (
    _In_reads_(_Inexpressible_(Length)) PVOID Data,
    _In_ ULONG Length,
    _In_ PVOID Context);
typedef KENUM_ROUTINE *PKENUM_ROUTINE;

NTKERNELAPI
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
VOID
KeEnumerateQueueApc (
    _Inout_ PKTHREAD Thread,
    _In_ PKENUM_ROUTINE CallbackRoutine,
    _In_ PVOID Context,
    _In_opt_ KPROCESSOR_MODE *ApcMode
    );

NTKERNELAPI
_Must_inspect_result_
_IRQL_requires_max_(HIGH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL + 1)
_IRQL_requires_same_
BOOLEAN
KeTryToInsertQueueApc (
    _Inout_ PRKAPC Apc,
    _In_opt_ PVOID SystemArgument1,
    _In_opt_ PVOID SystemArgument2
    );

ULONG
KeIsApcRunningThread (
    _In_ PKTHREAD Thread
    );

NTKERNELAPI
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
VOID
KeEnumerateProcessorDpcs (
    _In_ ULONG ProcessorNumber,
    _In_ PKENUM_ROUTINE CallbackRoutine,
    _In_ PVOID Context,
    _In_opt_ PULONG DpcType
    );

extern PLOADER_PARAMETER_BLOCK KeLoaderBlock;

#define THREAD_WAIT_OBJECTS 3

#if (NTDDI_VERSION < NTDDI_WIN7) || defined(_X86_) || !defined(NT_PROCESSOR_GROUPS)
#define SINGLE_GROUP_LEGACY_API 1
#endif

#if defined(_X86_) || defined(_AMD64_)
#define PAUSE_PROCESSOR YieldProcessor();
#elif defined(_ARM_) || defined(_ARM64_)
#define PAUSE_PROCESSOR __yield();
#endif

#define AFFINITY_MASK(n) ((ULONG_PTR)1 << (n))

typedef struct _KAPC_STATE
{
    LIST_ENTRY ApcListHead[MaximumMode];
    struct _KPROCESS *Process;
    union
    {
        UCHAR InProgressFlags;
        struct
        {
            BOOLEAN KernelApcInProgress : 1;
            BOOLEAN SpecialApcInProgress : 1;
        };
    };
    BOOLEAN KernelApcPending;
    BOOLEAN UserApcPending;
} KAPC_STATE, *PKAPC_STATE, *PRKAPC_STATE;

#define KE_KERNEL_APC_IN_PROGRESS 0x1
#define KE_SPECIAL_APC_IN_PROGRESS 0x2

typedef struct _KWAIT_BLOCK
{
    LIST_ENTRY WaitListEntry;
    UCHAR WaitType;
    volatile UCHAR BlockState;
    USHORT WaitKey;
#if defined(_WIN64)
    LONG SpareLong;
#endif
    union
    {
        struct _KTHREAD *Thread;
        struct _KQUEUE *NotificationQueue;
    };
    PVOID Object;
    PVOID SparePtr;
} KWAIT_BLOCK, *PKWAIT_BLOCK, *PRKWAIT_BLOCK;

#define ASSERT_DEVICE_QUEUE(E) NT_ASSERT((E)->Type == DeviceQueueObject)

typedef struct _KDEVICE_QUEUE
{
    CSHORT Type;
    CSHORT Size;
    LIST_ENTRY DeviceListHead;
    KSPIN_LOCK Lock;
#if defined(_AMD64_)
    union {
        BOOLEAN Busy;
        struct {
            LONG64 Reserved : 8;
            LONG64 Hint : 56;
        };
    };
#else
    BOOLEAN Busy;
#endif
} KDEVICE_QUEUE, *PKDEVICE_QUEUE, *PRKDEVICE_QUEUE;

typedef struct _KDEVICE_QUEUE_ENTRY
{
    LIST_ENTRY DeviceListEntry;
    ULONG SortKey;
    BOOLEAN Inserted;
} KDEVICE_QUEUE_ENTRY, *PKDEVICE_QUEUE_ENTRY, *PRKDEVICE_QUEUE_ENTRY;

typedef struct _KINTERRUPT *PKINTERRUPT, *PRKINTERRUPT;

typedef struct _KQUEUE
{
    DISPATCHER_HEADER Header;
    LIST_ENTRY EntryListHead;       // Object lock
    volatile ULONG CurrentCount;    // Interlocked
    ULONG MaximumCount;
    LIST_ENTRY ThreadListHead;      // Object lock
} KQUEUE, *PKQUEUE, *PRKQUEUE;

typedef struct _KPRIQUEUE {
    DISPATCHER_HEADER Header;
    LIST_ENTRY EntryListHead[MAXIMUM_PRIORITY];
    volatile LONG CurrentCount[MAXIMUM_PRIORITY];
    ULONG MaximumCount;
    LIST_ENTRY ThreadListHead;
} KPRIQUEUE, *PKPRIQUEUE;

typedef struct _KSEMAPHORE {
    DISPATCHER_HEADER Header;
    LONG Limit;
} KSEMAPHORE, *PKSEMAPHORE, *PRKSEMAPHORE;

#define KSEMAPHORE_ACTUAL_LENGTH                                             \
    (FIELD_OFFSET(KSEMAPHORE, Limit) + sizeof(LONG))


_When_(Wait==0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(Wait==1, _IRQL_requires_max_(APC_LEVEL))
_When_(Wait==1, __drv_reportError("Caution: 'Wait' argument does not provide"
                                      " any synchronization guarantees, only a hint"
                                      " to the system that the thread will immediately"
                                      " issue a wait operation"))

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
LONG
KeReadStateMutex (
    _In_ PRKMUTEX Mutex
    );

_When_(Wait==0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(Wait==1, _IRQL_requires_max_(APC_LEVEL))
_When_(Wait==1, __drv_reportError("Caution: 'Wait' argument does not provide"
                                      " any synchronization guarantees, only a hint"
                                      " to the system that the thread will immediately"
                                      " issue a wait operation"))
NTKERNELAPI
LONG
KeReleaseMutex (
    _Inout_ PRKMUTEX Mutex,
    _In_ BOOLEAN Wait
    );


#define KI_PRIQUEUE_WAIT_NEXT   0x00000001UL
#define KI_PRIQUEUE_THREAD_AVAILABLE  0x00000002UL

NTKERNELAPI
VOID
KeInitializePriQueue (
    _Out_ PKPRIQUEUE Queue,
    _In_ ULONG Count
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
KeInsertPriQueue (
    _Inout_ PKPRIQUEUE Queue,
    _Inout_ PLIST_ENTRY Entry,
    _In_ KPRIORITY Priority,
    _In_ KPRIORITY Increment,
    _In_ ULONG Flags
    );

_When_((Timeout==NULL || Timeout->QuadPart!=0), _IRQL_requires_max_(APC_LEVEL))
_When_((Timeout!=NULL && Timeout->QuadPart==0), _IRQL_requires_max_(DISPATCH_LEVEL))
NTKERNELAPI
PLIST_ENTRY
KeRemovePriQueue (
    _Inout_ PKPRIQUEUE Queue,
    _In_ KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

_IRQL_requires_same_
VOID
KeSetMaximumCountPriQueue (
    _Inout_ PKPRIQUEUE Queue,
    _In_ ULONG NewMaximumCount
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
KeDelayExecutionThread (
    _In_ KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_ PLARGE_INTEGER Interval
    );

VOID
NTAPI
KeInitializeInterlockedAffinityEx (
    _Out_ PKAFFINITY_EX Affinity)
{
    __debugbreak();
}

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
KPRIORITY
KeQueryPriorityThread (
    _In_ PKTHREAD Thread
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
ULONG
KeQueryRuntimeThread (
    _In_ PKTHREAD Thread,
    _Out_ PULONG UserTime
    );

_IRQL_requires_max_(APC_LEVEL)
_IRQL_requires_same_
ULONG64
KeQueryTotalCycleTimeThread (
    _Inout_ PKTHREAD Thread,
    _Out_ PULONG64 CycleTimeStamp
    );


#if defined(SINGLE_GROUP_LEGACY_API)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
KeRevertToUserAffinityThread (
    VOID
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
KeSetSystemAffinityThread (
    _In_ KAFFINITY Affinity
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
KeRevertToUserAffinityThreadEx (
    _In_ KAFFINITY Affinity
    );
#endif

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
KeSetSystemGroupAffinityThread (
    _In_ PGROUP_AFFINITY Affinity,
    _Out_opt_ PGROUP_AFFINITY PreviousAffinity
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
KeRevertToUserGroupAffinityThread (
    _In_ PGROUP_AFFINITY PreviousAffinity
    );

#if defined(SINGLE_GROUP_LEGACY_API)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
KAFFINITY
KeSetSystemAffinityThreadEx (
    _In_ KAFFINITY Affinity
    );
#endif

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
LONG
KeSetBasePriorityThread (
    _Inout_ PKTHREAD Thread,
    _In_ LONG Increment
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
BOOLEAN
KeSetKernelStackSwapEnable (
    _In_ BOOLEAN Enable
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
KPRIORITY
KeSetPriorityThread (
    _Inout_ PKTHREAD Thread,
    _In_ KPRIORITY Priority
    );

_Acquires_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
KeEnterCriticalRegion (
    VOID
    );

_Releases_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
KeLeaveCriticalRegion (
    VOID
    );

_Acquires_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
KeEnterGuardedRegion (
    VOID
    );

_Releases_lock_(_Global_critical_region_)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
KeLeaveGuardedRegion (
    VOID
    );

#define KeWaitForMutexObject KeWaitForSingleObject


#if ((defined(_X86_) && (defined(_WDM_INCLUDED_) || defined(WIN9X_COMPAT_SPINLOCK))) || \
     ((NTDDI_VERSION > NTDDI_WIN7) && !defined(WIN9X_COMPAT_SPINLOCK) && \
      (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_) || defined(_BLDR_))))

#else

CFORCEINLINE
VOID
NTAPI
KzInitializeSpinLock (
    _Out_ PKSPIN_LOCK SpinLock)
{
    *SpinLock = 0;
}

#define KeInitializeSpinLock KzInitializeSpinLock

#endif

#if defined(_X86_)

#define KeAcquireSpinLockAtDpcLevel(a) KefAcquireSpinLockAtDpcLevel(a)
#define KeReleaseSpinLockFromDpcLevel(a) KefReleaseSpinLockFromDpcLevel(a)


#define KeAcquireSpinLock(a,b) *(b) = KfAcquireSpinLock(a)
#define KeReleaseSpinLock(a,b) KfReleaseSpinLock(a,b)

#else

#define KeAcquireSpinLock(SpinLock, OldIrql) \
    *(OldIrql) = KeAcquireSpinLockRaiseToDpc(SpinLock)

_Requires_lock_not_held_(*SpinLock)
_Acquires_lock_(*SpinLock)
_IRQL_raises_(SYNCH_LEVEL)
_IRQL_saves_
NTKERNELAPI
KIRQL
KeAcquireSpinLockRaiseToSynch (
    _Inout_ PKSPIN_LOCK SpinLock
    );

#endif

typedef struct _KDPC_WATCHDOG_INFORMATION {
    ULONG DpcTimeLimit;
    ULONG DpcTimeCount;
    ULONG DpcWatchdogLimit;
    ULONG DpcWatchdogCount;
    ULONG Reserved;
} KDPC_WATCHDOG_INFORMATION, *PKDPC_WATCHDOG_INFORMATION;





typedef struct _KBUGCHECK_SECONDARY_DUMP_DATA {
    IN PVOID InBuffer;
    IN ULONG InBufferLength;
    IN ULONG MaximumAllowed;
    OUT GUID Guid;
    OUT PVOID OutBuffer;
    OUT ULONG OutBufferLength;
} KBUGCHECK_SECONDARY_DUMP_DATA, *PKBUGCHECK_SECONDARY_DUMP_DATA;

typedef struct _KBUGCHECK_SECONDARY_DUMP_DATA_EX {
    _In_    PVOID InBuffer;
    _In_    ULONG InBufferLength;
    _In_    ULONG MaximumAllowed;
    _Out_   GUID  Guid;
    _Inout_ PVOID OutBuffer;
    _Inout_ ULONG OutBufferLength;
    _Inout_ PVOID Context;
    _Inout_ ULONG Flags;         // KB_SECONDARY_DATA_FLAG_xxx
    _In_    ULONG DumpType;      // DUMP_TYPE defined in ntiodump.h
    _In_    ULONG BugCheckCode;
    _In_    ULONG_PTR BugCheckParameter1;
    _In_    ULONG_PTR BugCheckParameter2;
    _In_    ULONG_PTR BugCheckParameter3;
    _In_    ULONG_PTR BugCheckParameter4;
} KBUGCHECK_SECONDARY_DUMP_DATA_EX, *PKBUGCHECK_SECONDARY_DUMP_DATA_EX;

#define KB_SECONDARY_DATA_FLAG_ADDITIONAL_DATA      0x00000001
#define KB_SECONDARY_DATA_FLAG_NO_DEVICE_ACCESS     0x00000002

typedef enum _KBUGCHECK_DUMP_IO_TYPE {
    KbDumpIoInvalid,
    KbDumpIoHeader,
    KbDumpIoBody,
    KbDumpIoSecondaryData,
    KbDumpIoComplete
} KBUGCHECK_DUMP_IO_TYPE;

typedef struct _KBUGCHECK_DUMP_IO {
    IN ULONG64 Offset;
    IN PVOID Buffer;
    IN ULONG BufferLength;
    IN KBUGCHECK_DUMP_IO_TYPE Type;
} KBUGCHECK_DUMP_IO, *PKBUGCHECK_DUMP_IO;

#define KB_ADD_PAGES_FLAG_VIRTUAL_ADDRESS           0x00000001UL
#define KB_ADD_PAGES_FLAG_PHYSICAL_ADDRESS          0x00000002UL
#define KB_ADD_PAGES_FLAG_ADDITIONAL_RANGES_EXIST   0x80000000UL

typedef struct _KBUGCHECK_ADD_PAGES {
    _Inout_ PVOID Context;      // Private context for callback use
    _Inout_ ULONG Flags;        // Zero initialized on input
    _In_ ULONG BugCheckCode;
    _Out_ ULONG_PTR Address;
    _Out_ ULONG_PTR Count;
} KBUGCHECK_ADD_PAGES, *PKBUGCHECK_ADD_PAGES;

#define KB_REMOVE_PAGES_FLAG_VIRTUAL_ADDRESS           0x00000001UL
#define KB_REMOVE_PAGES_FLAG_PHYSICAL_ADDRESS          0x00000002UL
#define KB_REMOVE_PAGES_FLAG_ADDITIONAL_RANGES_EXIST   0x80000000UL

typedef struct _KBUGCHECK_REMOVE_PAGES {
    _Inout_ PVOID Context;
    _Inout_ ULONG Flags;
    _In_ ULONG BugCheckCode;
    _Out_ ULONG_PTR Address;
    _Out_ ULONG_PTR Count;
} KBUGCHECK_REMOVE_PAGES, *PKBUGCHECK_REMOVE_PAGES;

#define EXCEPTION_DIVIDED_BY_ZERO       0
#define EXCEPTION_DEBUG                 1
#define EXCEPTION_NMI                   2
#define EXCEPTION_INT3                  3
#define EXCEPTION_BOUND_CHECK           5
#define EXCEPTION_INVALID_OPCODE        6
#define EXCEPTION_NPX_NOT_AVAILABLE     7
#define EXCEPTION_DOUBLE_FAULT          8
#define EXCEPTION_NPX_OVERRUN           9
#define EXCEPTION_INVALID_TSS           0x0A
#define EXCEPTION_SEGMENT_NOT_PRESENT   0x0B
#define EXCEPTION_STACK_FAULT           0x0C
#define EXCEPTION_GP_FAULT              0x0D
#define EXCEPTION_RESERVED_TRAP         0x0F
#define EXCEPTION_NPX_ERROR             0x010
#define EXCEPTION_ALIGNMENT_CHECK       0x011






#define IOMMU_FLUSH_ENTIRE MAXULONG

typedef struct _KTB_FLUSH_VA {
    union {
        struct {
#define KTB_FLUSH_RUN_MAXIMUM  (PAGE_SIZE / 2 - 1)
            ULONG_PTR NumberOfEntries : 11;
            ULONG_PTR PageSize : 1;
        };
        PVOID Va;
        ULONG_PTR VaLong;
    } u1;
} KTB_FLUSH_VA, *PKTB_FLUSH_VA;



#define WIN32K_SERVICE_INDEX 1


#if !defined(_AMD64_) && !defined(_ARM64_)

NTKERNELAPI
ULONGLONG
KeQueryInterruptTime (
    VOID
    );

NTKERNELAPI
VOID
KeQuerySystemTime (
    _Out_ PLARGE_INTEGER CurrentTime);

#endif // !_AMD64_

NTKERNELAPI
ULONG
KeGetRecommendedSharedDataAlignment (
    VOID
    );

NTKERNELAPI
USHORT
KeGetProcessorNodeNumber (
    _In_ PKPRCB Prcb);

#define SECONDARY_INTERRUPT_FLAGS_NONE (0x0)


typedef enum _FIRMWARE_REENTRY {
    HalHaltRoutine,
    HalPowerDownRoutine,
    HalRestartRoutine,
    HalRebootRoutine,
    HalInteractiveModeRoutine,
    HalMaximumRoutine
} FIRMWARE_REENTRY, *PFIRMWARE_REENTRY;

#define INVALID_APIC_ID ((ULONG)-1)
#define INVALID_NODE_NUMBER ((USHORT)-1)



#define KE_PROCESSOR_CHANGE_ADD_EXISTING 1

#define INVALID_PROCESSOR_INDEX     0xffffffff


typedef struct _XSTATE_SAVE
{
#if defined(_AMD64_)
    struct _XSTATE_SAVE* Prev;
    struct _KTHREAD* Thread;
    UCHAR Level;
    XSTATE_CONTEXT XStateContext;
#elif defined(_ARM_) || defined(_ARM64_)
    ULONG Dummy;
#elif defined(_X86_)
    union {
        struct {
            LONG64 Reserved1;
            ULONG Reserved2;
            struct _XSTATE_SAVE* Prev;
            PXSAVE_AREA Reserved3;
            struct _KTHREAD* Thread;
            PVOID Reserved4;
            UCHAR Level;
        };
        XSTATE_CONTEXT XStateContext;
    };
#endif
} XSTATE_SAVE, *PXSTATE_SAVE;



#if !defined(XBOX_SYSTEMOS)

NTSTATUS
KeIntSteerPeriodic (
    _In_ PKAFFINITY_EX SteeringMask,
    _In_ ULONG NumProcs
    );

NTSTATUS
KeIntSteerSnapPerf(
    _Out_ PULONG IsrDpcLoadPercent,
    _Out_ PULONG64 CurrentTime
    );

#endif

NTSTATUS
KeLowPowerEpochCallback (
    _In_ LPCGUID SettingGuid,
    _In_bytecount_ (ValueLength) PULONG NewValue,
    _In_ ULONG ValueLength,
    _In_ PVOID Context
    );

typedef struct _EXT_SET_PARAMETERS_V0 {
    ULONG Version;
    ULONG Reserved;
    LONGLONG NoWakeTolerance;
} EXT_SET_PARAMETERS, *PEXT_SET_PARAMETERS;

typedef EXT_SET_PARAMETERS KT2_SET_PARAMETERS, *PKT2_SET_PARAMETERS;


#ifndef _TRACEHANDLE_DEFINED
#define _TRACEHANDLE_DEFINED
typedef ULONG64 TRACEHANDLE, *PTRACEHANDLE;
#endif

#ifdef RUN_WPP

NTKERNELAPI
_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
WmiTraceMessage (
    _In_ TRACEHANDLE LoggerHandle,
    _In_ ULONG MessageFlags,
    _In_ LPCGUID MessageGuid,
    _In_ USHORT MessageNumber,
    ...
    );

NTKERNELAPI
_IRQL_requires_max_(HIGH_LEVEL)
NTSTATUS
WmiTraceMessageVa (
    _In_ TRACEHANDLE LoggerHandle,
    _In_ ULONG MessageFlags,
    _In_ LPCGUID MessageGuid,
    _In_ USHORT MessageNumber,
    _In_ va_list MessageArgList
    );

#endif // #ifdef RUN_WPP

#ifndef TRACE_INFORMATION_CLASS_DEFINE

typedef struct _ETW_TRACE_SESSION_SETTINGS {
    ULONG Version;
    ULONG BufferSize;
    ULONG MinimumBuffers;
    ULONG MaximumBuffers;
    ULONG LoggerMode;
    ULONG FlushTimer;
    ULONG FlushThreshold;
    ULONG ClockType;
} ETW_TRACE_SESSION_SETTINGS, *PETW_TRACE_SESSION_SETTINGS;

typedef enum _TRACE_INFORMATION_CLASS {
    TraceIdClass,
    TraceHandleClass,
    TraceEnableFlagsClass,
    TraceEnableLevelClass,
    GlobalLoggerHandleClass,
    EventLoggerHandleClass,
    AllLoggerHandlesClass,
    TraceHandleByNameClass,
    LoggerEventsLostClass,
    TraceSessionSettingsClass,
    LoggerEventsLoggedClass,
    DiskIoNotifyRoutinesClass,
    TraceInformationClassReserved1,
    AllPossibleNotifyRoutinesClass = TraceInformationClassReserved1,
    FltIoNotifyRoutinesClass,
    TraceInformationClassReserved2,
    WdfNotifyRoutinesClass,
    MaxTraceInformationClass
} TRACE_INFORMATION_CLASS;

NTKERNELAPI
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
WmiQueryTraceInformation (
    _In_ TRACE_INFORMATION_CLASS TraceInformationClass,
    _Out_writes_bytes_(TraceInformationLength) PVOID TraceInformation,
    _In_ ULONG TraceInformationLength,
    _Out_opt_ PULONG RequiredLength,
    _In_opt_ PVOID Buffer
    );

#define TRACE_INFORMATION_CLASS_DEFINE
#endif // TRACE_INFOPRMATION_CLASS_DEFINE


#ifndef _ETW_KM_
#define _ETW_KM_
#endif

#include <evntprov.h>

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
_IRQL_requires_same_
VOID
NTAPI
ETWENABLECALLBACK (
    _In_ LPCGUID SourceId,
    _In_ ULONG ControlCode,
    _In_ UCHAR Level,
    _In_ ULONGLONG MatchAnyKeyword,
    _In_ ULONGLONG MatchAllKeyword,
    _In_opt_ PEVENT_FILTER_DESCRIPTOR FilterData,
    _Inout_opt_ PVOID CallbackContext
    );

typedef ETWENABLECALLBACK *PETWENABLECALLBACK;

NTKERNELAPI
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS
EtwActivityIdControlKernel (
    _In_ ULONG ControlCode,
    _Inout_ LPCGUID *ActivityId
    );

#define EVENT_WRITE_FLAG_NO_FAULTING 0x00000001

NTKERNELAPI
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
EtwWriteKMSecurityEvent (
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_opt_ LPCGUID ActivityId,
    _In_ ULONG UserDataCount,
    _In_opt_ PEVENT_DATA_DESCRIPTOR UserData
    );

typedef _Enum_is_bitflag_ enum _POOL_TYPE {
    NonPagedPool,
    NonPagedPoolExecute = NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed = NonPagedPool + 2,
    DontUseThisType,
    NonPagedPoolCacheAligned = NonPagedPool + 4,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS = NonPagedPool + 6,
    MaxPoolType,
    NonPagedPoolBase = 0,
    NonPagedPoolBaseMustSucceed = NonPagedPoolBase + 2,
    NonPagedPoolBaseCacheAligned = NonPagedPoolBase + 4,
    NonPagedPoolBaseCacheAlignedMustS = NonPagedPoolBase + 6,
    NonPagedPoolSession = 32,
    PagedPoolSession = NonPagedPoolSession + 1,
    NonPagedPoolMustSucceedSession = PagedPoolSession + 1,
    DontUseThisTypeSession = NonPagedPoolMustSucceedSession + 1,
    NonPagedPoolCacheAlignedSession = DontUseThisTypeSession + 1,
    PagedPoolCacheAlignedSession = NonPagedPoolCacheAlignedSession + 1,
    NonPagedPoolCacheAlignedMustSSession = PagedPoolCacheAlignedSession + 1,
    NonPagedPoolNx = 512,
    NonPagedPoolNxCacheAligned = NonPagedPoolNx + 4,
    NonPagedPoolSessionNx = NonPagedPoolNx + 32,

} _Enum_is_bitflag_ POOL_TYPE;

#define POOL_COLD_ALLOCATION 256     // Note this cannot encode into the header.

#define POOL_NX_ALLOCATION   512     // Note this cannot encode into the header.

#if (!defined(_X86_) && !defined(_AMD64_) && !defined(_NTOS_)) || defined(_PREFAST_)

#undef POOL_NX_OPTIN

#define POOL_NX_OPTIN_AUTO 1

#endif // !defined(_X86_) && !defined(_AMD64_) && !defined(_NTOSP_)

#if !POOL_NX_OPTOUT

#if POOL_NX_OPTIN_AUTO
#define NonPagedPool NonPagedPoolNx
#define NonPagedPoolCacheAligned NonPagedPoolNxCacheAligned
#elif POOL_NX_OPTIN
DECLSPEC_SELECTANY POOL_TYPE ExDefaultNonPagedPoolType = NonPagedPoolExecute;
DECLSPEC_SELECTANY ULONG ExDefaultMdlProtection = 0;
#define NonPagedPool ExDefaultNonPagedPoolType
#define NonPagedPoolCacheAligned (ExDefaultNonPagedPoolType + 4)
#endif // POOL_NX_OPTIN_AUTO

#endif // !POOL_NX_OPTOUT

#define POOL_MM_ALLOCATION 0x80000000     // Note this cannot encode into the header.

#define POOL_QUOTA_FAIL_INSTEAD_OF_RAISE 8
#define POOL_RAISE_IF_ALLOCATION_FAILURE 16

DECLSPEC_DEPRECATED_DDK                     // Use ExAllocatePoolWithTag
__drv_preferredFunction("ExAllocatePoolWithTag",
                        "No tag interferes with debugging.")
__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) == 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) != 0,
       _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
NTKERNELAPI
PVOID
ExAllocatePool (
    __drv_strictTypeMatch(__drv_typeExpr) _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes
    );

DECLSPEC_DEPRECATED_DDK                     // Use ExAllocatePoolWithQuotaTag
__drv_preferredFunction("ExAllocatePoolWithQuotaTag",
                        "No tag interferes with debugging.")
__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & POOL_QUOTA_FAIL_INSTEAD_OF_RAISE) != 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & POOL_QUOTA_FAIL_INSTEAD_OF_RAISE) == 0, _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
NTKERNELAPI
PVOID
ExAllocatePoolWithQuota (
    __drv_strictTypeMatch(__drv_typeExpr) _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes
    );

__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) == 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) != 0,
       _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
NTKERNELAPI
PVOID
NTAPI
ExAllocatePoolWithTag (
    _In_ __drv_strictTypeMatch(__drv_typeExpr) POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag
    );


__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) == 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & (NonPagedPoolMustSucceed |
                    POOL_RAISE_IF_ALLOCATION_FAILURE)) != 0,
       _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
NTKERNELAPI
PVOID
NTAPI
ExAllocatePoolWithTagPriority (
    _In_ __drv_strictTypeMatch(__drv_typeCond) POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag,
    _In_ __drv_strictTypeMatch(__drv_typeExpr) EX_POOL_PRIORITY Priority
    );

#ifndef POOL_TAGGING
#define ExAllocatePoolWithTag(a,b,c) ExAllocatePool(a,b)
#endif //POOL_TAGGING

__drv_allocatesMem(Mem)
_When_((PoolType & PagedPool) != 0, _IRQL_requires_max_(APC_LEVEL))
_When_((PoolType & PagedPool) == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_((PoolType & NonPagedPoolMustSucceed) != 0,
       __drv_reportError("Must succeed pool allocations are forbidden. "
                         "Allocation failures cause a system crash"))
_When_((PoolType & POOL_QUOTA_FAIL_INSTEAD_OF_RAISE) != 0,
       _Post_maybenull_ _Must_inspect_result_)
_When_((PoolType & POOL_QUOTA_FAIL_INSTEAD_OF_RAISE) == 0, _Post_notnull_)
_Post_writable_byte_size_(NumberOfBytes)
NTKERNELAPI
PVOID
ExAllocatePoolWithQuotaTag (
    _In_ __drv_strictTypeMatch(__drv_typeExpr) POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes,
    _In_ ULONG Tag
    );

#ifndef POOL_TAGGING
#define ExAllocatePoolWithQuotaTag(a,b,c) ExAllocatePoolWithQuota(a,b)
#endif //POOL_TAGGING

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
NTAPI
ExFreePool (
    _Pre_notnull_ __drv_freesMem(Mem) PVOID P
    );

#if defined(POOL_TAGGING)
#define ExFreePool(a) ExFreePoolWithTag (a,0)
#endif

#define PROTECTED_POOL 0x0

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExFreePoolWithTag (
    _Pre_notnull_ __drv_freesMem(Mem) PVOID P,
    _In_ ULONG Tag
    );

#ifndef POOL_TAGGING
#define ExFreePoolWithTag(a,b) ExFreePool (a)
#endif //POOL_TAGGING

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
SIZE_T
ExQueryPoolBlockSize (
    _In_ PVOID PoolBlock,
    _Out_ PBOOLEAN QuotaCharged
    );

#define FM_LOCK_BIT          0x1 // Actual lock bit, 1 = Unlocked, 0 = Locked
#define FM_LOCK_BIT_V        0x0 // Lock bit as a bit number

FORCEINLINE
VOID
ExInitializeFastMutex (
    _Out_ PFAST_MUTEX FastMutex)
{
    WriteRaw(&FastMutex->Count, FM_LOCK_BIT);
    FastMutex->Owner = NULL;
    FastMutex->Contention = 0;
    KeInitializeEvent(&FastMutex->Event, SynchronizationEvent, FALSE);
}


NTKERNELAPI
LARGE_INTEGER
ExInterlockedAddLargeInteger (
    _Inout_ PLARGE_INTEGER Addend,
    _In_ LARGE_INTEGER Increment,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock
    );

NTKERNELAPI
ULONG
FASTCALL
ExInterlockedAddUlong (
    _Inout_ PULONG Addend,
    _In_ ULONG Increment,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock
    );

#if defined(_AMD64_) || defined(_ARM_) || defined(_ARM64_)
#define ExInterlockedCompareExchange64(Destination, Exchange, Comperand, Lock) \
    InterlockedCompareExchange64(Destination, *(Exchange), *(Comperand))
#else
#define ExInterlockedCompareExchange64(Destination, Exchange, Comperand, Lock) \
    ExfInterlockedCompareExchange64(Destination, Exchange, Comperand)

NTKERNELAPI
LONGLONG
FASTCALL
ExfInterlockedCompareExchange64 (
    _Inout_ _Interlocked_operand_ LONGLONG volatile *Destination,
    _In_ PLONGLONG ExChange,
    _In_ PLONGLONG Comperand
    );

#endif

NTKERNELAPI
PLIST_ENTRY
FASTCALL
ExInterlockedInsertHeadList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PLIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock
    );

NTKERNELAPI
PLIST_ENTRY
FASTCALL
ExInterlockedInsertTailList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PLIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock
    );

NTKERNELAPI
PLIST_ENTRY
FASTCALL
ExInterlockedRemoveHeadList (
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock
    );

NTKERNELAPI
PSINGLE_LIST_ENTRY
FASTCALL
ExInterlockedPopEntryList (
    _Inout_ PSINGLE_LIST_ENTRY ListHead,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock
    );

NTKERNELAPI
PSINGLE_LIST_ENTRY
FASTCALL
ExInterlockedPushEntryList (
    _Inout_ PSINGLE_LIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PSINGLE_LIST_ENTRY ListEntry,
    _Inout_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock
    );

#if !defined(_WINBASE_)

#if defined(_WIN64) && (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_))

NTKERNELAPI
VOID
InitializeSListHead (
    _Out_ PSLIST_HEADER SListHead
    );

#else // defined(_WIN64) && (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_))

__inline
VOID
InitializeSListHead (
    _Out_ PSLIST_HEADER SListHead)
{
#if defined(_WIN64)
    if (((ULONG_PTR)SListHead & 0xf) != 0) {
        RtlRaiseStatus(STATUS_DATATYPE_MISALIGNMENT);
    }
#endif
    RtlZeroMemory(SListHead, sizeof(SLIST_HEADER));
}
#endif // defined(_WIN64) && (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_))
#endif // !defined(_WINBASE_)

#define ExInitializeSListHead InitializeSListHead

NTKERNELAPI
PSLIST_ENTRY
FirstEntrySList (
    _In_ PSLIST_HEADER SListHead
    );

#if !defined(_X86_)

#if (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_))
NTKERNELAPI
USHORT
ExQueryDepthSList (
    _In_ PSLIST_HEADER SListHead
    );
#else // (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_))
__inline
USHORT
ExQueryDepthSList (
    _In_ PSLIST_HEADER SListHead
    )
{
#if defined(_WIN64)
    return (USHORT)(SListHead->Alignment & 0xffff);
#else
    return (USHORT)SListHead->Depth;
#endif
}
#endif // (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_))

#else // !defined(_X86_)

#define ExQueryDepthSList(_listhead_) (_listhead_)->Depth

#endif // !defined(_X86_)

#if !defined(_WINBASE_)

#define QueryDepthSList(Head) \
    ExQueryDepthSList(Head)

#endif // !defined(_WINBASE_)

#if !defined(_X86_)

#define ExInterlockedPopEntrySList(Head, Lock) \
    ExpInterlockedPopEntrySList(Head)

#define ExInterlockedPushEntrySList(Head, Entry, Lock) \
    ExpInterlockedPushEntrySList(Head, Entry)

#define ExInterlockedFlushSList(Head) \
    ExpInterlockedFlushSList(Head)

#if !defined(_WINBASE_)

#define InterlockedPopEntrySList(Head) \
    ExpInterlockedPopEntrySList(Head)

#define InterlockedPushEntrySList(Head, Entry) \
    ExpInterlockedPushEntrySList(Head, Entry)

#define InterlockedFlushSList(Head) \
    ExpInterlockedFlushSList(Head)

#endif // !defined(_WINBASE_)

NTKERNELAPI
PSLIST_ENTRY
ExpInterlockedPopEntrySList (
    _Inout_ PSLIST_HEADER ListHead
    );

NTKERNELAPI
PSLIST_ENTRY
ExpInterlockedPushEntrySList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ __drv_aliasesMem PSLIST_ENTRY ListEntry
    );

NTKERNELAPI
PSLIST_ENTRY
ExpInterlockedFlushSList (
    _Inout_ PSLIST_HEADER ListHead
    );

#else // !defined(_X86_)

#if defined(_WIN2K_COMPAT_SLIST_USAGE)

NTKERNELAPI
PSLIST_ENTRY
FASTCALL
ExInterlockedPopEntrySList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_opt_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock
    );

NTKERNELAPI
PSLIST_ENTRY
FASTCALL
ExInterlockedPushEntrySList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ __drv_aliasesMem PSLIST_ENTRY ListEntry,
    _Inout_opt_ _Requires_lock_not_held_(*_Curr_) PKSPIN_LOCK Lock
    );

#else // defined(_WIN2K_COMPAT_SLIST_USAGE)

#define ExInterlockedPopEntrySList(ListHead, Lock) \
    InterlockedPopEntrySList(ListHead)

#define ExInterlockedPushEntrySList(ListHead, ListEntry, Lock) \
    InterlockedPushEntrySList(ListHead, ListEntry)

#endif // defined(_WIN2K_COMPAT_SLIST_USAGE)

NTKERNELAPI
PSLIST_ENTRY
FASTCALL
ExInterlockedFlushSList (
    _Inout_ PSLIST_HEADER ListHead
    );

#if !defined(_WINBASE_)

NTKERNELAPI
PSLIST_ENTRY
FASTCALL
InterlockedPopEntrySList (
    _Inout_ PSLIST_HEADER ListHead
    );

NTKERNELAPI
PSLIST_ENTRY
FASTCALL
InterlockedPushEntrySList (
    _Inout_ PSLIST_HEADER ListHead,
    _Inout_ __drv_aliasesMem PSLIST_ENTRY ListEntry
    );

#define InterlockedFlushSList(Head) \
    ExInterlockedFlushSList(Head)

#endif // !defined(_WINBASE_)

#endif // !defined(_X86_)


#define LOOKASIDE_MINIMUM_BLOCK_SIZE  (RTL_SIZEOF_THROUGH_FIELD (SLIST_ENTRY, Next))

typedef struct _LOOKASIDE_LIST_EX {
    GENERAL_LOOKASIDE_POOL L;
} LOOKASIDE_LIST_EX, *PLOOKASIDE_LIST_EX;

#if (NTDDI_VERSION >= NTDDI_VISTA)

#define EX_LOOKASIDE_LIST_EX_FLAGS_RAISE_ON_FAIL    0x00000001UL
#define EX_LOOKASIDE_LIST_EX_FLAGS_FAIL_NO_RAISE    0x00000002UL

#define EX_MAXIMUM_LOOKASIDE_DEPTH_BASE     256     // Base maximum depth
#define EX_MAXIMUM_LOOKASIDE_DEPTH_LIMIT    1024    // Upper limit maximum depth

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
NTSTATUS
ExInitializeLookasideListEx (
    _Out_ PLOOKASIDE_LIST_EX Lookaside,
    _In_opt_ PALLOCATE_FUNCTION_EX Allocate,
    _In_opt_ PFREE_FUNCTION_EX Free,
    _In_ POOL_TYPE PoolType,
    _In_ ULONG Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Tag,
    _In_ USHORT Depth
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExDeleteLookasideListEx (
    _Inout_ PLOOKASIDE_LIST_EX Lookaside
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExFlushLookasideListEx (
    _Inout_ PLOOKASIDE_LIST_EX Lookaside
    );

__drv_allocatesMem(Mem)
_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
FORCEINLINE
PVOID
#pragma warning(suppress: 28195) // memory is not always allocated here, sometimes we reuse an entry from the list
ExAllocateFromLookasideListEx (
    _Inout_ PLOOKASIDE_LIST_EX Lookaside)
{
    PVOID Entry;

    Lookaside->L.TotalAllocates += 1;
    Entry = InterlockedPopEntrySList(&Lookaside->L.ListHead);
    if (Entry == NULL) {
        Lookaside->L.AllocateMisses += 1;
        Entry = (Lookaside->L.AllocateEx)(Lookaside->L.Type,
                                          Lookaside->L.Size,
                                          Lookaside->L.Tag,
                                          Lookaside);
    }
}

_IRQL_requires_max_(DISPATCH_LEVEL)
FORCEINLINE
VOID
ExFreeToLookasideListEx (
    _Inout_ PLOOKASIDE_LIST_EX Lookaside,
    _In_ __drv_freesMem(Entry) PVOID Entry)
{

    Lookaside->L.TotalFrees += 1;
    if (ExQueryDepthSList(&Lookaside->L.ListHead) >= Lookaside->L.Depth) {
        Lookaside->L.FreeMisses += 1;
        (Lookaside->L.FreeEx)(Entry, Lookaside);

    } else {
        InterlockedPushEntrySList(&Lookaside->L.ListHead, (PSLIST_ENTRY)Entry);
    }
}

#endif // (NTDDI_VERSION >= NTDDI_VISTA)

typedef struct LOOKASIDE_ALIGN _NPAGED_LOOKASIDE_LIST
{
    GENERAL_LOOKASIDE L;
#if defined(_X86_)
    KSPIN_LOCK Lock__ObsoleteButDoNotDelete;
#endif
} NPAGED_LOOKASIDE_LIST, *PNPAGED_LOOKASIDE_LIST;

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExInitializeNPagedLookasideList (
    _Out_ PNPAGED_LOOKASIDE_LIST Lookaside,
    _In_opt_ PALLOCATE_FUNCTION Allocate,
    _In_opt_ PFREE_FUNCTION Free,
    _In_ ULONG Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Tag,
    _In_ USHORT Depth
    );

#if !POOL_NX_OPTOUT && (POOL_NX_OPTIN || POOL_NX_OPTIN_AUTO)

FORCEINLINE
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
ExInitializeNPagedLookasideList_NXPoolOptIn (
    _Out_ PNPAGED_LOOKASIDE_LIST Lookaside,
    _In_opt_ PALLOCATE_FUNCTION Allocate,
    _In_opt_ PFREE_FUNCTION Free,
    _In_ ULONG Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Tag,
    _In_ USHORT Depth
    )
{
    ExInitializeNPagedLookasideList(Lookaside,
                                    Allocate,
                                    Free,
#if POOL_NX_OPTIN_AUTO
                                    Flags | POOL_NX_ALLOCATION,
#else
                                    Flags | (ULONG) ExDefaultNonPagedPoolType,
#endif
                                    Size,
                                    Tag,
                                    Depth);

    return;
}

#define ExInitializeNPagedLookasideList ExInitializeNPagedLookasideList_NXPoolOptIn

#endif // !POOL_NX_OPTOUT && (POOL_NX_OPTIN || POOL_NX_OPTIN_AUTO)

#endif // (NTDDI_VERSION >= NTDDK_WIN2K)


_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExDeleteNPagedLookasideList (
    _Inout_ PNPAGED_LOOKASIDE_LIST Lookaside
    );

__drv_allocatesMem(Mem)
_IRQL_requires_max_(DISPATCH_LEVEL)
__inline
_Ret_maybenull_
_Post_writable_byte_size_(Lookaside->L.Size)
PVOID
#pragma warning(suppress: 28195) // memory is not always allocated here, sometimes we reuse an entry from the list
ExAllocateFromNPagedLookasideList (
    _Inout_ PNPAGED_LOOKASIDE_LIST Lookaside)
{
    PVOID Entry;

    Lookaside->L.TotalAllocates += 1;
#if defined(_WIN2K_COMPAT_SLIST_USAGE) && defined(_X86_)
    Entry = ExInterlockedPopEntrySList(&Lookaside->L.ListHead,
                                       &Lookaside->Lock__ObsoleteButDoNotDelete);
#else
    Entry = InterlockedPopEntrySList(&Lookaside->L.ListHead);
#endif
    if (Entry == NULL) {
        Lookaside->L.AllocateMisses += 1;
        Entry = (Lookaside->L.Allocate)(Lookaside->L.Type,
                                        Lookaside->L.Size,
                                        Lookaside->L.Tag);
    }

    return Entry;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
__inline
VOID
ExFreeToNPagedLookasideList (
    _Inout_ PNPAGED_LOOKASIDE_LIST Lookaside,
    _In_ __drv_freesMem(Mem) PVOID Entry)
{
    Lookaside->L.TotalFrees += 1;
    if (ExQueryDepthSList(&Lookaside->L.ListHead) >= Lookaside->L.Depth) {
        Lookaside->L.FreeMisses += 1;
        (Lookaside->L.Free)(Entry);

    } else {
#if defined(_WIN2K_COMPAT_SLIST_USAGE) && defined(_X86_)
        ExInterlockedPushEntrySList(&Lookaside->L.ListHead,
                                    (PSLIST_ENTRY)Entry,
                                    &Lookaside->Lock__ObsoleteButDoNotDelete);

#else
        InterlockedPushEntrySList(&Lookaside->L.ListHead, (PSLIST_ENTRY)Entry);
#endif
    }
}

typedef struct LOOKASIDE_ALIGN _PAGED_LOOKASIDE_LIST
{
    GENERAL_LOOKASIDE L;
#if defined(_X86_)
    FAST_MUTEX Lock__ObsoleteButDoNotDelete;
#endif
} PAGED_LOOKASIDE_LIST, *PPAGED_LOOKASIDE_LIST;

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExInitializePagedLookasideList (
    _Out_ PPAGED_LOOKASIDE_LIST Lookaside,
    _In_opt_ PALLOCATE_FUNCTION Allocate,
    _In_opt_ PFREE_FUNCTION Free,
    _In_ ULONG Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Tag,
    _In_ USHORT Depth
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExDeletePagedLookasideList (
    _Inout_ PPAGED_LOOKASIDE_LIST Lookaside
    );

#if defined(_WIN2K_COMPAT_SLIST_USAGE) && defined(_X86_)

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PVOID
ExAllocateFromPagedLookasideList (
    _Inout_ PPAGED_LOOKASIDE_LIST Lookaside
    );

#else

#pragma warning(push)
#pragma warning(disable: 28195) // memory is not always allocated here, sometimes we reuse an entry from the list
__drv_allocatesMem(Mem)
_IRQL_requires_max_(APC_LEVEL)
__inline
PVOID
ExAllocateFromPagedLookasideList (
    _Inout_ PPAGED_LOOKASIDE_LIST Lookaside)
{
    PVOID Entry;

    Lookaside->L.TotalAllocates += 1;
    Entry = InterlockedPopEntrySList(&Lookaside->L.ListHead);
    if (Entry == NULL) {
        Lookaside->L.AllocateMisses += 1;
        Entry = (Lookaside->L.Allocate)(Lookaside->L.Type,
                                        Lookaside->L.Size,
                                        Lookaside->L.Tag);
    }

    return Entry;
}

#pragma warning(pop)

#endif

#if defined(_WIN2K_COMPAT_SLIST_USAGE) && defined(_X86_)

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExFreeToPagedLookasideList (
    _Inout_ PPAGED_LOOKASIDE_LIST Lookaside,
    _In_ PVOID Entry
    );

#else

_IRQL_requires_max_(APC_LEVEL)
__inline
VOID
ExFreeToPagedLookasideList (
    _Inout_ PPAGED_LOOKASIDE_LIST Lookaside,
    _In_ __drv_freesMem(Mem) PVOID Entry)
{
    Lookaside->L.TotalFrees += 1;
    if (ExQueryDepthSList(&Lookaside->L.ListHead) >= Lookaside->L.Depth) {
        Lookaside->L.FreeMisses += 1;
        (Lookaside->L.Free)(Entry);

    } else {
        InterlockedPushEntrySList(&Lookaside->L.ListHead,
                                  (PSLIST_ENTRY)Entry);
    }
}

#endif

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
DECLSPEC_NORETURN
VOID
NTAPI
ExRaiseStatus (
    _In_ NTSTATUS Status);

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
DECLSPEC_NORETURN
VOID
ExRaiseDatatypeMisalignment (
    VOID
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
DECLSPEC_NORETURN
VOID
ExRaiseAccessViolation (
    VOID
    );



DECLSPEC_DEPRECATED_DDK                  // Use IoAllocateWorkItem
CFORCEINLINE
VOID
ExInitializeWorkItem (
    _Out_    PWORK_QUEUE_ITEM Item,
    _In_opt_ PWORKER_THREAD_ROUTINE Routine,
    _In_opt_ PVOID Context
    )
{
    Item->WorkerRoutine = Routine;
    Item->Parameter = Context;
    Item->List.Flink = NULL;
}

#ifdef _NTDDK_
_When_( (!__drv_defined(_DRIVER_TYPE_FILESYSTEM)
    && !__drv_defined(_DRIVER_TYPE_FILESYSTEM_FILTER))
    || NTDDI_VERSION >= NTDDI_VISTA,
    __drv_preferredFunction("IoQueueWorkItem[Ex]",
    "Obsolete in all drivers for Vista. Obsolete downlevel except for limited "
    "use in IFS. See the documentation"))
#endif

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExAllocateFromZone)
#endif

#define ExAllocateFromZone(Zone) \
    (PVOID)((Zone)->FreeList.Next); \
    if ( (Zone)->FreeList.Next ) (Zone)->FreeList.Next = (Zone)->FreeList.Next->Next

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExFreeToZone)
#endif

#define ExFreeToZone(Zone,Block)                                    \
    ( ((PSINGLE_LIST_ENTRY)(Block))->Next = (Zone)->FreeList.Next,  \
      (Zone)->FreeList.Next = ((PSINGLE_LIST_ENTRY)(Block)),        \
      ((PSINGLE_LIST_ENTRY)(Block))->Next                           \
    )

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExIsFullZone)
#endif

#define ExIsFullZone(Zone) \
    ( (Zone)->FreeList.Next == (PSINGLE_LIST_ENTRY)NULL )

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExInterlockedAllocateFromZone)
#endif

#define ExInterlockedAllocateFromZone(Zone,Lock) \
    (PVOID) ExInterlockedPopEntryList( &(Zone)->FreeList, Lock )

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExInterlockedFreeToZone)
#endif

#define ExInterlockedFreeToZone(Zone,Block,Lock) \
    ExInterlockedPushEntryList( &(Zone)->FreeList, ((PSINGLE_LIST_ENTRY) (Block)), Lock )

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExIsObjectInFirstZoneSegment)
#endif

#define ExIsObjectInFirstZoneSegment(Zone,Object) ((BOOLEAN)     \
    (((PUCHAR)(Object) >= (PUCHAR)(Zone)->SegmentList.Next) &&   \
     ((PUCHAR)(Object) < (PUCHAR)(Zone)->SegmentList.Next +      \
                         (Zone)->TotalSegmentSize))              \
)




#define ResourceNeverExclusive          0x0010
#define ResourceReleaseByOtherThread    0x0020
#define ResourceOwnedExclusive          0x0080

#define RESOURCE_HASH_TABLE_SIZE 64

typedef struct _RESOURCE_HASH_ENTRY {
    LIST_ENTRY ListEntry;
    PVOID Address;
    ULONG ContentionCount;
    ULONG Number;
} RESOURCE_HASH_ENTRY, *PRESOURCE_HASH_ENTRY;

typedef struct _RESOURCE_PERFORMANCE_DATA {
    ULONG ActiveResourceCount;
    ULONG TotalResourceCount;
    ULONG ExclusiveAcquire;
    ULONG SharedFirstLevel;
    ULONG SharedSecondLevel;
    ULONG StarveFirstLevel;
    ULONG StarveSecondLevel;
    ULONG WaitForExclusive;
    ULONG OwnerTableExpands;
    ULONG MaximumTableExpand;
    LIST_ENTRY HashTable[RESOURCE_HASH_TABLE_SIZE];
} RESOURCE_PERFORMANCE_DATA, *PRESOURCE_PERFORMANCE_DATA;

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
NTSTATUS
ExInitializeResourceLite (
    _Out_ PERESOURCE Resource
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
NTSTATUS
ExReinitializeResourceLite (
    _Inout_ PERESOURCE Resource
    );

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_When_(Wait!=0, _Post_satisfies_(return == 1))
_When_(Wait==0, _Post_satisfies_(return == 0 || return == 1) _Must_inspect_result_)
NTKERNELAPI
BOOLEAN
ExAcquireResourceSharedLite (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_shared_lock_(*_Curr_))
    PERESOURCE Resource,
    _In_ BOOLEAN Wait
    );

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
NTKERNELAPI
PVOID
ExEnterCriticalRegionAndAcquireResourceShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_shared_lock_(*_Curr_)
    PERESOURCE Resource
    );

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
_Acquires_lock_(_Global_priority_region_)
NTKERNELAPI
PVOID
ExEnterPriorityRegionAndAcquireResourceShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_shared_lock_(*_Curr_)
    PERESOURCE Resource
    );

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
BOOLEAN
ExTryToAcquireResourceExclusiveLite (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_exclusive_lock_(*_Curr_))
    PERESOURCE Resource
    );

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_When_(Wait!=0, _Post_satisfies_(return == 1))
_When_(Wait==0, _Post_satisfies_(return == 0 || return == 1) _Must_inspect_result_)
NTKERNELAPI
BOOLEAN
ExAcquireResourceExclusiveLite (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_exclusive_lock_(*_Curr_))
    PERESOURCE Resource,
    _In_ _Literal_ BOOLEAN Wait
    );

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
NTKERNELAPI
PVOID
ExEnterCriticalRegionAndAcquireResourceExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_exclusive_lock_(*_Curr_)
    PERESOURCE Resource
    );

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
_Acquires_lock_(_Global_priority_region_)
NTKERNELAPI
PVOID
ExEnterPriorityRegionAndAcquireResourceExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_exclusive_lock_(*_Curr_)
    PERESOURCE Resource
    );

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_When_(Wait!=0, _Post_satisfies_(return == 1))
_When_(Wait==0, _Post_satisfies_(return == 0 || return == 1) _Must_inspect_result_)
NTKERNELAPI
BOOLEAN
ExAcquireSharedStarveExclusive(
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_shared_lock_(*_Curr_))
    PERESOURCE Resource,
    _In_ BOOLEAN Wait
    );

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_When_(Wait!=0, _Post_satisfies_(return == 1))
_When_(Wait==0, _Post_satisfies_(return == 0 || return == 1) _Must_inspect_result_)
NTKERNELAPI
BOOLEAN
ExAcquireSharedWaitForExclusive(
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return!=0, _Acquires_lock_(*_Curr_))
    PERESOURCE Resource,
    _In_ BOOLEAN Wait
    );

_IRQL_requires_max_(APC_LEVEL)
_Acquires_lock_(_Global_critical_region_)
NTKERNELAPI
PVOID
ExEnterCriticalRegionAndAcquireSharedWaitForExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PERESOURCE Resource
    );

#endif

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExReleaseResource)       // Use ExReleaseResourceLite
#endif

#define ExReleaseResource(R) (ExReleaseResourceLite(R))

_Requires_lock_held_(_Global_critical_region_)
_Requires_lock_held_(*Resource)
_Releases_lock_(*Resource)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
FASTCALL
ExReleaseResourceLite(
    _Inout_ PERESOURCE Resource
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Releases_lock_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExReleaseResourceAndLeaveCriticalRegion(
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PERESOURCE Resource
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Releases_lock_(_Global_critical_region_)
_Releases_lock_(_Global_priority_region_)
NTKERNELAPI
VOID
FASTCALL
ExReleaseResourceAndLeavePriorityRegion(
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PERESOURCE Resource
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
ExReleaseResourceForThreadLite(
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PERESOURCE Resource,
    _In_ ERESOURCE_THREAD ResourceThreadId
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExSetResourceOwnerPointer(
    _Inout_ PERESOURCE Resource,
    _In_ PVOID OwnerPointer
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExSetResourceOwnerPointerEx(
    _Inout_ PERESOURCE Resource,
    _In_ PVOID OwnerPointer,
    _In_ ULONG Flags
    );

#define FLAG_OWNER_POINTER_IS_THREAD 0x1

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExConvertExclusiveToSharedLite(
    _Inout_ _Requires_lock_held_(*_Curr_) PERESOURCE Resource
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
NTSTATUS
ExDeleteResourceLite (
    _Inout_ PERESOURCE Resource
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
ULONG
ExGetExclusiveWaiterCount (
    _In_ PERESOURCE Resource
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
ULONG
ExGetSharedWaiterCount (
    _In_ PERESOURCE Resource
    );

#define ExGetCurrentResourceThread() ((ULONG_PTR)PsGetCurrentThread())

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
ExIsResourceAcquiredExclusiveLite (
    _In_ PERESOURCE Resource
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
ULONG
ExIsResourceAcquiredSharedLite (
    _In_ PERESOURCE Resource
    );

#define ExIsResourceAcquiredLite ExIsResourceAcquiredSharedLite

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(ExInitializeResource)            // use ExInitializeResourceLite
#pragma deprecated(ExAcquireResourceShared)         // use ExAcquireResourceSharedLite
#pragma deprecated(ExAcquireResourceExclusive)      // use ExAcquireResourceExclusiveLite
#pragma deprecated(ExReleaseResourceForThread)      // use ExReleaseResourceForThreadLite
#pragma deprecated(ExConvertExclusiveToShared)      // use ExConvertExclusiveToSharedLite
#pragma deprecated(ExDeleteResource)                // use ExDeleteResourceLite
#pragma deprecated(ExIsResourceAcquiredExclusive)   // use ExIsResourceAcquiredExclusiveLite
#pragma deprecated(ExIsResourceAcquiredShared)      // use ExIsResourceAcquiredSharedLite
#pragma deprecated(ExIsResourceAcquired)            // use ExIsResourceAcquiredSharedLite
#endif
#define ExInitializeResource ExInitializeResourceLite
#define ExAcquireResourceShared ExAcquireResourceSharedLite
#define ExAcquireResourceExclusive ExAcquireResourceExclusiveLite
#define ExReleaseResourceForThread ExReleaseResourceForThreadLite
#define ExConvertExclusiveToShared ExConvertExclusiveToSharedLite
#define ExDeleteResource ExDeleteResourceLite
#define ExIsResourceAcquiredExclusive ExIsResourceAcquiredExclusiveLite
#define ExIsResourceAcquiredShared ExIsResourceAcquiredSharedLite
#define ExIsResourceAcquired ExIsResourceAcquiredSharedLite

#define EX_PUSH_LOCK_FLAG_ENABLE_AUTOBOOST      0x1 // Deprecated.
#define EX_PUSH_LOCK_FLAG_DISABLE_AUTOBOOST     0x2
#define EX_PUSH_LOCK_FLAGS_VALID                0x3

typedef struct _EX_PUSH_LOCK {
#define EX_PUSH_LOCK_LOCK_V          ((ULONG_PTR)0x0)
#define EX_PUSH_LOCK_LOCK            ((ULONG_PTR)0x1)
#define EX_PUSH_LOCK_WAITING         ((ULONG_PTR)0x2)
#define EX_PUSH_LOCK_WAKING          ((ULONG_PTR)0x4)
#define EX_PUSH_LOCK_MULTIPLE_SHARED ((ULONG_PTR)0x8)
#define EX_PUSH_LOCK_SHARE_INC       ((ULONG_PTR)0x10)
#define EX_PUSH_LOCK_PTR_BITS        ((ULONG_PTR)0xf)
    union {
        struct {
            ULONG_PTR Locked         : 1;
            ULONG_PTR Waiting        : 1;
            ULONG_PTR Waking         : 1;
            ULONG_PTR MultipleShared : 1;
            ULONG_PTR Shared         : sizeof(ULONG_PTR) * 8 - 4;
        };
        __volatile ULONG_PTR Value;
        __volatile PVOID Ptr;
    };
} EX_PUSH_LOCK, *PEX_PUSH_LOCK;

#define EX_CACHE_LINE_SIZE 128
#define EX_PUSH_LOCK_FANNED_COUNT (PAGE_SIZE/EX_CACHE_LINE_SIZE)

typedef struct _EX_PUSH_LOCK_CACHE_AWARE_LEGACY {
    PEX_PUSH_LOCK Locks[EX_PUSH_LOCK_FANNED_COUNT];
} EX_PUSH_LOCK_CACHE_AWARE_LEGACY, *PEX_PUSH_LOCK_CACHE_AWARE_LEGACY;

typedef struct _EX_PUSH_LOCK_CACHE_AWARE_PADDED {
    EX_PUSH_LOCK Lock;
    union {
        UCHAR Pad[EX_CACHE_LINE_SIZE - sizeof (EX_PUSH_LOCK)];
        struct {
            BOOLEAN Single;
            PVOID ParentLock;
        };
    };
} EX_PUSH_LOCK_CACHE_AWARE_PADDED, *PEX_PUSH_LOCK_CACHE_AWARE_PADDED;

#define EX_AEPL_EXPANDED       ((ULONG)0x00000001)
#define EX_AEPL_TRANSITIONING  ((ULONG)0x00000002)
#define EX_AEPL_PAGEABLE       ((ULONG)0x00000004)

#define EX_AEPL_STATE_BIT_MASK ((ULONG)(EX_AEPL_EXPANDED |      \
                                        EX_AEPL_TRANSITIONING | \
                                        EX_AEPL_PAGEABLE))

typedef struct _EX_PUSH_LOCK_AUTO_EXPAND_STATE {
    union {
        struct {
            ULONG Expanded      : 1;
            ULONG Transitioning : 1;
            ULONG Pageable      : 1;
        };
        __volatile ULONG Value;
    };
} EX_PUSH_LOCK_AUTO_EXPAND_STATE, *PEX_PUSH_LOCK_AUTO_EXPAND_STATE;

typedef struct _EX_PUSH_LOCK_AUTO_EXPAND {
    EX_PUSH_LOCK LocalLock;
    EX_PUSH_LOCK_AUTO_EXPAND_STATE State;
    ULONG Stats;
} EX_PUSH_LOCK_AUTO_EXPAND, *PEX_PUSH_LOCK_AUTO_EXPAND;

#if (NTDDI_VERSION < NTDDI_WINBLUE)
#ifndef EX_LEGACY_PUSH_LOCKS
#define EX_LEGACY_PUSH_LOCKS
#endif
#endif // (NTDDI_VERSION < NTDDI_WINBLUE)

#ifndef EX_LEGACY_CACHE_AWARE_LOCKS
#define EX_LEGACY_CACHE_AWARE_LOCKS
#endif

#if defined(EX_LEGACY_PUSH_LOCKS) || (NTDDI_VERSION < NTDDI_WINBLUE) || defined(EX_LEGACY_CACHE_AWARE_LOCKS)
typedef EX_PUSH_LOCK_CACHE_AWARE_LEGACY EX_PUSH_LOCK_CACHE_AWARE,
                                        *PEX_PUSH_LOCK_CACHE_AWARE;
#else
typedef EX_PUSH_LOCK_AUTO_EXPAND EX_PUSH_LOCK_CACHE_AWARE,
                                 *PEX_PUSH_LOCK_CACHE_AWARE;
#endif

typedef struct _EX_RUNDOWN_REF
{
#define EX_RUNDOWN_ACTIVE      0x1
#define EX_RUNDOWN_COUNT_SHIFT 0x1
#define EX_RUNDOWN_COUNT_INC   (1<<EX_RUNDOWN_COUNT_SHIFT)
    union {
        __volatile ULONG_PTR Count;
        __volatile PVOID Ptr;
    };
} EX_RUNDOWN_REF, *PEX_RUNDOWN_REF;

typedef struct _EX_RUNDOWN_REF_CACHE_AWARE  *PEX_RUNDOWN_REF_CACHE_AWARE;

#define EX_CARR_EXPANDED           ((ULONG)0x00000001)
#define EX_CARR_TRANSITIONING      ((ULONG)0x00000002)
#define EX_CARR_EXPANSION_DISABLED ((ULONG)0x00000004)
#define EX_CARR_PAGEABLE           ((ULONG)0x00000008)

#define EX_CARR_STATE_BIT_MASK     ((ULONG)(EX_CARR_EXPANDED | \
                                            EX_CARR_TRANSITIONING | \
                                            EX_CARR_EXPANSION_DISABLED))

typedef struct _EX_RUNDOWN_REF_CACHE_AWARE_STATE {
    union {
        struct {

            ULONG Expanded          : 1;
            ULONG Transitioning     : 1;
            ULONG ExpansionDisabled : 1;
            ULONG Pageable          : 1;
        };
        __volatile ULONG Value;
    };
} EX_RUNDOWN_REF_CACHE_AWARE_STATE, *PEX_RUNDOWN_REF_CACHE_AWARE_STATE;

typedef struct _EX_RUNDOWN_REF_CACHE_AWARE {

    PEX_RUNDOWN_REF RunRefs;
    PVOID PoolToFree;
    ULONG RunRefSize;
    ULONG Number;
} EX_RUNDOWN_REF_CACHE_AWARE, *PEX_RUNDOWN_REF_CACHE_AWARE;

typedef struct _EXHANDLE {

    union {
        struct {
            ULONG TagBits : 2;
            ULONG Index : 30;
        };
        HANDLE GenericHandleOverlay;
#define HANDLE_VALUE_INC 4 // Amount to increment the Value to get to the next handle
        ULONG_PTR Value;
    };
} EXHANDLE, *PEXHANDLE;

_IRQL_requires_max_(APC_LEVEL)
int
ExSystemExceptionFilter(
    VOID
    );

NTKERNELAPI
VOID
ExSystemTimeToLocalTime (
    _In_ PLARGE_INTEGER SystemTime,
    _Out_ PLARGE_INTEGER LocalTime
    );

NTKERNELAPI
VOID
ExLocalTimeToSystemTime (
    _In_ PLARGE_INTEGER LocalTime,
    _Out_ PLARGE_INTEGER SystemTime
    );

typedef struct _EX_TIMER *PEX_TIMER;

_Function_class_(EXT_CALLBACK)
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_requires_same_
typedef
VOID
EXT_CALLBACK (
    _In_ PEX_TIMER Timer,
    _In_opt_ PVOID Context
    );

typedef EXT_CALLBACK *PEXT_CALLBACK;

_Function_class_(EXT_DELETE_CALLBACK)
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_requires_same_
typedef
VOID
EXT_DELETE_CALLBACK (
    _In_opt_ PVOID Context
    );

typedef EXT_DELETE_CALLBACK *PEXT_DELETE_CALLBACK;
typedef PVOID PEXT_CANCEL_PARAMETERS;
typedef struct _EXT_DELETE_PARAMETERS {
    ULONG Version;
    ULONG Reserved;
    PEXT_DELETE_CALLBACK DeleteCallback;
    PVOID DeleteContext;
} EXT_DELETE_PARAMETERS, *PEXT_DELETE_PARAMETERS;

#define EX_TIMER_HIGH_RESOLUTION 0x4
#define EX_TIMER_NO_WAKE 0x8
#define EX_TIMER_UNLIMITED_TOLERANCE ((LONGLONG)-1)
#define EX_TIMER_NOTIFICATION (1UL << 31)
#define EX_TIMER_IDLE_RESILIENT 0x2

typedef struct _CALLBACK_OBJECT *PCALLBACK_OBJECT;

typedef
_IRQL_requires_same_
_Function_class_(CALLBACK_FUNCTION)
VOID
CALLBACK_FUNCTION (
    _In_opt_ PVOID CallbackContext,
    _In_opt_ PVOID Argument1,
    _In_opt_ PVOID Argument2
    );

typedef CALLBACK_FUNCTION *PCALLBACK_FUNCTION;

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
ExCreateCallback (
    _Outptr_ PCALLBACK_OBJECT *CallbackObject,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ BOOLEAN Create,
    _In_ BOOLEAN AllowMultipleCallbacks
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PVOID
ExRegisterCallback (
    _Inout_ PCALLBACK_OBJECT CallbackObject,
    _In_ PCALLBACK_FUNCTION CallbackFunction,
    _In_opt_ PVOID CallbackContext
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExUnregisterCallback (
    _Inout_ PVOID CallbackRegistration
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExNotifyCallback (
    _In_ PVOID CallbackObject,
    _In_opt_ PVOID Argument1,
    _In_opt_ PVOID Argument2
    );

typedef
_IRQL_requires_same_
_Function_class_(WIN32_GLOBALATOMTABLE_CALLOUT)
PVOID
WIN32_GLOBALATOMTABLE_CALLOUT (
    VOID
    );

typedef WIN32_GLOBALATOMTABLE_CALLOUT *PKWIN32_GLOBALATOMTABLE_CALLOUT;

extern PKWIN32_GLOBALATOMTABLE_CALLOUT ExGlobalAtomTableCallout;

typedef GUID UUID;

NTKERNELAPI
VOID
FASTCALL
ExInitializeRundownProtection (
    _Out_ PEX_RUNDOWN_REF RunRef
    );

NTKERNELAPI
VOID
FASTCALL
ExReInitializeRundownProtection (
    _Inout_ PEX_RUNDOWN_REF RunRef
    );

_Must_inspect_result_
_Post_satisfies_(return == 0 || return == 1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExAcquireRundownProtection (
    _Inout_ PEX_RUNDOWN_REF RunRef
    );

_Must_inspect_result_
_Post_satisfies_(return == 0 || return == 1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExAcquireRundownProtectionEx (
    _Inout_ PEX_RUNDOWN_REF RunRef,
    _In_ ULONG Count
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
FASTCALL
ExReleaseRundownProtection (
    _Inout_ PEX_RUNDOWN_REF RunRef
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
FASTCALL
ExReleaseRundownProtectionEx (
    _Inout_ PEX_RUNDOWN_REF RunRef,
    _In_ ULONG Count
    );

NTKERNELAPI
VOID
FASTCALL
ExRundownCompleted (
    _Out_ PEX_RUNDOWN_REF RunRef
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
FASTCALL
ExWaitForRundownProtectionRelease (
    _Inout_ PEX_RUNDOWN_REF RunRef
    );

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PEX_RUNDOWN_REF_CACHE_AWARE
ExAllocateCacheAwareRundownProtection(
    __drv_strictTypeMatch(__drv_typeExpr) _In_ POOL_TYPE PoolType,
    _In_ ULONG PoolTag
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
SIZE_T
ExSizeOfRundownProtectionCacheAware(
    VOID
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExInitializeRundownProtectionCacheAware(
    _Out_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware,
    _In_ SIZE_T RunRefSize
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExFreeCacheAwareRundownProtection(
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
    );

_Must_inspect_result_
_Post_satisfies_(return == 0 || return == 1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExAcquireRundownProtectionCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
    );

NTKERNELAPI
VOID
FASTCALL
ExReleaseRundownProtectionCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
    );

_Must_inspect_result_
_Post_satisfies_(return == 0 || return == 1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExAcquireRundownProtectionCacheAwareEx (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware,
    _In_ ULONG Count
    );

NTKERNELAPI
VOID
FASTCALL
ExReleaseRundownProtectionCacheAwareEx (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRef,
    _In_ ULONG Count
    );

NTKERNELAPI
VOID
FASTCALL
ExWaitForRundownProtectionReleaseCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRef
    );

NTKERNELAPI
VOID
FASTCALL
ExReInitializeRundownProtectionCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
    );

NTKERNELAPI
VOID
FASTCALL
ExRundownCompletedCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
    );

#define EX_CARR_ALLOCATE_PAGED_POOL         0x00000000
#define EX_CARR_ALLOCATE_NONPAGED_POOL      0x00000001

#define EX_CARR_DISABLE_EXPANSION           0x00000002

#define EX_CARR_VALID_FLAGS                 (EX_CARR_ALLOCATE_NONPAGED_POOL | \
                                             EX_CARR_DISABLE_EXPANSION)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExInitializeRundownProtectionCacheAwareEx (
    _Out_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExCleanupRundownProtectionCacheAware (
    _Inout_ PEX_RUNDOWN_REF_CACHE_AWARE RunRefCacheAware
    );

#if !defined(NONTOSPINTERLOCK)

FORCEINLINE
VOID
ExInitializePushLock (
    _Out_ PEX_PUSH_LOCK PushLock)
{
    PushLock->Value = 0;
}

#if defined(_WIN64)
#define EX_TRY_ACQUIRE_PUSH_LOCK_EXCLUSIVE_OP(PUSHLOCK) \
    InterlockedBitTestAndSet64Acquire((LONG64 *)&(PUSHLOCK)->Value, EX_PUSH_LOCK_LOCK_V)
#else
#define EX_TRY_ACQUIRE_PUSH_LOCK_EXCLUSIVE_OP(PUSHLOCK) \
    InterlockedBitTestAndSetAcquire((LONG *)&(PUSHLOCK)->Value, EX_PUSH_LOCK_LOCK_V)
#endif

#endif  // // !defined(NONTOSPINTERLOCK)

#if !defined(NONTOSPINTERLOCK)

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExfAcquirePushLockExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock
    );

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
VOID
FASTCALL
ExfAcquirePushLockShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExfReleasePushLock (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExfReleasePushLockShared (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExfReleasePushLockExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock
    );

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExfTryAcquirePushLockShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_)
    _When_(return==1, _Acquires_lock_(*_Curr_))
    PEX_PUSH_LOCK PushLock
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
FASTCALL
ExfTryToWakePushLock (
    _Inout_ PEX_PUSH_LOCK PushLock
    );

#define ExAcquirePushLockSharedAssumeNoOwner ExAcquirePushLockShared
#define ExReleasePushLockSharedAssumeSingleOwner ExReleasePushLockShared

#if !defined(EX_LEGACY_PUSH_LOCKS)

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExAcquirePushLockExclusiveEx (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExAcquirePushLockSharedEx (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags
    );

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExTryAcquirePushLockExclusiveEx (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags
    );

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExTryAcquirePushLockSharedEx (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExReleasePushLockEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExReleasePushLockExclusiveEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExReleasePushLockSharedEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags
    );

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
NTKERNELAPI
BOOLEAN
FASTCALL
ExTryConvertPushLockSharedToExclusiveEx (
    _Inout_ _Requires_lock_held_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags
    );

#undef EX_DEFAULT_PUSH_LOCK_FLAGS

#if !defined(AB_TRACKING_DISABLED)
#define EX_DEFAULT_PUSH_LOCK_FLAGS      0
#else
#define EX_DEFAULT_PUSH_LOCK_FLAGS      EX_PUSH_LOCK_FLAG_DISABLE_AUTOBOOST
#endif // !defined(AB_TRACKING_DISABLED)

#define ExAcquirePushLockExclusive(Lock)   \
        ExAcquirePushLockExclusiveEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExAcquirePushLockShared(Lock)   \
        ExAcquirePushLockSharedEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExTryAcquirePushLockExclusive(Lock) \
        ExTryAcquirePushLockExclusiveEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExTryAcquirePushLockShared(Lock) \
        ExTryAcquirePushLockSharedEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExReleasePushLock(Lock) \
        ExReleasePushLockEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExReleasePushLockExclusive(Lock) \
        ExReleasePushLockExclusiveEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExReleasePushLockShared(Lock) \
        ExReleasePushLockSharedEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExTryConvertPushLockSharedToExclusive(Lock) \
        ExTryConvertPushLockSharedToExclusiveEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#else // EX_LEGACY_PUSH_LOCKS

#pragma warning (push)
#pragma prefast(disable: __WARNING_FAILING_TO_ACQUIRE_MEDIUM_CONFIDENCE, \
                "Prefast doesn't know that the success return from InterlockedCompareExchange in the ExAcquire* functions here actually acquires the pushlock.");

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
FORCEINLINE
VOID
ExAcquirePushLockExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    if (EX_TRY_ACQUIRE_PUSH_LOCK_EXCLUSIVE_OP(PushLock)) {

        ExfAcquirePushLockExclusive(PushLock);
    }

    NT_ASSERT(PushLock->Locked);
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
CFORCEINLINE
BOOLEAN
ExTryAcquirePushLockExclusive (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK PushLock)
{
    if (EX_TRY_ACQUIRE_PUSH_LOCK_EXCLUSIVE_OP(PushLock))
    {
        return FALSE;
    }

    NT_ASSERT(PushLock->Locked);
    return TRUE;
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
FORCEINLINE
BOOLEAN
ExTryAcquirePushLockShared (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK PushLock)
{
    EX_PUSH_LOCK OldValue, NewValue;

    OldValue.Value = 0;
    NewValue.Value = EX_PUSH_LOCK_SHARE_INC | EX_PUSH_LOCK_LOCK;

    if (InterlockedCompareExchangePointerAcquire(&PushLock->Ptr,
                                                 NewValue.Ptr,
                                                 OldValue.Ptr) != OldValue.Ptr)
    {
        if (!ExfTryAcquirePushLockShared(PushLock))
        {
            return FALSE;
        }
    }

#if DBG
    OldValue.Ptr = ReadPointerNoFence(&PushLock->Ptr);
    NT_ASSERT(OldValue.Locked);
    NT_ASSERT(OldValue.Waiting || OldValue.Shared > 0);
#endif

    return TRUE;
}

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
FORCEINLINE
VOID
ExAcquirePushLockShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    EX_PUSH_LOCK OldValue, NewValue;

    OldValue.Value = 0;
    NewValue.Value = EX_PUSH_LOCK_SHARE_INC | EX_PUSH_LOCK_LOCK;
    if (InterlockedCompareExchangePointerAcquire(&PushLock->Ptr,
                                                 NewValue.Ptr,
                                                 OldValue.Ptr) != OldValue.Ptr)
    {
        ExfAcquirePushLockShared(PushLock);
    }

#if DBG
    OldValue.Ptr = ReadPointerNoFence(&PushLock->Ptr);
    NT_ASSERT(OldValue.Locked);
    NT_ASSERT(OldValue.Waiting || OldValue.Shared > 0);
#endif
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
FORCEINLINE
VOID
ExReleasePushLock (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    EX_PUSH_LOCK OldValue, NewValue;

    PrefetchForWrite(PushLock);
    OldValue.Ptr = ReadPointerNoFence(&PushLock->Ptr);

    NT_ASSERT(OldValue.Locked);

    if (OldValue.Shared > 1)
    {
        NewValue.Value = OldValue.Value - EX_PUSH_LOCK_SHARE_INC;
    }
    else
    {
        NewValue.Value = 0;
    }

    if (OldValue.Waiting ||
        InterlockedCompareExchangePointerRelease(&PushLock->Ptr,
                                                 NewValue.Ptr,
                                                 OldValue.Ptr) != OldValue.Ptr)
    {
        ExfReleasePushLock(PushLock);
    }
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
FORCEINLINE
VOID
ExReleasePushLockExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    EX_PUSH_LOCK OldValue;

#if DBG
    PrefetchForWrite(PushLock);
    OldValue.Ptr = ReadPointerNoFence(&PushLock->Ptr);
    NT_ASSERT(OldValue.Locked);
    NT_ASSERT(OldValue.Waiting || OldValue.Shared == 0);
#endif

#if defined(_WIN64)
    OldValue.Value = InterlockedExchangeAddRelease64((PLONG64)&PushLock->Value,
                                                     -(LONG64)EX_PUSH_LOCK_LOCK);
#else
    OldValue.Value = InterlockedExchangeAddRelease((PLONG)&PushLock->Value,
                                                   -(LONG)EX_PUSH_LOCK_LOCK);
#endif

    _Analysis_assume_lock_held_ (PushLock);
    _Analysis_assume_lock_released_ (PushLock);

    NT_ASSERT(OldValue.Locked);
    NT_ASSERT(OldValue.Waiting || OldValue.Shared == 0);

    if (OldValue.Waiting && !OldValue.Waking)
    {
        ExfTryToWakePushLock(PushLock);
    }
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
FORCEINLINE
VOID
ExReleasePushLockShared (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    EX_PUSH_LOCK OldValue, NewValue;

#if DBG
    PrefetchForWrite(PushLock);
    OldValue.Ptr = ReadPointerNoFence(&PushLock->Ptr);
    NT_ASSERT(OldValue.Locked);
    NT_ASSERT(OldValue.Waiting || OldValue.Shared > 0);
#endif

    OldValue.Value = EX_PUSH_LOCK_SHARE_INC | EX_PUSH_LOCK_LOCK;
    NewValue.Value = 0;
    if (InterlockedCompareExchangePointerRelease(&PushLock->Ptr,
                                                 NewValue.Ptr,
                                                 OldValue.Ptr) != OldValue.Ptr)
    {
        ExfReleasePushLockShared(PushLock);
    }
    else
    {
        _Analysis_assume_lock_held_ (PushLock);
        _Analysis_assume_lock_released_ (PushLock);
    }
}

_Must_inspect_result_
_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
_Post_satisfies_(return == 0 || return == 1)
FORCEINLINE
BOOLEAN
ExTryConvertPushLockSharedToExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    if (InterlockedCompareExchangePointer(&PushLock->Ptr,
                                          (PVOID) EX_PUSH_LOCK_LOCK,
                                          (PVOID) (EX_PUSH_LOCK_SHARE_INC | EX_PUSH_LOCK_LOCK)) ==
                                            (PVOID)(EX_PUSH_LOCK_SHARE_INC | EX_PUSH_LOCK_LOCK))
    {
        NT_ASSERT(PushLock->Locked);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#endif // !EX_LEGACY_PUSH_LOCKS

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PEX_PUSH_LOCK_AUTO_EXPAND
ExAllocateAutoExpandPushLock (
     _In_ ULONG Flags
     );

#define EX_AEPL_ALLOCATE_PAGED_POOL       0x00000000
#define EX_AEPL_ALLOCATE_NONPAGED_POOL    0x00000001

#define EX_CAPLFL_ALLOCATE_PAGED_POOL       0x00000000
#define EX_CAPLFL_ALLOCATE_NONPAGED_POOL    0x00000001

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExFreeAutoExpandPushLock (
     _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND PushLock
     );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
FASTCALL
ExAcquireAutoExpandPushLockExclusive (
    _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
FASTCALL
ExReleaseAutoExpandPushLockExclusive (
    _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
PVOID
FASTCALL
ExAcquireAutoExpandPushLockShared (
    _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExReleaseAutoExpandPushLockShared (
    _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    _Inout_ PVOID PushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExInitializeAutoExpandPushLock (
    _Out_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
SIZE_T
ExSizeOfAutoExpandPushLock (
    _In_ ULONG Flags
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExCleanupAutoExpandPushLock (
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
FASTCALL
ExTryAcquireAutoExpandPushLockExclusive (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
     _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
     _In_ ULONG Flags
     );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PVOID
FASTCALL
ExTryAcquireAutoExpandPushLockShared (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK_AUTO_EXPAND AutoExpandPushLock,
    _In_ ULONG Flags
    );

#if defined(EX_LEGACY_PUSH_LOCKS)

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
FORCEINLINE
PEX_PUSH_LOCK
ExAcquireCacheAwarePushLockShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock)
{
    PEX_PUSH_LOCK PushLock;
    ULONG ProcIndex;

    ProcIndex = KeGetCurrentProcessorNumberEx(NULL);
    PushLock = CacheAwarePushLock->Locks[ProcIndex % EX_PUSH_LOCK_FANNED_COUNT];
    ExAcquirePushLockSharedAssumeNoOwner(PushLock);
    return PushLock;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
FORCEINLINE
VOID
ExReleaseCacheAwarePushLockShared (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock)
{
    ExReleasePushLockSharedAssumeSingleOwner(PushLock);
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PEX_PUSH_LOCK_CACHE_AWARE
ExAllocateCacheAwarePushLock (
     _In_ ULONG Flags
     );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExFreeCacheAwarePushLock (
     _Inout_ PEX_PUSH_LOCK_CACHE_AWARE_LEGACY PushLock
     );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExAcquireCacheAwarePushLockExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExReleaseCacheAwarePushLockExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock
    );

#elif ((NTDDI_VERSION < NTDDI_WINBLUE) || defined(EX_LEGACY_CACHE_AWARE_LOCKS)) // EX_LEGACY_PUSH_LOCKS

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
PEX_PUSH_LOCK_CACHE_AWARE_LEGACY
ExAllocateCacheAwarePushLock (
     _In_ ULONG Flags
     );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExFreeCacheAwarePushLock (
     _Inout_ PEX_PUSH_LOCK_CACHE_AWARE_LEGACY PushLock
     );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExAcquireCacheAwarePushLockExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE CacheAwarePushLock
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExReleaseCacheAwarePushLockExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE CacheAwarePushLock
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
FASTCALL
ExAcquireCacheAwarePushLockExclusiveEx (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
FASTCALL
ExReleaseCacheAwarePushLockExclusiveEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(APC_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
PEX_PUSH_LOCK
FASTCALL
ExAcquireCacheAwarePushLockSharedEx (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_PUSH_LOCK_CACHE_AWARE_LEGACY CacheAwarePushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
_Requires_lock_held_(_Global_critical_region_)
NTKERNELAPI
VOID
FASTCALL
ExReleaseCacheAwarePushLockSharedEx (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_PUSH_LOCK PushLock,
    _In_ ULONG Flags
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
FASTCALL
ExTryAcquireCacheAwarePushLockExclusiveEx (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
     _Inout_ PEX_PUSH_LOCK_CACHE_AWARE_LEGACY AutoExpandPushLock,
     _In_ ULONG Flags
     );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
PVOID
FASTCALL
ExTryAcquireCacheAwarePushLockSharedEx (
    _When_(return!=0, _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_))
    _Inout_ PEX_PUSH_LOCK_CACHE_AWARE_LEGACY AutoExpandPushLock,
    _In_ ULONG Flags
    );

#define ExAcquireCacheAwarePushLockShared(Lock) \
        ExAcquireCacheAwarePushLockSharedEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExReleaseCacheAwarePushLockShared(Lock) \
        ExReleaseCacheAwarePushLockSharedEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#else // !EX_LEGACY_PUSHLOCKS && (NTDDI_VERSION <= NTDDI_WINBLUE)

#define ExAllocateCacheAwarePushLock(Flags) \
        ExAllocateAutoExpandPushLock(Flags)

#define ExFreeCacheAwarePushLock(Lock) \
        ExFreeAutoExpandPushLock(Lock)

#define ExAcquireCacheAwarePushLockShared(Lock) \
        ExAcquireAutoExpandPushLockShared(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExReleaseCacheAwarePushLockShared(Lock) \
        ExReleaseAutoExpandPushLockShared(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExAcquireCacheAwarePushLockSharedEx(Lock, Flags) \
        ExAcquireAutoExpandPushLockShared(Lock, Flags)

#define ExReleaseCacheAwarePushLockSharedEx(Lock, Flags) \
        ExReleaseAutoExpandPushLockShared(Lock, Flags)

#define ExAcquireCacheAwarePushLockExclusive(Lock) \
        ExAcquireAutoExpandPushLockExclusive(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExReleaseCacheAwarePushLockExclusive(Lock) \
        ExReleaseAutoExpandPushLockExclusive(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExAcquireCacheAwarePushLockExclusiveEx(Lock, Flags) \
        ExAcquireAutoExpandPushLockExclusive(Lock, Flags)

#define ExReleaseCacheAwarePushLockExclusiveEx(Lock, Flags) \
        ExReleaseAutoExpandPushlockExclusive(Lock, Flags)

#define ExTryAcquireCacheAwarePushLockExclusive(Lock) \
        ExTryAcquireAutoExpandPushLockExclusive(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExTryAcquireCacheAwarePushLockShared(Lock) \
        ExTryAcquireAutoExpandPushLockShared(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExTryAcquireCacheAwarePushLockExclusiveEx(Lock, Flags) \
        ExTryAcquireAutoExpandPushLockExclusive(Lock, Flags)

#define ExTryAcquireCacheAwarePushLockSharedEx(Lock, Flags) \
        ExTryAcquireAutoExpandPushLockShared(Lock, Flags)

#endif // !EX_LEGACY_PUSHLOCKS && (NTDDI_VERSION > NTDDI_WINBLUE)

#endif // !defined(NONTOSPINTERLOCK)


#if !defined(NONTOSPINTERLOCK)

NTKERNELAPI
NTSTATUS
FASTCALL
ExBlockOnAddressPushLock (
     _Inout_ PEX_PUSH_LOCK PushLock,
     _In_reads_bytes_(AddressSize) volatile VOID *Address,
     _In_reads_bytes_(AddressSize) PVOID CompareAddress,
     _In_ SIZE_T AddressSize,
     _In_opt_ PLARGE_INTEGER Timeout
     );

NTKERNELAPI
VOID
FASTCALL
ExfUnblockPushLock (
     _Inout_ PEX_PUSH_LOCK PushLock,
     _Inout_opt_ PVOID WaitBlock
     );

#if !defined(EX_LEGACY_PUSH_LOCKS)

NTKERNELAPI
VOID
FASTCALL
ExUnblockPushLockEx (
     _Inout_ PEX_PUSH_LOCK PushLock,
     _In_ ULONG Flags
     );

NTKERNELAPI
VOID
FASTCALL
ExUnblockOnAddressPushLockEx (
     _Inout_ PEX_PUSH_LOCK PushLock,
     _In_ ULONG Flags
     );

#define ExUnblockPushLock(Lock) \
        ExUnblockPushLockEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#define ExUnblockOnAddressPushLock(Lock) \
        ExUnblockOnAddressPushLockEx(Lock, EX_DEFAULT_PUSH_LOCK_FLAGS)

#else // !defined(EX_LEGACY_PUSH_LOCKS)

FORCEINLINE
NTKERNELAPI
VOID
ExUnblockPushLock (
     _Inout_ PEX_PUSH_LOCK PushLock)
{
    KeMemoryBarrier ();
    if (PushLock->Ptr != NULL) {
        ExfUnblockPushLock (PushLock, NULL);
    }
}

FORCEINLINE
NTKERNELAPI
VOID
ExUnblockOnAddressPushLock (
     _Inout_ PEX_PUSH_LOCK PushLock)
{
    ExUnblockPushLock (PushLock);
}

#endif // !defined(EX_LEGACY_PUSH_LOCKS)


#endif // !defined(NONTOSPINTERLOCK)

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
ExShareAddressSpaceWithDevice (
    _In_ struct _DEVICE_OBJECT *PhysicalDeviceObject,
    _Out_ PULONG ReturnedAsid
    );

typedef volatile LONG EX_SPIN_LOCK, *PEX_SPIN_LOCK;
#define ALIGNED_EX_SPINLOCK DECLSPEC_CACHEALIGN EX_SPIN_LOCK

_IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExAcquireSpinLockSharedAtDpcLevel (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_SPIN_LOCK SpinLock
    );

_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
NTKERNELAPI
KIRQL
ExAcquireSpinLockShared (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_SPIN_LOCK SpinLock
    );

_IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExReleaseSpinLockSharedFromDpcLevel (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_SPIN_LOCK SpinLock
    );

_IRQL_requires_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExReleaseSpinLockShared (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_SPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL OldIrql
    );

_Must_inspect_result_
_IRQL_requires_(DISPATCH_LEVEL)
_Post_satisfies_(return == 0 || return == 1)
NTKERNELAPI
LOGICAL
ExTryConvertSharedSpinLockExclusive (
    _Inout_ PEX_SPIN_LOCK SpinLock
    );

_IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExAcquireSpinLockExclusiveAtDpcLevel (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_SPIN_LOCK SpinLock
    );

_IRQL_saves_
_IRQL_raises_(DISPATCH_LEVEL)
NTKERNELAPI
KIRQL
ExAcquireSpinLockExclusive (
    _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
    PEX_SPIN_LOCK SpinLock
    );

_IRQL_requires_min_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExReleaseSpinLockExclusiveFromDpcLevel (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_SPIN_LOCK SpinLock
    );

_IRQL_requires_(DISPATCH_LEVEL)
NTKERNELAPI
VOID
ExReleaseSpinLockExclusive (
    _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
    PEX_SPIN_LOCK SpinLock,
    _In_ _IRQL_restores_ KIRQL OldIrql
    );



_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
ExUpdateLicenseData(
    _In_ ULONG MemCacheDataSize,
    _In_reads_bytes_(MemCacheDataSize) PVOID MemCacheData
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ExSetLicenseTamperState(
    _In_ LICENSING_TAMPER_STATE LicensingTamperState
    );

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
BOOLEAN
ExGetLicenseTamperState(
    _Out_opt_ PLICENSING_TAMPER_STATE LicensingTamperState
    );

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
ExFetchLicenseData(
    _Out_writes_bytes_to_opt_(DataSize, *ResultDataSize) PVOID Data,
    _In_ ULONG DataSize,
    _Out_ PULONG ResultDataSize
    );

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
ExHandleSPCall2(
    _In_ KPROCESSOR_MODE PreviousMode,
    _In_ volatile SYSTEM_POLICY_INFORMATION* SPCall2Information
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
BOOLEAN
ExQueryFastCacheDevLicense(
    VOID
    );

enum {
    FAST_CACHE_APP_ORIGIN_UNKNOWN        = 0,
    FAST_CACHE_APP_ORIGIN_UNSIGNED,
    FAST_CACHE_APP_ORIGIN_INBOX,
    FAST_CACHE_APP_ORIGIN_APP_STORE,
    FAST_CACHE_APP_ORIGIN_DEV_UNSIGNED,
    FAST_CACHE_APP_ORIGIN_DEV_SIGNED,
    FAST_CACHE_APP_ORIGIN_LINE_OF_BUSINESS
};

#define EX_PCW_EXTENSION_ID              1
#define EX_AUTH_EXTENSION_ID             2
#define EX_BCRYPT_EXTENSION_ID           3
#define EX_NET_RATE_CONTROL_EXTENSION_ID 4
#define EX_IO_QOS_EXTENSION_ID           5

#define EX_PCW_EXTENSION_VERSION              1
#define EX_AUTH_EXTENSION_VERSION             1
#define EX_BCRYPT_EXTENSION_VERSION           1
#define EX_NET_RATE_CONTROL_EXTENSION_VERSION 1
#define EX_IO_QOS_EXTENSION_VERSION           1

typedef struct _EX_EXTENSION *PEX_EXTENSION;

typedef struct _EX_EXTENSION_REGISTRATION_1
{
    USHORT ExtensionId;
    USHORT ExtensionVersion;
    USHORT FunctionCount;
    const VOID *FunctionTable;
    PVOID *HostTable;
    PVOID DriverObject;
} EX_EXTENSION_REGISTRATION_1, *PEX_EXTENSION_REGISTRATION_1;

#define EX_EXTENSION_REGISTRATION_VERSION_1 0x10000

#define LOAD_INFORMATION_IMAGE_HASH_INVALID     0x00000001
#define LOAD_INFORMATION_MALFORMED_DRIVER_PATH  0x00000002
#define LOAD_INFORMATION_IMPORT_LOAD_FAILED     0x00000004
#define LOAD_INFORMATION_EMBEDDED_SIGNED        0x00000008
#define LOAD_INFORMATION_CATALOG_SIGNED         0x00000010
#define LOAD_INFORMATION_POLICY_VIOLATION       0x00000020

typedef struct _BOOT_DRIVER_LIST_ENTRY {
    LIST_ENTRY Link;
    UNICODE_STRING FilePath;
    UNICODE_STRING RegistryPath;
    PBLDR_DATA_TABLE_ENTRY LdrEntry;
    NTSTATUS LoadStatus;
    ULONG LoadInformation;
} BOOT_DRIVER_LIST_ENTRY, *PBOOT_DRIVER_LIST_ENTRY;

typedef enum _REG_NOTIFY_CLASS {
    RegNtDeleteKey,
    RegNtPreDeleteKey = RegNtDeleteKey,
    RegNtSetValueKey,
    RegNtPreSetValueKey = RegNtSetValueKey,
    RegNtDeleteValueKey,
    RegNtPreDeleteValueKey = RegNtDeleteValueKey,
    RegNtSetInformationKey,
    RegNtPreSetInformationKey = RegNtSetInformationKey,
    RegNtRenameKey,
    RegNtPreRenameKey = RegNtRenameKey,
    RegNtEnumerateKey,
    RegNtPreEnumerateKey = RegNtEnumerateKey,
    RegNtEnumerateValueKey,
    RegNtPreEnumerateValueKey = RegNtEnumerateValueKey,
    RegNtQueryKey,
    RegNtPreQueryKey = RegNtQueryKey,
    RegNtQueryValueKey,
    RegNtPreQueryValueKey = RegNtQueryValueKey,
    RegNtQueryMultipleValueKey,
    RegNtPreQueryMultipleValueKey = RegNtQueryMultipleValueKey,
    RegNtPreCreateKey,
    RegNtPostCreateKey,
    RegNtPreOpenKey,
    RegNtPostOpenKey,
    RegNtKeyHandleClose,
    RegNtPreKeyHandleClose = RegNtKeyHandleClose,
    RegNtPostDeleteKey,
    RegNtPostSetValueKey,
    RegNtPostDeleteValueKey,
    RegNtPostSetInformationKey,
    RegNtPostRenameKey,
    RegNtPostEnumerateKey,
    RegNtPostEnumerateValueKey,
    RegNtPostQueryKey,
    RegNtPostQueryValueKey,
    RegNtPostQueryMultipleValueKey,
    RegNtPostKeyHandleClose,
    RegNtPreCreateKeyEx,
    RegNtPostCreateKeyEx,
    RegNtPreOpenKeyEx,
    RegNtPostOpenKeyEx,
    RegNtPreFlushKey,
    RegNtPostFlushKey,
    RegNtPreLoadKey,
    RegNtPostLoadKey,
    RegNtPreUnLoadKey,
    RegNtPostUnLoadKey,
    RegNtPreQueryKeySecurity,
    RegNtPostQueryKeySecurity,
    RegNtPreSetKeySecurity,
    RegNtPostSetKeySecurity,
    RegNtCallbackObjectContextCleanup,
    RegNtPreRestoreKey,
    RegNtPostRestoreKey,
    RegNtPreSaveKey,
    RegNtPostSaveKey,
    RegNtPreReplaceKey,
    RegNtPostReplaceKey,

    MaxRegNtNotifyClass //should always be the last enum
} REG_NOTIFY_CLASS;

typedef struct _REG_DELETE_KEY_INFORMATION {
    PVOID    Object;                      // IN
    PVOID    CallContext;  // new to Windows Vista
    PVOID    ObjectContext;// new to Windows Vista
    PVOID    Reserved;     // new to Windows Vista
} REG_DELETE_KEY_INFORMATION, *PREG_DELETE_KEY_INFORMATION
#if (NTDDI_VERSION >= NTDDI_VISTA)
, REG_FLUSH_KEY_INFORMATION, *PREG_FLUSH_KEY_INFORMATION
#endif // NTDDI_VERSION >= NTDDI_VISTA
;

typedef struct _REG_SET_VALUE_KEY_INFORMATION {
    PVOID               Object;                         // IN
    PUNICODE_STRING     ValueName;                      // IN
    ULONG               TitleIndex;                     // IN
    ULONG               Type;                           // IN
    PVOID               Data;                           // IN
    ULONG               DataSize;                       // IN
    PVOID               CallContext;  // new to Windows Vista
    PVOID               ObjectContext;// new to Windows Vista
    PVOID               Reserved;     // new to Windows Vista
} REG_SET_VALUE_KEY_INFORMATION, *PREG_SET_VALUE_KEY_INFORMATION;

typedef struct _REG_DELETE_VALUE_KEY_INFORMATION {
    PVOID               Object;                         // IN
    PUNICODE_STRING     ValueName;                      // IN
    PVOID               CallContext;  // new to Windows Vista
    PVOID               ObjectContext;// new to Windows Vista
    PVOID               Reserved;     // new to Windows Vista
} REG_DELETE_VALUE_KEY_INFORMATION, *PREG_DELETE_VALUE_KEY_INFORMATION;

typedef struct _REG_SET_INFORMATION_KEY_INFORMATION {
    PVOID                       Object;                 // IN
    KEY_SET_INFORMATION_CLASS   KeySetInformationClass; // IN
    PVOID                       KeySetInformation;      // IN
    ULONG                       KeySetInformationLength;// IN
    PVOID                       CallContext;  // new to Windows Vista
    PVOID                       ObjectContext;// new to Windows Vista
    PVOID                       Reserved;     // new to Windows Vista
} REG_SET_INFORMATION_KEY_INFORMATION, *PREG_SET_INFORMATION_KEY_INFORMATION;

typedef struct _REG_ENUMERATE_KEY_INFORMATION {
    PVOID                       Object;                 // IN
    ULONG                       Index;                  // IN
    KEY_INFORMATION_CLASS       KeyInformationClass;    // IN
    PVOID                       KeyInformation;         // IN
    ULONG                       Length;                 // IN
    PULONG                      ResultLength;           // OUT
    PVOID                       CallContext;  // new to Windows Vista
    PVOID                       ObjectContext;// new to Windows Vista
    PVOID                       Reserved;     // new to Windows Vista
} REG_ENUMERATE_KEY_INFORMATION, *PREG_ENUMERATE_KEY_INFORMATION;

typedef struct _REG_ENUMERATE_VALUE_KEY_INFORMATION {
    PVOID                           Object;                     // IN
    ULONG                           Index;                      // IN
    KEY_VALUE_INFORMATION_CLASS     KeyValueInformationClass;   // IN
    PVOID                           KeyValueInformation;        // IN
    ULONG                           Length;                     // IN
    PULONG                          ResultLength;               // OUT
    PVOID                           CallContext;  // new to Windows Vista
    PVOID                           ObjectContext;// new to Windows Vista
    PVOID                           Reserved;     // new to Windows Vista
} REG_ENUMERATE_VALUE_KEY_INFORMATION, *PREG_ENUMERATE_VALUE_KEY_INFORMATION;

typedef struct _REG_QUERY_KEY_INFORMATION {
    PVOID                       Object;                 // IN
    KEY_INFORMATION_CLASS       KeyInformationClass;    // IN
    PVOID                       KeyInformation;         // IN
    ULONG                       Length;                 // IN
    PULONG                      ResultLength;           // OUT
    PVOID                       CallContext;  // new to Windows Vista
    PVOID                       ObjectContext;// new to Windows Vista
    PVOID                       Reserved;     // new to Windows Vista
} REG_QUERY_KEY_INFORMATION, *PREG_QUERY_KEY_INFORMATION;

typedef struct _REG_QUERY_VALUE_KEY_INFORMATION {
    PVOID                           Object;                     // IN
    PUNICODE_STRING                 ValueName;                  // IN
    KEY_VALUE_INFORMATION_CLASS     KeyValueInformationClass;   // IN
    PVOID                           KeyValueInformation;        // IN
    ULONG                           Length;                     // IN
    PULONG                          ResultLength;               // OUT
    PVOID                           CallContext;  // new to Windows Vista
    PVOID                           ObjectContext;// new to Windows Vista
    PVOID                           Reserved;     // new to Windows Vista
} REG_QUERY_VALUE_KEY_INFORMATION, *PREG_QUERY_VALUE_KEY_INFORMATION;

typedef struct _REG_QUERY_MULTIPLE_VALUE_KEY_INFORMATION {
    PVOID               Object;                 // IN
    PKEY_VALUE_ENTRY    ValueEntries;           // IN
    ULONG               EntryCount;             // IN
    PVOID               ValueBuffer;            // IN
    PULONG              BufferLength;           // IN OUT
    PULONG              RequiredBufferLength;   // OUT
    PVOID               CallContext;  // new to Windows Vista
    PVOID               ObjectContext;// new to Windows Vista
    PVOID 	            Reserved;     // new to Windows Vista
} REG_QUERY_MULTIPLE_VALUE_KEY_INFORMATION, *PREG_QUERY_MULTIPLE_VALUE_KEY_INFORMATION;

typedef struct _REG_RENAME_KEY_INFORMATION {
    PVOID            Object;    // IN
    PUNICODE_STRING  NewName;   // IN
    PVOID            CallContext;  // new to Windows Vista
    PVOID            ObjectContext;// new to Windows Vista
    PVOID            Reserved;     // new to Windows Vista
} REG_RENAME_KEY_INFORMATION, *PREG_RENAME_KEY_INFORMATION;


typedef struct _REG_KEY_HANDLE_CLOSE_INFORMATION {
    PVOID               Object;         // IN
    PVOID               CallContext;  // new to Windows Vista
    PVOID               ObjectContext;// new to Windows Vista
    PVOID               Reserved;     // new to Windows Vista
} REG_KEY_HANDLE_CLOSE_INFORMATION, *PREG_KEY_HANDLE_CLOSE_INFORMATION;

typedef struct _REG_CREATE_KEY_INFORMATION {
    PUNICODE_STRING     CompleteName; // IN
    PVOID               RootObject;   // IN
    PVOID               ObjectType;   // new to Windows Vista
    ULONG               CreateOptions;// new to Windows Vista
    PUNICODE_STRING     Class;        // new to Windows Vista
    PVOID               SecurityDescriptor;// new to Windows Vista
    PVOID               SecurityQualityOfService;// new to Windows Vista
    ACCESS_MASK         DesiredAccess;// new to Windows Vista
    ACCESS_MASK         GrantedAccess;// new to Windows Vista
			  		                  // to be filled in by callbacks
                                      // when bypassing native code
    PULONG              Disposition;  // new to Windows Vista
                                      // on pass through, callback should fill
                                      // in disposition
    PVOID               *ResultObject;// new to Windows Vista
				                      // on pass through, callback should return
                                      // object to be used for the return handle
    PVOID               CallContext;  // new to Windows Vista
    PVOID               RootObjectContext;  // new to Windows Vista
    PVOID               Transaction;  // new to Windows Vista
    PVOID               Reserved;     // new to Windows Vista
} REG_CREATE_KEY_INFORMATION, REG_OPEN_KEY_INFORMATION,*PREG_CREATE_KEY_INFORMATION, *PREG_OPEN_KEY_INFORMATION;

typedef struct _REG_CREATE_KEY_INFORMATION_V1 {
    PUNICODE_STRING     CompleteName; // IN
    PVOID               RootObject;   // IN
    PVOID               ObjectType;   // new to Windows Vista
    ULONG               Options;      // new to Windows Vista
    PUNICODE_STRING     Class;        // new to Windows Vista
    PVOID               SecurityDescriptor;// new to Windows Vista
    PVOID               SecurityQualityOfService;// new to Windows Vista
    ACCESS_MASK         DesiredAccess;// new to Windows Vista
    ACCESS_MASK         GrantedAccess;// new to Windows Vista
			  		                  // to be filled in by callbacks
                                      // when bypassing native code
    PULONG              Disposition;  // new to Windows Vista
                                      // on pass through, callback should fill
                                      // in disposition
    PVOID               *ResultObject;// new to Windows Vista
				                      // on pass through, callback should return
                                      // object to be used for the return handle
    PVOID               CallContext;  // new to Windows Vista
    PVOID               RootObjectContext;  // new to Windows Vista
    PVOID               Transaction;  // new to Windows Vista

    ULONG_PTR           Version;      // following is new to Windows 7
    PUNICODE_STRING     RemainingName;// the true path left to parse
    ULONG               Wow64Flags;   // Wow64 specific flags gotten from DesiredAccess input
    ULONG               Attributes;   // ObjectAttributes->Attributes
    KPROCESSOR_MODE     CheckAccessMode;  // mode used for the securiry checks
} REG_CREATE_KEY_INFORMATION_V1, REG_OPEN_KEY_INFORMATION_V1,*PREG_CREATE_KEY_INFORMATION_V1, *PREG_OPEN_KEY_INFORMATION_V1;

typedef struct _REG_POST_OPERATION_INFORMATION {
    PVOID               Object;         // IN
    NTSTATUS            Status;         // IN
    PVOID               PreInformation; // new to Windows Vista; identical with the pre information that was sent
                                        // in the pre notification
    NTSTATUS            ReturnStatus;   // new to Windows Vista; callback can now change the outcome of the operation
                                        // during post by returning the new staus here
    PVOID               CallContext;    // new to Windows Vista
    PVOID               ObjectContext;  // new to Windows Vista
    PVOID               Reserved;       // new to Windows Vista
} REG_POST_OPERATION_INFORMATION,*PREG_POST_OPERATION_INFORMATION;

typedef struct _REG_PRE_CREATE_KEY_INFORMATION {
    PUNICODE_STRING     CompleteName;   // IN
} REG_PRE_CREATE_KEY_INFORMATION, REG_PRE_OPEN_KEY_INFORMATION,*PREG_PRE_CREATE_KEY_INFORMATION, *PREG_PRE_OPEN_KEY_INFORMATION;;

typedef struct _REG_POST_CREATE_KEY_INFORMATION {
    PUNICODE_STRING     CompleteName;   // IN
    PVOID               Object;         // IN
    NTSTATUS            Status;         // IN
} REG_POST_CREATE_KEY_INFORMATION,REG_POST_OPEN_KEY_INFORMATION, *PREG_POST_CREATE_KEY_INFORMATION, *PREG_POST_OPEN_KEY_INFORMATION;

typedef struct _REG_LOAD_KEY_INFORMATION {
    PVOID               Object;
    PUNICODE_STRING     KeyName;
    PUNICODE_STRING     SourceFile;
	ULONG				Flags;
    PVOID               TrustClassObject;
	PVOID               UserEvent;
	ACCESS_MASK         DesiredAccess;
    PHANDLE             RootHandle;
    PVOID               CallContext;
    PVOID               ObjectContext;
    PVOID               Reserved;
} REG_LOAD_KEY_INFORMATION, *PREG_LOAD_KEY_INFORMATION;

typedef struct _REG_UNLOAD_KEY_INFORMATION {
    PVOID    Object;
    PVOID	 UserEvent;
    PVOID    CallContext;
    PVOID    ObjectContext;
    PVOID    Reserved;
} REG_UNLOAD_KEY_INFORMATION, *PREG_UNLOAD_KEY_INFORMATION;

typedef struct _REG_CALLBACK_CONTEXT_CLEANUP_INFORMATION {
    PVOID   Object;
    PVOID   ObjectContext;
    PVOID   Reserved;
} REG_CALLBACK_CONTEXT_CLEANUP_INFORMATION, *PREG_CALLBACK_CONTEXT_CLEANUP_INFORMATION;

typedef struct _REG_QUERY_KEY_SECURITY_INFORMATION {
    PVOID                   Object;
    PSECURITY_INFORMATION   SecurityInformation;  // IN
    PSECURITY_DESCRIPTOR    SecurityDescriptor;   // INOUT
    PULONG                  Length;               // INOUT
    PVOID                   CallContext;
    PVOID                   ObjectContext;
    PVOID                   Reserved;
} REG_QUERY_KEY_SECURITY_INFORMATION, *PREG_QUERY_KEY_SECURITY_INFORMATION;

typedef struct _REG_SET_KEY_SECURITY_INFORMATION {
    PVOID                   Object;
    PSECURITY_INFORMATION   SecurityInformation;  // IN
    PSECURITY_DESCRIPTOR    SecurityDescriptor;   // IN
    PVOID                   CallContext;
    PVOID                   ObjectContext;
    PVOID                   Reserved;
} REG_SET_KEY_SECURITY_INFORMATION, *PREG_SET_KEY_SECURITY_INFORMATION;

typedef struct _REG_RESTORE_KEY_INFORMATION {
    PVOID               Object;
    HANDLE              FileHandle;
    ULONG				Flags;
    PVOID               CallContext;
    PVOID               ObjectContext;
    PVOID               Reserved;
} REG_RESTORE_KEY_INFORMATION, *PREG_RESTORE_KEY_INFORMATION;

typedef struct _REG_SAVE_KEY_INFORMATION {
    PVOID               Object;
    HANDLE              FileHandle;
    ULONG               Format;
    PVOID               CallContext;
    PVOID               ObjectContext;
    PVOID               Reserved;
} REG_SAVE_KEY_INFORMATION, *PREG_SAVE_KEY_INFORMATION;

typedef struct _REG_REPLACE_KEY_INFORMATION {
    PVOID               Object;
    PUNICODE_STRING     OldFileName;
    PUNICODE_STRING     NewFileName;
    PVOID               CallContext;
    PVOID               ObjectContext;
    PVOID               Reserved;
} REG_REPLACE_KEY_INFORMATION, *PREG_REPLACE_KEY_INFORMATION;

#define IDLE_TRANSITION 0x80000000

NTKERNELAPI
NTSTATUS
KdPowerTransition (
    _In_ DEVICE_POWER_STATE newDeviceState
    );

NTSTATUS
KdCallPowerHandlers (
    __in DEVICE_POWER_STATE PowerState
    );

VOID
KdMarkHiberPhase (
    VOID
    );

#define MAX_DEBUGGING_DEVICES_SUPPORTED 2

NTKERNELAPI
NTSTATUS
KdSystemDebugControl (
    _In_ SYSDBG_COMMAND Command,
    _Inout_updates_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_opt_ PULONG ReturnLength,
    _In_ KPROCESSOR_MODE PreviousMode
    );

NTKERNELAPI
NTSTATUS
KdSecureEnableDebugger (
    VOID
    );

#if defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_WDMDDK_) || defined(_NTOSP_)

extern PBOOLEAN KdDebuggerNotPresent;
extern PBOOLEAN KdDebuggerEnabled;
#define KD_DEBUGGER_ENABLED     *KdDebuggerEnabled
#define KD_DEBUGGER_NOT_PRESENT *KdDebuggerNotPresent

#else

extern BOOLEAN KdDebuggerNotPresent;
extern BOOLEAN KdDebuggerEnabled;
#define KD_DEBUGGER_ENABLED     KdDebuggerEnabled
#define KD_DEBUGGER_NOT_PRESENT KdDebuggerNotPresent

#endif

NTKERNELAPI
NTSTATUS
KdDisableDebugger(
    VOID
    );

NTKERNELAPI
NTSTATUS
KdEnableDebugger(
    VOID
    );

NTKERNELAPI
BOOLEAN
KdRefreshDebuggerNotPresent(
    VOID
    );

typedef enum _KD_OPTION {
    KD_OPTION_SET_BLOCK_ENABLE,
} KD_OPTION;

NTSTATUS
KdChangeOption(
    _In_ KD_OPTION Option,
    _In_ ULONG InBufferBytes OPTIONAL,
    _In_ PVOID InBuffer,
    _In_ ULONG OutBufferBytes OPTIONAL,
    _Out_ PVOID OutBuffer,
    _Out_ PULONG OutBufferNeeded OPTIONAL
    );

typedef
NTSTATUS
(*PKD_SET_POWER) (
    __in DEVICE_POWER_STATE PowerState,
    __in PVOID Context
    );

typedef struct _KD_POWER_HANDLER {
    LIST_ENTRY List;
    PKD_SET_POWER SetPower;
    PVOID Context;
} KD_POWER_HANDLER, *PKD_POWER_HANDLER;

NTSTATUS
KdRegisterPowerHandler (
    __in PKD_SET_POWER PowerCallback,
    __in PVOID Context,
    __out PHANDLE CallbackHandle
    );

NTSTATUS
KdDeregisterPowerHandler (
    __in HANDLE CallbackHandle
    );

#define EVENT_INCREMENT                 1
#define IO_NO_INCREMENT                 0
#define IO_CD_ROM_INCREMENT             1
#define IO_DISK_INCREMENT               1
#define IO_KEYBOARD_INCREMENT           6
#define IO_MAILSLOT_INCREMENT           2
#define IO_MOUSE_INCREMENT              6
#define IO_NAMED_PIPE_INCREMENT         2
#define IO_NETWORK_INCREMENT            2
#define IO_PARALLEL_INCREMENT           1
#define IO_SERIAL_INCREMENT             2
#define IO_SOUND_INCREMENT              8
#define IO_VIDEO_INCREMENT              1
#define MUTANT_INCREMENT                1
#define SEMAPHORE_INCREMENT             1
#define IO_TYPE_ADAPTER                 0x00000001
#define IO_TYPE_CONTROLLER              0x00000002
#define IO_TYPE_DEVICE                  0x00000003
#define IO_TYPE_DRIVER                  0x00000004
#define IO_TYPE_FILE                    0x00000005
#define IO_TYPE_IRP                     0x00000006
#define IO_TYPE_MASTER_ADAPTER          0x00000007
#define IO_TYPE_OPEN_PACKET             0x00000008
#define IO_TYPE_TIMER                   0x00000009
#define IO_TYPE_VPB                     0x0000000a
#define IO_TYPE_ERROR_LOG               0x0000000b
#define IO_TYPE_ERROR_MESSAGE           0x0000000c
#define IO_TYPE_DEVICE_OBJECT_EXTENSION 0x0000000d
#define IRP_MJ_CREATE                   0x00
#define IRP_MJ_CREATE_NAMED_PIPE        0x01
#define IRP_MJ_CLOSE                    0x02
#define IRP_MJ_READ                     0x03
#define IRP_MJ_WRITE                    0x04
#define IRP_MJ_QUERY_INFORMATION        0x05
#define IRP_MJ_SET_INFORMATION          0x06
#define IRP_MJ_QUERY_EA                 0x07
#define IRP_MJ_SET_EA                   0x08
#define IRP_MJ_FLUSH_BUFFERS            0x09
#define IRP_MJ_QUERY_VOLUME_INFORMATION 0x0a
#define IRP_MJ_SET_VOLUME_INFORMATION   0x0b
#define IRP_MJ_DIRECTORY_CONTROL        0x0c
#define IRP_MJ_FILE_SYSTEM_CONTROL      0x0d
#define IRP_MJ_DEVICE_CONTROL           0x0e
#define IRP_MJ_INTERNAL_DEVICE_CONTROL  0x0f
#define IRP_MJ_SHUTDOWN                 0x10
#define IRP_MJ_LOCK_CONTROL             0x11
#define IRP_MJ_CLEANUP                  0x12
#define IRP_MJ_CREATE_MAILSLOT          0x13
#define IRP_MJ_QUERY_SECURITY           0x14
#define IRP_MJ_SET_SECURITY             0x15
#define IRP_MJ_POWER                    0x16
#define IRP_MJ_SYSTEM_CONTROL           0x17
#define IRP_MJ_DEVICE_CHANGE            0x18
#define IRP_MJ_QUERY_QUOTA              0x19
#define IRP_MJ_SET_QUOTA                0x1a
#define IRP_MJ_PNP                      0x1b
#define IRP_MJ_PNP_POWER                IRP_MJ_PNP      // Obsolete....
#define IRP_MJ_MAXIMUM_FUNCTION         0x1b

#define IRP_MJ_SCSI                     IRP_MJ_INTERNAL_DEVICE_CONTROL

#define IRP_MN_QUERY_DIRECTORY          0x01
#define IRP_MN_NOTIFY_CHANGE_DIRECTORY  0x02

#define IRP_MN_USER_FS_REQUEST          0x00
#define IRP_MN_MOUNT_VOLUME             0x01
#define IRP_MN_VERIFY_VOLUME            0x02
#define IRP_MN_LOAD_FILE_SYSTEM         0x03
#define IRP_MN_TRACK_LINK               0x04    // To be obsoleted soon
#define IRP_MN_KERNEL_CALL              0x04

#define IRP_MN_LOCK                     0x01
#define IRP_MN_UNLOCK_SINGLE            0x02
#define IRP_MN_UNLOCK_ALL               0x03
#define IRP_MN_UNLOCK_ALL_BY_KEY        0x04

#define IRP_MN_FLUSH_AND_PURGE          0x01
#if (NTDDI_VERSION >= NTDDI_WIN8)
#define IRP_MN_FLUSH_DATA_ONLY          0x02    //see FLUSH_FLAGS_FILE_DATA_ONLY for definition of how this works
#define IRP_MN_FLUSH_NO_SYNC            0x03    //see FLUSH_FLAGS_NO_SYNC for definition of how this works
#endif

#define IRP_MN_NORMAL                   0x00
#define IRP_MN_DPC                      0x01
#define IRP_MN_MDL                      0x02
#define IRP_MN_COMPLETE                 0x04
#define IRP_MN_COMPRESSED               0x08

#define IRP_MN_MDL_DPC                  (IRP_MN_MDL | IRP_MN_DPC)
#define IRP_MN_COMPLETE_MDL             (IRP_MN_COMPLETE | IRP_MN_MDL)
#define IRP_MN_COMPLETE_MDL_DPC         (IRP_MN_COMPLETE_MDL | IRP_MN_DPC)

#define IRP_MN_SCSI_CLASS               0x01

#define IRP_MN_START_DEVICE                 0x00
#define IRP_MN_QUERY_REMOVE_DEVICE          0x01
#define IRP_MN_REMOVE_DEVICE                0x02
#define IRP_MN_CANCEL_REMOVE_DEVICE         0x03
#define IRP_MN_STOP_DEVICE                  0x04
#define IRP_MN_QUERY_STOP_DEVICE            0x05
#define IRP_MN_CANCEL_STOP_DEVICE           0x06

#define IRP_MN_QUERY_DEVICE_RELATIONS       0x07
#define IRP_MN_QUERY_INTERFACE              0x08
#define IRP_MN_QUERY_CAPABILITIES           0x09
#define IRP_MN_QUERY_RESOURCES              0x0A
#define IRP_MN_QUERY_RESOURCE_REQUIREMENTS  0x0B
#define IRP_MN_QUERY_DEVICE_TEXT            0x0C
#define IRP_MN_FILTER_RESOURCE_REQUIREMENTS 0x0D

#define IRP_MN_READ_CONFIG                  0x0F
#define IRP_MN_WRITE_CONFIG                 0x10
#define IRP_MN_EJECT                        0x11
#define IRP_MN_SET_LOCK                     0x12
#define IRP_MN_QUERY_ID                     0x13
#define IRP_MN_QUERY_PNP_DEVICE_STATE       0x14
#define IRP_MN_QUERY_BUS_INFORMATION        0x15
#define IRP_MN_DEVICE_USAGE_NOTIFICATION    0x16
#define IRP_MN_SURPRISE_REMOVAL             0x17

#define IRP_MN_DEVICE_ENUMERATED            0x19

#define IRP_MN_QUERY_LEGACY_BUS_INFORMATION 0x18

#define IRP_MN_WAIT_WAKE                    0x00
#define IRP_MN_POWER_SEQUENCE               0x01
#define IRP_MN_SET_POWER                    0x02
#define IRP_MN_QUERY_POWER                  0x03

#define IRP_MN_QUERY_ALL_DATA               0x00
#define IRP_MN_QUERY_SINGLE_INSTANCE        0x01
#define IRP_MN_CHANGE_SINGLE_INSTANCE       0x02
#define IRP_MN_CHANGE_SINGLE_ITEM           0x03
#define IRP_MN_ENABLE_EVENTS                0x04
#define IRP_MN_DISABLE_EVENTS               0x05
#define IRP_MN_ENABLE_COLLECTION            0x06
#define IRP_MN_DISABLE_COLLECTION           0x07
#define IRP_MN_REGINFO                      0x08
#define IRP_MN_EXECUTE_METHOD               0x09
// Minor code 0x0a is reserved
#define IRP_MN_REGINFO_EX                   0x0b

#define IO_FORCE_ACCESS_CHECK           0x0001
#define IO_NO_PARAMETER_CHECKING        0x0100

#define IO_REPARSE                      0x0
#define IO_REMOUNT                      0x1


#define IO_CHECK_CREATE_PARAMETERS      0x0200
#define IO_ATTACH_DEVICE                0x0400

#define IO_IGNORE_SHARE_ACCESS_CHECK    0x0800  // Ignores share access checks on opens.

typedef
VOID
(*PSTALL_ROUTINE) (
    _In_ ULONG Delay
    );

typedef
BOOLEAN
(*PDUMP_DRIVER_OPEN) (
    _In_ LARGE_INTEGER PartitionOffset
    );

typedef
NTSTATUS
(*PDUMP_DRIVER_WRITE) (
    _In_ PLARGE_INTEGER DiskByteOffset,
    _In_ PMDL Mdl
    );

typedef
NTSTATUS
(*PDUMP_DRIVER_READ) (
    _In_ LONG   Action,
    _In_ PLARGE_INTEGER DiskByteOffset,
    _In_ PMDL Mdl
    );

typedef
NTSTATUS
(*PDUMP_DRIVER_GET_TELEMETRY) (
    _In_ ULONG  Flags,
    _In_ ULONG  Level,
    _Out_ PVOID Buffer,
    _In_ ULONG  BufferSize
    );

#define IO_DUMP_FULFILL   0   // fulfill IO request as if DRIVER_WAIT
#define IO_DUMP_START     1   // start new IO
#define IO_DUMP_QUERY     2   // query pending IO
#define IO_DUMP_FINISH    3   // finish pending IO
#define IO_DUMP_INIT      4   // initialize locals

#define IO_DUMP_WRITE_FULFILL   IO_DUMP_FULFILL
#define IO_DUMP_WRITE_START     IO_DUMP_START
#define IO_DUMP_WRITE_RESUME    IO_DUMP_QUERY
#define IO_DUMP_WRITE_FINISH    IO_DUMP_FINISH
#define IO_DUMP_WRITE_INIT      IO_DUMP_INIT

#define IO_DUMP_WRITE_DATA_PAGES 2
#define IO_DUMP_WRITE_DATA_SIZE (IO_DUMP_WRITE_DATA_PAGES << PAGE_SHIFT)

typedef
NTSTATUS
(*PDUMP_DRIVER_WRITE_PENDING) (
    _In_ LONG Action,
    _In_ PLARGE_INTEGER DiskByteOffset,
    _In_ PMDL Mdl,
    _In_ PVOID LocalData
    );

typedef
VOID
(*PDUMP_DRIVER_FINISH) (
    VOID
    );

typedef
VOID
(*PDUMP_DRIVER_GET_TRANSFER_SIZES) (
    _Out_opt_ PULONG Minimum,
    _Out_opt_ PULONG Maximum
    );

typedef enum _DUMP_EVENTS {

    DUMP_EVENT_NONE = 0,
    DUMP_EVENT_HIBER_RESUME,
    DUMP_EVENT_HIBER_RESUME_END

} DUMP_EVENTS, *PDUMP_EVENTS;

typedef
VOID
(*PDUMP_NOTIFY)(
    _In_     DUMP_EVENTS Event,
    _In_opt_ PVOID Context,
    _In_     ULONG Arg
    );

struct _ADAPTER_OBJECT;

#define DUMP_INIT_TC_MAX_PARAMS 16
#define DUMP_MEMORY_BLOCK_BOOT_PAGES 2

typedef struct _DUMP_INITIALIZATION_CONTEXT {
    ULONG Length;
    ULONG Reserved;
    PVOID MemoryBlock;
    PVOID CommonBuffer[2];
    PHYSICAL_ADDRESS PhysicalAddress[2];
    PSTALL_ROUTINE StallRoutine;
    PDUMP_DRIVER_OPEN OpenRoutine;
    PDUMP_DRIVER_WRITE WriteRoutine;
    PDUMP_DRIVER_FINISH FinishRoutine;
    struct _ADAPTER_OBJECT *AdapterObject;
    PVOID MappedRegisterBase;
    PVOID PortConfiguration;
    BOOLEAN CrashDump;
    BOOLEAN MarkMemoryOnly;
    BOOLEAN HiberResume;
    BOOLEAN Reserved1;
    ULONG MaximumTransferSize;
    ULONG CommonBufferSize;
    PVOID TargetAddress;
    PDUMP_DRIVER_WRITE_PENDING WritePendingRoutine;
    ULONG PartitionStyle;
    union {
        struct {
            ULONG Signature;
            ULONG CheckSum;
        } Mbr;
        struct {
            GUID DiskId;
        } Gpt;
    } DiskInfo;
    PDUMP_DRIVER_READ   ReadRoutine;
    PDUMP_DRIVER_GET_TELEMETRY  GetDriveTelemetryRoutine;
    ULONG                       LogSectionTruncateSize;
    ULONG                       Parameters[DUMP_INIT_TC_MAX_PARAMS];
    PDUMP_DRIVER_GET_TRANSFER_SIZES GetTransferSizesRoutine;
    PDUMP_NOTIFY DumpNotifyRoutine;

} DUMP_INITIALIZATION_CONTEXT, *PDUMP_INITIALIZATION_CONTEXT;

typedef union _IO_LIVEDUMP_CONTROL_FLAGS {

    struct {
        ULONG UseDumpStorageStack: 1;
        ULONG CompressMemoryPagesData: 1;
        ULONG IncludeUserSpaceMemoryPages: 1;
        ULONG DeferDumpFileWrite: 1;
        ULONG AbortIfMemoryPressure : 1;
        ULONG Reserved: 27;
    };

    ULONG AsUlong;
} IO_LIVEDUMP_CONTROL_FLAGS, *PIO_LIVEDUMP_CONTROL_FLAGS;

typedef union _IO_LIVEDUMP_CONTROL_ADDPAGES {
    struct {
        ULONG HypervisorPages: 1;
        ULONG Reserved: 31;
    };
    ULONG AsUlong;
} IO_LIVEDUMP_CONTROL_ADDPAGES, *PIO_LIVEDUMP_CONTROL_ADDPAGES;

typedef struct _IO_LIVEDUMP_SECONDARY_DATA {
    GUID Identifier;
    PVOID Data;
    ULONG Size;
    ULONG Reserved;
    struct _IO_LIVEDUMP_SECONDARY_DATA *Next;
} IO_LIVEDUMP_SECONDARY_DATA, *PIO_LIVEDUMP_SECONDARY_DATA;

typedef struct _IO_LIVEDUMP_SECONDARY_DATA_HEADER {
    ULONG Flags;
    ULONG Reserved;
    PIO_LIVEDUMP_SECONDARY_DATA Data;
} IO_LIVEDUMP_SECONDARY_DATA_HEADER, *PIO_LIVEDUMP_SECONDARY_DATA_HEADER;

#define IO_LIVEDUMP_CONTROL_VERSION_1   (ULONG)1

typedef _Struct_size_bytes_(Size)
struct _IO_LIVEDUMP_CONTROL {
  ULONG Version;
  ULONG Size;
  HANDLE DumpFileHandle;
  PVOID CancelObject;
  IO_LIVEDUMP_CONTROL_FLAGS Flags;
  IO_LIVEDUMP_CONTROL_ADDPAGES AddPagesControl;
  IO_LIVEDUMP_SECONDARY_DATA_HEADER SecondaryData;
} IO_LIVEDUMP_CONTROL, *PIO_LIVEDUMP_CONTROL;

_At_(*LiveDumpContext, _When_(return == STATUS_MORE_PROCESSING_REQUIRED, _Out_))
_At_(*LiveDumpContext, _When_(return != STATUS_MORE_PROCESSING_REQUIRED, _Out_opt_))
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
IoCaptureLiveDump (
    _In_ ULONG BugcheckCode,
    _In_ ULONG_PTR BugCheckParameter1,
    _In_ ULONG_PTR BugCheckParameter2,
    _In_ ULONG_PTR BugCheckParameter3,
    _In_ ULONG_PTR BugCheckParameter4,
    _In_ PIO_LIVEDUMP_CONTROL Control,
    PVOID *LiveDumpContext
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
IoWriteDeferredLiveDumpData(
    _In_ PVOID LiveDumpContext
    );

_IRQL_requires_max_(APC_LEVEL)
NTSTATUS
IoDiscardDeferredLiveDumpData(
    _In_ PVOID LiveDumpContext
    );


typedef enum _IO_QUERY_DEVICE_DATA_FORMAT {
    IoQueryDeviceIdentifier = 0,
    IoQueryDeviceConfigurationData,
    IoQueryDeviceComponentInformation,
    IoQueryDeviceMaxData
} IO_QUERY_DEVICE_DATA_FORMAT, *PIO_QUERY_DEVICE_DATA_FORMAT;

typedef struct _NAMED_PIPE_CREATE_PARAMETERS {
    ULONG NamedPipeType;
    ULONG ReadMode;
    ULONG CompletionMode;
    ULONG MaximumInstances;
    ULONG InboundQuota;
    ULONG OutboundQuota;
    LARGE_INTEGER DefaultTimeout;
    BOOLEAN TimeoutSpecified;
} NAMED_PIPE_CREATE_PARAMETERS, *PNAMED_PIPE_CREATE_PARAMETERS;

typedef struct _MAILSLOT_CREATE_PARAMETERS {
    ULONG MailslotQuota;
    ULONG MaximumMessageSize;
    LARGE_INTEGER ReadTimeout;
    BOOLEAN TimeoutSpecified;
} MAILSLOT_CREATE_PARAMETERS, *PMAILSLOT_CREATE_PARAMETERS;

struct _DEVICE_DESCRIPTION;
struct _DEVICE_OBJECT;
struct _DMA_ADAPTER;
struct _DRIVER_OBJECT;
struct _DRIVE_LAYOUT_INFORMATION;
struct _DISK_PARTITION;

struct _FILE_OBJECT;

#if defined(_WIN64)
#define POINTER_ALIGNMENT DECLSPEC_ALIGN(8)
#else
#define POINTER_ALIGNMENT
#endif

struct DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT) _IRP;
struct _SCSI_REQUEST_BLOCK;
struct _SCATTER_GATHER_LIST;

_Function_class_(IO_DPC_ROUTINE)
_IRQL_always_function_min_(DISPATCH_LEVEL)
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_requires_same_
typedef
VOID
IO_DPC_ROUTINE (
    _In_ PKDPC Dpc,
    _In_ struct _DEVICE_OBJECT *DeviceObject,
    _Inout_ struct _IRP *Irp,
    _In_opt_ PVOID Context
    );

typedef IO_DPC_ROUTINE *PIO_DPC_ROUTINE;


_Function_class_(DRIVER_INITIALIZE)
_IRQL_requires_same_
_IRQL_requires_(PASSIVE_LEVEL)
typedef
NTSTATUS
DRIVER_INITIALIZE (
    _In_ struct _DRIVER_OBJECT *DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    );

typedef DRIVER_INITIALIZE *PDRIVER_INITIALIZE;



_Function_class_(DRIVER_DISPATCH)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
typedef
NTSTATUS
DRIVER_DISPATCH (
    _In_ struct _DEVICE_OBJECT *DeviceObject,
    _Inout_ struct _IRP *Irp
    );

typedef DRIVER_DISPATCH *PDRIVER_DISPATCH;

typedef DRIVER_DISPATCH DRIVER_DISPATCH_RAISED;

_Function_class_(DRIVER_DISPATCH)
_IRQL_requires_max_(PASSIVE_LEVEL)
_IRQL_requires_same_
typedef
NTSTATUS
DRIVER_DISPATCH_PAGED (
    _In_ struct _DEVICE_OBJECT *DeviceObject,
    _Inout_ struct _IRP *Irp
    );

typedef DRIVER_DISPATCH_PAGED *PDRIVER_DISPATCH_PAGED;

_Function_class_(DRIVER_STARTIO)
_IRQL_always_function_min_(DISPATCH_LEVEL)
_IRQL_requires_(DISPATCH_LEVEL)
_IRQL_requires_same_
typedef
VOID
DRIVER_STARTIO (
    _Inout_ struct _DEVICE_OBJECT *DeviceObject,
    _Inout_ struct _IRP *Irp
    );

typedef DRIVER_STARTIO *PDRIVER_STARTIO;

_Function_class_(DRIVER_UNLOAD)
_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
typedef
VOID
DRIVER_UNLOAD (
    _In_ struct _DRIVER_OBJECT *DriverObject
    );

typedef DRIVER_UNLOAD *PDRIVER_UNLOAD;

_Function_class_(DRIVER_ADD_DEVICE)
_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
_When_(return>=0, _Kernel_clear_do_init_(__yes))
typedef
NTSTATUS
DRIVER_ADD_DEVICE (
    _In_ struct _DRIVER_OBJECT *DriverObject,
    _In_ struct _DEVICE_OBJECT *PhysicalDeviceObject
    );

typedef DRIVER_ADD_DEVICE *PDRIVER_ADD_DEVICE;

_Function_class_(FAST_IO_CHECK_IF_POSSIBLE)
_IRQL_requires_same_
_Success_(return != FALSE)
typedef
BOOLEAN
FAST_IO_CHECK_IF_POSSIBLE (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _In_ ULONG LockKey,
    _In_ BOOLEAN CheckForReadOperation,
    _Pre_notnull_
    _When_(return != FALSE, _Post_equal_to_(_Old_(IoStatus)))
    _When_(return == FALSE, _Post_valid_)
    PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_CHECK_IF_POSSIBLE *PFAST_IO_CHECK_IF_POSSIBLE;

_Function_class_(FAST_IO_READ)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_READ (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _In_ ULONG LockKey,
    _Out_ PVOID Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_READ *PFAST_IO_READ;

_Function_class_(FAST_IO_WRITE)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_WRITE (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ BOOLEAN Wait,
    _In_ ULONG LockKey,
    _In_ PVOID Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_WRITE *PFAST_IO_WRITE;

_Function_class_(FAST_IO_QUERY_BASIC_INFO)
_IRQL_requires_same_
_Success_(return != FALSE)
typedef
BOOLEAN
FAST_IO_QUERY_BASIC_INFO (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ BOOLEAN Wait,
    _Out_ PFILE_BASIC_INFORMATION Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_QUERY_BASIC_INFO *PFAST_IO_QUERY_BASIC_INFO;

_Function_class_(FAST_IO_QUERY_STANDARD_INFO)
_IRQL_requires_same_
_Success_(return != FALSE)
typedef
BOOLEAN
FAST_IO_QUERY_STANDARD_INFO (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ BOOLEAN Wait,
    _Out_ PFILE_STANDARD_INFORMATION Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_QUERY_STANDARD_INFO *PFAST_IO_QUERY_STANDARD_INFO;

_Function_class_(FAST_IO_LOCK)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_LOCK (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ PEPROCESS ProcessId,
    _In_ ULONG Key,
    _In_ BOOLEAN FailImmediately,
    _In_ BOOLEAN ExclusiveLock,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_LOCK *PFAST_IO_LOCK;

_Function_class_(FAST_IO_UNLOCK_SINGLE)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_UNLOCK_SINGLE (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ PLARGE_INTEGER Length,
    _In_ PEPROCESS ProcessId,
    _In_ ULONG Key,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_UNLOCK_SINGLE *PFAST_IO_UNLOCK_SINGLE;

_Function_class_(FAST_IO_UNLOCK_ALL)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_UNLOCK_ALL (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PEPROCESS ProcessId,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_UNLOCK_ALL *PFAST_IO_UNLOCK_ALL;

_Function_class_(FAST_IO_UNLOCK_ALL_BY_KEY)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_UNLOCK_ALL_BY_KEY (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PVOID ProcessId,
    _In_ ULONG Key,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_UNLOCK_ALL_BY_KEY *PFAST_IO_UNLOCK_ALL_BY_KEY;

_Function_class_(FAST_IO_DEVICE_CONTROL)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_DEVICE_CONTROL (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ BOOLEAN Wait,
    _In_opt_ PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_opt_ PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _In_ ULONG IoControlCode,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_DEVICE_CONTROL *PFAST_IO_DEVICE_CONTROL;

_Function_class_(FAST_IO_ACQUIRE_FILE)
_IRQL_requires_same_
typedef
VOID
FAST_IO_ACQUIRE_FILE (
    _In_ struct _FILE_OBJECT *FileObject
    );

typedef FAST_IO_ACQUIRE_FILE *PFAST_IO_ACQUIRE_FILE;

_Function_class_(FAST_IO_RELEASE_FILE)
_IRQL_requires_same_
typedef
VOID
FAST_IO_RELEASE_FILE (
    _In_ struct _FILE_OBJECT *FileObject
    );

typedef FAST_IO_RELEASE_FILE *PFAST_IO_RELEASE_FILE;

_Function_class_(FAST_IO_DETACH_DEVICE)
_IRQL_requires_same_
typedef
VOID
FAST_IO_DETACH_DEVICE (
    _In_ struct _DEVICE_OBJECT *SourceDevice,
    _In_ struct _DEVICE_OBJECT *TargetDevice
    );

typedef FAST_IO_DETACH_DEVICE *PFAST_IO_DETACH_DEVICE;

_Function_class_(FAST_IO_QUERY_NETWORK_OPEN_INFO)
_IRQL_requires_same_
_Success_(return != FALSE)
typedef
BOOLEAN
FAST_IO_QUERY_NETWORK_OPEN_INFO (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ BOOLEAN Wait,
    _Out_ struct _FILE_NETWORK_OPEN_INFORMATION *Buffer,
    _Out_ struct _IO_STATUS_BLOCK *IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_QUERY_NETWORK_OPEN_INFO *PFAST_IO_QUERY_NETWORK_OPEN_INFO;

_Function_class_(FAST_IO_MDL_READ)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_MDL_READ (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG LockKey,
    _Out_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_READ *PFAST_IO_MDL_READ;

_Function_class_(FAST_IO_MDL_READ_COMPLETE)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_MDL_READ_COMPLETE (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PMDL MdlChain,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_READ_COMPLETE *PFAST_IO_MDL_READ_COMPLETE;

_Function_class_(FAST_IO_PREPARE_MDL_WRITE)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_PREPARE_MDL_WRITE (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG LockKey,
    _Out_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_PREPARE_MDL_WRITE *PFAST_IO_PREPARE_MDL_WRITE;

_Function_class_(FAST_IO_MDL_WRITE_COMPLETE)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_MDL_WRITE_COMPLETE (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ PMDL MdlChain,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_WRITE_COMPLETE *PFAST_IO_MDL_WRITE_COMPLETE;

_Function_class_(FAST_IO_ACQUIRE_FOR_MOD_WRITE)
_IRQL_requires_same_
typedef
NTSTATUS
FAST_IO_ACQUIRE_FOR_MOD_WRITE (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER EndingOffset,
    _Out_ struct _ERESOURCE **ResourceToRelease,
    _In_ struct _DEVICE_OBJECT *DeviceObject
             );

typedef FAST_IO_ACQUIRE_FOR_MOD_WRITE *PFAST_IO_ACQUIRE_FOR_MOD_WRITE;

_Function_class_(FAST_IO_RELEASE_FOR_MOD_WRITE)
_IRQL_requires_same_
typedef
NTSTATUS
FAST_IO_RELEASE_FOR_MOD_WRITE (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ struct _ERESOURCE *ResourceToRelease,
    _In_ struct _DEVICE_OBJECT *DeviceObject
             );

typedef FAST_IO_RELEASE_FOR_MOD_WRITE *PFAST_IO_RELEASE_FOR_MOD_WRITE;

_Function_class_(FAST_IO_ACQUIRE_FOR_CCFLUSH)
_IRQL_requires_same_
typedef
NTSTATUS
FAST_IO_ACQUIRE_FOR_CCFLUSH (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ struct _DEVICE_OBJECT *DeviceObject
             );

typedef FAST_IO_ACQUIRE_FOR_CCFLUSH *PFAST_IO_ACQUIRE_FOR_CCFLUSH;

_Function_class_(FAST_IO_RELEASE_FOR_CCFLUSH)
_IRQL_requires_same_
typedef
NTSTATUS
FAST_IO_RELEASE_FOR_CCFLUSH (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ struct _DEVICE_OBJECT *DeviceObject
             );

typedef FAST_IO_RELEASE_FOR_CCFLUSH *PFAST_IO_RELEASE_FOR_CCFLUSH;

_Function_class_(FAST_IO_READ_COMPRESSED)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_READ_COMPRESSED (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG LockKey,
    _Out_ PVOID Buffer,
    _Out_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _Out_ struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
    _In_ ULONG CompressedDataInfoLength,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_READ_COMPRESSED *PFAST_IO_READ_COMPRESSED;

_Function_class_(FAST_IO_WRITE_COMPRESSED)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_WRITE_COMPRESSED (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ ULONG Length,
    _In_ ULONG LockKey,
    _In_ PVOID Buffer,
    _Out_ PMDL *MdlChain,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    _In_ struct _COMPRESSED_DATA_INFO *CompressedDataInfo,
    _In_ ULONG CompressedDataInfoLength,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_WRITE_COMPRESSED *PFAST_IO_WRITE_COMPRESSED;

_Function_class_(FAST_IO_MDL_READ_COMPLETE_COMPRESSED)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_MDL_READ_COMPLETE_COMPRESSED (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PMDL MdlChain,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_READ_COMPLETE_COMPRESSED *PFAST_IO_MDL_READ_COMPLETE_COMPRESSED;

_Function_class_(FAST_IO_MDL_WRITE_COMPLETE_COMPRESSED)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_MDL_WRITE_COMPLETE_COMPRESSED (
    _In_ struct _FILE_OBJECT *FileObject,
    _In_ PLARGE_INTEGER FileOffset,
    _In_ PMDL MdlChain,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_MDL_WRITE_COMPLETE_COMPRESSED *PFAST_IO_MDL_WRITE_COMPLETE_COMPRESSED;

_Function_class_(FAST_IO_QUERY_OPEN)
_IRQL_requires_same_
typedef
BOOLEAN
FAST_IO_QUERY_OPEN (
    _Inout_ struct _IRP *Irp,
    _Out_ PFILE_NETWORK_OPEN_INFORMATION NetworkInformation,
    _In_ struct _DEVICE_OBJECT *DeviceObject
    );

typedef FAST_IO_QUERY_OPEN *PFAST_IO_QUERY_OPEN;

typedef struct _FAST_IO_DISPATCH {
    ULONG SizeOfFastIoDispatch;
    PFAST_IO_CHECK_IF_POSSIBLE FastIoCheckIfPossible;
    PFAST_IO_READ FastIoRead;
    PFAST_IO_WRITE FastIoWrite;
    PFAST_IO_QUERY_BASIC_INFO FastIoQueryBasicInfo;
    PFAST_IO_QUERY_STANDARD_INFO FastIoQueryStandardInfo;
    PFAST_IO_LOCK FastIoLock;
    PFAST_IO_UNLOCK_SINGLE FastIoUnlockSingle;
    PFAST_IO_UNLOCK_ALL FastIoUnlockAll;
    PFAST_IO_UNLOCK_ALL_BY_KEY FastIoUnlockAllByKey;
    PFAST_IO_DEVICE_CONTROL FastIoDeviceControl;
    PFAST_IO_ACQUIRE_FILE AcquireFileForNtCreateSection;
    PFAST_IO_RELEASE_FILE ReleaseFileForNtCreateSection;
    PFAST_IO_DETACH_DEVICE FastIoDetachDevice;
    PFAST_IO_QUERY_NETWORK_OPEN_INFO FastIoQueryNetworkOpenInfo;
    PFAST_IO_ACQUIRE_FOR_MOD_WRITE AcquireForModWrite;
    PFAST_IO_MDL_READ MdlRead;
    PFAST_IO_MDL_READ_COMPLETE MdlReadComplete;
    PFAST_IO_PREPARE_MDL_WRITE PrepareMdlWrite;
    PFAST_IO_MDL_WRITE_COMPLETE MdlWriteComplete;
    PFAST_IO_READ_COMPRESSED FastIoReadCompressed;
    PFAST_IO_WRITE_COMPRESSED FastIoWriteCompressed;
    PFAST_IO_MDL_READ_COMPLETE_COMPRESSED MdlReadCompleteCompressed;
    PFAST_IO_MDL_WRITE_COMPLETE_COMPRESSED MdlWriteCompleteCompressed;
    PFAST_IO_QUERY_OPEN FastIoQueryOpen;
    PFAST_IO_RELEASE_FOR_MOD_WRITE ReleaseForModWrite;
    PFAST_IO_ACQUIRE_FOR_CCFLUSH AcquireForCcFlush;
    PFAST_IO_RELEASE_FOR_CCFLUSH ReleaseForCcFlush;
} FAST_IO_DISPATCH, *PFAST_IO_DISPATCH;

typedef enum _IO_ALLOCATION_ACTION {
    KeepObject = 1,
    DeallocateObject,
    DeallocateObjectKeepRegisters
} IO_ALLOCATION_ACTION, *PIO_ALLOCATION_ACTION;

typedef
_Function_class_(DRIVER_CONTROL)
_IRQL_requires_same_
IO_ALLOCATION_ACTION
DRIVER_CONTROL (
    _In_ struct _DEVICE_OBJECT *DeviceObject,
    _Inout_ struct _IRP *Irp,
    _In_ PVOID MapRegisterBase,
    _In_ PVOID Context
    );
typedef DRIVER_CONTROL *PDRIVER_CONTROL;

typedef struct _IO_SECURITY_CONTEXT {
    PSECURITY_QUALITY_OF_SERVICE SecurityQos;
    PACCESS_STATE AccessState;
    ACCESS_MASK DesiredAccess;
    ULONG FullCreateOptions;
} IO_SECURITY_CONTEXT, *PIO_SECURITY_CONTEXT;

#define VPB_MOUNTED                     0x00000001
#define VPB_LOCKED                      0x00000002
#define VPB_PERSISTENT                  0x00000004
#define VPB_REMOVE_PENDING              0x00000008
#define VPB_RAW_MOUNT                   0x00000010
#define VPB_DIRECT_WRITES_ALLOWED       0x00000020




#if defined(_WIN64) || defined(_ARM_)

#ifndef USE_DMA_MACROS
#define USE_DMA_MACROS
#endif

#ifndef NO_LEGACY_DRIVERS
#define NO_LEGACY_DRIVERS
#endif

#endif // _WIN64

#if defined(USE_DMA_MACROS) && !defined(_NTHAL_) && ( defined(_NTDDK_) || defined(_NTDRIVER_) || defined(_NTOSP_))
typedef struct _DMA_ADAPTER *PADAPTER_OBJECT;
#elif defined(_WDM_INCLUDED_)
typedef struct _DMA_ADAPTER *PADAPTER_OBJECT;
#else
typedef struct _ADAPTER_OBJECT *PADAPTER_OBJECT; // ntndis
#endif // USE_DMA_MACROS && (_NTDDK_ || _NTDRIVER_ || _NTOSP_)

typedef struct _WAIT_CONTEXT_BLOCK {
    union {
        KDEVICE_QUEUE_ENTRY WaitQueueEntry;
        struct {
            LIST_ENTRY DmaWaitEntry;
            ULONG NumberOfChannels;
            ULONG SyncCallback : 1;
            ULONG DmaContext : 1;
            ULONG Reserved : 30;
        };
    };
    PDRIVER_CONTROL DeviceRoutine;
    PVOID DeviceContext;
    ULONG NumberOfMapRegisters;
    PVOID DeviceObject;
    PVOID CurrentIrp;
    PKDPC BufferChainingDpc;
} WAIT_CONTEXT_BLOCK, *PWAIT_CONTEXT_BLOCK;

typedef struct _CONTROLLER_OBJECT {
    CSHORT Type;
    CSHORT Size;
    PVOID ControllerExtension;
    KDEVICE_QUEUE DeviceWaitQueue;
    ULONG Spare1;
    LARGE_INTEGER Spare2;
} CONTROLLER_OBJECT, *PCONTROLLER_OBJECT;

#define DO_VERIFY_VOLUME                    0x00000002      // ntddk nthal ntifs wdm wudfpwdm
#define DO_BUFFERED_IO                      0x00000004      // ntddk nthal ntifs wdm wudfpwdm
#define DO_EXCLUSIVE                        0x00000008      // ntddk nthal ntifs wdm wudfpwdm
#define DO_DIRECT_IO                        0x00000010      // ntddk nthal ntifs wdm wudfpwdm
#define DO_MAP_IO_BUFFER                    0x00000020      // ntddk nthal ntifs wdm wudfpwdm
#define DO_DEVICE_HAS_NAME                  0x00000040      // ntddk nthal ntifs
#define DO_DEVICE_INITIALIZING              0x00000080      // ntddk nthal ntifs wdm wudfpwdm
#define DO_SYSTEM_BOOT_PARTITION            0x00000100      // ntddk nthal ntifs
#define DO_LONG_TERM_REQUESTS               0x00000200      // ntddk nthal ntifs
#define DO_HIGH_PRIORITY_FILESYSTEM         0x00000200      // ntosifs
#define DO_NEVER_LAST_DEVICE                0x00000400      // ntddk nthal ntifs
#define DO_SHUTDOWN_REGISTERED              0x00000800      // ntddk nthal ntifs wdm wudfpwdm
#define DO_BUS_ENUMERATED_DEVICE            0x00001000      // ntddk nthal ntifs wdm wudfpwdm
#define DO_POWER_PAGABLE                    0x00002000      // ntddk nthal ntifs wdm wudfpwdm
#define DO_POWER_INRUSH                     0x00004000      // ntddk nthal ntifs wdm wudfpwdm
#define DO_POWER_NOOP                       0x00008000
#define DO_LOW_PRIORITY_FILESYSTEM          0x00010000      // ntddk nthal ntifs
#define DO_SUPPORTS_PERSISTENT_ACLS         0x00020000      // ntifs
#define DO_SUPPORTS_TRANSACTIONS            0x00040000      // ntddk nthal ntifs
#define DO_FORCE_NEITHER_IO                 0x00080000      // ntddk nthal ntifs
#define DO_VOLUME_DEVICE_OBJECT             0x00100000      // ntddk nthal ntifs
#define DO_SYSTEM_SYSTEM_PARTITION          0x00200000      // ntddk nthal ntifs
#define DO_SYSTEM_CRITICAL_PARTITION        0x00400000      // ntddk nthal ntifs
#define DO_DISALLOW_EXECUTE                 0x00800000      // ntddk nthal ntifs
#define DO_PRIORITY_CALLBACK_ENABLED        0x01000000
#define DO_DEVICE_USED_BY_DEBUGGER          0x02000000
#define DO_DEVICE_TO_BE_RESET               0x04000000      // ntddk nthal ntifs wdm wudfpwdm

#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4324) // structure was padded due to __declspec(align())
#endif

typedef struct DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT) _DEVICE_OBJECT {
    CSHORT Type;
    USHORT Size;
    LONG ReferenceCount;
    struct _DRIVER_OBJECT *DriverObject;
    struct _DEVICE_OBJECT *NextDevice;
    struct _DEVICE_OBJECT *AttachedDevice;
    struct _IRP *CurrentIrp;
    PIO_TIMER Timer;
    ULONG Flags;                                // See above:  DO_...
    ULONG Characteristics;                      // See ntioapi:  FILE_...
    __volatile PVPB Vpb;
    PVOID DeviceExtension;
    DEVICE_TYPE DeviceType;
    CCHAR StackSize;
    union {
        LIST_ENTRY ListEntry;
        WAIT_CONTEXT_BLOCK Wcb;
    } Queue;
    ULONG AlignmentRequirement;
    KDEVICE_QUEUE DeviceQueue;
    KDPC Dpc;
    ULONG ActiveThreadCount;
    PSECURITY_DESCRIPTOR SecurityDescriptor;
    KEVENT DeviceLock;

    USHORT SectorSize;
    USHORT Spare1;

    struct _DEVOBJ_EXTENSION  *DeviceObjectExtension;
    PVOID  Reserved;

} DEVICE_OBJECT;

typedef struct _DEVICE_OBJECT *PDEVICE_OBJECT; // ntndis

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

struct  _DEVICE_OBJECT_POWER_EXTENSION;

typedef struct _DEVOBJ_EXTENSION {

    CSHORT          Type;
    USHORT          Size;
    PDEVICE_OBJECT  DeviceObject;               // owning device object
    ULONG           PowerFlags;                             // wdm
    struct          _DEVICE_OBJECT_POWER_EXTENSION  *Dope;  // wdm
    ULONG ExtensionFlags;                                   // wdm
    PVOID           DeviceNode;                             // wdm
    PDEVICE_OBJECT  AttachedTo;                             // wdm
    __volatile LONG StartIoCount;
    LONG           StartIoKey;                              // wdm
    ULONG          StartIoFlags;                            // wdm
    PVPB           Vpb;                                     // wdm
    PVOID DependencyNode;
    __volatile PVOID VerifierContext;
} DEVOBJ_EXTENSION, *PDEVOBJ_EXTENSION;

#define DRVO_UNLOAD_INVOKED             0x00000001
#define DRVO_LEGACY_DRIVER              0x00000002
#define DRVO_BUILTIN_DRIVER             0x00000004    // Driver objects for Hal, PnP Mgr
#define DRVO_REINIT_REGISTERED          0x00000008
#define DRVO_INITIALIZED                0x00000010
#define DRVO_BOOTREINIT_REGISTERED      0x00000020
#define DRVO_LEGACY_RESOURCES           0x00000040

typedef struct _DRIVER_EXTENSION {
    struct _DRIVER_OBJECT *DriverObject;
    PDRIVER_ADD_DEVICE AddDevice;
    ULONG Count;
    UNICODE_STRING ServiceKeyName;
} DRIVER_EXTENSION, *PDRIVER_EXTENSION;

typedef struct _DRIVER_OBJECT {
    CSHORT Type;
    CSHORT Size;
    PDEVICE_OBJECT DeviceObject;
    ULONG Flags;
    PVOID DriverStart;
    ULONG DriverSize;
    PVOID DriverSection;
    PDRIVER_EXTENSION DriverExtension;
    UNICODE_STRING DriverName;
    PUNICODE_STRING HardwareDatabase;
    PFAST_IO_DISPATCH FastIoDispatch;
    PDRIVER_INITIALIZE DriverInit;
    PDRIVER_STARTIO DriverStartIo;
    PDRIVER_UNLOAD DriverUnload;
    PDRIVER_DISPATCH MajorFunction[IRP_MJ_MAXIMUM_FUNCTION + 1];
} DRIVER_OBJECT;
typedef struct _DRIVER_OBJECT *PDRIVER_OBJECT; // ntndis

typedef struct _SECTION_OBJECT_POINTERS {
    PVOID DataSectionObject;
    PVOID SharedCacheMap;
    PVOID ImageSectionObject;
} SECTION_OBJECT_POINTERS;
typedef SECTION_OBJECT_POINTERS *PSECTION_OBJECT_POINTERS;

typedef struct _IO_COMPLETION_CONTEXT {
    PVOID Port;
    PVOID Key;
} IO_COMPLETION_CONTEXT, *PIO_COMPLETION_CONTEXT;

#define FO_FILE_OPEN                    0x00000001
#define FO_SYNCHRONOUS_IO               0x00000002
#define FO_ALERTABLE_IO                 0x00000004
#define FO_NO_INTERMEDIATE_BUFFERING    0x00000008
#define FO_WRITE_THROUGH                0x00000010
#define FO_SEQUENTIAL_ONLY              0x00000020
#define FO_CACHE_SUPPORTED              0x00000040
#define FO_NAMED_PIPE                   0x00000080
#define FO_STREAM_FILE                  0x00000100
#define FO_MAILSLOT                     0x00000200
#define FO_GENERATE_AUDIT_ON_CLOSE      0x00000400
#define FO_QUEUE_IRP_TO_THREAD          FO_GENERATE_AUDIT_ON_CLOSE
#define FO_DIRECT_DEVICE_OPEN           0x00000800
#define FO_FILE_MODIFIED                0x00001000
#define FO_FILE_SIZE_CHANGED            0x00002000
#define FO_CLEANUP_COMPLETE             0x00004000
#define FO_TEMPORARY_FILE               0x00008000
#define FO_DELETE_ON_CLOSE              0x00010000
#define FO_OPENED_CASE_SENSITIVE        0x00020000
#define FO_HANDLE_CREATED               0x00040000
#define FO_FILE_FAST_IO_READ            0x00080000
#define FO_RANDOM_ACCESS                0x00100000
#define FO_FILE_OPEN_CANCELLED          0x00200000
#define FO_VOLUME_OPEN                  0x00400000
#define FO_REMOTE_ORIGIN                0x01000000
#define FO_DISALLOW_EXCLUSIVE           0x02000000
#define FO_SKIP_COMPLETION_PORT         FO_DISALLOW_EXCLUSIVE
#define FO_SKIP_SET_EVENT               0x04000000
#define FO_SKIP_SET_FAST_IO             0x08000000
#define FO_INDIRECT_WAIT_OBJECT         0x10000000
#define FO_SECTION_MINSTORE_TREATMENT   0x20000000

#define FO_FLAGS_VALID_ONLY_DURING_CREATE FO_DISALLOW_EXCLUSIVE

#define FO_KEEPALIVE_COUNTS_ACTIVE      FO_SECTION_MINSTORE_TREATMENT

typedef struct _FILE_OBJECT {
    CSHORT Type;
    CSHORT Size;
    PDEVICE_OBJECT DeviceObject;
    PVPB Vpb;
    PVOID FsContext;
    PVOID FsContext2;
    PSECTION_OBJECT_POINTERS SectionObjectPointer;
    PVOID PrivateCacheMap;
    NTSTATUS FinalStatus;
    struct _FILE_OBJECT *RelatedFileObject;
    BOOLEAN LockOperation;
    BOOLEAN DeletePending;
    BOOLEAN ReadAccess;
    BOOLEAN WriteAccess;
    BOOLEAN DeleteAccess;
    BOOLEAN SharedRead;
    BOOLEAN SharedWrite;
    BOOLEAN SharedDelete;
    ULONG Flags;
    UNICODE_STRING FileName;
    LARGE_INTEGER CurrentByteOffset;
    __volatile ULONG Waiters;
    __volatile ULONG Busy;
    PVOID LastLock;
    KEVENT Lock;
    KEVENT Event;
    __volatile PIO_COMPLETION_CONTEXT CompletionContext;
    KSPIN_LOCK IrpListLock;
    LIST_ENTRY IrpList;
    __volatile PVOID FileObjectExtension;
} FILE_OBJECT;
typedef struct _FILE_OBJECT *PFILE_OBJECT; // ntndis

#define IRP_NOCACHE                     0x00000001
#define IRP_PAGING_IO                   0x00000002
#define IRP_MOUNT_COMPLETION            0x00000002
#define IRP_SYNCHRONOUS_API             0x00000004
#define IRP_ASSOCIATED_IRP              0x00000008
#define IRP_BUFFERED_IO                 0x00000010
#define IRP_DEALLOCATE_BUFFER           0x00000020
#define IRP_INPUT_OPERATION             0x00000040
#define IRP_SYNCHRONOUS_PAGING_IO       0x00000040
#define IRP_CREATE_OPERATION            0x00000080
#define IRP_READ_OPERATION              0x00000100
#define IRP_WRITE_OPERATION             0x00000200
#define IRP_CLOSE_OPERATION             0x00000400
#define IRP_DEFER_IO_COMPLETION         0x00000800
#define IRP_OB_QUERY_NAME               0x00001000
#define IRP_HOLD_DEVICE_QUEUE           0x00002000

#define IRP_UM_DRIVER_INITIATED_IO      0x00400000

#define IRP_QUOTA_CHARGED               0x01
#define IRP_ALLOCATED_MUST_SUCCEED      0x02
#define IRP_ALLOCATED_FIXED_SIZE        0x04
#define IRP_LOOKASIDE_ALLOCATION        0x08

#define IRP_BACKPOCKET_POSSIBLE         0x20
#define IRP_BACKPOCKET_IRP              (IRP_BACKPOCKET_POSSIBLE | IRP_QUOTA_CHARGED)
#define IRP_EXTENSION_ALLOCATED         0x40
#define IRP_EXTENSION_GENERIC_ONLY      0x80

typedef struct DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT) _IRP {
    CSHORT Type;
    USHORT Size;

#if defined(_WIN64)
    USHORT AllocationProcessorNumber;
    USHORT Reserved;
#endif
    PMDL MdlAddress;
    ULONG Flags;
    union {
        struct _IRP *MasterIrp;
        __volatile LONG IrpCount;
        PVOID SystemBuffer;
    } AssociatedIrp;
    LIST_ENTRY ThreadListEntry;
    IO_STATUS_BLOCK IoStatus;
    KPROCESSOR_MODE RequestorMode;
    BOOLEAN PendingReturned;
    CHAR StackCount;
    CHAR CurrentLocation;
    BOOLEAN Cancel;
    KIRQL CancelIrql;
    CCHAR ApcEnvironment;
    UCHAR AllocationFlags;
    PIO_STATUS_BLOCK UserIosb;
    PKEVENT UserEvent;
    union {
        struct {
            union {
                PIO_APC_ROUTINE UserApcRoutine;
                PVOID IssuingProcess;
            };
            PVOID UserApcContext;
        } AsynchronousParameters;
        LARGE_INTEGER AllocationSize;
    } Overlay;
    __volatile PDRIVER_CANCEL CancelRoutine;
    PVOID UserBuffer;
    union {
        struct {
            union {
                KDEVICE_QUEUE_ENTRY DeviceQueueEntry;
                struct {
                    PVOID DriverContext[4];
                } ;
            } ;
            PETHREAD Thread;
            PCHAR AuxiliaryBuffer;
            struct {
                LIST_ENTRY ListEntry;
                union {
                    struct _IO_STACK_LOCATION *CurrentStackLocation;
                    ULONG PacketType;
                };
            };
            PFILE_OBJECT OriginalFileObject;
            PVOID IrpExtension;
        } Overlay;

        KAPC Apc;
        PVOID CompletionKey;
    } Tail;
} IRP;

typedef IRP *PIRP;


#define SL_PENDING_RETURNED             0x01
#define SL_ERROR_RETURNED               0x02
#define SL_INVOKE_ON_CANCEL             0x20
#define SL_INVOKE_ON_SUCCESS            0x40
#define SL_INVOKE_ON_ERROR              0x80

#define SL_FORCE_ACCESS_CHECK           0x01
#define SL_OPEN_PAGING_FILE             0x02
#define SL_OPEN_TARGET_DIRECTORY        0x04
#define SL_STOP_ON_SYMLINK              0x08


#define SL_CASE_SENSITIVE               0x80

#define SL_KEY_SPECIFIED                0x01
#define SL_OVERRIDE_VERIFY_VOLUME       0x02
#define SL_WRITE_THROUGH                0x04
#define SL_FT_SEQUENTIAL_WRITE          0x08
#define SL_FORCE_DIRECT_WRITE           0x10
#define SL_REALTIME_STREAM              0x20

#define SL_READ_ACCESS_GRANTED          0x01
#define SL_WRITE_ACCESS_GRANTED         0x04    // Gap for SL_OVERRIDE_VERIFY_VOLUME

#define SL_FAIL_IMMEDIATELY             0x01
#define SL_EXCLUSIVE_LOCK               0x02

#define SL_RESTART_SCAN                 0x01
#define SL_RETURN_SINGLE_ENTRY          0x02
#define SL_INDEX_SPECIFIED              0x04

#define SL_WATCH_TREE                   0x01

#define SL_ALLOW_RAW_MOUNT              0x01

#define SL_BYPASS_ACCESS_CHECK          0x01

typedef struct _DEVICE_RELATIONS {
    ULONG Count;
    _Field_size_(Count) PDEVICE_OBJECT Objects[1];  // variable length
} DEVICE_RELATIONS, *PDEVICE_RELATIONS;

typedef enum _DEVICE_USAGE_NOTIFICATION_TYPE {
    DeviceUsageTypeUndefined,
    DeviceUsageTypePaging,
    DeviceUsageTypeHibernation,
    DeviceUsageTypeDumpFile,
    DeviceUsageTypeBoot,
    DeviceUsageTypePostDisplay
} DEVICE_USAGE_NOTIFICATION_TYPE;

#undef INTERFACE

typedef struct _INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
} INTERFACE, *PINTERFACE;

typedef _Struct_size_bytes_(Size) struct _DEVICE_CAPABILITIES {
    _Field_range_(==, sizeof(struct _DEVICE_CAPABILITIES)) USHORT Size;
    USHORT Version;
    ULONG DeviceD1:1;
    ULONG DeviceD2:1;
    ULONG LockSupported:1;
    ULONG EjectSupported:1;
    ULONG Removable:1;
    ULONG DockDevice:1;
    ULONG UniqueID:1;
    ULONG SilentInstall:1;
    ULONG RawDeviceOK:1;
    ULONG SurpriseRemovalOK:1;
    ULONG WakeFromD0:1;
    ULONG WakeFromD1:1;
    ULONG WakeFromD2:1;
    ULONG WakeFromD3:1;
    ULONG HardwareDisabled:1;
    ULONG NonDynamic:1;
    ULONG WarmEjectSupported:1;
    ULONG NoDisplayInUI:1;
    ULONG Reserved1:1;
    ULONG WakeFromInterrupt:1;
    ULONG Reserved:12;
    ULONG Address;
    ULONG UINumber;
    DEVICE_POWER_STATE DeviceState[POWER_SYSTEM_MAXIMUM];
    _Field_range_(PowerSystemUnspecified, PowerSystemHibernate) SYSTEM_POWER_STATE SystemWake;
    _Field_range_(PowerDeviceUnspecified, PowerDeviceD3) DEVICE_POWER_STATE DeviceWake;
    ULONG D1Latency;
    ULONG D2Latency;
    ULONG D3Latency;
} DEVICE_CAPABILITIES, *PDEVICE_CAPABILITIES;

typedef struct _POWER_SEQUENCE {
    ULONG SequenceD1;
    ULONG SequenceD2;
    ULONG SequenceD3;
} POWER_SEQUENCE, *PPOWER_SEQUENCE;

typedef enum {
    BusQueryDeviceID = 0,       // <Enumerator>\<Enumerator-specific device id>
    BusQueryHardwareIDs = 1,    // Hardware ids
    BusQueryCompatibleIDs = 2,  // compatible device ids
    BusQueryInstanceID = 3,     // persistent id for this instance of the device
    BusQueryDeviceSerialNumber = 4,   // serial number for this device
    BusQueryContainerID = 5     // unique id of the device's physical container
} BUS_QUERY_ID_TYPE, *PBUS_QUERY_ID_TYPE;

typedef ULONG PNP_DEVICE_STATE, *PPNP_DEVICE_STATE;

#define PNP_DEVICE_DISABLED                      0x00000001
#define PNP_DEVICE_DONT_DISPLAY_IN_UI            0x00000002
#define PNP_DEVICE_FAILED                        0x00000004
#define PNP_DEVICE_REMOVED                       0x00000008
#define PNP_DEVICE_RESOURCE_REQUIREMENTS_CHANGED 0x00000010
#define PNP_DEVICE_NOT_DISABLEABLE               0x00000020
#define PNP_DEVICE_DISCONNECTED                  0x00000040

typedef enum {
    DeviceTextDescription = 0,            // DeviceDesc property
    DeviceTextLocationInformation = 1     // DeviceLocation property
} DEVICE_TEXT_TYPE, *PDEVICE_TEXT_TYPE;

#if !defined(_AMD64_) && !defined(_ARM_) && !defined(_ARM64_)
#include "pshpack4.h"
#endif

#if defined(_WIN64)
#define POINTER_ALIGNMENT DECLSPEC_ALIGN(8)
#else
#define POINTER_ALIGNMENT
#endif

#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4324) // structure was padded due to __declspec(align())
#endif

typedef struct _IO_STACK_LOCATION {
    UCHAR MajorFunction;
    UCHAR MinorFunction;
    UCHAR Flags;
    UCHAR Control;

    union
    {
        struct
        {
            PIO_SECURITY_CONTEXT SecurityContext;
            ULONG Options;
            USHORT POINTER_ALIGNMENT FileAttributes;
            USHORT ShareAccess;
            ULONG POINTER_ALIGNMENT EaLength;
        } Create;

        struct
        {
            PIO_SECURITY_CONTEXT SecurityContext;
            ULONG Options;
            USHORT POINTER_ALIGNMENT Reserved;
            USHORT ShareAccess;
            PNAMED_PIPE_CREATE_PARAMETERS Parameters;
        } CreatePipe;

        struct
        {
            PIO_SECURITY_CONTEXT SecurityContext;
            ULONG Options;
            USHORT POINTER_ALIGNMENT Reserved;
            USHORT ShareAccess;
            PMAILSLOT_CREATE_PARAMETERS Parameters;
        } CreateMailslot;

        struct
        {
            ULONG Length;
            ULONG POINTER_ALIGNMENT Key;
            LARGE_INTEGER ByteOffset;
        } Read;

        struct
        {
            ULONG Length;
            ULONG POINTER_ALIGNMENT Key;
            LARGE_INTEGER ByteOffset;
        } Write;

        struct
        {
            ULONG Length;
            PUNICODE_STRING FileName;
            FILE_INFORMATION_CLASS FileInformationClass;
            ULONG POINTER_ALIGNMENT FileIndex;
        } QueryDirectory;

        struct
        {
            ULONG Length;
            ULONG POINTER_ALIGNMENT CompletionFilter;
        } NotifyDirectory;

        struct
        {
            ULONG Length;
            FILE_INFORMATION_CLASS POINTER_ALIGNMENT FileInformationClass;
        } QueryFile;

        struct
        {
            ULONG Length;
            FILE_INFORMATION_CLASS POINTER_ALIGNMENT FileInformationClass;
            PFILE_OBJECT FileObject;
            union {
                struct {
                    BOOLEAN ReplaceIfExists;
                    BOOLEAN AdvanceOnly;
                };
                ULONG ClusterCount;
                HANDLE DeleteHandle;
            };
        } SetFile;

        struct
        {
            ULONG Length;
            FS_INFORMATION_CLASS POINTER_ALIGNMENT FsInformationClass;
        } QueryVolume;

        struct
        {
            ULONG OutputBufferLength;
            ULONG POINTER_ALIGNMENT InputBufferLength;
            ULONG POINTER_ALIGNMENT FsControlCode;
            PVOID Type3InputBuffer;
        } FileSystemControl;

        struct
        {
            PLARGE_INTEGER Length;
            ULONG POINTER_ALIGNMENT Key;
            LARGE_INTEGER ByteOffset;
        } LockControl;

        struct
        {
            ULONG OutputBufferLength;
            ULONG POINTER_ALIGNMENT InputBufferLength;
            ULONG POINTER_ALIGNMENT IoControlCode;
            PVOID Type3InputBuffer;
        } DeviceIoControl;

        struct
        {
            SECURITY_INFORMATION SecurityInformation;
            ULONG POINTER_ALIGNMENT Length;
        } QuerySecurity;

        struct
        {
            SECURITY_INFORMATION SecurityInformation;
            PSECURITY_DESCRIPTOR SecurityDescriptor;
        } SetSecurity;

        struct
        {
            PVPB Vpb;
            PDEVICE_OBJECT DeviceObject;
        } MountVolume;

        struct
        {
            PVPB Vpb;
            PDEVICE_OBJECT DeviceObject;
        } VerifyVolume;

        struct
        {
            struct _SCSI_REQUEST_BLOCK *Srb;
        } Scsi;

        struct
        {
            DEVICE_RELATION_TYPE Type;
        } QueryDeviceRelations;

        struct
        {
            CONST GUID *InterfaceType;
            USHORT Size;
            USHORT Version;
            PINTERFACE Interface;
            PVOID InterfaceSpecificData;
        } QueryInterface;

        struct
        {
            PDEVICE_CAPABILITIES Capabilities;
        } DeviceCapabilities;

        struct
        {
            PIO_RESOURCE_REQUIREMENTS_LIST IoResourceRequirementList;
        } FilterResourceRequirements;

        struct
        {
            ULONG WhichSpace;
            PVOID Buffer;
            ULONG Offset;
            ULONG POINTER_ALIGNMENT Length;
        } ReadWriteConfig;

        struct
        {
            BOOLEAN Lock;
        } SetLock;

        struct
        {
            BUS_QUERY_ID_TYPE IdType;
        } QueryId;

        struct
        {
            DEVICE_TEXT_TYPE DeviceTextType;
            LCID POINTER_ALIGNMENT LocaleId;
        } QueryDeviceText;

        struct
        {
            BOOLEAN InPath;
            BOOLEAN Reserved[3];
            DEVICE_USAGE_NOTIFICATION_TYPE POINTER_ALIGNMENT Type;
        } UsageNotification;

        struct
        {
            SYSTEM_POWER_STATE PowerState;
        } WaitWake;

        struct
        {
            PPOWER_SEQUENCE PowerSequence;
        } PowerSequence;

#if (NTDDI_VERSION >= NTDDI_VISTA)
        struct
        {
            union
            {
                ULONG SystemContext;
                SYSTEM_POWER_STATE_CONTEXT SystemPowerStateContext;
            };
            POWER_STATE_TYPE POINTER_ALIGNMENT Type;
            POWER_STATE POINTER_ALIGNMENT State;
            POWER_ACTION POINTER_ALIGNMENT ShutdownType;
        } Power;
#else
        struct {
            ULONG SystemContext;
            POWER_STATE_TYPE POINTER_ALIGNMENT Type;
            POWER_STATE POINTER_ALIGNMENT State;
            POWER_ACTION POINTER_ALIGNMENT ShutdownType;
        } Power;
#endif // (NTDDI_VERSION >= NTDDI_VISTA)

        struct
        {
            PCM_RESOURCE_LIST AllocatedResources;
            PCM_RESOURCE_LIST AllocatedResourcesTranslated;
        } StartDevice;
        struct
        {
            ULONG_PTR ProviderId;
            PVOID DataPath;
            ULONG BufferSize;
            PVOID Buffer;
        } WMI;
        struct
        {
            PVOID Argument1;
            PVOID Argument2;
            PVOID Argument3;
            PVOID Argument4;
        } Others;
    } Parameters;
    PDEVICE_OBJECT DeviceObject;
    PFILE_OBJECT FileObject;
    PIO_COMPLETION_ROUTINE CompletionRoutine;
    PVOID Context;
} IO_STACK_LOCATION, *PIO_STACK_LOCATION;

#if !defined(_AMD64_) && !defined(_ARM_) && !defined(_ARM64_)
#include "poppack.h"
#endif


#if !(defined(USE_DMA_MACROS) && (defined(_NTDDK_) || defined(_NTDRIVER_)) || defined(_WDM_INCLUDED_))

#endif // !(defined(USE_DMA_MACROS) && (defined(_NTDDK_) || defined(_NTDRIVER_)) || defined(_WDM_INCLUDED_))

typedef struct _BOOTDISK_INFORMATION_EX {
    LONGLONG BootPartitionOffset;
    LONGLONG SystemPartitionOffset;
    ULONG BootDeviceSignature;
    ULONG SystemDeviceSignature;
    GUID BootDeviceGuid;
    GUID SystemDeviceGuid;
    BOOLEAN BootDeviceIsGpt;
    BOOLEAN SystemDeviceIsGpt;
} BOOTDISK_INFORMATION_EX, *PBOOTDISK_INFORMATION_EX;


#define IoCallDriver(a,b)   \
        IofCallDriver(a,b)

#define STATUS_CONTINUE_COMPLETION      STATUS_SUCCESS  // wudfpwdm

typedef enum _IO_COMPLETION_ROUTINE_RESULT {

    ContinueCompletion = STATUS_CONTINUE_COMPLETION,
    StopCompletion = STATUS_MORE_PROCESSING_REQUIRED
} IO_COMPLETION_ROUTINE_RESULT, *PIO_COMPLETION_ROUTINE_RESULT;

#define IoCompleteRequest(a,b)  \
        IofCompleteRequest(a,b)





#define CONNECT_FULLY_SPECIFIED         0x1
#define CONNECT_LINE_BASED              0x2
#define CONNECT_MESSAGE_BASED           0x3
#define CONNECT_FULLY_SPECIFIED_GROUP   0x4
#define CONNECT_CURRENT_VERSION         0x4

#define WDM_MAJORVERSION        0x06
#define WDM_MINORVERSION        0x00

#define IoDeassignArcName( ArcName ) (  \
    IoDeleteSymbolicLink( (ArcName) ) )


FORCEINLINE
__drv_aliasesMem
PIO_STACK_LOCATION
IoGetCurrentIrpStackLocation(
    _In_ PIRP Irp)
{
    NT_ASSERT(Irp->CurrentLocation <= Irp->StackCount + 1);
    return Irp->Tail.Overlay.CurrentStackLocation;
}

#define IoGetFunctionCodeFromCtlCode( ControlCode ) (\
    ( ControlCode >> 2) & 0x00000FFF )

// ntosp.h
NTKERNELAPI
NTSTATUS
FASTCALL
IoCallDriverStackSafe(
    _In_ PDEVICE_OBJECT DeviceObject,
    _Inout_ PIRP Irp,
    _In_ ULONG StackThreshold,
    _In_ ULONG FailIfNoSwitch
    );

#define IoCallDriverStackSafeDefault(a, b) IoCallDriver(a, b)

_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
ULONG_PTR
IoGetRemainingStackSize (
    VOID)
{
    ULONG_PTR Top;
    ULONG_PTR Bottom;
    IoGetStackLimits( &Bottom, &Top );
    return((ULONG_PTR)(&Top) - Bottom );
}

FORCEINLINE
__drv_aliasesMem
PIO_STACK_LOCATION
IoGetNextIrpStackLocation(
    _In_ PIRP Irp)
{
    NT_ASSERT(Irp->CurrentLocation > 0);
    return ((Irp)->Tail.Overlay.CurrentStackLocation - 1 );
}

// ntosp.h
VOID
FORCEINLINE
IoInitializeDpcRequest(
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIO_DPC_ROUTINE DpcRoutine
    )
{
    KeInitializeDpc( &DeviceObject->Dpc,
#pragma warning (suppress: 28024) // implementation of the required way
                     (PKDEFERRED_ROUTINE) DpcRoutine,
                     DeviceObject );
}

// ntosp.h
VOID
FORCEINLINE
IoInitializeThreadedDpcRequest(
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PIO_DPC_ROUTINE DpcRoutine)
{
#pragma warning (suppress: 28128) // implementation of the required way
    KeInitializeThreadedDpc( &DeviceObject->Dpc,
#pragma warning (suppress: 28165 28024) // implementation of the required way
                             (PKDEFERRED_ROUTINE) DpcRoutine,
                             DeviceObject );
}

#define IoIsErrorUserInduced( Status ) ((BOOLEAN)  \
    (((Status) == STATUS_DEVICE_NOT_READY) ||      \
     ((Status) == STATUS_IO_TIMEOUT) ||            \
     ((Status) == STATUS_MEDIA_WRITE_PROTECTED) || \
     ((Status) == STATUS_NO_MEDIA_IN_DEVICE) ||    \
     ((Status) == STATUS_VERIFY_REQUIRED) ||       \
     ((Status) == STATUS_UNRECOGNIZED_MEDIA) ||    \
     ((Status) == STATUS_WRONG_VOLUME)))

// ntosp.h
FORCEINLINE
VOID
IoMarkIrpPending(
    _Inout_ PIRP Irp)
{
    IoGetCurrentIrpStackLocation( (Irp) )->Control |= SL_PENDING_RETURNED;
}

// ntosp.h
FORCEINLINE
VOID
IoRequestDpc(
    _Inout_  PDEVICE_OBJECT DeviceObject,
    _In_opt_ PIRP Irp,
    _In_opt_ __drv_aliasesMem PVOID Context)
{
    KeInsertQueueDpc( &DeviceObject->Dpc, Irp, Context );
}

#if !defined(NONTOSPINTERLOCK)
_IRQL_requires_max_(DISPATCH_LEVEL)
_Ret_maybenull_
FORCEINLINE
PDRIVER_CANCEL
IoSetCancelRoutine(
    _Inout_  PIRP Irp,
    _In_opt_ PDRIVER_CANCEL CancelRoutine)
{
    return (PDRIVER_CANCEL)(ULONG_PTR) InterlockedExchangePointer((PVOID *)&(Irp)->CancelRoutine, (PVOID)(ULONG_PTR)(CancelRoutine) );
}
#endif // !defined(NONTOSPINTERLOCK)

_IRQL_requires_max_(DISPATCH_LEVEL)
FORCEINLINE
VOID
IoSetCompletionRoutine(
    _In_ PIRP Irp,
    _In_opt_ PIO_COMPLETION_ROUTINE CompletionRoutine,
    _In_opt_ __drv_aliasesMem PVOID Context,
    _In_ BOOLEAN InvokeOnSuccess,
    _In_ BOOLEAN InvokeOnError,
    _In_ BOOLEAN InvokeOnCancel
    )
{
    PIO_STACK_LOCATION irpSp;
    NT_ASSERT( (InvokeOnSuccess || InvokeOnError || InvokeOnCancel) ? (CompletionRoutine != NULL) : TRUE );
    irpSp = IoGetNextIrpStackLocation(Irp);
    irpSp->CompletionRoutine = CompletionRoutine;
    irpSp->Context = Context;
    irpSp->Control = 0;

    if (InvokeOnSuccess) {
        irpSp->Control = SL_INVOKE_ON_SUCCESS;
    }

    if (InvokeOnError) {
        irpSp->Control |= SL_INVOKE_ON_ERROR;
    }

    if (InvokeOnCancel) {
        irpSp->Control |= SL_INVOKE_ON_CANCEL;
    }
}

FORCEINLINE
VOID
IoSetNextIrpStackLocation (
   _Inout_ PIRP Irp
    )
{
    NT_ASSERT(Irp->CurrentLocation > 0);
    Irp->CurrentLocation--;
    Irp->Tail.Overlay.CurrentStackLocation--;
}

FORCEINLINE
VOID
IoCopyCurrentIrpStackLocationToNext(
    _Inout_ PIRP Irp)
{
    PIO_STACK_LOCATION irpSp;
    PIO_STACK_LOCATION nextIrpSp;
    irpSp = IoGetCurrentIrpStackLocation(Irp);
    nextIrpSp = IoGetNextIrpStackLocation(Irp);
    RtlCopyMemory( nextIrpSp, irpSp, FIELD_OFFSET(IO_STACK_LOCATION, CompletionRoutine));
    nextIrpSp->Control = 0;
}

FORCEINLINE
VOID
IoSkipCurrentIrpStackLocation (
    _Inout_ PIRP Irp)
{
    NT_ASSERT(Irp->CurrentLocation <= Irp->StackCount);
    Irp->CurrentLocation++;
    Irp->Tail.Overlay.CurrentStackLocation++;
}

#define IoInitializeRemoveLock(Lock, Tag, Maxmin, HighWater) \
        IoInitializeRemoveLockEx (Lock, Tag, Maxmin, HighWater, sizeof (IO_REMOVE_LOCK))

#if DBG
#define IoAcquireRemoveLock(RemoveLock, Tag) \
        IoAcquireRemoveLockEx(RemoveLock, Tag, __FILE__, __LINE__, sizeof (IO_REMOVE_LOCK))
#else
#define IoAcquireRemoveLock(RemoveLock, Tag) \
        IoAcquireRemoveLockEx(RemoveLock, Tag, "", 1, sizeof (IO_REMOVE_LOCK))
#endif

#define IoReleaseRemoveLock(RemoveLock, Tag) \
        IoReleaseRemoveLockEx(RemoveLock, Tag, sizeof (IO_REMOVE_LOCK))


#define IoReleaseRemoveLockAndWait(RemoveLock, Tag) \
        IoReleaseRemoveLockAndWaitEx(RemoveLock, Tag, sizeof (IO_REMOVE_LOCK))


#define IoSizeOfIrp( StackSize ) \
    ((USHORT) (sizeof( IRP ) + ((StackSize) * (sizeof( IO_STACK_LOCATION )))))




#define WMIREG_ACTION_REGISTER      1
#define WMIREG_ACTION_DEREGISTER    2
#define WMIREG_ACTION_REREGISTER    3
#define WMIREG_ACTION_UPDATE_GUIDS  4
#define WMIREG_ACTION_BLOCK_IRPS    5

#define WMIREGISTER                 0
#define WMIUPDATE                   1

typedef
_Function_class_(WMI_NOTIFICATION_CALLBACK)
_IRQL_requires_same_
VOID FWMI_NOTIFICATION_CALLBACK (
    PVOID Wnode,
    PVOID Context
    );
typedef FWMI_NOTIFICATION_CALLBACK *WMI_NOTIFICATION_CALLBACK;

// ntosp.h
NTKERNELAPI
NTSTATUS
IoUpdateDiskGeometry(
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ struct _DISK_GEOMETRY_EX* OldDiskGeometry,
    _In_ struct _DISK_GEOMETRY_EX* NewDiskGeometry
    );

#define IO_TYPE_CSQ_IRP_CONTEXT 1
#define IO_TYPE_CSQ             2
#define IO_TYPE_CSQ_EX          3


typedef struct _IO_CSQ {
    ULONG                            Type;
    PIO_CSQ_INSERT_IRP               CsqInsertIrp;
    PIO_CSQ_REMOVE_IRP               CsqRemoveIrp;
    PIO_CSQ_PEEK_NEXT_IRP            CsqPeekNextIrp;
    PIO_CSQ_ACQUIRE_LOCK             CsqAcquireLock;
    PIO_CSQ_RELEASE_LOCK             CsqReleaseLock;
    PIO_CSQ_COMPLETE_CANCELED_IRP    CsqCompleteCanceledIrp;
    PVOID                            ReservePointer;    // Future expansion
} IO_CSQ, *PIO_CSQ;

typedef struct _TXN_PARAMETER_BLOCK {

    USHORT Length;
    USHORT TxFsContext;
    PVOID  TransactionObject;
} TXN_PARAMETER_BLOCK, *PTXN_PARAMETER_BLOCK;

#define TXF_MINIVERSION_DEFAULT_VIEW        (0xFFFE)

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

typedef struct _CREATE_USER_PROCESS_ECP_CONTEXT
{
    USHORT Size;
    USHORT Reserved;
    PACCESS_TOKEN AccessToken;
} CREATE_USER_PROCESS_ECP_CONTEXT, *PCREATE_USER_PROCESS_ECP_CONTEXT;

// {E0E429FF-6DDC-4E65-AAB6-45D05A038A08}
DEFINE_GUID(GUID_ECP_CREATE_USER_PROCESS, 0xe0e429ff, 0x6ddc, 0x4e65, 0xaa, 0xb6, 0x45, 0xd0, 0x5a, 0x3, 0x8a, 0x8);

#endif // NTDDI_VERSION >= NTDDI_WINTHRESHOLD

#define OPLOCK_KEY_VERSION_WIN7     0x0001
#define OPLOCK_KEY_VERSION_WIN8     0x0002

#define OPLOCK_KEY_FLAG_PARENT_KEY  0x0001
#define OPLOCK_KEY_FLAG_TARGET_KEY  0x0002


VOID
FORCEINLINE
IoInitializeDriverCreateContext(
    PIO_DRIVER_CREATE_CONTEXT DriverContext
    )
{
    // Initialize the context
    RtlZeroMemory(DriverContext, sizeof(IO_DRIVER_CREATE_CONTEXT));
    DriverContext->Size = sizeof(IO_DRIVER_CREATE_CONTEXT);
}

typedef enum _IO_ACCESS_TYPE {
    ReadAccess,
    WriteAccess,
    ModifyAccess
} IO_ACCESS_TYPE;

typedef enum _IO_ACCESS_MODE {
    SequentialAccess,
    RandomAccess
} IO_ACCESS_MODE;

typedef struct _IO_SESSION_STATE_NOTIFICATION {
    ULONG Size;
    ULONG Flags;
    PVOID IoObject;
    ULONG EventMask;
    PVOID Context;
} IO_SESSION_STATE_NOTIFICATION, *PIO_SESSION_STATE_NOTIFICATION;

typedef struct _IO_SESSION_STATE_INFORMATION {
    ULONG SessionId;
    IO_SESSION_STATE SessionState;
    BOOLEAN LocalSession;
} IO_SESSION_STATE_INFORMATION, *PIO_SESSION_STATE_INFORMATION;


typedef
NTSTATUS
IO_SESSION_NOTIFICATION_FUNCTION (
    _In_ PVOID SessionObject,
    _In_ PVOID IoObject,
    _In_ ULONG Event,
    _In_ PVOID Context,
    _In_reads_bytes_opt_(PayloadLength) PVOID NotificationPayload,
    _In_ ULONG PayloadLength
    );

typedef IO_SESSION_NOTIFICATION_FUNCTION *PIO_SESSION_NOTIFICATION_FUNCTION;



VOID
FORCEINLINE
IoInitializePriorityInfo(
    _Out_ PIO_PRIORITY_INFO PriorityInfo
    )
{
    PriorityInfo->Size = sizeof(IO_PRIORITY_INFO);
    PriorityInfo->ThreadPriority = 0xffff;
    PriorityInfo->IoPriority = IoPriorityNormal;
    PriorityInfo->PagePriority = 0;
}

#define BDCB_IMAGEFLAGS_FAILED_CODE_INTEGRITY   (1UL << 0)

typedef enum _BDCB_CALLBACK_TYPE {
    BdCbStatusUpdate,
    BdCbInitializeImage,
} BDCB_CALLBACK_TYPE, *PBDCB_CALLBACK_TYPE;

typedef enum _BDCB_CLASSIFICATION {
    BdCbClassificationUnknownImage,
    BdCbClassificationKnownGoodImage,
    BdCbClassificationKnownBadImage,
    BdCbClassificationKnownBadImageBootCritical,
    BdCbClassificationEnd,
} BDCB_CLASSIFICATION, *PBDCB_CLASSIFICATION;

typedef enum _BDCB_STATUS_UPDATE_TYPE {
    BdCbStatusPrepareForDependencyLoad,
    BdCbStatusPrepareForDriverLoad,
    BdCbStatusPrepareForUnload,
} BDCB_STATUS_UPDATE_TYPE, *PBDCB_STATUS_UPDATE_TYPE;

typedef struct _BDCB_STATUS_UPDATE_CONTEXT {
    BDCB_STATUS_UPDATE_TYPE StatusType;
} BDCB_STATUS_UPDATE_CONTEXT, *PBDCB_STATUS_UPDATE_CONTEXT;

typedef struct _BDCB_IMAGE_INFORMATION {
    BDCB_CLASSIFICATION Classification;
    ULONG ImageFlags;
    UNICODE_STRING ImageName;
    UNICODE_STRING RegistryPath;
    UNICODE_STRING CertificatePublisher;
    UNICODE_STRING CertificateIssuer;
    PVOID ImageHash;
    PVOID CertificateThumbprint;
    ULONG ImageHashAlgorithm;
    ULONG ThumbprintHashAlgorithm;
    ULONG ImageHashLength;
    ULONG CertificateThumbprintLength;
} BDCB_IMAGE_INFORMATION, *PBDCB_IMAGE_INFORMATION;

typedef
VOID
BOOT_DRIVER_CALLBACK_FUNCTION (
    _In_opt_ PVOID CallbackContext,
    _In_ BDCB_CALLBACK_TYPE Classification,
    _Inout_ PBDCB_IMAGE_INFORMATION ImageInformation
    );

typedef BOOT_DRIVER_CALLBACK_FUNCTION *PBOOT_DRIVER_CALLBACK_FUNCTION;

#define IO_IRPEXT_PROPAGATE_GENERIC         0x00000001
#define IO_IRPEXT_PROPAGATE_ACTIVITY_ID     0x00000002
#define IO_IRPEXT_PROPAGATE_TRACKED_OFFSET  0x00000004

#define IO_IRPEXT_PROPAGATE_ALL             0xffffffff      //Drivers should use this unless there is a specific reason to not propagate everything

NTSTATUS
IoGetFsZeroingOffset (
    _In_ PIRP Irp,
    _Out_ PULONG ZeroingOffset
    );

NTSTATUS
IoSetFsZeroingOffsetRequired (
    _Inout_ PIRP Irp
    );

NTSTATUS
IoSetFsZeroingOffset (
    _Inout_ PIRP Irp,
    _In_ ULONG ZeroingOffset
    );

#ifndef _IO_IRP_EXT_TRACK_OFFSET_HEADER_
#define _IO_IRP_EXT_TRACK_OFFSET_HEADER_

struct _IO_IRP_EXT_TRACK_OFFSET_HEADER;


#define IRP_EXT_TRACK_OFFSET_HEADER_VALIDATION_VALUE 'TO'

#define EFS_TRACKED_OFFSET_HEADER_FLAG 0x0001 //EFS Flag

#endif // _IO_IRP_EXT_TRACK_OFFSET_HEADER_

typedef
_Function_class_(TRANSLATE_BUS_ADDRESS)
_IRQL_requires_same_
_Success_(return)
BOOLEAN TRANSLATE_BUS_ADDRESS(
    _Inout_opt_ PVOID Context,
    _In_ PHYSICAL_ADDRESS BusAddress,
    _In_ ULONG Length,
    _Out_ PULONG AddressSpace,
    _Out_ PPHYSICAL_ADDRESS TranslatedAddress
    );
typedef TRANSLATE_BUS_ADDRESS *PTRANSLATE_BUS_ADDRESS;

typedef
_Function_class_(GET_DMA_ADAPTER)
_IRQL_requires_same_
struct _DMA_ADAPTER *GET_DMA_ADAPTER(
    _Inout_opt_ PVOID Context,
    _In_ struct _DEVICE_DESCRIPTION *DeviceDescriptor,
    _Out_ PULONG NumberOfMapRegisters
    );
typedef GET_DMA_ADAPTER *PGET_DMA_ADAPTER;

typedef
_Function_class_(GET_SET_DEVICE_DATA)
_IRQL_requires_same_
ULONG GET_SET_DEVICE_DATA (
    _Inout_opt_ PVOID Context,
    _In_ ULONG DataType,
    _Inout_updates_bytes_(Length) PVOID Buffer,
    _In_ ULONG Offset,
    _In_range_(!=,0) ULONG Length
    );
typedef GET_SET_DEVICE_DATA *PGET_SET_DEVICE_DATA;

typedef enum _DEVICE_INSTALL_STATE {
    InstallStateInstalled,
    InstallStateNeedsReinstall,
    InstallStateFailedInstall,
    InstallStateFinishInstall
} DEVICE_INSTALL_STATE, *PDEVICE_INSTALL_STATE;

typedef struct _PNP_BUS_INFORMATION {
    GUID BusTypeGuid;
    INTERFACE_TYPE LegacyBusType;
    ULONG BusNumber;
} PNP_BUS_INFORMATION, *PPNP_BUS_INFORMATION;

typedef struct _LEGACY_BUS_INFORMATION {
    GUID BusTypeGuid;
    INTERFACE_TYPE LegacyBusType;
    ULONG BusNumber;
} LEGACY_BUS_INFORMATION, *PLEGACY_BUS_INFORMATION;

typedef enum _DEVICE_REMOVAL_POLICY {

    RemovalPolicyExpectNoRemoval = 1,
    RemovalPolicyExpectOrderlyRemoval = 2,
    RemovalPolicyExpectSurpriseRemoval = 3

} DEVICE_REMOVAL_POLICY, *PDEVICE_REMOVAL_POLICY;

typedef struct _BUS_INTERFACE_STANDARD {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PTRANSLATE_BUS_ADDRESS TranslateBusAddress;
    PGET_DMA_ADAPTER GetDmaAdapter;
    PGET_SET_DEVICE_DATA SetBusData;
    PGET_SET_DEVICE_DATA GetBusData;

} BUS_INTERFACE_STANDARD, *PBUS_INTERFACE_STANDARD;

typedef
_Function_class_(GET_VIRTUAL_DEVICE_DATA)
_IRQL_requires_same_
_IRQL_requires_max_(DISPATCH_LEVEL)
ULONG GET_VIRTUAL_DEVICE_DATA (
    _Inout_                 PVOID Context,
    _In_                    USHORT VirtualFunction,
    _Out_writes_bytes_(Length)    PVOID Buffer,
    _In_                    ULONG Offset,
    _In_                    ULONG Length
    );
typedef GET_VIRTUAL_DEVICE_DATA *PGET_VIRTUAL_DEVICE_DATA;

typedef
_Function_class_(SET_VIRTUAL_DEVICE_DATA)
_IRQL_requires_same_
_IRQL_requires_max_(DISPATCH_LEVEL)
ULONG SET_VIRTUAL_DEVICE_DATA (
    _Inout_             PVOID Context,
    _In_                USHORT VirtualFunction,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_                ULONG Offset,
    _In_                ULONG Length
    );
typedef SET_VIRTUAL_DEVICE_DATA *PSET_VIRTUAL_DEVICE_DATA;

typedef
_Function_class_(GET_VIRTUAL_DEVICE_LOCATION)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS GET_VIRTUAL_DEVICE_LOCATION (
    _Inout_     PVOID Context,
    _In_        USHORT VirtualFunction,
    _Out_       PUINT16 SegmentNumber,
    _Out_       PUINT8 BusNumber,
    _Out_       PUINT8 FunctionNumber
    );
typedef GET_VIRTUAL_DEVICE_LOCATION *PGET_VIRTUAL_DEVICE_LOCATION;

typedef
_Function_class_(GET_VIRTUAL_DEVICE_RESOURCES)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
VOID GET_VIRTUAL_DEVICE_RESOURCES (
    _Inout_     PVOID   Context,
    _Out_       PUINT8  CapturedBusNumbers
    );
typedef GET_VIRTUAL_DEVICE_RESOURCES *PGET_VIRTUAL_DEVICE_RESOURCES;

typedef
_Function_class_(ENABLE_VIRTUALIZATION)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS ENABLE_VIRTUALIZATION (
    _Inout_     PVOID   Context,
    _In_        UINT16  NumVFs,
    _In_        BOOLEAN EnableVfMigration,
    _In_        BOOLEAN EnableMigrationInterrupt,
    _In_        BOOLEAN EnableVirtualization
    );
typedef ENABLE_VIRTUALIZATION *PENABLE_VIRTUALIZATION;


typedef
_Function_class_(GET_VIRTUAL_FUNCTION_PROBED_BARS)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
GET_VIRTUAL_FUNCTION_PROBED_BARS(
    _Inout_         PVOID  Context,
    _Out_writes_(6) PULONG BaseRegisterValues
    ) ;
typedef GET_VIRTUAL_FUNCTION_PROBED_BARS *PGET_VIRTUAL_FUNCTION_PROBED_BARS;


typedef struct _PCI_VIRTUALIZATION_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PSET_VIRTUAL_DEVICE_DATA SetVirtualFunctionData;
    PGET_VIRTUAL_DEVICE_DATA GetVirtualFunctionData;
    PGET_VIRTUAL_DEVICE_LOCATION    GetLocation;
    PGET_VIRTUAL_DEVICE_RESOURCES   GetResources;
    PENABLE_VIRTUALIZATION EnableVirtualization;
    PGET_VIRTUAL_FUNCTION_PROBED_BARS GetVirtualFunctionProbedBars;
} PCI_VIRTUALIZATION_INTERFACE, *PPCI_VIRTUALIZATION_INTERFACE;

#define PCI_SECURITY_INTERFACE_VERSION 1

typedef enum _PCI_ACS_BIT {

    PciAcsReserved = 0,
    PciAcsBitEnable,
    PciAcsBitDisable,
    PciAcsBitDontCare
} PCI_ACS_BIT, *PPCI_ACS_BIT;

typedef
_Function_class_(PCI_SET_ACS)
_IRQL_requires_same_
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS PCI_SET_ACS (
    _Inout_     PVOID   Context,
    _In_        PCI_ACS_BIT EnableSourceValidation,
    _In_        PCI_ACS_BIT EnableTranslationBlocking,
    _In_        PCI_ACS_BIT EnableP2PRequestRedirect,
    _In_        PCI_ACS_BIT EnableCompletionRedirect,
    _In_        PCI_ACS_BIT EnableUpstreamForwarding,
    _In_        PCI_ACS_BIT EnableEgressControl,
    _In_        PCI_ACS_BIT EnableDirectTranslatedP2P
    );

typedef PCI_SET_ACS *PPCI_SET_ACS;

typedef struct _PCI_SECURITY_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PPCI_SET_ACS    SetAccessControlServices;
} PCI_SECURITY_INTERFACE, *PPCI_SECURITY_INTERFACE;

typedef
VOID
(*PREENUMERATE_SELF)(
    _In_ PVOID Context
    );

typedef struct _REENUMERATE_SELF_INTERFACE_STANDARD {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PREENUMERATE_SELF SurpriseRemoveAndReenumerateSelf;
} REENUMERATE_SELF_INTERFACE_STANDARD, *PREENUMERATE_SELF_INTERFACE_STANDARD;

#define D3COLD_SUPPORT_INTERFACE_VERSION 1

typedef
_Function_class_(SET_D3COLD_SUPPORT)
_IRQL_requires_(PASSIVE_LEVEL)
VOID
SET_D3COLD_SUPPORT (
    _In_reads_opt_(_Inexpressible_("varies")) PVOID Context,
    _In_ BOOLEAN D3ColdSupport
    );

typedef SET_D3COLD_SUPPORT *PSET_D3COLD_SUPPORT;

typedef enum _DEVICE_WAKE_DEPTH {
    DeviceWakeDepthNotWakeable    = 0,
    DeviceWakeDepthD0,
    DeviceWakeDepthD1,
    DeviceWakeDepthD2,
    DeviceWakeDepthD3hot,
    DeviceWakeDepthD3cold,
    DeviceWakeDepthMaximum
} DEVICE_WAKE_DEPTH, *PDEVICE_WAKE_DEPTH;

FORCEINLINE
DEVICE_POWER_STATE
MapWakeDepthToDstate(
    _In_ DEVICE_WAKE_DEPTH WakeDepth
    )
{
    const DEVICE_POWER_STATE dstateMap[DeviceWakeDepthMaximum] =
    {
        PowerDeviceD0,
        PowerDeviceD0,
        PowerDeviceD1,
        PowerDeviceD2,
        PowerDeviceD3,
        PowerDeviceD3
    };

    if (WakeDepth < 0 || WakeDepth >= DeviceWakeDepthMaximum) {
        return PowerDeviceUnspecified;
    } else {
        return dstateMap[WakeDepth];
    }
}

typedef
_Function_class_(GET_IDLE_WAKE_INFO)
_IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
GET_IDLE_WAKE_INFO (
    _In_reads_opt_(_Inexpressible_("varies")) PVOID Context,
    _In_ SYSTEM_POWER_STATE SystemPowerState,
    _Out_ PDEVICE_WAKE_DEPTH DeepestWakeableDstate
    );

typedef GET_IDLE_WAKE_INFO *PGET_IDLE_WAKE_INFO;

typedef
_Function_class_(GET_D3COLD_CAPABILITY)
_IRQL_requires_(PASSIVE_LEVEL)
NTSTATUS
GET_D3COLD_CAPABILITY (
    _In_reads_opt_(_Inexpressible_("varies")) PVOID Context,
    _Out_ PBOOLEAN D3ColdSupported
    );

typedef GET_D3COLD_CAPABILITY *PGET_D3COLD_CAPABILITY;

typedef enum _D3COLD_LAST_TRANSITION_STATUS {
    LastDStateTransitionStatusUnknown = 0,
    LastDStateTransitionD3hot,
    LastDStateTransitionD3cold
} D3COLD_LAST_TRANSITION_STATUS, *PD3COLD_LAST_TRANSITION_STATUS;

typedef
_Function_class_(GET_D3COLD_LAST_TRANSITION_STATUS)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
GET_D3COLD_LAST_TRANSITION_STATUS (
    _In_reads_opt_(_Inexpressible_("varies")) PVOID Context,
    _Out_ PD3COLD_LAST_TRANSITION_STATUS LastTransitionStatus
    );

typedef GET_D3COLD_LAST_TRANSITION_STATUS *PGET_D3COLD_LAST_TRANSITION_STATUS;

typedef struct _D3COLD_SUPPORT_INTERFACE {

    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    PSET_D3COLD_SUPPORT                 SetD3ColdSupport;
    PGET_IDLE_WAKE_INFO                 GetIdleWakeInfo;
    PGET_D3COLD_CAPABILITY              GetD3ColdCapability;
    PGET_D3COLD_CAPABILITY              GetBusDriverD3ColdSupport;
    PGET_D3COLD_LAST_TRANSITION_STATUS  GetLastTransitionStatus;

} D3COLD_SUPPORT_INTERFACE, *PD3COLD_SUPPORT_INTERFACE;

typedef struct _AGP_TARGET_BUS_INTERFACE_STANDARD {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PGET_SET_DEVICE_DATA SetBusData;
    PGET_SET_DEVICE_DATA GetBusData;
    UCHAR CapabilityID;  // 2 (AGPv2 host) or new 0xE (AGPv3 bridge)

} AGP_TARGET_BUS_INTERFACE_STANDARD, *PAGP_TARGET_BUS_INTERFACE_STANDARD;

typedef BOOLEAN (* PGPE_SERVICE_ROUTINE) (
                            PVOID,
                            PVOID);

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS (* PGPE_CONNECT_VECTOR) (
                            PDEVICE_OBJECT,
                            ULONG,
                            KINTERRUPT_MODE,
                            BOOLEAN,
                            PGPE_SERVICE_ROUTINE,
                            PVOID,
                            PVOID);

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS (* PGPE_DISCONNECT_VECTOR) (
                            PVOID);

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS (* PGPE_ENABLE_EVENT) (
                            PDEVICE_OBJECT,
                            PVOID);

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS (* PGPE_DISABLE_EVENT) (
                            PDEVICE_OBJECT,
                            PVOID);

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS (* PGPE_CLEAR_STATUS) (
                            PDEVICE_OBJECT,
                            PVOID);

typedef
VOID (* PDEVICE_NOTIFY_CALLBACK) (
                            PVOID,
                            ULONG);

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS (* PREGISTER_FOR_DEVICE_NOTIFICATIONS) (
                            PDEVICE_OBJECT,
                            PDEVICE_NOTIFY_CALLBACK,
                            PVOID);

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
void (* PUNREGISTER_FOR_DEVICE_NOTIFICATIONS) (
                            PDEVICE_OBJECT,
                            PDEVICE_NOTIFY_CALLBACK);

typedef struct _ACPI_INTERFACE_STANDARD {
    USHORT                  Size;
    USHORT                  Version;
    PVOID                   Context;
    PINTERFACE_REFERENCE    InterfaceReference;
    PINTERFACE_DEREFERENCE  InterfaceDereference;
    PGPE_CONNECT_VECTOR                     GpeConnectVector;
    PGPE_DISCONNECT_VECTOR                  GpeDisconnectVector;
    PGPE_ENABLE_EVENT                       GpeEnableEvent;
    PGPE_DISABLE_EVENT                      GpeDisableEvent;
    PGPE_CLEAR_STATUS                       GpeClearStatus;
    PREGISTER_FOR_DEVICE_NOTIFICATIONS      RegisterForDeviceNotifications;
    PUNREGISTER_FOR_DEVICE_NOTIFICATIONS    UnregisterForDeviceNotifications;
} ACPI_INTERFACE_STANDARD, *PACPI_INTERFACE_STANDARD;

typedef
BOOLEAN
(*PGPE_SERVICE_ROUTINE2) (
    PVOID   ObjectContext,
    PVOID   ServiceContext
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS
(*PGPE_CONNECT_VECTOR2) (
    PVOID           Context,
    ULONG           GpeNumber,
    KINTERRUPT_MODE Mode,
    BOOLEAN         Shareable,
    PGPE_SERVICE_ROUTINE    ServiceRoutine,
    PVOID           ServiceContext,
    PVOID           *ObjectContext
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS
(*PGPE_DISCONNECT_VECTOR2) (
    PVOID   Context,
    PVOID   ObjectContext
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS
(*PGPE_ENABLE_EVENT2) (
    PVOID   Context,
    PVOID   ObjectContext
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS
(*PGPE_DISABLE_EVENT2) (
    PVOID   Context,
    PVOID   ObjectContext
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS
(*PGPE_CLEAR_STATUS2) (
    PVOID   Context,
    PVOID   ObjectContext
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(*PDEVICE_NOTIFY_CALLBACK2) (
    PVOID   NotificationContext,
    ULONG   NotifyCode
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS
(*PREGISTER_FOR_DEVICE_NOTIFICATIONS2) (
    PVOID   Context,
    PDEVICE_NOTIFY_CALLBACK2    NotificationHandler,
    PVOID   NotificationContext
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(*PUNREGISTER_FOR_DEVICE_NOTIFICATIONS2) (
    PVOID   Context
    );

typedef struct {
    USHORT                  Size;
    USHORT                  Version;
    PVOID                   Context;
    PINTERFACE_REFERENCE    InterfaceReference;
    PINTERFACE_DEREFERENCE  InterfaceDereference;
    PGPE_CONNECT_VECTOR2                    GpeConnectVector;
    PGPE_DISCONNECT_VECTOR2                 GpeDisconnectVector;
    PGPE_ENABLE_EVENT2                      GpeEnableEvent;
    PGPE_DISABLE_EVENT2                     GpeDisableEvent;
    PGPE_CLEAR_STATUS2                      GpeClearStatus;
    PREGISTER_FOR_DEVICE_NOTIFICATIONS2     RegisterForDeviceNotifications;
    PUNREGISTER_FOR_DEVICE_NOTIFICATIONS2   UnregisterForDeviceNotifications;

} ACPI_INTERFACE_STANDARD2, *PACPI_INTERFACE_STANDARD2;

typedef enum _ACPI_REG_TYPE {
    PM1a_ENABLE,
    PM1b_ENABLE,
    PM1a_STATUS,
    PM1b_STATUS,
    PM1a_CONTROL,
    PM1b_CONTROL,
    GP_STATUS,
    GP_ENABLE,
    SMI_CMD,
    MaxRegType
} ACPI_REG_TYPE, *PACPI_REG_TYPE;

typedef USHORT (*PREAD_ACPI_REGISTER) (
  _In_ ACPI_REG_TYPE AcpiReg,
  _In_ ULONG         Register);

typedef VOID (*PWRITE_ACPI_REGISTER) (
  _In_ ACPI_REG_TYPE AcpiReg,
  _In_ ULONG         Register,
  _In_ USHORT        Value
  );

typedef struct ACPI_REGS_INTERFACE_STANDARD {
    USHORT Size;
    USHORT Version;
    PVOID  Context;
    PINTERFACE_REFERENCE   InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PREAD_ACPI_REGISTER  ReadAcpiRegister;
    PWRITE_ACPI_REGISTER WriteAcpiRegister;

} ACPI_REGS_INTERFACE_STANDARD, *PACPI_REGS_INTERFACE_STANDARD;


typedef NTSTATUS (*PHAL_QUERY_ALLOCATE_PORT_RANGE) (
  _In_ BOOLEAN IsSparse,
  _In_ BOOLEAN PrimaryIsMmio,
  _In_opt_ PVOID VirtBaseAddr,
  _In_ PHYSICAL_ADDRESS PhysBaseAddr,  // Only valid if PrimaryIsMmio = TRUE
  _In_ ULONG Length,                   // Only valid if PrimaryIsMmio = TRUE
  _Out_ PUSHORT NewRangeId
  );

typedef VOID (*PHAL_FREE_PORT_RANGE)(
    _In_ USHORT RangeId
    );


typedef struct _HAL_PORT_RANGE_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID  Context;
    PINTERFACE_REFERENCE   InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PHAL_QUERY_ALLOCATE_PORT_RANGE QueryAllocateRange;
    PHAL_FREE_PORT_RANGE FreeRange;
} HAL_PORT_RANGE_INTERFACE, *PHAL_PORT_RANGE_INTERFACE;

typedef enum _CMOS_DEVICE_TYPE {
    CmosTypeStdPCAT,
    CmosTypeIntelPIIX4,
    CmosTypeDal1501
} CMOS_DEVICE_TYPE;

typedef
ULONG
(*PREAD_ACPI_CMOS) (
    _In_ CMOS_DEVICE_TYPE CmosType,
    _In_ ULONG SourceAddress,
    _Out_writes_bytes_(ByteCount) PUCHAR DataBuffer,
    _In_ ULONG ByteCount
    );

typedef
ULONG
(*PWRITE_ACPI_CMOS) (
    _In_ CMOS_DEVICE_TYPE CmosType,
    _In_ ULONG SourceAddress,
    _In_reads_bytes_(ByteCount) PUCHAR DataBuffer,
    _In_ ULONG ByteCount
    );

typedef struct _ACPI_CMOS_INTERFACE_STANDARD {
    USHORT Size;
    USHORT Version;
    PVOID  Context;
    PINTERFACE_REFERENCE   InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PREAD_ACPI_CMOS     ReadCmos;
    PWRITE_ACPI_CMOS    WriteCmos;
} ACPI_CMOS_INTERFACE_STANDARD, *PACPI_CMOS_INTERFACE_STANDARD;

typedef struct {
    PVOID   LinkNode;
    ULONG   StaticVector;
    UCHAR   Flags;
} ROUTING_TOKEN, *PROUTING_TOKEN;

#define PCI_MSI_ROUTING         0x1
#define PCI_STATIC_ROUTING      0x2

typedef enum _PCI_BUSMASTER_RID_TYPE {
    BusmasterRidFromDeviceRid,
    BusmasterRidFromBridgeRid,
    BusmasterRidFromMultipleBridges
} PCI_BUSMASTER_RID_TYPE, *PPCI_BUSMASTER_RID_TYPE;

typedef struct _PCI_BUSMASTER_DESCRIPTOR {
    PCI_BUSMASTER_RID_TYPE Type;
    ULONG Segment;
    union {
        struct {
            UCHAR   Bus;
            UCHAR   Device;
            UCHAR   Function;
            UCHAR   Reserved;
        } DeviceRid;
        struct {
            UCHAR   Bus;
            UCHAR   Device;
            UCHAR   Function;
            UCHAR   Reserved;
        } BridgeRid;
        struct {
            UCHAR   SecondaryBus;
            UCHAR   SubordinateBus;
        } MultipleBridges;

    } DUMMYSTRUCTNAME;
} PCI_BUSMASTER_DESCRIPTOR, *PPCI_BUSMASTER_DESCRIPTOR;

typedef
NTSTATUS
(*PGET_INTERRUPT_ROUTING)(
    _In_  PDEVICE_OBJECT  Pdo,
    _Inout_ ULONG           *Bus,
    _Inout_ ULONG           *PciSlot,
    _Out_opt_ UCHAR           *InterruptLine,
    _Out_opt_ UCHAR           *InterruptPin,
    _Out_opt_ UCHAR           *ClassCode,
    _Out_opt_ UCHAR           *SubClassCode,
    _Outptr_result_maybenull_ PDEVICE_OBJECT  *ParentPdo,
    _Out_opt_ UCHAR           *Flags,
    _Out_opt_ UCHAR                    *PhantomFunctionBits,
    _Out_opt_ PCI_BUSMASTER_DESCRIPTOR *InitiatingRidDescriptor
    );

typedef
VOID
(*PUPDATE_INTERRUPT_LINE)(
    _In_ PDEVICE_OBJECT Pdo,
    _In_ UCHAR LineRegister
    );

typedef struct _INT_ROUTE_INTERFACE_STANDARD {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PGET_INTERRUPT_ROUTING GetInterruptRouting;
    PVOID                   Reserved;
    PUPDATE_INTERRUPT_LINE UpdateInterruptLine;
} INT_ROUTE_INTERFACE_STANDARD, *PINT_ROUTE_INTERFACE_STANDARD;

#define PCI_INT_ROUTE_INTRF_STANDARD_VER 2


_IRQL_requires_max_(PASSIVE_LEVEL)
_When_((DeviceProperty & __string_type),
    _At_(PropertyBuffer,
        _Post_z_)
    )
_When_((DeviceProperty & __multiString_type),
    _At_(PropertyBuffer,
        _Post_ _NullNull_terminated_)
    )

#define PLUGPLAY_REGKEY_DEVICE  1
#define PLUGPLAY_REGKEY_DRIVER  2
#define PLUGPLAY_REGKEY_CURRENT_HWPROFILE 4



#define DEVICE_INTERFACE_INCLUDE_NONACTIVE   0x00000001

#define PNPNOTIFY_DEVICE_INTERFACE_INCLUDE_EXISTING_INTERFACES    0x00000001



#define IoAdjustPagingPathCount(_count_,_paging_) {     \
    if (_paging_) {                                     \
        InterlockedIncrement(_count_);                  \
    } else {                                            \
        InterlockedDecrement(_count_);                  \
    }                                                   \
}


typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS
(*PGET_LOCATION_STRING) (
    _Inout_opt_ PVOID Context,
    _Outptr_
    _At_(*LocationStrings,
        _When_(return == 0, __drv_allocatesMem(Mem)))
    PZZWSTR *LocationStrings
    );

typedef struct _PNP_LOCATION_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PGET_LOCATION_STRING GetLocationString;
} PNP_LOCATION_INTERFACE, *PPNP_LOCATION_INTERFACE;

typedef enum _ARBITER_ACTION {
    ArbiterActionTestAllocation,
    ArbiterActionRetestAllocation,
    ArbiterActionCommitAllocation,
    ArbiterActionRollbackAllocation,
    ArbiterActionQueryAllocatedResources,
    ArbiterActionWriteReservedResources,
    ArbiterActionQueryConflict,
    ArbiterActionQueryArbitrate,
    ArbiterActionAddReserved,
    ArbiterActionBootAllocation
} ARBITER_ACTION, *PARBITER_ACTION;

typedef struct _ARBITER_CONFLICT_INFO {
    PDEVICE_OBJECT OwningObject;
    ULONGLONG Start;
    ULONGLONG End;
} ARBITER_CONFLICT_INFO, *PARBITER_CONFLICT_INFO;

typedef struct _ARBITER_TEST_ALLOCATION_PARAMETERS {
    _Inout_ PLIST_ENTRY ArbitrationList;
    _In_ ULONG AllocateFromCount;
    _In_ PCM_PARTIAL_RESOURCE_DESCRIPTOR AllocateFrom;
} ARBITER_TEST_ALLOCATION_PARAMETERS, *PARBITER_TEST_ALLOCATION_PARAMETERS;

typedef struct _ARBITER_RETEST_ALLOCATION_PARAMETERS {
    _Inout_ PLIST_ENTRY ArbitrationList;
    _In_ ULONG AllocateFromCount;
    _In_ PCM_PARTIAL_RESOURCE_DESCRIPTOR AllocateFrom;
} ARBITER_RETEST_ALLOCATION_PARAMETERS, *PARBITER_RETEST_ALLOCATION_PARAMETERS;

typedef struct _ARBITER_BOOT_ALLOCATION_PARAMETERS {
    _Inout_ PLIST_ENTRY ArbitrationList;
} ARBITER_BOOT_ALLOCATION_PARAMETERS, *PARBITER_BOOT_ALLOCATION_PARAMETERS;


typedef struct _ARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS {
    _Out_ PCM_PARTIAL_RESOURCE_LIST *AllocatedResources;
} ARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS, *PARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS;

typedef struct _ARBITER_QUERY_CONFLICT_PARAMETERS {
    _In_ PDEVICE_OBJECT PhysicalDeviceObject;
    _In_ PIO_RESOURCE_DESCRIPTOR ConflictingResource;
    _Out_ PULONG ConflictCount;
    _Out_ PARBITER_CONFLICT_INFO *Conflicts;
} ARBITER_QUERY_CONFLICT_PARAMETERS, *PARBITER_QUERY_CONFLICT_PARAMETERS;

typedef struct _ARBITER_QUERY_ARBITRATE_PARAMETERS {
    _In_ PLIST_ENTRY ArbitrationList;
} ARBITER_QUERY_ARBITRATE_PARAMETERS, *PARBITER_QUERY_ARBITRATE_PARAMETERS;

typedef struct _ARBITER_ADD_RESERVED_PARAMETERS {
    _In_ PDEVICE_OBJECT ReserveDevice;
} ARBITER_ADD_RESERVED_PARAMETERS, *PARBITER_ADD_RESERVED_PARAMETERS;


typedef struct _ARBITER_PARAMETERS {
    union {
        ARBITER_TEST_ALLOCATION_PARAMETERS              TestAllocation;
        ARBITER_RETEST_ALLOCATION_PARAMETERS            RetestAllocation;
        ARBITER_BOOT_ALLOCATION_PARAMETERS              BootAllocation;
        ARBITER_QUERY_ALLOCATED_RESOURCES_PARAMETERS    QueryAllocatedResources;
        ARBITER_QUERY_CONFLICT_PARAMETERS               QueryConflict;
        ARBITER_QUERY_ARBITRATE_PARAMETERS              QueryArbitrate;
        ARBITER_ADD_RESERVED_PARAMETERS                 AddReserved;
    } Parameters;
} ARBITER_PARAMETERS, *PARBITER_PARAMETERS;

typedef enum _ARBITER_REQUEST_SOURCE {
    ArbiterRequestUndefined = -1,
    ArbiterRequestLegacyReported,   // IoReportResourceUsage
    ArbiterRequestHalReported,      // IoReportHalResourceUsage
    ArbiterRequestLegacyAssigned,   // IoAssignResources
    ArbiterRequestPnpDetected,      // IoReportResourceForDetection
    ArbiterRequestPnpEnumerated     // IRP_MN_QUERY_RESOURCE_REQUIREMENTS

} ARBITER_REQUEST_SOURCE;


typedef enum _ARBITER_RESULT {

    ArbiterResultUndefined = -1,
    ArbiterResultSuccess,
    ArbiterResultExternalConflict, // This indicates that the request can never be solved for devices in this list
    ArbiterResultNullRequest       // The request was for length zero and thus no translation should be attempted

} ARBITER_RESULT;

#define ARBITER_FLAG_BOOT_CONFIG 0x00000001
#define ARBITER_FLAG_ROOT_ENUM   0x00000002
#define ARBITER_FLAG_OTHER_ENUM  0x00000004

typedef struct _ARBITER_LIST_ENTRY {

    LIST_ENTRY ListEntry;
    ULONG AlternativeCount;
    _Field_size_(AlternativeCount)
    PIO_RESOURCE_DESCRIPTOR Alternatives;
    PDEVICE_OBJECT PhysicalDeviceObject;
    ARBITER_REQUEST_SOURCE RequestSource;
    ULONG Flags;
    LONG_PTR WorkSpace;
    INTERFACE_TYPE InterfaceType;
    ULONG SlotNumber;
    ULONG BusNumber;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR Assignment;
    PIO_RESOURCE_DESCRIPTOR SelectedAlternative;
    ARBITER_RESULT Result;
} ARBITER_LIST_ENTRY, *PARBITER_LIST_ENTRY;

typedef
NTSTATUS
(*PARBITER_HANDLER) (
    _Inout_opt_ PVOID Context,
    _In_ ARBITER_ACTION Action,
    _Inout_ PARBITER_PARAMETERS Parameters
    );

#define ARBITER_PARTIAL   0x00000001

typedef struct _ARBITER_INTERFACE {

    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PARBITER_HANDLER ArbiterHandler;
    ULONG Flags;

} ARBITER_INTERFACE, *PARBITER_INTERFACE;

typedef enum _RESOURCE_TRANSLATION_DIRECTION {
    TranslateChildToParent,
    TranslateParentToChild
} RESOURCE_TRANSLATION_DIRECTION;

typedef
NTSTATUS
(*PTRANSLATE_RESOURCE_HANDLER)(
    _Inout_opt_ PVOID Context,
    _In_ PCM_PARTIAL_RESOURCE_DESCRIPTOR Source,
    _In_ RESOURCE_TRANSLATION_DIRECTION Direction,
    _In_opt_ ULONG AlternativesCount,
    _In_reads_opt_(AlternativesCount) IO_RESOURCE_DESCRIPTOR Alternatives[],
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _Out_ PCM_PARTIAL_RESOURCE_DESCRIPTOR Target
);

typedef
NTSTATUS
(*PTRANSLATE_RESOURCE_REQUIREMENTS_HANDLER)(
    _Inout_opt_ PVOID Context,
    _In_ PIO_RESOURCE_DESCRIPTOR Source,
    _In_ PDEVICE_OBJECT PhysicalDeviceObject,
    _Out_ PULONG TargetCount,
    _Out_writes_(*TargetCount) PIO_RESOURCE_DESCRIPTOR *Target
);

typedef struct _TRANSLATOR_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PTRANSLATE_RESOURCE_HANDLER TranslateResources;
    PTRANSLATE_RESOURCE_REQUIREMENTS_HANDLER TranslateResourceRequirements;
} TRANSLATOR_INTERFACE, *PTRANSLATOR_INTERFACE;

typedef
NTSTATUS
(*PLEGACY_DEVICE_DETECTION_HANDLER)(
    _Inout_opt_ PVOID Context,
    _In_ INTERFACE_TYPE LegacyBusType,
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _Outptr_ PDEVICE_OBJECT *PhysicalDeviceObject
);

typedef struct _LEGACY_DEVICE_DETECTION_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PLEGACY_DEVICE_DETECTION_HANDLER LegacyDeviceDetection;
} LEGACY_DEVICE_DETECTION_INTERFACE, *PLEGACY_DEVICE_DETECTION_INTERFACE;

typedef struct _PLUGPLAY_NOTIFICATION_HEADER {
    USHORT Version; // presently at version 1.
    USHORT Size;    // size (in bytes) of header + event-specific data.
    GUID Event;
} PLUGPLAY_NOTIFICATION_HEADER, *PPLUGPLAY_NOTIFICATION_HEADER;

typedef struct _HWPROFILE_CHANGE_NOTIFICATION {
    USHORT Version;
    USHORT Size;
    GUID Event;
} HWPROFILE_CHANGE_NOTIFICATION, *PHWPROFILE_CHANGE_NOTIFICATION;

typedef struct _DEVICE_INTERFACE_CHANGE_NOTIFICATION {
    USHORT Version;
    USHORT Size;
    GUID Event;
    GUID InterfaceClassGuid;
    PUNICODE_STRING SymbolicLinkName;
} DEVICE_INTERFACE_CHANGE_NOTIFICATION, *PDEVICE_INTERFACE_CHANGE_NOTIFICATION;

typedef struct _TARGET_DEVICE_REMOVAL_NOTIFICATION {
    USHORT Version;
    USHORT Size;
    GUID Event;
    PFILE_OBJECT FileObject;
} TARGET_DEVICE_REMOVAL_NOTIFICATION, *PTARGET_DEVICE_REMOVAL_NOTIFICATION;

typedef struct _TARGET_DEVICE_CUSTOM_NOTIFICATION {
    USHORT Version;
    USHORT Size;
    GUID Event;

    PFILE_OBJECT FileObject;
    LONG NameBufferOffset;
    UCHAR CustomDataBuffer[1];
} TARGET_DEVICE_CUSTOM_NOTIFICATION, *PTARGET_DEVICE_CUSTOM_NOTIFICATION;

#if (NTDDI_VERSION >= NTDDI_VISTA)
#include <devpropdef.h>
#define PLUGPLAY_PROPERTY_PERSISTENT  0x00000001
#endif

#define PNP_REPLACE_TEST_QUIESCE 0x80000000

typedef
NTSTATUS
(*PPARTITION_UNIT_GET_UNIQUE_ID) (
    _In_ PVOID Context,
    _Out_ PULONG64 UniqueId
    );

#define SPARE_PROPERTY_HARDWARE_MIRRORING   0x01
#define SPARE_PROPERTY_HARDWARE_PAGE_COPY   0x02
#define SPARE_PROPERTY_HARDWARE_QUIESCE     0x04

typedef
NTSTATUS
(*PPARTITION_UNIT_GET_SPARE_PROPERTIES) (
    _In_ PVOID Context,
    _Out_ PULONG Properties
    );

typedef
BOOLEAN
(*PPARTITION_UNIT_IS_VALID_SPARE) (
    _In_ PVOID Context,
    _In_ ULONG64 UniqueId
    );

#define PARTITION_UNIT_INTERFACE_VERSION    1

typedef struct _PARTITION_UNIT_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PPARTITION_UNIT_GET_UNIQUE_ID GetUniqueId;
    PPARTITION_UNIT_GET_SPARE_PROPERTIES GetSpareProperties;
    PPARTITION_UNIT_IS_VALID_SPARE IsValidSpare;

} PARTITION_UNIT_INTERFACE, *PPARTITION_UNIT_INTERFACE;

typedef struct _PNP_REPLACE_DRIVER_INTERFACE *PPNP_REPLACE_DRIVER_INTERFACE;

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_DRIVER_INIT) (
    _Inout_ PPNP_REPLACE_DRIVER_INTERFACE Interface,
    _In_ PVOID Unused
    );

#define PNP_REPLACE_NO_MAP MAXLONGLONG

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_MAP_MEMORY) (
    _In_    PHYSICAL_ADDRESS    TargetPhysicalAddress,
    _In_    PHYSICAL_ADDRESS    SparePhysicalAddress,
    _Inout_ PLARGE_INTEGER      NumberOfBytes,
    _Outptr_ PVOID *TargetAddress,
    _Outptr_ PVOID *SpareAddress
    );

typedef struct _PNP_REPLACE_MEMORY_LIST {

    ULONG AllocatedCount;
    ULONG Count;
    ULONGLONG TotalLength;
    struct {
        PHYSICAL_ADDRESS Address;
        ULONGLONG Length;
    } Ranges[ANYSIZE_ARRAY];

} PNP_REPLACE_MEMORY_LIST, *PPNP_REPLACE_MEMORY_LIST;

typedef struct _PNP_REPLACE_PROCESSOR_LIST {

    PKAFFINITY Affinity;
    ULONG GroupCount;
    ULONG AllocatedCount;
    ULONG Count;
    ULONG ApicIds[ANYSIZE_ARRAY];

} PNP_REPLACE_PROCESSOR_LIST, *PPNP_REPLACE_PROCESSOR_LIST;

typedef struct _PNP_REPLACE_PROCESSOR_LIST_V1 {

    KAFFINITY AffinityMask;
    ULONG AllocatedCount;
    ULONG Count;
    ULONG ApicIds[ANYSIZE_ARRAY];

} PNP_REPLACE_PROCESSOR_LIST_V1, *PPNP_REPLACE_PROCESSOR_LIST_V1;

#define PNP_REPLACE_PARAMETERS_VERSION 2

typedef struct _PNP_REPLACE_PARAMETERS {

    ULONG Size;
    ULONG Version;

    ULONG64 Target;
    ULONG64 Spare;
    PPNP_REPLACE_PROCESSOR_LIST TargetProcessors;
    PPNP_REPLACE_PROCESSOR_LIST SpareProcessors;
    PPNP_REPLACE_MEMORY_LIST TargetMemory;
    PPNP_REPLACE_MEMORY_LIST SpareMemory;

    PREPLACE_MAP_MEMORY MapMemory;

} PNP_REPLACE_PARAMETERS, *PPNP_REPLACE_PARAMETERS;

typedef
VOID
(*PREPLACE_UNLOAD) (
    VOID
    );

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_BEGIN) (
    _In_ PPNP_REPLACE_PARAMETERS Parameters,
    _Outptr_ PVOID *Context
);

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_END) (
    _In_ PVOID Context
    );

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_MIRROR_PHYSICAL_MEMORY) (
    _In_ PVOID Context,
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ LARGE_INTEGER ByteCount
    );

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_SET_PROCESSOR_ID) (
    _In_ PVOID Context,
    _In_ ULONG ApicId,
    _In_ BOOLEAN Target
    );

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_SWAP) (
    _In_ PVOID Context
    );

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_INITIATE_HARDWARE_MIRROR) (
    _In_ PVOID Context
    );

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_MIRROR_PLATFORM_MEMORY) (
    _In_ PVOID Context
    );

typedef
_Must_inspect_result_
NTSTATUS
(*PREPLACE_GET_MEMORY_DESTINATION) (
    _In_ PVOID Context,
    _In_ PHYSICAL_ADDRESS SourceAddress,
    _Out_ PPHYSICAL_ADDRESS DestinationAddress
    );

typedef
_Must_inspect_result_ NTSTATUS
(*PREPLACE_ENABLE_DISABLE_HARDWARE_QUIESCE) (
    _In_ PVOID Context,
    _In_ BOOLEAN Enable
    );

#define PNP_REPLACE_DRIVER_INTERFACE_VERSION 1
#define PNP_REPLACE_DRIVER_INTERFACE_MINIMUM_SIZE \
             FIELD_OFFSET(PNP_REPLACE_DRIVER_INTERFACE, InitiateHardwareMirror)

#define PNP_REPLACE_MEMORY_SUPPORTED            0x0001
#define PNP_REPLACE_PROCESSOR_SUPPORTED         0x0002
#define PNP_REPLACE_HARDWARE_MEMORY_MIRRORING   0x0004
#define PNP_REPLACE_HARDWARE_PAGE_COPY          0x0008
#define PNP_REPLACE_HARDWARE_QUIESCE            0x0010

typedef struct _PNP_REPLACE_DRIVER_INTERFACE {

    ULONG Size;
    ULONG Version;

    ULONG Flags;
    PREPLACE_UNLOAD Unload;
    PREPLACE_BEGIN BeginReplace;
    PREPLACE_END EndReplace;
    PREPLACE_MIRROR_PHYSICAL_MEMORY MirrorPhysicalMemory;
    PREPLACE_SET_PROCESSOR_ID SetProcessorId;
    PREPLACE_SWAP Swap;
    PREPLACE_INITIATE_HARDWARE_MIRROR InitiateHardwareMirror;
    PREPLACE_MIRROR_PLATFORM_MEMORY MirrorPlatformMemory;
    PREPLACE_GET_MEMORY_DESTINATION GetMemoryDestination;
    PREPLACE_ENABLE_DISABLE_HARDWARE_QUIESCE EnableDisableHardwareQuiesce;

} PNP_REPLACE_DRIVER_INTERFACE, *PPNP_REPLACE_DRIVER_INTERFACE;

typedef
NTSTATUS
(*PCRASHDUMP_POWER_ON)(
    _In_opt_ PVOID Context
    );

typedef struct _CRASHDUMP_FUNCTIONS_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PCRASHDUMP_POWER_ON PowerOn;
} CRASHDUMP_FUNCTIONS_INTERFACE, *PCRASHDUMP_FUNCTIONS_INTERFACE;

#define PNP_DEPENDENCY_TYPE_INITIALIZATION 0x1
#define PNP_DEPENDENCY_TYPE_START          0x2

typedef enum {
    DependencyPathNone,
    DependencyPathDirect,
    DependencyPathIndirect
} PNP_DEPENDENCY_PATH_TYPE, *PPNP_DEPENDENCY_PATH_TYPE;


NTKERNELAPI
ULONG
IoPnPDeliverServicePowerNotification(
    _In_   POWER_ACTION           PowerOperation,
    _In_   ULONG                  PowerNotificationCode,
    _In_   ULONG                  PowerNotificationData,
    _In_   BOOLEAN                Synchronous
    );

typedef struct _DMA_CACHE_COHERENCY_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    BOOLEAN CacheCoherent;
} DMA_CACHE_COHERENCY_INTERFACE, *PDMA_CACHE_COHERENCY_INTERFACE;

typedef union _IOMMU_SVM_CAPABILITIES {
    struct {
        ULONG AtsCapability:1;
        ULONG PriCapability:1;
        ULONG PasidCapability:1;

        struct {
            ULONG PasidMaxWidth:5;
            ULONG PasidExePerm:1;
            ULONG PasidPrivMode:1;
            ULONG AtsPageAlignedRequest:1;
            ULONG AtsGlobalInvalidate:1;
            ULONG AtsInvalidateQueueDepth:5;
        } CapReg;

        ULONG Rsvd:15;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;
} IOMMU_SVM_CAPABILITIES, *PIOMMU_SVM_CAPABILITIES;

typedef NTSTATUS (*PHAL_DEVICE_POWER_TRANSITION_CALLBACK)(
    __in PDEVICE_OBJECT Pdo,
    __in DEVICE_POWER_STATE NewPowerState,
    __in PVOID Context
    );

typedef
_Function_class_(GET_SVM_CAPABILITIES)
_IRQL_requires_same_
NTSTATUS GET_SVM_CAPABILITIES(
    __inout PVOID Context,
    __out PIOMMU_SVM_CAPABILITIES CapabilitiesOut
    );
typedef GET_SVM_CAPABILITIES *PGET_SVM_CAPABILITIES;

typedef
_Function_class_(ENABLE_SVM_CAPABILITIES)
_IRQL_requires_same_
NTSTATUS ENABLE_SVM_CAPABILITIES(
    __in PVOID Context,
    __in PIOMMU_SVM_CAPABILITIES Capabilities,
    __in PHAL_DEVICE_POWER_TRANSITION_CALLBACK HalDevicePowerTransCallback,
    __in PVOID HalDevicePowerTransCallbackContext
    );
typedef ENABLE_SVM_CAPABILITIES *PENABLE_SVM_CAPABILITIES;

typedef
_Function_class_(DISABLE_SVM_CAPABILITIES)
_IRQL_requires_same_
NTSTATUS DISABLE_SVM_CAPABILITIES(
    __in PVOID Context,
    __in PIOMMU_SVM_CAPABILITIES Capabilities
    );
typedef DISABLE_SVM_CAPABILITIES *PDISABLE_SVM_CAPABILITIES;

typedef struct _IOMMU_DEVICE_PATH {
    GUID BusTypeGuid;
    ULONG UniqueIdLength;
    ULONG PathLength;
    PVOID UniqueId;
    PVOID Path;
} IOMMU_DEVICE_PATH, *PIOMMU_DEVICE_PATH;

typedef
_Function_class_(GET_DEVICE_PATH_INFORMATION)
_IRQL_requires_same_
NTSTATUS GET_DEVICE_PATH_INFORMATION(
    __in PVOID Context,
    __out PIOMMU_DEVICE_PATH *PathOut
    );
typedef GET_DEVICE_PATH_INFORMATION *PGET_DEVICE_PATH_INFORMATION;

typedef struct _IOMMU_BUS_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PGET_SVM_CAPABILITIES GetSvmCapabilities;
    PENABLE_SVM_CAPABILITIES EnableSvmCapabilities;
    PDISABLE_SVM_CAPABILITIES DisableSvmCapabilities;
    PGET_DEVICE_PATH_INFORMATION GetDevicePathInformation;
} IOMMU_BUS_INTERFACE, *PIOMMU_BUS_INTERFACE;

#define DEVICE_RESET_INTERFACE_VERSION  1

typedef enum _DEVICE_RESET_TYPE
{
    FunctionLevelDeviceReset,
    PlatformLevelDeviceReset
} DEVICE_RESET_TYPE;

typedef
VOID
(DEVICE_RESET_COMPLETION)(
    _In_ NTSTATUS Status,
    _Inout_opt_ PVOID Context
    );

typedef DEVICE_RESET_COMPLETION *PDEVICE_RESET_COMPLETION;

typedef struct _FUNCTION_LEVEL_DEVICE_RESET_PARAMETERS {
    ULONG Size;
    PDEVICE_RESET_COMPLETION DeviceResetCompletion;
    PVOID CompletionContext;
} FUNCTION_LEVEL_DEVICE_RESET_PARAMETERS, *PFUNCTION_LEVEL_DEVICE_RESET_PARAMETERS;

typedef
NTSTATUS
(*PDEVICE_RESET_HANDLER)(
    _In_ PVOID InterfaceContext,
    _In_ DEVICE_RESET_TYPE ResetType,
    _In_ ULONG Flags,
    _In_opt_ PVOID ResetParameters
    );

typedef struct _DEVICE_RESET_INTERFACE_STANDARD {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PDEVICE_RESET_HANDLER DeviceReset;
    PVOID Reserved;
} DEVICE_RESET_INTERFACE_STANDARD, *PDEVICE_RESET_INTERFACE_STANDARD;

#define MM_BAD_POINTER (                               \
                       __pragma(warning(push))         \
                       __pragma(warning(disable:4995)) \
                       *(PVOID *) MmBadPointer         \
                       __pragma(warning(pop))          \
                        )

#pragma deprecated(MmBadPointer)  // Use MM_BAD_POINTER instead

#define MM_MAXIMUM_DISK_IO_SIZE          (0x10000)

#define ROUND_TO_PAGES(Size)  (((ULONG_PTR)(Size) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))

#define BYTES_TO_PAGES(Size)  (((Size) >> PAGE_SHIFT) + \
                               (((Size) & (PAGE_SIZE - 1)) != 0))
#define BYTE_OFFSET(Va) ((ULONG)((LONG_PTR)(Va) & (PAGE_SIZE - 1)))

#define PAGE_ALIGN(Va) ((PVOID)((ULONG_PTR)(Va) & ~(PAGE_SIZE - 1)))

#define ADDRESS_AND_SIZE_TO_SPAN_PAGES(Va,Size) \
    ((BYTE_OFFSET (Va) + ((SIZE_T) (Size)) + (PAGE_SIZE - 1)) >> PAGE_SHIFT)

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(COMPUTE_PAGES_SPANNED)   // Use ADDRESS_AND_SIZE_TO_SPAN_PAGES
#endif

#define COMPUTE_PAGES_SPANNED(Va, Size) ADDRESS_AND_SIZE_TO_SPAN_PAGES(Va,Size)

#define IS_SYSTEM_ADDRESS(VA) ((VA) >= MM_SYSTEM_RANGE_START)

#define MmGetMdlPfnArray(Mdl) ((PPFN_NUMBER)(Mdl + 1))

#define MmGetMdlVirtualAddress(Mdl)                                     \
    ((PVOID) ((PCHAR) ((Mdl)->StartVa) + (Mdl)->ByteOffset))

#define MmGetMdlByteCount(Mdl)  ((Mdl)->ByteCount)

#define MmGetMdlByteOffset(Mdl)  ((Mdl)->ByteOffset)

#define MmGetMdlBaseVa(Mdl)  ((Mdl)->StartVa)

typedef enum _MM_PAGE_PRIORITY {
    LowPagePriority,
    NormalPagePriority = 16,
    HighPagePriority = 32
} MM_PAGE_PRIORITY;

#define MdlMappingNoWrite       0x80000000  // Create the mapping as nowrite
#define MdlMappingNoExecute     0x40000000  // Create the mapping as noexecute

#if !POOL_NX_OPTOUT && (POOL_NX_OPTIN || POOL_NX_OPTIN_AUTO)

FORCEINLINE
_Post_writable_byte_size_(MemoryDescriptorList->ByteCount)
_When_(AccessMode==KernelMode, _IRQL_requires_max_(DISPATCH_LEVEL))
_When_(AccessMode==UserMode, _Maybe_raises_SEH_exception_ _IRQL_requires_max_(APC_LEVEL) _Post_notnull_)
_At_(MemoryDescriptorList->MappedSystemVa,
    _Post_writable_byte_size_(MemoryDescriptorList->ByteCount)) // Esp:829
_Must_inspect_result_
_Success_(return != NULL)
PVOID
MmMapLockedPagesSpecifyCache_NXOptIn (
    _Inout_ PMDL MemoryDescriptorList,
    _In_ __drv_strictType(KPROCESSOR_MODE/enum _MODE,__drv_typeConst)
            KPROCESSOR_MODE AccessMode,
    _In_ __drv_strictTypeMatch(__drv_typeCond) MEMORY_CACHING_TYPE CacheType,
    _In_opt_ PVOID RequestedAddress,
    _In_     ULONG BugCheckOnFailure,
    _In_     ULONG Priority  // MM_PAGE_PRIORITY logically OR'd with MdlMapping*
    )
{
    return MmMapLockedPagesSpecifyCache (MemoryDescriptorList,
                                         AccessMode,
                                         CacheType,
                                         RequestedAddress,
                                         BugCheckOnFailure,
#if POOL_NX_OPTIN_AUTO
                                         Priority | MdlMappingNoExecute
#else
                                         Priority | ExDefaultMdlProtection
#endif
                                         );
}

#define MmMapLockedPagesSpecifyCache MmMapLockedPagesSpecifyCache_NXOptIn

#endif // !POOL_NX_OPTOUT && (POOL_NX_OPTIN || POOL_NX_OPTIN_AUTO)

#define MM_DONT_ZERO_ALLOCATION                 0x00000001
#define MM_ALLOCATE_FROM_LOCAL_NODE_ONLY        0x00000002
#define MM_ALLOCATE_FULLY_REQUIRED              0x00000004
#define MM_ALLOCATE_NO_WAIT                     0x00000008
#define MM_ALLOCATE_PREFER_CONTIGUOUS           0x00000010
#define MM_ALLOCATE_REQUIRE_CONTIGUOUS_CHUNKS   0x00000020
#define MM_ALLOCATE_FAST_LARGE_PAGES            0x00000040
#define MM_ALLOCATE_TRIM_IF_NECESSARY           0x00000080
#define MM_ALLOCATE_AND_HOT_REMOVE              0x00000100

#define MM_COPY_MEMORY_PHYSICAL             0x1
#define MM_COPY_MEMORY_VIRTUAL              0x2
#define MM_ANY_NODE_OK          0x80000000


#define MM_SYSTEM_VIEW_EXCEPTIONS_FOR_INPAGE_ERRORS 0x1

_IRQL_requires_max_(DISPATCH_LEVEL)
FORCEINLINE
VOID
MmInitializeMdl (
    _Out_writes_bytes_(sizeof(MDL)+(sizeof(PFN_NUMBER)*ADDRESS_AND_SIZE_TO_SPAN_PAGES(BaseVa,Length)))
             PMDL MemoryDescriptorList,
    _In_opt_ PVOID BaseVa,
    _In_     SIZE_T Length)
{
    MemoryDescriptorList->Next = (PMDL) NULL;
    MemoryDescriptorList->Size = (CSHORT)(sizeof(MDL) +
            (sizeof(PFN_NUMBER) * ADDRESS_AND_SIZE_TO_SPAN_PAGES(BaseVa, Length)));
    MemoryDescriptorList->MdlFlags = 0;
    MemoryDescriptorList->StartVa = (PVOID) PAGE_ALIGN(BaseVa);
    MemoryDescriptorList->ByteOffset = BYTE_OFFSET(BaseVa);
    MemoryDescriptorList->ByteCount = (ULONG)Length;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_Post_writable_byte_size_(Mdl->ByteCount)
_At_(Mdl->MappedSystemVa,
    _Post_writable_byte_size_(Mdl->ByteCount)) // Esp:829
_Check_return_
_Success_(return != NULL)
FORCEINLINE
PVOID
MmGetSystemAddressForMdlSafe (
    _Inout_ PMDL Mdl,
    _In_    ULONG Priority)
{
    if (Mdl->MdlFlags & (MDL_MAPPED_TO_SYSTEM_VA | MDL_SOURCE_IS_NONPAGED_POOL)) {
        return Mdl->MappedSystemVa;
    } else {
        return MmMapLockedPagesSpecifyCache(Mdl, KernelMode, MmCached,
                                            NULL, FALSE, Priority);
    }
}


//#define MmGetSystemAddressForMdl(MDL)
//     (((MDL)->MdlFlags & (MDL_MAPPED_TO_SYSTEM_VA)) ?
//                             ((MDL)->MappedSystemVa) :
//                ((((MDL)->MdlFlags & (MDL_SOURCE_IS_NONPAGED_POOL)) ?
//                      ((PVOID)((ULONG)(MDL)->StartVa | (MDL)->ByteOffset)) :
//                            (MmMapLockedPages((MDL),KernelMode)))))

#if PRAGMA_DEPRECATED_DDK
#pragma deprecated(MmGetSystemAddressForMdl)    // Use MmGetSystemAddressForMdlSafe
#endif

#define MmGetSystemAddressForMdl(MDL)                                  \
     (((MDL)->MdlFlags & (MDL_MAPPED_TO_SYSTEM_VA |                    \
                        MDL_SOURCE_IS_NONPAGED_POOL)) ?                \
                             ((MDL)->MappedSystemVa) :                 \
                             (MmMapLockedPages((MDL),KernelMode)))

_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
FORCEINLINE
MmPrepareMdlForReuse (
    _Inout_ PMDL MDL)
{
    if ((MDL->MdlFlags & MDL_PARTIAL_HAS_BEEN_MAPPED) != 0) {
        NT_ASSERT((MDL->MdlFlags & MDL_PARTIAL) != 0);
        MmUnmapLockedPages( MDL->MappedSystemVa, MDL );
    } else if ((MDL->MdlFlags & MDL_PARTIAL) == 0) {
        NT_ASSERT((MDL->MdlFlags & MDL_MAPPED_TO_SYSTEM_VA) == 0);
    }
}

typedef NTSTATUS (*PMM_DLL_INITIALIZE) (
    _In_ PUNICODE_STRING RegistryPath
    );

typedef NTSTATUS (*PMM_DLL_UNLOAD) (
    VOID
    );

struct _DRIVER_OBJECT;



#define PREFETCH_VIRTUAL_ADDRESS_LIST_VERSION_1     0x1

#define OEM_FONT_VERSION 0x200
#define OEM_FONT_TYPE 0
#define OEM_FONT_ITALIC 0
#define OEM_FONT_UNDERLINE 0
#define OEM_FONT_STRIKEOUT 0
#define OEM_FONT_CHARACTER_SET 255
#define OEM_FONT_FAMILY (3 << 4)

#include "pshpack1.h"
typedef struct _OEM_FONT_FILE_HEADER {
    USHORT Version;
    ULONG FileSize;
    UCHAR Copyright[60];
    USHORT Type;
    USHORT Points;
    USHORT VerticleResolution;
    USHORT HorizontalResolution;
    USHORT Ascent;
    USHORT InternalLeading;
    USHORT ExternalLeading;
    UCHAR Italic;
    UCHAR Underline;
    UCHAR StrikeOut;
    USHORT Weight;
    UCHAR CharacterSet;
    USHORT PixelWidth;
    USHORT PixelHeight;
    UCHAR Family;
    USHORT AverageWidth;
    USHORT MaximumWidth;
    UCHAR FirstCharacter;
    UCHAR LastCharacter;
    UCHAR DefaultCharacter;
    UCHAR BreakCharacter;
    USHORT WidthInBytes;
    ULONG Device;
    ULONG Face;
    ULONG BitsPointer;
    ULONG BitsOffset;
    UCHAR Filler;
    struct {
        USHORT Width;
        USHORT Offset;
    } Map[1];
} OEM_FONT_FILE_HEADER, *POEM_FONT_FILE_HEADER;
#include "poppack.h"

typedef struct _DEVICE_DESCRIPTION {
    ULONG Version;
    BOOLEAN Master;
    BOOLEAN ScatterGather;
    BOOLEAN DemandMode;
    BOOLEAN AutoInitialize;
    BOOLEAN Dma32BitAddresses;
    BOOLEAN IgnoreCount;
    BOOLEAN Reserved1;          // must be false
    BOOLEAN Dma64BitAddresses;
    ULONG BusNumber; // unused for WDM
    ULONG DmaChannel;
    INTERFACE_TYPE  InterfaceType;
    DMA_WIDTH DmaWidth;
    DMA_SPEED DmaSpeed;
    ULONG MaximumLength;
    ULONG DmaPort;
#if (NTDDI_VERSION >= NTDDI_WIN8)
    ULONG DmaAddressWidth;
    ULONG DmaControllerInstance;
    ULONG DmaRequestLine;
    PHYSICAL_ADDRESS DeviceAddress;
#endif /* NTDDI_VERSION >= NTDDI_WIN8 */
} DEVICE_DESCRIPTION, *PDEVICE_DESCRIPTION;

#define DEVICE_DESCRIPTION_VERSION  0
#define DEVICE_DESCRIPTION_VERSION1 1
#define DEVICE_DESCRIPTION_VERSION2 2
#define DEVICE_DESCRIPTION_VERSION3 3

#define DMA_ADAPTER_INFO_VERSION1   1
#define DMA_TRANSFER_INFO_VERSION1  1

typedef struct _DMA_ADAPTER_INFO_V1 {
    ULONG ReadDmaCounterAvailable;
    ULONG ScatterGatherLimit;
    ULONG DmaAddressWidth;
    ULONG Flags;
    ULONG MinimumTransferUnit;
} DMA_ADAPTER_INFO_V1, *PDMA_ADAPTER_INFO_V1;

typedef struct _DMA_ADAPTER_INFO {
    ULONG Version;
    union {
        DMA_ADAPTER_INFO_V1 V1;
    };
} DMA_ADAPTER_INFO, *PDMA_ADAPTER_INFO;

#define ADAPTER_INFO_SYNCHRONOUS_CALLBACK             0x0001

typedef struct _DMA_TRANSFER_INFO_V1 {
    ULONG MapRegisterCount;
    ULONG ScatterGatherElementCount;
    ULONG ScatterGatherListSize;
} DMA_TRANSFER_INFO_V1, *PDMA_TRANSFER_INFO_V1;

typedef struct _DMA_TRANSFER_INFO {
    ULONG Version;
    union {
        DMA_TRANSFER_INFO_V1 V1;
    };
} DMA_TRANSFER_INFO, *PDMA_TRANSFER_INFO;

#define DMA_TRANSFER_CONTEXT_VERSION1  1

#if defined (_WIN64)
#define DMA_TRANSFER_CONTEXT_SIZE_V1   128
#else
#define DMA_TRANSFER_CONTEXT_SIZE_V1   64
#endif

#define DMA_SYNCHRONOUS_CALLBACK  0x01

typedef struct _PARTITION_DESCRIPTOR {
    UCHAR ActiveFlag;               // Bootable or not
    UCHAR StartingTrack;            // Not used
    UCHAR StartingCylinderLsb;      // Not used
    UCHAR StartingCylinderMsb;      // Not used
    UCHAR PartitionType;            // 12 bit FAT, 16 bit FAT etc.
    UCHAR EndingTrack;              // Not used
    UCHAR EndingCylinderLsb;        // Not used
    UCHAR EndingCylinderMsb;        // Not used
    UCHAR StartingSectorLsb0;       // Hidden sectors
    UCHAR StartingSectorLsb1;
    UCHAR StartingSectorMsb0;
    UCHAR StartingSectorMsb1;
    UCHAR PartitionLengthLsb0;      // Sectors in this partition
    UCHAR PartitionLengthLsb1;
    UCHAR PartitionLengthMsb0;
    UCHAR PartitionLengthMsb1;
} PARTITION_DESCRIPTOR, *PPARTITION_DESCRIPTOR;

#define NUM_PARTITION_TABLE_ENTRIES     4

#define PARTITION_TABLE_OFFSET         (0x1be / 2)
#define BOOT_SIGNATURE_OFFSET          ((0x200 / 2) - 1)
#define BOOT_RECORD_SIGNATURE          (0xaa55)
#define PARTITION_BUFFER_SIZE          2048
#define PARTITION_ACTIVE_FLAG          0x80

NTHALAPI
ARC_STATUS
HalGetEnvironmentVariable (
    _In_ PSTR Variable,
    _In_ USHORT Length,
    _Out_writes_bytes_(Length) PCHAR Buffer
    );

NTHALAPI
ARC_STATUS
HalSetEnvironmentVariable (
    _In_ PSTR Variable,
    _In_ PSTR Value
    );

NTHALAPI
NTSTATUS
HalGetEnvironmentVariableEx (
    _In_ PWSTR VariableName,
    _In_ LPCGUID VendorGuid,
    _Out_writes_bytes_(*ValueLength) PVOID Value,
    _Inout_ PULONG ValueLength,
    _Out_opt_ PULONG Attributes
    );


NTHALAPI
NTSTATUS
HalSetEnvironmentVariableEx (
    _In_ PWSTR VariableName,
    _In_ LPCGUID VendorGuid,
    _In_reads_bytes_(ValueLength) PVOID Value,
    _In_ ULONG ValueLength,
    _In_ ULONG Attributes
    );

NTHALAPI
NTSTATUS
HalEnumerateEnvironmentVariablesEx (
    _In_ ULONG InformationClass,
    _Out_writes_bytes_(*BufferLength) PVOID Buffer,
    _Inout_ PULONG BufferLength
    );

NTHALAPI
NTSTATUS
HalQueryEnvironmentVariableInfoEx (
    _In_ ULONG Attributes,
    _Out_ PULONGLONG MaximumVariableStorageSize,
    _Out_ PULONGLONG RemainingVariableStorageSize,
    _Out_ PULONGLONG MaximumVariableSize
    );

#if defined(_M_IX86) || defined(_M_AMD64)
#define HalGetDmaAlignmentRequirement() 1L
#elif defined(_M_ARM) || defined(_M_ARM64)
#define HalGetDmaAlignmentRequirement() 1L
#endif

#if defined(_ARM_) || defined(_ARM64_)

NTHALAPI
VOID
HalFlushIoBuffers (
    IN PMDL Mdl,
    IN BOOLEAN ReadOperation,
    IN BOOLEAN DmaOperation
    );

#endif

NTHALAPI
VOID
KeFlushWriteBuffer (
    VOID
    );

NTHALAPI
BOOLEAN
HalQueryRealTimeClock (
    _Out_ PTIME_FIELDS TimeFields
    );

NTHALAPI
VOID
HalReturnToFirmware (
    _In_ FIRMWARE_REENTRY Routine
    );

typedef struct _INTERRUPT_CONNECTION_DATA *PINTERRUPT_CONNECTION_DATA;
typedef struct _INTERRUPT_VECTOR_DATA *PINTERRUPT_VECTOR_DATA;
typedef struct _INTERRUPT_REMAPPING_INFO *PINTERRUPT_REMAPPING_INFO;

NTHALAPI
NTSTATUS
HalEnableInterrupt (
    _In_ PINTERRUPT_CONNECTION_DATA ConnectionData
    );

NTHALAPI
NTSTATUS
HalDisableInterrupt (
    _In_ PINTERRUPT_CONNECTION_DATA ConnectionData
    );

NTHALAPI
KIRQL
HalConvertDeviceIdtToIrql (
    _In_ ULONG IdtEntry
    );

NTHALAPI
NTSTATUS
HalGetVectorInput (
    _In_ ULONG Vector,
    _In_ PGROUP_AFFINITY Affinity,
    _Out_ PULONG Input,
    _Out_ PKINTERRUPT_POLARITY Polarity,
    _Out_ PINTERRUPT_REMAPPING_INFO IntRemapInfo
    );

#if !defined(NO_LEGACY_DRIVERS)

DECLSPEC_DEPRECATED_DDK                 // Use Pnp or IoReportDetectedDevice
__drv_preferredFunction("(see documentation)", "Obsolete")
NTHALAPI
NTSTATUS
HalAssignSlotResources (
    _In_ PUNICODE_STRING RegistryPath,
    _In_ PUNICODE_STRING DriverClassName OPTIONAL,
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ INTERFACE_TYPE BusType,
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _Inout_ PCM_RESOURCE_LIST *AllocatedResources
    );

DECLSPEC_DEPRECATED_DDK                 // Use Pnp or IoReportDetectedDevice
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction(
    "IoReportDetectedDevice and IoReportResourceForDetection", "Obsolete")
NTHALAPI
ULONG
HalGetInterruptVector (
    _In_ INTERFACE_TYPE  InterfaceType,
    _In_ ULONG BusNumber,
    _In_ ULONG BusInterruptLevel,
    _In_ ULONG BusInterruptVector,
    _Out_ PKIRQL Irql,
    _Out_ PKAFFINITY Affinity
    );

DECLSPEC_DEPRECATED_DDK                 // Use IRP_MN_QUERY_INTERFACE and IRP_MN_READ_CONFIG
_When_(BusDataType!=0,  /* Cmos == 0 */
    __drv_preferredFunction(
    "IRP_MN_QUERY_INTERFACE and IRP_MN_WRITE_CONFIG requests",
    "Obsolete except for BusDataType==Cmos"))
NTHALAPI
ULONG
HalSetBusData (
    _In_ BUS_DATA_TYPE BusDataType,
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length
    );

#endif // NO_LEGACY_DRIVERS

DECLSPEC_DEPRECATED_DDK                 // Use IRP_MN_QUERY_INTERFACE and IRP_MN_READ_CONFIG
_When_(BusDataType!=0, /* Cmos == 0 */
    __drv_preferredFunction(
    "IRP_MN_QUERY_INTERFACE and IRP_MN_WRITE_CONFIG requests",
    "Obsolete except for BusDataType==Cmos"))
NTHALAPI
ULONG
HalSetBusDataByOffset (
    _In_ BUS_DATA_TYPE BusDataType,
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Offset,
    _In_ ULONG Length
    );

DECLSPEC_DEPRECATED_DDK                 // Use IRP_MN_QUERY_INTERFACE and IRP_MN_READ_CONFIG
__drv_preferredFunction("(see documentation)", "Obsolete")
NTHALAPI
BOOLEAN
HalTranslateBusAddress (
    _In_ INTERFACE_TYPE  InterfaceType,
    _In_ ULONG BusNumber,
    _In_ PHYSICAL_ADDRESS BusAddress,
    _Inout_ PULONG AddressSpace,
    _Out_ PPHYSICAL_ADDRESS TranslatedAddress
    );

NTHALAPI
PVOID
HalAllocateCrashDumpRegisters (
    _In_ PADAPTER_OBJECT AdapterObject,
    _Inout_ PULONG NumberOfMapRegisters
    );

typedef enum _HAL_DMA_CRASH_DUMP_REGISTER_TYPE {
    HalDmaCrashDumpRegisterSet1 = 0,
    HalDmaCrashDumpRegisterSet2,
    HalDmaCrashDumpRegisterSetMax
} HAL_DMA_CRASH_DUMP_REGISTER_TYPE, *PHAL_DMA_CRASH_DUMP_REGISTER_TYPE;

NTSTATUS
HalDmaAllocateCrashDumpRegistersEx (
    _In_ PADAPTER_OBJECT Adapter,
    _In_ ULONG NumberOfMapRegisters,
    _In_ HAL_DMA_CRASH_DUMP_REGISTER_TYPE Type,
    _Out_ PVOID *MapRegisterBase,
    _Out_ PULONG MapRegistersAvailable
    );

NTSTATUS
HalDmaFreeCrashDumpRegistersEx (
    _In_ PADAPTER_OBJECT Adapter,
    _In_ HAL_DMA_CRASH_DUMP_REGISTER_TYPE Type
    );

#if !defined(NO_LEGACY_DRIVERS)

DECLSPEC_DEPRECATED_DDK                 // Use IRP_MN_QUERY_INTERFACE and IRP_MN_READ_CONFIG
_When_(BusDataType!=0,
    __drv_preferredFunction(
        "IRP_MN_QUERY_INTERFACE and IRP_MN_READ_CONFIG requests",
        "Obsolete except for BusDataType==Cmos"))
NTHALAPI
ULONG
HalGetBusData (
    _In_ BUS_DATA_TYPE BusDataType,
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length
    );

#endif // NO_LEGACY_DRIVERS

DECLSPEC_DEPRECATED_DDK                 // Use IRP_MN_QUERY_INTERFACE and IRP_MN_READ_CONFIG
_When_(BusDataType!=0,
    __drv_preferredFunction("IRP_MN_QUERY_INTERFACE",
    "Obsolete except for BusDataType==Cmos"))
NTHALAPI
ULONG
HalGetBusDataByOffset (
    _In_ BUS_DATA_TYPE BusDataType,
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Offset,
    _In_ ULONG Length
    );

DECLSPEC_DEPRECATED_DDK                 // Use IoGetDmaAdapter
_IRQL_requires_max_(PASSIVE_LEVEL)
__drv_preferredFunction("IoGetDmaAdapter", "Obsolete")
NTHALAPI
PADAPTER_OBJECT
HalGetAdapter (
    _In_ PDEVICE_DESCRIPTION DeviceDescription,
    _Out_ PULONG NumberOfMapRegisters
    );

#if !defined(NO_LEGACY_DRIVERS)
NTHALAPI
NTSTATUS
HalAdjustResourceList (
    _Inout_ PIO_RESOURCE_REQUIREMENTS_LIST *pResourceList
    );
#endif // NO_LEGACY_DRIVERS

#if !defined(NO_LEGACY_DRIVERS)
DECLSPEC_DEPRECATED_DDK
NTHALAPI
BOOLEAN
HalMakeBeep(
    _In_ ULONG Frequency
    );
#endif // NO_LEGACY_DRIVERS

NTHALAPI
NTSTATUS
HalGetProcessorIdByNtNumber (
    _In_ ULONG Number,
    _Out_ PULONG Id
    );

typedef enum _IPI_TYPE {
    IpiAffinity = 0,
    IpiAllButSelf,
    IpiAll
} IPI_TYPE;

NTSTATUS
HalRequestIpiSpecifyVector (
    _In_ IPI_TYPE IpiType,
    _In_opt_ PKAFFINITY_EX Affinity,
    _In_ ULONG Vector
    );

typedef
VOID
(*PHAL_LOG_ROUTINE) (
    _In_ ULONG EventId,
    _In_ PVOID Buffer,
    _In_ ULONG Size
    );

typedef struct _HAL_LOG_REGISTER_CONTEXT {
    PHAL_LOG_ROUTINE LogRoutine;
    ULONG Flag;
} HAL_LOG_REGISTER_CONTEXT, *PHAL_LOG_REGISTER_CONTEXT;

NTHALAPI
LARGE_INTEGER
KeQueryPerformanceCounter (
   _Out_opt_ PLARGE_INTEGER PerformanceFrequency
   );

NTHALAPI
VOID
KeStallExecutionProcessor (
    _In_ ULONG MicroSeconds
    );

typedef
NTSTATUS
(*PINSTALL_BUS_HANDLER)(
      _In_ PBUS_HANDLER   Bus
      );

typedef
NTSTATUS
(*pHalRegisterBusHandler)(
    _In_ INTERFACE_TYPE          InterfaceType,
    _In_ BUS_DATA_TYPE           AssociatedConfigurationSpace,
    _In_ ULONG                   BusNumber,
    _In_ INTERFACE_TYPE          ParentBusType,
    _In_ ULONG                   ParentBusNumber,
    _In_ ULONG                   SizeofBusExtensionData,
    _In_ PINSTALL_BUS_HANDLER    InstallBusHandlers,
    _Out_ PBUS_HANDLER           *BusHandler
    );

typedef
PBUS_HANDLER
(FASTCALL *pHalHandlerForBus) (
    _In_ INTERFACE_TYPE InterfaceType,
    _In_ ULONG          BusNumber
    );
typedef
PBUS_HANDLER
(FASTCALL *pHalHandlerForConfigSpace) (
    _In_ BUS_DATA_TYPE  ConfigSpace,
    _In_ ULONG          BusNumber
    );
typedef
VOID
(FASTCALL *pHalReferenceBusHandler) (
    _In_ PBUS_HANDLER   BusHandler
    );
typedef
VOID
(*pHalSetWakeEnable)(
    _In_ BOOLEAN       Enable
    );

typedef
NTSTATUS
(*pHalSetWakeAlarm)(
    _In_opt_ ULONGLONG AcWakeTime,
    _In_opt_ ULONGLONG DcWakeTime
    );

typedef
VOID
(*pHalLocateHiberRanges)(
    _In_ PVOID MemoryMap
    );

typedef struct _HAL_STATE_ELEMENT {
    _Field_size_bytes_(Size) PVOID Address;
    SIZE_T Size;
} HAL_STATE_ELEMENT, *PHAL_STATE_ELEMENT;

typedef CONST HAL_STATE_ELEMENT *PCHAL_STATE_ELEMENT;

typedef struct _HAL_STATE_ELEMENT_INFORMATION {
    PCHAL_STATE_ELEMENT StateElements;
    SIZE_T StateElementCount;
} HAL_STATE_ELEMENT_INFORMATION, *PHAL_STATE_ELEMENT_INFORMATION;

typedef enum _HAL_QUERY_INFORMATION_CLASS {
    HalInstalledBusInformation,
    HalProfileSourceInformation,
    HalInformationClassUnused1,
    HalPowerInformation,
    HalProcessorSpeedInformation,
    HalCallbackInformation,
    HalMapRegisterInformation,
    HalMcaLogInformation,               // Machine Check Abort Information
    HalFrameBufferCachingInformation,
    HalDisplayBiosInformation,
    HalProcessorFeatureInformation,
    HalNumaTopologyInterface,
    HalErrorInformation,                // General MCA, CMC, CPE Error Information.
    HalCmcLogInformation,               // Processor Corrected Machine Check Information
    HalCpeLogInformation,               // Corrected Platform Error Information
    HalQueryMcaInterface,
    HalQueryAMLIIllegalIOPortAddresses,
    HalQueryMaxHotPlugMemoryAddress,
    HalPartitionIpiInterface,
    HalPlatformInformation,
    HalQueryProfileSourceList,
    HalInitLogInformation,
    HalFrequencyInformation,
    HalProcessorBrandString,
    HalHypervisorInformation,
    HalPlatformTimerInformation,
    HalAcpiAuditInformation,
    HalIrtInformation,
    HalSecondaryInterruptInformation,
    HalParkingPageInformation,
    HalNumaRangeTableInformation,
    HalChannelTopologyInformation,
    HalExternalCacheInformation,
    HalQueryDebuggerInformation,
    HalFwBootPerformanceInformation,
    HalFwS3PerformanceInformation,
    HalGetChannelPowerInformation,
    HalQueryStateElementInformation,
    HalPsciInformation,
    HalInterruptControllerInformation,
    HalQueryIommuReservedRegionInformation,
    HalQueryArmErrataInformation,
    // information levels >= 0x8000000 reserved for OEM use
} HAL_QUERY_INFORMATION_CLASS, *PHAL_QUERY_INFORMATION_CLASS;


typedef enum _HAL_SET_INFORMATION_CLASS {
    HalProfileSourceInterval,
    HalProfileSourceInterruptHandler,  // Register performance monitor interrupt callback
    HalMcaRegisterDriver,              // Register Machine Check Abort driver
    HalKernelErrorHandler,
    HalCmcRegisterDriver,              // Register Processor Corrected Machine Check driver
    HalCpeRegisterDriver,              // Register Corrected Platform  Error driver
    HalMcaLog,
    HalCmcLog,
    HalCpeLog,
    HalGenerateCmcInterrupt,           // Used to test CMC
    HalProfileSourceTimerHandler,      // Resister profile timer interrupt callback
    HalEnlightenment,
    HalProfileDpgoSourceInterruptHandler,  // Register performance monitor interrupt callback for dpgo
    HalRegisterSecondaryInterruptInterface,
    HalSetChannelPowerInformation,
    HalI386ExceptionChainTerminatorInformation, // Set x86 SEHOP exception chain terminator
//    HalRegisterPlatformServicesInterface,
} HAL_SET_INFORMATION_CLASS, *PHAL_SET_INFORMATION_CLASS;

typedef struct _HAL_SET_I386_EXCEPTION_CHAIN_TERMINATOR_INFORMATION {
    PVOID ExceptionChainTerminator;
} HAL_SET_I386_EXCEPTION_CHAIN_TERMINATOR_INFORMATION, *PHAL_SET_I386_EXCEPTION_CHAIN_TERMINATOR_INFORMATION;

typedef
NTSTATUS
(*pHalQuerySystemInformation)(
    _In_ HAL_QUERY_INFORMATION_CLASS  InformationClass,
    _In_ ULONG     BufferSize,
    _Out_writes_bytes_to_(BufferSize, *ReturnedLength) PVOID Buffer,
    _Out_ PULONG   ReturnedLength
    );

NTSTATUS
HaliQuerySystemInformation (
    _In_ HAL_QUERY_INFORMATION_CLASS InformationClass,
    _In_ ULONG BufferSize,
    _Out_writes_bytes_to_(BufferSize, *ReturnedLength) PVOID Buffer,
    _Out_ PULONG ReturnedLength
    );

typedef
NTSTATUS
(*pHalSetSystemInformation)(
    _In_ HAL_SET_INFORMATION_CLASS    InformationClass,
    _In_ ULONG     BufferSize,
    _In_ PVOID     Buffer
    );

NTSTATUS
HaliSetSystemInformation (
    _In_ HAL_SET_INFORMATION_CLASS InformationClass,
    _In_ ULONG BufferSize,
    _In_reads_bytes_(BufferSize) PVOID Buffer
    );

typedef
VOID
(FASTCALL *pHalExamineMBR)(
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ ULONG MBRTypeIdentifier,
    _Out_ PVOID *Buffer
    );

typedef
NTSTATUS
(FASTCALL *pHalIoReadPartitionTable)(
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ BOOLEAN ReturnRecognizedPartitions,
    _Out_ struct _DRIVE_LAYOUT_INFORMATION **PartitionBuffer
    );

typedef
NTSTATUS
(FASTCALL *pHalIoSetPartitionInformation)(
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ ULONG PartitionNumber,
    _In_ ULONG PartitionType
    );

typedef
NTSTATUS
(FASTCALL *pHalIoWritePartitionTable)(
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG SectorSize,
    _In_ ULONG SectorsPerTrack,
    _In_ ULONG NumberOfHeads,
    _In_ struct _DRIVE_LAYOUT_INFORMATION *PartitionBuffer
    );

typedef
NTSTATUS
(*pHalQueryBusSlots)(
    _In_ PBUS_HANDLER         BusHandler,
    _In_ ULONG                BufferSize,
    _Out_ PULONG              SlotNumbers,
    _Out_ PULONG              ReturnedLength
    );

typedef
NTSTATUS
(*pHalInitPnpDriver)(
    VOID
    );

NTSTATUS
HaliInitPnpDriver (
    VOID
    );

typedef struct _PM_DISPATCH_TABLE {
    ULONG   Signature;
    ULONG   Version;
    PVOID   Function[1];
} PM_DISPATCH_TABLE, *PPM_DISPATCH_TABLE;

typedef
NTSTATUS
(*pHalInitPowerManagement)(
    _In_ PPM_DISPATCH_TABLE  PmDriverDispatchTable,
    _Out_ PPM_DISPATCH_TABLE *PmHalDispatchTable
    );

NTSTATUS
HaliInitPowerManagement (
    _In_ PPM_DISPATCH_TABLE PmDriverDispatchTable,
    _Inout_ PPM_DISPATCH_TABLE *PmHalDispatchTable
    );

typedef
struct _DMA_ADAPTER *
(*pHalGetDmaAdapter)(
    _In_opt_ PVOID PhysicalDeviceObject,
    _In_ struct _DEVICE_DESCRIPTION *DeviceDescriptor,
    _Out_ PULONG NumberOfMapRegisters
    );

struct _DMA_ADAPTER *
HaliGetDmaAdapter (
    _In_opt_ PVOID PhysicalDeviceObject,
    _In_ struct _DEVICE_DESCRIPTION *DeviceDescriptor,
    _Out_ PULONG NumberOfMapRegisters
    );

typedef
NTSTATUS
(*pHalGetInterruptTranslator)(
    _In_ INTERFACE_TYPE ParentInterfaceType,
    _In_ ULONG ParentBusNumber,
    _In_ INTERFACE_TYPE BridgeInterfaceType,
    _In_ USHORT Size,
    _In_ USHORT Version,
    _Out_ PTRANSLATOR_INTERFACE Translator,
    _Out_ PULONG BridgeBusNumber
    );

NTSTATUS
HaliGetInterruptTranslator (
    _In_ INTERFACE_TYPE ParentInterfaceType,
    _In_ ULONG ParentBusNumber,
    _In_ INTERFACE_TYPE BridgeInterfaceType,
    _In_ USHORT Size,
    _In_ USHORT Version,
    _Out_ PTRANSLATOR_INTERFACE Translator,
    _Out_ PULONG BridgeBusNumber
    );

typedef
BOOLEAN
(*pHalTranslateBusAddress)(
    _In_ INTERFACE_TYPE  InterfaceType,
    _In_ ULONG BusNumber,
    _In_ PHYSICAL_ADDRESS BusAddress,
    _Inout_ PULONG AddressSpace,
    _Out_ PPHYSICAL_ADDRESS TranslatedAddress
    );

typedef
NTSTATUS
(*pHalAssignSlotResources) (
    _In_ PUNICODE_STRING RegistryPath,
    _In_ PUNICODE_STRING DriverClassName OPTIONAL,
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ INTERFACE_TYPE BusType,
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _Inout_ PCM_RESOURCE_LIST *AllocatedResources
    );

typedef
VOID
(*pHalHaltSystem) (
    VOID
    );

typedef
BOOLEAN
(*pHalResetDisplay) (
    VOID
    );

typedef struct _MAP_REGISTER_ENTRY {
    PVOID   MapRegister;
    BOOLEAN WriteToDevice;
} MAP_REGISTER_ENTRY, *PMAP_REGISTER_ENTRY;

typedef
NTSTATUS
(*pHalAllocateMapRegisters)(
    _In_ struct _ADAPTER_OBJECT *DmaAdapter,
    _In_ ULONG NumberOfMapRegisters,
    _In_ ULONG BaseAddressCount,
    _Out_ PMAP_REGISTER_ENTRY MapRegsiterArray
    );

NTSTATUS
HalAllocateMapRegisters(
    _In_ struct _ADAPTER_OBJECT *DmaAdapter,
    _In_ ULONG NumberOfMapRegisters,
    _In_ ULONG BaseAddressCount,
    _Out_ PMAP_REGISTER_ENTRY MapRegsiterArray
    );

typedef
UCHAR
(*pHalVectorToIDTEntry) (
    ULONG Vector
);

typedef
BOOLEAN
(*pHalFindBusAddressTranslation) (
    _In_ PHYSICAL_ADDRESS BusAddress,
    _Inout_ PULONG AddressSpace,
    _Out_ PPHYSICAL_ADDRESS TranslatedAddress,
    _Inout_ PULONG_PTR Context,
    _In_ BOOLEAN NextBus
    );

typedef
NTSTATUS
(*pHalStartMirroring)(
    VOID
    );

typedef
NTSTATUS
(*pHalEndMirroring)(
    _In_ ULONG PassNumber
    );

typedef
NTSTATUS
(*pHalMirrorPhysicalMemory)(
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ LARGE_INTEGER NumberOfBytes
    );

typedef
NTSTATUS
(*pHalMirrorVerify)(
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ LARGE_INTEGER NumberOfBytes
    );

typedef struct {
    UCHAR     Type;  //CmResourceType
    BOOLEAN   Valid;
    UCHAR     Reserved[2];
    PUCHAR    TranslatedAddress;
    ULONG     Length;
} DEBUG_DEVICE_ADDRESS, *PDEBUG_DEVICE_ADDRESS;

typedef struct {
    PHYSICAL_ADDRESS  Start;
    PHYSICAL_ADDRESS  MaxEnd;
    PVOID             VirtualAddress;
    ULONG             Length;
    BOOLEAN           Cached;
    BOOLEAN           Aligned;
} DEBUG_MEMORY_REQUIREMENTS, *PDEBUG_MEMORY_REQUIREMENTS;

typedef enum {
    KdNameSpacePCI,
    KdNameSpaceACPI,
    KdNameSpaceAny,
    KdNameSpaceNone,
    KdNameSpaceMax,
} KD_NAMESPACE_ENUM, *PKD_NAMESPACE_ENUM;

typedef enum {
    KdConfigureDeviceAndContinue,
    KdSkipDeviceAndContinue,
    KdConfigureDeviceAndStop,
    KdSkipDeviceAndStop,
} KD_CALLBACK_ACTION, *PKD_CALLBACK_ACTION;

typedef struct _DEBUG_TRANSPORT_DATA {
    ULONG HwContextSize;
} DEBUG_TRANSPORT_DATA, *PDEBUG_TRANSPORT_DATA;

#define MAXIMUM_DEBUG_BARS 6

#define DBG_DEVICE_FLAG_HAL_SCRATCH_ALLOCATED 0x01
#define DBG_DEVICE_FLAG_BARS_MAPPED           0x02
#define DBG_DEVICE_FLAG_SCRATCH_ALLOCATED     0x04

typedef struct _DEBUG_DEVICE_DESCRIPTOR {
    ULONG     Bus;
    ULONG     Slot;
    USHORT    Segment;
    USHORT    VendorID;
    USHORT    DeviceID;
    UCHAR     BaseClass;
    UCHAR     SubClass;
    UCHAR     ProgIf;
    UCHAR     Flags;
    BOOLEAN   Initialized;
    BOOLEAN   Configured;
    DEBUG_DEVICE_ADDRESS BaseAddress[MAXIMUM_DEBUG_BARS];
    DEBUG_MEMORY_REQUIREMENTS Memory;
    USHORT    PortType;
    USHORT    PortSubtype;
    PVOID     OemData;
    ULONG     OemDataLength;
    KD_NAMESPACE_ENUM NameSpace;
    PWCHAR    NameSpacePath;
    ULONG     NameSpacePathLength;
    DEBUG_TRANSPORT_DATA TransportData;
} DEBUG_DEVICE_DESCRIPTOR, *PDEBUG_DEVICE_DESCRIPTOR;

typedef struct _PCI_DEBUGGING_DEVICE_IN_USE {
    USHORT Segment;
    ULONG Bus;
    ULONG Slot;
} PCI_DEBUGGING_DEVICE_IN_USE, *PPCI_DEBUGGING_DEVICE_IN_USE;

typedef struct _ACPI_DEBUGGING_DEVICE_IN_USE {
    ULONG NameSpacePathLength;
    WCHAR NameSpacePath[ANYSIZE_ARRAY];
} ACPI_DEBUGGING_DEVICE_IN_USE, *PACPI_DEBUGGING_DEVICE_IN_USE;

typedef struct _DEBUGGING_DEVICE_IN_USE {
    KD_NAMESPACE_ENUM NameSpace;
    ULONG StructureLength;
    union {
        ACPI_DEBUGGING_DEVICE_IN_USE AcpiDevice;
        PCI_DEBUGGING_DEVICE_IN_USE PciDevice;
    };
} DEBUGGING_DEVICE_IN_USE, *PDEBUGGING_DEVICE_IN_USE;

typedef struct _DEBUGGING_DEVICE_IN_USE_INFORMATION {
    ULONG DeviceCount;
    DEBUGGING_DEVICE_IN_USE Device[ANYSIZE_ARRAY];
} DEBUGGING_DEVICE_IN_USE_INFORMATION, *PDEBUGGING_DEVICE_IN_USE_INFORMATION;

typedef
KD_CALLBACK_ACTION
(*PDEBUG_DEVICE_FOUND_FUNCTION) (
    PDEBUG_DEVICE_DESCRIPTOR Device
    );

typedef
NTSTATUS
(*pKdEnumerateDebuggingDevices) (
    _In_ PVOID LoaderBlock,
    _Inout_ PDEBUG_DEVICE_DESCRIPTOR Device,
    _In_ PDEBUG_DEVICE_FOUND_FUNCTION Callback
    );

typedef
NTSTATUS
(*pKdSetupPciDeviceForDebugging)(
    _In_    PVOID                     LoaderBlock,   OPTIONAL
    _Inout_ PDEBUG_DEVICE_DESCRIPTOR  PciDevice
);

typedef
NTSTATUS
(*pKdReleasePciDeviceForDebugging)(
    _Inout_ PDEBUG_DEVICE_DESCRIPTOR  PciDevice
);

typedef
NTSTATUS
(*pKdSetupIntegratedDeviceForDebugging)(
    _In_    PVOID                     LoaderBlock,   OPTIONAL
    _Inout_ PDEBUG_DEVICE_DESCRIPTOR  IntegratedDevice
);

typedef
NTSTATUS
(*pKdReleaseIntegratedDeviceForDebugging)(
    _Inout_ PDEBUG_DEVICE_DESCRIPTOR  IntegratedDevice
);

typedef
PVOID
(*pKdGetAcpiTablePhase0)(
    _In_ struct _LOADER_PARAMETER_BLOCK *LoaderBlock,
    _In_ ULONG Signature
    );

typedef
VOID
(*pKdCheckPowerButton)(
    VOID
    );

typedef
VOID
(*pHalEndOfBoot)(
    VOID
    );

typedef
PVOID
(*pKdMapPhysicalMemory64)(
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ ULONG NumberPages,
    _In_ BOOLEAN FlushCurrentTLB
    );

typedef
VOID
(*pKdUnmapVirtualAddress)(
    _In_ PVOID VirtualAddress,
    _In_ ULONG NumberPages,
    _In_ BOOLEAN FlushCurrentTLB
    );

typedef
ULONG
(*pKdGetPciDataByOffset)(
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Offset,
    _In_ ULONG Length
    );

typedef
ULONG
(*pKdSetPciDataByOffset)(
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Offset,
    _In_ ULONG Length
    );

typedef
PVOID
(*pHalGetAcpiTable)(
    _In_ ULONG Signature,
    _In_opt_ PCSTR OemId,
    _In_opt_ PCSTR OemTableId
    );

typedef
VOID
(*PCI_ERROR_HANDLER_CALLBACK)(
    VOID
    );

typedef
VOID
(*pHalSetPciErrorHandlerCallback)(
    _In_ PCI_ERROR_HANDLER_CALLBACK Callback
    );

typedef
ULONG
(*pHalGetInterruptVector)(
    _In_ INTERFACE_TYPE InterfaceType,
    _In_ ULONG BusNumber,
    _In_ ULONG BusInterruptLevel,
    _In_ ULONG BusInterruptVector,
    _Out_ PKIRQL Irql,
    _Out_ PKAFFINITY Affinity
    );

typedef
NTSTATUS
(*pHalGetVectorInput)(
    _In_ ULONG Vector,
    _In_ PGROUP_AFFINITY Affinity,
    _Out_ PULONG Input,
    _Out_ PKINTERRUPT_POLARITY Polarity,
    _Out_ PINTERRUPT_REMAPPING_INFO IntRemapInfo
    );

typedef
NTSTATUS
(*pHalLoadMicrocode)(
    _In_ PVOID ImageHandle
    );

typedef
NTSTATUS
(*pHalUnloadMicrocode)(
    VOID
    );

typedef
NTSTATUS
(*pHalPostMicrocodeUpdate)(
    VOID
    );

typedef
NTSTATUS
(*pHalAllocateMessageTarget)(
    _In_ PDEVICE_OBJECT Owner,
    _In_ PGROUP_AFFINITY ProcessorSet,
    _In_ ULONG NumberOfIdtEntries,
    _In_ KINTERRUPT_MODE Mode,
    _In_ BOOLEAN ShareVector,
    _Out_ PULONG Vector,
    _Out_ PKIRQL Irql,
    _Out_ PULONG IdtEntry
    );

typedef
VOID
(*pHalFreeMessageTarget)(
    _In_ PDEVICE_OBJECT Owner,
    _In_ ULONG Vector,
    _In_ PGROUP_AFFINITY ProcessorSet
    );

#define HAL_DP_REPLACE_PHASE_QUIESCE    0
#define HAL_DP_REPLACE_PHASE_SWAP       1
#define HAL_DP_REPLACE_PHASE_WAKE       2
#define HAL_DP_REPLACE_PHASE_CANCEL     3

typedef struct _PNP_REPLACE_PROCESSOR_LIST *PPNP_REPLACE_PROCESSOR_LIST;

#define HAL_DP_REPLACE_PROCESSOR_ID_RECONFIGURE     0x01
#define HAL_DP_REPLACE_HARDWARE_QUIESCE             0x02

typedef struct _HAL_DP_REPLACE_PARAMETERS {
    ULONG Flags;
    PPNP_REPLACE_PROCESSOR_LIST TargetProcessors;
    PPNP_REPLACE_PROCESSOR_LIST SpareProcessors;
} HAL_DP_REPLACE_PARAMETERS, *PHAL_DP_REPLACE_PARAMETERS;

typedef
NTSTATUS
(*pHalDpReplaceBegin)(
    _In_ PHAL_DP_REPLACE_PARAMETERS Parameters,
    _Outptr_ PVOID *ReplaceContext
    );

typedef
VOID
(*pHalDpReplaceTarget)(
    _In_ PVOID ReplaceContext
    );

typedef
NTSTATUS
(*pHalDpReplaceControl)(
    _In_ ULONG Phase,
    _In_ PVOID ReplaceContext
    );

typedef
VOID
(*pHalDpReplaceEnd)(
    _In_ PVOID ReplaceContext
    );

typedef
NTSTATUS
(*pHalDpMaskLevelTriggeredInterrupts)(
    VOID
    );

typedef
NTSTATUS
(*pHalDpUnmaskLevelTriggeredInterrupts)(
    VOID
    );

typedef
NTSTATUS
(*pHalDpGetInterruptReplayState)(
    _In_ PVOID ReplaceContext,
    _Outptr_ PVOID *Buffer
    );

typedef
NTSTATUS
(*pHalDpReplayInterrupts)(
    _In_ PVOID InterruptState
    );

#define HAL_PREPARE_NMI_IN_PROGRESS     0x00000001UL

typedef
VOID
(*pHalPrepareForBugcheck)(
    _In_ ULONG Flags
    );

typedef
BOOLEAN
(*pHalQueryWakeTime)(
    _Out_ PULONGLONG WakeTime,
    _Out_opt_ PULONGLONG TscOffset
    );

typedef
BOOLEAN
(*pHalQueryIoPortAccessSupported)(
    VOID
    );

typedef
VOID
(*pHalReportIdleStateUsage)(
    _In_ UCHAR DeepestHardwareIdleState,
    _In_ PKAFFINITY_EX TargetSet
    );

typedef
VOID
(*pHalTscSynchronization)(
    _In_ BOOLEAN ForcedSynchronization,
    _In_opt_ PULONG TargetProcessor
    );

typedef struct _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR
    *PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR;

typedef struct _WHEA_PROCESSOR_GENERIC_ERROR_SECTION
    *PWHEA_PROCESSOR_GENERIC_ERROR_SECTION;

typedef
NTSTATUS
(*pHalWheaInitProcessorGenericSection)(
    _Out_ PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR Descriptor,
    _Out_ PWHEA_PROCESSOR_GENERIC_ERROR_SECTION Section
    );

typedef
VOID
(*pHalStopLegacyUsbInterrupts)(
    _In_ SYSTEM_POWER_STATE LastSystemState
    );

typedef
NTSTATUS
(*pHalReadWheaPhysicalMemory)(
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ ULONG Length,
    _Out_writes_bytes_(Length) PVOID Data
    );

typedef
NTSTATUS
(*pHalWriteWheaPhysicalMemory)(
    _In_ PHYSICAL_ADDRESS PhysicalAddress,
    _In_ ULONG Length,
    _In_reads_bytes_(Length) PVOID Data
    );


#if !defined(_ARM64_) && !defined(_ARM_)
#define _HAL_ENLIGHTENMENT_INFORMATION _HAL_INTEL_ENLIGHTENMENT_INFORMATION
#define  HAL_ENLIGHTENMENT_INFORMATION  HAL_INTEL_ENLIGHTENMENT_INFORMATION
#define PHAL_ENLIGHTENMENT_INFORMATION PHAL_INTEL_ENLIGHTENMENT_INFORMATION
#else
#define _HAL_ENLIGHTENMENT_INFORMATION _HAL_ARM_ENLIGHTENMENT_INFORMATION
#define  HAL_ENLIGHTENMENT_INFORMATION  HAL_ARM_ENLIGHTENMENT_INFORMATION
#define PHAL_ENLIGHTENMENT_INFORMATION PHAL_ARM_ENLIGHTENMENT_INFORMATION
#endif

typedef struct _HAL_ENLIGHTENMENT_INFORMATION
    HAL_ENLIGHTENMENT_INFORMATION, *PHAL_ENLIGHTENMENT_INFORMATION;

typedef
VOID
(*pHalGetEnlightenmentInformation)(
    PHAL_ENLIGHTENMENT_INFORMATION EnlightenmentInformation
    );

typedef
PVOID
(*pHalAllocateEarlyPages)(
    _In_ PLOADER_PARAMETER_BLOCK LoaderBlock,
    _In_ ULONG PageCount,
    _Out_ PULONG64 PhysicalAddress,
    _In_ ULONG Protection
    );

typedef
PVOID
(*pHalMapEarlyPages)(
    _In_ ULONG64 PhysicalAddress,
    _In_ ULONG PageCount,
    _In_ ULONG Protection
    );

#define HAL_PREPARE_FOR_IDLE_INTERRUPTIBLE   (1 << 0)

typedef
NTSTATUS
(*pHalPrepareProcessorForIdle) (
    _In_ ULONG Flags
    );

typedef
VOID
(*pHalResumeProcessorFromIdle) (
   VOID
   );

typedef
VOID
(*pHalNotifyProcessorFreeze) (
    _In_ BOOLEAN Freezing,
    _In_ BOOLEAN ThawingToSpinLoop
    );

typedef
VOID
(*pHalRegisterLogRoutine) (
    _In_ PHAL_LOG_REGISTER_CONTEXT Context
    );

typedef enum _HAL_CLOCK_TIMER_MODE {
    HalClockTimerModePeriodic,
    HalClockTimerModeOneShot,
    HalClockTimerModeMax
} HAL_CLOCK_TIMER_MODE, *PHAL_CLOCK_TIMER_MODE;

typedef struct _HAL_CLOCK_TIMER_CONFIGURATION {
    union {
        BOOLEAN Flags;
        struct {
            BOOLEAN AlwaysOnTimer: 1;
            BOOLEAN HighLatency: 1;
            BOOLEAN PerCpuTimer: 1;
            BOOLEAN DynamicTickSupported: 1;
        };
    };

    ULONG KnownType;
    ULONG Capabilities;
    ULONG64 MaxIncrement;
    ULONG MinIncrement;
} HAL_CLOCK_TIMER_CONFIGURATION, *PHAL_CLOCK_TIMER_CONFIGURATION;

typedef
VOID
(*pHalGetClockConfiguration) (
    _Out_ PHAL_CLOCK_TIMER_CONFIGURATION Configuration
    );

typedef
VOID
(*pHalClockTimerActivate) (
    _In_ BOOLEAN ClockOwner
    );

typedef
VOID
(*pHalClockTimerInitialize) (
    VOID
    );

typedef
VOID
 (*pHalClockTimerStop) (
    VOID
    );

typedef
NTSTATUS
(*pHalClockTimerArm) (
    _In_ HAL_CLOCK_TIMER_MODE Mode,
    _In_ ULONG64 RequestedInteval,
    _Out_ PULONG64 ActualInterval
    );

typedef
BOOLEAN
(*pHalTimerOnlyClockInterruptPending) (
    VOID
    );

typedef struct _HAL_IOMMU_DISPATCH HAL_IOMMU_DISPATCH, *PHAL_IOMMU_DISPATCH;

typedef
VOID
(*pHalIommuRegisterDispatchTable) (
    _Inout_ PHAL_IOMMU_DISPATCH DispatchTable
    );

typedef
ULONG
(*pHalVectorToIDTEntryEx) (
    ULONG Vector
);

typedef
NTSTATUS
(*pHalSecondaryInterruptQueryPrimaryInformation) (
    _In_ PINTERRUPT_VECTOR_DATA VectorData,
    _Out_ PULONG PrimaryGsiv
    );

typedef
BOOLEAN
(*pHalIsInterruptTypeSecondary) (
    _In_ ULONG Type,                        // INTERRUPT_CONNECTION_TYPE
    _In_ ULONG InputGsiv
    );

#define HAL_MASK_UNMASK_FLAGS_NONE (0x0)
#define HAL_MASK_UNMASK_FLAGS_SERVICING_DEFERRED (0x1)
#define HAL_MASK_UNMASK_FLAGS_SERVICING_COMPLETE (0x2)

typedef
NTSTATUS
(*pHalMaskInterrupt) (
    _In_ ULONG InputGsiv,
    _In_ ULONG Flags
    );

typedef
NTSTATUS
(*pHalUnmaskInterrupt) (
    _In_ ULONG InputGsiv,
    _In_ ULONG Flags
    );

typedef
NTSTATUS
(*pHalAllocateGsivForSecondaryInterrupt) (
    _In_reads_bytes_(OwnerNameLength) PCCHAR OwnerName,
    _In_ USHORT OwnerNameLength,
    _Out_ PULONG Gsiv
    );

typedef
NTSTATUS
(*pHalInterruptVectorDataToGsiv) (
    _In_ PINTERRUPT_VECTOR_DATA VectorData,
    _Out_ PULONG Gsiv
    );

typedef
NTSTATUS
(*pHalAddInterruptRemapping) (
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _In_ PPCI_BUSMASTER_DESCRIPTOR BusMasterDescriptor,
    _In_range_(0, 3) UCHAR PhantomBits,
    _Inout_updates_(VectorCount) PINTERRUPT_VECTOR_DATA VectorData,
    ULONG VectorCount
    );

typedef
VOID
(*pHalRemoveInterruptRemapping) (
    _In_ ULONG BusNumber,
    _In_ ULONG SlotNumber,
    _In_ PPCI_BUSMASTER_DESCRIPTOR BusMasterDescriptor,
    _In_range_(0, 3) UCHAR PhantomBits,
    _Inout_updates_(VectorCount) PINTERRUPT_VECTOR_DATA VectorData,
    ULONG VectorCount
    );

typedef
VOID
(*pHalSaveAndDisableHvEnlightenment) (
    VOID
    );

typedef
VOID
(*pHalRestoreHvEnlightenment) (
    VOID
    );

typedef
VOID
(*pHalFlushIoBuffersExternalCache) (
    IN PMDL  Mdl,
    IN BOOLEAN  ReadOperation
    );

typedef
VOID
(*pHalFlushIoRectangleExternalCache) (
    IN PMDL Mdl,
    IN ULONG StartOffset,
    IN ULONG Width,
    IN ULONG Height,
    IN ULONG Stride,
    IN BOOLEAN ReadOperation
    );

typedef
VOID
(*pHalFlushExternalCache) (
    IN BOOLEAN Invalidate
    );

typedef
VOID
(*pHalFlushAndInvalidatePageExternalCache) (
    IN PHYSICAL_ADDRESS PhysicalAddress
    );

typedef
NTSTATUS
(*pHalPciEarlyRestore) (
    _In_ SYSTEM_POWER_STATE SleepState
    );

typedef
VOID
(*pHalPciLateRestore) (
    VOID
    );

typedef
NTSTATUS
(*pHalGetProcessorId) (
    _In_ ULONG ProcessorIndex,
    _Out_ ULONG *Identifier
    );

typedef struct _HAL_PMC_COUNTERS *PMC_HANDLE;

typedef
NTSTATUS
(*pHalAllocatePmcCounterSet) (
    _In_ ULONG ProcessorIndex,
    _In_reads_(SourceCount) KPROFILE_SOURCE *SourceList,
    _In_ ULONG SourceCount,
    _Out_ PMC_HANDLE *Handle
    );

typedef
VOID
(*pHalFreePmcCounterSet) (
    _In_ PMC_HANDLE Handle
    );

typedef
VOID
(*pHalCollectPmcCounters) (
    _In_ PMC_HANDLE Handle,
    _Out_ PULONG64 Data
    );

typedef
ULONGLONG
(*pHalTimerQueryCycleCounter) (
    _Out_opt_ PULONGLONG CycleCounterFrequency
    );

typedef
NTSTATUS
PROCESSOR_HALT_ROUTINE (
    _Inout_opt_ PVOID Context
    );

typedef PROCESSOR_HALT_ROUTINE *PPROCESSOR_HALT_ROUTINE;

// end_wdm

typedef
NTSTATUS
(*pHalProcessorHalt) (
    _In_ ULONG Flags,
    _Inout_opt_ PVOID Context,
    _In_ PPROCESSOR_HALT_ROUTINE Halt
    );

typedef
VOID
(*pHalPciMarkHiberPhase) (
    VOID
    );

typedef
NTSTATUS
(*pHalQueryProcessorRestartEntryPoint) (
    _Out_ PPHYSICAL_ADDRESS EntryPoint
    );

typedef
NTSTATUS
(*pHalRequestInterrupt) (
    _In_ ULONG Gsiv
    );

typedef
VOID
(*pHalPowerEarlyRestore) (
    ULONG Phase
    );

typedef
NTSTATUS
(*pHalUpdateCapsule) (
    _In_ PVOID CapsuleHeaderArray,
    _In_ ULONG CapsuleCount,
    _In_opt_ PHYSICAL_ADDRESS ScatterGatherList
    );

typedef
NTSTATUS
(*pHalQueryCapsuleCapabilities) (
    _In_ PVOID CapsuleHeaderArray,
    _In_ ULONG CapsuleCount,
    _Out_ PULONGLONG MaximumCapsuleSize,
    _Out_ PULONG ResetType
    );

typedef
BOOLEAN
(*pHalPciMultiStageResumeCapable) (
    VOID
    );

typedef
VOID
(*pHalDmaFreeCrashDumpRegisters) (
    _In_ ULONG Phase
    );

typedef
BOOLEAN
(*pHalAcpiAoacCapable) (
    VOID
    );

typedef
NTSTATUS
(*pHalInterruptSetDestination) (
    __in ULONG Gsiv,
    __in PINTERRUPT_VECTOR_DATA VectorData,
    __in PGROUP_AFFINITY TargetProcessors
    );

#define HAL_UNMASKED_INTERRUPT_INFORMATION_V1 0x00000001
#define HAL_UNMASKED_INTERRUPT_INFORMATION_MINIMUM_SIZE \
    RTL_SIZEOF_THROUGH_FIELD(HAL_UNMASKED_INTERRUPT_INFORMATION, DeviceHandle)

typedef union _HAL_UNMASKED_INTERRUPT_FLAGS {
    struct {
        USHORT SecondaryInterrupt: 1;
        USHORT Reserved: 15;
    };

    USHORT AsUSHORT;

} HAL_UNMASKED_INTERRUPT_FLAGS, *PHAL_UNMASKED_INTERRUPT_FLAGS;

typedef struct _HAL_UNMASKED_INTERRUPT_INFORMATION {
    USHORT Version;
    USHORT Size;
    HAL_UNMASKED_INTERRUPT_FLAGS Flags;
    KINTERRUPT_MODE Mode;
    KINTERRUPT_POLARITY Polarity;
    ULONG Gsiv;
    USHORT PinNumber;
    PVOID DeviceHandle;
} HAL_UNMASKED_INTERRUPT_INFORMATION, *PHAL_UNMASKED_INTERRUPT_INFORMATION;

typedef
BOOLEAN
(HAL_ENUMERATE_INTERRUPT_SOURCE_CALLBACK)(
    _In_ PVOID Context,
    _In_ PHAL_UNMASKED_INTERRUPT_INFORMATION InterruptInformation
    );

typedef HAL_ENUMERATE_INTERRUPT_SOURCE_CALLBACK
    *PHAL_ENUMERATE_INTERRUPT_SOURCE_CALLBACK;

typedef
NTSTATUS
(*pHalEnumerateUnmaskedInterrupts) (
    _In_ PHAL_ENUMERATE_INTERRUPT_SOURCE_CALLBACK Callback,
    _In_ PVOID Context,
    _Out_ PHAL_UNMASKED_INTERRUPT_INFORMATION InterruptInformation
    );

typedef
PVOID
(*pHalAcpiGetMultiNode) (
    VOID
    );

typedef
void
(HALREBOOTHANDLER)(
    _In_ ULONG ProcessorNumber,
    _Inout_opt_ volatile LONG* ProcessorsStarted
    );

typedef HALREBOOTHANDLER *PHALREBOOTHANDLER;

typedef
PHALREBOOTHANDLER
(*pHalPowerSetRebootHandler) (
    _In_opt_ PHALREBOOTHANDLER NewHandler
    );

typedef
NTSTATUS
(*pHalTimerWatchdogStart) (
    VOID
    );

typedef
VOID
(*pHalTimerWatchdogResetCountdown) (
    _In_ LOGICAL SetWakeTimer
    );

typedef
NTSTATUS
(*pHalTimerWatchdogStop) (
    VOID
    );

typedef
BOOLEAN
(*pHalTimerWatchdogGeneratedLastReset) (
    VOID
    );

typedef
NTSTATUS
(*pHalTimerWatchdogTriggerSystemReset) (
    BOOLEAN ResetViaClockInterrupt
    );

typedef
NTSTATUS
(*pHalInterruptGetHighestPriorityInterrupt) (
    __out PULONG HighestPendingVector,
    __out PBOOLEAN SingleInterrupt
    );

typedef
NTSTATUS
(*pHalProcessorOn) (
    _In_ ULONG NtNumber
    );

typedef
NTSTATUS
(*pHalProcessorOff) (
    VOID
    );

typedef
NTSTATUS
(*pHalProcessorFreeze) (
    VOID
    );

typedef
NTSTATUS
(*pHalDmaLinkDeviceObjectByToken) (
    _In_ ULONG_PTR Token,
    _In_opt_ PDEVICE_OBJECT DeviceObject
    );

typedef
NTSTATUS
(*pHalDmaCheckAdapterToken) (
    _In_ ULONG_PTR Token
    );

typedef
NTSTATUS
(*pHalTimerConvertAuxiliaryCounterToPerformanceCounter) (
    __in ULONG64 AuxiliaryCounterValue,
    __out PULONG64 PerformanceCounterValueOut,
    __out_opt PULONG64 ConversionErrorOut
    );

typedef
NTSTATUS
(*pHalTimerConvertPerformanceCounterToAuxiliaryCounter) (
    __in ULONG64 PerformanceCounterValue,
    __out PULONG64 AuxiliaryCounterValueOut,
    __out_opt PULONG64 ConversionErrorOut
    );

typedef
NTSTATUS
(*pHalTimerQueryAuxiliaryCounterFrequency) (
    __out PULONG64 AuxiliaryCounterFrequencyOut
    );

typedef struct {
    ULONG                           Version;
    pHalQuerySystemInformation      HalQuerySystemInformation;
    pHalSetSystemInformation        HalSetSystemInformation;
    pHalQueryBusSlots               HalQueryBusSlots;
    ULONG                           Spare1;
    pHalExamineMBR                  HalExamineMBR;
    pHalIoReadPartitionTable        HalIoReadPartitionTable;
    pHalIoSetPartitionInformation   HalIoSetPartitionInformation;
    pHalIoWritePartitionTable       HalIoWritePartitionTable;

    pHalHandlerForBus               HalReferenceHandlerForBus;
    pHalReferenceBusHandler         HalReferenceBusHandler;
    pHalReferenceBusHandler         HalDereferenceBusHandler;

    pHalInitPnpDriver               HalInitPnpDriver;
    pHalInitPowerManagement         HalInitPowerManagement;

    pHalGetDmaAdapter               HalGetDmaAdapter;
    pHalGetInterruptTranslator      HalGetInterruptTranslator;

    pHalStartMirroring              HalStartMirroring;
    pHalEndMirroring                HalEndMirroring;
    pHalMirrorPhysicalMemory        HalMirrorPhysicalMemory;
    pHalEndOfBoot                   HalEndOfBoot;
    pHalMirrorVerify                HalMirrorVerify;

    pHalGetAcpiTable                HalGetCachedAcpiTable;
    pHalSetPciErrorHandlerCallback  HalSetPciErrorHandlerCallback;

} HAL_DISPATCH, *PHAL_DISPATCH;

#if defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_)

extern  PHAL_DISPATCH   HalDispatchTable;
#define HALDISPATCH     HalDispatchTable

#else

extern  HAL_DISPATCH    HalDispatchTable;
#define HALDISPATCH     (&HalDispatchTable)

#endif

#define HAL_DISPATCH_VERSION        4

#define HalDispatchTableVersion         HALDISPATCH->Version
#define HalQuerySystemInformation       HALDISPATCH->HalQuerySystemInformation
#define HalSetSystemInformation         HALDISPATCH->HalSetSystemInformation
#define HalQueryBusSlots                HALDISPATCH->HalQueryBusSlots

#define HalReferenceHandlerForBus       HALDISPATCH->HalReferenceHandlerForBus
#define HalReferenceBusHandler          HALDISPATCH->HalReferenceBusHandler
#define HalDereferenceBusHandler        HALDISPATCH->HalDereferenceBusHandler

#define HalInitPnpDriver                HALDISPATCH->HalInitPnpDriver
#define HalInitPowerManagement          HALDISPATCH->HalInitPowerManagement

#define HalGetDmaAdapter                HALDISPATCH->HalGetDmaAdapter
#define HalGetInterruptTranslator       HALDISPATCH->HalGetInterruptTranslator

#define HalStartMirroring               HALDISPATCH->HalStartMirroring
#define HalEndMirroring                 HALDISPATCH->HalEndMirroring
#define HalMirrorPhysicalMemory         HALDISPATCH->HalMirrorPhysicalMemory
#define HalEndOfBoot                    HALDISPATCH->HalEndOfBoot
#define HalMirrorVerify                 HALDISPATCH->HalMirrorVerify

#define HalGetCachedAcpiTable           HALDISPATCH->HalGetCachedAcpiTable
#define HalSetPciErrorHandlerCallback   HALDISPATCH->HalSetPciErrorHandlerCallback

typedef struct {
    ULONG                                  Version;

    pHalHandlerForBus                      HalHandlerForBus;
    pHalHandlerForConfigSpace              HalHandlerForConfigSpace;
    pHalLocateHiberRanges                  HalLocateHiberRanges;

    pHalRegisterBusHandler                 HalRegisterBusHandler;

    pHalSetWakeEnable                      HalSetWakeEnable;
    pHalSetWakeAlarm                       HalSetWakeAlarm;

    pHalTranslateBusAddress                HalPciTranslateBusAddress;
    pHalAssignSlotResources                HalPciAssignSlotResources;

    pHalHaltSystem                         HalHaltSystem;

    pHalFindBusAddressTranslation          HalFindBusAddressTranslation;

    pHalResetDisplay                       HalResetDisplay;

    pHalAllocateMapRegisters               HalAllocateMapRegisters;

    pKdSetupPciDeviceForDebugging          KdSetupPciDeviceForDebugging;
    pKdReleasePciDeviceForDebugging        KdReleasePciDeviceForDebugging;

    pKdGetAcpiTablePhase0                  KdGetAcpiTablePhase0;
    pKdCheckPowerButton                    KdCheckPowerButton;

    pHalVectorToIDTEntry                   HalVectorToIDTEntry;

    pKdMapPhysicalMemory64                 KdMapPhysicalMemory64;
    pKdUnmapVirtualAddress                 KdUnmapVirtualAddress;

    pKdGetPciDataByOffset                  KdGetPciDataByOffset;
    pKdSetPciDataByOffset                  KdSetPciDataByOffset;

    pHalGetInterruptVector                 HalGetInterruptVectorOverride;
    pHalGetVectorInput                     HalGetVectorInputOverride;

    pHalLoadMicrocode                      HalLoadMicrocode;
    pHalUnloadMicrocode                    HalUnloadMicrocode;
    pHalPostMicrocodeUpdate                HalPostMicrocodeUpdate;

    pHalAllocateMessageTarget              HalAllocateMessageTargetOverride;
    pHalFreeMessageTarget                  HalFreeMessageTargetOverride;

    pHalDpReplaceBegin                     HalDpReplaceBegin;
    pHalDpReplaceTarget                    HalDpReplaceTarget;
    pHalDpReplaceControl                   HalDpReplaceControl;
    pHalDpReplaceEnd                       HalDpReplaceEnd;

    pHalPrepareForBugcheck                 HalPrepareForBugcheck;
    pHalQueryWakeTime                      HalQueryWakeTime;
    pHalReportIdleStateUsage               HalReportIdleStateUsage;
    pHalTscSynchronization                 HalTscSynchronization;

    pHalWheaInitProcessorGenericSection    HalWheaInitProcessorGenericSection;

    pHalStopLegacyUsbInterrupts            HalStopLegacyUsbInterrupts;

    pHalReadWheaPhysicalMemory             HalReadWheaPhysicalMemory;
    pHalWriteWheaPhysicalMemory            HalWriteWheaPhysicalMemory;

    pHalDpMaskLevelTriggeredInterrupts     HalDpMaskLevelTriggeredInterrupts;
    pHalDpUnmaskLevelTriggeredInterrupts   HalDpUnmaskLevelTriggeredInterrupts;
    pHalDpGetInterruptReplayState          HalDpGetInterruptReplayState;
    pHalDpReplayInterrupts                 HalDpReplayInterrupts;
    pHalQueryIoPortAccessSupported         HalQueryIoPortAccessSupported;

    pKdSetupIntegratedDeviceForDebugging   KdSetupIntegratedDeviceForDebugging;
    pKdReleaseIntegratedDeviceForDebugging KdReleaseIntegratedDeviceForDebugging;
    pHalGetEnlightenmentInformation        HalGetEnlightenmentInformation;
    pHalAllocateEarlyPages                 HalAllocateEarlyPages;
    pHalMapEarlyPages                      HalMapEarlyPages;

    PVOID                                  Dummy1;
    PVOID                                  Dummy2;
    pHalNotifyProcessorFreeze              HalNotifyProcessorFreeze;
    pHalPrepareProcessorForIdle            HalPrepareProcessorForIdle;
    pHalRegisterLogRoutine                 HalRegisterLogRoutine;
    pHalResumeProcessorFromIdle            HalResumeProcessorFromIdle;
    PVOID                                  Dummy;

    pHalVectorToIDTEntryEx              HalVectorToIDTEntryEx;
    pHalSecondaryInterruptQueryPrimaryInformation HalSecondaryInterruptQueryPrimaryInformation;
    pHalMaskInterrupt                   HalMaskInterrupt;
    pHalUnmaskInterrupt                 HalUnmaskInterrupt;
    pHalIsInterruptTypeSecondary        HalIsInterruptTypeSecondary;
    pHalAllocateGsivForSecondaryInterrupt   HalAllocateGsivForSecondaryInterrupt;
    pHalAddInterruptRemapping           HalAddInterruptRemapping;
    pHalRemoveInterruptRemapping        HalRemoveInterruptRemapping;
    pHalSaveAndDisableHvEnlightenment   HalSaveAndDisableHvEnlightenment;
    pHalRestoreHvEnlightenment          HalRestoreHvEnlightenment;

    pHalFlushIoBuffersExternalCache     HalFlushIoBuffersExternalCache;
    pHalFlushExternalCache              HalFlushExternalCache;

    pHalPciEarlyRestore                 HalPciEarlyRestore;
    pHalGetProcessorId                  HalGetProcessorId;
    pHalAllocatePmcCounterSet           HalAllocatePmcCounterSet;
    pHalCollectPmcCounters              HalCollectPmcCounters;
    pHalFreePmcCounterSet               HalFreePmcCounterSet;
    pHalProcessorHalt                   HalProcessorHalt;
    pHalTimerQueryCycleCounter          HalTimerQueryCycleCounter;
    PVOID                               Dummy3;
    pHalPciMarkHiberPhase               HalPciMarkHiberPhase;
    pHalQueryProcessorRestartEntryPoint HalQueryProcessorRestartEntryPoint;
    pHalRequestInterrupt                HalRequestInterrupt;
    pHalEnumerateUnmaskedInterrupts     HalEnumerateUnmaskedInterrupts;

    pHalFlushAndInvalidatePageExternalCache HalFlushAndInvalidatePageExternalCache;
    pKdEnumerateDebuggingDevices        KdEnumerateDebuggingDevices;

    pHalFlushIoRectangleExternalCache   HalFlushIoRectangleExternalCache;

    pHalPowerEarlyRestore               HalPowerEarlyRestore;

    pHalQueryCapsuleCapabilities        HalQueryCapsuleCapabilities;
    pHalUpdateCapsule                   HalUpdateCapsule;
    pHalPciMultiStageResumeCapable      HalPciMultiStageResumeCapable;
    pHalDmaFreeCrashDumpRegisters       HalDmaFreeCrashDumpRegisters;

    pHalAcpiAoacCapable                 HalAcpiAoacCapable;
    pHalInterruptSetDestination         HalInterruptSetDestination;
    pHalGetClockConfiguration           HalGetClockConfiguration;
    pHalClockTimerActivate              HalClockTimerActivate;
    pHalClockTimerInitialize            HalClockTimerInitialize;
    pHalClockTimerStop                  HalClockTimerStop;
    pHalClockTimerArm                   HalClockTimerArm;
    pHalTimerOnlyClockInterruptPending  HalTimerOnlyClockInterruptPending;

    pHalAcpiGetMultiNode                HalAcpiGetMultiNode;
    pHalPowerSetRebootHandler           HalPowerSetRebootHandler;

    pHalIommuRegisterDispatchTable      HalIommuRegisterDispatchTable;
    pHalTimerWatchdogStart              HalTimerWatchdogStart;
    pHalTimerWatchdogResetCountdown     HalTimerWatchdogResetCountdown;
    pHalTimerWatchdogStop               HalTimerWatchdogStop;
    pHalTimerWatchdogGeneratedLastReset HalTimerWatchdogGeneratedLastReset;
    pHalTimerWatchdogTriggerSystemReset HalTimerWatchdogTriggerSystemReset;

    pHalInterruptVectorDataToGsiv       HalInterruptVectorDataToGsiv;

    pHalInterruptGetHighestPriorityInterrupt    HalInterruptGetHighestPriorityInterrupt;

    pHalProcessorOn              HalProcessorOn;
    pHalProcessorOff             HalProcessorOff;

    pHalProcessorFreeze          HalProcessorFreeze;

    pHalDmaLinkDeviceObjectByToken  HalDmaLinkDeviceObjectByToken;

    pHalDmaCheckAdapterToken     HalDmaCheckAdapterToken;

    pHalPciLateRestore           HalPciLateRestore;
    pHalTimerConvertPerformanceCounterToAuxiliaryCounter HalTimerConvertPerformanceCounterToAuxiliaryCounter;
    pHalTimerConvertAuxiliaryCounterToPerformanceCounter HalTimerConvertAuxiliaryCounterToPerformanceCounter;
    pHalTimerQueryAuxiliaryCounterFrequency HalTimerQueryAuxiliaryCounterFrequency;
} HAL_PRIVATE_DISPATCH, *PHAL_PRIVATE_DISPATCH;

#if defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_)
extern  PHAL_PRIVATE_DISPATCH           HalPrivateDispatchTable;
#define HALPDISPATCH                    HalPrivateDispatchTable
#else
extern  HAL_PRIVATE_DISPATCH            HalPrivateDispatchTable;
#define HALPDISPATCH                    (&HalPrivateDispatchTable)
#endif

#define HAL_PRIVATE_DISPATCH_VERSION        30

#define HalRegisterBusHandler           HALPDISPATCH->HalRegisterBusHandler
#define HalHandlerForBus                HALPDISPATCH->HalHandlerForBus
#define HalHandlerForConfigSpace        HALPDISPATCH->HalHandlerForConfigSpace
#define HalLocateHiberRanges            HALPDISPATCH->HalLocateHiberRanges
#define HalSetWakeEnable                HALPDISPATCH->HalSetWakeEnable
#define HalSetWakeAlarm                 HALPDISPATCH->HalSetWakeAlarm
#define HalHaltSystem                   HALPDISPATCH->HalHaltSystem
#define HalResetDisplay                 HALPDISPATCH->HalResetDisplay
#define HalAllocateMapRegisters         HALPDISPATCH->HalAllocateMapRegisters
#define KdEnumerateDebuggingDevices     HALPDISPATCH->KdEnumerateDebuggingDevices
#define KdSetupPciDeviceForDebugging    HALPDISPATCH->KdSetupPciDeviceForDebugging
#define KdReleasePciDeviceForDebugging  HALPDISPATCH->KdReleasePciDeviceForDebugging
#define KdSetupIntegratedDeviceForDebugging   HALPDISPATCH->KdSetupIntegratedDeviceForDebugging
#define KdReleaseIntegratedDeviceForDebugging HALPDISPATCH->KdReleaseIntegratedDeviceForDebugging
#define KdGetAcpiTablePhase0                  HALPDISPATCH->KdGetAcpiTablePhase0
#define KdCheckPowerButton                    HALPDISPATCH->KdCheckPowerButton
#define HalVectorToIDTEntry                   HALPDISPATCH->HalVectorToIDTEntry
#define KdMapPhysicalMemory64                 HALPDISPATCH->KdMapPhysicalMemory64
#define KdUnmapVirtualAddress                 HALPDISPATCH->KdUnmapVirtualAddress
#define KdGetPciDataByOffset                  HALPDISPATCH->KdGetPciDataByOffset
#define KdSetPciDataByOffset                  HALPDISPATCH->KdSetPciDataByOffset
#define HalLoadMicrocode                      HALPDISPATCH->HalLoadMicrocode
#define HalUnloadMicrocode                    HALPDISPATCH->HalUnloadMicrocode
#define HalPostMicrocodeUpdate                HALPDISPATCH->HalPostMicrocodeUpdate
#define HalDpReplaceBegin                     HALPDISPATCH->HalDpReplaceBegin
#define HalDpReplaceTarget                    HALPDISPATCH->HalDpReplaceTarget
#define HalDpReplaceControl                   HALPDISPATCH->HalDpReplaceControl
#define HalDpReplaceEnd                       HALPDISPATCH->HalDpReplaceEnd
#define HalPrepareForBugcheck                 HALPDISPATCH->HalPrepareForBugcheck
#define HalQueryWakeTime                      HALPDISPATCH->HalQueryWakeTime
#define HalReportIdleStateUsage               HALPDISPATCH->HalReportIdleStateUsage
#define HalTscSynchronization                 HALPDISPATCH->HalTscSynchronization
#define HalWheaInitProcessorGenericSection    HALPDISPATCH->HalWheaInitProcessorGenericSection
#define HalStopLegacyUsbInterrupts            HALPDISPATCH->HalStopLegacyUsbInterrupts
#define HalReadWheaPhysicalMemory             HALPDISPATCH->HalReadWheaPhysicalMemory
#define HalWriteWheaPhysicalMemory            HALPDISPATCH->HalWriteWheaPhysicalMemory
#define HalDpMaskLevelTriggeredInterrupts     HALPDISPATCH->HalDpMaskLevelTriggeredInterrupts
#define HalDpUnmaskLevelTriggeredInterrupts   HALPDISPATCH->HalDpUnmaskLevelTriggeredInterrupts
#define HalDpGetInterruptReplayState          HALPDISPATCH->HalDpGetInterruptReplayState
#define HalDpReplayInterrupts                 HALPDISPATCH->HalDpReplayInterrupts
#define HalQueryIoPortAccessSupported         HALPDISPATCH->HalQueryIoPortAccessSupported
#define HalGetEnlightenmentInformation        HALPDISPATCH->HalGetEnlightenmentInformation
#define HalAllocateEarlyPages                 HALPDISPATCH->HalAllocateEarlyPages
#define HalMapEarlyPages                      HALPDISPATCH->HalMapEarlyPages
#define HalNotifyProcessorFreeze              HALPDISPATCH->HalNotifyProcessorFreeze
#define HalPrepareProcessorForIdle            HALPDISPATCH->HalPrepareProcessorForIdle
#define HalRegisterLogRoutine                 HALPDISPATCH->HalRegisterLogRoutine
#define HalResumeProcessorFromIdle            HALPDISPATCH->HalResumeProcessorFromIdle
#define HalVectorToIDTEntryEx                 HALPDISPATCH->HalVectorToIDTEntryEx
#define HalSecondaryInterruptQueryPrimaryInformation       HALPDISPATCH->HalSecondaryInterruptQueryPrimaryInformation
#define HalMaskInterrupt                      HALPDISPATCH->HalMaskInterrupt
#define HalUnmaskInterrupt                    HALPDISPATCH->HalUnmaskInterrupt
#define HalIsInterruptTypeSecondary           HALPDISPATCH->HalIsInterruptTypeSecondary
#define HalAllocateGsivForSecondaryInterrupt  HALPDISPATCH->HalAllocateGsivForSecondaryInterrupt
#define HalAddInterruptRemapping              HALPDISPATCH->HalAddInterruptRemapping
#define HalRemoveInterruptRemapping           HALPDISPATCH->HalRemoveInterruptRemapping
#define HalSaveAndDisableHvEnlightenment      HALPDISPATCH->HalSaveAndDisableHvEnlightenment
#define HalRestoreHvEnlightenment             HALPDISPATCH->HalRestoreHvEnlightenment
#define HalFlushIoBuffersExternalCache        HALPDISPATCH->HalFlushIoBuffersExternalCache
#define HalFlushExternalCache                 HALPDISPATCH->HalFlushExternalCache
#define HalPciEarlyRestore                    HALPDISPATCH->HalPciEarlyRestore
#define HalGetProcessorId                     HALPDISPATCH->HalGetProcessorId
#define HalAllocatePmcCounterSet              HALPDISPATCH->HalAllocatePmcCounterSet
#define HalCollectPmcCounters                 HALPDISPATCH->HalCollectPmcCounters
#define HalFreePmcCounterSet                  HALPDISPATCH->HalFreePmcCounterSet
#define HalProcessorHalt                      HALPDISPATCH->HalProcessorHalt
#define HalTimerQueryCycleCounter             HALPDISPATCH->HalTimerQueryCycleCounter
#define HalPciMarkHiberPhase                  HALPDISPATCH->HalPciMarkHiberPhase
#define HalQueryProcessorRestartEntryPoint    HALPDISPATCH->HalQueryProcessorRestartEntryPoint
#define HalRequestInterrupt                   HALPDISPATCH->HalRequestInterrupt
#define HalEnumerateUnmaskedInterrupts        HALPDISPATCH->HalEnumerateUnmaskedInterrupts
#define HalFlushAndInvalidatePageExternalCache HALPDISPATCH->HalFlushAndInvalidatePageExternalCache
#define HalFlushIoRectangleExternalCache      HALPDISPATCH->HalFlushIoRectangleExternalCache
#define HalPowerEarlyRestore                  HALPDISPATCH->HalPowerEarlyRestore
#define HalQueryCapsuleCapabilities           HALPDISPATCH->HalQueryCapsuleCapabilities
#define HalUpdateCapsule                      HALPDISPATCH->HalUpdateCapsule
#define HalPciMultiStageResumeCapable         HALPDISPATCH->HalPciMultiStageResumeCapable
#define HalDmaFreeCrashDumpRegisters          HALPDISPATCH->HalDmaFreeCrashDumpRegisters
#define HalAcpiAoacCapable                    HALPDISPATCH->HalAcpiAoacCapable
#define HalInterruptSetDestination            HALPDISPATCH->HalInterruptSetDestination
#define HalGetClockConfiguration              HALPDISPATCH->HalGetClockConfiguration
#define HalClockTimerActivate                 HALPDISPATCH->HalClockTimerActivate
#define HalClockTimerInitialize               HALPDISPATCH->HalClockTimerInitialize
#define HalClockTimerStop                     HALPDISPATCH->HalClockTimerStop
#define HalClockTimerArm                      HALPDISPATCH->HalClockTimerArm
#define HalTimerOnlyClockInterruptPending     HALPDISPATCH->HalTimerOnlyClockInterruptPending
#define HalAcpiGetMultiNode                   HALPDISPATCH->HalAcpiGetMultiNode
#define HalPowerSetRebootHandler              HALPDISPATCH->HalPowerSetRebootHandler
#define HalIommuRegisterDispatchTable         HALPDISPATCH->HalIommuRegisterDispatchTable
#define HalTimerWatchdogStart                 HALPDISPATCH->HalTimerWatchdogStart
#define HalTimerWatchdogResetCountdown        HALPDISPATCH->HalTimerWatchdogResetCountdown
#define HalTimerWatchdogStop                  HALPDISPATCH->HalTimerWatchdogStop
#define HalTimerWatchdogGeneratedLastReset    HALPDISPATCH->HalTimerWatchdogGeneratedLastReset
#define HalTimerWatchdogTriggerSystemReset    HALPDISPATCH->HalTimerWatchdogTriggerSystemReset
#define HalInterruptVectorDataToGsiv          HALPDISPATCH->HalInterruptVectorDataToGsiv
#define HalInterruptGetHighestPriorityInterrupt HALPDISPATCH->HalInterruptGetHighestPriorityInterrupt
#define HalProcessorOn                        HALPDISPATCH->HalProcessorOn
#define HalProcessorOff                       HALPDISPATCH->HalProcessorOff
#define HalProcessorFreeze                    HALPDISPATCH->HalProcessorFreeze
#define HalDmaLinkDeviceObjectByToken         HALPDISPATCH->HalDmaLinkDeviceObjectByToken
#define HalDmaCheckAdapterToken               HALPDISPATCH->HalDmaCheckAdapterToken
#define HalPciLateRestore                     HALPDISPATCH->HalPciLateRestore
#define HalTimerConvertPerformanceCounterToAuxiliaryCounter \
        HALPDISPATCH->HalTimerConvertPerformanceCounterToAuxiliaryCounter

#define HalTimerConvertAuxiliaryCounterToPerformanceCounter \
        HALPDISPATCH->HalTimerConvertAuxiliaryCounterToPerformanceCounter

#define HalTimerQueryAuxiliaryCounterFrequency \
        HALPDISPATCH->HalTimerQueryAuxiliaryCounterFrequency

typedef
BOOLEAN
(*pHalIommuSupportEnabled) (
    VOID
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuGetConfiguration) (
    _In_ ULONG Domain,
    _Out_ PULONG PageRequestQueues,
    _Out_ PULONG MaximumAsids,
    _Out_ PVOID *SystemContext
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuGetLibraryContext) (
    _In_ ULONG Pasid,
    _In_ ULONG Domain,
    _Out_ PVOID *LibraryContext
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuMapDevice) (
    _In_ PVOID LibraryContext,
    _In_ PIOMMU_DEVICE_PATH DevicePath,
    _In_ PIOMMU_SVM_CAPABILITIES DeviceCapabilities,
    _Out_ PVOID *DeviceHandle
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuEnableDevicePasid) (
    _In_ PVOID LibraryContext,
    _In_ PVOID DeviceHandle
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuSetAddressSpace) (
    _In_ PVOID LibraryContext,
    _In_ ULONG_PTR DirectoryBase
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuDisableDevicePasid) (
    _In_ PVOID LibraryContext,
    _In_ PVOID DeviceHandle
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuUnmapDevice) (
    _In_ PVOID SystemContext,
    _In_ PVOID DeviceHandle
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuFreeLibraryContext) (
    _In_ PVOID LibraryContext
    );

typedef
_IRQL_requires_max_(HIGH_LEVEL)
VOID
(*pHalIommuFlushTb) (
    _In_ PVOID LibraryContext,
    _In_ ULONG Number,
    _In_count_ (Number) KTB_FLUSH_VA Virtual[]
    );

typedef
_IRQL_requires_max_(HIGH_LEVEL)
VOID
(*pHalIommuFlushAllPasid) (
    _In_ PVOID LibraryContext,
    _In_ ULONG Number,
    _In_count_ (Number) KTB_FLUSH_VA VA[]
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
BOOLEAN
(*pHalIommuProcessPageRequestQueue) (
    _In_ ULONG Index
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuDevicePowerChange) (
    _In_ PVOID SystemContext,
    _In_ PVOID DeviceHandle,
    _In_ BOOLEAN PowerActive
    );

typedef
_IRQL_requires_max_(HIGH_LEVEL)
VOID
(*pHalIommuFaultRoutine) (
    _In_ ULONG Index
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
PVOID
(*pHalIommuReferenceAsid) (
    _In_ ULONG Asid
    );

typedef
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
(*pHalIommuDereferenceAsid) (
    _In_ ULONG Asid
    );

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
(*pHalIommuServicePageFault) (
    _In_ ULONG_PTR FaultStatus,
    _In_ PVOID FaultingVa,
    _In_ ULONG Asid
    );

struct _HAL_IOMMU_DISPATCH {
    pHalIommuSupportEnabled         HalIommuSupportEnabled;
    pHalIommuGetConfiguration       HalIommuGetConfiguration;
    pHalIommuGetLibraryContext      HalIommuGetLibraryContext;
    pHalIommuMapDevice              HalIommuMapDevice;
    pHalIommuEnableDevicePasid      HalIommuEnableDevicePasid;
    pHalIommuSetAddressSpace        HalIommuSetAddressSpace;
    pHalIommuDisableDevicePasid     HalIommuDisableDevicePasid;
    pHalIommuUnmapDevice            HalIommuUnmapDevice;
    pHalIommuFreeLibraryContext     HalIommuFreeLibraryContext;
    pHalIommuFlushTb                HalIommuFlushTb;
    pHalIommuFlushAllPasid          HalIommuFlushAllPasid;
    pHalIommuProcessPageRequestQueue HalIommuProcessPageRequestQueue;
    pHalIommuFaultRoutine           HalIommuFaultRoutine;
    pHalIommuReferenceAsid          HalIommuReferenceAsid;
    pHalIommuDereferenceAsid        HalIommuDereferenceAsid;
    pHalIommuServicePageFault       HalIommuServicePageFault;
    pHalIommuDevicePowerChange      HalIommuDevicePowerChange;
};

extern  PHAL_IOMMU_DISPATCH         HalIommuDispatch;

#define HalIommuSupportEnabled      HalIommuDispatch->HalIommuSupportEnabled
#define HalIommuGetConfiguration    HalIommuDispatch->HalIommuGetConfiguration
#define HalIommuGetLibraryContext   HalIommuDispatch->HalIommuGetLibraryContext
#define HalIommuMapDevice           HalIommuDispatch->HalIommuMapDevice
#define HalIommuEnableDevicePasid   HalIommuDispatch->HalIommuEnableDevicePasid
#define HalIommuSetAddressSpace     HalIommuDispatch->HalIommuSetAddressSpace
#define HalIommuDisableDevicePasid  HalIommuDispatch->HalIommuDisableDevicePasid
#define HalIommuUnmapDevice         HalIommuDispatch->HalIommuUnmapDevice
#define HalIommuFreeLibraryContext  HalIommuDispatch->HalIommuFreeLibraryContext
#define HalIommuFlushTb             HalIommuDispatch->HalIommuFlushTb
#define HalIommuFlushAllPasid       HalIommuDispatch->HalIommuFlushAllPasid
#define HalIommuProcessPageRequestQueue HalIommuDispatch->HalIommuProcessPageRequestQueue
#define HalIommuFaultRoutine        HalIommuDispatch->HalIommuFaultRoutine
#define HalIommuReferenceAsid       HalIommuDispatch->HalIommuReferenceAsid
#define HalIommuDereferenceAsid     HalIommuDispatch->HalIommuDereferenceAsid
#define HalIommuServicePageFault    HalIommuDispatch->HalIommuServicePageFault
#define HalIommuDevicePowerChange   HalIommuDispatch->HalIommuDevicePowerChange

typedef struct _HAL_BUS_INFORMATION{
    INTERFACE_TYPE  BusType;
    BUS_DATA_TYPE   ConfigurationType;
    ULONG           BusNumber;
    ULONG           Reserved;
} HAL_BUS_INFORMATION, *PHAL_BUS_INFORMATION;

typedef enum _HAL_DISPLAY_BIOS_INFORMATION {
    HalDisplayInt10Bios,
    HalDisplayEmulatedBios,
    HalDisplayNoBios
} HAL_DISPLAY_BIOS_INFORMATION, *PHAL_DISPLAY_BIOS_INFORMATION;

typedef struct _HAL_POWER_INFORMATION {
    ULONG   TBD;
} HAL_POWER_INFORMATION, *PHAL_POWER_INFORMATION;

typedef struct _HAL_PROCESSOR_SPEED_INFO {
    ULONG   ProcessorSpeed;
} HAL_PROCESSOR_SPEED_INFORMATION, *PHAL_PROCESSOR_SPEED_INFORMATION;

typedef struct _HAL_CALLBACKS {
    PCALLBACK_OBJECT  SetSystemInformation;
    PCALLBACK_OBJECT  BusCheck;
} HAL_CALLBACKS, *PHAL_CALLBACKS;

typedef struct _HAL_PROCESSOR_FEATURE {
    ULONG UsableFeatureBits;
} HAL_PROCESSOR_FEATURE;

typedef struct _HAL_PROFILE_SOURCE_INFORMATION {
    KPROFILE_SOURCE Source;
    BOOLEAN Supported;
    ULONG Interval;
    PCWSTR Description;
} HAL_PROFILE_SOURCE_INFORMATION, *PHAL_PROFILE_SOURCE_INFORMATION;

typedef struct _HAL_PROFILE_SOURCE_INFORMATION_EX {
    KPROFILE_SOURCE Source;
    BOOLEAN         Supported;
    ULONG_PTR       Interval;
    ULONG_PTR       DefInterval;
    ULONG_PTR       MaxInterval;
    ULONG_PTR       MinInterval;
} HAL_PROFILE_SOURCE_INFORMATION_EX, *PHAL_PROFILE_SOURCE_INFORMATION_EX;

typedef struct _HAL_PROFILE_SOURCE_INTERVAL {
    KPROFILE_SOURCE Source;
    ULONG Interval;
} HAL_PROFILE_SOURCE_INTERVAL, *PHAL_PROFILE_SOURCE_INTERVAL;

typedef struct _HAL_PROFILE_SOURCE_LIST {
    ULONG NextEntryOffset;
    KPROFILE_SOURCE Source;
    ULONG MinInterval;
    ULONG MaxInterval;
    ULONG64 Reserved;
    WCHAR Description[ANYSIZE_ARRAY];
} HAL_PROFILE_SOURCE_LIST, *PHAL_PROFILE_SOURCE_LIST;

typedef enum _HAL_PLATFORM_TIMER_SOURCE {
    HalPlatformTimerNotSpecified = 0,
    HalPlatformTimer8254,
    HalPlatformTimerRtc,
    HalPlatformTimerAcpi,
    HalPlatformTimerAcpiBroken,
    HalPlatformTimerHpet,
    HalPlatformTimerProcessorCounter,
    HalPlatformTimerHvReferenceTime,
    HalPlatformTimerSfi,
    HalPlatformTimerApic,
    HalPlatformTimerHvSynthetic,
    HalPlatformTimerCustom,
    HalPlatformTimerCycleCounter,
    HalPlatformTimerGit,
} HAL_PLATFORM_TIMER_SOURCE;

#define HAL_PLATFORM_TIMER_INFORMATION_VERSION 1

typedef struct _HAL_PLATFORM_TIMER_INFORMATION {
    ULONG Version;
    HAL_PLATFORM_TIMER_SOURCE ClockInterruptSource;
    HAL_PLATFORM_TIMER_SOURCE PerformanceCounterSource;
} HAL_PLATFORM_TIMER_INFORMATION, *PHAL_PLATFORM_TIMER_INFORMATION;

typedef struct _HAL_ACPI_AUDIT_INFORMATION {
    ULONG RsdpCount;
    struct {
        ULONG SameRsdt:1;
        ULONG SlicPresent:1;
        ULONG SlicDifferent:1;
    };
} HAL_ACPI_AUDIT_INFORMATION, *PHAL_ACPI_AUDIT_INFORMATION;

typedef struct _HAL_PARKING_PAGE_INFORMATION {
    ULONG Processor;
    PHYSICAL_ADDRESS PhysicalPageAddress;
    PVOID VirtualPageAddress;
} HAL_PARKING_PAGE_INFORMATION, *PHAL_PARKING_PAGE_INFORMATION;

typedef struct _HAL_IOMMU_RESERVED_REGION_INFORMATION {
    PDEVICE_OBJECT DeviceObject;
    BOOLEAN RequiresReservedRegion;
} HAL_IOMMU_RESERVED_REGION_INFORMATION, *PHAL_IOMMU_RESERVED_REGION_INFORMATION;

typedef ULONG HAL_HV_LOGICAL_PROCESSOR_INDEX, *PHAL_HV_LOGICAL_PROCESSOR_INDEX;
typedef ULONG HAL_HV_VIRTUAL_PROCESSOR_INDEX, *PHAL_HV_VIRTUAL_PROCESSOR_INDEX;

typedef
VOID
(*PHAL_ENLIGHTENMENT_EOI) (
    VOID
    );

typedef
VOID
(*PHAL_ENLIGHTENMENT_WRITE_ICR) (
    _In_ ULONG Target,
    _In_ ULONG Command
    );

typedef
VOID
(*PHAL_LONG_SPIN_WAIT) (
    _In_ ULONG SpinCount
    );

typedef
ULONG64
(*PHAL_GET_REFERENCE_TIME) (
    VOID
    );

typedef
NTSTATUS
(*PHAL_SET_SYSTEM_SLEEP_PROPERTY)(
    _In_ UINT32 SleepState,
    _In_ UINT8 Pm1a_SLP_TYP,
    _In_ UINT8 Pm1b_SLP_TYP
    );

typedef
NTSTATUS
(*PHAL_SET_SYSTEM_MACHINE_CHECK_PROPERTY)(
    _In_ PVOID MachineCheckPropertyInfo
    );

typedef
NTSTATUS
(*PHAL_ENTER_SLEEP_STATE)(
    _In_ UINT32 SleepState
    );

typedef
NTSTATUS
(*PHAL_NOTIFY_DEBUG_DEVICE_AVAILABLE)(
    VOID
    );

typedef
NTSTATUS
(*PHAL_MAP_DEVICE_INTERRUPT)(
    _In_ UINT64 DeviceId,
    _In_ UINT64 Flags,
    _In_ PVOID InterruptDescriptor,
    _In_opt_ PGROUP_AFFINITY GroupAffinity,
    _Out_ PVOID InterruptEntry
    );

typedef
NTSTATUS
(*PHAL_UNMAP_DEVICE_INTERRUPT)(
    _In_ UINT64 DeviceId,
    _In_ PVOID InterruptEntry
    );

typedef
NTSTATUS
(*PHAL_SET_HPET_CONFIG)(
    _In_ PHYSICAL_ADDRESS BaseAddress,
    _In_ ULONG TimerIndex,
    _In_ UINT64 DeviceId,
    _In_ UCHAR TimerInterruptPin,
    _Out_ PVOID InterruptEntry
    );

typedef
NTSTATUS
(*PHAL_NOTIFY_HPET_ENABLED)(
    VOID
    );

typedef
NTSTATUS
(*PHAL_QUERY_ASSOCIATED_PROCESSORS) (
    _In_ ULONG VpIndex,
    _Inout_ PULONG Count,
    _Out_writes_to_opt_(*Count, *Count) PHAL_HV_LOGICAL_PROCESSOR_INDEX PpIndices
    );

typedef
NTSTATUS
(*PHAL_LP_READ_MULTIPLE_MSR) (
    _In_ HAL_HV_LOGICAL_PROCESSOR_INDEX HvLpIndex,
    _In_ ULONG Count,
    _In_reads_(Count) PULONG MsrIndices,
    _Out_writes_(Count) PULONG64 MsrValues
    );

typedef
NTSTATUS
(*PHAL_LP_WRITE_MULTIPLE_MSR) (
    _In_ HAL_HV_LOGICAL_PROCESSOR_INDEX HvLpIndex,
    _In_ ULONG Count,
    _In_reads_(Count) PULONG MsrIndices,
    _In_reads_(Count) PULONG64 MsrValues
    );

typedef
NTSTATUS
(*PHAL_LP_READ_CPUID) (
    _In_ HAL_HV_LOGICAL_PROCESSOR_INDEX HvLpIndex,
    _In_ ULONG InEax,
    _Out_ PULONG OutEax,
    _Out_ PULONG OutEbx,
    _Out_ PULONG OutEcx,
    _Out_ PULONG OutEdx
    );

typedef
NTSTATUS
(*PHAL_LP_WRITEBACK_INVALIDATE) (
    _In_ HAL_HV_LOGICAL_PROCESSOR_INDEX HvLpIndex
    );

typedef
NTSTATUS
(*PHAL_LP_GET_MACHINE_CHECK_CONTEXT) (
    _In_ HAL_HV_LOGICAL_PROCESSOR_INDEX HvLpIndex,
    _Out_ UINT32 *Source,
    _Out_ UINT64 *PartitionId,
    _Out_ UINT32 *VpIndex
    );

typedef
NTSTATUS
(*PHAL_SUSPEND_PARTITION) (
    _In_ UINT64 PartitionId
    );

typedef
NTSTATUS
(*PHAL_RESUME_PARTITION) (
    _In_ UINT64 PartitionId
    );

typedef struct _WHEA_RECOVERY_CONTEXT *PWHEA_RECOVERY_CONTEXT;

typedef
NTSTATUS
(*PHAL_WHEA_ERROR_NOTIFICATION) (
    _In_ PWHEA_RECOVERY_CONTEXT RecoveryContext,
    _In_ BOOLEAN PlatformDirected,
    _In_ BOOLEAN Poisoned
    );

typedef
ULONG
(*PHAL_GET_PROCESSOR_INDEX_FROM_VP_INDEX) (
    _In_ ULONG VpIndex
    );

typedef
NTSTATUS
(*PHAL_SYNTHETIC_CLUSTER_IPI) (
    _In_ PKAFFINITY_EX Affinity,
    _In_ ULONG Vector
    );

typedef union _HAL_X64_SEGMENT_SELECTOR {
    UINT16 AsUINT16;
    struct {
        UINT16 Rpl:2;
        UINT16 LdtSelector:1;
        UINT16 TableIndex:13;
    };
} HAL_X64_SEGMENT_SELECTOR, *PHAL_X64_SEGMENT_SELECTOR;

typedef
BOOLEAN
(*PHAL_VP_START_ENABLED) (
    VOID
    );

typedef
NTSTATUS
(*PHAL_START_VIRTUAL_PROCESSOR) (
    _In_ ULONG VpIndex,
    _In_ PVOID Context
    );

typedef
NTSTATUS
(*PHAL_GET_VP_INDEX_FROM_APIC_ID) (
    _In_ ULONG ApicId,
    _Out_ PULONG VpIndex
    );

typedef struct _HAL_HV_SVM_SYSTEM_CAPABILITIES {
    struct {
        ULONG SvmSupported : 1;
        ULONG GpaAlwaysValid : 1;
    };
    ULONG MaxPasidSpaceCount;
    ULONG MaxPasidSpacePasidCount;
    ULONG MaxPrqSize;
    ULONG IommuCount;
    ULONG MinIommuPasidCount;
} HAL_HV_SVM_SYSTEM_CAPABILITIES, *PHAL_HV_SVM_SYSTEM_CAPABILITIES;

typedef
VOID
(*PHAL_SVM_GET_SYSTEM_CAPABILITIES) (
    _Out_ PHAL_HV_SVM_SYSTEM_CAPABILITIES Capabilities
    );

typedef
SIZE_T // EFI_STATUS
(*PHAL_IUM_EFI_RUNTIME_SERVICE) (
    _In_ ULONG Service,
    _Inout_updates_bytes_(Size) PVOID Data,
    _In_ ULONGLONG Size,
    _Inout_opt_ ULONGLONG Parameters[]
    );

typedef struct _HAL_HV_SVM_DEVICE_CAPABILITIES {
    struct {
        ULONG SvmSupported : 1;
        ULONG PciExecute : 1;
        ULONG NoExecute : 1;
        ULONG Reserved : 28;
        ULONG OverflowPossible : 1;
    };
    ULONG PasidCount;
    ULONG IommuIndex;
} HAL_HV_SVM_DEVICE_CAPABILITIES, *PHAL_HV_SVM_DEVICE_CAPABILITIES;

typedef
NTSTATUS
(*PHAL_SVM_GET_DEVICE_CAPABILITIES) (
    _In_ ULONG DeviceId,
    _Out_ PHAL_HV_SVM_DEVICE_CAPABILITIES Capabilities
    );

typedef
NTSTATUS
(*PHAL_SVM_CREATE_PASID_SPACE) (
    _In_ ULONG PasidSpaceId,
    _In_ ULONG PasidCount
    );

typedef
NTSTATUS
(*PHAL_SVM_SET_PASID_ADDRESS_SPACE) (
    _In_ ULONG PasidSpaceId,
    _In_ ULONG Pasid,
    _In_ ULONGLONG AddressSpace
    );

typedef
VOID
(*PHAL_SVM_FLUSH_PASID) (
    _In_ ULONG PasidSpaceId,
    _In_ ULONG Pasid,
    _In_ ULONG Number,
    _In_reads_opt_(Number) KTB_FLUSH_VA Virtual[]
    );

typedef
NTSTATUS
(*PHAL_SVM_ATTACH_PASID_SPACE) (
    _In_ ULONG DeviceId,
    _In_ ULONG PasidSpaceId,
    _In_ ULONG PrqId,
    _In_ ULONG PciCapabilities
    );

typedef
NTSTATUS
(*PHAL_SVM_DETACH_PASID_SPACE) (
    _In_ ULONG DeviceId
    );

typedef
NTSTATUS
(*PHAL_SVM_ENABLE_PASID) (
    _In_ ULONG DeviceId,
    _In_ ULONG Pasid
    );

typedef
NTSTATUS
(*PHAL_SVM_DISABLE_PASID) (
    _In_ ULONG DeviceId,
    _In_ ULONG Pasid
    );

typedef
NTSTATUS
(*PHAL_SVM_ACKNOWLEDGE_PAGE_REQUEST) (
    _In_ ULONG Count,
    _In_ PVOID PageRequestList,
    _Out_opt_ PULONG Processed
    );

typedef
NTSTATUS
(*PHAL_SVM_CREATE_PR_QUEUE) (
    _In_ ULONG QueueId,
    _In_ ULONG Size,
    _In_ PHYSICAL_ADDRESS BaseAddress,
    _In_ ULONG InterruptVector,
    _In_ ULONG InterruptProcessorIndex
    );

typedef
NTSTATUS
(*PHAL_SVM_DELETE_PR_QUEUE) (
    _In_ ULONG QueueId
    );

typedef
NTSTATUS
(*PHAL_SVM_CLEAR_PRQ_STALLED) (
    _In_ ULONG QueueId
    );

typedef
NTSTATUS
(*PHAL_SVM_SET_DEVICE_ENABLED) (
    _In_ ULONG DeviceId,
    _In_ BOOLEAN Enabled
    );

#if !defined(_ARM64_) && !defined(_ARM_)

typedef struct _HAL_INTEL_ENLIGHTENMENT_INFORMATION {
    ULONG Enlightenments;
    LOGICAL HypervisorConnected;
    PHAL_ENLIGHTENMENT_EOI EndOfInterrupt;
    PHAL_ENLIGHTENMENT_WRITE_ICR ApicWriteIcr;
    ULONG Reserved0;
    ULONG SpinCountMask;
    PHAL_LONG_SPIN_WAIT LongSpinWait;
    PHAL_GET_REFERENCE_TIME GetReferenceTime;
    PHAL_SET_SYSTEM_SLEEP_PROPERTY SetSystemSleepProperty;
    PHAL_ENTER_SLEEP_STATE EnterSleepState;
    PHAL_NOTIFY_DEBUG_DEVICE_AVAILABLE NotifyDebugDeviceAvailable;
    PHAL_MAP_DEVICE_INTERRUPT MapDeviceInterrupt;
    PHAL_UNMAP_DEVICE_INTERRUPT UnmapDeviceInterrupt;
    PHAL_SET_HPET_CONFIG SetHpetConfig;
    PHAL_NOTIFY_HPET_ENABLED NotifyHpetEnabled;
    PHAL_QUERY_ASSOCIATED_PROCESSORS QueryAssociatedProcessors;
    PHAL_LP_READ_MULTIPLE_MSR ReadMultipleMsr;
    PHAL_LP_WRITE_MULTIPLE_MSR WriteMultipleMsr;
    PHAL_LP_READ_CPUID ReadCpuid;
    PHAL_LP_WRITEBACK_INVALIDATE LpWritebackInvalidate;
    PHAL_LP_GET_MACHINE_CHECK_CONTEXT GetMachineCheckContext;
    PHAL_SUSPEND_PARTITION SuspendPartition;
    PHAL_RESUME_PARTITION ResumePartition;
    PHAL_SET_SYSTEM_MACHINE_CHECK_PROPERTY SetSystemMachineCheckProperty;
    PHAL_WHEA_ERROR_NOTIFICATION WheaErrorNotification;
    PHAL_GET_PROCESSOR_INDEX_FROM_VP_INDEX GetProcessorIndexFromVpIndex;
    PHAL_SYNTHETIC_CLUSTER_IPI SyntheticClusterIpi;
    PHAL_VP_START_ENABLED VpStartEnabled;
    PHAL_START_VIRTUAL_PROCESSOR StartVirtualProcessor;
    PHAL_GET_VP_INDEX_FROM_APIC_ID GetVpIndexFromApicId;
    PHAL_IUM_EFI_RUNTIME_SERVICE IumEfiRuntimeService;
    PHAL_SVM_GET_SYSTEM_CAPABILITIES SvmGetSystemCapabilities;
    PHAL_SVM_GET_DEVICE_CAPABILITIES SvmGetDeviceCapabilities;
    PHAL_SVM_CREATE_PASID_SPACE SvmCreatePasidSpace;
    PHAL_SVM_SET_PASID_ADDRESS_SPACE SvmSetPasidAddressSpace;
    PHAL_SVM_FLUSH_PASID SvmFlushPasid;
    PHAL_SVM_ATTACH_PASID_SPACE SvmAttachPasidSpace;
    PHAL_SVM_DETACH_PASID_SPACE SvmDetachPasidSpace;
    PHAL_SVM_ENABLE_PASID SvmEnablePasid;
    PHAL_SVM_DISABLE_PASID SvmDisablePasid;
    PHAL_SVM_ACKNOWLEDGE_PAGE_REQUEST SvmAcknowledgePageRequest;
    PHAL_SVM_CREATE_PR_QUEUE SvmCreatePrQueue;
    PHAL_SVM_DELETE_PR_QUEUE SvmDeletePrQueue;
    PHAL_SVM_CLEAR_PRQ_STALLED SvmClearPrqStalled;
    PHAL_SVM_SET_DEVICE_ENABLED SvmSetDeviceEnabled;
} HAL_INTEL_ENLIGHTENMENT_INFORMATION, *PHAL_INTEL_ENLIGHTENMENT_INFORMATION;

#else

typedef struct _HAL_ARM_ENLIGHTENMENT_INFORMATION {
    ULONG Enlightenments;
    LOGICAL HypervisorConnected;
    ULONG Reserved0;
    ULONG SpinCountMask;
    PHAL_LONG_SPIN_WAIT LongSpinWait;
    PHAL_GET_REFERENCE_TIME GetReferenceTime;
    PHAL_SET_SYSTEM_SLEEP_PROPERTY SetSystemSleepProperty;
    PHAL_ENTER_SLEEP_STATE EnterSleepState;
    PHAL_NOTIFY_DEBUG_DEVICE_AVAILABLE NotifyDebugDeviceAvailable;
    PHAL_MAP_DEVICE_INTERRUPT MapDeviceInterrupt;
    PHAL_UNMAP_DEVICE_INTERRUPT UnmapDeviceInterrupt;
    PHAL_QUERY_ASSOCIATED_PROCESSORS QueryAssociatedProcessors;
    PHAL_LP_GET_MACHINE_CHECK_CONTEXT GetMachineCheckContext;
    PHAL_SUSPEND_PARTITION SuspendPartition;
    PHAL_RESUME_PARTITION ResumePartition;
    PHAL_SET_SYSTEM_MACHINE_CHECK_PROPERTY SetSystemMachineCheckProperty;
    PHAL_WHEA_ERROR_NOTIFICATION WheaErrorNotification;
    PHAL_GET_PROCESSOR_INDEX_FROM_VP_INDEX GetProcessorIndexFromVpIndex;
    PHAL_SYNTHETIC_CLUSTER_IPI SyntheticClusterIpi;
} HAL_ARM_ENLIGHTENMENT_INFORMATION, *PHAL_ARM_ENLIGHTENMENT_INFORMATION;

#endif

typedef
NTSTATUS
(*PHALNUMAQUERYPROCESSORNODE)(
    _In_ ULONG ProcessorNumber,
    _Inout_ PULONG Identifier,
    _Out_ PUSHORT Node
    );

typedef
NTSTATUS
(*PHALNUMAQUERYPROXIMITYNODE)(
    _In_ ULONG ProximityId,
    _Out_ PUSHORT Node
    );

typedef
NTSTATUS
(*PHALNUMAADDRANGEPROXIMITY)(
    _In_ ULONG_PTR PhysicalPageNumber,
    _In_ ULONG_PTR Length,
    _In_ ULONG ProximityId
    );

typedef
NTSTATUS
(*PHALNUMAQUERYPROXIMITYID)(
    _In_ USHORT Node,
    _Out_ PULONG ProximityId,
    _Out_opt_ PULONG OrigProximityId
    );

typedef
NTSTATUS
(*PHALNUMAQUERYNODECAPACITY)(
    _In_ USHORT Node,
    _Out_ PULONG Capacity
    );

typedef
NTSTATUS
(*PHALNUMAQUERYNODEDISTANCE)(
    _In_ USHORT Node1,
    _In_ USHORT Node2,
    _Out_ PULONG Distance
    );

typedef struct _HAL_NUMA_TOPOLOGY_INTERFACE {
    USHORT                              NumberOfNodes;
    PHALNUMAQUERYPROCESSORNODE          QueryProcessorNode;
    PVOID                               Spare;
    PHALNUMAQUERYPROXIMITYNODE          QueryProximityNode;
    PHALNUMAADDRANGEPROXIMITY           AddRangeProximity;
    PHALNUMAQUERYPROXIMITYID            QueryProximityId;
    PHALNUMAQUERYNODECAPACITY           QueryNodeCapacity;
    PHALNUMAQUERYNODEDISTANCE           QueryNodeDistance;
} HAL_NUMA_TOPOLOGY_INTERFACE;

typedef struct _HAL_NODE_RANGE {
    ULONG_PTR PageFrameIndex;
    ULONG Node;
} HAL_NODE_RANGE, *PHAL_NODE_RANGE;

typedef struct _HAL_IRT_INFORMATION {
    ULONG   SegmentCount;
    ULONG   IrtEntriesForParentOsPerSegment;
    ULONG   IrtEntriesForChildOsesPerSegment;
} HAL_IRT_INFORMATION, *PHAL_IRT_INFORMATION;

typedef struct _HAL_CHANNEL_MEMORY_RANGES {
    ULONG_PTR PageFrameIndex;
    USHORT MpnId;
    USHORT Node;
    USHORT Channel;
    BOOLEAN IsPowerManageable;
    UCHAR DeepPowerState;
} HAL_CHANNEL_MEMORY_RANGES, *PHAL_CHANNEL_MEMORY_RANGES;

typedef enum {
    HalPccChannelPowerCommandGetPowerState = 1,
    HalPccChannelPowerCommandSetPowerState,
    HalPccChannelPowerCommandGetExpectedPowerConsumed,
    HalPccChannelPowerCommandGetEnergyConsumed,
    HalPccChannelPowerCommandMax
} HAL_PCC_CHANNEL_POWER_COMMAND, *PHAL_PCC_CHANNEL_POWER_COMMAND;

typedef struct _HAL_CHANNEL_COMMAND {
    USHORT Node;
    USHORT Channel;
    HAL_PCC_CHANNEL_POWER_COMMAND Command;
    ULONG Status;
    ULONGLONG Data;
} HAL_CHANNEL_COMMAND, *PHAL_CHANNEL_COMMAND;

#define HAL_CHANNEL_POWER_STATE_HOT         0x0
#define HAL_CHANNEL_POWER_STATE_COOL        0x1

typedef struct _HAL_EXTERNAL_CACHE_INFO {
    CACHE_DESCRIPTOR CacheDescriptor;
    BOOLEAN GlobalSyncRequired;
} HAL_EXTERNAL_CACHE_INFO, *PHAL_EXTERNAL_CACHE_INFO;

typedef union _HAL_PSCI_INFO {
    ULONG Flags;
    struct {
        ULONG CpuDefaultSuspendSupported: 1;
        ULONG Reserved: 31;
    };
} HAL_PSCI_INFO, *PHAL_PSCI_INFO;

typedef union _INTERRUPT_CONTROLLER_INFO {
    ULONG Flags;
    struct {
        ULONG InterruptSteeringCapable: 1;
        ULONG Reserved: 31;
    };
} INTERRUPT_CONTROLLER_INFO, *PINTERRUPT_CONTROLLER_INFO;

typedef struct _ARM_ERRATA_INFO {
    union {
        ULONG Flags;
        struct {
            ULONG SignalIpiOnTlbFlush : 1;
            ULONG Reserved: 31;
        };
    };
} ARM_ERRATA_INFO, *PARM_ERRATA_INFO;

typedef
NTSTATUS
(*PHALIOREADWRITEHANDLER)(
    _In_      BOOLEAN fRead,
    _In_      ULONG dwAddr,
    _In_      ULONG dwSize,
    _Inout_  PULONG pdwData
    );

typedef struct _HAL_AMLI_BAD_IO_ADDRESS_LIST
{
    ULONG                   BadAddrBegin;
    ULONG                   BadAddrSize;
    ULONG                   OSVersionTrigger;
    PHALIOREADWRITEHANDLER  IOHandler;
} HAL_AMLI_BAD_IO_ADDRESS_LIST, *PHAL_AMLI_BAD_IO_ADDRESS_LIST;

typedef enum {
    InterruptTargetTypeApic,
    InterruptTargetTypeApicRequest,
    InterruptTargetTypeGlobal           // use for Interrupt Controller Input
} HAL_INTERRUPT_TARGET_TYPE;

#define INTERRUPT_TARGET_APIC_MSI_SUPPORTED             0x1
#define INTERRUPT_TARGET_APIC_PHYSICAL_MODE_SUPPORTED   0x2
#define INTERRUPT_TARGET_PM_REQUIRES_BREAK_EVENT        0x4
#define INTERRUPT_TARGET_ONE_PENDING_INTERRUPT_PER_IRQL 0x8

typedef enum {
    ApicDestinationModePhysical = 1,
    ApicDestinationModeLogicalFlat,
    ApicDestinationModeLogicalClustered,
    ApicDestinationModeUnknown
} HAL_APIC_DESTINATION_MODE, *PHAL_APIC_DESTINATION_MODE;

typedef struct _HAL_INTERRUPT_TARGET_INFORMATION {
    HAL_INTERRUPT_TARGET_TYPE Type;
    PROCESSOR_NUMBER ProcessorNumber;
    ULONG Flags;

    union {
        struct {
            ULONG LogicalApicId;
            ULONG ClusterId;
            HAL_APIC_DESTINATION_MODE DestinationMode;
        } Apic;

        struct {
            BOOLEAN Enabled;
            ULONG MinimumIndex;
            ULONG MaximumIndex;
        } Irt;
    };
} HAL_INTERRUPT_TARGET_INFORMATION, *PHAL_INTERRUPT_TARGET_INFORMATION;

typedef struct _INTERRUPT_REMAPPING_INFO {
    ULONG IrtIndex:30;
    ULONG FlagHalInternal:1;
    ULONG FlagTranslated:1;

    union {
        ULARGE_INTEGER RemappedFormat; // generic form

        struct {
            ULONG   MessageAddressLow;
            USHORT  MessageData;
            USHORT  Reserved;
        } Msi;
    } u;
} INTERRUPT_REMAPPING_INFO, *PINTERRUPT_REMAPPING_INFO;

typedef struct _HAL_MESSAGE_TARGET_REQUEST {
    HAL_INTERRUPT_TARGET_TYPE Type;

    struct {
        ULONG Vector;
        GROUP_AFFINITY TargetProcessors;
        HAL_APIC_DESTINATION_MODE DestinationMode;
        INTERRUPT_REMAPPING_INFO IntRemapInfo;
    } Apic;
} HAL_MESSAGE_TARGET_REQUEST, *PHAL_MESSAGE_TARGET_REQUEST;

NTHALAPI
NTSTATUS
HalGetInterruptTargetInformation (
    _In_ HAL_INTERRUPT_TARGET_TYPE TargetType,
    _In_ ULONG ProcessorId,
    _Out_ PHAL_INTERRUPT_TARGET_INFORMATION TargetInformation
    );

NTHALAPI
NTSTATUS
HalGetMessageRoutingInfo (
    _In_ PHAL_MESSAGE_TARGET_REQUEST Request,
    _Out_ PINTERRUPT_CONNECTION_DATA ConnectionData
    );

typedef enum {
    InterruptTypeControllerInput,
    InterruptTypeXapicMessage,
    InterruptTypeHypertransport,
    InterruptTypeMessageRequest
} INTERRUPT_CONNECTION_TYPE;

typedef struct _INTERRUPT_HT_INTR_INFO {

    union {
        struct {
            ULONG Mask:1;             // bit 0
            ULONG Polarity:1;         // bit 1
            ULONG MessageType:3;      // bits [4:2]
            ULONG RequestEOI:1;       // bit 5
            ULONG DestinationMode:1;  // bit 6
            ULONG MessageType3:1;     // bit 7
            ULONG Destination:8;      // bits [15:8]
            ULONG Vector:8;           // bits [23:16]
            ULONG ExtendedAddress:8;  // bits [31:24] -- always set to 0xF8
        } bits;

        ULONG AsULONG;

    } LowPart;

    union {
        struct {
            ULONG ExtendedDestination:24;
            ULONG Reserved:6;
            ULONG PassPW:1;
            ULONG WaitingForEOI:1;
        } bits;

        ULONG AsULONG;

    } HighPart;

} INTERRUPT_HT_INTR_INFO, *PINTERRUPT_HT_INTR_INFO;

typedef struct _INTERRUPT_VECTOR_DATA {

    INTERRUPT_CONNECTION_TYPE Type;
    ULONG Vector;
    KIRQL Irql;

    KINTERRUPT_POLARITY Polarity;
    KINTERRUPT_MODE Mode;
    GROUP_AFFINITY TargetProcessors;
    INTERRUPT_REMAPPING_INFO IntRemapInfo;

    struct {
        ULONG Gsiv;
        ULONG WakeInterrupt:1;
        ULONG ReservedFlags:31;
    } ControllerInput;

    union {
        struct {
            PHYSICAL_ADDRESS Address;
            ULONG DataPayload;
        } XapicMessage;

        struct {
            INTERRUPT_HT_INTR_INFO IntrInfo;
        } Hypertransport;

        struct {
            PHYSICAL_ADDRESS Address;
            ULONG DataPayload;
        } GenericMessage;

        struct {
            HAL_APIC_DESTINATION_MODE DestinationMode;
        } MessageRequest;
    };
} INTERRUPT_VECTOR_DATA, *PINTERRUPT_VECTOR_DATA;

typedef struct _INTERRUPT_CONNECTION_DATA {

    ULONG Count;

    _Field_size_full_(Count)
    INTERRUPT_VECTOR_DATA Vectors[ANYSIZE_ARRAY];

} INTERRUPT_CONNECTION_DATA, *PINTERRUPT_CONNECTION_DATA;

typedef struct _SCATTER_GATHER_ELEMENT {
    PHYSICAL_ADDRESS Address;
    ULONG Length;
    ULONG_PTR Reserved;
} SCATTER_GATHER_ELEMENT, *PSCATTER_GATHER_ELEMENT;

#if defined(_MSC_EXTENSIONS)

#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4200)
typedef struct _SCATTER_GATHER_LIST {
    ULONG NumberOfElements;
    ULONG_PTR Reserved;
    SCATTER_GATHER_ELEMENT Elements[];
} SCATTER_GATHER_LIST, *PSCATTER_GATHER_LIST;
#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4200)
#endif

#else

struct _SCATTER_GATHER_LIST;
typedef struct _SCATTER_GATHER_LIST SCATTER_GATHER_LIST, *PSCATTER_GATHER_LIST;

#endif

typedef struct _DMA_OPERATIONS *PDMA_OPERATIONS;

#define HAL_DMA_ADAPTER_VERSION_1 1

typedef struct _DMA_ADAPTER {
    USHORT Version;
    USHORT Size;
    PDMA_OPERATIONS DmaOperations;
    // Private Bus Device Driver data follows,
} DMA_ADAPTER, *PDMA_ADAPTER;

typedef enum {
    DmaComplete,
    DmaAborted,
    DmaError,
    DmaCancelled
} DMA_COMPLETION_STATUS;

typedef VOID (*PPUT_DMA_ADAPTER)(
    PDMA_ADAPTER DmaAdapter
    );

typedef PVOID (*PALLOCATE_COMMON_BUFFER)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ ULONG Length,
    _Out_ PPHYSICAL_ADDRESS LogicalAddress,
    _In_ BOOLEAN CacheEnabled
    );

typedef VOID (*PFREE_COMMON_BUFFER)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ ULONG Length,
    _In_ PHYSICAL_ADDRESS LogicalAddress,
    _In_ PVOID VirtualAddress,
    _In_ BOOLEAN CacheEnabled
    );

typedef NTSTATUS (*PALLOCATE_ADAPTER_CHANNEL)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG NumberOfMapRegisters,
    _In_ PDRIVER_CONTROL ExecutionRoutine,
    _In_ PVOID Context
    );

typedef BOOLEAN (*PFLUSH_ADAPTER_BUFFERS)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PMDL Mdl,
    _In_ PVOID MapRegisterBase,
    _In_ PVOID CurrentVa,
    _In_ ULONG Length,
    _In_ BOOLEAN WriteToDevice
    );

typedef VOID (*PFREE_ADAPTER_CHANNEL)(
    _In_ PDMA_ADAPTER DmaAdapter
    );

typedef VOID (*PFREE_ADAPTER_OBJECT)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ IO_ALLOCATION_ACTION AllocationAction
    );

typedef VOID (*PFREE_MAP_REGISTERS)(
    _In_ PDMA_ADAPTER DmaAdapter,
    PVOID MapRegisterBase,
    ULONG NumberOfMapRegisters
    );

typedef PHYSICAL_ADDRESS (*PMAP_TRANSFER)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PMDL Mdl,
    _In_ PVOID MapRegisterBase,
    _In_ PVOID CurrentVa,
    _Inout_ PULONG Length,
    _In_ BOOLEAN WriteToDevice
    );

typedef ULONG (*PGET_DMA_ALIGNMENT)(
    _In_ PDMA_ADAPTER DmaAdapter
    );

typedef ULONG (*PREAD_DMA_COUNTER)(
    _In_ PDMA_ADAPTER DmaAdapter
    );

typedef
_Function_class_(DRIVER_LIST_CONTROL)
_IRQL_requires_same_
VOID
DRIVER_LIST_CONTROL(
    _In_ struct _DEVICE_OBJECT *DeviceObject,
    _In_ struct _IRP *Irp,
    _In_ PSCATTER_GATHER_LIST ScatterGather,
    _In_ PVOID Context
    );
typedef DRIVER_LIST_CONTROL *PDRIVER_LIST_CONTROL;

typedef NTSTATUS
(*PGET_SCATTER_GATHER_LIST)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PMDL Mdl,
    _In_ PVOID CurrentVa,
    _In_ ULONG Length,
    _In_ PDRIVER_LIST_CONTROL ExecutionRoutine,
    _In_ PVOID Context,
    _In_ BOOLEAN WriteToDevice
    );

typedef VOID
(*PPUT_SCATTER_GATHER_LIST)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PSCATTER_GATHER_LIST ScatterGather,
    _In_ BOOLEAN WriteToDevice
    );

typedef NTSTATUS
(*PCALCULATE_SCATTER_GATHER_LIST_SIZE)(
     _In_ PDMA_ADAPTER DmaAdapter,
     _In_ OPTIONAL PMDL Mdl,
     _In_ PVOID CurrentVa,
     _In_ ULONG Length,
     _Out_ PULONG  ScatterGatherListSize,
     _Out_ OPTIONAL PULONG pNumberOfMapRegisters
     );

typedef NTSTATUS
(*PBUILD_SCATTER_GATHER_LIST)(
     _In_ PDMA_ADAPTER DmaAdapter,
     _In_ PDEVICE_OBJECT DeviceObject,
     _In_ PMDL Mdl,
     _In_ PVOID CurrentVa,
     _In_ ULONG Length,
     _In_ PDRIVER_LIST_CONTROL ExecutionRoutine,
     _In_ PVOID Context,
     _In_ BOOLEAN WriteToDevice,
     _In_ PVOID   ScatterGatherBuffer,
     _In_ ULONG   ScatterGatherLength
     );

typedef NTSTATUS
(*PBUILD_MDL_FROM_SCATTER_GATHER_LIST)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PSCATTER_GATHER_LIST ScatterGather,
    _In_ PMDL OriginalMdl,
    _Out_ PMDL *TargetMdl
    );

typedef NTSTATUS
(*PGET_DMA_ADAPTER_INFO)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _Inout_ PDMA_ADAPTER_INFO AdapterInfo
    );

typedef NTSTATUS
(*PGET_DMA_TRANSFER_INFO)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PMDL Mdl,
    _In_ ULONGLONG Offset,
    _In_ ULONG Length,
    _In_ BOOLEAN WriteOnly,
    _Inout_ PDMA_TRANSFER_INFO TransferInfo
    );

typedef NTSTATUS
(*PCONFIGURE_ADAPTER_CHANNEL)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ ULONG FunctionNumber,
    _In_ PVOID Context
    );

typedef NTSTATUS
(*PINITIALIZE_DMA_TRANSFER_CONTEXT)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _Out_ PVOID DmaTransferContext
    );

typedef PVOID
(*PALLOCATE_COMMON_BUFFER_EX)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_opt_ PPHYSICAL_ADDRESS MaximumAddress,
    _In_ ULONG Length,
    _Out_ PPHYSICAL_ADDRESS LogicalAddress,
    _In_ BOOLEAN CacheEnabled,
    _In_ NODE_REQUIREMENT PreferredNode
    );

typedef NTSTATUS
(*PALLOCATE_ADAPTER_CHANNEL_EX)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PVOID DmaTransferContext,
    _In_ ULONG NumberOfMapRegisters,
    _In_ ULONG Flags,
    _In_opt_ PDRIVER_CONTROL ExecutionRoutine,
    _In_opt_ PVOID ExecutionContext,
    _Out_opt_ PVOID *MapRegisterBase
    );

typedef VOID
_Function_class_(DMA_COMPLETION_ROUTINE)
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
DMA_COMPLETION_ROUTINE(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PVOID CompletionContext,
    _In_ DMA_COMPLETION_STATUS Status
    );
typedef DMA_COMPLETION_ROUTINE *PDMA_COMPLETION_ROUTINE;

typedef NTSTATUS
(*PMAP_TRANSFER_EX)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PMDL Mdl,
    _In_ PVOID MapRegisterBase,
    _In_ ULONGLONG Offset,
    _In_ ULONG DeviceOffset,
    _Inout_ PULONG Length,
    _In_ BOOLEAN WriteToDevice,
    _Out_writes_bytes_opt_(ScatterGatherBufferLength) PSCATTER_GATHER_LIST ScatterGatherBuffer,
    _In_ ULONG ScatterGatherBufferLength,
    _In_opt_ PDMA_COMPLETION_ROUTINE DmaCompletionRoutine,
    _In_opt_ PVOID CompletionContext
    );

typedef BOOLEAN
(*PCANCEL_ADAPTER_CHANNEL)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PVOID DmaTransferContext
    );

typedef NTSTATUS
(*PCANCEL_MAPPED_TRANSFER)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PVOID DmaTransferContext
    );

typedef NTSTATUS
(*PFLUSH_ADAPTER_BUFFERS_EX)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PMDL Mdl,
    _In_ PVOID MapRegisterBase,
    _In_ ULONGLONG Offset,
    _In_ ULONG Length,
    _In_ BOOLEAN WriteToDevice
    );

typedef NTSTATUS
(*PGET_SCATTER_GATHER_LIST_EX)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PVOID DmaTransferContext,
    _In_ PMDL Mdl,
    _In_ ULONGLONG Offset,
    _In_ ULONG Length,
    _In_ ULONG Flags,
    _In_opt_ PDRIVER_LIST_CONTROL ExecutionRoutine,
    _In_opt_ PVOID Context,
    _In_ BOOLEAN WriteToDevice,
    _In_opt_ PDMA_COMPLETION_ROUTINE DmaCompletionRoutine,
    _In_opt_ PVOID CompletionContext,
    _Out_opt_ PSCATTER_GATHER_LIST *ScatterGatherList
    );

typedef NTSTATUS
(*PBUILD_SCATTER_GATHER_LIST_EX)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PVOID DmaTransferContext,
    _In_ PMDL Mdl,
    _In_ ULONGLONG Offset,
    _In_ ULONG Length,
    _In_ ULONG Flags,
    _In_opt_ PDRIVER_LIST_CONTROL ExecutionRoutine,
    _In_opt_ PVOID Context,
    _In_ BOOLEAN WriteToDevice,
    _In_ PVOID ScatterGatherBuffer,
    _In_ ULONG ScatterGatherLength,
    _In_opt_ PDMA_COMPLETION_ROUTINE DmaCompletionRoutine,
    _In_opt_ PVOID CompletionContext,
    _Out_opt_ PVOID ScatterGatherList
    );

typedef NTSTATUS
(*PALLOCATE_DOMAIN_COMMON_BUFFER)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ HANDLE DomainHandle,
    _In_opt_ PPHYSICAL_ADDRESS MaximumAddress,
    _In_ ULONG Length,
    _In_ ULONG Flags,
    _In_opt_ MEMORY_CACHING_TYPE *CacheType,
    _In_ NODE_REQUIREMENT PreferredNode,
    _Out_ PPHYSICAL_ADDRESS LogicalAddress,
    _Out_ PVOID *VirtualAddress
    );

#define DOMAIN_COMMON_BUFFER_LARGE_PAGE                 0x0001

typedef NTSTATUS
(*PFLUSH_DMA_BUFFER)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PMDL Mdl,
    _In_ BOOLEAN ReadOperation
);

typedef NTSTATUS
(*PJOIN_DMA_DOMAIN)(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ HANDLE DomainHandle
);

typedef NTSTATUS
(*PLEAVE_DMA_DOMAIN)(
    _In_ PDMA_ADAPTER DmaAdapter
);

typedef HANDLE
(*PGET_DMA_DOMAIN)(
    _In_ PDMA_ADAPTER DmaAdapter
);

typedef struct _DMA_OPERATIONS {
    ULONG Size;
    PPUT_DMA_ADAPTER PutDmaAdapter;
    PALLOCATE_COMMON_BUFFER AllocateCommonBuffer;
    PFREE_COMMON_BUFFER FreeCommonBuffer;
    PALLOCATE_ADAPTER_CHANNEL AllocateAdapterChannel;
    PFLUSH_ADAPTER_BUFFERS FlushAdapterBuffers;
    PFREE_ADAPTER_CHANNEL FreeAdapterChannel;
    PFREE_MAP_REGISTERS FreeMapRegisters;
    PMAP_TRANSFER MapTransfer;
    PGET_DMA_ALIGNMENT GetDmaAlignment;
    PREAD_DMA_COUNTER ReadDmaCounter;
    PGET_SCATTER_GATHER_LIST GetScatterGatherList;
    PPUT_SCATTER_GATHER_LIST PutScatterGatherList;
    PCALCULATE_SCATTER_GATHER_LIST_SIZE CalculateScatterGatherList;
    PBUILD_SCATTER_GATHER_LIST BuildScatterGatherList;
    PBUILD_MDL_FROM_SCATTER_GATHER_LIST BuildMdlFromScatterGatherList;
    PGET_DMA_ADAPTER_INFO GetDmaAdapterInfo;
    PGET_DMA_TRANSFER_INFO GetDmaTransferInfo;
    PINITIALIZE_DMA_TRANSFER_CONTEXT InitializeDmaTransferContext;
    PALLOCATE_COMMON_BUFFER_EX AllocateCommonBufferEx;
    PALLOCATE_ADAPTER_CHANNEL_EX AllocateAdapterChannelEx;
    PCONFIGURE_ADAPTER_CHANNEL ConfigureAdapterChannel;
    PCANCEL_ADAPTER_CHANNEL CancelAdapterChannel;
    PMAP_TRANSFER_EX MapTransferEx;
    PGET_SCATTER_GATHER_LIST_EX GetScatterGatherListEx;
    PBUILD_SCATTER_GATHER_LIST_EX BuildScatterGatherListEx;
    PFLUSH_ADAPTER_BUFFERS_EX FlushAdapterBuffersEx;
    PFREE_ADAPTER_OBJECT FreeAdapterObject;
    PCANCEL_MAPPED_TRANSFER CancelMappedTransfer;
    PALLOCATE_DOMAIN_COMMON_BUFFER AllocateDomainCommonBuffer;
    PFLUSH_DMA_BUFFER FlushDmaBuffer;
    PJOIN_DMA_DOMAIN JoinDmaDomain;
    PLEAVE_DMA_DOMAIN LeaveDmaDomain;
    PGET_DMA_DOMAIN GetDmaDomain;
} DMA_OPERATIONS;

#if defined(_WIN64) || defined(_ARM_)

#ifndef USE_DMA_MACROS
#define USE_DMA_MACROS
#endif

#ifndef NO_LEGACY_DRIVERS
#define NO_LEGACY_DRIVERS
#endif

#endif // _WIN64

#if defined(USE_DMA_MACROS) && !defined(_NTHAL_) && (defined(_NTDDK_) || defined(_NTDRIVER_)) || defined(_WDM_INCLUDED_) // ntddk

DECLSPEC_DEPRECATED_DDK                 // Use AllocateCommonBuffer
__drv_preferredFunction("AllocateCommonBuffer","Obsolete")
FORCEINLINE
PVOID
HalAllocateCommonBuffer(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ ULONG Length,
    _Out_ PPHYSICAL_ADDRESS LogicalAddress,
    _In_ BOOLEAN CacheEnabled)
{
    PALLOCATE_COMMON_BUFFER allocateCommonBuffer;
    PVOID commonBuffer;

    allocateCommonBuffer = *(DmaAdapter)->DmaOperations->AllocateCommonBuffer;
    NT_ASSERT( allocateCommonBuffer != NULL );

    commonBuffer = allocateCommonBuffer( DmaAdapter,
                                         Length,
                                         LogicalAddress,
                                         CacheEnabled );

    return commonBuffer;
}

DECLSPEC_DEPRECATED_DDK                 // Use FreeCommonBuffer
__drv_preferredFunction("FreeCommonBuffer","Obsolete")
FORCEINLINE
VOID
HalFreeCommonBuffer(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ ULONG Length,
    _In_ PHYSICAL_ADDRESS LogicalAddress,
    _In_ PVOID VirtualAddress,
    _In_ BOOLEAN CacheEnabled)
{
    PFREE_COMMON_BUFFER freeCommonBuffer;

    freeCommonBuffer = *(DmaAdapter)->DmaOperations->FreeCommonBuffer;
    NT_ASSERT( freeCommonBuffer != NULL );

    freeCommonBuffer( DmaAdapter,
                      Length,
                      LogicalAddress,
                      VirtualAddress,
                      CacheEnabled );
}

DECLSPEC_DEPRECATED_DDK                 // Use AllocateAdapterChannel
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_min_(DISPATCH_LEVEL)
__drv_preferredFunction("AllocateAdapterChannel","obsolete")
FORCEINLINE
NTSTATUS
IoAllocateAdapterChannel(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ ULONG NumberOfMapRegisters,
    _In_ PDRIVER_CONTROL ExecutionRoutine,
    _In_ PVOID Context)
{
    PALLOCATE_ADAPTER_CHANNEL allocateAdapterChannel;
    NTSTATUS status;

    allocateAdapterChannel =
        *(DmaAdapter)->DmaOperations->AllocateAdapterChannel;

    NT_ASSERT( allocateAdapterChannel != NULL );

    status = allocateAdapterChannel( DmaAdapter,
                                     DeviceObject,
                                     NumberOfMapRegisters,
                                     ExecutionRoutine,
                                     Context );

    return status;
}

DECLSPEC_DEPRECATED_DDK                 // Use FlushAdapterBuffers
__drv_preferredFunction("FlushAdapterBuffers","Obsolete")
FORCEINLINE
BOOLEAN
IoFlushAdapterBuffers(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PMDL Mdl,
    _In_ PVOID MapRegisterBase,
    _In_ PVOID CurrentVa,
    _In_ ULONG Length,
    _In_ BOOLEAN WriteToDevice)
{
    PFLUSH_ADAPTER_BUFFERS flushAdapterBuffers;
    BOOLEAN result;

    flushAdapterBuffers = *(DmaAdapter)->DmaOperations->FlushAdapterBuffers;
    NT_ASSERT( flushAdapterBuffers != NULL );

    result = flushAdapterBuffers( DmaAdapter,
                                  Mdl,
                                  MapRegisterBase,
                                  CurrentVa,
                                  Length,
                                  WriteToDevice );
    return result;
}

DECLSPEC_DEPRECATED_DDK                 // Use FreeAdapterChannel
__drv_preferredFunction("FreeAdapterChannel","Obsolete")
FORCEINLINE
VOID
IoFreeAdapterChannel(
    _In_ PDMA_ADAPTER DmaAdapter)
{
    PFREE_ADAPTER_CHANNEL freeAdapterChannel;

    freeAdapterChannel = *(DmaAdapter)->DmaOperations->FreeAdapterChannel;
    NT_ASSERT( freeAdapterChannel != NULL );

    freeAdapterChannel( DmaAdapter );
}

DECLSPEC_DEPRECATED_DDK                 // Use FreeMapRegisters
__drv_preferredFunction("FreeMapRegisters","Obsolete")
FORCEINLINE
VOID
IoFreeMapRegisters(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PVOID MapRegisterBase,
    _In_ ULONG NumberOfMapRegisters)
{
    PFREE_MAP_REGISTERS freeMapRegisters;

    freeMapRegisters = *(DmaAdapter)->DmaOperations->FreeMapRegisters;
    NT_ASSERT( freeMapRegisters != NULL );

    freeMapRegisters( DmaAdapter,
                      MapRegisterBase,
                      NumberOfMapRegisters );
}


DECLSPEC_DEPRECATED_DDK                 // Use MapTransfer
__drv_preferredFunction("MapTransfer","Obsolete")
FORCEINLINE
PHYSICAL_ADDRESS
IoMapTransfer(
    _In_ PDMA_ADAPTER DmaAdapter,
    _In_ PMDL Mdl,
    _In_ PVOID MapRegisterBase,
    _In_ PVOID CurrentVa,
    _Inout_ PULONG Length,
    _In_ BOOLEAN WriteToDevice)
{
    PHYSICAL_ADDRESS physicalAddress;
    PMAP_TRANSFER mapTransfer;

    mapTransfer = *(DmaAdapter)->DmaOperations->MapTransfer;
    NT_ASSERT( mapTransfer != NULL );

    physicalAddress = mapTransfer( DmaAdapter,
                                   Mdl,
                                   MapRegisterBase,
                                   CurrentVa,
                                   Length,
                                   WriteToDevice );

    return physicalAddress;
}

DECLSPEC_DEPRECATED_DDK                 // Use GetDmaAlignment
FORCEINLINE
ULONG
HalGetDmaAlignment(
    _In_ PDMA_ADAPTER DmaAdapter)
{
    PGET_DMA_ALIGNMENT getDmaAlignment;
    ULONG alignment;

    getDmaAlignment = *(DmaAdapter)->DmaOperations->GetDmaAlignment;
    NT_ASSERT( getDmaAlignment != NULL );

    alignment = getDmaAlignment( DmaAdapter );
    return alignment;
}

DECLSPEC_DEPRECATED_DDK                 // Use ReadDmaCounter
__drv_preferredFunction("ReadDmaCounter","Obsolete")
FORCEINLINE
ULONG
HalReadDmaCounter(
    _In_ PDMA_ADAPTER DmaAdapter)
{
    PREAD_DMA_COUNTER readDmaCounter;
    ULONG counter;

    readDmaCounter = *(DmaAdapter)->DmaOperations->ReadDmaCounter;
    NT_ASSERT( readDmaCounter != NULL );

    counter = readDmaCounter( DmaAdapter );
    return counter;
}

#else

DECLSPEC_DEPRECATED_DDK                 // Use AllocateAdapterChannel
NTHALAPI
NTSTATUS
HalAllocateAdapterChannel(
    _In_ PADAPTER_OBJECT AdapterObject,
    _In_ PWAIT_CONTEXT_BLOCK Wcb,
    _In_ ULONG NumberOfMapRegisters,
    _In_ PDRIVER_CONTROL ExecutionRoutine
    );

DECLSPEC_DEPRECATED_DDK                 // Use AllocateCommonBuffer
__drv_preferredFunction("AllocateCommonBuffer","Obsolete")
NTHALAPI
PVOID
HalAllocateCommonBuffer(
    _In_ PADAPTER_OBJECT AdapterObject,
    _In_ ULONG Length,
    _Out_ PPHYSICAL_ADDRESS LogicalAddress,
    _In_ BOOLEAN CacheEnabled
    );

DECLSPEC_DEPRECATED_DDK                 // Use FreeCommonBuffer
__drv_preferredFunction("FreeCommonBuffer","Obsolete")
NTHALAPI
VOID
HalFreeCommonBuffer(
    _In_ PADAPTER_OBJECT AdapterObject,
    _In_ ULONG Length,
    _In_ PHYSICAL_ADDRESS LogicalAddress,
    _In_ PVOID VirtualAddress,
    _In_ BOOLEAN CacheEnabled
    );

DECLSPEC_DEPRECATED_DDK                 // Use ReadDmaCounter
__drv_preferredFunction("ReadDmaCounter","Obsolete")
NTHALAPI
ULONG
HalReadDmaCounter(
    _In_ PADAPTER_OBJECT AdapterObject
    );

DECLSPEC_DEPRECATED_DDK                 // Use FlushAdapterBuffers
__drv_preferredFunction("FlushAdapterBuffers","Obsolete")
NTHALAPI
BOOLEAN
IoFlushAdapterBuffers(
    _In_ PADAPTER_OBJECT AdapterObject,
    _In_ PMDL Mdl,
    _In_ PVOID MapRegisterBase,
    _In_ PVOID CurrentVa,
    _In_ ULONG Length,
    _In_ BOOLEAN WriteToDevice
    );

DECLSPEC_DEPRECATED_DDK                 // Use FreeAdapterChannel
__drv_preferredFunction("FreeAdapterChannel","Obsolete")
NTHALAPI
VOID
IoFreeAdapterChannel(
    _In_ PADAPTER_OBJECT AdapterObject
    );

DECLSPEC_DEPRECATED_DDK                 // Use FreeMapRegisters
__drv_preferredFunction("FreeMapRegisters","Obsolete")
NTHALAPI
VOID
IoFreeMapRegisters(
   _In_ PADAPTER_OBJECT AdapterObject,
   _In_ PVOID MapRegisterBase,
   _In_ ULONG NumberOfMapRegisters
   );

DECLSPEC_DEPRECATED_DDK                 // Use MapTransfer
__drv_preferredFunction("MapTransfer","Obsolete")
NTHALAPI
PHYSICAL_ADDRESS
IoMapTransfer(
    _In_ PADAPTER_OBJECT AdapterObject,
    _In_ PMDL Mdl,
    _In_ PVOID MapRegisterBase,
    _In_ PVOID CurrentVa,
    _Inout_ PULONG Length,
    _In_ BOOLEAN WriteToDevice
    );

#endif // USE_DMA_MACROS && (_NTDDK_ || _NTDRIVER_)

DECLSPEC_DEPRECATED_DDK
NTSTATUS
HalGetScatterGatherList (               // Use GetScatterGatherList
    _In_ PADAPTER_OBJECT DmaAdapter,
    _In_ PDEVICE_OBJECT DeviceObject,
    _In_ PMDL Mdl,
    _In_ PVOID CurrentVa,
    _In_ ULONG Length,
    _In_ PDRIVER_LIST_CONTROL ExecutionRoutine,
    _In_ PVOID Context,
    _In_ BOOLEAN WriteToDevice
    );

DECLSPEC_DEPRECATED_DDK                 // Use PutScatterGatherList
VOID
HalPutScatterGatherList (
    _In_ PADAPTER_OBJECT DmaAdapter,
    _In_ PSCATTER_GATHER_LIST ScatterGather,
    _In_ BOOLEAN WriteToDevice
    );

DECLSPEC_DEPRECATED_DDK                 // Use PutDmaAdapter
VOID
HalPutDmaAdapter(
    _In_ PADAPTER_OBJECT DmaAdapter
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)

typedef struct _WHEA_ERROR_SOURCE_DESCRIPTOR *PWHEA_ERROR_SOURCE_DESCRIPTOR;
typedef struct _WHEA_ERROR_RECORD *PWHEA_ERROR_RECORD;

NTHALAPI
VOID
HalBugCheckSystem (
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _In_ PWHEA_ERROR_RECORD ErrorRecord
    );

#elif (NTDDI_VERSION >= NTDDI_VISTA)

typedef struct _WHEA_ERROR_RECORD *PWHEA_ERROR_RECORD;

NTHALAPI
VOID
HalBugCheckSystem (
    _In_ PWHEA_ERROR_RECORD ErrorRecord
    );

#endif

typedef struct _SECURITY_SUBJECT_CONTEXT {
    PACCESS_TOKEN ClientToken;
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
    PACCESS_TOKEN PrimaryToken;
    PVOID ProcessAuditId;
} SECURITY_SUBJECT_CONTEXT, *PSECURITY_SUBJECT_CONTEXT;

#define INITIAL_PRIVILEGE_COUNT         3

typedef struct _INITIAL_PRIVILEGE_SET {
    ULONG PrivilegeCount;
    ULONG Control;
    LUID_AND_ATTRIBUTES Privilege[INITIAL_PRIVILEGE_COUNT];
} INITIAL_PRIVILEGE_SET, * PINITIAL_PRIVILEGE_SET;

typedef struct _ACCESS_STATE {
   LUID OperationID;                // Currently unused, replaced by TransactionId in AUX_ACCESS_DATA
   BOOLEAN SecurityEvaluated;
   BOOLEAN GenerateAudit;
   BOOLEAN GenerateOnClose;
   BOOLEAN PrivilegesAllocated;
   ULONG Flags;
   ACCESS_MASK RemainingDesiredAccess;
   ACCESS_MASK PreviouslyGrantedAccess;
   ACCESS_MASK OriginalDesiredAccess;
   SECURITY_SUBJECT_CONTEXT SubjectSecurityContext;
   PSECURITY_DESCRIPTOR SecurityDescriptor; // it stores SD supplied by caller when creating a new object.
   PVOID AuxData;
   union {
      INITIAL_PRIVILEGE_SET InitialPrivilegeSet;
      PRIVILEGE_SET PrivilegeSet;
      } Privileges;

   BOOLEAN AuditPrivileges;
   UNICODE_STRING ObjectName;
   UNICODE_STRING ObjectTypeName;

} ACCESS_STATE, *PACCESS_STATE;

typedef VOID
(*PNTFS_DEREF_EXPORTED_SECURITY_DESCRIPTOR)(
    _In_ PVOID  Vcb,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor);


typedef struct _AUX_ACCESS_DATA {
    PPRIVILEGE_SET PrivilegesUsed;
    GENERIC_MAPPING GenericMapping;
    ACCESS_MASK AccessesToAudit;
    ACCESS_MASK MaximumAuditMask;
    GUID TransactionId;
    PSECURITY_DESCRIPTOR NewSecurityDescriptor; // The new SD for a new object.
    PSECURITY_DESCRIPTOR ExistingSecurityDescriptor; // The exisiting SD that has been passed into SeAccessCheck.
    PSECURITY_DESCRIPTOR ParentSecurityDescriptor; // The parent SD that has been passed into SeAccessCheck to check delete and read attribute.
    PNTFS_DEREF_EXPORTED_SECURITY_DESCRIPTOR DeRefSecurityDescriptor;
    PVOID SDLock;
    ACCESS_REASONS AccessReasons;
    BOOLEAN GenerateStagingEvents;
} AUX_ACCESS_DATA, *PAUX_ACCESS_DATA;

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
BOOLEAN
SeAccessCheckWithHint(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG SecurityDescriptorFlags,
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
    _In_ BOOLEAN SubjectContextLocked,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK PreviouslyGrantedAccess,
    _Outptr_opt_ PPRIVILEGE_SET *Privileges,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
BOOLEAN
SeAccessCheckEx(
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
    _In_ BOOLEAN SubjectContextLocked,
    _Inout_ PSE_ACCESS_REQUEST Request,
    _Inout_ PSE_ACCESS_REPLY Reply,
    _Inout_opt_ PSE_AUDIT_INFO AuditInfo,
    _In_ KPROCESSOR_MODE AccessMode
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
BOOLEAN
SeSrpAccessCheck(
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
    _In_ BOOLEAN SubjectContextLocked,
    _Inout_ PSE_ACCESS_REQUEST Request,
    _Inout_ PSE_ACCESS_REPLY Reply,
    _Inout_opt_ PSE_AUDIT_INFO AuditInfo,
    _In_ KPROCESSOR_MODE AccessMode
    );

FORCEINLINE
VOID
SeSetAccessStateNewSecurityDescriptor(
    _Inout_ PACCESS_STATE AccessState,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    PAUX_ACCESS_DATA AuxData = (PAUX_ACCESS_DATA)(AccessState->AuxData);

    if (AuxData->NewSecurityDescriptor != NULL)
    {
        ExFreePool(AuxData->NewSecurityDescriptor);
    }
    AuxData->NewSecurityDescriptor = SecurityDescriptor;
}


typedef struct _SE_EXPORTS {
    LUID    SeCreateTokenPrivilege;
    LUID    SeAssignPrimaryTokenPrivilege;
    LUID    SeLockMemoryPrivilege;
    LUID    SeIncreaseQuotaPrivilege;
    LUID    SeUnsolicitedInputPrivilege;
    LUID    SeTcbPrivilege;
    LUID    SeSecurityPrivilege;
    LUID    SeTakeOwnershipPrivilege;
    LUID    SeLoadDriverPrivilege;
    LUID    SeCreatePagefilePrivilege;
    LUID    SeIncreaseBasePriorityPrivilege;
    LUID    SeSystemProfilePrivilege;
    LUID    SeSystemtimePrivilege;
    LUID    SeProfileSingleProcessPrivilege;
    LUID    SeCreatePermanentPrivilege;
    LUID    SeBackupPrivilege;
    LUID    SeRestorePrivilege;
    LUID    SeShutdownPrivilege;
    LUID    SeDebugPrivilege;
    LUID    SeAuditPrivilege;
    LUID    SeSystemEnvironmentPrivilege;
    LUID    SeChangeNotifyPrivilege;
    LUID    SeRemoteShutdownPrivilege;
    PSID  SeNullSid;
    PSID  SeWorldSid;
    PSID  SeLocalSid;
    PSID  SeCreatorOwnerSid;
    PSID  SeCreatorGroupSid;
    PSID  SeNtAuthoritySid;
    PSID  SeDialupSid;
    PSID  SeNetworkSid;
    PSID  SeBatchSid;
    PSID  SeInteractiveSid;
    PSID  SeLocalSystemSid;
    PSID  SeAliasAdminsSid;
    PSID  SeAliasUsersSid;
    PSID  SeAliasGuestsSid;
    PSID  SeAliasPowerUsersSid;
    PSID  SeAliasAccountOpsSid;
    PSID  SeAliasSystemOpsSid;
    PSID  SeAliasPrintOpsSid;
    PSID  SeAliasBackupOpsSid;
    PSID  SeAuthenticatedUsersSid;
    PSID  SeRestrictedSid;
    PSID  SeAnonymousLogonSid;
    LUID  SeUndockPrivilege;
    LUID  SeSyncAgentPrivilege;
    LUID  SeEnableDelegationPrivilege;
    PSID  SeLocalServiceSid;
    PSID  SeNetworkServiceSid;
    LUID  SeManageVolumePrivilege;
    LUID  SeImpersonatePrivilege;
    LUID  SeCreateGlobalPrivilege;
    LUID  SeTrustedCredManAccessPrivilege;
    LUID  SeRelabelPrivilege;
    LUID  SeIncreaseWorkingSetPrivilege;
    LUID  SeTimeZonePrivilege;
    LUID  SeCreateSymbolicLinkPrivilege;
    PSID  SeIUserSid;
    PSID SeUntrustedMandatorySid;
    PSID SeLowMandatorySid;
    PSID SeMediumMandatorySid;
    PSID SeHighMandatorySid;
    PSID SeSystemMandatorySid;
    PSID SeOwnerRightsSid;
    PSID SeAllAppPackagesSid;
    PSID SeUserModeDriversSid;
    PSID SeTrustedInstallerSid;

} SE_EXPORTS, *PSE_EXPORTS;

#define SeDeleteClientSecurity(C)  {                                           \
            if (SeTokenType((C)->ClientToken) == TokenPrimary) {               \
                PsDereferencePrimaryToken( (C)->ClientToken );                 \
            } else {                                                           \
                PsDereferenceImpersonationToken( (C)->ClientToken );           \
            }                                                                  \
        }

#define SeStopImpersonatingClient() PsRevertToSelf()

#define SeQuerySubjectContextToken( SubjectContext ) \
        ( ARGUMENT_PRESENT( ((PSECURITY_SUBJECT_CONTEXT) SubjectContext)->ClientToken) ? \
            ((PSECURITY_SUBJECT_CONTEXT) SubjectContext)->ClientToken : \
            ((PSECURITY_SUBJECT_CONTEXT) SubjectContext)->PrimaryToken )

NTKERNELAPI
NTSTATUS
SeCaptureSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR InputSecurityDescriptor,
    _In_ KPROCESSOR_MODE RequestorMode,
    _In_ POOL_TYPE PoolType,
    _In_ BOOLEAN ForceCapture,
    _Outptr_ PSECURITY_DESCRIPTOR *OutputSecurityDescriptor
    );

NTKERNELAPI
VOID
SeReleaseSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR CapturedSecurityDescriptor,
    _In_ KPROCESSOR_MODE RequestorMode,
    _In_ BOOLEAN ForceCapture
    );

NTKERNELAPI
VOID
SeCaptureSubjectContextEx (
    _In_opt_ PETHREAD Thread,
    _In_ PEPROCESS Process,
    _Out_ PSECURITY_SUBJECT_CONTEXT SubjectContext
    );

NTKERNELAPI
VOID
SeCaptureSubjectContext (
    _Out_ PSECURITY_SUBJECT_CONTEXT SubjectContext
    );

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
SeLockSubjectContext(
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectContext
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
SeUnlockSubjectContext(
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectContext
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
SeReleaseSubjectContext (
    _Inout_ PSECURITY_SUBJECT_CONTEXT SubjectContext
    );
#endif


#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
SeAssignSecurity (
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR ExplicitDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *NewDescriptor,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectContext,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ POOL_TYPE PoolType
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTKERNELAPI
ULONG
SeComputeAutoInheritByObjectType(
    _In_ PVOID ObjectType,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR ParentSecurityDescriptor
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
NTSTATUS
SeAssignSecurityEx (
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR ExplicitDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *NewDescriptor,
    _In_opt_ GUID *ObjectType,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ ULONG AutoInheritFlags,
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectContext,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ POOL_TYPE PoolType
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
SeDeassignSecurity (
    _Inout_ PSECURITY_DESCRIPTOR *SecurityDescriptor
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
ULONG
SeObjectCreateSaclAccessBits(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
BOOLEAN
SeAccessCheck (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
    _In_ BOOLEAN SubjectContextLocked,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK PreviouslyGrantedAccess,
    _Outptr_opt_ PPRIVILEGE_SET *Privileges,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
    );
#endif


#ifdef SE_NTFS_WORLD_CACHE

#if (NTDDI_VERSION >= NTDDI_VISTA)
VOID
SeGetWorldRights (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_ PACCESS_MASK GrantedAccess
    );
#endif

#endif

#if (NTDDI_VERSION >= NTDDI_WS03SP1)
_At_(AuditParameters->ParameterCount, _Const_)
NTSTATUS
SeSetAuditParameter(
    _Inout_ PSE_ADT_PARAMETER_ARRAY AuditParameters,
    _In_ SE_ADT_PARAMETER_TYPE Type,
    _In_range_(<,SE_MAX_AUDIT_PARAMETERS) ULONG Index,
    _In_reads_(_Inexpressible_("depends on SE_ADT_PARAMETER_TYPE")) PVOID Data
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WS03SP1)
NTSTATUS
SeReportSecurityEvent(
    _In_ ULONG Flags,
    _In_ PUNICODE_STRING SourceName,
    _In_opt_ PSID UserSid,
    _In_ PSE_ADT_PARAMETER_ARRAY AuditParameters
    );
#endif

NTSTATUS
SeReportSecurityEventWithSubCategory(
    _In_ ULONG Flags,
    _In_ PUNICODE_STRING SourceName,
    _In_opt_ PSID UserSid,
    _In_ PSE_ADT_PARAMETER_ARRAY AuditParameters,
    _In_ ULONG AuditSubcategoryId
    );

BOOLEAN
SeAccessCheckFromState (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PTOKEN_ACCESS_INFORMATION PrimaryTokenInformation,
    _In_opt_ PTOKEN_ACCESS_INFORMATION ClientTokenInformation,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK PreviouslyGrantedAccess,
    _Outptr_opt_result_maybenull_ PPRIVILEGE_SET *Privileges,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
    );

#if (NTDDI_VERSION >= NTDDI_WIN8)
BOOLEAN
SeAccessCheckFromStateEx (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PACCESS_TOKEN PrimaryToken,
    _In_opt_ PACCESS_TOKEN ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK PreviouslyGrantedAccess,
    _Outptr_opt_result_maybenull_ PPRIVILEGE_SET *Privileges,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSTATUS
SeTokenFromAccessInformation(
    _In_opt_ PTOKEN_ACCESS_INFORMATION AccessInformation,
    _Inout_opt_ PACCESS_TOKEN Token,
    _In_ ULONG Length,
    _Out_ PULONG RequiredLength
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
BOOLEAN
SePrivilegeCheck(
    _Inout_ PPRIVILEGE_SET RequiredPrivileges,
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
    _In_ KPROCESSOR_MODE AccessMode
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
SeFreePrivileges(
    _In_ PPRIVILEGE_SET Privileges
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
SeOpenObjectAuditAlarm (
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_opt_ PVOID Object,
    _In_opt_ PUNICODE_STRING AbsoluteObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PACCESS_STATE AccessState,
    _In_ BOOLEAN ObjectCreated,
    _In_ BOOLEAN AccessGranted,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PBOOLEAN GenerateOnClose
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTKERNELAPI
VOID
SeOpenObjectAuditAlarmWithTransaction (
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_opt_ PVOID Object,
    _In_opt_ PUNICODE_STRING AbsoluteObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PACCESS_STATE AccessState,
    _In_ BOOLEAN ObjectCreated,
    _In_ BOOLEAN AccessGranted,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_opt_ GUID *TransactionId,
    _Out_ PBOOLEAN GenerateOnClose
    );
#endif


#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
SeOpenObjectForDeleteAuditAlarm (
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_opt_ PVOID Object,
    _In_opt_ PUNICODE_STRING AbsoluteObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PACCESS_STATE AccessState,
    _In_ BOOLEAN ObjectCreated,
    _In_ BOOLEAN AccessGranted,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PBOOLEAN GenerateOnClose
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTKERNELAPI
VOID
SeOpenObjectForDeleteAuditAlarmWithTransaction (
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_opt_ PVOID Object,
    _In_opt_ PUNICODE_STRING AbsoluteObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PACCESS_STATE AccessState,
    _In_ BOOLEAN ObjectCreated,
    _In_ BOOLEAN AccessGranted,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_opt_ GUID *TransactionId,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTKERNELAPI
VOID
SeExamineSacl(
    _In_ PACL Sacl,
    _In_ PACL ResourceSacl,
    _In_ PACCESS_TOKEN Token,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN AccessGranted,
    _Out_ PBOOLEAN GenerateAudit,
    _Out_ PBOOLEAN GenerateAlarm
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
SeDeleteObjectAuditAlarm(
    _In_ PVOID Object,
    _In_ HANDLE Handle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTKERNELAPI
VOID
SeDeleteObjectAuditAlarmWithTransaction(
    _In_ PVOID Object,
    _In_ HANDLE Handle,
    _In_opt_ GUID *TransactionId
    );



#endif

NTKERNELAPI
VOID
SePrivilegeObjectAuditAlarm(
    _In_ HANDLE Handle,
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted,
    _In_ KPROCESSOR_MODE AccessMode
    );

NTKERNELAPI
VOID
SeOpenObjectAuditAlarmForNonObObject(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_opt_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK GrantedAccess,
    _In_opt_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted,
    _Out_ PBOOLEAN GenerateOnClose
    );

NTKERNELAPI
VOID
SeCloseObjectAuditAlarmForNonObObject(
    _In_ PUNICODE_STRING SubsystemName,
    _In_ PVOID HandleId,
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectSecurityContext,
    _In_ BOOLEAN GenerateOnClose
    );

extern struct _OBJECT_TYPE *SeTokenObjectType;

#if (NTDDI_VERSION >= NTDDI_WIN2K)              // ntifs
NTKERNELAPI                                     // ntifs
TOKEN_TYPE                                      // ntifs
SeTokenType(                                    // ntifs
    _In_ PACCESS_TOKEN Token                    // ntifs
    );                                          // ntifs
#endif                                          // ntifs

SECURITY_IMPERSONATION_LEVEL
SeTokenImpersonationLevel(
    _In_ PACCESS_TOKEN Token
    );

// begin_ntifs
#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
BOOLEAN
SeTokenIsAdmin(
    _In_ PACCESS_TOKEN Token
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
BOOLEAN
SeTokenIsRestricted(
    _In_ PACCESS_TOKEN Token
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA || (NTDDI_VERSION >= NTDDI_WINXPSP2 && NTDDI_VERSION < NTDDI_WS03))
NTKERNELAPI
BOOLEAN
SeTokenIsWriteRestricted(
    _In_ PACCESS_TOKEN Token
    );
#endif
// end_ntifs

NTKERNELAPI
NTSTATUS
SeGetLinkedToken(
    _In_ TOKEN_ELEVATION_TYPE Type,
    _In_ PACCESS_TOKEN Token,
    _Outptr_ PACCESS_TOKEN *NewToken
    );

NTKERNELAPI
NTSTATUS
SeTokenCanImpersonate(
    _In_ PACCESS_TOKEN ProcessToken,
    _In_ PACCESS_TOKEN Token,
    _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
    _Out_ PBOOLEAN UseProcessTrust
    );
#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
NTSTATUS
SeQueryAuthenticationIdToken(
    _In_ PACCESS_TOKEN Token,
    _Out_ PLUID AuthenticationId
    );
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTKERNELAPI
VOID
SeQueryTokenIntegrity(
    _In_ PACCESS_TOKEN Token,
    _Inout_ PSID_AND_ATTRIBUTES IntegritySA
    );
#endif
#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
NTSTATUS
SeCreateClientSecurity (
    _In_ PETHREAD ClientThread,
    _In_ PSECURITY_QUALITY_OF_SERVICE ClientSecurityQos,
    _In_ BOOLEAN RemoteSession,
    _Out_ PSECURITY_CLIENT_CONTEXT ClientContext
    );
#endif
#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
NTSTATUS
SeImpersonateClientEx(
    _In_ PSECURITY_CLIENT_CONTEXT ClientContext,
    _In_opt_ PETHREAD ServerThread
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
NTSTATUS
SeCreateClientSecurityFromSubjectContext (
    _In_ PSECURITY_SUBJECT_CONTEXT SubjectContext,
    _In_ PSECURITY_QUALITY_OF_SERVICE ClientSecurityQos,
    _In_ BOOLEAN ServerIsRemote,
    _Out_ PSECURITY_CLIENT_CONTEXT ClientContext
    );
#endif

// end_ntifs
NTKERNELAPI
NTSTATUS
SeCreateAccessState(
   _Out_ PACCESS_STATE AccessState,
   _Out_ PAUX_ACCESS_DATA AuxData,
   _In_ ACCESS_MASK DesiredAccess,
   _In_ PGENERIC_MAPPING GenericMapping
   );

NTSTATUS
SeCreateAccessStateEx(
   _In_opt_ PETHREAD Thread,
   _In_ PEPROCESS Process,
   _Out_ PACCESS_STATE AccessState,
   _Out_ PAUX_ACCESS_DATA AuxData,
   _In_ ACCESS_MASK DesiredAccess,
   _In_opt_ PGENERIC_MAPPING GenericMapping
   );

NTKERNELAPI
VOID
SeDeleteAccessState(
    _In_ PACCESS_STATE AccessState
    );

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
NTSTATUS
SeQuerySecurityDescriptorInfo (
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _Out_writes_bytes_(*Length) PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Inout_ PULONG Length,
    _Inout_ PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
NTSTATUS
SeSetSecurityDescriptorInfo (
    _In_opt_ PVOID Object,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR ModificationDescriptor,
    _Inout_ PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
NTSTATUS
SeSetSecurityDescriptorInfoEx (
    _In_opt_ PVOID Object,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR ModificationDescriptor,
    _Inout_ PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
    _In_ ULONG AutoInheritFlags,
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
NTSTATUS
SeAppendPrivileges(
    _Inout_ PACCESS_STATE AccessState,
    _In_ PPRIVILEGE_SET Privileges
    );
#endif


#if (NTDDI_VERSION >= NTDDI_WIN2K)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
BOOLEAN
SeSinglePrivilegeCheck(
    _In_ LUID PrivilegeValue,
    _In_ KPROCESSOR_MODE PreviousMode
    );
#endif


#if (NTDDI_VERSION >= NTDDI_WIN2K)
#define QUERY_TYPE_ULONG(TokenInformationClass) TokenInformationClass == TokenIntegrityLevel        || \
                                                TokenInformationClass == TokenIsAppContainer        || \
                                                TokenInformationClass == TokenVirtualizationAllowed || \
                                                TokenInformationClass == TokenVirtualizationEnabled || \
                                                TokenInformationClass == TokenUIAccess              || \
                                                TokenInformationClass == TokenSessionId             || \
                                                TokenInformationClass == TokenHasRestrictions       || \
                                                TokenInformationClass == TokenAppContainerNumber    || \
                                                TokenInformationClass == TokenPrivateNameSpace

_When_(QUERY_TYPE_ULONG(TokenInformationClass), _At_((PULONG)TokenInformation, _Out_))
_When_(!QUERY_TYPE_ULONG(TokenInformationClass), _At_(TokenInformation, _Outptr_result_buffer_(_Inexpressible_(token-dependent))))
NTKERNELAPI
NTSTATUS
SeQueryInformationToken (
    _In_ PACCESS_TOKEN Token,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
         PVOID *TokenInformation
    );
#endif


NTSTATUS
SeLocateProcessImageName(
    _Inout_ PEPROCESS Process,
    _Outptr_ PUNICODE_STRING *pImageFileName
    );

extern NTKERNELAPI PSE_EXPORTS SeExports;


#if (NTDDI_VERSION >= NTDDI_WIN7)

NTKERNELAPI
VOID
SeExamineGlobalSacl(
    _In_ PUNICODE_STRING ObjectType,
    _In_ PACL ResourceSacl,
    _In_ PACCESS_TOKEN Token,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN AccessGranted,
    _Inout_ PBOOLEAN GenerateAudit,
    _Inout_opt_ PBOOLEAN GenerateAlarm
);

NTKERNELAPI
VOID
SeMaximumAuditMaskFromGlobalSacl(
    _In_opt_ PUNICODE_STRING ObjectTypeName,
    _In_ ACCESS_MASK GrantedAccess,
    _In_ PACCESS_TOKEN Token,
    _Inout_ PACCESS_MASK AuditMask
    );

#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTKERNELAPI
BOOLEAN
FASTCALL
SeAuditingWithTokenForSubcategory(
    _In_ ULONG Subcategory,
    _In_opt_ PACCESS_TOKEN AccessToken
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTKERNELAPI
BOOLEAN
SeSecurityAttributePresent(
    _In_ PACCESS_TOKEN AccessToken,
    _In_ PCUNICODE_STRING Name);

#endif
#if (NTDDI_VERSION >= NTDDI_WIN8)
NTKERNELAPI
NTSTATUS
SeGetLogonSessionToken(
    _In_ HANDLE TokenHandle,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PHANDLE LogonSessionToken
    );
#endif
#if (NTDDI_VERSION >= NTDDI_WIN8)
NTKERNELAPI
NTSTATUS
SeQuerySecureBootPolicyValue(
    _In_ PCUNICODE_STRING ValuePath,
    _In_ PCUNICODE_STRING ValueName,
    _In_ ULONG ValueType,
    _Out_writes_bytes_to_opt_(DataSize, *ResultDataSize) PVOID Data,
    _In_ ULONG DataSize,
    _Out_ PULONG ResultDataSize
    );
#endif
#if (NTDDI_VERSION >= NTDDI_WINBLUE)
NTKERNELAPI
BOOLEAN
SeIsParentOfChildAppContainer(
    _In_ ULONG SessionId,
    _In_ ULONG LowboxNumber1,
    _In_ ULONG LowboxNumber2
    );
#endif

typedef enum _SE_IMAGE_TYPE
{
  SeImageTypeElamDriver = 0,
  SeImageTypeDriver,
  SeImageTypeMax
} SE_IMAGE_TYPE, *PSE_IMAGE_TYPE;

typedef struct _BDCB_IMAGE_INFORMATION *PBDCB_IMAGE_INFORMATION;

typedef
_IRQL_requires_same_
_Function_class_(SE_IMAGE_VERIFICATION_CALLBACK_FUNCTION)
VOID
SE_IMAGE_VERIFICATION_CALLBACK_FUNCTION (
    _In_opt_ PVOID CallbackContext,
    _In_ SE_IMAGE_TYPE ImageType,
    _Inout_ PBDCB_IMAGE_INFORMATION ImageInformation
    );

typedef SE_IMAGE_VERIFICATION_CALLBACK_FUNCTION *PSE_IMAGE_VERIFICATION_CALLBACK_FUNCTION;

typedef enum _SE_IMAGE_VERIFICATION_CALLBACK_TYPE {
    SeImageVerificationCallbackInformational = 0
} SE_IMAGE_VERIFICATION_CALLBACK_TYPE, *PSE_IMAGE_VERIFICATION_CALLBACK_TYPE;

typedef PVOID SE_IMAGE_VERIFICATION_CALLBACK_TOKEN, *PSE_IMAGE_VERIFICATION_CALLBACK_TOKEN;

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
SeRegisterImageVerificationCallback(
    _In_ SE_IMAGE_TYPE ImageType,
    _In_ SE_IMAGE_VERIFICATION_CALLBACK_TYPE CallbackType,
    _In_ PSE_IMAGE_VERIFICATION_CALLBACK_FUNCTION CallbackFunction,
    _In_opt_ PVOID CallbackContext,
    _Reserved_ SE_IMAGE_VERIFICATION_CALLBACK_TOKEN Token,
    _Out_ PVOID* CallbackHandle
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
VOID
SeUnregisterImageVerificationCallback (
    _In_ PVOID CallbackHandle
    );
#endif

#define SE_CODE_INTEGRITY_MAX_EKU_LENGTH 64
#define SE_CODE_INTEGRITY_MAX_EKU_COUNT 3

#define SE_POLICY_PROTECTED_IMAGE 0x1


#define PO_FIXED_WAKE_SOURCE_POWER_BUTTON 0x00000001
#define PO_FIXED_WAKE_SOURCE_SLEEP_BUTTON 0x00000002
#define PO_FIXED_WAKE_SOURCE_RTC          0x00000004
#define PO_FIXED_WAKE_SOURCE_AC_ALARM     0x00000008
#define PO_FIXED_WAKE_SOURCE_DC_ALARM     0x00000010

#define PO_MEM_PRESERVE         0x00000001      // memory range needs preserved
#define PO_MEM_CLONE            0x00000002      // Clone this range
#define PO_MEM_CL_OR_NCHK       0x00000004      // Either clone or do not checksum
#define PO_MEM_DISCARD          0x00008000      // This range to be removed
#define PO_MEM_PAGE_ADDRESS     0x00004000      // Arguments passed are physical pages
#define PO_MEM_BOOT_PHASE       0x00010000


#define PO_CB_SYSTEM_POWER_POLICY       0
#define PO_CB_AC_STATUS                 1
#define PO_CB_BUTTON_COLLISION          2 // deprecated
#define PO_CB_SYSTEM_STATE_LOCK         3
#define PO_CB_LID_SWITCH_STATE          4
#define PO_CB_PROCESSOR_POWER_POLICY    5 // deprecated

#define PO_FX_VERSION_V1 0x00000001
#define PO_FX_VERSION_V2 0x00000002
#define PO_FX_VERSION PO_FX_VERSION_V1

typedef struct _PO_SESSION_INIT {
    BOOLEAN volatile *Sleeping;
    BOOLEAN volatile *HybridShutdown;
    ULONG DisplayTimeout;
    ULONG DisplayDimTimeout;
    ULONG AwayMode;
    ULONG AcDc;
    ULONG NormalBrightnessLevel;
    ULONG DimBrightnessLevel;
    ULONG AlsOffset;
} PO_SESSION_INIT, *PPO_SESSION_INIT;

typedef struct _PO_SESSION_DISPLAY_STATE {
    ULONG SessionId;
    ULONG DisplayState;
    POWER_MONITOR_REQUEST_REASON RequestReason;
    BOOLEAN IsConsole;
    BOOLEAN LogicalTransition;
    BOOLEAN VisibleTransition;
} PO_SESSION_DISPLAY_STATE, *PPO_SESSION_DISPLAY_STATE;


typedef struct _PO_CS_DEVICE_NOTIFICATION {
    PVOID Device;
    PO_CS_DEVICE_NOTIFICATION_TYPE DeviceType;
    BOOLEAN Arriving;
    BOOLEAN Compliant;
} PO_CS_DEVICE_NOTIFICATION, *PPO_CS_DEVICE_NOTIFICATION;

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
#define PEP_FLAG_TEST                   0x80000000
#endif

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
PoCreateThermalRequest (
    _Outptr_ PVOID *ThermalRequest,
    _In_ PDEVICE_OBJECT TargetDeviceObject,
    _In_ PDEVICE_OBJECT PolicyDeviceObject,
    _In_ PCOUNTED_REASON_CONTEXT Context,
    _In_ ULONG Flags
    );
#endif

typedef enum _PO_THERMAL_REQUEST_TYPE {
    PoThermalRequestPassive,
    PoThermalRequestActive,
} PO_THERMAL_REQUEST_TYPE, *PPO_THERMAL_REQUEST_TYPE;

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
BOOLEAN
PoGetThermalRequestSupport (
    _In_ PVOID ThermalRequest,
    _In_ PO_THERMAL_REQUEST_TYPE Type
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
PoSetThermalPassiveCooling (
    _Inout_ PVOID ThermalRequest,
    _In_ UCHAR Throttle
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
PoSetThermalActiveCooling (
    _Inout_ PVOID ThermalRequest,
    _In_ BOOLEAN Engaged
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
PoDeleteThermalRequest (
    _Inout_ PVOID ThermalRequest
    );
#endif

#define PO_THERMAL_REQUEST_SKIP_PROTECTION 0x80000000
#define PO_THERMAL_REQUEST_INVALID_FLAGS   (~0x80000000)

#if !defined(_PSGETCURRENTTHREAD_)

#define _PSGETCURRENTTHREAD_

_IRQL_requires_max_(DISPATCH_LEVEL)
CFORCEINLINE
PETHREAD
PsGetCurrentThread (
    VOID)
{
    return (PETHREAD)KeGetCurrentThread();
}

#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)


#define IMAGE_ADDRESSING_MODE_32BIT     3



#define PS_EXCEPTION_FLAGS_QUERY_WOW64  0x00000001UL

typedef struct _WIN32_PROCESS_CALLOUT_PARAMETERS {
    PEPROCESS Process;
    union {
        ULONG Flags;
        struct {
            ULONG Initialize    : 1;
            ULONG WindowsSigned : 1;
            ULONG Reserved      : 30;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
} WIN32_PROCESS_CALLOUT_PARAMETERS, *PKWIN32_PROCESS_CALLOUT_PARAMETERS;

typedef enum _PSW32JOBCALLOUTTYPE {
    PsW32JobCalloutSetInformation,
    PsW32JobCalloutAddProcess,
    PsW32JobCalloutTerminate
} PSW32JOBCALLOUTTYPE;

typedef struct _WIN32_JOBCALLOUT_PARAMETERS {
    PVOID Job;
    PSW32JOBCALLOUTTYPE CalloutType;
    _In_ PVOID Data;
} WIN32_JOBCALLOUT_PARAMETERS, *PKWIN32_JOBCALLOUT_PARAMETERS;

typedef enum _PSW32THREADCALLOUTTYPE {
    PsW32ThreadCalloutInitialize,
    PsW32ThreadCalloutExit
} PSW32THREADCALLOUTTYPE;

typedef struct _WIN32_THREAD_CALLOUT_PARAMETERS {
    PETHREAD Thread;
    PSW32THREADCALLOUTTYPE CalloutType;
} WIN32_THREAD_CALLOUT_PARAMETERS, *PKWIN32_THREAD_CALLOUT_PARAMETERS;

typedef enum _PSPOWEREVENTTYPE {
    PsW32FullWake,
    PsW32EventCode,
    PsW32SystemPowerState,
    PsW32SystemTime,
    PsW32MonitorOn,
    PsW32MonitorOff,
    PsW32ScreenSaver,
    PsW32MonitorDim,
    PsW32RITActive,
    PsW32RITTimeout,
    PsW32PostMonitorOn,
    PsW32PostMonitorOff,
    PsW32DisplayBurst
} PSPOWEREVENTTYPE, *PPSPOWEREVENTTYPE;

typedef struct _WIN32_POWEREVENT_PARAMETERS {
    PSPOWEREVENTTYPE EventNumber;
    ULONG_PTR Code;
} WIN32_POWEREVENT_PARAMETERS, *PKWIN32_POWEREVENT_PARAMETERS;

typedef enum _POWERSTATETASK {
    PowerState_BlockSessionSwitch,
    PowerState_Init,
    PowerState_SuspendApps,
    PowerState_SuspendServices,
    PowerState_NotifyWL,
    PowerState_ResumeApps,
    PowerState_ResumeServices,
    PowerState_UnBlockSessionSwitch,
    PowerState_End,
    PowerState_Flush,
    PowerState_StartPartitionReplace,
    PowerState_EndPartitionReplace,
    PowerState_MonitorOff
} POWERSTATETASK;

typedef struct _WIN32_POWERSTATE_PARAMETERS {
    BOOLEAN Promotion;
    POWER_ACTION SystemAction;
    SYSTEM_POWER_STATE MinSystemState;
    ULONG Flags;
    POWERSTATETASK PowerStateTask;
    POWER_MONITOR_REQUEST_REASON RequestReason;
} WIN32_POWERSTATE_PARAMETERS, *PKWIN32_POWERSTATE_PARAMETERS;

typedef enum _WIN32_POWERINFO_TYPE {
    PowerInfo_PolicyChange,
    PowerInfo_UserPresent,
    PowerInfo_DisplayRequired,
    PowerInfo_Monitor,
    PowerInfo_Input,
    PowerInfo_Max
} WIN32_POWERINFO_TYPE, *PWIN32_POWERINFO_TYPE;

typedef enum _WIN32K_INPUT_MODE {
    PowerInputEnabled,
    PowerInputSuppressed,
    PowerInputFiltered,
} WIN32K_INPUT_MODE, *PWIN32K_INPUT_MODE;

// {6F5E16B8-8575-4014-B209-215FD159D7CD}
DEFINE_GUID(GUID_CONSOLE_VIDEO_TIMEOUT, 0x6f5e16b8, 0x8575, 0x4014, 0xb2, 0x9, 0x21, 0x5f, 0xd1, 0x59, 0xd7, 0xcd);

// {8592A7F6-022C-4f42-8C81-D7745F8CA920}
DEFINE_GUID(GUID_TS_INPUT_TIMEOUT, 0x8592a7f6, 0x22c, 0x4f42, 0x8c, 0x81, 0xd7, 0x74, 0x5f, 0x8c, 0xa9, 0x20);

// {34A64C3B-8317-4171-ABD8-A3B1EE3E4331}
DEFINE_GUID(GUID_CONSOLE_INPUT_TIMEOUT, 0x34a64c3b, 0x8317, 0x4171, 0xab, 0xd8, 0xa3, 0xb1, 0xee, 0x3e, 0x43, 0x31);

typedef struct _WIN32_POWERINFO_POLICYCHANGE {
    GUID Guid;
    ULONG Value;
} WIN32_POWERINFO_POLICYCHANGE, *PKWIN32_POWERINFO_POLICYCHANGE;

typedef struct _WIN32_POWERINFO_DISPLAYREQUIRED {
    BOOLEAN Set;
} WIN32_POWERINFO_DISPLAYREQUIRED, *PKWIN32_POWERINFO_DISPLAYREQUIRED;

typedef struct _WIN32_POWERINFO_USERPRESENT {
    BOOLEAN Virtual;
    BOOLEAN UpdateLastInputOnly;
    POWER_MONITOR_REQUEST_REASON RequestReason;
} WIN32_POWERINFO_USERPRESENT, *PKWIN32_POWERINFO_USERPRESENT;

typedef struct _WIN32_POWERINFO_MONITOR {
    BOOLEAN On;
    BOOLEAN AssertPresence;
    POWER_MONITOR_REQUEST_REASON RequestReason;
} WIN32_POWERINFO_MONITOR, *PKWIN32_POWERINFO_MONITOR;

typedef struct _WIN32_POWERINFO_CALLOUT_PARAMETERS {
    WIN32_POWERINFO_TYPE Type;
    BOOLEAN Synchronous;
    ULONG InputSize;
    PVOID InputBuffer;
    ULONG OutputSize;
    PVOID OutputBuffer;
} WIN32_POWERINFO_CALLOUT_PARAMETERS, *PKWIN32_POWERINFO_CALLOUT_PARAMETERS;

typedef struct _WIN32_JOBINTERFERENCEINFO_CALLOUT_PARAMETERS {
    PEPROCESS Process;
    ULONG* InterferenceCount;               // How many times the process interfered with rendering since process start.
} WIN32_JOBINTERFERENCEINFO_CALLOUT_PARAMETERS, *PWIN32_JOBINTERFERENCEINFO_CALLOUT_PARAMETERS;

typedef struct _WIN32_SUBSYSTEM_PROCESS_QUERY_CALLOUT_PARAMETERS {
    PEPROCESS SubsystemProcess;             // Caller must dereference
} WIN32_SUBSYSTEM_PROCESS_QUERY_CALLOUT_PARAMETERS, *PWIN32_SUBSYSTEM_PROCESS_QUERY_CALLOUT_PARAMETERS;

C_ASSERT(sizeof(WIN32_SUBSYSTEM_PROCESS_QUERY_CALLOUT_PARAMETERS) == sizeof(PVOID));

typedef enum _WIN32_CALLOUTS_OPERATION {
    Win32ProcessCallout = 0,
    Win32ThreadCallout,
    Win32GlobalAtomTableCallout,
    Win32PowerEventCallout,
    Win32PowerStateCallout,
    Win32PowerInfoCallout,
    Win32JobCallout,
    Win32BatchFlushCallout,
    Win32DesktopOpenCallout,
    Win32DesktopOkToCloseCallout,
    Win32DesktopCloseCallout,
    Win32DesktopDeleteCallout,
    Win32WindowStationOkToCloseCallout,
    Win32WindowStationCloseCallout,
    Win32WindowStationDeleteCallout,
    Win32WindowStationParseCallout,
    Win32WindowStationOpenCallout,
    Win32LicensingCallout,
    Win32CompositionObjectOpenCallout,
    Win32CompositionObjectOkToCloseCallout,
    Win32CompositionObjectCloseCallout,
    Win32CompositionObjectDeleteCallout,
    Win32ProcessFreezeCallout,
    Win32ProcessThawCallout,
    Win32JobGetInterferenceCountsCallout,
    Win32GetGpuStatisticsCallout,
    Win32SubsystemProcessQueryCallout,

    Win32RawInputManagerObjectOpenCallout,
    Win32RawInputManagerObjectOkToCloseCallout,
    Win32RawInputManagerObjectCloseCallout,
    Win32RawInputManagerObjectDeleteCallout,

    Win32CalloutsMax
} WIN32_CALLOUTS_OPERATION, *PKWIN32_CALLOUTS_OPERATION;

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
CCHAR
PsGetCurrentThreadPreviousMode(
    VOID
    );

#define PsGetCurrentProcessImageFileName() PsGetProcessImageFileName(PsGetCurrentProcess())

#define PsGetProcessPcb(Process) ((PKPROCESS)(Process))

#define PsGetCurrentProcessWin32WindowStation() PsGetProcessWin32WindowStation(PsGetCurrentProcess())


#define  PsGetThreadTcb(Thread) ((PKTHREAD)(Thread))




#define PS_WAKE_COUNTER_CONDITIONAL_CHARGE  0x00000001UL
#define PS_WAKE_COUNTER_NO_WAKE_CHARGE      0x00000002UL
#define PS_WAKE_COUNTER_BREAK_IF_SUSPENDED  0x80000000UL



typedef
NTSTATUS
NTAPI
PS_SET_CONTEXT_THREAD_INTERNAL (
    __in PETHREAD Thread,
    __in PCONTEXT ThreadContext,
    __in KPROCESSOR_MODE ProbeMode,
    __in KPROCESSOR_MODE CtxMode,
    __in BOOLEAN PerformUnwind);
typedef PS_SET_CONTEXT_THREAD_INTERNAL *PPS_SET_CONTEXT_THREAD_INTERNAL;

typedef
NTSTATUS
NTAPI
PS_GET_CONTEXT_THREAD_INTERNAL (
    __in PETHREAD Thread,
    __inout PCONTEXT ThreadContext,
    __in KPROCESSOR_MODE ProbeMode,
    __in KPROCESSOR_MODE CtxMode,
    __in BOOLEAN PerformUnwind);
typedef PS_GET_CONTEXT_THREAD_INTERNAL *PPS_GET_CONTEXT_THREAD_INTERNAL;

typedef
NTSTATUS
NTAPI
PS_TERMINATE_THREAD (
    __inout PETHREAD Thread,
    __in NTSTATUS ExitStatus,
    __in BOOLEAN DirectTerminate);
typedef PS_TERMINATE_THREAD *PPS_TERMINATE_THREAD;

#define PS_PICO_CREATE_PROCESS_CLONE_PARENT             0x1
#define PS_PICO_CREATE_PROCESS_INHERIT_HANDLES          0x2
#define PS_PICO_CREATE_PROCESS_CLONE_REDUCED_COMMIT     0x4
#define PS_PICO_CREATE_PROCESS_INHERIT_PROTECTION       0x8

#define PS_PICO_CREATE_PROCESS_FLAGS_MASK ( \
    PS_PICO_CREATE_PROCESS_CLONE_PARENT | \
    PS_PICO_CREATE_PROCESS_INHERIT_HANDLES | \
    PS_PICO_CREATE_PROCESS_CLONE_REDUCED_COMMIT | \
    PS_PICO_CREATE_PROCESS_INHERIT_PROTECTION)

typedef struct _PS_PICO_PROCESS_ATTRIBUTES
{
    HANDLE ParentProcess;
    PVOID Context;
    ULONG Flags;
} PS_PICO_PROCESS_ATTRIBUTES, *PPS_PICO_PROCESS_ATTRIBUTES;

typedef struct _PS_PICO_THREAD_ATTRIBUTES {
    HANDLE Process;
    ULONG_PTR UserStack;
    ULONG_PTR StartRoutine;
    ULONG_PTR StartParameter1;
    ULONG_PTR StartParameter2;
#if defined(_AMD64_)
    ULONG UserFsBase;
    ULONG64 UserGsBase;
#elif defined(_X86_)
    ULONG UserFsBase;
    ULONG UserGsBase;
    USHORT UserFsSeg;
    USHORT UserGsSeg;
    ULONG_PTR Eax;
    ULONG_PTR Ebx;
    ULONG_PTR Ecx;
    ULONG_PTR Edx;
    ULONG_PTR Edi;
    ULONG_PTR Esi;
    ULONG_PTR Ebp;
#elif defined(_ARM_)
    ULONG UserRoBase;
    ULONG UserRwBase;
    ULONG Lr;
    ULONG R2;
    ULONG R3;
    ULONG R4;
    ULONG R5;
    ULONG R6;
    ULONG R7;
    ULONG R8;
    ULONG R9;
    ULONG R10;
    ULONG R11;
    ULONG R12;
#endif
    PVOID Context;
} PS_PICO_THREAD_ATTRIBUTES, *PPS_PICO_THREAD_ATTRIBUTES;

typedef
NTSTATUS
NTAPI
PS_PICO_CREATE_PROCESS (
    _In_ PPS_PICO_PROCESS_ATTRIBUTES ProcessAttributes,
    _Outptr_ PHANDLE ProcessHandle);
typedef PS_PICO_CREATE_PROCESS *PPS_PICO_CREATE_PROCESS;

typedef
NTSTATUS
NTAPI
PS_PICO_CREATE_THREAD (
    _In_ PPS_PICO_THREAD_ATTRIBUTES ThreadAttributes,
    _Outptr_ PHANDLE ThreadHandle);
typedef PS_PICO_CREATE_THREAD *PPS_PICO_CREATE_THREAD;

typedef
PVOID
NTAPI
PS_PICO_GET_PROCESS_CONTEXT (
    _In_ PEPROCESS Process);
typedef PS_PICO_GET_PROCESS_CONTEXT *PPS_PICO_GET_PROCESS_CONTEXT;

typedef
PVOID
NTAPI
PS_PICO_GET_THREAD_CONTEXT (
    _In_ PETHREAD Thread);
typedef PS_PICO_GET_THREAD_CONTEXT *PPS_PICO_GET_THREAD_CONTEXT;

typedef enum _PS_PICO_THREAD_DESCRIPTOR_TYPE
{
#if defined(_X86_) || defined(_AMD64_)
    PicoThreadDescriptorTypeFs,
    PicoThreadDescriptorTypeGs,
#elif defined(_ARM_)
    PicoThreadDescriptorTypeUserRo,
    PicoThreadDescriptorTypeUserRw,
#endif
    PicoThreadDescriptorTypeMax
} PS_PICO_THREAD_DESCRIPTOR_TYPE, *PPS_PICO_THREAD_DESCRIPTOR_TYPE;

typedef
VOID
NTAPI
PS_PICO_SET_THREAD_DESCRIPTOR_BASE (
    _In_ PS_PICO_THREAD_DESCRIPTOR_TYPE Type,
    _In_ ULONG_PTR Base);
typedef PS_PICO_SET_THREAD_DESCRIPTOR_BASE *PPS_PICO_SET_THREAD_DESCRIPTOR_BASE;

typedef struct _PS_PICO_ROUTINES
{
    PPS_PICO_CREATE_PROCESS CreateProcess;
    PPS_PICO_CREATE_THREAD CreateThread;
    PPS_PICO_GET_PROCESS_CONTEXT GetProcessContext;
    PPS_PICO_GET_THREAD_CONTEXT GetThreadContext;
    PPS_GET_CONTEXT_THREAD_INTERNAL GetContextThreadInternal;
    PPS_SET_CONTEXT_THREAD_INTERNAL SetContextThreadInternal;
    PPS_TERMINATE_THREAD TerminateThread;
    PPS_RESUME_THREAD ResumeThread;
    PPS_PICO_SET_THREAD_DESCRIPTOR_BASE SetThreadDescriptorBase;
    PPS_SUSPEND_THREAD SuspendThread;
} PS_PICO_ROUTINES, *PPS_PICO_ROUTINES;

typedef struct _PS_PICO_SYSTEM_CALL_INFORMATION
{
    PKTRAP_FRAME TrapFrame;
#if defined(_ARM_)
    ULONG R4;
    ULONG R5;
    ULONG R7;
#endif
} PS_PICO_SYSTEM_CALL_INFORMATION, *PPS_PICO_SYSTEM_CALL_INFORMATION;

typedef
VOID
NTAPI
PS_PICO_PROVIDER_SYSTEM_CALL_DISPATCH (
    _In_ PPS_PICO_SYSTEM_CALL_INFORMATION SystemCall);
typedef PS_PICO_PROVIDER_SYSTEM_CALL_DISPATCH *PPS_PICO_PROVIDER_SYSTEM_CALL_DISPATCH;

typedef
VOID
NTAPI
PS_PICO_PROVIDER_THREAD_EXIT (
    _In_ PETHREAD Thread);
typedef PS_PICO_PROVIDER_THREAD_EXIT *PPS_PICO_PROVIDER_THREAD_EXIT;

typedef
VOID
NTAPI
PS_PICO_PROVIDER_PROCESS_EXIT (
    _In_ PEPROCESS Process);
typedef PS_PICO_PROVIDER_PROCESS_EXIT *PPS_PICO_PROVIDER_PROCESS_EXIT;

typedef
BOOLEAN
NTAPI
PS_PICO_PROVIDER_DISPATCH_EXCEPTION (
    _Inout_ PEXCEPTION_RECORD ExceptionRecord,
    _Inout_ PKEXCEPTION_FRAME ExceptionFrame,
    _Inout_ PKTRAP_FRAME TrapFrame,
    _In_ ULONG Chance,
    _In_ KPROCESSOR_MODE PreviousMode);
typedef PS_PICO_PROVIDER_DISPATCH_EXCEPTION *PPS_PICO_PROVIDER_DISPATCH_EXCEPTION;

typedef struct _PS_PICO_PROVIDER_ROUTINES
{
    PPS_PICO_PROVIDER_SYSTEM_CALL_DISPATCH DispatchSystemCall;
    PPS_PICO_PROVIDER_THREAD_EXIT ExitThread;
    PPS_PICO_PROVIDER_PROCESS_EXIT ExitProcess;
    PPS_PICO_PROVIDER_DISPATCH_EXCEPTION DispatchException;
} PS_PICO_PROVIDER_ROUTINES, *PPS_PICO_PROVIDER_ROUTINES;

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
NTAPI
PsRegisterPicoProvider (
    _In_ PPS_PICO_PROVIDER_ROUTINES ProviderRoutines,
    _Out_ PPS_PICO_ROUTINES PicoRoutines);

#define CONTAINER_INFO_FLAG_CHARGE_ONLY 1

typedef struct _OBJECT_DUMP_CONTROL
{
    PVOID Stream;
    ULONG Detail;
} OB_DUMP_CONTROL, *POB_DUMP_CONTROL;

typedef VOID (*OB_DUMP_METHOD) (
    _In_ PVOID Object,
    _In_opt_ POB_DUMP_CONTROL Control
    );

typedef enum _OB_OPEN_REASON {
    ObCreateHandle,
    ObOpenHandle,
    ObDuplicateHandle,
    ObInheritHandle,
    ObMaxOpenReason
} OB_OPEN_REASON;

typedef NTSTATUS (*OB_OPEN_METHOD)(
    _In_ OB_OPEN_REASON OpenReason,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _Inout_ PACCESS_MASK GrantedAccess,
    _In_ ULONG HandleCount
    );

typedef BOOLEAN (*OB_OKAYTOCLOSE_METHOD)(
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ HANDLE Handle,
    _In_ KPROCESSOR_MODE PreviousMode
    );

typedef VOID (*OB_CLOSE_METHOD)(
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ ULONG_PTR ProcessHandleCount,
    _In_ ULONG_PTR SystemHandleCount
    );

typedef VOID (*OB_DELETE_METHOD)(
    _In_  PVOID   Object
    );

typedef NTSTATUS (*OB_PARSE_METHOD)(
    _In_ PVOID ParseObject,
    _In_ PVOID ObjectType,
    _Inout_ PACCESS_STATE AccessState,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Attributes,
    _Inout_ PUNICODE_STRING CompleteName,
    _Inout_ PUNICODE_STRING RemainingName,
    _Inout_opt_ PVOID Context,
    _In_opt_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    _Out_ PVOID *Object
    );

typedef NTSTATUS (*OB_SECURITY_METHOD)(
    _In_ PVOID Object,
    _In_ SECURITY_OPERATION_CODE OperationCode,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Inout_ PULONG CapturedLength,
    _Inout_ PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE Mode
    );

typedef NTSTATUS (*OB_QUERYNAME_METHOD)(
    _In_ PVOID Object,
    _In_ BOOLEAN HasObjectName,
    _Out_writes_bytes_opt_(Length) POBJECT_NAME_INFORMATION ObjectNameInfo,
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength,
    _In_ KPROCESSOR_MODE Mode
    );

typedef struct _WIN32_OPENMETHOD_PARAMETERS {
   OB_OPEN_REASON OpenReason;
   PEPROCESS Process;
   PVOID Object;
   ACCESS_MASK GrantedAccess;
   ULONG HandleCount;
} WIN32_OPENMETHOD_PARAMETERS, *PKWIN32_OPENMETHOD_PARAMETERS;

typedef struct _WIN32_OKAYTOCLOSEMETHOD_PARAMETERS {
   PEPROCESS Process;
   PVOID Object;
   HANDLE Handle;
   KPROCESSOR_MODE PreviousMode;
} WIN32_OKAYTOCLOSEMETHOD_PARAMETERS, *PKWIN32_OKAYTOCLOSEMETHOD_PARAMETERS;

typedef struct _WIN32_CLOSEMETHOD_PARAMETERS {
   PEPROCESS Process;
   PVOID Object;
   ULONG ProcessHandleCount;
   ULONG SystemHandleCount;
} WIN32_CLOSEMETHOD_PARAMETERS, *PKWIN32_CLOSEMETHOD_PARAMETERS;

typedef struct _WIN32_DELETEMETHOD_PARAMETERS {
   PVOID Object;
} WIN32_DELETEMETHOD_PARAMETERS, *PKWIN32_DELETEMETHOD_PARAMETERS;

typedef struct _WIN32_PARSEMETHOD_PARAMETERS {
   PVOID ParseObject;
   PVOID ObjectType;
   PACCESS_STATE AccessState;
   KPROCESSOR_MODE AccessMode;
   ULONG Attributes;
   PUNICODE_STRING CompleteName;
   PUNICODE_STRING RemainingName;
   PVOID Context;
   PSECURITY_QUALITY_OF_SERVICE SecurityQos;
   PVOID *Object;
} WIN32_PARSEMETHOD_PARAMETERS, *PKWIN32_PARSEMETHOD_PARAMETERS;

#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4201)   // nameless struct/union
#pragma warning(disable:4214)   // bit field types other than int
#endif

typedef struct _OBJECT_TYPE_INITIALIZER {
    USHORT Length;
    union {
        UCHAR ObjectTypeFlags;
        struct {
            UCHAR CaseInsensitive : 1;
            UCHAR UnnamedObjectsOnly : 1;
            UCHAR UseDefaultObject : 1;
            UCHAR SecurityRequired : 1;
            UCHAR MaintainHandleCount : 1;
            UCHAR MaintainTypeList : 1;
            UCHAR SupportsObjectCallbacks : 1;
            UCHAR CacheAligned : 1;
        };
    };

    ULONG ObjectTypeCode;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccessMask;
    ULONG RetainAccess;
    POOL_TYPE PoolType;
    ULONG DefaultPagedPoolCharge;
    ULONG DefaultNonPagedPoolCharge;
    OB_DUMP_METHOD DumpProcedure;
    OB_OPEN_METHOD OpenProcedure;
    OB_CLOSE_METHOD CloseProcedure;
    OB_DELETE_METHOD DeleteProcedure;
    OB_PARSE_METHOD ParseProcedure;
    OB_SECURITY_METHOD SecurityProcedure;
    OB_QUERYNAME_METHOD QueryNameProcedure;
    OB_OKAYTOCLOSE_METHOD OkayToCloseProcedure;
    ULONG WaitObjectFlagMask;
    USHORT WaitObjectFlagOffset;
    USHORT WaitObjectPointerOffset;
} OBJECT_TYPE_INITIALIZER, *POBJECT_TYPE_INITIALIZER;

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

typedef struct _OBJECT_TYPE {
    LIST_ENTRY TypeList;
    UNICODE_STRING Name;            // Copy from object header for convenience
    PVOID DefaultObject;
    UCHAR Index;
    __volatile ULONG TotalNumberOfObjects;
    __volatile ULONG TotalNumberOfHandles;
    ULONG HighWaterNumberOfObjects;
    ULONG HighWaterNumberOfHandles;
    OBJECT_TYPE_INITIALIZER TypeInfo;
    EX_PUSH_LOCK TypeLock;
    ULONG Key;
    LIST_ENTRY CallbackList;
} OBJECT_TYPE, *POBJECT_TYPE;

#define OB_TYPEINIT_FLAG_SUPPORTS_CALLBACKS     0x40

#define NUMBER_HASH_BUCKETS         37
#define OBJ_INVALID_SESSION_ID      0xFFFFFFFF

#define OBP_DIRECTORY_NAMESPACE     0x00000001
#define OBP_NAMESPACE_DELETED       0x00000002
#define OBP_SEARCH_SHADOW           0x00000004
#define OBP_INHERIT_SECURITY        0x00000008

typedef struct _OBJECT_DIRECTORY {

    struct _OBJECT_DIRECTORY_ENTRY *HashBuckets[ NUMBER_HASH_BUCKETS ];
    EX_PUSH_LOCK Lock;
    union {
        struct _DEVICE_MAP *DeviceMap;
        struct _OBJECT_DIRECTORY* ShadowDirectory;
    };
    ULONG SessionId;
    PVOID NamespaceEntry;
    ULONG Flags;

} OBJECT_DIRECTORY, *POBJECT_DIRECTORY;

typedef struct _OBJECT_CREATE_INFORMATION *POBJECT_CREATE_INFORMATION;

typedef struct _OBJECT_HEADER {
    __volatile LONG_PTR PointerCount;
    union {
        __volatile LONG_PTR HandleCount;
        PVOID NextToFree;
    };

    EX_PUSH_LOCK Lock;
    UCHAR TypeIndex;

#define OB_OBJECT_REF_TRACE                 0x1
#define OB_OBJECT_TRACE_PERMANENT           0x2
    union {
        UCHAR TraceFlags;
        struct {
            UCHAR DbgRefTrace       : 1;
            UCHAR DbgTracePermanent : 1;
        };
    };

    UCHAR InfoMask;

#define OB_FLAG_NEW_OBJECT              0x01
#define OB_FLAG_KERNEL_OBJECT           0x02
#define OB_FLAG_KERNEL_ONLY_ACCESS      0x04
#define OB_FLAG_EXCLUSIVE_OBJECT        0x08
#define OB_FLAG_PERMANENT_OBJECT        0x10
#define OB_FLAG_DEFAULT_SECURITY_QUOTA  0x20
#define OB_FLAG_SINGLE_HANDLE_ENTRY     0x40
#define OB_FLAG_DELETED_INLINE          0x80

    union {
        UCHAR Flags;
        struct {
            UCHAR NewObject : 1;
            UCHAR KernelObject : 1;
            UCHAR KernelOnlyAccess : 1;
            UCHAR ExclusiveObject : 1;
            UCHAR PermanentObject : 1;
            UCHAR DefaultSecurityQuota : 1;
            UCHAR SingleHandleEntry : 1;
            UCHAR DeletedInline : 1;
        };
    };

#if defined(_WIN64)
    ULONG Spare;
#endif

    union {
        POBJECT_CREATE_INFORMATION ObjectCreateInfo;
        PVOID QuotaBlockCharged;
    };

    PSECURITY_DESCRIPTOR SecurityDescriptor;
    QUAD Body;
} OBJECT_HEADER, *POBJECT_HEADER;

typedef struct _OBJECT_HEADER_NAME_INFO {
    POBJECT_DIRECTORY Directory;
    UNICODE_STRING Name;
    LONG ReferenceCount;
} OBJECT_HEADER_NAME_INFO, *POBJECT_HEADER_NAME_INFO;

POBJECT_HEADER_NAME_INFO
ObQueryNameInfo (
    _In_ PVOID Object
    );

NTSTATUS
ObQueryNameStringMode(
    _In_ PVOID Object,
    _Out_writes_bytes_opt_(Length)POBJECT_NAME_INFORMATION ObjectNameInfo,
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength,
    _In_ KPROCESSOR_MODE Mode
      );

POBJECT_TYPE
ObGetObjectType (
    _In_ PVOID Object
    );
#define OBJECT_TO_OBJECT_HEADER( o ) \
    CONTAINING_RECORD( (o), OBJECT_HEADER, Body )

NTKERNELAPI
NTSTATUS
ObCreateObjectType(
    _In_ PUNICODE_STRING TypeName,
    _In_ POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Outptr_ POBJECT_TYPE *ObjectType
    );

NTKERNELAPI
NTSTATUS
ObCreateObjectTypeEx(
    _In_ PUNICODE_STRING TypeName,
    _In_ POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ LONG_PTR WaitObjectInfo,
    _Outptr_ POBJECT_TYPE *ObjectType
    );

#define OBJ_PROTECT_CLOSE       0x00000001L

NTKERNELAPI
NTSTATUS
ObReferenceFileObjectForWrite(
    _In_ HANDLE Handle,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PVOID *FileObject,
    _Out_ POBJECT_HANDLE_INFORMATION HandleInformation
    );

NTKERNELAPI
NTSTATUS
ObOpenObjectByName(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Inout_opt_ PACCESS_STATE AccessState,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _Inout_opt_ PVOID ParseContext,
    _Out_ PHANDLE Handle
    );

NTKERNELAPI
NTSTATUS
ObReferenceObjectByName(
    _In_ PUNICODE_STRING ObjectName,
    _In_ ULONG Attributes,
    _In_opt_ PACCESS_STATE AccessState,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Inout_opt_ PVOID ParseContext,
    _Out_ PVOID *Object
    );

NTKERNELAPI
BOOLEAN
ObFindHandleForObject(
    _In_ PEPROCESS Process,
    _In_opt_ PVOID Object,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_opt_ POBJECT_HANDLE_INFORMATION MatchCriteria,
    _Out_ PHANDLE Handle
    );

NTKERNELAPI
NTSTATUS
ObLogSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR InputSecurityDescriptor,
    _Out_ PSECURITY_DESCRIPTOR *OutputSecurityDescriptor,
    _In_ ULONG RefBias
    );

NTKERNELAPI
VOID
ObDereferenceSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Count
    );

NTKERNELAPI
VOID
ObReferenceSecurityDescriptor (
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Count
    );

NTKERNELAPI
BOOLEAN
ObCheckCreateObjectAccess(
    _In_ PVOID DirectoryObject,
    _In_ ACCESS_MASK CreateAccess,
    _In_ PACCESS_STATE AccessState,
    _In_ PUNICODE_STRING ComponentName,
    _In_ BOOLEAN TypeMutexLocked,
    _In_ KPROCESSOR_MODE PreviousMode,
    _Out_ PNTSTATUS AccessStatus
   );

NTKERNELAPI
BOOLEAN
ObCheckObjectAccess(
    _In_ PVOID Object,
    _Inout_ PACCESS_STATE AccessState,
    _In_ BOOLEAN TypeMutexLocked,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PNTSTATUS AccessStatus
    );

NTKERNELAPI
NTSTATUS
ObAssignSecurity(
    _In_ PACCESS_STATE AccessState,
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_ PVOID Object,
    _In_ POBJECT_TYPE ObjectType
    );

NTKERNELAPI
NTSTATUS
ObSetSecurityObjectByPointer (
    _In_ PVOID Object,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
    );

NTKERNELAPI
NTSTATUS
ObSetHandleAttributes (
    _In_ HANDLE Handle,
    _In_ POBJECT_HANDLE_FLAG_INFORMATION HandleFlags,
    _In_ KPROCESSOR_MODE PreviousMode
    );

NTKERNELAPI
NTSTATUS
ObSetSecurityDescriptorInfo(
    _In_ PVOID Object,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Inout_ PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping
    );

typedef struct _OBJECT_HANDLE_INFORMATION {
    ULONG HandleAttributes;
    ACCESS_MASK GrantedAccess;
} OBJECT_HANDLE_INFORMATION, *POBJECT_HANDLE_INFORMATION;

NTKERNELAPI
VOID
ObDeleteCapturedInsertInfo(
    _In_ PVOID Object
    );

NTKERNELAPI
NTSTATUS
ObCreateObject(
    _In_ KPROCESSOR_MODE ProbeMode,
    _In_ POBJECT_TYPE ObjectType,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ KPROCESSOR_MODE OwnershipMode,
    _Inout_opt_ PVOID ParseContext,
    _In_ ULONG ObjectBodySize,
    _In_ ULONG PagedPoolCharge,
    _In_ ULONG NonPagedPoolCharge,
    _Outptr_ PVOID *Object
    );

NTKERNELAPI
NTSTATUS
ObInsertObject(
    _In_ PVOID Object,
    _Inout_opt_ PACCESS_STATE PassedAccessState,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _In_ ULONG ObjectPointerBias,
    _Out_opt_ PVOID *NewObject,
    _Out_opt_ PHANDLE Handle
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
ObReferenceObjectByHandle(
    _In_ HANDLE Handle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PVOID *Object,
    _Out_opt_ POBJECT_HANDLE_INFORMATION HandleInformation
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
NTSTATUS
ObReferenceObjectByHandleWithTag(
    _In_ HANDLE Handle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Tag,
    _Out_ PVOID *Object,
    _Out_opt_ POBJECT_HANDLE_INFORMATION HandleInformation
    );

NTKERNELAPI
BOOLEAN
FASTCALL
ObReferenceObjectSafe (
    _In_ PVOID Object
    );

NTKERNELAPI
BOOLEAN
FASTCALL
ObReferenceObjectSafeWithTag (
    _In_ PVOID Object,
    _In_ ULONG Tag
    );

NTKERNELAPI
NTSTATUS
ObCloseHandle (
    _In_ HANDLE Handle,
    _In_ KPROCESSOR_MODE PreviousMode
    );

CFORCEINLINE
NTSTATUS
_ObReferenceObjectByHandle(
    _In_ HANDLE Handle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PVOID *pObject,
    _Out_opt_ POBJECT_HANDLE_INFORMATION pHandleInformation
    )
{
    PVOID Object;
    NTSTATUS Status;

    Status = ObReferenceObjectByHandle (Handle,
                                        DesiredAccess,
                                        ObjectType,
                                        AccessMode,
                                        &Object,
                                        pHandleInformation);

    *pObject = Object;
    return Status;
}

#define ObReferenceObjectByHandle _ObReferenceObjectByHandle

NTKERNELAPI
NTSTATUS
ObOpenObjectByPointer(
    _In_ PVOID Object,
    _In_ ULONG HandleAttributes,
    _In_opt_ PACCESS_STATE PassedAccessState,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PHANDLE Handle
    );

NTKERNELAPI
NTSTATUS
ObOpenObjectByPointerWithTag(
    _In_ PVOID Object,
    _In_ ULONG HandleAttributes,
    _In_opt_ PACCESS_STATE PassedAccessState,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Tag,
    _Out_ PHANDLE Handle
    );

NTKERNELAPI
VOID
ObMakeTemporaryObject(
    _In_ PVOID Object
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
#define ObDereferenceObject(a) ObfDereferenceObject(a)
#define ObReferenceObject(Object) ObfReferenceObject(Object)
#define ObDereferenceObjectWithTag(a, t) ObfDereferenceObjectWithTag(a, t)
#define ObReferenceObjectWithTag(Object, Tag) ObfReferenceObjectWithTag(Object, Tag)
#else
#define ObDereferenceObject(a) ObfDereferenceObject(a)
#define ObReferenceObject(Object) ObfReferenceObject(Object)
#endif

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
LONG_PTR
FASTCALL
ObfReferenceObject(
    _In_ PVOID Object
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
LONG_PTR
FASTCALL
ObfReferenceObjectWithTag(
    _In_ PVOID Object,
    _In_ ULONG Tag
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
NTSTATUS
ObReferenceObjectByPointer(
    _In_ PVOID Object,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
NTSTATUS
ObReferenceObjectByPointerWithTag(
    _In_ PVOID Object,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Tag
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
LONG_PTR
FASTCALL
ObfDereferenceObject(
    _In_ PVOID Object
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
LONG_PTR
FASTCALL
ObfDereferenceObjectWithTag(
    _In_ PVOID Object,
    _In_ ULONG Tag
    );

NTKERNELAPI
VOID
ObDereferenceObjectDeferDelete(
    _In_ PVOID Object
    );

NTKERNELAPI
VOID
ObDereferenceObjectDeferDeleteWithTag(
    _In_ PVOID Object,
    _In_ ULONG Tag
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
ObWaitForSingleObject(
    _In_ HANDLE Handle,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
ObWaitForMultipleObjects (
    _In_range_(<=, MAXIMUM_WAIT_OBJECTS) ULONG Count,
    _In_reads_(Count) HANDLE CapturedHandles[],
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ WAIT_TYPE WaitType,
    _In_ KPROCESSOR_MODE WaitMode,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
    );

NTKERNELAPI
NTSTATUS
ObQueryNameString(
    _In_ PVOID Object,
    _Out_writes_bytes_opt_(Length) POBJECT_NAME_INFORMATION ObjectNameInfo,
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength
    );

NTKERNELAPI
BOOLEAN
ObIsKernelHandle (
    _In_ HANDLE Handle
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
NTSTATUS
ObGetObjectSecurity(
    _In_ PVOID Object,
    _Out_ PSECURITY_DESCRIPTOR *SecurityDescriptor,
    _Out_ PBOOLEAN MemoryAllocated
    );

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
VOID
ObReleaseObjectSecurity(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ BOOLEAN MemoryAllocated
    );

NTKERNELAPI
NTSTATUS
ObIsDosDeviceLocallyMapped(
    _In_ ULONG DriveIndex,
    _Out_ PBOOLEAN LocallyMapped
    );

NTSTATUS
ObDuplicateObject (
    _In_ PEPROCESS SourceProcess,
    _In_ HANDLE SourceHandle,
    _In_opt_ PEPROCESS TargetProcess,
    _Out_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options,
    _In_ KPROCESSOR_MODE PreviousMode
    );
#endif

#define OB_FLT_REGISTRATION_VERSION_0100  0x0100
#define OB_FLT_REGISTRATION_VERSION OB_FLT_REGISTRATION_VERSION_0100

typedef ULONG OB_OPERATION;

#define OB_OPERATION_HANDLE_CREATE              0x00000001
#define OB_OPERATION_HANDLE_DUPLICATE           0x00000002

typedef struct _OB_PRE_CREATE_HANDLE_INFORMATION {
    _Inout_ ACCESS_MASK         DesiredAccess;
    _In_ ACCESS_MASK            OriginalDesiredAccess;
} OB_PRE_CREATE_HANDLE_INFORMATION, *POB_PRE_CREATE_HANDLE_INFORMATION;

typedef struct _OB_PRE_DUPLICATE_HANDLE_INFORMATION {
    _Inout_ ACCESS_MASK         DesiredAccess;
    _In_ ACCESS_MASK            OriginalDesiredAccess;
    _In_ PVOID                  SourceProcess;
    _In_ PVOID                  TargetProcess;
} OB_PRE_DUPLICATE_HANDLE_INFORMATION, * POB_PRE_DUPLICATE_HANDLE_INFORMATION;

typedef union _OB_PRE_OPERATION_PARAMETERS {
    _Inout_ OB_PRE_CREATE_HANDLE_INFORMATION        CreateHandleInformation;
    _Inout_ OB_PRE_DUPLICATE_HANDLE_INFORMATION     DuplicateHandleInformation;
} OB_PRE_OPERATION_PARAMETERS, *POB_PRE_OPERATION_PARAMETERS;

typedef struct _OB_PRE_OPERATION_INFORMATION {
    _In_ OB_OPERATION           Operation;
    union {
        _In_ ULONG Flags;
        struct {
            _In_ ULONG KernelHandle:1;
            _In_ ULONG Reserved:31;
        };
    };
    _In_ PVOID                         Object;
    _In_ POBJECT_TYPE                  ObjectType;
    _Out_ PVOID                        CallContext;
    _In_ POB_PRE_OPERATION_PARAMETERS  Parameters;
} OB_PRE_OPERATION_INFORMATION, *POB_PRE_OPERATION_INFORMATION;

typedef struct _OB_POST_CREATE_HANDLE_INFORMATION {
    _In_ ACCESS_MASK            GrantedAccess;
} OB_POST_CREATE_HANDLE_INFORMATION, *POB_POST_CREATE_HANDLE_INFORMATION;

typedef struct _OB_POST_DUPLICATE_HANDLE_INFORMATION {
    _In_ ACCESS_MASK            GrantedAccess;
} OB_POST_DUPLICATE_HANDLE_INFORMATION, * POB_POST_DUPLICATE_HANDLE_INFORMATION;

typedef union _OB_POST_OPERATION_PARAMETERS {
    _In_ OB_POST_CREATE_HANDLE_INFORMATION       CreateHandleInformation;
    _In_ OB_POST_DUPLICATE_HANDLE_INFORMATION    DuplicateHandleInformation;
} OB_POST_OPERATION_PARAMETERS, *POB_POST_OPERATION_PARAMETERS;

typedef struct _OB_POST_OPERATION_INFORMATION {
    _In_ OB_OPERATION  Operation;
    union {
        _In_ ULONG Flags;
        struct {
            _In_ ULONG KernelHandle:1;
            _In_ ULONG Reserved:31;
        };
    };
    _In_ PVOID                          Object;
    _In_ POBJECT_TYPE                   ObjectType;
    _In_ PVOID                          CallContext;
    _In_ NTSTATUS                       ReturnStatus;
    _In_ POB_POST_OPERATION_PARAMETERS  Parameters;
} OB_POST_OPERATION_INFORMATION,*POB_POST_OPERATION_INFORMATION;

typedef enum _OB_PREOP_CALLBACK_STATUS {
    OB_PREOP_SUCCESS
} OB_PREOP_CALLBACK_STATUS, *POB_PREOP_CALLBACK_STATUS;

typedef OB_PREOP_CALLBACK_STATUS
(*POB_PRE_OPERATION_CALLBACK) (
    _In_ PVOID RegistrationContext,
    _Inout_ POB_PRE_OPERATION_INFORMATION OperationInformation
    );

typedef VOID
(*POB_POST_OPERATION_CALLBACK) (
    _In_ PVOID RegistrationContext,
    _In_ POB_POST_OPERATION_INFORMATION OperationInformation
    );

typedef struct _OB_OPERATION_REGISTRATION {
    _In_ POBJECT_TYPE                *ObjectType;
    _In_ OB_OPERATION                Operations;
    _In_ POB_PRE_OPERATION_CALLBACK  PreOperation;
    _In_ POB_POST_OPERATION_CALLBACK PostOperation;
} OB_OPERATION_REGISTRATION, *POB_OPERATION_REGISTRATION;

typedef struct _OB_CALLBACK_REGISTRATION {
    _In_ USHORT                     Version;
    _In_ USHORT                     OperationRegistrationCount;
    _In_ UNICODE_STRING             Altitude;
    _In_ PVOID                      RegistrationContext;
    _In_ OB_OPERATION_REGISTRATION  *OperationRegistration;
} OB_CALLBACK_REGISTRATION, *POB_CALLBACK_REGISTRATION;

NTKERNELAPI
NTSTATUS
ObRegisterCallbacks (
    _In_ POB_CALLBACK_REGISTRATION CallbackRegistration,
    _Outptr_ PVOID *RegistrationHandle
    );

NTKERNELAPI
VOID
ObUnRegisterCallbacks (
    _In_ PVOID RegistrationHandle
    );

NTKERNELAPI
USHORT
ObGetFilterVersion ();

#ifndef _PCI_X_
#define _PCI_X_

typedef struct _PCI_SLOT_NUMBER {
    union {
        struct {
            ULONG   DeviceNumber:5;
            ULONG   FunctionNumber:3;
            ULONG   Reserved:24;
        } bits;
        ULONG   AsULONG;
    } u;
} PCI_SLOT_NUMBER, *PPCI_SLOT_NUMBER;

#define PCI_TYPE0_ADDRESSES             6
#define PCI_TYPE1_ADDRESSES             2
#define PCI_TYPE2_ADDRESSES             5

typedef struct _PCI_COMMON_HEADER {
    USHORT  VendorID;                   // (ro)
    USHORT  DeviceID;                   // (ro)
    USHORT  Command;                    // Device control
    USHORT  Status;
    UCHAR   RevisionID;                 // (ro)
    UCHAR   ProgIf;                     // (ro)
    UCHAR   SubClass;                   // (ro)
    UCHAR   BaseClass;                  // (ro)
    UCHAR   CacheLineSize;              // (ro+)
    UCHAR   LatencyTimer;               // (ro+)
    UCHAR   HeaderType;                 // (ro)
    UCHAR   BIST;                       // Built in self test

    union {
        struct _PCI_HEADER_TYPE_0 {
            ULONG   BaseAddresses[PCI_TYPE0_ADDRESSES];
            ULONG   CIS;
            USHORT  SubVendorID;
            USHORT  SubSystemID;
            ULONG   ROMBaseAddress;
            UCHAR   CapabilitiesPtr;
            UCHAR   Reserved1[3];
            ULONG   Reserved2;
            UCHAR   InterruptLine;      //
            UCHAR   InterruptPin;       // (ro)
            UCHAR   MinimumGrant;       // (ro)
            UCHAR   MaximumLatency;     // (ro)
        } type0;

        struct _PCI_HEADER_TYPE_1 {
            ULONG   BaseAddresses[PCI_TYPE1_ADDRESSES];
            UCHAR   PrimaryBus;
            UCHAR   SecondaryBus;
            UCHAR   SubordinateBus;
            UCHAR   SecondaryLatency;
            UCHAR   IOBase;
            UCHAR   IOLimit;
            USHORT  SecondaryStatus;
            USHORT  MemoryBase;
            USHORT  MemoryLimit;
            USHORT  PrefetchBase;
            USHORT  PrefetchLimit;
            ULONG   PrefetchBaseUpper32;
            ULONG   PrefetchLimitUpper32;
            USHORT  IOBaseUpper16;
            USHORT  IOLimitUpper16;
            UCHAR   CapabilitiesPtr;
            UCHAR   Reserved1[3];
            ULONG   ROMBaseAddress;
            UCHAR   InterruptLine;
            UCHAR   InterruptPin;
            USHORT  BridgeControl;
        } type1;

        struct _PCI_HEADER_TYPE_2 {
            ULONG   SocketRegistersBaseAddress;
            UCHAR   CapabilitiesPtr;
            UCHAR   Reserved;
            USHORT  SecondaryStatus;
            UCHAR   PrimaryBus;
            UCHAR   SecondaryBus;
            UCHAR   SubordinateBus;
            UCHAR   SecondaryLatency;
            struct  {
                ULONG   Base;
                ULONG   Limit;
            }       Range[PCI_TYPE2_ADDRESSES-1];
            UCHAR   InterruptLine;
            UCHAR   InterruptPin;
            USHORT  BridgeControl;
        } type2;
    } u;
} PCI_COMMON_HEADER, *PPCI_COMMON_HEADER;

#ifdef __cplusplus
typedef struct _PCI_COMMON_CONFIG : PCI_COMMON_HEADER {
    UCHAR   DeviceSpecific[192];
} PCI_COMMON_CONFIG, *PPCI_COMMON_CONFIG;
#else
typedef struct _PCI_COMMON_CONFIG {
    PCI_COMMON_HEADER DUMMYSTRUCTNAME;
    UCHAR   DeviceSpecific[192];
} PCI_COMMON_CONFIG, *PPCI_COMMON_CONFIG;
#endif

#define PCI_COMMON_HDR_LENGTH (FIELD_OFFSET (PCI_COMMON_CONFIG, DeviceSpecific))
#define PCI_EXTENDED_CONFIG_LENGTH          0x1000

#define PCI_MAX_DEVICES                     32
#define PCI_MAX_FUNCTION                    8
#define PCI_MAX_BRIDGE_NUMBER               0xFF

#define PCI_INVALID_VENDORID                0xFFFF

#define PCI_MULTIFUNCTION                   0x80
#define PCI_DEVICE_TYPE                     0x00
#define PCI_BRIDGE_TYPE                     0x01
#define PCI_CARDBUS_BRIDGE_TYPE             0x02

#define PCI_CONFIGURATION_TYPE(PciData) \
    (((PPCI_COMMON_CONFIG)(PciData))->HeaderType & ~PCI_MULTIFUNCTION)

#define PCI_MULTIFUNCTION_DEVICE(PciData) \
    ((((PPCI_COMMON_CONFIG)(PciData))->HeaderType & PCI_MULTIFUNCTION) != 0)

#define PCI_ENABLE_IO_SPACE                 0x0001
#define PCI_ENABLE_MEMORY_SPACE             0x0002
#define PCI_ENABLE_BUS_MASTER               0x0004
#define PCI_ENABLE_SPECIAL_CYCLES           0x0008
#define PCI_ENABLE_WRITE_AND_INVALIDATE     0x0010
#define PCI_ENABLE_VGA_COMPATIBLE_PALETTE   0x0020
#define PCI_ENABLE_PARITY                   0x0040  // (ro+)
#define PCI_ENABLE_WAIT_CYCLE               0x0080  // (ro+)
#define PCI_ENABLE_SERR                     0x0100  // (ro+)
#define PCI_ENABLE_FAST_BACK_TO_BACK        0x0200  // (ro)
#define PCI_DISABLE_LEVEL_INTERRUPT         0x0400

#define PCI_STATUS_INTERRUPT_PENDING        0x0008
#define PCI_STATUS_CAPABILITIES_LIST        0x0010  // (ro)
#define PCI_STATUS_66MHZ_CAPABLE            0x0020  // (ro)
#define PCI_STATUS_UDF_SUPPORTED            0x0040  // (ro)
#define PCI_STATUS_FAST_BACK_TO_BACK        0x0080  // (ro)
#define PCI_STATUS_DATA_PARITY_DETECTED     0x0100
#define PCI_STATUS_DEVSEL                   0x0600  // 2 bits wide
#define PCI_STATUS_SIGNALED_TARGET_ABORT    0x0800
#define PCI_STATUS_RECEIVED_TARGET_ABORT    0x1000
#define PCI_STATUS_RECEIVED_MASTER_ABORT    0x2000
#define PCI_STATUS_SIGNALED_SYSTEM_ERROR    0x4000
#define PCI_STATUS_DETECTED_PARITY_ERROR    0x8000

#define PCI_WHICHSPACE_CONFIG               0x0
#define PCI_WHICHSPACE_ROM                  0x52696350

#define PCI_CAPABILITY_ID_POWER_MANAGEMENT  0x01
#define PCI_CAPABILITY_ID_AGP               0x02
#define PCI_CAPABILITY_ID_VPD               0x03
#define PCI_CAPABILITY_ID_SLOT_ID           0x04
#define PCI_CAPABILITY_ID_MSI               0x05
#define PCI_CAPABILITY_ID_CPCI_HOTSWAP      0x06
#define PCI_CAPABILITY_ID_PCIX              0x07
#define PCI_CAPABILITY_ID_HYPERTRANSPORT    0x08
#define PCI_CAPABILITY_ID_VENDOR_SPECIFIC   0x09
#define PCI_CAPABILITY_ID_DEBUG_PORT        0x0A
#define PCI_CAPABILITY_ID_CPCI_RES_CTRL     0x0B
#define PCI_CAPABILITY_ID_SHPC              0x0C
#define PCI_CAPABILITY_ID_P2P_SSID          0x0D
#define PCI_CAPABILITY_ID_AGP_TARGET        0x0E
#define PCI_CAPABILITY_ID_SECURE            0x0F
#define PCI_CAPABILITY_ID_PCI_EXPRESS       0x10
#define PCI_CAPABILITY_ID_MSIX              0x11
#define PCI_CAPABILITY_ID_SATA_CONFIG       0x12
#define PCI_CAPABILITY_ID_ADVANCED_FEATURES 0x13

typedef struct _PCI_CAPABILITIES_HEADER {
    UCHAR   CapabilityID;
    UCHAR   Next;
} PCI_CAPABILITIES_HEADER, *PPCI_CAPABILITIES_HEADER;

typedef struct _PCI_PMC {
    UCHAR       Version:3;
    UCHAR       PMEClock:1;
    UCHAR       Rsvd1:1;
    UCHAR       DeviceSpecificInitialization:1;
    UCHAR       Rsvd2:2;
    struct _PM_SUPPORT {
        UCHAR   Rsvd2:1;
        UCHAR   D1:1;
        UCHAR   D2:1;
        UCHAR   PMED0:1;
        UCHAR   PMED1:1;
        UCHAR   PMED2:1;
        UCHAR   PMED3Hot:1;
        UCHAR   PMED3Cold:1;
    } Support;
} PCI_PMC, *PPCI_PMC;

typedef struct _PCI_PMCSR {
    USHORT      PowerState:2;
    USHORT      Rsvd1:1;
    USHORT      NoSoftReset:1;
    USHORT      Rsvd2:4;
    USHORT      PMEEnable:1;
    USHORT      DataSelect:4;
    USHORT      DataScale:2;
    USHORT      PMEStatus:1;
} PCI_PMCSR, *PPCI_PMCSR;


typedef struct _PCI_PMCSR_BSE {
    UCHAR       Rsvd1:6;
    UCHAR       D3HotSupportsStopClock:1;       // B2_B3#
    UCHAR       BusPowerClockControlEnabled:1;  // BPCC_EN
} PCI_PMCSR_BSE, *PPCI_PMCSR_BSE;

typedef struct _PCI_PM_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;
    union {
        PCI_PMC         Capabilities;
        USHORT          AsUSHORT;
    } PMC;

    union {
        PCI_PMCSR       ControlStatus;
        USHORT          AsUSHORT;
    } PMCSR;

    union {
        PCI_PMCSR_BSE   BridgeSupport;
        UCHAR           AsUCHAR;
    } PMCSR_BSE;

    UCHAR   Data;

} PCI_PM_CAPABILITY, *PPCI_PM_CAPABILITY;

typedef struct _PCI_AGP_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;

    USHORT  Minor:4;
    USHORT  Major:4;
    USHORT  Rsvd1:8;

    struct _PCI_AGP_STATUS {
        ULONG   Rate:3;
        ULONG   Agp3Mode:1;
        ULONG   FastWrite:1;
        ULONG   FourGB:1;
        ULONG   HostTransDisable:1;
        ULONG   Gart64:1;
        ULONG   ITA_Coherent:1;
        ULONG   SideBandAddressing:1;                   // SBA
        ULONG   CalibrationCycle:3;
        ULONG   AsyncRequestSize:3;
        ULONG   Rsvd1:1;
        ULONG   Isoch:1;
        ULONG   Rsvd2:6;
        ULONG   RequestQueueDepthMaximum:8;             // RQ
    } AGPStatus;

    struct _PCI_AGP_COMMAND {
        ULONG   Rate:3;
        ULONG   Rsvd1:1;
        ULONG   FastWriteEnable:1;
        ULONG   FourGBEnable:1;
        ULONG   Rsvd2:1;
        ULONG   Gart64:1;
        ULONG   AGPEnable:1;
        ULONG   SBAEnable:1;
        ULONG   CalibrationCycle:3;
        ULONG   AsyncReqSize:3;
        ULONG   Rsvd3:8;
        ULONG   RequestQueueDepth:8;
    } AGPCommand;

} PCI_AGP_CAPABILITY, *PPCI_AGP_CAPABILITY;

typedef enum _EXTENDED_AGP_REGISTER {
    IsochStatus,
    AgpControl,
    ApertureSize,
    AperturePageSize,
    GartLow,
    GartHigh,
    IsochCommand
} EXTENDED_AGP_REGISTER, *PEXTENDED_AGP_REGISTER;

typedef struct _PCI_AGP_ISOCH_STATUS {
    ULONG ErrorCode: 2;
    ULONG Rsvd1: 1;
    ULONG Isoch_L: 3;
    ULONG Isoch_Y: 2;
    ULONG Isoch_N: 8;
    ULONG Rsvd2: 16;
} PCI_AGP_ISOCH_STATUS, *PPCI_AGP_ISOCH_STATUS;

typedef struct _PCI_AGP_CONTROL {
    ULONG Rsvd1: 7;
    ULONG GTLB_Enable: 1;
    ULONG AP_Enable: 1;
    ULONG CAL_Disable: 1;
    ULONG Rsvd2: 22;
} PCI_AGP_CONTROL, *PPCI_AGP_CONTROL;

typedef struct _PCI_AGP_APERTURE_PAGE_SIZE {
    USHORT PageSizeMask: 11;
    USHORT Rsvd1: 1;
    USHORT PageSizeSelect: 4;
} PCI_AGP_APERTURE_PAGE_SIZE, *PPCI_AGP_APERTURE_PAGE_SIZE;

typedef struct _PCI_AGP_ISOCH_COMMAND {
    USHORT Rsvd1: 6;
    USHORT Isoch_Y: 2;
    USHORT Isoch_N: 8;
} PCI_AGP_ISOCH_COMMAND, *PPCI_AGP_ISOCH_COMMAND;

typedef struct PCI_AGP_EXTENDED_CAPABILITY {

    PCI_AGP_ISOCH_STATUS IsochStatus;

    PCI_AGP_CONTROL AgpControl;
    USHORT ApertureSize;
    PCI_AGP_APERTURE_PAGE_SIZE AperturePageSize;
    ULONG GartLow;
    ULONG GartHigh;
    PCI_AGP_ISOCH_COMMAND IsochCommand;

} PCI_AGP_EXTENDED_CAPABILITY, *PPCI_AGP_EXTENDED_CAPABILITY;


#define PCI_AGP_RATE_1X     0x1
#define PCI_AGP_RATE_2X     0x2
#define PCI_AGP_RATE_4X     0x4

typedef struct {

    PCI_CAPABILITIES_HEADER Header;

    union {
        struct {
            USHORT  DataParityErrorRecoveryEnable:1;
            USHORT  EnableRelaxedOrdering:1;
            USHORT  MaxMemoryReadByteCount:2;
            USHORT  MaxOutstandingSplitTransactions:3;
            USHORT  Reserved:9;
        } bits;
        USHORT  AsUSHORT;
    } Command;

    union {
        struct {
            ULONG   FunctionNumber:3;
            ULONG   DeviceNumber:5;
            ULONG   BusNumber:8;
            ULONG   Device64Bit:1;
            ULONG   Capable133MHz:1;
            ULONG   SplitCompletionDiscarded:1;
            ULONG   UnexpectedSplitCompletion:1;
            ULONG   DeviceComplexity:1;
            ULONG   DesignedMaxMemoryReadByteCount:2;
            ULONG   DesignedMaxOutstandingSplitTransactions:3;
            ULONG   DesignedMaxCumulativeReadSize:3;
            ULONG   ReceivedSplitCompletionErrorMessage:1;
            ULONG   CapablePCIX266:1;
            ULONG   CapablePCIX533:1;
        } bits;
        ULONG   AsULONG;
    } Status;
} PCI_X_CAPABILITY, *PPCI_X_CAPABILITY;

#define PCIX_MODE_CONVENTIONAL_PCI  0x0
#define PCIX_MODE1_66MHZ            0x1
#define PCIX_MODE1_100MHZ           0x2
#define PCIX_MODE1_133MHZ           0x3
#define PCIX_MODE2_266_66MHZ        0x9
#define PCIX_MODE2_266_100MHZ       0xA
#define PCIX_MODE2_266_133MHZ       0xB
#define PCIX_MODE2_533_66MHZ        0xD
#define PCIX_MODE2_533_100MHZ       0xE
#define PCIX_MODE2_533_133MHZ       0xF

#define PCIX_VERSION_MODE1_ONLY     0x0
#define PCIX_VERSION_MODE2_ECC      0x1
#define PCIX_VERSION_DUAL_MODE_ECC  0x2

typedef struct _PCIX_BRIDGE_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;

    union {
        struct {
            USHORT Bus64Bit:1;
            USHORT Bus133MHzCapable:1;
            USHORT SplitCompletionDiscarded:1;
            USHORT UnexpectedSplitCompletion:1;
            USHORT SplitCompletionOverrun:1;
            USHORT SplitRequestDelayed:1;
            USHORT BusModeFrequency:4;  // PCIX_MODE_x
            USHORT Rsvd:2;
            USHORT Version:2;           // PCIX_VERSION_x
            USHORT Bus266MHzCapable:1;
            USHORT Bus533MHzCapable:1;
        } DUMMYSTRUCTNAME;
        USHORT AsUSHORT;
    } SecondaryStatus;

    union {
        struct {
            ULONG FunctionNumber:3;
            ULONG DeviceNumber:5;
            ULONG BusNumber:8;
            ULONG Device64Bit:1;
            ULONG Device133MHzCapable:1;
            ULONG SplitCompletionDiscarded:1;
            ULONG UnexpectedSplitCompletion:1;
            ULONG SplitCompletionOverrun:1;
            ULONG SplitRequestDelayed:1;
            ULONG Rsvd:7;
            ULONG DIMCapable:1;
            ULONG Device266MHzCapable:1;
            ULONG Device533MHzCapable:1;
        } DUMMYSTRUCTNAME;
        ULONG AsULONG;
    } BridgeStatus;

    USHORT UpstreamSplitTransactionCapacity;
    USHORT UpstreamSplitTransactionLimit;

    USHORT DownstreamSplitTransactionCapacity;
    USHORT DownstreamSplitTransactionLimit;

    union {
        struct {
            ULONG SelectSecondaryRegisters:1;
            ULONG ErrorPresentInOtherBank:1;
            ULONG AdditionalCorrectableError:1;
            ULONG AdditionalUncorrectableError:1;
            ULONG ErrorPhase:3;
            ULONG ErrorCorrected:1;
            ULONG Syndrome:8;
            ULONG ErrorFirstCommand:4;
            ULONG ErrorSecondCommand:4;
            ULONG ErrorUpperAttributes:4;
            ULONG ControlUpdateEnable:1;
            ULONG Rsvd:1;
            ULONG DisableSingleBitCorrection:1;
            ULONG EccMode:1;
        } DUMMYSTRUCTNAME;
        ULONG AsULONG;
    } EccControlStatus;

    ULONG EccFirstAddress;
    ULONG EccSecondAddress;
    ULONG EccAttribute;

} PCIX_BRIDGE_CAPABILITY, *PPCIX_BRIDGE_CAPABILITY;

typedef struct _PCI_SUBSYSTEM_IDS_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;
    USHORT Reserved;
    USHORT SubVendorID;
    USHORT SubSystemID;

} PCI_SUBSYSTEM_IDS_CAPABILITY, *PPCI_SUBSYSTEM_IDS_CAPABILITY;

typedef struct _PCI_ADVANCED_FEATURES_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;
    UCHAR Length;

    union {
        struct {
            UCHAR FunctionLevelResetSupported:1;
            UCHAR TransactionsPendingSupported:1;
            UCHAR Rsvd:6;
        } DUMMYSTRUCTNAME;

        UCHAR AsUCHAR;
    } Capabilities;

    union {
        struct {
            UCHAR InitiateFunctionLevelReset:1;
            UCHAR Rsvd:7;
        } DUMMYSTRUCTNAME;

        UCHAR AsUCHAR;
    } Control;

    union {
        struct {
            UCHAR TransactionsPending:1;
            UCHAR Rsvd:7;
        } DUMMYSTRUCTNAME;

        UCHAR AsUCHAR;
    } Status;

} PCI_ADVANCED_FEATURES_CAPABILITY, *PPCI_ADVANCED_FEATURES_CAPABILITY;

#define OSC_FIRMWARE_FAILURE                            0x02
#define OSC_UNRECOGNIZED_UUID                           0x04
#define OSC_UNRECOGNIZED_REVISION                       0x08
#define OSC_CAPABILITIES_MASKED                         0x10

#define PCI_ROOT_BUS_OSC_METHOD_CAPABILITY_REVISION     0x01

typedef struct _PCI_ROOT_BUS_OSC_SUPPORT_FIELD {
    union {
        struct {
            ULONG ExtendedConfigOpRegions:1;
            ULONG ActiveStatePowerManagement:1;
            ULONG ClockPowerManagement:1;
            ULONG SegmentGroups:1;
            ULONG MessageSignaledInterrupts:1;
            ULONG OptimizedBufferFlushAndFill:1;
            ULONG AspmOptionality:1;
            ULONG Reserved:25;
        } DUMMYSTRUCTNAME;
        ULONG AsULONG;
    } u;
} PCI_ROOT_BUS_OSC_SUPPORT_FIELD, *PPCI_ROOT_BUS_OSC_SUPPORT_FIELD;

typedef struct _PCI_ROOT_BUS_OSC_CONTROL_FIELD {
    union {
        struct {
            ULONG ExpressNativeHotPlug:1;
            ULONG ShpcNativeHotPlug:1;
            ULONG ExpressNativePME:1;
            ULONG ExpressAdvancedErrorReporting:1;
            ULONG ExpressCapabilityStructure:1;
            ULONG LatencyToleranceReporting:1;
            ULONG Reserved:26;
        } DUMMYSTRUCTNAME;
        ULONG AsULONG;
    } u;
} PCI_ROOT_BUS_OSC_CONTROL_FIELD, *PPCI_ROOT_BUS_OSC_CONTROL_FIELD;

typedef struct _PCI_FIRMWARE_BUS_CAPS {
    USHORT Type;
    USHORT Length; // must be 16
    struct {
        UCHAR SixtyFourBitDevice:1;
        UCHAR PciXMode1EccCapable:1;
        UCHAR DeviceIdMessagingCapable:1;
        UCHAR ObffWakeSignalCapable:1;
        UCHAR Reserved1:4;
    } DUMMYSTRUCTNAME;
    UCHAR CurrentSpeedAndMode;
    UCHAR SupportedSpeedsAndModesLowByte;
    UCHAR SupportedSpeedsAndModesHighByte;
    UCHAR Voltage;
    UCHAR Reserved2[7];
} PCI_FIRMWARE_BUS_CAPS, *PPCI_FIRMWARE_BUS_CAPS;

typedef struct _PCI_FIRMWARE_BUS_CAPS_RETURN_BUFFER {
    USHORT Version;
    USHORT Status;
    ULONG  Length;
    PCI_FIRMWARE_BUS_CAPS Caps;
} PCI_FIRMWARE_BUS_CAPS_RETURN_BUFFER, *PPCI_FIRMWARE_BUS_CAPS_RETURN_BUFFER;

typedef enum _PCI_HARDWARE_INTERFACE {

    PciConventional,
    PciXMode1,
    PciXMode2,
    PciExpress

} PCI_HARDWARE_INTERFACE, *PPCI_HARDWARE_INTERFACE;

typedef enum {

    BusWidth32Bits,
    BusWidth64Bits

} PCI_BUS_WIDTH;

typedef struct _PCI_ROOT_BUS_HARDWARE_CAPABILITY {

    PCI_HARDWARE_INTERFACE SecondaryInterface;
    struct {
        BOOLEAN BusCapabilitiesFound;
        ULONG CurrentSpeedAndMode;
        ULONG SupportedSpeedsAndModes;
        BOOLEAN DeviceIDMessagingCapable;
        PCI_BUS_WIDTH SecondaryBusWidth;
    } DUMMYSTRUCTNAME;
    PCI_ROOT_BUS_OSC_SUPPORT_FIELD OscFeatureSupport;
    PCI_ROOT_BUS_OSC_CONTROL_FIELD OscControlRequest;
    PCI_ROOT_BUS_OSC_CONTROL_FIELD OscControlGranted;

} PCI_ROOT_BUS_HARDWARE_CAPABILITY, *PPCI_ROOT_BUS_HARDWARE_CAPABILITY;

typedef union _PCI_EXPRESS_CAPABILITIES_REGISTER {

    struct {

        USHORT CapabilityVersion:4;
        USHORT DeviceType:4;               // PCI_EXPRESS_DEVICE_TYPE
        USHORT SlotImplemented:1;
        USHORT InterruptMessageNumber:5;
        USHORT Rsvd:2;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_CAPABILITIES_REGISTER, *PPCI_EXPRESS_CAPABILITIES_REGISTER;

typedef union _PCI_EXPRESS_DEVICE_CAPABILITIES_REGISTER {

    struct {

        ULONG MaxPayloadSizeSupported:3;     // EXPRESS_MAX_PAYLOAD_SIZE
        ULONG PhantomFunctionsSupported:2;
        ULONG ExtendedTagSupported:1;
        ULONG L0sAcceptableLatency:3;        // EXPRESS_L0S_LATENCY
        ULONG L1AcceptableLatency:3;         // EXPRESS_L1_LATENCY
        ULONG Undefined:3;
        ULONG RoleBasedErrorReporting:1;
        ULONG Rsvd1:2;
        ULONG CapturedSlotPowerLimit:8;
        ULONG CapturedSlotPowerLimitScale:2;
        ULONG FunctionLevelResetCapability:1;
        ULONG Rsvd2:3;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_DEVICE_CAPABILITIES_REGISTER, *PPCI_EXPRESS_DEVICE_CAPABILITIES_REGISTER;

#define PCI_EXPRESS_AER_DEVICE_CONTROL_MASK 0x07;

typedef union _PCI_EXPRESS_DEVICE_CONTROL_REGISTER {

    struct {

        USHORT CorrectableErrorEnable:1;
        USHORT NonFatalErrorEnable:1;
        USHORT FatalErrorEnable:1;
        USHORT UnsupportedRequestErrorEnable:1;
        USHORT EnableRelaxedOrder:1;
        USHORT MaxPayloadSize:3;                 // EXPRESS_MAX_PAYLOAD_SIZE
        USHORT ExtendedTagEnable:1;
        USHORT PhantomFunctionsEnable:1;
        USHORT AuxPowerEnable:1;
        USHORT NoSnoopEnable:1;
        USHORT MaxReadRequestSize:3;             // EXPRESS_MAX_PAYLOAD_SIZE
        USHORT BridgeConfigRetryEnable:1;
    } DUMMYSTRUCTNAME;
    struct {
        USHORT :15;
        USHORT InitiateFunctionLevelReset:1;
    } DUMMYSTRUCTNAME2;

    USHORT AsUSHORT;

} PCI_EXPRESS_DEVICE_CONTROL_REGISTER, *PPCI_EXPRESS_DEVICE_CONTROL_REGISTER;

#define PCI_EXPRESS_AER_DEVICE_STATUS_MASK 0x0F;

typedef union _PCI_EXPRESS_DEVICE_STATUS_REGISTER {

    struct {

        USHORT CorrectableErrorDetected:1;
        USHORT NonFatalErrorDetected:1;
        USHORT FatalErrorDetected:1;
        USHORT UnsupportedRequestDetected:1;
        USHORT AuxPowerDetected:1;
        USHORT TransactionsPending:1;
        USHORT Rsvd:10;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_DEVICE_STATUS_REGISTER, *PPCI_EXPRESS_DEVICE_STATUS_REGISTER;

typedef union _PCI_EXPRESS_LINK_CAPABILITIES_REGISTER {

    struct {

        ULONG MaximumLinkSpeed:4;
        ULONG MaximumLinkWidth:6;
        ULONG ActiveStatePMSupport:2;   // EXPRESS_ASPM_CONFIG
        ULONG L0sExitLatency:3;         // EXPRESS_L0S_LATENCY
        ULONG L1ExitLatency:3;          // EXPRESS_L1_LATENCY
        ULONG ClockPowerManagement:1;
        ULONG SurpriseDownErrorReportingCapable:1;
        ULONG DataLinkLayerActiveReportingCapable:1;
        ULONG LinkBandwidthNotificationCapability:1;
        ULONG AspmOptionalityCompliance:1;
        ULONG Rsvd:1;
        ULONG PortNumber:8;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_LINK_CAPABILITIES_REGISTER, *PPCI_EXPRESS_LINK_CAPABILITIES_REGISTER;

typedef union _PCI_EXPRESS_LINK_CONTROL_REGISTER {

    struct {

        USHORT ActiveStatePMControl:2;    // EXPRESS_ASPM_CONFIG
        USHORT Rsvd1:1;
        USHORT ReadCompletionBoundary:1;  // EXPRESS_RCB
        USHORT LinkDisable:1;
        USHORT RetrainLink:1;
        USHORT CommonClockConfig:1;
        USHORT ExtendedSynch:1;
        USHORT EnableClockPowerManagement:1;
        USHORT Rsvd2:7;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_LINK_CONTROL_REGISTER, *PPCI_EXPRESS_LINK_CONTROL_REGISTER;

typedef union _PCI_EXPRESS_LINK_STATUS_REGISTER {

    struct {

        USHORT LinkSpeed:4;
        USHORT LinkWidth:6;
        USHORT Undefined:1;
        USHORT LinkTraining:1;
        USHORT SlotClockConfig:1;
        USHORT DataLinkLayerActive:1;
        USHORT Rsvd:2;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_LINK_STATUS_REGISTER, *PPCI_EXPRESS_LINK_STATUS_REGISTER;

typedef union _PCI_EXPRESS_SLOT_CAPABILITIES_REGISTER {

    struct {

        ULONG AttentionButtonPresent:1;
        ULONG PowerControllerPresent:1;
        ULONG MRLSensorPresent:1;
        ULONG AttentionIndicatorPresent:1;
        ULONG PowerIndicatorPresent:1;
        ULONG HotPlugSurprise:1;
        ULONG HotPlugCapable:1;
        ULONG SlotPowerLimit:8;
        ULONG SlotPowerLimitScale:2;
        ULONG ElectromechanicalLockPresent:1;
        ULONG NoCommandCompletedSupport:1;
        ULONG PhysicalSlotNumber:13;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_SLOT_CAPABILITIES_REGISTER, *PPCI_EXPRESS_SLOT_CAPABILITIES_REGISTER;

typedef union _PCI_EXPRESS_SLOT_CONTROL_REGISTER {

    struct {

        USHORT AttentionButtonEnable:1;
        USHORT PowerFaultDetectEnable:1;
        USHORT MRLSensorEnable:1;
        USHORT PresenceDetectEnable:1;
        USHORT CommandCompletedEnable:1;
        USHORT HotPlugInterruptEnable:1;
        USHORT AttentionIndicatorControl:2;  // EXPRESS_INDICATOR_STATE
        USHORT PowerIndicatorControl:2;      // EXPRESS_INDICATOR_STATE
        USHORT PowerControllerControl:1;     // EXPRESS_POWER_STATE
        USHORT ElectromechanicalLockControl:1;
        USHORT DataLinkStateChangeEnable:1;
        USHORT Rsvd:3;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_SLOT_CONTROL_REGISTER, *PPCI_EXPRESS_SLOT_CONTROL_REGISTER;

typedef union _PCI_EXPRESS_SLOT_STATUS_REGISTER {

    struct {

        USHORT AttentionButtonPressed:1;
        USHORT PowerFaultDetected:1;
        USHORT MRLSensorChanged:1;
        USHORT PresenceDetectChanged:1;
        USHORT CommandCompleted:1;
        USHORT MRLSensorState:1;        // EXPRESS_MRL_STATE
        USHORT PresenceDetectState:1;   // EXPRESS_CARD_PRESENCE
        USHORT ElectromechanicalLockEngaged:1;
        USHORT DataLinkStateChanged:1;
        USHORT Rsvd:7;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_SLOT_STATUS_REGISTER, *PPCI_EXPRESS_SLOT_STATUS_REGISTER;

typedef union _PCI_EXPRESS_ROOT_CONTROL_REGISTER {

    struct {

        USHORT CorrectableSerrEnable:1;
        USHORT NonFatalSerrEnable:1;
        USHORT FatalSerrEnable:1;
        USHORT PMEInterruptEnable:1;
        USHORT CRSSoftwareVisibilityEnable:1;
        USHORT Rsvd:11;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_ROOT_CONTROL_REGISTER, *PPCI_EXPRESS_ROOT_CONTROL_REGISTER;

typedef union _PCI_EXPRESS_ROOT_CAPABILITIES_REGISTER {

    struct {

        USHORT CRSSoftwareVisibility:1;
        USHORT Rsvd:15;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_ROOT_CAPABILITIES_REGISTER, *PPCI_EXPRESS_ROOT_CAPABILITIES_REGISTER;

typedef union _PCI_EXPRESS_ROOT_STATUS_REGISTER {

    struct {

        ULONG PMERequestorId:16;  // PCI_EXPRESS_REQUESTOR_ID
        ULONG PMEStatus:1;
        ULONG PMEPending:1;
        ULONG Rsvd:14;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_ROOT_STATUS_REGISTER, *PPCI_EXPRESS_ROOT_STATUS_REGISTER;

typedef union _PCI_EXPRESS_DEVICE_CAPABILITIES_2_REGISTER {

    struct {

        ULONG CompletionTimeoutRangesSupported:4;
        ULONG CompletionTimeoutDisableSupported:1;
        ULONG AriForwardingSupported:1;
        ULONG AtomicOpRoutingSupported:1;
        ULONG AtomicOpCompleterSupported32Bit:1;
        ULONG AtomicOpCompleterSupported64Bit:1;
        ULONG CASCompleterSupported128Bit:1;
        ULONG NoROEnabledPRPRPassing:1;
        ULONG LTRMechanismSupported:1;
        ULONG TPHCompleterSupported:2;
        ULONG Rsvd:4;
        ULONG OBFFSupported:2;
        ULONG ExtendedFmtFieldSuported:1;
        ULONG EndEndTLPPrefixSupported:1;
        ULONG MaxEndEndTLPPrefixes:2;
        ULONG Rsvd2:8;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_DEVICE_CAPABILITIES_2_REGISTER, *PPCI_EXPRESS_DEVICE_CAPABILITIES_2_REGISTER;

typedef union _PCI_EXPRESS_DEVICE_CONTROL_2_REGISTER {

    struct {

        USHORT CompletionTimeoutValue:4;
        USHORT CompletionTimeoutDisable:1;
        USHORT AriForwardingEnable:1;
        USHORT AtomicOpRequesterEnable:1;
        USHORT AtomicOpEgresBlocking:1;
        USHORT IDORequestEnable:1;
        USHORT IDOCompletionEnable:1;
        USHORT LTRMechanismEnable:1;
        USHORT Rsvd:2;
        USHORT OBFFEnable:2;
        USHORT EndEndTLPPrefixBlocking:1;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_DEVICE_CONTROL_2_REGISTER, *PPCI_EXPRESS_DEVICE_CONTROL_2_REGISTER;

typedef union _PCI_EXPRESS_DEVICE_STATUS_2_REGISTER {
    struct {
        USHORT Rsvd:16;
    } DUMMYSTRUCTNAME;
    USHORT AsUSHORT;
} PCI_EXPRESS_DEVICE_STATUS_2_REGISTER, *PPCI_EXPRESS_DEVICE_STATUS_2_REGISTER;

typedef struct _PCI_EXPRESS_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;
    PCI_EXPRESS_CAPABILITIES_REGISTER ExpressCapabilities;
    PCI_EXPRESS_DEVICE_CAPABILITIES_REGISTER DeviceCapabilities;
    PCI_EXPRESS_DEVICE_CONTROL_REGISTER DeviceControl;
    PCI_EXPRESS_DEVICE_STATUS_REGISTER DeviceStatus;
    PCI_EXPRESS_LINK_CAPABILITIES_REGISTER LinkCapabilities;
    PCI_EXPRESS_LINK_CONTROL_REGISTER LinkControl;
    PCI_EXPRESS_LINK_STATUS_REGISTER LinkStatus;
    PCI_EXPRESS_SLOT_CAPABILITIES_REGISTER SlotCapabilities;
    PCI_EXPRESS_SLOT_CONTROL_REGISTER SlotControl;
    PCI_EXPRESS_SLOT_STATUS_REGISTER SlotStatus;
    PCI_EXPRESS_ROOT_CONTROL_REGISTER RootControl;
    PCI_EXPRESS_ROOT_CAPABILITIES_REGISTER RootCapabilities;
    PCI_EXPRESS_ROOT_STATUS_REGISTER RootStatus;
    PCI_EXPRESS_DEVICE_CAPABILITIES_2_REGISTER DeviceCapabilities2;
    PCI_EXPRESS_DEVICE_CONTROL_2_REGISTER DeviceControl2;
    PCI_EXPRESS_DEVICE_STATUS_2_REGISTER DeviceStatus2;
} PCI_EXPRESS_CAPABILITY, *PPCI_EXPRESS_CAPABILITY;

typedef enum {
    MRLClosed = 0,
    MRLOpen
} PCI_EXPRESS_MRL_STATE;

typedef enum {
    SlotEmpty = 0,
    CardPresent
} PCI_EXPRESS_CARD_PRESENCE;

typedef enum {
    IndicatorOn = 1,
    IndicatorBlink,
    IndicatorOff
} PCI_EXPRESS_INDICATOR_STATE;

typedef enum {

    PowerOn = 0,
    PowerOff

} PCI_EXPRESS_POWER_STATE;

typedef enum {

    NoAspmSupport = 0,
    L0sEntrySupport = 1,
    L1EntrySupport = 2,
    L0sAndL1EntrySupport = 3

} PCI_EXPRESS_ASPM_SUPPORT;

typedef enum {

    L0sAndL1EntryDisabled,
    L0sEntryEnabled,
    L1EntryEnabled,
    L0sAndL1EntryEnabled

} PCI_EXPRESS_ASPM_CONTROL;

typedef enum {

    L0s_Below64ns = 0,
    L0s_64ns_128ns,
    L0s_128ns_256ns,
    L0s_256ns_512ns,
    L0s_512ns_1us,
    L0s_1us_2us,
    L0s_2us_4us,
    L0s_Above4us

} PCI_EXPRESS_L0s_EXIT_LATENCY;

typedef enum {
    L1_Below1us = 0,
    L1_1us_2us,
    L1_2us_4us,
    L1_4us_8us,
    L1_8us_16us,
    L1_16us_32us,
    L1_32us_64us,
    L1_Above64us
} PCI_EXPRESS_L1_EXIT_LATENCY;

typedef enum {

    PciExpressEndpoint = 0,
    PciExpressLegacyEndpoint,
    PciExpressRootPort = 4,
    PciExpressUpstreamSwitchPort,
    PciExpressDownstreamSwitchPort,
    PciExpressToPciXBridge,
    PciXToExpressBridge,
    PciExpressRootComplexIntegratedEndpoint,
    PciExpressRootComplexEventCollector

} PCI_EXPRESS_DEVICE_TYPE;

typedef enum {

    MaxPayload128Bytes = 0,
    MaxPayload256Bytes,
    MaxPayload512Bytes,
    MaxPayload1024Bytes,
    MaxPayload2048Bytes,
    MaxPayload4096Bytes

} PCI_EXPRESS_MAX_PAYLOAD_SIZE;

typedef union _PCI_EXPRESS_PME_REQUESTOR_ID {

    struct {

        USHORT FunctionNumber:3;
        USHORT DeviceNumber:5;
        USHORT BusNumber:8;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_PME_REQUESTOR_ID, *PPCI_EXPRESS_PME_REQUESTOR_ID;

#define PCI_EXPRESS_ADVANCED_ERROR_REPORTING_CAP_ID                     0x0001
#define PCI_EXPRESS_VIRTUAL_CHANNEL_CAP_ID                              0x0002
#define PCI_EXPRESS_DEVICE_SERIAL_NUMBER_CAP_ID                         0x0003
#define PCI_EXPRESS_POWER_BUDGETING_CAP_ID                              0x0004
#define PCI_EXPRESS_RC_LINK_DECLARATION_CAP_ID                          0x0005
#define PCI_EXPRESS_RC_INTERNAL_LINK_CONTROL_CAP_ID                     0x0006
#define PCI_EXPRESS_RC_EVENT_COLLECTOR_ENDPOINT_ASSOCIATION_CAP_ID      0x0007
#define PCI_EXPRESS_MFVC_CAP_ID                                         0x0008
#define PCI_EXPRESS_VC_AND_MFVC_CAP_ID                                  0x0009
#define PCI_EXPRESS_RCRB_HEADER_CAP_ID                                  0x000A
#define PCI_EXPRESS_VENDOR_SPECIFIC_CAP_ID                              0x000B
#define PCI_EXPRESS_CONFIGURATION_ACCESS_CORRELATION_CAP_ID             0x000C
#define PCI_EXPRESS_ACCESS_CONTROL_SERVICES_CAP_ID                      0x000D
#define PCI_EXPRESS_ARI_CAP_ID                                          0x000E
#define PCI_EXPRESS_ATS_CAP_ID                                          0x000F
#define PCI_EXPRESS_SINGLE_ROOT_IO_VIRTUALIZATION_CAP_ID                0x0010
#define PCI_EXPRESS_MULTI_ROOT_IO_VIRTUALIZATION_CAP_ID                 0x0011
#define PCI_EXPRESS_MULTICAST_CAP_ID                                    0x0012
#define PCI_EXPRESS_PAGE_REQUEST_CAP_ID                                 0x0013
#define PCI_EXPRESS_RESERVED_FOR_AMD_CAP_ID                             0x0014
#define PCI_EXPRESS_RESIZABLE_BAR_CAP_ID                                0x0015
#define PCI_EXPRESS_DPA_CAP_ID                                          0x0016
#define PCI_EXPRESS_TPH_REQUESTER_CAP_ID                                0x0017
#define PCI_EXPRESS_LTR_CAP_ID                                          0x0018
#define PCI_EXPRESS_SECONDARY_PCI_EXPRESS_CAP_ID                        0x0019
#define PCI_EXPRESS_PMUX_CAP_ID                                         0x001A
#define PCI_EXPRESS_PASID_CAP_ID                                        0x001B
#define PCI_EXPRESS_LN_REQUESTER_CAP_ID                                 0x001C
#define PCI_EXPRESS_DPC_CAP_ID                                          0x001D
#define PCI_EXPRESS_L1_PM_SS_CAP_ID                                     0x001E
#define PCI_EXPRESS_PTM_CAP_ID                                          0x001F
#define PCI_EXPRESS_MPCIE_CAP_ID                                        0x0020
#define PCI_EXPRESS_FRS_QUEUEING_CAP_ID                                 0x0021
#define PCI_EXPRESS_READINESS_TIME_REPORTING_CAP_ID                     0x0022

typedef struct _PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER {

    USHORT CapabilityID;
    USHORT Version:4;
    USHORT Next:12;

} PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER, *PPCI_EXPRESS_ENHANCED_CAPABILITY_HEADER;

typedef struct _PCI_EXPRESS_VENDOR_SPECIFIC_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    USHORT VsecId;
    USHORT VsecRev:4;
    USHORT VsecLength:12;

} PCI_EXPRESS_VENDOR_SPECIFIC_CAPABILITY, *PPCI_EXPRESS_VENDOR_SPECIFIC_CAPABILITY;

typedef struct _PCI_EXPRESS_SERIAL_NUMBER_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    ULONG LowSerialNumber;
    ULONG HighSerialNumber;

} PCI_EXPRESS_SERIAL_NUMBER_CAPABILITY, *PPCI_EXPRESS_SERIAL_NUMBER_CAPABILITY;

typedef struct _PCI_EXPRESS_ARI_CAPABILITY_REGISTER {

    USHORT MfvcFunctionGroupsCapability:1;
    USHORT AcsFunctionGroupsCapability:1;
    USHORT Reserved:6;
    USHORT NextFunctionNumber:8;

} PCI_EXPRESS_ARI_CAPABILITY_REGISTER, *PPCI_EXPRESS_ARI_CAPABILITY_REGISTER;

typedef struct _PCI_EXPRESS_ARI_CONTROL_REGISTER {

    USHORT MfvcFunctionGroupsEnable:1;
    USHORT AcsFunctionGroupsEnable:1;
    USHORT Reserved1:2;
    USHORT FunctionGroup:3;
    USHORT Reserved2:9;

} PCI_EXPRESS_ARI_CONTROL_REGISTER, *PPCI_EXPRESS_ARI_CONTROL_REGISTER;

typedef struct _PCI_EXPRESS_ARI_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    PCI_EXPRESS_ARI_CAPABILITY_REGISTER Capability;
    PCI_EXPRESS_ARI_CONTROL_REGISTER Control;

} PCI_EXPRESS_ARI_CAPABILITY, *PPCI_EXPRESS_ARI_CAPABILITY;

typedef union _VIRTUAL_CHANNEL_CAPABILITIES1 {
    struct {
        ULONG ExtendedVCCount:2;
        ULONG RsvdP1:1;
        ULONG LowPriorityExtendedVCCount:2;
        ULONG RsvdP2:1;
        ULONG ReferenceClock:2;
        ULONG PortArbitrationTableEntrySize:2;
        ULONG RsvdP3:20;
    };
    ULONG AsULONG;
} VIRTUAL_CHANNEL_CAPABILITIES1, *PVIRTUAL_CHANNEL_CAPABILITIES1;

typedef union _VIRTUAL_CHANNEL_CAPABILITIES2 {
    struct {
        ULONG VCArbitrationCapability:8;
        ULONG RsvdP:16;
        ULONG VCArbitrationTableOffset:8;
    };
    ULONG AsULONG;
} VIRTUAL_CHANNEL_CAPABILITIES2, *PVIRTUAL_CHANNEL_CAPABILITIES2;

typedef union _VIRTUAL_CHANNEL_CONTROL {
    struct {
        USHORT  LoadVCArbitrationTable:1;
        USHORT  VCArbitrationSelect:3;
        USHORT  RsvdP:12;
    };
    USHORT AsUSHORT;
} VIRTUAL_CHANNEL_CONTROL, *PVIRTUAL_CHANNEL_CONTROL;

typedef union _VIRTUAL_CHANNEL_STATUS {
    struct {
        USHORT  VCArbitrationTableStatus:1;
        USHORT  RsvdZ:15;
    };
    USHORT AsUSHORT;
} VIRTUAL_CHANNEL_STATUS, *PVIRTUAL_CHANNEL_STATUS;

typedef union _VIRTUAL_RESOURCE_CAPABILITY {
    struct {
        ULONG   PortArbitrationCapability:8;
        ULONG   RsvdP1:6;
        ULONG   Undefined:1;
        ULONG   RejectSnoopTransactions:1;
        ULONG   MaximumTimeSlots:7;
        ULONG   RsvdP2:1;
        ULONG   PortArbitrationTableOffset:8;
    };
    ULONG AsULONG;
} VIRTUAL_RESOURCE_CAPABILITY, *PVIRTUAL_RESOURCE_CAPABILITY;

typedef union _VIRTUAL_RESOURCE_CONTROL {
    struct {
        ULONG   TcVcMap:8;
        ULONG   RsvdP1:8;
        ULONG   LoadPortArbitrationTable:1;
        ULONG   PortArbitrationSelect:3;
        ULONG   RsvdP2:4;
        ULONG   VcID:3;
        ULONG   RsvdP3:4;
        ULONG   VcEnable:1;
    };
    ULONG AsULONG;
} VIRTUAL_RESOURCE_CONTROL, *PVIRTUAL_RESOURCE_CONTROL;

typedef union _VIRTUAL_RESOURCE_STATUS {
    struct {
        USHORT  PortArbitrationTableStatus:1;
        USHORT  VcNegotiationPending:1;
        USHORT  RsvdZ:14;
    };
    USHORT AsUSHORT;
} VIRTUAL_RESOURCE_STATUS, *PVIRTUAL_RESOURCE_STATUS;

typedef struct _VIRTUAL_RESOURCE {
    VIRTUAL_RESOURCE_CAPABILITY     Capability;
    VIRTUAL_RESOURCE_CONTROL        Control;
    USHORT                          RsvdP;
    VIRTUAL_RESOURCE_STATUS         Status;
} VIRTUAL_RESOURCE, *PVIRTUAL_RESOURCE;

typedef struct _PCI_EXPRESS_VIRTUAL_CHANNEL_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    VIRTUAL_CHANNEL_CAPABILITIES1   Capabilities1;
    VIRTUAL_CHANNEL_CAPABILITIES2   Capabilities2;
    VIRTUAL_CHANNEL_CONTROL         Control;
    VIRTUAL_CHANNEL_STATUS          Status;
    VIRTUAL_RESOURCE                Resource[8];

} PCI_EXPRESS_VIRTUAL_CHANNEL_CAPABILITY, *PPCI_EXPRESS_VIRTUAL_CHANNEL_CAPABILITY;

typedef struct _PCI_EXPRESS_ATS_CAPABILITY_REGISTER {

    USHORT InvalidateQueueDepth:5;
    USHORT PageAlignedRequest:1;
    USHORT GlobalInvalidateSupported:1;
    USHORT Reserved:9;

} PCI_EXPRESS_ATS_CAPABILITY_REGISTER, *PPCI_EXPRESS_ATS_CAPABILITY_REGISTER;

typedef struct _PCI_EXPRESS_ATS_CONTROL_REGISTER {

    USHORT SmallestTransactionUnit:5;
    USHORT Reserved:10;
    USHORT Enable:1;

} PCI_EXPRESS_ATS_CONTROL_REGISTER, *PPCI_EXPRESS_ATS_CONTROL_REGISTER;

typedef struct _PCI_EXPRESS_ATS_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    PCI_EXPRESS_ATS_CAPABILITY_REGISTER Capability;
    PCI_EXPRESS_ATS_CONTROL_REGISTER Control;

} PCI_EXPRESS_ATS_CAPABILITY, *PPCI_EXPRESS_ATS_CAPABILITY;

typedef union _PCI_EXPRESS_PASID_CAPABILITY_REGISTER {
    struct {
        USHORT Rsvd:1;
        USHORT ExecutePermissionSupported:1;
        USHORT PrivilegedModeSupported:1;
        USHORT Rsvd2:5;
        USHORT MaxPASIDWidth:5;
        USHORT Rsvd3:3;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;
} PCI_EXPRESS_PASID_CAPABILITY_REGISTER, *PPCI_EXPRESS_PASID_CAPABILITY_REGISTER;

typedef union _PCI_EXPRESS_PASID_CONTROL_REGISTER {
    struct {
        USHORT PASIDEnable:1;
        USHORT ExecutePermissionEnable:1;
        USHORT PrivilegedModeEnable:1;
        USHORT Rsvd:13;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;
} PCI_EXPRESS_PASID_CONTROL_REGISTER, *PPCI_EXPRESS_PASID_CONTROL_REGISTER;

typedef struct _PCI_EXPRESS_PASID_CAPABILITY {
    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;
    PCI_EXPRESS_PASID_CAPABILITY_REGISTER Capability;
    PCI_EXPRESS_PASID_CONTROL_REGISTER Control;
} PCI_EXPRESS_PASID_CAPABILITY, *PPCI_EXPRESS_PASID_CAPABILITY;

typedef union _PCI_EXPRESS_PRI_STATUS_REGISTER {
    struct {
        USHORT ResponseFailure:1;
        USHORT UnexpectedPageRequestGroupIndex:1;
        USHORT Rsvd:6;
        USHORT Stopped:1;
        USHORT Rsvd2:6;
        USHORT PrgResponsePasidRequired:1;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;
} PCI_EXPRESS_PRI_STATUS_REGISTER, *PPCI_EXPRESS_PRI_STATUS_REGISTER;

typedef union _PCI_EXPRESS_PRI_CONTROL_REGISTER {
    struct {
        USHORT Enable:1;
        USHORT Reset:1;
        USHORT Rsvd:14;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;
} PCI_EXPRESS_PRI_CONTROL_REGISTER, *PPCI_EXPRESS_PRI_CONTROL_REGISTER;

typedef struct _PCI_EXPRESS_PRI_CAPABILITY {
    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;
    PCI_EXPRESS_PRI_CONTROL_REGISTER Control;
    PCI_EXPRESS_PRI_STATUS_REGISTER Status;
    ULONG PRCapacity;
    ULONG PRAllocation;
} PCI_EXPRESS_PRI_CAPABILITY, *PPCI_EXPRESS_PRI_CAPABILITY;

typedef union _PCI_EXPRESS_UNCORRECTABLE_ERROR_STATUS {

    struct {
        ULONG Undefined:1;
        ULONG Reserved1:3;
        ULONG DataLinkProtocolError:1;
        ULONG SurpriseDownError:1;
        ULONG Reserved2:6;
        ULONG PoisonedTLP:1;
        ULONG FlowControlProtocolError:1;
        ULONG CompletionTimeout:1;
        ULONG CompleterAbort:1;
        ULONG UnexpectedCompletion:1;
        ULONG ReceiverOverflow:1;
        ULONG MalformedTLP:1;
        ULONG ECRCError:1;
        ULONG UnsupportedRequestError:1;
        ULONG AcsViolation:1;
        ULONG UncorrectableInternalError:1;
        ULONG MCBlockedTlp:1;
        ULONG AtomicOpEgressBlocked:1;
        ULONG TlpPrefixBlocked:1;
        ULONG Reserved3:6;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_UNCORRECTABLE_ERROR_STATUS, *PPCI_EXPRESS_UNCORRECTABLE_ERROR_STATUS;

typedef union _PCI_EXPRESS_UNCORRECTABLE_ERROR_MASK {

    struct {
        ULONG Undefined:1;
        ULONG Reserved1:3;
        ULONG DataLinkProtocolError:1;
        ULONG SurpriseDownError:1;
        ULONG Reserved2:6;
        ULONG PoisonedTLP:1;
        ULONG FlowControlProtocolError:1;
        ULONG CompletionTimeout:1;
        ULONG CompleterAbort:1;
        ULONG UnexpectedCompletion:1;
        ULONG ReceiverOverflow:1;
        ULONG MalformedTLP:1;
        ULONG ECRCError:1;
        ULONG UnsupportedRequestError:1;
        ULONG AcsViolation:1;
        ULONG UncorrectableInternalError:1;
        ULONG MCBlockedTlp:1;
        ULONG AtomicOpEgressBlocked:1;
        ULONG TlpPrefixBlocked:1;
        ULONG Reserved3:6;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_UNCORRECTABLE_ERROR_MASK, *PPCI_EXPRESS_UNCORRECTABLE_ERROR_MASK;

typedef union _PCI_EXPRESS_UNCORRECTABLE_ERROR_SEVERITY {

    struct {
        ULONG Undefined:1;
        ULONG Reserved1:3;
        ULONG DataLinkProtocolError:1;
        ULONG SurpriseDownError:1;
        ULONG Reserved2:6;
        ULONG PoisonedTLP:1;
        ULONG FlowControlProtocolError:1;
        ULONG CompletionTimeout:1;
        ULONG CompleterAbort:1;
        ULONG UnexpectedCompletion:1;
        ULONG ReceiverOverflow:1;
        ULONG MalformedTLP:1;
        ULONG ECRCError:1;
        ULONG UnsupportedRequestError:1;
        ULONG AcsViolation:1;
        ULONG UncorrectableInternalError:1;
        ULONG MCBlockedTlp:1;
        ULONG AtomicOpEgressBlocked:1;
        ULONG TlpPrefixBlocked:1;
        ULONG Reserved3:6;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_UNCORRECTABLE_ERROR_SEVERITY, *PPCI_EXPRESS_UNCORRECTABLE_ERROR_SEVERITY;

typedef union _PCI_EXPRESS_CORRECTABLE_ERROR_STATUS {

    struct {
        ULONG ReceiverError:1;
        ULONG Reserved1:5;
        ULONG BadTLP:1;
        ULONG BadDLLP:1;
        ULONG ReplayNumRollover:1;
        ULONG Reserved2:3;
        ULONG ReplayTimerTimeout:1;
        ULONG AdvisoryNonFatalError:1;
        ULONG CorrectedInternalError:1;
        ULONG HeaderLogOverflow:1;
        ULONG Reserved3:16;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_CORRECTABLE_ERROR_STATUS, *PPCI_CORRECTABLE_ERROR_STATUS;

typedef union _PCI_EXPRESS_CORRECTABLE_ERROR_MASK {

    struct {
        ULONG ReceiverError:1;
        ULONG Reserved1:5;
        ULONG BadTLP:1;
        ULONG BadDLLP:1;
        ULONG ReplayNumRollover:1;
        ULONG Reserved2:3;
        ULONG ReplayTimerTimeout:1;
        ULONG AdvisoryNonFatalError:1;
        ULONG CorrectedInternalError:1;
        ULONG HeaderLogOverflow:1;
        ULONG Reserved3:16;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_CORRECTABLE_ERROR_MASK, *PPCI_CORRECTABLE_ERROR_MASK;

typedef union _PCI_EXPRESS_AER_CAPABILITIES {

    struct {
        ULONG FirstErrorPointer:5;
        ULONG ECRCGenerationCapable:1;
        ULONG ECRCGenerationEnable:1;
        ULONG ECRCCheckCapable:1;
        ULONG ECRCCheckEnable:1;
        ULONG MultipleHeaderRecordingCapable:1;
        ULONG MultipleHeaderRecordingEnable:1;
        ULONG TlpPrefixLogPresent:1;
        ULONG Reserved:20;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_AER_CAPABILITIES, *PPCI_EXPRESS_AER_CAPABILITIES;

typedef union _PCI_EXPRESS_ROOT_ERROR_COMMAND {

    struct {
        ULONG CorrectableErrorReportingEnable:1;
        ULONG NonFatalErrorReportingEnable:1;
        ULONG FatalErrorReportingEnable:1;
        ULONG Reserved:29;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_ROOT_ERROR_COMMAND, *PPCI_EXPRESS_ROOT_ERROR_COMMAND;

typedef union _PCI_EXPRESS_ROOT_ERROR_STATUS {

    struct {
        ULONG CorrectableErrorReceived:1;
        ULONG MultipleCorrectableErrorsReceived:1;
        ULONG UncorrectableErrorReceived:1;
        ULONG MultipleUncorrectableErrorsReceived:1;
        ULONG FirstUncorrectableFatal:1;
        ULONG NonFatalErrorMessagesReceived:1;
        ULONG FatalErrorMessagesReceived:1;
        ULONG Reserved:20;
        ULONG AdvancedErrorInterruptMessageNumber:5;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_ROOT_ERROR_STATUS, *PPCI_EXPRESS_ROOT_ERROR_STATUS;

typedef union _PCI_EXPRESS_ERROR_SOURCE_ID {

    struct {
        USHORT CorrectableSourceIdFun:3;
        USHORT CorrectableSourceIdDev:5;
        USHORT CorrectableSourceIdBus:8;
        USHORT UncorrectableSourceIdFun:3;
        USHORT UncorrectableSourceIdDev:5;
        USHORT UncorrectableSourceIdBus:8;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_ERROR_SOURCE_ID, *PPCI_EXPRESS_ERROR_SOURCE_ID;

typedef union _PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_STATUS {

    struct {
        ULONG TargetAbortOnSplitCompletion:1;
        ULONG MasterAbortOnSplitCompletion:1;
        ULONG ReceivedTargetAbort:1;
        ULONG ReceivedMasterAbort:1;
        ULONG RsvdZ:1;
        ULONG UnexpectedSplitCompletionError:1;
        ULONG UncorrectableSplitCompletion:1;
        ULONG UncorrectableDataError:1;
        ULONG UncorrectableAttributeError:1;
        ULONG UncorrectableAddressError:1;
        ULONG DelayedTransactionDiscardTimerExpired:1;
        ULONG PERRAsserted:1;
        ULONG SERRAsserted:1;
        ULONG InternalBridgeError:1;
        ULONG Reserved:18;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_STATUS,
  *PPCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_STATUS;

typedef union _PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_MASK {

    struct {
        ULONG TargetAbortOnSplitCompletion:1;
        ULONG MasterAbortOnSplitCompletion:1;
        ULONG ReceivedTargetAbort:1;
        ULONG ReceivedMasterAbort:1;
        ULONG RsvdZ:1;
        ULONG UnexpectedSplitCompletionError:1;
        ULONG UncorrectableSplitCompletion:1;
        ULONG UncorrectableDataError:1;
        ULONG UncorrectableAttributeError:1;
        ULONG UncorrectableAddressError:1;
        ULONG DelayedTransactionDiscardTimerExpired:1;
        ULONG PERRAsserted:1;
        ULONG SERRAsserted:1;
        ULONG InternalBridgeError:1;
        ULONG Reserved:18;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_MASK,
  *PPCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_MASK;

typedef union _PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_SEVERITY {

    struct {
        ULONG TargetAbortOnSplitCompletion:1;
        ULONG MasterAbortOnSplitCompletion:1;
        ULONG ReceivedTargetAbort:1;
        ULONG ReceivedMasterAbort:1;
        ULONG RsvdZ:1;
        ULONG UnexpectedSplitCompletionError:1;
        ULONG UncorrectableSplitCompletion:1;
        ULONG UncorrectableDataError:1;
        ULONG UncorrectableAttributeError:1;
        ULONG UncorrectableAddressError:1;
        ULONG DelayedTransactionDiscardTimerExpired:1;
        ULONG PERRAsserted:1;
        ULONG SERRAsserted:1;
        ULONG InternalBridgeError:1;
        ULONG Reserved:18;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_SEVERITY,
  *PPCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_SEVERITY;

typedef union _PCI_EXPRESS_SEC_AER_CAPABILITIES {

    struct {
        ULONG SecondaryUncorrectableFirstErrorPtr:5;
        ULONG Reserved:27;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_SEC_AER_CAPABILITIES, *PPCI_EXPRESS_SEC_AER_CAPABILITIES;

#define ROOT_CMD_ENABLE_CORRECTABLE_ERROR_REPORTING  0x00000001
#define ROOT_CMD_ENABLE_NONFATAL_ERROR_REPORTING     0x00000002
#define ROOT_CMD_ENABLE_FATAL_ERROR_REPORTING        0x00000004

#define ROOT_CMD_ERROR_REPORTING_ENABLE_MASK \
    (ROOT_CMD_ENABLE_FATAL_ERROR_REPORTING | \
     ROOT_CMD_ENABLE_NONFATAL_ERROR_REPORTING | \
     ROOT_CMD_ENABLE_CORRECTABLE_ERROR_REPORTING)

typedef struct _PCI_EXPRESS_AER_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    PCI_EXPRESS_UNCORRECTABLE_ERROR_STATUS UncorrectableErrorStatus;
    PCI_EXPRESS_UNCORRECTABLE_ERROR_MASK UncorrectableErrorMask;
    PCI_EXPRESS_UNCORRECTABLE_ERROR_SEVERITY UncorrectableErrorSeverity;
    PCI_EXPRESS_CORRECTABLE_ERROR_STATUS CorrectableErrorStatus;
    PCI_EXPRESS_CORRECTABLE_ERROR_MASK CorrectableErrorMask;
    PCI_EXPRESS_AER_CAPABILITIES CapabilitiesAndControl;
    ULONG HeaderLog[4];
    PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_STATUS SecUncorrectableErrorStatus;
    PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_MASK SecUncorrectableErrorMask;
    PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_SEVERITY SecUncorrectableErrorSeverity;
    PCI_EXPRESS_SEC_AER_CAPABILITIES SecCapabilitiesAndControl;
    ULONG SecHeaderLog[4];

} PCI_EXPRESS_AER_CAPABILITY, *PPCI_EXPRESS_AER_CAPABILITY;

typedef struct _PCI_EXPRESS_ROOTPORT_AER_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    PCI_EXPRESS_UNCORRECTABLE_ERROR_STATUS UncorrectableErrorStatus;
    PCI_EXPRESS_UNCORRECTABLE_ERROR_MASK UncorrectableErrorMask;
    PCI_EXPRESS_UNCORRECTABLE_ERROR_SEVERITY UncorrectableErrorSeverity;
    PCI_EXPRESS_CORRECTABLE_ERROR_STATUS CorrectableErrorStatus;
    PCI_EXPRESS_CORRECTABLE_ERROR_MASK CorrectableErrorMask;
    PCI_EXPRESS_AER_CAPABILITIES CapabilitiesAndControl;
    ULONG HeaderLog[4];
    PCI_EXPRESS_ROOT_ERROR_COMMAND RootErrorCommand;
    PCI_EXPRESS_ROOT_ERROR_STATUS RootErrorStatus;
    PCI_EXPRESS_ERROR_SOURCE_ID ErrorSourceId;

} PCI_EXPRESS_ROOTPORT_AER_CAPABILITY, *PPCI_EXPRESS_ROOTPORT_AER_CAPABILITY;

typedef struct _PCI_EXPRESS_BRIDGE_AER_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    PCI_EXPRESS_UNCORRECTABLE_ERROR_STATUS UncorrectableErrorStatus;
    PCI_EXPRESS_UNCORRECTABLE_ERROR_MASK UncorrectableErrorMask;
    PCI_EXPRESS_UNCORRECTABLE_ERROR_SEVERITY UncorrectableErrorSeverity;
    PCI_EXPRESS_CORRECTABLE_ERROR_STATUS CorrectableErrorStatus;
    PCI_EXPRESS_CORRECTABLE_ERROR_MASK CorrectableErrorMask;
    PCI_EXPRESS_AER_CAPABILITIES CapabilitiesAndControl;
    ULONG HeaderLog[4];
    PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_STATUS SecUncorrectableErrorStatus;
    PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_MASK SecUncorrectableErrorMask;
    PCI_EXPRESS_SEC_UNCORRECTABLE_ERROR_SEVERITY SecUncorrectableErrorSeverity;
    PCI_EXPRESS_SEC_AER_CAPABILITIES SecCapabilitiesAndControl;
    ULONG SecHeaderLog[4];

} PCI_EXPRESS_BRIDGE_AER_CAPABILITY, *PPCI_EXPRESS_BRIDGE_AER_CAPABILITY;

typedef union _PCI_EXPRESS_ACS_CAPABILITY_REGISTER {

    struct {
        USHORT SourceValidation:1;
        USHORT TranslationBlocking:1;
        USHORT RequestRedirect:1;
        USHORT CompletionRedirect:1;
        USHORT UpstreamForwarding:1;
        USHORT EgressControl:1;
        USHORT DirectTranslation:1;
        USHORT Reserved:1;
        USHORT EgressControlVectorSize:8;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_ACS_CAPABILITY_REGISTER, *PPCI_EXPRESS_ACS_CAPABILITY_REGISTER;

typedef union _PCI_EXPRESS_ACS_CONTROL {

    struct {
        USHORT SourceValidation:1;
        USHORT TranslationBlocking:1;
        USHORT RequestRedirect:1;
        USHORT CompletionRedirect:1;
        USHORT UpstreamForwarding:1;
        USHORT EgressControl:1;
        USHORT DirectTranslation:1;
        USHORT Reserved:9;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_ACS_CONTROL, *PPCI_EXPRESS_ACS_CONTROL;

typedef struct _PCI_EXPRESS_ACS_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER  Header;

    PCI_EXPRESS_ACS_CAPABILITY_REGISTER      Capability;
    PCI_EXPRESS_ACS_CONTROL                 Control;

    ULONG                                   EgressControl[1];
} PCI_EXPRESS_ACS_CAPABILITY, *PPCI_EXPRESS_ACS_CAPABILITY ;

typedef union _PCI_EXPRESS_SRIOV_CAPS {

    struct {
        ULONG VFMigrationCapable:1;
        ULONG Reserved1:20;
        ULONG VFMigrationInterruptNumber:11;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_SRIOV_CAPS, *PPCI_EXPRESS_SRIOV_CAPS;

typedef union _PCI_EXPRESS_SRIOV_CONTROL {

    struct {
        USHORT VFEnable:1;
        USHORT VFMigrationEnable:1;
        USHORT VFMigrationInterruptEnable:1;
        USHORT VFMemorySpaceEnable:1;
        USHORT ARICapableHierarchy:1;
        USHORT Reserved1:11;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_SRIOV_CONTROL, *PPCI_EXPRESS_SRIOV_CONTROL;

typedef union _PCI_EXPRESS_SRIOV_STATUS {

    struct {
        USHORT VFMigrationStatus:1;
        USHORT Reserved1:15;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_SRIOV_STATUS, *PPCI_EXPRESS_SRIOV_STATUS;

typedef union _PCI_EXPRESS_SRIOV_MIGRATION_STATE_ARRAY {

    struct {
        ULONG VFMigrationStateBIR:3;
        ULONG VFMigrationStateOffset:29;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_SRIOV_MIGRATION_STATE_ARRAY, *PPCI_EXPRESS_SRIOV_MIGRATION_STATE_ARRAY;

typedef struct _PCI_EXPRESS_SRIOV_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER  Header;

    PCI_EXPRESS_SRIOV_CAPS                  SRIOVCapabilities;
    PCI_EXPRESS_SRIOV_CONTROL               SRIOVControl;
    PCI_EXPRESS_SRIOV_STATUS                SRIOVStatus;
    USHORT                                  InitialVFs;
    USHORT                                  TotalVFs;
    USHORT                                  NumVFs;
    UCHAR                                   FunctionDependencyLink;
    UCHAR                                   RsvdP1;
    USHORT                                  FirstVFOffset;
    USHORT                                  VFStride;
    USHORT                                  RsvdP2;
    USHORT                                  VFDeviceId;
    ULONG                                   SupportedPageSizes;
    ULONG                                   SystemPageSize;
    ULONG                                   BaseAddresses[PCI_TYPE0_ADDRESSES];
    PCI_EXPRESS_SRIOV_MIGRATION_STATE_ARRAY VFMigrationStateArrayOffset;

} PCI_EXPRESS_SRIOV_CAPABILITY, *PPCI_EXPRESS_SRIOV_CAPABILITY;

#define PCI_CLASS_PRE_20                    0x00
#define PCI_CLASS_MASS_STORAGE_CTLR         0x01
#define PCI_CLASS_NETWORK_CTLR              0x02
#define PCI_CLASS_DISPLAY_CTLR              0x03
#define PCI_CLASS_MULTIMEDIA_DEV            0x04
#define PCI_CLASS_MEMORY_CTLR               0x05
#define PCI_CLASS_BRIDGE_DEV                0x06
#define PCI_CLASS_SIMPLE_COMMS_CTLR         0x07
#define PCI_CLASS_BASE_SYSTEM_DEV           0x08
#define PCI_CLASS_INPUT_DEV                 0x09
#define PCI_CLASS_DOCKING_STATION           0x0a
#define PCI_CLASS_PROCESSOR                 0x0b
#define PCI_CLASS_SERIAL_BUS_CTLR           0x0c
#define PCI_CLASS_WIRELESS_CTLR             0x0d
#define PCI_CLASS_INTELLIGENT_IO_CTLR       0x0e
#define PCI_CLASS_SATELLITE_COMMS_CTLR      0x0f
#define PCI_CLASS_ENCRYPTION_DECRYPTION     0x10
#define PCI_CLASS_DATA_ACQ_SIGNAL_PROC      0x11

#define PCI_CLASS_NOT_DEFINED               0xff

#define PCI_SUBCLASS_PRE_20_NON_VGA         0x00
#define PCI_SUBCLASS_PRE_20_VGA             0x01

#define PCI_SUBCLASS_MSC_SCSI_BUS_CTLR      0x00
#define PCI_SUBCLASS_MSC_IDE_CTLR           0x01
#define PCI_SUBCLASS_MSC_FLOPPY_CTLR        0x02
#define PCI_SUBCLASS_MSC_IPI_CTLR           0x03
#define PCI_SUBCLASS_MSC_RAID_CTLR          0x04
#define PCI_SUBCLASS_MSC_AHCI_CTLR          0x06
#define PCI_SUBCLASS_MSC_NVM_CTLR           0x08
#define PCI_SUBCLASS_MSC_OTHER              0x80

#define PCI_PROGRAMMING_INTERFACE_MSC_NVM_EXPRESS   0x02

#define PCI_SUBCLASS_NET_ETHERNET_CTLR      0x00
#define PCI_SUBCLASS_NET_TOKEN_RING_CTLR    0x01
#define PCI_SUBCLASS_NET_FDDI_CTLR          0x02
#define PCI_SUBCLASS_NET_ATM_CTLR           0x03
#define PCI_SUBCLASS_NET_ISDN_CTLR          0x04
#define PCI_SUBCLASS_NET_OTHER              0x80

#define PCI_SUBCLASS_VID_VGA_CTLR           0x00
#define PCI_SUBCLASS_VID_XGA_CTLR           0x01
#define PCI_SUBLCASS_VID_3D_CTLR            0x02
#define PCI_SUBCLASS_VID_OTHER              0x80

#define PCI_SUBCLASS_MM_VIDEO_DEV           0x00
#define PCI_SUBCLASS_MM_AUDIO_DEV           0x01
#define PCI_SUBCLASS_MM_TELEPHONY_DEV       0x02
#define PCI_SUBCLASS_MM_OTHER               0x80

#define PCI_SUBCLASS_MEM_RAM                0x00
#define PCI_SUBCLASS_MEM_FLASH              0x01
#define PCI_SUBCLASS_MEM_OTHER              0x80

#define PCI_SUBCLASS_BR_HOST                0x00
#define PCI_SUBCLASS_BR_ISA                 0x01
#define PCI_SUBCLASS_BR_EISA                0x02
#define PCI_SUBCLASS_BR_MCA                 0x03
#define PCI_SUBCLASS_BR_PCI_TO_PCI          0x04
#define PCI_SUBCLASS_BR_PCMCIA              0x05
#define PCI_SUBCLASS_BR_NUBUS               0x06
#define PCI_SUBCLASS_BR_CARDBUS             0x07
#define PCI_SUBCLASS_BR_RACEWAY             0x08
#define PCI_SUBCLASS_BR_OTHER               0x80

#define PCI_SUBCLASS_COM_SERIAL             0x00
#define PCI_SUBCLASS_COM_PARALLEL           0x01
#define PCI_SUBCLASS_COM_MULTIPORT          0x02
#define PCI_SUBCLASS_COM_MODEM              0x03
#define PCI_SUBCLASS_COM_OTHER              0x80

#define PCI_SUBCLASS_SYS_INTERRUPT_CTLR     0x00
#define PCI_SUBCLASS_SYS_DMA_CTLR           0x01
#define PCI_SUBCLASS_SYS_SYSTEM_TIMER       0x02
#define PCI_SUBCLASS_SYS_REAL_TIME_CLOCK    0x03
#define PCI_SUBCLASS_SYS_GEN_HOTPLUG_CTLR   0x04
#define PCI_SUBCLASS_SYS_SDIO_CTRL          0x05
#define PCI_SUBCLASS_SYS_OTHER              0x80

#define PCI_SUBCLASS_INP_KEYBOARD           0x00
#define PCI_SUBCLASS_INP_DIGITIZER          0x01
#define PCI_SUBCLASS_INP_MOUSE              0x02
#define PCI_SUBCLASS_INP_SCANNER            0x03
#define PCI_SUBCLASS_INP_GAMEPORT           0x04
#define PCI_SUBCLASS_INP_OTHER              0x80

#define PCI_SUBCLASS_DOC_GENERIC            0x00
#define PCI_SUBCLASS_DOC_OTHER              0x80

#define PCI_SUBCLASS_PROC_386               0x00
#define PCI_SUBCLASS_PROC_486               0x01
#define PCI_SUBCLASS_PROC_PENTIUM           0x02
#define PCI_SUBCLASS_PROC_ALPHA             0x10
#define PCI_SUBCLASS_PROC_POWERPC           0x20
#define PCI_SUBCLASS_PROC_COPROCESSOR       0x40

#define PCI_SUBCLASS_SB_IEEE1394            0x00
#define PCI_SUBCLASS_SB_ACCESS              0x01
#define PCI_SUBCLASS_SB_SSA                 0x02
#define PCI_SUBCLASS_SB_USB                 0x03
#define PCI_SUBCLASS_SB_FIBRE_CHANNEL       0x04
#define PCI_SUBCLASS_SB_SMBUS               0x05
#define PCI_SUBCLASS_SB_THUNDERBOLT         0x0A

#define PCI_SUBCLASS_WIRELESS_IRDA          0x00
#define PCI_SUBCLASS_WIRELESS_CON_IR        0x01
#define PCI_SUBCLASS_WIRELESS_RF            0x10
#define PCI_SUBCLASS_WIRELESS_OTHER         0x80

#define PCI_SUBCLASS_INTIO_I2O              0x00

#define PCI_SUBCLASS_SAT_TV                 0x01
#define PCI_SUBCLASS_SAT_AUDIO              0x02
#define PCI_SUBCLASS_SAT_VOICE              0x03
#define PCI_SUBCLASS_SAT_DATA               0x04

#define PCI_SUBCLASS_CRYPTO_NET_COMP        0x00
#define PCI_SUBCLASS_CRYPTO_ENTERTAINMENT   0x10
#define PCI_SUBCLASS_CRYPTO_OTHER           0x80

#define PCI_SUBCLASS_DASP_DPIO              0x00
#define PCI_SUBCLASS_DASP_OTHER             0x80

#define PCI_ADDRESS_IO_SPACE                0x00000001  // (ro)
#define PCI_ADDRESS_MEMORY_TYPE_MASK        0x00000006  // (ro)
#define PCI_ADDRESS_MEMORY_PREFETCHABLE     0x00000008  // (ro)

#define PCI_ADDRESS_IO_ADDRESS_MASK         0xfffffffc
#define PCI_ADDRESS_MEMORY_ADDRESS_MASK     0xfffffff0
#define PCI_ADDRESS_ROM_ADDRESS_MASK        0xfffff800

#define PCI_TYPE_32BIT      0
#define PCI_TYPE_20BIT      2
#define PCI_TYPE_64BIT      4

#define PCI_ROMADDRESS_ENABLED              0x00000001

typedef VOID
(*PciPin2Line) (
    _In_ struct _BUS_HANDLER  *BusHandler,
    _In_ struct _BUS_HANDLER  *RootHandler,
    _In_ PCI_SLOT_NUMBER      SlotNumber,
    _In_ PPCI_COMMON_CONFIG   PciData
    );

typedef VOID
(*PciLine2Pin) (
    _In_ struct _BUS_HANDLER  *BusHandler,
    _In_ struct _BUS_HANDLER  *RootHandler,
    _In_ PCI_SLOT_NUMBER      SlotNumber,
    _In_ PPCI_COMMON_CONFIG   PciNewData,
    _In_ PPCI_COMMON_CONFIG   PciOldData
    );

typedef VOID
(*PciReadWriteConfig) (
    _In_ struct _BUS_HANDLER *BusHandler,
    _In_ PCI_SLOT_NUMBER Slot,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Offset,
    _In_ ULONG Length
    );

#define PCI_DATA_TAG            ' ICP'
#define PCI_DATA_VERSION        1

typedef struct _PCIBUSDATA {
    ULONG                   Tag;
    ULONG                   Version;
    PciReadWriteConfig      ReadConfig;
    PciReadWriteConfig      WriteConfig;
    PciPin2Line             Pin2Line;
    PciLine2Pin             Line2Pin;
    PCI_SLOT_NUMBER         ParentSlot;
    PVOID                   Reserved[4];
} PCIBUSDATA, *PPCIBUSDATA;

typedef union _PCI_EXPRESS_LTR_MAX_LATENCY_REGISTER {

    struct {

        ULONG MaxSnoopLatencyValue:10;
        ULONG MaxSnoopLatencyScale:3;
        ULONG Rsvd:2;
        ULONG MaxSnoopRequirement:1;

        ULONG MaxNoSnoopLatencyValue:10;
        ULONG MaxNoSnoopLatencyScale:3;
        ULONG Rsvd2:2;
        ULONG MaxNoSnoopRequirement:1;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_LTR_MAX_LATENCY_REGISTER, *PPCI_EXPRESS_LTR_MAX_LATENCY_REGISTER;

typedef struct _PCI_EXPRESS_LTR_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    PCI_EXPRESS_LTR_MAX_LATENCY_REGISTER Latency;

} PCI_EXPRESS_LTR_CAPABILITY, *PPCI_EXPRESS_LTR_CAPABILITY;

#define PCI_EXPRESS_TPH_ST_LOCATION_NONE 0
#define PCI_EXPRESS_TPH_ST_LOCATION_TPH_CAPABILITY 1
#define PCI_EXPRESS_TPH_ST_LOCATION_MSIX_TABLE 2
#define PCI_EXPRESS_TPH_ST_LOCATION_RESERVED 3

typedef union _PCI_EXPRESS_TPH_REQUESTER_CAPABILITY_REGISTER {

    struct {

        ULONG NoStModeSupported:1;
        ULONG InteruptVectorModeSupported:1;
        ULONG DeviceSpecificModeSupported:1;
        ULONG Rsvd:5;
        ULONG ExtendedTPHRequesterSupported:1;
        ULONG StTableLocation:2;
        ULONG Rsvd2:5;
        ULONG StTableSize:11;
        ULONG Rsvd3:5;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_TPH_REQUESTER_CAPABILITY_REGISTER, *PPCI_EXPRESS_TPH_REQUESTER_CAPABILITY_REGISTER;

typedef union _PCI_EXPRESS_TPH_REQUESTER_CONTROL_REGISTER {

    struct {

        ULONG StModeSelect:3;
        ULONG Rsvd:5;
        ULONG TphRequesterEnable:2;
        ULONG Rsvd2:22;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_TPH_REQUESTER_CONTROL_REGISTER, *PPCI_EXPRESS_TPH_REQUESTER_CONTROL_REGISTER;

typedef union _PCI_EXPRESS_TPH_ST_TABLE_ENTRY {

    struct {

        USHORT LowerEntry:8;
        USHORT UpperEntry:8;
    } DUMMYSTRUCTNAME;

    USHORT AsUSHORT;

} PCI_EXPRESS_TPH_ST_TABLE_ENTRY, *PPCI_EXPRESS_TPH_ST_TABLE_ENTRY;

typedef struct _PCI_EXPRESS_TPH_REQUESTER_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    PCI_EXPRESS_TPH_REQUESTER_CAPABILITY_REGISTER RequesterCapability;
    PCI_EXPRESS_TPH_REQUESTER_CONTROL_REGISTER RequesterControl;

} PCI_EXPRESS_TPH_REQUESTER_CAPABILITY, *PPCI_EXPRESS_TPH_REQUESTER_CAPABILITY;

typedef union _PCI_EXPRESS_L1_PM_SS_CAPABILITIES_REGISTER {

    struct {
        ULONG PciPmL12Supported:1;
        ULONG PciPmL11Supported:1;
        ULONG AspmL12Supported:1;
        ULONG AspmL11Supported:1;
        ULONG L1PmSsSupported:1;
        ULONG Rsvd:3;
        ULONG PortCommonModeRestoreTime:8;
        ULONG PortTPowerOnScale:2;
        ULONG Rsvd2:1;
        ULONG PortTPowerOnValue:5;
        ULONG Rsvd3:8;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_L1_PM_SS_CAPABILITIES_REGISTER, *PPCI_EXPRESS_L1_PM_SS_CAPABILITIES_REGISTER;

typedef union _PCI_EXPRESS_L1_PM_SS_CONTROL_1_REGISTER {

    struct {
        ULONG PciPmL12Enabled:1;
        ULONG PciPmL11Enabled:1;
        ULONG AspmL12Enabled:1;
        ULONG AspmL11Enabled:1;
        ULONG Rsvd:4;
        ULONG CommonModeRestoreTime:8;
        ULONG LtrL12ThresholdValue:10;
        ULONG Rsvd2:3;
        ULONG LtrL12ThresholdScale:3;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_L1_PM_SS_CONTROL_1_REGISTER, *PPCI_EXPRESS_L1_PM_SS_CONTROL_1_REGISTER;

typedef union _PCI_EXPRESS_L1_PM_SS_CONTROL_2_REGISTER {

    struct {

        ULONG TPowerOnScale:2;
        ULONG Rsvd:1;
        ULONG TPowerOnValue:5;
        ULONG Rsvd2:24;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_L1_PM_SS_CONTROL_2_REGISTER, *PPCI_EXPRESS_L1_PM_SS_CONTROL_2_REGISTER;

typedef struct _PCI_EXPRESS_L1_PM_SS_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    PCI_EXPRESS_L1_PM_SS_CAPABILITIES_REGISTER L1PmSsCapabilities;
    PCI_EXPRESS_L1_PM_SS_CONTROL_1_REGISTER L1PmSsControl1;
    PCI_EXPRESS_L1_PM_SS_CONTROL_2_REGISTER L1PmSsControl2;

} PCI_EXPRESS_L1_PM_SS_CAPABILITY, *PPCI_EXPRESS_L1_PM_SS_CAPABILITY;

typedef union _PCI_EXPRESS_RESIZABLE_BAR_CAPABILITY_REGISTER {
    struct {
        ULONG Rsvd:4;
        ULONG SizesSupported:20;
        ULONG Rsvd2:8;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_RESIZABLE_BAR_CAPABILITY_REGISTER, *PPCI_EXPRESS_RESIZABLE_BAR_CAPABILITY_REGISTER;

typedef union _PCI_EXPRESS_RESIZABLE_BAR_CONTROL_REGISTER {
    struct {

        ULONG BarIndex:3;
        ULONG Rsvd:2;
        ULONG NumberOfResizableBars:3;
        ULONG BarSize:5;
        ULONG Rsvd2:19;
    } DUMMYSTRUCTNAME;

    ULONG AsULONG;

} PCI_EXPRESS_RESIZABLE_BAR_CONTROL_REGISTER, *PPCI_EXPRESS_RESIZABLE_BAR_CONTROL_REGISTER;

typedef struct _PCI_EXPRESS_RESIZABLE_BAR_ENTRY {
    PCI_EXPRESS_RESIZABLE_BAR_CAPABILITY_REGISTER Capability;
    PCI_EXPRESS_RESIZABLE_BAR_CONTROL_REGISTER Control;
} PCI_EXPRESS_RESIZABLE_BAR_ENTRY, *PPCI_EXPRESS_RESIZABLE_BAR_ENTRY;

typedef struct _PCI_EXPRESS_RESIZABLE_BAR_CAPABILITY {

    PCI_EXPRESS_ENHANCED_CAPABILITY_HEADER Header;

    PCI_EXPRESS_RESIZABLE_BAR_ENTRY Entry[6];

} PCI_EXPRESS_RESIZABLE_BAR_CAPABILITY, *PPCI_EXPRESS_RESIZABLE_BAR_CAPABILITY;

#endif // _PCI_X_

#pragma warning(push)
#pragma warning(disable:4214) // nonstandard extensions

typedef struct _PCI_REGISTRY_INFO {
    UCHAR       MajorRevision;
    UCHAR       MinorRevision;
    UCHAR       NoBuses;
    UCHAR       HardwareMechanism;
} PCI_REGISTRY_INFO, *PPCI_REGISTRY_INFO;

#define PciBridgeIO2Base(a,b)   \
        ( ((a >> 4) << 12) + (((a & 0xf) == 1) ? (b << 16) : 0) )

#define PciBridgeIO2Limit(a,b)  (PciBridgeIO2Base(a,b) | 0xfff)

#define PciBridgeMemory2Base(a)  (ULONG) ((a & 0xfff0) << 16)
#define PciBridgeMemory2Limit(a) (PciBridgeMemory2Base(a) | 0xfffff)

#define PciBridgePrefetch2Base(a, b) \
       ( ((a & 0xfff0) << 16) + (((a & 0x1) == 1) ? ((ULONG64)b << 32) : 0) )

#define PciBridgePrefetch2Limit(a, b) (PciBridgePrefetch2Base(a,b) | 0xfffff)

#define PCI_ENABLE_BRIDGE_PARITY_ERROR        0x0001
#define PCI_ENABLE_BRIDGE_SERR                0x0002
#define PCI_ENABLE_BRIDGE_ISA                 0x0004
#define PCI_ENABLE_BRIDGE_VGA                 0x0008
#define PCI_ENABLE_BRIDGE_MASTER_ABORT_SERR   0x0020
#define PCI_ASSERT_BRIDGE_RESET               0x0040
#define PCI_ENABLE_BRIDGE_VGA_16BIT           0x0010

#define PCI_ENABLE_BRIDGE_FAST_BACK_TO_BACK   0x0080

#define PCI_ENABLE_CARDBUS_IRQ_ROUTING        0x0080
#define PCI_ENABLE_CARDBUS_MEM0_PREFETCH      0x0100
#define PCI_ENABLE_CARDBUS_MEM1_PREFETCH      0x0200
#define PCI_ENABLE_CARDBUS_WRITE_POSTING      0x0400

typedef struct {

      PCI_CAPABILITIES_HEADER Header;

      struct _PCI_MSI_MESSAGE_CONTROL {
          USHORT MSIEnable:1;
          USHORT MultipleMessageCapable:3;
          USHORT MultipleMessageEnable:3;
          USHORT CapableOf64Bits:1;
          USHORT PerVectorMaskCapable:1;
          USHORT Reserved:7;
      } MessageControl;

      union {

          struct _PCI_MSI_MESSAGE_ADDRESS {
              ULONG Reserved:2;              // always zero, DWORD aligned address
              ULONG Address:30;
          } Register;

          ULONG Raw;

      } MessageAddressLower;

      union {

          struct {
              USHORT MessageData;
              USHORT Reserved;
              ULONG MaskBits;
              ULONG PendingBits;
          } Option32Bit;

          struct {
              ULONG MessageAddressUpper;
              USHORT MessageData;
              USHORT Reserved;
              ULONG MaskBits;
              ULONG PendingBits;
          } Option64Bit;
      };

} PCI_MSI_CAPABILITY, *PPCI_MSI_CAPABILITY;

#define MSIX_TABLE_OFFSET_MASK              0xfffffff8

#define MSIX_PBA_TABLE_ENTRY_SIZE               8
#define MSIX_PENDING_BITS_IN_PBA_TABLE_ENTRY   64

typedef struct {

    union {

        struct {
            ULONG BaseIndexRegister:3;
            ULONG Reserved:29;
        };

        ULONG TableOffset;
    };

} MSIX_TABLE_POINTER, *PMSIX_TABLE_POINTER;

typedef struct {

    PHYSICAL_ADDRESS MessageAddress;
    ULONG MessageData;

    struct {
        ULONG Mask:1;
        ULONG Reserved:15;
        ULONG StLower:8;
        ULONG StUpper:8;
    } VectorControl;

} PCI_MSIX_TABLE_ENTRY, *PPCI_MSIX_TABLE_ENTRY;

typedef struct {

      PCI_CAPABILITIES_HEADER Header;

      struct {
          USHORT TableSize:11;
          USHORT Reserved:3;
          USHORT FunctionMask:1;
          USHORT MSIXEnable:1;
      } MessageControl;

      MSIX_TABLE_POINTER  MessageTable;
      MSIX_TABLE_POINTER  PBATable;   // Pending Bit Array

} PCI_MSIX_CAPABILITY, *PPCI_MSIX_CAPABILITY;

typedef enum {
    HTSlavePrimary0 = 0,
    HTSlavePrimary1 = 1,
    HTSlavePrimary2 = 2,
    HTSlavePrimary3 = 3,
    HTHostSecondary0 = 4,
    HTHostSecondary1 = 5,
    HTHostSecondary2 = 6,
    HTHostSecondary3 = 7,
    HTInterruptDiscoveryConfig = 0x10,
    HTAddressMapping = 0x14,
    HTInterruptMsiMapping = 0x15
} PCI_HT_CapabilitiesType, *PPCI_HT_CapabilitiesType;

typedef struct {

    PCI_CAPABILITIES_HEADER Header;

    union {
        struct {
            USHORT Reserved:11;
            USHORT CapabilityType:5; // use PCI_HT_CapabilitiesType
        } Generic;

        struct {
            USHORT Index:8;
            USHORT Reserved:3;
            USHORT CapabilityType:5; // use PCI_HT_CapabilitiesType
        } Interrupt;

        struct {
            USHORT Enable:1;
            USHORT Fixed:1;
            USHORT Reserved:9;
            USHORT CapabilityType:5;
        } MsiMapping;

    } Command;

    union {

        ULONG InterruptDataPort;

        struct {
            ULONG Reserved:20;
            ULONG AddressLow:12;
        } MsiMapping;

    } Offset04;

    union {

        struct {
            ULONG AddressUpper;
        } MsiMapping;

    } Offset08;

} PCI_HT_CAPABILITY, *PPCI_HT_CAPABILITY;

#define PCI_HT_CAPABILITY_COMMON_SIZE FIELD_OFFSET(PCI_HT_CAPABILITY, Offset04)
#define PCI_HT_MSI_MAPPING_CAPABILITY_SIZE (PCI_HT_CAPABILITY_COMMON_SIZE + 2 * sizeof(ULONG))

typedef struct {
    USHORT Reserved1;
    UCHAR LastInterrupt;
    UCHAR Reserved2;
} PCI_HT_INTERRUPT_INDEX_1, *PPCI_HT_INTERRUPT_INDEX_1;

typedef struct {

    union {
        struct {
            ULONG Mask:1;             // bit 0
            ULONG Polarity:1;         // bit 1
            ULONG MessageType:3;      // bits [4:2]
            ULONG RequestEOI:1;       // bit 5
            ULONG DestinationMode:1;  // bit 6
            ULONG MessageType3:1;     // bit 7
            ULONG Destination:8;      // bits [15:8]
            ULONG Vector:8;           // bits [23:16]
            ULONG ExtendedAddress:8;  // bits [31:24] -- always set to 0xF8
        } bits;

        ULONG AsULONG;

    } LowPart;

    union {
        struct {
            ULONG ExtendedDestination:24;
            ULONG Reserved:6;
            ULONG PassPW:1;
            ULONG WaitingForEOI:1;
        } bits;

        ULONG AsULONG;

    } HighPart;

} PCI_HT_INTERRUPT_INDEX_N, *PPCI_HT_INTERRUPT_INDEX_N;

#define PCI_TYPE1_ADDR_PORT     0xCF8
#define PCI_TYPE1_DATA_PORT     0xCFC

typedef struct _PCI_TYPE1_CFG_BITS {
    union {
        struct {
            ULONG   Reserved1:2;
            ULONG   RegisterNumber:6;
            ULONG   FunctionNumber:3;
            ULONG   DeviceNumber:5;
            ULONG   BusNumber:8;
            ULONG   Reserved2:7;
            ULONG   Enable:1;
        } bits;

        ULONG   AsULONG;
    } u;
} PCI_TYPE1_CFG_BITS, *PPCI_TYPE1_CFG_BITS;

#define PCI_TYPE2_CSE_PORT              ((PUCHAR)(LONG_PTR) 0xCF8)
#define PCI_TYPE2_FORWARD_PORT          ((PUCHAR)(LONG_PTR) 0xCFA)
#define PCI_TYPE2_ADDRESS_BASE          0xC


typedef struct _PCI_TYPE2_CSE_BITS {
    union {
        struct {
            UCHAR   Enable:1;
            UCHAR   FunctionNumber:3;
            UCHAR   Key:4;
        } bits;
        UCHAR   AsUCHAR;
    } u;
} PCI_TYPE2_CSE_BITS, PPCI_TYPE2_CSE_BITS;


typedef struct _PCI_TYPE2_ADDRESS_BITS {
    union {
        struct {
            USHORT  RegisterNumber:8;
            USHORT  Agent:4;
            USHORT  AddressBase:4;
        } bits;
        USHORT  AsUSHORT;
    } u;
} PCI_TYPE2_ADDRESS_BITS, *PPCI_TYPE2_ADDRESS_BITS;

typedef struct _PCI_TYPE0_CFG_CYCLE_BITS {
    union {
        struct {
            ULONG   Reserved1:2;
            ULONG   RegisterNumber:6;
            ULONG   FunctionNumber:3;
            ULONG   Reserved2:21;
        } bits;
        ULONG   AsULONG;
    } u;
} PCI_TYPE0_CFG_CYCLE_BITS, *PPCI_TYPE0_CFG_CYCLE_BITS;

typedef struct _PCI_TYPE1_CFG_CYCLE_BITS {
    union {
        struct {
            ULONG   Reserved1:2;
            ULONG   RegisterNumber:6;
            ULONG   FunctionNumber:3;
            ULONG   DeviceNumber:5;
            ULONG   BusNumber:8;
            ULONG   Reserved2:8;
        } bits;
        ULONG   AsULONG;
    } u;
} PCI_TYPE1_CFG_CYCLE_BITS, *PPCI_TYPE1_CFG_CYCLE_BITS;

#pragma warning(pop)

NTSTATUS
NTKERNELAPI
HvlQueryActiveHypervisorProcessorCount(
    _Out_ PULONG LpCount
    );

NTSTATUS
NTKERNELAPI
HvlQueryHypervisorProcessorNodeNumber(
    _In_ ULONG LpIndex,
    _Out_ PUSHORT NodeNumber
    );

NTSTATUS
HvlQueryNumaDistance (
    __in USHORT CpuNumaNode,
    __in USHORT MemoryNumaNode,
    __out PULONG64 Distance
    );

#ifndef _PCIINTRF_X_
#define _PCIINTRF_X_

typedef
_Function_class_(PCI_READ_WRITE_CONFIG)
_IRQL_requires_max_(HIGH_LEVEL)
ULONG
PCI_READ_WRITE_CONFIG (
    _In_ PVOID Context,
    _In_ ULONG BusOffset,
    _In_ ULONG Slot,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Offset,
    _In_ ULONG Length
    );

typedef PCI_READ_WRITE_CONFIG *PPCI_READ_WRITE_CONFIG;

typedef
_Function_class_(PCI_PIN_TO_LINE)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
PCI_PIN_TO_LINE (
    _In_ PVOID Context,
    _In_ PPCI_COMMON_CONFIG PciData
    );

typedef PCI_PIN_TO_LINE *PPCI_PIN_TO_LINE;

typedef
_Function_class_(PCI_LINE_TO_PIN)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
PCI_LINE_TO_PIN (
    _In_ PVOID Context,
    _In_ PPCI_COMMON_CONFIG PciNewData,
    _In_ PPCI_COMMON_CONFIG PciOldData
    );

typedef PCI_LINE_TO_PIN *PPCI_LINE_TO_PIN;

typedef
_Function_class_(PCI_ROOT_BUS_CAPABILITY)
_IRQL_requires_(PASSIVE_LEVEL)
VOID
PCI_ROOT_BUS_CAPABILITY (
    _In_ PVOID Context,
    _Out_ PPCI_ROOT_BUS_HARDWARE_CAPABILITY HardwareCapability
    );

typedef PCI_ROOT_BUS_CAPABILITY *PPCI_ROOT_BUS_CAPABILITY;

typedef
_Function_class_(PCI_EXPRESS_WAKE_CONTROL)
_IRQL_requires_max_(DISPATCH_LEVEL)
VOID
PCI_EXPRESS_WAKE_CONTROL (
    _In_ PVOID Context,
    _In_ BOOLEAN EnableWake
    );

typedef PCI_EXPRESS_WAKE_CONTROL *PPCI_EXPRESS_WAKE_CONTROL;

typedef
_Function_class_(PCI_PREPARE_MULTISTAGE_RESUME)
_IRQL_requires_max_(HIGH_LEVEL)
VOID
PCI_PREPARE_MULTISTAGE_RESUME (
    _In_ PVOID Context
    );

typedef PCI_PREPARE_MULTISTAGE_RESUME *PPCI_PREPARE_MULTISTAGE_RESUME;


typedef struct _PCI_BUS_INTERFACE_STANDARD {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PPCI_READ_WRITE_CONFIG ReadConfig;
    PPCI_READ_WRITE_CONFIG WriteConfig;
    PPCI_PIN_TO_LINE PinToLine;
    PPCI_LINE_TO_PIN LineToPin;
    PPCI_ROOT_BUS_CAPABILITY RootBusCapability;
    PPCI_EXPRESS_WAKE_CONTROL ExpressWakeControl;
    PPCI_PREPARE_MULTISTAGE_RESUME PrepareMultistageResume;

} PCI_BUS_INTERFACE_STANDARD, *PPCI_BUS_INTERFACE_STANDARD;

#define PCI_BUS_INTERFACE_STANDARD_VERSION 2
#define PCI_BUS_INTERFACE_STANDARD_VERSION_1_LENGTH \
    FIELD_OFFSET(PCI_BUS_INTERFACE_STANDARD, PrepareMultistageResume)

#define PCI_DEVICE_PRESENT_INTERFACE_VERSION 1

#define PCI_USE_SUBSYSTEM_IDS   0x00000001
#define PCI_USE_REVISION        0x00000002
#define PCI_USE_VENDEV_IDS      0x00000004
#define PCI_USE_CLASS_SUBCLASS  0x00000008
#define PCI_USE_PROGIF          0x00000010
#define PCI_USE_LOCAL_BUS       0x00000020
#define PCI_USE_LOCAL_DEVICE    0x00000040

typedef struct _PCI_DEVICE_PRESENCE_PARAMETERS {

    ULONG Size;
    ULONG Flags;

    USHORT VendorID;
    USHORT DeviceID;
    UCHAR RevisionID;
    USHORT SubVendorID;
    USHORT SubSystemID;
    UCHAR BaseClass;
    UCHAR SubClass;
    UCHAR ProgIf;

} PCI_DEVICE_PRESENCE_PARAMETERS, *PPCI_DEVICE_PRESENCE_PARAMETERS;

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
typedef
BOOLEAN
PCI_IS_DEVICE_PRESENT (
    _In_ USHORT VendorID,
    _In_ USHORT DeviceID,
    _In_ UCHAR RevisionID,
    _In_ USHORT SubVendorID,
    _In_ USHORT SubSystemID,
    _In_ ULONG Flags
);

typedef PCI_IS_DEVICE_PRESENT *PPCI_IS_DEVICE_PRESENT;

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
typedef
BOOLEAN
PCI_IS_DEVICE_PRESENT_EX (
    _In_ PVOID Context,
    _In_ PPCI_DEVICE_PRESENCE_PARAMETERS Parameters
    );

typedef PCI_IS_DEVICE_PRESENT_EX *PPCI_IS_DEVICE_PRESENT_EX;

typedef struct _PCI_DEVICE_PRESENT_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;
    PPCI_IS_DEVICE_PRESENT IsDevicePresent;
    PPCI_IS_DEVICE_PRESENT_EX IsDevicePresentEx;
} PCI_DEVICE_PRESENT_INTERFACE, *PPCI_DEVICE_PRESENT_INTERFACE;

#define PCI_EXPRESS_LINK_QUIESCENT_INTERFACE_VERSION      1

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
typedef
NTSTATUS
PCI_EXPRESS_ENTER_LINK_QUIESCENT_MODE (
    _Inout_ PVOID Context
    );

typedef PCI_EXPRESS_ENTER_LINK_QUIESCENT_MODE *PPCI_EXPRESS_ENTER_LINK_QUIESCENT_MODE;

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
typedef
NTSTATUS
PCI_EXPRESS_EXIT_LINK_QUIESCENT_MODE (
    _Inout_ PVOID Context
    );

typedef PCI_EXPRESS_EXIT_LINK_QUIESCENT_MODE *PPCI_EXPRESS_EXIT_LINK_QUIESCENT_MODE;

typedef struct _PCI_EXPRESS_LINK_QUIESCENT_INTERFACE {

    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    PPCI_EXPRESS_ENTER_LINK_QUIESCENT_MODE PciExpressEnterLinkQuiescentMode;
    PPCI_EXPRESS_EXIT_LINK_QUIESCENT_MODE PciExpressExitLinkQuiescentMode;

} PCI_EXPRESS_LINK_QUIESCENT_INTERFACE, *PPCI_EXPRESS_LINK_QUIESCENT_INTERFACE;

#define PCI_EXPRESS_ROOT_PORT_INTERFACE_VERSION        1

typedef
ULONG
(*PPCI_EXPRESS_ROOT_PORT_READ_CONFIG_SPACE) (
    _In_ PVOID Context,
    _Out_writes_bytes_(Length) PVOID Buffer,
    _In_ ULONG Offset,
    _In_ ULONG Length
    );

typedef
ULONG
(*PPCI_EXPRESS_ROOT_PORT_WRITE_CONFIG_SPACE) (
    _In_ PVOID Context,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Offset,
    _In_ ULONG Length
    );

typedef struct _PCI_EXPRESS_ROOT_PORT_INTERFACE {

    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    PPCI_EXPRESS_ROOT_PORT_READ_CONFIG_SPACE ReadConfigSpace;
    PPCI_EXPRESS_ROOT_PORT_WRITE_CONFIG_SPACE WriteConfigSpace;

} PCI_EXPRESS_ROOT_PORT_INTERFACE, *PPCI_EXPRESS_ROOT_PORT_INTERFACE;

#define PCI_MSIX_TABLE_CONFIG_INTERFACE_VERSION 1

_Must_inspect_result_
typedef
NTSTATUS
PCI_MSIX_SET_ENTRY (
    _In_ PVOID Context,
    _In_ ULONG TableEntry,
    _In_ ULONG MessageNumber
    );

typedef PCI_MSIX_SET_ENTRY *PPCI_MSIX_SET_ENTRY;

_Must_inspect_result_
typedef
NTSTATUS
PCI_MSIX_MASKUNMASK_ENTRY (
    _In_ PVOID Context,
    _In_ ULONG TableEntry
    );

typedef PCI_MSIX_MASKUNMASK_ENTRY *PPCI_MSIX_MASKUNMASK_ENTRY;

_Must_inspect_result_
typedef
NTSTATUS
PCI_MSIX_GET_ENTRY (
    _In_ PVOID Context,
    _In_ ULONG TableEntry,
    _Out_ PULONG MessageNumber,
    _Out_ PBOOLEAN Masked
    );

typedef PCI_MSIX_GET_ENTRY *PPCI_MSIX_GET_ENTRY;

_Must_inspect_result_
typedef
NTSTATUS
PCI_MSIX_GET_TABLE_SIZE (
    _In_ PVOID Context,
    _Out_ PULONG TableSize
    );

typedef PCI_MSIX_GET_TABLE_SIZE *PPCI_MSIX_GET_TABLE_SIZE;

typedef struct _PCI_MSIX_TABLE_CONFIG_INTERFACE {
    USHORT Size;
    USHORT Version;
    PVOID Context;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    PPCI_MSIX_SET_ENTRY SetTableEntry;
    PPCI_MSIX_MASKUNMASK_ENTRY MaskTableEntry;
    PPCI_MSIX_MASKUNMASK_ENTRY UnmaskTableEntry;
    PPCI_MSIX_GET_ENTRY GetTableEntry;
    PPCI_MSIX_GET_TABLE_SIZE GetTableSize;
} PCI_MSIX_TABLE_CONFIG_INTERFACE, *PPCI_MSIX_TABLE_CONFIG_INTERFACE;

#define PCI_MSIX_TABLE_CONFIG_MINIMUM_SIZE \
        RTL_SIZEOF_THROUGH_FIELD(PCI_MSIX_TABLE_CONFIG_INTERFACE, UnmaskTableEntry)

#define FSRTL_FILE_NAME_QUERY_CACHE_ONLY  0x0200
#define FSRTL_FILE_NAME_QUERY_FILESYSTEM_ONLY 0x0300
#define FSRTL_FILE_NAME_QUERY_ALWAYS_ALLOW_CACHE_LOOKUP 0x0400

#define FSRTL_FSP_TOP_LEVEL_IRP                 ((LONG_PTR)0x01)
#define FSRTL_CACHE_TOP_LEVEL_IRP               ((LONG_PTR)0x02)
#define FSRTL_MOD_WRITE_TOP_LEVEL_IRP           ((LONG_PTR)0x03)
#define FSRTL_FAST_IO_TOP_LEVEL_IRP             ((LONG_PTR)0x04)
#define FSRTL_NETWORK1_TOP_LEVEL_IRP            ((LONG_PTR)0x05)
#define FSRTL_NETWORK2_TOP_LEVEL_IRP            ((LONG_PTR)0x06)
#define FSRTL_ASYNC_CACHED_READ_TOP_LEVEL_IRP   ((LONG_PTR)0x07)
#define FSRTL_MAX_TOP_LEVEL_IRP_FLAG            ((LONG_PTR)0xFFFF)

#define FsRtlIsChecksumError(STS) ((BOOLEAN)!FsRtlIsTotalDeviceFailure(STS))

#define LEGAL_ANSI_CHARACTER_ARRAY        (*FsRtlLegalAnsiCharacterArray)
#define NLS_OEM_LEAD_BYTE_INFO            (*NlsOemLeadByteInfo)

extern UCHAR const* const LEGAL_ANSI_CHARACTER_ARRAY;
extern PUSHORT NLS_OEM_LEAD_BYTE_INFO;  // Lead byte info. for ACP

#define FSRTL_FAT_LEGAL         0x01
#define FSRTL_HPFS_LEGAL        0x02
#define FSRTL_NTFS_LEGAL        0x04
#define FSRTL_WILD_CHARACTER    0x08
#define FSRTL_OLE_LEGAL         0x10
#define FSRTL_NTFS_STREAM_LEGAL (FSRTL_NTFS_LEGAL | FSRTL_OLE_LEGAL)

#define FsRtlIsAnsiCharacterWild(C) (                               \
    FsRtlTestAnsiCharacter((C), FALSE, FALSE, FSRTL_WILD_CHARACTER) \
)

#define FsRtlIsAnsiCharacterLegalFat(C,WILD_OK) (                 \
    FsRtlTestAnsiCharacter((C), TRUE, (WILD_OK), FSRTL_FAT_LEGAL) \
)

#define FsRtlIsAnsiCharacterLegalHpfs(C,WILD_OK) (                 \
    FsRtlTestAnsiCharacter((C), TRUE, (WILD_OK), FSRTL_HPFS_LEGAL) \
)

#define FsRtlIsAnsiCharacterLegalNtfs(C,WILD_OK) (                 \
    FsRtlTestAnsiCharacter((C), TRUE, (WILD_OK), FSRTL_NTFS_LEGAL) \
)

#define FsRtlIsAnsiCharacterLegalNtfsStream(C,WILD_OK) (                    \
    FsRtlTestAnsiCharacter((C), TRUE, (WILD_OK), FSRTL_NTFS_STREAM_LEGAL)   \
)

#define FsRtlIsAnsiCharacterLegal(C,FLAGS) (          \
    FsRtlTestAnsiCharacter((C), TRUE, FALSE, (FLAGS)) \
)

#define FsRtlTestAnsiCharacter(C, DEFAULT_RET, WILD_OK, FLAGS) (            \
        ((SCHAR)(C) < 0) ? DEFAULT_RET :                                    \
                           FlagOn( LEGAL_ANSI_CHARACTER_ARRAY[(C)],         \
                                   (FLAGS) |                                \
                                   ((WILD_OK) ? FSRTL_WILD_CHARACTER : 0) ) \
)

#define FsRtlIsLeadDbcsCharacter(DBCS_CHAR) (                      \
    (BOOLEAN)((UCHAR)(DBCS_CHAR) < 0x80 ? FALSE :                  \
              (NLS_MB_CODE_PAGE_TAG &&                             \
               (NLS_OEM_LEAD_BYTE_INFO[(UCHAR)(DBCS_CHAR)] != 0))) \
)

#if (NTDDI_VERSION >= NTDDI_VISTA)
#define FSRTL_ALLOCATE_ECP_FLAG_CHARGE_QUOTA    0x00000001
#define FSRTL_ALLOCATE_ECP_FLAG_NONPAGED_POOL   0x00000002
#define FSRTL_ECP_LOOKASIDE_FLAG_NONPAGED_POOL 0x00000002
#define FSRTL_VIRTDISK_FULLY_ALLOCATED  0x00000001
#define FSRTL_VIRTDISK_NO_DRIVE_LETTER  0x00000002
#endif


#define FSRTL_DRIVER_BACKING_FLAG_USE_PAGE_FILE        0x00000001

BOOLEAN
NTKERNELAPI
FsRtlIsMobileOS();


NTKERNELAPI
NTSTATUS
LpcDisconnectPort (
    _In_ PVOID Port
    );

#define WHEA_PHYSICAL_ADDRESS LARGE_INTEGER

typedef enum _WHEA_ERROR_SOURCE_TYPE {
    WheaErrSrcTypeMCE        = 0x00,    // Machine Check Exception
    WheaErrSrcTypeCMC        = 0x01,    // Corrected Machine Check
    WheaErrSrcTypeCPE        = 0x02,    // Corrected Platform Error
    WheaErrSrcTypeNMI        = 0x03,    // Non-Maskable Interrupt
    WheaErrSrcTypePCIe       = 0x04,    // PCI Express Error
    WheaErrSrcTypeGeneric    = 0x05,    // Other types of error sources
    WheaErrSrcTypeINIT       = 0x06,    // IA64 INIT Error Source
    WheaErrSrcTypeBOOT       = 0x07,    // BOOT Error Source
    WheaErrSrcTypeSCIGeneric = 0x08,    // SCI-based generic error source
    WheaErrSrcTypeIPFMCA     = 0x09,    // Itanium Machine Check Abort
    WheaErrSrcTypeIPFCMC     = 0x0a,    // Itanium Machine check
    WheaErrSrcTypeIPFCPE     = 0x0b,    // Itanium Corrected Platform Error
    WheaErrSrcTypeMax
} WHEA_ERROR_SOURCE_TYPE, *PWHEA_ERROR_SOURCE_TYPE;

typedef enum _WHEA_ERROR_SOURCE_STATE {
    WheaErrSrcStateStopped = 0x01,
    WheaErrSrcStateStarted = 0x02
} WHEA_ERROR_SOURCE_STATE, *PWHEA_ERROR_SOURCE_STATE;

#define WHEA_ERROR_SOURCE_DESCRIPTOR_VERSION_10          10

#define WHEA_MAX_MC_BANKS                                32

#define WHEA_ERROR_SOURCE_FLAG_FIRMWAREFIRST             0x00000001
#define WHEA_ERROR_SOURCE_FLAG_GLOBAL                    0x00000002
#define WHEA_ERROR_SOURCE_FLAG_PREALLOCATE_PER_PROCESSOR 0x00000004
#define WHEA_ERROR_SOURCE_FLAG_DEFAULTSOURCE             0x80000000

#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_XPFMCE         0
#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_XPFCMC         1
#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_XPFNMI         2
#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_IPFMCA         3
#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_IPFCMC         4
#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_IPFCPE         5
#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_AERROOTPORT    6
#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_AERENDPOINT    7
#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_AERBRIDGE      8
#define WHEA_ERROR_SOURCE_DESCRIPTOR_TYPE_GENERIC        9

#define WHEA_XPF_MC_BANK_STATUSFORMAT_IA32MCA            0
#define WHEA_XPF_MC_BANK_STATUSFORMAT_Intel64MCA         1
#define WHEA_XPF_MC_BANK_STATUSFORMAT_AMD64MCA           2

#define WHEA_NOTIFICATION_TYPE_POLLED                    0
#define WHEA_NOTIFICATION_TYPE_EXTERNALINTERRUPT         1
#define WHEA_NOTIFICATION_TYPE_LOCALINTERRUPT            2
#define WHEA_NOTIFICATION_TYPE_SCI                       3
#define WHEA_NOTIFICATION_TYPE_NMI                       4

#include <pshpack1.h>

typedef union _WHEA_NOTIFICATION_FLAGS {
    struct {
        USHORT PollIntervalRW:1;
        USHORT SwitchToPollingThresholdRW:1;
        USHORT SwitchToPollingWindowRW:1;
        USHORT ErrorThresholdRW:1;
        USHORT ErrorThresholdWindowRW:1;
        USHORT Reserved:11;
    } DUMMYSTRUCTNAME;
    USHORT AsUSHORT;
} WHEA_NOTIFICATION_FLAGS, *PWHEA_NOTIFICATION_FLAGS;

typedef union _XPF_MC_BANK_FLAGS {
    struct {
        UCHAR ClearOnInitializationRW:1;
        UCHAR ControlDataRW:1;
        UCHAR Reserved:6;
    } DUMMYSTRUCTNAME;
    UCHAR AsUCHAR;
} XPF_MC_BANK_FLAGS, *PXPF_MC_BANK_FLAGS;

typedef union _XPF_MCE_FLAGS {
    struct {
        ULONG MCG_CapabilityRW:1;
        ULONG MCG_GlobalControlRW:1;
        ULONG Reserved:30;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} XPF_MCE_FLAGS, *PXPF_MCE_FLAGS;

typedef union _AER_ROOTPORT_DESCRIPTOR_FLAGS {
    struct {
        USHORT UncorrectableErrorMaskRW:1;
        USHORT UncorrectableErrorSeverityRW:1;
        USHORT CorrectableErrorMaskRW:1;
        USHORT AdvancedCapsAndControlRW:1;
        USHORT RootErrorCommandRW:1;
        USHORT Reserved:11;
    } DUMMYSTRUCTNAME;
    USHORT AsUSHORT;
} AER_ROOTPORT_DESCRIPTOR_FLAGS, *PAER_ROOTPORT_DESCRIPTOR_FLAGS;

typedef union _AER_ENDPOINT_DESCRIPTOR_FLAGS {
    struct {
        USHORT UncorrectableErrorMaskRW:1;
        USHORT UncorrectableErrorSeverityRW:1;
        USHORT CorrectableErrorMaskRW:1;
        USHORT AdvancedCapsAndControlRW:1;
        USHORT Reserved:12;
    } DUMMYSTRUCTNAME;
    USHORT AsUSHORT;
} AER_ENDPOINT_DESCRIPTOR_FLAGS, *PAER_ENDPOINT_DESCRIPTOR_FLAGS;

typedef union _AER_BRIDGE_DESCRIPTOR_FLAGS {
    struct {
        USHORT UncorrectableErrorMaskRW:1;
        USHORT UncorrectableErrorSeverityRW:1;
        USHORT CorrectableErrorMaskRW:1;
        USHORT AdvancedCapsAndControlRW:1;
        USHORT SecondaryUncorrectableErrorMaskRW:1;
        USHORT SecondaryUncorrectableErrorSevRW:1;
        USHORT SecondaryCapsAndControlRW:1;
        USHORT Reserved:9;
    } DUMMYSTRUCTNAME;
    USHORT AsUSHORT;
} AER_BRIDGE_DESCRIPTOR_FLAGS, *PAER_BRIDGE_DESCRIPTOR_FLAGS;

typedef struct _WHEA_NOTIFICATION_DESCRIPTOR {
    UCHAR Type;
    UCHAR Length;
    WHEA_NOTIFICATION_FLAGS Flags;

    union {
        struct {
            ULONG PollInterval;
        } Polled;

        struct {
            ULONG PollInterval;
            ULONG Vector;
            ULONG SwitchToPollingThreshold;
            ULONG SwitchToPollingWindow;
            ULONG ErrorThreshold;
            ULONG ErrorThresholdWindow;
        } Interrupt;

        struct {
            ULONG PollInterval;
            ULONG Vector;
            ULONG SwitchToPollingThreshold;
            ULONG SwitchToPollingWindow;
            ULONG ErrorThreshold;
            ULONG ErrorThresholdWindow;
        } LocalInterrupt;

        struct {
            ULONG PollInterval;
            ULONG Vector;
            ULONG SwitchToPollingThreshold;
            ULONG SwitchToPollingWindow;
            ULONG ErrorThreshold;
            ULONG ErrorThresholdWindow;
        } Sci;

        struct {
            ULONG PollInterval;
            ULONG Vector;
            ULONG SwitchToPollingThreshold;
            ULONG SwitchToPollingWindow;
            ULONG ErrorThreshold;
            ULONG ErrorThresholdWindow;
        } Nmi;
    } u;
} WHEA_NOTIFICATION_DESCRIPTOR, *PWHEA_NOTIFICATION_DESCRIPTOR;

typedef struct _WHEA_XPF_MC_BANK_DESCRIPTOR {
    UCHAR BankNumber;
    BOOLEAN ClearOnInitialization;
    UCHAR StatusDataFormat;
    XPF_MC_BANK_FLAGS Flags;
    ULONG ControlMsr;
    ULONG StatusMsr;
    ULONG AddressMsr;
    ULONG MiscMsr;
    ULONGLONG ControlData;
} WHEA_XPF_MC_BANK_DESCRIPTOR, *PWHEA_XPF_MC_BANK_DESCRIPTOR;

typedef struct _WHEA_XPF_MCE_DESCRIPTOR {
    USHORT Type;
    UCHAR Enabled;
    UCHAR NumberOfBanks;
    XPF_MCE_FLAGS Flags;
    ULONGLONG MCG_Capability;
    ULONGLONG MCG_GlobalControl;
    WHEA_XPF_MC_BANK_DESCRIPTOR Banks[WHEA_MAX_MC_BANKS];
} WHEA_XPF_MCE_DESCRIPTOR, *PWHEA_XPF_MCE_DESCRIPTOR;

typedef struct _WHEA_XPF_CMC_DESCRIPTOR {
    USHORT Type;
    BOOLEAN Enabled;
    UCHAR NumberOfBanks;
    ULONG Reserved;
    WHEA_NOTIFICATION_DESCRIPTOR Notify;
    WHEA_XPF_MC_BANK_DESCRIPTOR Banks[WHEA_MAX_MC_BANKS];
} WHEA_XPF_CMC_DESCRIPTOR, *PWHEA_XPF_CMC_DESCRIPTOR;

typedef struct _WHEA_PCI_SLOT_NUMBER {
    union {
        struct {
            ULONG DeviceNumber:5;
            ULONG FunctionNumber:3;
            ULONG Reserved:24;
        } bits;
        ULONG AsULONG;
    } u;
} WHEA_PCI_SLOT_NUMBER, *PWHEA_PCI_SLOT_NUMBER;

typedef struct _WHEA_XPF_NMI_DESCRIPTOR {
    USHORT Type;
    BOOLEAN Enabled;
} WHEA_XPF_NMI_DESCRIPTOR, *PWHEA_XPF_NMI_DESCRIPTOR;

typedef struct _WHEA_AER_ROOTPORT_DESCRIPTOR {
    USHORT Type;
    BOOLEAN Enabled;
    UCHAR Reserved;
    ULONG BusNumber;
    WHEA_PCI_SLOT_NUMBER Slot;
    USHORT DeviceControl;
    AER_ROOTPORT_DESCRIPTOR_FLAGS Flags;
    ULONG UncorrectableErrorMask;
    ULONG UncorrectableErrorSeverity;
    ULONG CorrectableErrorMask;
    ULONG AdvancedCapsAndControl;
    ULONG RootErrorCommand;
} WHEA_AER_ROOTPORT_DESCRIPTOR, *PWHEA_AER_ROOTPORT_DESCRIPTOR;

typedef struct _WHEA_AER_ENDPOINT_DESCRIPTOR {
    USHORT Type;
    BOOLEAN Enabled;
    UCHAR Reserved;
    ULONG BusNumber;
    WHEA_PCI_SLOT_NUMBER Slot;
    USHORT DeviceControl;
    AER_ENDPOINT_DESCRIPTOR_FLAGS Flags;
    ULONG UncorrectableErrorMask;
    ULONG UncorrectableErrorSeverity;
    ULONG CorrectableErrorMask;
    ULONG AdvancedCapsAndControl;
} WHEA_AER_ENDPOINT_DESCRIPTOR, *PWHEA_AER_ENDPOINT_DESCRIPTOR;

typedef struct _WHEA_AER_BRIDGE_DESCRIPTOR {
    USHORT Type;
    BOOLEAN Enabled;
    UCHAR Reserved;
    ULONG BusNumber;
    WHEA_PCI_SLOT_NUMBER Slot;
    USHORT DeviceControl;
    AER_BRIDGE_DESCRIPTOR_FLAGS Flags;
    ULONG UncorrectableErrorMask;
    ULONG UncorrectableErrorSeverity;
    ULONG CorrectableErrorMask;
    ULONG AdvancedCapsAndControl;
    ULONG SecondaryUncorrectableErrorMask;
    ULONG SecondaryUncorrectableErrorSev;
    ULONG SecondaryCapsAndControl;
} WHEA_AER_BRIDGE_DESCRIPTOR, *PWHEA_AER_BRIDGE_DESCRIPTOR;

typedef struct _WHEA_GENERIC_ERROR_DESCRIPTOR {
    USHORT Type;
    UCHAR Reserved;
    UCHAR Enabled;
    ULONG ErrStatusBlockLength;
    ULONG RelatedErrorSourceId;
    UCHAR ErrStatusAddressSpaceID;
    UCHAR ErrStatusAddressBitWidth;
    UCHAR ErrStatusAddressBitOffset;
    UCHAR ErrStatusAddressAccessSize;
    WHEA_PHYSICAL_ADDRESS ErrStatusAddress;
    WHEA_NOTIFICATION_DESCRIPTOR Notify;

} WHEA_GENERIC_ERROR_DESCRIPTOR, *PWHEA_GENERIC_ERROR_DESCRIPTOR;

typedef struct _WHEA_IPF_MCA_DESCRIPTOR {
    USHORT Type;
    UCHAR Enabled;
    UCHAR Reserved;
} WHEA_IPF_MCA_DESCRIPTOR, *PWHEA_IPF_MCA_DESCRIPTOR;

typedef struct _WHEA_IPF_CMC_DESCRIPTOR {
    USHORT Type;
    UCHAR Enabled;
    UCHAR Reserved;
} WHEA_IPF_CMC_DESCRIPTOR, *PWHEA_IPF_CMC_DESCRIPTOR;

typedef struct _WHEA_IPF_CPE_DESCRIPTOR {
    USHORT Type;
    UCHAR Enabled;
    UCHAR Reserved;
} WHEA_IPF_CPE_DESCRIPTOR, *PWHEA_IPF_CPE_DESCRIPTOR;

typedef struct _WHEA_ERROR_SOURCE_DESCRIPTOR {
    ULONG Length;                                              // +00 (0)
    ULONG Version;                                             // +04 (4)
    WHEA_ERROR_SOURCE_TYPE Type;                               // +08 (8)
    WHEA_ERROR_SOURCE_STATE State;                             // +0C (12)
    ULONG MaxRawDataLength;                                    // +10 (16)
    ULONG NumRecordsToPreallocate;                             // +14 (20)
    ULONG MaxSectionsPerRecord;                                // +18 (24)
    ULONG ErrorSourceId;                                       // +1C (28)
    ULONG PlatformErrorSourceId;                               // +20 (32)
    ULONG Flags;                                               // +24 (36)

    union {                                                    // +28 (40)
        WHEA_XPF_MCE_DESCRIPTOR XpfMceDescriptor;
        WHEA_XPF_CMC_DESCRIPTOR XpfCmcDescriptor;
        WHEA_XPF_NMI_DESCRIPTOR XpfNmiDescriptor;
        WHEA_IPF_MCA_DESCRIPTOR IpfMcaDescriptor;
        WHEA_IPF_CMC_DESCRIPTOR IpfCmcDescriptor;
        WHEA_IPF_CPE_DESCRIPTOR IpfCpeDescriptor;
        WHEA_AER_ROOTPORT_DESCRIPTOR AerRootportDescriptor;
        WHEA_AER_ENDPOINT_DESCRIPTOR AerEndpointDescriptor;
        WHEA_AER_BRIDGE_DESCRIPTOR AerBridgeDescriptor;
        WHEA_GENERIC_ERROR_DESCRIPTOR GenErrDescriptor;
    } Info;

} WHEA_ERROR_SOURCE_DESCRIPTOR, *PWHEA_ERROR_SOURCE_DESCRIPTOR;

#define    WHEA_DISABLE_OFFLINE        0
#define    WHEA_MEM_PERSISTOFFLINE     1
#define    WHEA_MEM_PFA_DISABLE        2
#define    WHEA_MEM_PFA_PAGECOUNT      3
#define    WHEA_MEM_PFA_THRESHOLD      4
#define    WHEA_MEM_PFA_TIMEOUT        5
#define    WHEA_DISABLE_DUMMY_WRITE    6

#include <poppack.h>

#define CPER_FIELD_CHECK(type, field, offset, length) \
    C_ASSERT(((FIELD_OFFSET(type, field) == (offset)) && \
              (RTL_FIELD_SIZE(type, field) == (length))))

#include <pshpack1.h>

#if WHEA_DOWNLEVEL_TYPE_NAMES

#define PROCESSOR_GENERIC_SECTION_GUID          PROCESSOR_GENERIC_ERROR_SECTION_GUID
#define X86_PROCESSOR_SPECIFIC_SECTION_GUID     XPF_PROCESSOR_ERROR_SECTION_GUID
#define IPF_PROCESSOR_SPECIFIC_SECTION_GUID     IPF_PROCESSOR_ERROR_SECTION_GUID
#define PLATFORM_MEMORY_SECTION_GUID            MEMORY_ERROR_SECTION_GUID
#define PCIEXPRESS_SECTION_GUID                 PCIEXPRESS_ERROR_SECTION_GUID
#define PCIX_BUS_SECTION_GUID                   PCIXBUS_ERROR_SECTION_GUID
#define PCIX_COMPONENT_SECTION_GUID             PCIXDEVICE_ERROR_SECTION_GUID
#define IPF_SAL_RECORD_REFERENCE_SECTION_GUID   FIRMWARE_ERROR_RECORD_REFERENCE_GUID

#endif

typedef union _WHEA_REVISION {
    struct {
        UCHAR MinorRevision;
        UCHAR MajorRevision;
    } DUMMYSTRUCTNAME;
    USHORT AsUSHORT;
} WHEA_REVISION, *PWHEA_REVISION;

typedef enum _WHEA_ERROR_SEVERITY {
    WheaErrSevRecoverable   = 0,
    WheaErrSevFatal         = 1,
    WheaErrSevCorrected     = 2,
    WheaErrSevInformational = 3
} WHEA_ERROR_SEVERITY, *PWHEA_ERROR_SEVERITY;

typedef union _WHEA_TIMESTAMP {
    struct {
        ULONGLONG Seconds:8;
        ULONGLONG Minutes:8;
        ULONGLONG Hours:8;
        ULONGLONG Precise:1;
        ULONGLONG Reserved:7;
        ULONGLONG Day:8;
        ULONGLONG Month:8;
        ULONGLONG Year:8;
        ULONGLONG Century:8;
    } DUMMYSTRUCTNAME;
    LARGE_INTEGER AsLARGE_INTEGER;
} WHEA_TIMESTAMP, *PWHEA_TIMESTAMP;

typedef union _WHEA_PERSISTENCE_INFO {
    struct {
        ULONGLONG Signature:16;
        ULONGLONG Length:24;
        ULONGLONG Identifier:16;
        ULONGLONG Attributes:2;
        ULONGLONG DoNotLog:1;
        ULONGLONG Reserved:5;
    } DUMMYSTRUCTNAME;
    ULONGLONG AsULONGLONG;
} WHEA_PERSISTENCE_INFO, *PWHEA_PERSISTENCE_INFO;

#define ERRTYP_INTERNAL                 0x01 // 1
#define ERRTYP_BUS                      0x10 // 16
#define ERRTYP_MEM                      0x04 // 4
#define ERRTYP_TLB                      0x05 // 5
#define ERRTYP_CACHE                    0x06 // 6
#define ERRTYP_FUNCTION                 0x07 // 7
#define ERRTYP_SELFTEST                 0x08 // 8
#define ERRTYP_FLOW                     0x09 // 9
#define ERRTYP_MAP                      0x11 // 17
#define ERRTYP_IMPROPER                 0x12 // 18
#define ERRTYP_UNIMPL                   0x13 // 19
#define ERRTYP_LOSSOFLOCKSTEP           0x14 // 20
#define ERRTYP_RESPONSE                 0x15 // 21
#define ERRTYP_PARITY                   0x16 // 22
#define ERRTYP_PROTOCOL                 0x17 // 23
#define ERRTYP_PATHERROR                0x18 // 24
#define ERRTYP_TIMEOUT                  0x19 // 25
#define ERRTYP_POISONED                 0x1A // 26

typedef union _WHEA_ERROR_STATUS {
    ULONGLONG ErrorStatus;
    struct {
        ULONGLONG Reserved1:8;
        ULONGLONG ErrorType:8;
        ULONGLONG Address:1;
        ULONGLONG Control:1;
        ULONGLONG Data:1;
        ULONGLONG Responder:1;
        ULONGLONG Requester:1;
        ULONGLONG FirstError:1;
        ULONGLONG Overflow:1;
        ULONGLONG Reserved2:41;
    } DUMMYSTRUCTNAME;
} WHEA_ERROR_STATUS, *PWHEA_ERROR_STATUS;

typedef union _WHEA_ERROR_RECORD_HEADER_VALIDBITS {
    struct {
        ULONG PlatformId:1;
        ULONG Timestamp:1;
        ULONG PartitionId:1;
        ULONG Reserved:29;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_ERROR_RECORD_HEADER_VALIDBITS, *PWHEA_ERROR_RECORD_HEADER_VALIDBITS;

#define WHEA_ERROR_RECORD_VALID_PLATFORMID           0x00000001
#define WHEA_ERROR_RECORD_VALID_TIMESTAMP            0x00000002
#define WHEA_ERROR_RECORD_VALID_PARTITIONID          0x00000004

typedef union _WHEA_ERROR_RECORD_HEADER_FLAGS {
    struct {
        ULONG Recovered:1;
        ULONG PreviousError:1;
        ULONG Simulated:1;
        ULONG Reserved:29;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_ERROR_RECORD_HEADER_FLAGS, *PWHEA_ERROR_RECORD_HEADER_FLAGS;

#define WHEA_ERROR_RECORD_FLAGS_RECOVERED            0x00000001
#define WHEA_ERROR_RECORD_FLAGS_PREVIOUSERROR        0x00000002
#define WHEA_ERROR_RECORD_FLAGS_SIMULATED            0x00000004

typedef struct _WHEA_ERROR_RECORD_HEADER {
    ULONG Signature;
    WHEA_REVISION Revision;
    ULONG SignatureEnd;
    USHORT SectionCount;
    WHEA_ERROR_SEVERITY Severity;
    WHEA_ERROR_RECORD_HEADER_VALIDBITS ValidBits;
    _Field_range_(>=, (sizeof(WHEA_ERROR_RECORD_HEADER)
                       + (SectionCount
                          * sizeof(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR))))
        ULONG Length;
    WHEA_TIMESTAMP Timestamp;
    GUID PlatformId;
    GUID PartitionId;
    GUID CreatorId;
    GUID NotifyType;
    ULONGLONG RecordId;
    WHEA_ERROR_RECORD_HEADER_FLAGS Flags;
    WHEA_PERSISTENCE_INFO PersistenceInfo;
    UCHAR Reserved[12];
} WHEA_ERROR_RECORD_HEADER, *PWHEA_ERROR_RECORD_HEADER;

#define WHEA_ERROR_RECORD_SIGNATURE         'REPC'
#define WHEA_ERROR_RECORD_REVISION          0x0210
#define WHEA_ERROR_RECORD_SIGNATURE_END     0xFFFFFFFF

CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, Signature,         0,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, Revision,          4,  2);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, SignatureEnd,      6,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, SectionCount,     10,  2);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, Severity,         12,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, ValidBits,        16,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, Length,           20,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, Timestamp,        24,  8);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, PlatformId,       32, 16);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, PartitionId,      48, 16);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, CreatorId,        64, 16);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, NotifyType,       80, 16);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, RecordId,         96,  8);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, Flags,           104,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, PersistenceInfo, 108,  8);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_HEADER, Reserved,        116, 12);

typedef union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS {
    struct {
        ULONG Primary:1;
        ULONG ContainmentWarning:1;
        ULONG Reset:1;
        ULONG ThresholdExceeded:1;
        ULONG ResourceNotAvailable:1;
        ULONG LatentError:1;
        ULONG Reserved:26;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS,
    *PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS;

#define WHEA_SECTION_DESCRIPTOR_FLAGS_PRIMARY            0x00000001
#define WHEA_SECTION_DESCRIPTOR_FLAGS_CONTAINMENTWRN     0x00000002
#define WHEA_SECTION_DESCRIPTOR_FLAGS_RESET              0x00000004
#define WHEA_SECTION_DESCRIPTOR_FLAGS_THRESHOLDEXCEEDED  0x00000008
#define WHEA_SECTION_DESCRIPTOR_FLAGS_RESOURCENA         0x00000010
#define WHEA_SECTION_DESCRIPTOR_FLAGS_LATENTERROR        0x00000020

typedef union _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS {
    struct {
        UCHAR FRUId:1;
        UCHAR FRUText:1;
        UCHAR Reserved:6;
    } DUMMYSTRUCTNAME;
    UCHAR AsUCHAR;
} WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS,
    *PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS;

typedef struct _WHEA_ERROR_RECORD_SECTION_DESCRIPTOR {
    ULONG SectionOffset;
    ULONG SectionLength;
    WHEA_REVISION Revision;
    WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_VALIDBITS ValidBits;
    UCHAR Reserved;
    WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_FLAGS Flags;
    GUID SectionType;
    GUID FRUId;
    WHEA_ERROR_SEVERITY SectionSeverity;
    CCHAR FRUText[20];
} WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, *PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR;

#define WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_REVISION   0x0201

#if WHEA_DOWNLEVEL_TYPE_NAMES

#define WHEA_SECTION_DESCRIPTOR_REVISION \
    WHEA_ERROR_RECORD_SECTION_DESCRIPTOR_REVISION

#endif

CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, SectionOffset,    0,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, SectionLength,    4,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, Revision,         8,  2);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, ValidBits,       10,  1);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, Reserved,        11,  1);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, Flags,           12,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, SectionType,     16, 16);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, FRUId,           32, 16);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, SectionSeverity, 48,  4);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR, FRUText,         52, 20);

typedef _Struct_size_bytes_(Header.Length) struct _WHEA_ERROR_RECORD {
    WHEA_ERROR_RECORD_HEADER Header;
    _Field_size_(Header.SectionCount)
        WHEA_ERROR_RECORD_SECTION_DESCRIPTOR SectionDescriptor[ANYSIZE_ARRAY];
} WHEA_ERROR_RECORD, *PWHEA_ERROR_RECORD;

CPER_FIELD_CHECK(WHEA_ERROR_RECORD, Header,              0,  128);
CPER_FIELD_CHECK(WHEA_ERROR_RECORD, SectionDescriptor, 128,   72);

#define GENPROC_PROCTYPE_XPF                 0
#define GENPROC_PROCTYPE_IPF                 1

#define GENPROC_PROCISA_X86                  0
#define GENPROC_PROCISA_IPF                  1
#define GENPROC_PROCISA_X64                  2

#define GENPROC_PROCERRTYPE_UNKNOWN          0
#define GENPROC_PROCERRTYPE_CACHE            1
#define GENPROC_PROCERRTYPE_TLB              2
#define GENPROC_PROCERRTYPE_BUS              4
#define GENPROC_PROCERRTYPE_MAE              8

#define GENPROC_OP_GENERIC                   0
#define GENPROC_OP_DATAREAD                  1
#define GENPROC_OP_DATAWRITE                 2
#define GENPROC_OP_INSTRUCTIONEXE            3

#define GENPROC_FLAGS_RESTARTABLE            0x01
#define GENPROC_FLAGS_PRECISEIP              0x02
#define GENPROC_FLAGS_OVERFLOW               0x04
#define GENPROC_FLAGS_CORRECTED              0x08

typedef union _WHEA_PROCESSOR_FAMILY_INFO {
    struct {
        ULONG Stepping:4;
        ULONG Model:4;
        ULONG Family:4;
        ULONG ProcessorType:2;
        ULONG Reserved1:2;
        ULONG ExtendedModel:4;
        ULONG ExtendedFamily:8;
        ULONG Reserved2:4;
        ULONG Reserved3;
    } DUMMYSTRUCTNAME;
    ULONGLONG AsULONGLONG;
} WHEA_PROCESSOR_FAMILY_INFO, *PWHEA_PROCESSOR_FAMILY_INFO;

typedef union _WHEA_PROCESSOR_GENERIC_ERROR_SECTION_VALIDBITS {
    struct {
        ULONGLONG ProcessorType:1;
        ULONGLONG InstructionSet:1;
        ULONGLONG ErrorType:1;
        ULONGLONG Operation:1;
        ULONGLONG Flags:1;
        ULONGLONG Level:1;
        ULONGLONG CPUVersion:1;
        ULONGLONG CPUBrandString:1;
        ULONGLONG ProcessorId:1;
        ULONGLONG TargetAddress:1;
        ULONGLONG RequesterId:1;
        ULONGLONG ResponderId:1;
        ULONGLONG InstructionPointer:1;
        ULONGLONG Reserved:51;
    } DUMMYSTRUCTNAME;
    ULONGLONG ValidBits;
} WHEA_PROCESSOR_GENERIC_ERROR_SECTION_VALIDBITS,
  *PWHEA_PROCESSOR_GENERIC_ERROR_SECTION_VALIDBITS;

typedef struct _WHEA_PROCESSOR_GENERIC_ERROR_SECTION {
    WHEA_PROCESSOR_GENERIC_ERROR_SECTION_VALIDBITS ValidBits;
    UCHAR ProcessorType;
    UCHAR InstructionSet;
    UCHAR ErrorType;
    UCHAR Operation;
    UCHAR Flags;
    UCHAR Level;
    USHORT Reserved;
    ULONGLONG CPUVersion;
    UCHAR CPUBrandString[128];
    ULONGLONG ProcessorId;
    ULONGLONG TargetAddress;
    ULONGLONG RequesterId;
    ULONGLONG ResponderId;
    ULONGLONG InstructionPointer;
} WHEA_PROCESSOR_GENERIC_ERROR_SECTION, *PWHEA_PROCESSOR_GENERIC_ERROR_SECTION;

#if WHEA_DOWNLEVEL_TYPE_NAMES
typedef WHEA_PROCESSOR_GENERIC_ERROR_SECTION_VALIDBITS
    WHEA_GENERIC_PROCESSOR_ERROR_VALIDBITS,
    *PWHEA_GENERIC_PROCESSOR_ERROR_VALIDBITS;

typedef WHEA_PROCESSOR_GENERIC_ERROR_SECTION
    WHEA_GENERIC_PROCESSOR_ERROR, *PWHEA_GENERIC_PROCESSOR_ERROR;
#endif

CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, ValidBits,            0,   8);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, ProcessorType,        8,   1);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, InstructionSet,       9,   1);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, ErrorType,           10,   1);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, Operation,           11,   1);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, Flags,               12,   1);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, Level,               13,   1);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, Reserved,            14,   2);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, CPUVersion,          16,   8);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, CPUBrandString,      24, 128);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, ProcessorId,        152,   8);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, TargetAddress,      160,   8);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, RequesterId,        168,   8);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, ResponderId,        176,   8);
CPER_FIELD_CHECK(WHEA_PROCESSOR_GENERIC_ERROR_SECTION, InstructionPointer, 184,   8);

#define XPF_CACHE_CHECK_TRANSACTIONTYPE_INSTRUCTION     0
#define XPF_CACHE_CHECK_TRANSACTIONTYPE_DATAACCESS      1
#define XPF_CACHE_CHECK_TRANSACTIONTYPE_GENERIC         2

#define XPF_CACHE_CHECK_OPERATION_GENERIC               0
#define XPF_CACHE_CHECK_OPERATION_GENREAD               1
#define XPF_CACHE_CHECK_OPERATION_GENWRITE              2
#define XPF_CACHE_CHECK_OPERATION_DATAREAD              3
#define XPF_CACHE_CHECK_OPERATION_DATAWRITE             4
#define XPF_CACHE_CHECK_OPERATION_INSTRUCTIONFETCH      5
#define XPF_CACHE_CHECK_OPERATION_PREFETCH              6
#define XPF_CACHE_CHECK_OPERATION_EVICTION              7
#define XPF_CACHE_CHECK_OPERATION_SNOOP                 8

typedef union _WHEA_XPF_CACHE_CHECK {
    struct {
        ULONGLONG TransactionTypeValid:1;
        ULONGLONG OperationValid:1;
        ULONGLONG LevelValid:1;
        ULONGLONG ProcessorContextCorruptValid:1;
        ULONGLONG UncorrectedValid:1;
        ULONGLONG PreciseIPValid:1;
        ULONGLONG RestartableIPValid:1;
        ULONGLONG OverflowValid:1;
        ULONGLONG ReservedValid:8;

        ULONGLONG TransactionType:2;
        ULONGLONG Operation:4;
        ULONGLONG Level:3;
        ULONGLONG ProcessorContextCorrupt:1;
        ULONGLONG Uncorrected:1;
        ULONGLONG PreciseIP:1;
        ULONGLONG RestartableIP:1;
        ULONGLONG Overflow:1;

        ULONGLONG Reserved:34;
    } DUMMYSTRUCTNAME;
    ULONGLONG XpfCacheCheck;
} WHEA_XPF_CACHE_CHECK, *PWHEA_XPF_CACHE_CHECK;

#define XPF_TLB_CHECK_TRANSACTIONTYPE_INSTRUCTION     0
#define XPF_TLB_CHECK_TRANSACTIONTYPE_DATAACCESS      1
#define XPF_TLB_CHECK_TRANSACTIONTYPE_GENERIC         2

#define XPF_TLB_CHECK_OPERATION_GENERIC               0
#define XPF_TLB_CHECK_OPERATION_GENREAD               1
#define XPF_TLB_CHECK_OPERATION_GENWRITE              2
#define XPF_TLB_CHECK_OPERATION_DATAREAD              3
#define XPF_TLB_CHECK_OPERATION_DATAWRITE             4
#define XPF_TLB_CHECK_OPERATION_INSTRUCTIONFETCH      5
#define XPF_TLB_CHECK_OPERATION_PREFETCH              6

typedef union _WHEA_XPF_TLB_CHECK {
    struct {
        ULONGLONG TransactionTypeValid:1;
        ULONGLONG OperationValid:1;
        ULONGLONG LevelValid:1;
        ULONGLONG ProcessorContextCorruptValid:1;
        ULONGLONG UncorrectedValid:1;
        ULONGLONG PreciseIPValid:1;
        ULONGLONG RestartableIPValid:1;
        ULONGLONG OverflowValid:1;
        ULONGLONG ReservedValid:8;

        ULONGLONG TransactionType:2;
        ULONGLONG Operation:4;
        ULONGLONG Level:3;
        ULONGLONG ProcessorContextCorrupt:1;
        ULONGLONG Uncorrected:1;
        ULONGLONG PreciseIP:1;
        ULONGLONG RestartableIP:1;
        ULONGLONG Overflow:1;
        ULONGLONG Reserved:34;
    } DUMMYSTRUCTNAME;
    ULONGLONG XpfTLBCheck;
} WHEA_XPF_TLB_CHECK, *PWHEA_XPF_TLB_CHECK;

#define XPF_BUS_CHECK_TRANSACTIONTYPE_INSTRUCTION     0
#define XPF_BUS_CHECK_TRANSACTIONTYPE_DATAACCESS      1
#define XPF_BUS_CHECK_TRANSACTIONTYPE_GENERIC         2

#define XPF_BUS_CHECK_OPERATION_GENERIC               0
#define XPF_BUS_CHECK_OPERATION_GENREAD               1
#define XPF_BUS_CHECK_OPERATION_GENWRITE              2
#define XPF_BUS_CHECK_OPERATION_DATAREAD              3
#define XPF_BUS_CHECK_OPERATION_DATAWRITE             4
#define XPF_BUS_CHECK_OPERATION_INSTRUCTIONFETCH      5
#define XPF_BUS_CHECK_OPERATION_PREFETCH              6

#define XPF_BUS_CHECK_PARTICIPATION_PROCORIGINATED    0
#define XPF_BUS_CHECK_PARTICIPATION_PROCRESPONDED     1
#define XPF_BUS_CHECK_PARTICIPATION_PROCOBSERVED      2
#define XPF_BUS_CHECK_PARTICIPATION_GENERIC           3

#define XPF_BUS_CHECK_ADDRESS_MEMORY                  0
#define XPF_BUS_CHECK_ADDRESS_RESERVED                1
#define XPF_BUS_CHECK_ADDRESS_IO                      2
#define XPF_BUS_CHECK_ADDRESS_OTHER                   3

typedef union _WHEA_XPF_BUS_CHECK {
    struct {
        ULONGLONG TransactionTypeValid:1;
        ULONGLONG OperationValid:1;
        ULONGLONG LevelValid:1;
        ULONGLONG ProcessorContextCorruptValid:1;
        ULONGLONG UncorrectedValid:1;
        ULONGLONG PreciseIPValid:1;
        ULONGLONG RestartableIPValid:1;
        ULONGLONG OverflowValid:1;
        ULONGLONG ParticipationValid:1;
        ULONGLONG TimeoutValid:1;
        ULONGLONG AddressSpaceValid:1;
        ULONGLONG ReservedValid:5;

        ULONGLONG TransactionType:2;
        ULONGLONG Operation:4;
        ULONGLONG Level:3;
        ULONGLONG ProcessorContextCorrupt:1;
        ULONGLONG Uncorrected:1;
        ULONGLONG PreciseIP:1;
        ULONGLONG RestartableIP:1;
        ULONGLONG Overflow:1;
        ULONGLONG Participation:2;
        ULONGLONG Timeout:1;
        ULONGLONG AddressSpace:2;
        ULONGLONG Reserved:29;
    } DUMMYSTRUCTNAME;
    ULONGLONG XpfBusCheck;
} WHEA_XPF_BUS_CHECK, *PWHEA_XPF_BUS_CHECK;

#define XPF_MS_CHECK_ERRORTYPE_NOERROR               0
#define XPF_MS_CHECK_ERRORTYPE_UNCLASSIFIED          1
#define XPF_MS_CHECK_ERRORTYPE_MCROMPARITY           2
#define XPF_MS_CHECK_ERRORTYPE_EXTERNAL              3
#define XPF_MS_CHECK_ERRORTYPE_FRC                   4
#define XPF_MS_CHECK_ERRORTYPE_INTERNALUNCLASSIFIED  5

typedef union _WHEA_XPF_MS_CHECK {
    struct {
        ULONGLONG ErrorTypeValid:1;
        ULONGLONG ProcessorContextCorruptValid:1;
        ULONGLONG UncorrectedValid:1;
        ULONGLONG PreciseIPValid:1;
        ULONGLONG RestartableIPValid:1;
        ULONGLONG OverflowValid:1;
        ULONGLONG ReservedValue:10;

        ULONGLONG ErrorType:3;
        ULONGLONG ProcessorContextCorrupt:1;
        ULONGLONG Uncorrected:1;
        ULONGLONG PreciseIP:1;
        ULONGLONG RestartableIP:1;
        ULONGLONG Overflow:1;
        ULONGLONG Reserved:40;
    } DUMMYSTRUCTNAME;
    ULONGLONG XpfMsCheck;
} WHEA_XPF_MS_CHECK, *PWHEA_XPF_MS_CHECK;

typedef union _WHEA_XPF_PROCINFO_VALIDBITS {
    struct {
        ULONGLONG CheckInfo:1;
        ULONGLONG TargetId:1;
        ULONGLONG RequesterId:1;
        ULONGLONG ResponderId:1;
        ULONGLONG InstructionPointer:1;
        ULONGLONG Reserved:59;
    } DUMMYSTRUCTNAME;
    ULONGLONG ValidBits;
} WHEA_XPF_PROCINFO_VALIDBITS, *PWHEA_XPF_PROCINFO_VALIDBITS;

typedef struct _WHEA_XPF_PROCINFO {
    GUID CheckInfoId;
    WHEA_XPF_PROCINFO_VALIDBITS ValidBits;
    union {
        WHEA_XPF_CACHE_CHECK CacheCheck;
        WHEA_XPF_TLB_CHECK TlbCheck;
        WHEA_XPF_BUS_CHECK BusCheck;
        WHEA_XPF_MS_CHECK MsCheck;
        ULONGLONG AsULONGLONG;
    } CheckInfo;
    ULONGLONG TargetId;
    ULONGLONG RequesterId;
    ULONGLONG ResponderId;
    ULONGLONG InstructionPointer;
} WHEA_XPF_PROCINFO, *PWHEA_XPF_PROCINFO;

typedef struct _WHEA_X86_REGISTER_STATE {
    ULONG Eax;
    ULONG Ebx;
    ULONG Ecx;
    ULONG Edx;
    ULONG Esi;
    ULONG Edi;
    ULONG Ebp;
    ULONG Esp;
    USHORT Cs;
    USHORT Ds;
    USHORT Ss;
    USHORT Es;
    USHORT Fs;
    USHORT Gs;
    ULONG Eflags;
    ULONG Eip;
    ULONG Cr0;
    ULONG Cr1;
    ULONG Cr2;
    ULONG Cr3;
    ULONG Cr4;
    ULONGLONG Gdtr;
    ULONGLONG Idtr;
    USHORT Ldtr;
    USHORT Tr;
} WHEA_X86_REGISTER_STATE, *PWHEA_X86_REGISTER_STATE;

typedef struct DECLSPEC_ALIGN(16) _WHEA128A {
    ULONGLONG Low;
    LONGLONG High;
} WHEA128A, *PWHEA128A;

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#pragma warning(disable:4324) // structure padded due to __declspec(align())
#endif
#endif

typedef struct _WHEA_X64_REGISTER_STATE {
    ULONGLONG Rax;
    ULONGLONG Rbx;
    ULONGLONG Rcx;
    ULONGLONG Rdx;
    ULONGLONG Rsi;
    ULONGLONG Rdi;
    ULONGLONG Rbp;
    ULONGLONG Rsp;
    ULONGLONG R8;
    ULONGLONG R9;
    ULONGLONG R10;
    ULONGLONG R11;
    ULONGLONG R12;
    ULONGLONG R13;
    ULONGLONG R14;
    ULONGLONG R15;
    USHORT Cs;
    USHORT Ds;
    USHORT Ss;
    USHORT Es;
    USHORT Fs;
    USHORT Gs;
    ULONG Reserved;
    ULONGLONG Rflags;
    ULONGLONG Eip;
    ULONGLONG Cr0;
    ULONGLONG Cr1;
    ULONGLONG Cr2;
    ULONGLONG Cr3;
    ULONGLONG Cr4;
    ULONGLONG Cr8;
    WHEA128A Gdtr;
    WHEA128A Idtr;
    USHORT Ldtr;
    USHORT Tr;
} WHEA_X64_REGISTER_STATE, *PWHEA_X64_REGISTER_STATE;

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(pop)
#endif
#endif

#define XPF_CONTEXT_INFO_UNCLASSIFIEDDATA       0
#define XPF_CONTEXT_INFO_MSRREGISTERS           1
#define XPF_CONTEXT_INFO_32BITCONTEXT           2
#define XPF_CONTEXT_INFO_64BITCONTEXT           3
#define XPF_CONTEXT_INFO_FXSAVE                 4
#define XPF_CONTEXT_INFO_32BITDEBUGREGS         5
#define XPF_CONTEXT_INFO_64BITDEBUGREGS         6
#define XPF_CONTEXT_INFO_MMREGISTERS            7

typedef struct _WHEA_XPF_CONTEXT_INFO {
    USHORT RegisterContextType;
    USHORT RegisterDataSize;
    ULONG MSRAddress;
    ULONGLONG MmRegisterAddress;
} WHEA_XPF_CONTEXT_INFO, *PWHEA_XPF_CONTEXT_INFO;

typedef union _WHEA_XPF_PROCESSOR_ERROR_SECTION_VALIDBITS {
    struct {
        ULONGLONG LocalAPICId:1;
        ULONGLONG CpuId:1;
        ULONGLONG ProcInfoCount:6;
        ULONGLONG ContextInfoCount:6;
        ULONGLONG Reserved:50;
    } DUMMYSTRUCTNAME;
    ULONGLONG ValidBits;
} WHEA_XPF_PROCESSOR_ERROR_SECTION_VALIDBITS,
  *PWHEA_XPF_PROCESSOR_ERROR_SECTION_VALIDBITS;

typedef struct _WHEA_XPF_PROCESSOR_ERROR_SECTION {
    WHEA_XPF_PROCESSOR_ERROR_SECTION_VALIDBITS ValidBits;
    ULONGLONG LocalAPICId;
    UCHAR CpuId[48];
    UCHAR VariableInfo[ANYSIZE_ARRAY];
} WHEA_XPF_PROCESSOR_ERROR_SECTION, *PWHEA_XPF_PROCESSOR_ERROR_SECTION;

#if WHEA_DOWNLEVEL_TYPE_NAMES
typedef struct WHEA_XPF_PROCESSOR_ERROR_SECTION_VALIDBITS
    WHEA_XPF_PROCESSOR_ERROR_VALIDBITS, *PWHEA_XPF_PROCESSOR_ERROR_VALIDBITS;

typedef struct WHEA_XPF_PROCESSOR_ERROR_SECTION
    WHEA_XPF_PROCESSOR_ERROR, *PWHEA_XPF_PROCESSOR_ERROR;
#endif

CPER_FIELD_CHECK(WHEA_XPF_PROCINFO, CheckInfoId,         0, 16);
CPER_FIELD_CHECK(WHEA_XPF_PROCINFO, ValidBits,          16,  8);
CPER_FIELD_CHECK(WHEA_XPF_PROCINFO, CheckInfo,          24,  8);
CPER_FIELD_CHECK(WHEA_XPF_PROCINFO, TargetId,           32,  8);
CPER_FIELD_CHECK(WHEA_XPF_PROCINFO, RequesterId,        40,  8);
CPER_FIELD_CHECK(WHEA_XPF_PROCINFO, ResponderId,        48,  8);
CPER_FIELD_CHECK(WHEA_XPF_PROCINFO, InstructionPointer, 56,  8);

CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Eax,       0,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Ebx,       4,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Ecx,       8,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Edx,      12,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Esi,      16,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Edi,      20,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Ebp,      24,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Esp,      28,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Cs,       32,   2);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Ds,       34,   2);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Ss,       36,   2);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Es,       38,   2);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Fs,       40,   2);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Gs,       42,   2);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Eflags,   44,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Eip,      48,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Cr0,      52,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Cr1,      56,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Cr2,      60,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Cr3,      64,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Cr4,      68,   4);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Gdtr,     72,   8);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Idtr,     80,   8);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Ldtr,     88,   2);
CPER_FIELD_CHECK(WHEA_X86_REGISTER_STATE, Tr,       90,   2);

CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Rax,       0,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Rbx,       8,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Rcx,      16,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Rdx,      24,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Rsi,      32,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Rdi,      40,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Rbp,      48,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Rsp,      56,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, R8,       64,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, R9,       72,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, R10,      80,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, R11,      88,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, R12,      96,   8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, R13,      104,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, R14,      112,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, R15,      120,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Cs,       128,  2);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Ds,       130,  2);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Ss,       132,  2);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Es,       134,  2);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Fs,       136,  2);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Gs,       138,  2);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Reserved, 140,  4);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Rflags,   144,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Eip,      152,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Cr0,      160,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Cr1,      168,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Cr2,      176,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Cr3,      184,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Cr4,      192,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Cr8,      200,  8);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Gdtr,     208, 16);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Idtr,     224, 16);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Ldtr,     240,  2);
CPER_FIELD_CHECK(WHEA_X64_REGISTER_STATE, Tr,       242,  2);

CPER_FIELD_CHECK(WHEA_XPF_CONTEXT_INFO, RegisterContextType,  0, 2);
CPER_FIELD_CHECK(WHEA_XPF_CONTEXT_INFO, RegisterDataSize,     2, 2);
CPER_FIELD_CHECK(WHEA_XPF_CONTEXT_INFO, MSRAddress,           4, 4);
CPER_FIELD_CHECK(WHEA_XPF_CONTEXT_INFO, MmRegisterAddress,    8, 8);

CPER_FIELD_CHECK(WHEA_XPF_PROCESSOR_ERROR_SECTION, ValidBits,     0,  8);
CPER_FIELD_CHECK(WHEA_XPF_PROCESSOR_ERROR_SECTION, LocalAPICId,   8,  8);
CPER_FIELD_CHECK(WHEA_XPF_PROCESSOR_ERROR_SECTION, CpuId,        16, 48);
CPER_FIELD_CHECK(WHEA_XPF_PROCESSOR_ERROR_SECTION, VariableInfo, 64, ANYSIZE_ARRAY);

typedef union _WHEA_MEMORY_ERROR_SECTION_VALIDBITS {
    struct {
        ULONGLONG ErrorStatus:1;
        ULONGLONG PhysicalAddress:1;
        ULONGLONG PhysicalAddressMask:1;
        ULONGLONG Node:1;
        ULONGLONG Card:1;
        ULONGLONG Module:1;
        ULONGLONG Bank:1;
        ULONGLONG Device:1;
        ULONGLONG Row:1;
        ULONGLONG Column:1;
        ULONGLONG BitPosition:1;
        ULONGLONG RequesterId:1;
        ULONGLONG ResponderId:1;
        ULONGLONG TargetId:1;
        ULONGLONG ErrorType:1;
        ULONGLONG Reserved:49;
    } DUMMYSTRUCTNAME;
    ULONGLONG ValidBits;
} WHEA_MEMORY_ERROR_SECTION_VALIDBITS,
  *PWHEA_MEMORY_ERROR_SECTION_VALIDBITS;

#define WHEA_MEMERRTYPE_UNKNOWN                 0x00
#define WHEA_MEMERRTYPE_NOERROR                 0x01
#define WHEA_MEMERRTYPE_SINGLEBITECC            0x02
#define WHEA_MEMERRTYPE_MULTIBITECC             0x03
#define WHEA_MEMERRTYPE_SINGLESYMCHIPKILL       0x04
#define WHEA_MEMERRTYPE_MULTISYMCHIPKILL        0x05
#define WHEA_MEMERRTYPE_MASTERABORT             0x06
#define WHEA_MEMERRTYPE_TARGETABORT             0x07
#define WHEA_MEMERRTYPE_PARITYERROR             0x08
#define WHEA_MEMERRTYPE_WATCHDOGTIMEOUT         0x09
#define WHEA_MEMERRTYPE_INVALIDADDRESS          0x0A
#define WHEA_MEMERRTYPE_MIRRORBROKEN            0x0B
#define WHEA_MEMERRTYPE_MEMORYSPARING           0x0C

typedef struct _WHEA_MEMORY_ERROR_SECTION {
    WHEA_MEMORY_ERROR_SECTION_VALIDBITS ValidBits;
    WHEA_ERROR_STATUS ErrorStatus;
    ULONGLONG PhysicalAddress;
    ULONGLONG PhysicalAddressMask;
    USHORT Node;
    USHORT Card;
    USHORT Module;
    USHORT Bank;
    USHORT Device;
    USHORT Row;
    USHORT Column;
    USHORT BitPosition;
    ULONGLONG RequesterId;
    ULONGLONG ResponderId;
    ULONGLONG TargetId;
    UCHAR ErrorType;
} WHEA_MEMORY_ERROR_SECTION, *PWHEA_MEMORY_ERROR_SECTION;

#if WHEA_DOWNLEVEL_TYPE_NAMES
typedef WHEA_MEMORY_ERROR_SECTION_VALIDBITS
    WHEA_MEMORY_ERROR_VALIDBITS, *PWHEA_MEMORY_ERROR_VALIDBITS;

typedef WHEA_MEMORY_ERROR_SECTION
    WHEA_MEMORY_ERROR, *PWHEA_MEMORY_ERROR;
#endif

CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, ValidBits,            0, 8);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, ErrorStatus,          8, 8);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, PhysicalAddress,     16, 8);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, PhysicalAddressMask, 24, 8);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, Node,                32, 2);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, Card,                34, 2);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, Module,              36, 2);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, Bank,                38, 2);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, Device,              40, 2);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, Row,                 42, 2);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, Column,              44, 2);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, BitPosition,         46, 2);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, RequesterId,         48, 8);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, ResponderId,         56, 8);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, TargetId,            64, 8);
CPER_FIELD_CHECK(WHEA_MEMORY_ERROR_SECTION, ErrorType,           72, 1);

typedef union _WHEA_PCIEXPRESS_ERROR_SECTION_VALIDBITS {
    struct {
        ULONGLONG PortType:1;
        ULONGLONG Version:1;
        ULONGLONG CommandStatus:1;
        ULONGLONG DeviceId:1;
        ULONGLONG DeviceSerialNumber:1;
        ULONGLONG BridgeControlStatus:1;
        ULONGLONG ExpressCapability:1;
        ULONGLONG AerInfo:1;
        ULONGLONG Reserved:56;
    } DUMMYSTRUCTNAME;
    ULONGLONG ValidBits;
} WHEA_PCIEXPRESS_ERROR_SECTION_VALIDBITS,
  *PWHEA_PCIEXPRESS_ERROR_SECTION_VALIDBITS;

typedef struct _WHEA_PCIEXPRESS_DEVICE_ID {
    USHORT VendorID;
    USHORT DeviceID;
    ULONG ClassCode:24;
    ULONG FunctionNumber:8;
    ULONG DeviceNumber:8;
    ULONG Segment:16;
    ULONG PrimaryBusNumber:8;
    ULONG SecondaryBusNumber:8;
    ULONG Reserved1:3;
    ULONG SlotNumber:13;
    ULONG Reserved2:8;
} WHEA_PCIEXPRESS_DEVICE_ID, *PWHEA_PCIEXPRESS_DEVICE_ID;

typedef union _WHEA_PCIEXPRESS_VERSION {
    struct {
        UCHAR MinorVersion;
        UCHAR MajorVersion;
        USHORT Reserved;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_PCIEXPRESS_VERSION, *PWHEA_PCIEXPRESS_VERSION;

typedef union _WHEA_PCIEXPRESS_COMMAND_STATUS {
    struct {
        USHORT Command;
        USHORT Status;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_PCIEXPRESS_COMMAND_STATUS, *PWHEA_PCIEXPRESS_COMMAND_STATUS;

typedef union _WHEA_PCIEXPRESS_BRIDGE_CONTROL_STATUS {
    struct {
        USHORT BridgeSecondaryStatus;
        USHORT BridgeControl;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_PCIEXPRESS_BRIDGE_CONTROL_STATUS,
    *PWHEA_PCIEXPRESS_BRIDGE_CONTROL_STATUS;

typedef enum _WHEA_PCIEXPRESS_DEVICE_TYPE {
    WheaPciExpressEndpoint = 0,
    WheaPciExpressLegacyEndpoint,
    WheaPciExpressRootPort = 4,
    WheaPciExpressUpstreamSwitchPort,
    WheaPciExpressDownstreamSwitchPort,
    WheaPciExpressToPciXBridge,
    WheaPciXToExpressBridge,
    WheaPciExpressRootComplexIntegratedEndpoint,
    WheaPciExpressRootComplexEventCollector
} WHEA_PCIEXPRESS_DEVICE_TYPE;

typedef struct _WHEA_PCIEXPRESS_ERROR_SECTION {
    WHEA_PCIEXPRESS_ERROR_SECTION_VALIDBITS ValidBits;
    WHEA_PCIEXPRESS_DEVICE_TYPE PortType;
    WHEA_PCIEXPRESS_VERSION Version;
    WHEA_PCIEXPRESS_COMMAND_STATUS CommandStatus;
    ULONG Reserved;
    WHEA_PCIEXPRESS_DEVICE_ID DeviceId;
    ULONGLONG DeviceSerialNumber;
    WHEA_PCIEXPRESS_BRIDGE_CONTROL_STATUS BridgeControlStatus;
    UCHAR ExpressCapability[60];
    UCHAR AerInfo[96];
} WHEA_PCIEXPRESS_ERROR_SECTION, *PWHEA_PCIEXPRESS_ERROR_SECTION;

#if WHEA_DOWNLEVEL_TYPE_NAMES
typedef WHEA_PCIEXPRESS_ERROR_SECTION_VALIDBITS
    WHEA_PCIEXPRESS_ERROR_VALIDBITS,
    *PWHEA_PCIEXPRESS_ERROR_VALIDBITS;
typedef WHEA_PCIEXPRESS_ERROR_SECTION
    WHEA_PCIEXPRESS_ERROR, *PWHEA_PCIEXPRESS_ERROR;
#endif

CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, ValidBits,             0,  8);
CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, PortType,              8,  4);
CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, Version,              12,  4);
CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, CommandStatus,        16,  4);
CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, Reserved,             20,  4);
CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, DeviceId,             24, 16);
CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, DeviceSerialNumber,   40,  8);
CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, BridgeControlStatus,  48,  4);
CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, ExpressCapability,    52, 60);
CPER_FIELD_CHECK(WHEA_PCIEXPRESS_ERROR_SECTION, AerInfo,             112, 96);

#define PCIXBUS_ERRTYPE_UNKNOWN             0x0000
#define PCIXBUS_ERRTYPE_DATAPARITY          0x0001
#define PCIXBUS_ERRTYPE_SYSTEM              0x0002
#define PCIXBUS_ERRTYPE_MASTERABORT         0x0003
#define PCIXBUS_ERRTYPE_BUSTIMEOUT          0x0004
#define PCIXBUS_ERRTYPE_MASTERDATAPARITY    0x0005
#define PCIXBUS_ERRTYPE_ADDRESSPARITY       0x0006
#define PCIXBUS_ERRTYPE_COMMANDPARITY       0x0007

typedef union _WHEA_PCIXBUS_ERROR_SECTION_VALIDBITS {
    struct {
        ULONGLONG ErrorStatus:1;
        ULONGLONG ErrorType:1;
        ULONGLONG BusId:1;
        ULONGLONG BusAddress:1;
        ULONGLONG BusData:1;
        ULONGLONG BusCommand:1;
        ULONGLONG RequesterId:1;
        ULONGLONG CompleterId:1;
        ULONGLONG TargetId:1;
        ULONGLONG Reserved:55;
    } DUMMYSTRUCTNAME;
    ULONGLONG ValidBits;
} WHEA_PCIXBUS_ERROR_SECTION_VALIDBITS, *PWHEA_PCIXBUS_ERROR_SECTION_VALIDBITS;

typedef union _WHEA_PCIXBUS_ID {
    struct {
        UCHAR BusNumber;
        UCHAR BusSegment;
    } DUMMYSTRUCTNAME;
    USHORT AsUSHORT;
} WHEA_PCIXBUS_ID, *PWHEA_PCIXBUS_ID;

typedef union _WHEA_PCIXBUS_COMMAND {
    struct {
        ULONGLONG Command:56;
        ULONGLONG PCIXCommand:1;
        ULONGLONG Reserved:7;
    } DUMMYSTRUCTNAME;
    ULONGLONG AsULONGLONG;
} WHEA_PCIXBUS_COMMAND, *PWHEA_PCIXBUS_COMMAND;

typedef struct _WHEA_PCIXBUS_ERROR_SECTION {
    WHEA_PCIXBUS_ERROR_SECTION_VALIDBITS ValidBits;
    WHEA_ERROR_STATUS ErrorStatus;
    USHORT ErrorType;
    WHEA_PCIXBUS_ID BusId;
    ULONG Reserved;
    ULONGLONG BusAddress;
    ULONGLONG BusData;
    WHEA_PCIXBUS_COMMAND BusCommand;
    ULONGLONG RequesterId;
    ULONGLONG CompleterId;
    ULONGLONG TargetId;
} WHEA_PCIXBUS_ERROR_SECTION, *PWHEA_PCIXBUS_ERROR_SECTION;

#if WHEA_DOWNLEVEL_TYPE_NAMES
typedef WHEA_PCIXBUS_ERROR_SECTION_VALIDBITS
    WHEA_PCIXBUS_ERROR_VALIDBITS,
    *PWHEA_PCIXBUS_ERROR_VALIDBITS;

typedef WHEA_PCIXBUS_ERROR_SECTION
    WHEA_PCIXBUS_ERROR, *PWHEA_PCIXBUS_ERROR;
#endif

CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, ValidBits,    0, 8);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, ErrorStatus,  8, 8);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, ErrorType,   16, 2);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, BusId,       18, 2);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, Reserved,    20, 4);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, BusAddress,  24, 8);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, BusData,     32, 8);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, BusCommand,  40, 8);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, RequesterId, 48, 8);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, CompleterId, 56, 8);
CPER_FIELD_CHECK(WHEA_PCIXBUS_ERROR_SECTION, TargetId,    64, 8);

typedef union _WHEA_PCIXDEVICE_ERROR_SECTION_VALIDBITS {
    struct {
        ULONGLONG ErrorStatus:1;
        ULONGLONG IdInfo:1;
        ULONGLONG MemoryNumber:1;
        ULONGLONG IoNumber:1;
        ULONGLONG RegisterDataPairs:1;
        ULONGLONG Reserved:59;
    } DUMMYSTRUCTNAME;
    ULONGLONG ValidBits;
} WHEA_PCIXDEVICE_ERROR_SECTION_VALIDBITS,
  *PWHEA_PCIXDEVICE_ERROR_SECTION_VALIDBITS;

typedef struct _WHEA_PCIXDEVICE_ID {
    USHORT VendorId;
    USHORT DeviceId;
    ULONG ClassCode:24;
    ULONG FunctionNumber:8;
    ULONG DeviceNumber:8;
    ULONG BusNumber:8;
    ULONG SegmentNumber:8;
    ULONG Reserved1:8;
    ULONG Reserved2;
} WHEA_PCIXDEVICE_ID, *PWHEA_PCIXDEVICE_ID;

typedef struct WHEA_PCIXDEVICE_REGISTER_PAIR {
    ULONGLONG Register;
    ULONGLONG Data;
} WHEA_PCIXDEVICE_REGISTER_PAIR, *PWHEA_PCIXDEVICE_REGISTER_PAIR;

typedef struct _WHEA_PCIXDEVICE_ERROR_SECTION {
    WHEA_PCIXDEVICE_ERROR_SECTION_VALIDBITS ValidBits;
    WHEA_ERROR_STATUS ErrorStatus;
    WHEA_PCIXDEVICE_ID IdInfo;
    ULONG MemoryNumber;
    ULONG IoNumber;
    WHEA_PCIXDEVICE_REGISTER_PAIR RegisterDataPairs[ANYSIZE_ARRAY];
} WHEA_PCIXDEVICE_ERROR_SECTION, *PWHEA_PCIXDEVICE_ERROR_SECTION;

#if WHEA_DOWNLEVEL_TYPE_NAMES
typedef WHEA_PCIXDEVICE_ERROR_SECTION_VALIDBITS
    WHEA_PCIXDEVICE_ERROR_VALIDBITS, *PWHEA_PCIXDEVICE_ERROR_VALIDBITS;
typedef WHEA_PCIXDEVICE_ERROR_SECTION
    WHEA_PCIXDEVICE_ERROR, *PWHEA_PCIXDEVICE_ERROR;
#endif

CPER_FIELD_CHECK(WHEA_PCIXDEVICE_ERROR_SECTION, ValidBits,          0,  8);
CPER_FIELD_CHECK(WHEA_PCIXDEVICE_ERROR_SECTION, ErrorStatus,        8,  8);
CPER_FIELD_CHECK(WHEA_PCIXDEVICE_ERROR_SECTION, IdInfo,            16, 16);
CPER_FIELD_CHECK(WHEA_PCIXDEVICE_ERROR_SECTION, MemoryNumber,      32,  4);
CPER_FIELD_CHECK(WHEA_PCIXDEVICE_ERROR_SECTION, IoNumber,          36,  4);
CPER_FIELD_CHECK(WHEA_PCIXDEVICE_ERROR_SECTION, RegisterDataPairs, 40, 16);

#define WHEA_FIRMWARE_RECORD_TYPE_IPFSAL 0

typedef struct _WHEA_FIRMWARE_ERROR_RECORD_REFERENCE {
    UCHAR Type;
    UCHAR Reserved[7];
    ULONGLONG FirmwareRecordId;
} WHEA_FIRMWARE_ERROR_RECORD_REFERENCE, *PWHEA_FIRMWARE_ERROR_RECORD_REFERENCE;

#if WHEA_DOWNLEVEL_TYPE_NAMES

typedef WHEA_FIRMWARE_ERROR_RECORD_REFERENCE
    WHEA_FIRMWARE_RECORD, *PWHEA_FIRMWARE_RECORD;

#endif

CPER_FIELD_CHECK(WHEA_FIRMWARE_ERROR_RECORD_REFERENCE, Type,             0,  1);
CPER_FIELD_CHECK(WHEA_FIRMWARE_ERROR_RECORD_REFERENCE, Reserved,         1,  7);
CPER_FIELD_CHECK(WHEA_FIRMWARE_ERROR_RECORD_REFERENCE, FirmwareRecordId, 8,  8);

typedef union _MCG_STATUS {
    struct {
        ULONG RestartIpValid:1;
        ULONG ErrorIpValid:1;
        ULONG MachineCheckInProgress:1;
        ULONG Reserved1:29;
        ULONG Reserved2;
    } DUMMYSTRUCTNAME;
    ULONGLONG QuadPart;
} MCG_STATUS, *PMCG_STATUS;

typedef union _MCI_STATUS {
    struct {
        USHORT McaErrorCode;
        USHORT ModelErrorCode;
        ULONG OtherInformation : 23;
        ULONG ActionRequired : 1;
        ULONG Signalling : 1;
        ULONG ContextCorrupt : 1;
        ULONG AddressValid : 1;
        ULONG MiscValid : 1;
        ULONG ErrorEnabled : 1;
        ULONG UncorrectedError : 1;
        ULONG StatusOverFlow : 1;
        ULONG Valid : 1;
    } DUMMYSTRUCTNAME;
    ULONG64 QuadPart;
} MCI_STATUS, *PMCI_STATUS;

typedef enum _WHEA_CPU_VENDOR {
    WheaCpuVendorOther = 0,
    WheaCpuVendorIntel,
    WheaCpuVendorAmd
} WHEA_CPU_VENDOR, *PWHEA_CPU_VENDOR;

#define WHEA_XPF_MCA_EXTREG_MAX_COUNT            24
#define WHEA_XPF_MCA_SECTION_VERSION             1

typedef struct _WHEA_XPF_MCA_SECTION {
    ULONG               VersionNumber;
    WHEA_CPU_VENDOR     CpuVendor;
    LARGE_INTEGER       Timestamp;
    ULONG               ProcessorNumber;
    MCG_STATUS          GlobalStatus;
    ULONGLONG           InstructionPointer;
    ULONG               BankNumber;
    MCI_STATUS          Status;
    ULONGLONG           Address;
    ULONGLONG           Misc;
    ULONG               ExtendedRegisterCount;
    ULONG               Reserved2;
    ULONGLONG           ExtendedRegisters[WHEA_XPF_MCA_EXTREG_MAX_COUNT];
} WHEA_XPF_MCA_SECTION, *PWHEA_XPF_MCA_SECTION;

typedef union _WHEA_NMI_ERROR_SECTION_FLAGS {
    struct {
        ULONG HypervisorError:1;
        ULONG Reserved:31;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_NMI_ERROR_SECTION_FLAGS, *PWHEA_NMI_ERROR_SECTION_FLAGS;

typedef struct _WHEA_NMI_ERROR_SECTION {
    UCHAR Data[8];
    WHEA_NMI_ERROR_SECTION_FLAGS Flags;
} WHEA_NMI_ERROR_SECTION, *PWHEA_NMI_ERROR_SECTION;

#include <poppack.h>


/* 2dce8bb1-bdd7-450e-b9ad-9cf4ebd4f890 */
DEFINE_GUID(CMC_NOTIFY_TYPE_GUID,
            0x2dce8bb1, 0xbdd7, 0x450e, 0xb9, 0xad,
            0x9c, 0xf4, 0xeb, 0xd4, 0xf8, 0x90);

/* 4e292f96-d843-4a55-a8c2-d481f27ebeee */
DEFINE_GUID(CPE_NOTIFY_TYPE_GUID,
            0x4e292f96, 0xd843, 0x4a55, 0xa8, 0xc2,
            0xd4, 0x81, 0xf2, 0x7e, 0xbe, 0xee);

/* e8f56ffe-919c-4cc5-ba88-65abe14913bb */
DEFINE_GUID(MCE_NOTIFY_TYPE_GUID,
            0xe8f56ffe, 0x919c, 0x4cc5, 0xba, 0x88,
            0x65, 0xab, 0xe1, 0x49, 0x13, 0xbb);

/* cf93c01f-1a16-4dfc-b8bc-9c4daf67c104 */
DEFINE_GUID(PCIe_NOTIFY_TYPE_GUID,
            0xcf93c01f, 0x1a16, 0x4dfc, 0xb8, 0xbc,
            0x9c, 0x4d, 0xaf, 0x67, 0xc1, 0x04);

/* cc5263e8-9308-454a-89d0-340bd39bc98e */
DEFINE_GUID(INIT_NOTIFY_TYPE_GUID,
            0xcc5263e8, 0x9308, 0x454a, 0x89, 0xd0,
            0x34, 0x0b, 0xd3, 0x9b, 0xc9, 0x8e);

/* 5bad89ff-b7e6-42c9-814a-cf2485d6e98a */
DEFINE_GUID(NMI_NOTIFY_TYPE_GUID,
            0x5bad89ff, 0xb7e6, 0x42c9, 0x81, 0x4a,
            0xcf, 0x24, 0x85, 0xd6, 0xe9, 0x8a);

/* 3d61a466-ab40-409a-a698-f362d464b38f */
DEFINE_GUID(BOOT_NOTIFY_TYPE_GUID,
            0x3d61a466, 0xab40, 0x409a, 0xa6, 0x98,
            0xf3, 0x62, 0xd4, 0x64, 0xb3, 0x8f);

/* 9876ccad-47b4-4bdb-b65e-16f193c4f3db */
DEFINE_GUID(PROCESSOR_GENERIC_ERROR_SECTION_GUID,
            0x9876ccad, 0x47b4, 0x4bdb, 0xb6, 0x5e,
            0x16, 0xf1, 0x93, 0xc4, 0xf3, 0xdb);

/* dc3ea0b0-a144-4797-b95b-53fa242b6e1d */
DEFINE_GUID(XPF_PROCESSOR_ERROR_SECTION_GUID,
            0xdc3ea0b0, 0xa144, 0x4797, 0xb9, 0x5b,
            0x53, 0xfa, 0x24, 0x2b, 0x6e, 0x1d);

/* e429faf1-3cb7-11d4-bca7-0080c73c8881 */
DEFINE_GUID(IPF_PROCESSOR_ERROR_SECTION_GUID,
            0xe429faf1, 0x3cb7, 0x11d4, 0xbc, 0xa7,
            0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81);

/* a5bc1114-6f64-4ede-b863-3e83ed7c83b1 */
DEFINE_GUID(MEMORY_ERROR_SECTION_GUID,
            0xa5bc1114, 0x6f64, 0x4ede, 0xb8, 0x63,
            0x3e, 0x83, 0xed, 0x7c, 0x83, 0xb1);

/* d995e954-bbc1-430f-ad91-b44dcb3c6f35 */
DEFINE_GUID(PCIEXPRESS_ERROR_SECTION_GUID,
            0xd995e954, 0xbbc1, 0x430f, 0xad, 0x91,
            0xb4, 0x4d, 0xcb, 0x3c, 0x6f, 0x35);

/* c5753963-3b84-4095-bf78-eddad3f9c9dd */
DEFINE_GUID(PCIXBUS_ERROR_SECTION_GUID,
            0xc5753963, 0x3b84, 0x4095, 0xbf, 0x78,
            0xed, 0xda, 0xd3, 0xf9, 0xc9, 0xdd);

/* eb5e4685-ca66-4769-b6a2-26068b001326 */
DEFINE_GUID(PCIXDEVICE_ERROR_SECTION_GUID,
            0xeb5e4685, 0xca66, 0x4769, 0xb6, 0xa2,
            0x26, 0x06, 0x8b, 0x00, 0x13, 0x26);

/* 81212a96-09ed-4996-9471-8d729c8e69ed */
DEFINE_GUID(FIRMWARE_ERROR_RECORD_REFERENCE_GUID,
            0x81212a96, 0x09ed, 0x4996, 0x94, 0x71,
            0x8d, 0x72, 0x9c, 0x8e, 0x69, 0xed);

/* a55701f5-e3ef-43de-ac72-249b573fad2c */
DEFINE_GUID(WHEA_CACHECHECK_GUID,
            0xa55701f5, 0xe3ef, 0x43de, 0xac, 0x72,
            0x24, 0x9b, 0x57, 0x3f, 0xad, 0x2c);

/* fc06b535-5e1f-4562-9f25-0a3b9adb63c3 */
DEFINE_GUID(WHEA_TLBCHECK_GUID,
            0xfc06b535, 0x5e1f, 0x4562, 0x9f, 0x25,
            0x0a, 0x3b, 0x9a, 0xdb, 0x63, 0xc3);

/* 1cf3f8b3-c5b1-49a2-aa59-5eef92ffa63c */
DEFINE_GUID(WHEA_BUSCHECK_GUID,
            0x1cf3f8b3, 0xc5b1, 0x49a2, 0xaa, 0x59,
            0x5e, 0xef, 0x92, 0xff, 0xa6, 0x3c);

/* 48ab7f57-dc34-4f6c-a7d3-b0b5b0a74314 */
DEFINE_GUID(WHEA_MSCHECK_GUID,
            0x48ab7f57, 0xdc34, 0x4f6c, 0xa7, 0xd3,
            0xb0, 0xb5, 0xb0, 0xa7, 0x43, 0x14);

/* cf07c4bd-b789-4e18-b3c4-1f732cb57131 */
DEFINE_GUID(WHEA_RECORD_CREATOR_GUID,
            0xcf07c4bd,
            0xb789, 0x4e18,
            0xb3, 0xc4, 0x1f, 0x73, 0x2c, 0xb5, 0x71, 0x31);

/* 3e62a467-ab40-409a-a698-f362d464b38f */
DEFINE_GUID(GENERIC_NOTIFY_TYPE_GUID,
            0x3e62a467,
            0xab40, 0x409a,
            0xa6, 0x98, 0xf3, 0x62, 0xd4, 0x64, 0xb3, 0x8f);

/* 6f3380d1-6eb0-497f-a578-4d4c65a71617 */
DEFINE_GUID(IPF_SAL_RECORD_SECTION_GUID,
            0x6f3380d1,
            0x6eb0, 0x497f,
            0xa5, 0x78, 0x4d, 0x4c, 0x65, 0xa7, 0x16, 0x17);

/* 8a1e1d01-42f9-4557-9c33-565e5cc3f7e8 */
DEFINE_GUID(XPF_MCA_SECTION_GUID,
            0x8a1e1d01,
            0x42f9, 0x4557,
            0x9c, 0x33, 0x56, 0x5e, 0x5c, 0xc3, 0xf7, 0xe8);

/* e71254e7-c1b9-4940-ab76-909703a4320f */
DEFINE_GUID(NMI_SECTION_GUID,
            0xe71254e7,
            0xc1b9, 0x4940,
            0xab, 0x76, 0x90, 0x97, 0x03, 0xa4, 0x32, 0x0f);

/* e71254e8-c1b9-4940-ab76-909703a4320f */
DEFINE_GUID(GENERIC_SECTION_GUID,
            0xe71254e8,
            0xc1b9, 0x4940,
            0xab, 0x76, 0x90, 0x97, 0x03, 0xa4, 0x32, 0x0f);

/* e71254e9-c1b9-4940-ab76-909703a4320f */
DEFINE_GUID(WHEA_ERROR_PACKET_SECTION_GUID,
            0xe71254e9,
            0xc1b9, 0x4940,
            0xab, 0x76, 0x90, 0x97, 0x03, 0xa4, 0x32, 0x0f);


#if defined(_NTPSHEDDLL_)
#define NTPSHEDAPI
#else
#define NTPSHEDAPI DECLSPEC_IMPORT
#endif

#include <pshpack1.h>

typedef enum _WHEA_ERROR_TYPE {
    WheaErrTypeProcessor = 0,
    WheaErrTypeMemory,
    WheaErrTypePCIExpress,
    WheaErrTypeNMI,
    WheaErrTypePCIXBus,
    WheaErrTypePCIXDevice,
    WheaErrTypeGeneric
} WHEA_ERROR_TYPE, *PWHEA_ERROR_TYPE;

typedef union _WHEA_ERROR_PACKET_FLAGS {
    struct {
        ULONG PreviousError:1;
        ULONG Reserved1:1;
        ULONG HypervisorError:1;
        ULONG Simulated:1;
        ULONG PlatformPfaControl:1;
        ULONG PlatformDirectedOffline:1;
        ULONG Reserved2:26;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_ERROR_PACKET_FLAGS, *PWHEA_ERROR_PACKET_FLAGS;

typedef enum _WHEA_ERROR_PACKET_DATA_FORMAT {
    WheaDataFormatIPFSalRecord = 0,
    WheaDataFormatXPFMCA,
    WheaDataFormatMemory,
    WheaDataFormatPCIExpress,
    WheaDataFormatNMIPort,
    WheaDataFormatPCIXBus,
    WheaDataFormatPCIXDevice,
    WheaDataFormatGeneric,
    WheaDataFormatMax
} WHEA_ERROR_PACKET_DATA_FORMAT, *PWHEA_ERROR_PACKET_DATA_FORMAT;

typedef enum _WHEA_RAW_DATA_FORMAT {
    WheaRawDataFormatIPFSalRecord = 0x00,
    WheaRawDataFormatIA32MCA,
    WheaRawDataFormatIntel64MCA,
    WheaRawDataFormatAMD64MCA,
    WheaRawDataFormatMemory,
    WheaRawDataFormatPCIExpress,
    WheaRawDataFormatNMIPort,
    WheaRawDataFormatPCIXBus,
    WheaRawDataFormatPCIXDevice,
    WheaRawDataFormatGeneric,
    WheaRawDataFormatMax
} WHEA_RAW_DATA_FORMAT, *PWHEA_RAW_DATA_FORMAT;

typedef struct _WHEA_ERROR_PACKET_V1 {
    ULONG                   Signature;                          // +0x00 (0)
    WHEA_ERROR_PACKET_FLAGS Flags;                              // +0x04 (4)
    ULONG                   Size;                               // +0x08 (8)
    ULONG                   RawDataLength;                      // +0x0C (12)
    ULONGLONG               Reserved1;                          // +0x10 (16)
    ULONGLONG               Context;                            // +0x18 (24)
    WHEA_ERROR_TYPE         ErrorType;                          // +0x20 (32)
    WHEA_ERROR_SEVERITY     ErrorSeverity;                      // +0x24 (36)
    ULONG                   ErrorSourceId;                      // +0x28 (40)
    WHEA_ERROR_SOURCE_TYPE  ErrorSourceType;                    // +0x2C (44)
    ULONG                   Reserved2;                          // +0x30 (48)
    ULONG                   Version;                            // +0x34 (52)
    ULONGLONG               Cpu;                                // +0x38 (56)
    union {
        WHEA_PROCESSOR_GENERIC_ERROR_SECTION    ProcessorError; // +0x40 (64)
        WHEA_MEMORY_ERROR_SECTION               MemoryError;
        WHEA_NMI_ERROR_SECTION                  NmiError;
        WHEA_PCIEXPRESS_ERROR_SECTION           PciExpressError;
        WHEA_PCIXBUS_ERROR_SECTION              PciXBusError;
        WHEA_PCIXDEVICE_ERROR_SECTION           PciXDeviceError;
    } u;
    WHEA_RAW_DATA_FORMAT     RawDataFormat;                     // +0x110 (272)
    ULONG                    RawDataOffset;                     // +0x114 (276)
    UCHAR                    RawData[1];                        // +0x118 (280)

} WHEA_ERROR_PACKET_V1, *PWHEA_ERROR_PACKET_V1;

#define WHEA_ERROR_PACKET_V1_SIGNATURE  'tPrE'
#define WHEA_ERROR_PACKET_V1_VERSION    2

typedef struct _WHEA_ERROR_PACKET_V2 {
    ULONG Signature;
    ULONG Version;
    ULONG Length;
    WHEA_ERROR_PACKET_FLAGS Flags;
    WHEA_ERROR_TYPE ErrorType;
    WHEA_ERROR_SEVERITY ErrorSeverity;
    ULONG ErrorSourceId;
    WHEA_ERROR_SOURCE_TYPE ErrorSourceType;
    GUID NotifyType;
    ULONGLONG Context;
    WHEA_ERROR_PACKET_DATA_FORMAT DataFormat;
    ULONG Reserved1;
    ULONG DataOffset;
    ULONG DataLength;
    ULONG PshedDataOffset;
    ULONG PshedDataLength;
    // UCHAR Data[ANYSIZE_ARRAY];
    // UCHAR PshedData[ANYSIZE_ARRAY];
} WHEA_ERROR_PACKET_V2, *PWHEA_ERROR_PACKET_V2;

CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, Signature,         0,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, Version,           4,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, Length,            8,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, Flags,            12,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, ErrorType,        16,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, ErrorSeverity,    20,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, ErrorSourceId,    24,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, ErrorSourceType,  28,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, NotifyType,       32,  16);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, Context,          48,   8);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, DataFormat,       56,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, Reserved1,        60,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, DataOffset,       64,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, DataLength,       68,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, PshedDataOffset,  72,   4);
CPER_FIELD_CHECK(WHEA_ERROR_PACKET_V2, PshedDataLength,  76,   4);

#define WHEA_ERROR_PACKET_V2_SIGNATURE 'AEHW'
#define WHEA_ERROR_PACKET_V2_VERSION   3

#if (NTDDI_VERSION >= NTDDI_WIN7)

#define WHEA_ERROR_PACKET_SIGNATURE     WHEA_ERROR_PACKET_V2_SIGNATURE
#define WHEA_ERROR_PACKET_VERSION       WHEA_ERROR_PACKET_V2_VERSION
typedef struct _WHEA_ERROR_PACKET_V2    WHEA_ERROR_PACKET, *PWHEA_ERROR_PACKET;

#else

#define WHEA_ERROR_PACKET_SIGNATURE     WHEA_ERROR_PACKET_V1_SIGNATURE
#define WHEA_ERROR_PACKET_VERSION       WHEA_ERROR_PACKET_V1_VERSION
#define WHEA_ERROR_PKT_SIGNATURE        WHEA_ERROR_PACKET_SIGNATURE
#define WHEA_ERROR_PKT_VERSION          WHEA_ERROR_PACKET_VERSION
typedef struct _WHEA_ERROR_PACKET_V1    WHEA_ERROR_PACKET, *PWHEA_ERROR_PACKET;

#endif

typedef union _WHEA_GENERIC_ERROR_BLOCKSTATUS {
    struct {
        ULONG UncorrectableError:1;
        ULONG CorrectableError:1;
        ULONG MultipleUncorrectableErrors:1;
        ULONG MultipleCorrectableErrors:1;
        ULONG ErrorDataEntryCount:10;
        ULONG Reserved:18;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_GENERIC_ERROR_BLOCKSTATUS, *PWHEA_GENERIC_ERROR_BLOCKSTATUS;

typedef struct _WHEA_GENERIC_ERROR {
    WHEA_GENERIC_ERROR_BLOCKSTATUS BlockStatus;
    ULONG RawDataOffset;
    ULONG RawDataLength;
    ULONG DataLength;
    WHEA_ERROR_SEVERITY ErrorSeverity;
    UCHAR Data[1];
} WHEA_GENERIC_ERROR, *PWHEA_GENERIC_ERROR;

typedef struct _WHEA_GENERIC_ERROR_DATA_ENTRY {
    GUID SectionType;
    WHEA_ERROR_SEVERITY ErrorSeverity;
    WHEA_REVISION Revision;
    UCHAR ValidBits;
    UCHAR Flags;
    ULONG ErrorDataLength;
    GUID FRUId;
    UCHAR FRUText[20];
    UCHAR Data[1];
} WHEA_GENERIC_ERROR_DATA_ENTRY, *PWHEA_GENERIC_ERROR_DATA_ENTRY;

#include <poppack.h>

typedef
NTSTATUS
(*WHEA_ERROR_SOURCE_CORRECT)(
    _Inout_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _Out_ PULONG MaximumSectionLength
    );

typedef
NTSTATUS
(*WHEA_ERROR_SOURCE_INITIALIZE)(
    _In_ ULONG Phase,
    _Inout_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _Inout_opt_ PVOID Context
    );

typedef
NTSTATUS
(*WHEA_ERROR_SOURCE_CREATE_RECORD)(
    _Inout_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _Inout_ PWHEA_ERROR_PACKET ErrorPacket,
    _Out_writes_bytes_to_(BufferSize, *RecordLength) PWHEA_ERROR_RECORD ErrorRecord,
    _In_ ULONG BufferSize,
    _Inout_opt_ PVOID Context
    );

typedef
NTSTATUS
(*WHEA_ERROR_SOURCE_RECOVER)(
    _Inout_ PVOID Context,
    _Inout_ PWHEA_ERROR_SEVERITY Severity
    );

typedef struct _WHEA_ERROR_SOURCE_CONFIGURATION {
    ULONG Flags;
    WHEA_ERROR_SOURCE_CORRECT Correct;
    WHEA_ERROR_SOURCE_INITIALIZE Initialize;
    WHEA_ERROR_SOURCE_CREATE_RECORD CreateRecord;
    WHEA_ERROR_SOURCE_RECOVER Recover;
} WHEA_ERROR_SOURCE_CONFIGURATION, *PWHEA_ERROR_SOURCE_CONFIGURATION;

NTKERNELAPI
NTSTATUS
WheaReportHwError(
    _Inout_ PWHEA_ERROR_PACKET ErrorPacket
    );

NTKERNELAPI
NTSTATUS
WheaAddErrorSource(
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _In_opt_ PVOID Context
    );

NTKERNELAPI
PWHEA_ERROR_SOURCE_DESCRIPTOR
WheaGetErrorSource (
    _In_ ULONG ErrorSourceId
    );

NTKERNELAPI
NTSTATUS
WheaRemoveErrorSource(
    _In_ HANDLE Handle
    );

NTKERNELAPI
NTSTATUS
WheaConfigureErrorSource (
    _In_ WHEA_ERROR_SOURCE_TYPE SourceType,
    _In_ PWHEA_ERROR_SOURCE_CONFIGURATION Configuration
    );

NTKERNELAPI
NTSTATUS
WheaInitializeRecordHeader (
    _Out_ PWHEA_ERROR_RECORD_HEADER Header
    );

#if defined (_AMD64_)

typedef struct _WHEA_DRS_OBJECT *PWHEA_DRS_OBJECT;

typedef
VOID
(*WHEA_DRS_HANDLER) (
    _Inout_ PWHEA_DRS_OBJECT DrsObject,
    _In_ PVOID Context
    );

typedef struct _WHEA_DRS_OBJECT {
    PWHEA_DRS_OBJECT Next;
    LONG Busy;
    WHEA_DRS_HANDLER Handler;
    KIRQL Level;
    PVOID Context;
} WHEA_DRS_OBJECT;

NTKERNELAPI
VOID
WheaDeferredRecoveryService (
    VOID
    );

NTKERNELAPI
VOID
WheaInitializeDeferredRecoveryObject (
    _Out_ PWHEA_DRS_OBJECT Object,
    _In_ WHEA_DRS_HANDLER Handler,
    _In_ KIRQL Level
    );

NTKERNELAPI
BOOLEAN
WheaRequestDeferredRecovery (
    _Inout_ PWHEA_DRS_OBJECT Object,
    _In_opt_ PVOID Context
    );

#endif // defined (_AMD64_)

NTKERNELAPI
NTSTATUS
WheaAttemptPhysicalPageOffline (
    _In_ PFN_NUMBER Page,
    _In_ BOOLEAN PlatformDirected,
    _In_ BOOLEAN Poisoned
    );

_Must_inspect_result_
__inline
PWHEA_ERROR_PACKET
WheaGetErrPacketFromErrRecord (
    _In_ PWHEA_ERROR_RECORD Record)
{
    PWHEA_ERROR_PACKET Packet;
    PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR Descriptor;
    ULONG Section;
    ULONG SizeRequired;

    Packet = NULL;
    if (Record->Header.Signature != WHEA_ERROR_RECORD_SIGNATURE) {
        goto GetErrPacketFromErrRecordEnd;
    }

    SizeRequired = sizeof(WHEA_ERROR_RECORD_HEADER) +
        (sizeof(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR) *
         Record->Header.SectionCount);

    if (Record->Header.Length < SizeRequired) {
        goto GetErrPacketFromErrRecordEnd;
    }

    Descriptor = &Record->SectionDescriptor[0];
    for (Section = 0; Section < Record->Header.SectionCount; Section += 1) {

        if (RtlCompareMemory(&Descriptor->SectionType,
                             &WHEA_ERROR_PACKET_SECTION_GUID,
                             sizeof(GUID)) == sizeof(GUID)) {

                SizeRequired = Descriptor->SectionOffset +
                    Descriptor->SectionLength;

                if (Record->Header.Length < SizeRequired) {
                    goto GetErrPacketFromErrRecordEnd;
                }

                Packet = (PWHEA_ERROR_PACKET)
                    (((PUCHAR)Record) + Descriptor->SectionOffset);

#pragma warning(suppress: 26019)
                if (Packet->Signature != WHEA_ERROR_PACKET_SIGNATURE) {
                    Packet = NULL;
                }

                goto GetErrPacketFromErrRecordEnd;
        }

        Descriptor += 1;
    }

GetErrPacketFromErrRecordEnd:
    return Packet;
}

typedef union _WHEA_ERROR_INJECTION_CAPABILITIES {
    struct {
        ULONG ProcessorCorrectable:1;                   // 0x00000001
        ULONG ProcessorUncorrectableNonFatal:1;         // 0x00000002
        ULONG ProcessorUncorrectableFatal:1;            // 0x00000004
        ULONG MemoryCorrectable:1;                      // 0x00000008
        ULONG MemoryUncorrectableNonFatal:1;            // 0x00000010
        ULONG MemoryUncorrectableFatal:1;               // 0x00000020
        ULONG PCIExpressCorrectable:1;                  // 0x00000040
        ULONG PCIExpressUncorrectableNonFatal:1;        // 0x00000080
        ULONG PCIExpressUncorrectableFatal:1;           // 0x00000100
        ULONG PlatformCorrectable:1;                    // 0x00000200
        ULONG PlatformUncorrectableNonFatal:1;          // 0x00000400
        ULONG PlatformUncorrectableFatal:1;             // 0x00000800
        ULONG IA64Corrected:1;                          // 0x00001000
        ULONG IA64Recoverable:1;                        // 0x00002000
        ULONG IA64Fatal:1;                              // 0x00004000
        ULONG IA64RecoverableCache:1;                   // 0x00008000
        ULONG IA64RecoverableRegFile:1;                 // 0x00010000
        ULONG Reserved:15;
    } DUMMYSTRUCTNAME;
    ULONG AsULONG;
} WHEA_ERROR_INJECTION_CAPABILITIES, *PWHEA_ERROR_INJECTION_CAPABILITIES;

#define INJECT_ERRTYPE_PROCESSOR_CORRECTABLE                    0x00000001
#define INJECT_ERRTYPE_PROCESSOR_UNCORRECTABLENONFATAL          0x00000002
#define INJECT_ERRTYPE_PROCESSOR_UNCORRECTABLEFATAL             0x00000004
#define INJECT_ERRTYPE_MEMORY_CORRECTABLE                       0x00000008
#define INJECT_ERRTYPE_MEMORY_UNCORRECTABLENONFATAL             0x00000010
#define INJECT_ERRTYPE_MEMORY_UNCORRECTABLEFATAL                0x00000020
#define INJECT_ERRTYPE_PCIEXPRESS_CORRECTABLE                   0x00000040
#define INJECT_ERRTYPE_PCIEXPRESS_UNCORRECTABLENONFATAL         0x00000080
#define INJECT_ERRTYPE_PCIEXPRESS_UNCORRECTABLEFATAL            0x00000100
#define INJECT_ERRTYPE_PLATFORM_CORRECTABLE                     0x00000200
#define INJECT_ERRTYPE_PLATFORM_UNCORRECTABLENONFATAL           0x00000400
#define INJECT_ERRTYPE_PLATFORM_UNCORRECTABLEFATAL              0x00000800

#if defined (_AMD64_)

typedef
BOOLEAN
(*PFN_IN_USE_PAGE_OFFLINE_NOTIFY) (
    _In_ PFN_NUMBER Page,
    _In_ BOOLEAN PlatformDirected,
    _In_ BOOLEAN Poisoned,
    _In_ PVOID Context
    );

NTKERNELAPI
NTSTATUS
WheaRegisterInUsePageOfflineNotification (
    _In_ PFN_IN_USE_PAGE_OFFLINE_NOTIFY Callback,
    _In_opt_ PVOID Context
    );

NTKERNELAPI
NTSTATUS
WheaUnregisterInUsePageOfflineNotification (
    _In_ PFN_IN_USE_PAGE_OFFLINE_NOTIFY Callback
    );

#endif // _AMD64_

typedef struct _WHEA_RECOVERY_CONTEXT {
    union {
        struct {
            ULONG_PTR Address;
            BOOLEAN Consumed;
            UINT16 ErrorCode;
            BOOLEAN ErrorIpValid;
            BOOLEAN RestartIpValid;
        } MemoryError;
    };
    UINT64 PartitionId;  //HV_PARTITION_ID
    UINT32 VpIndex;      //HV_VP_INDEX

} WHEA_RECOVERY_CONTEXT, *PWHEA_RECOVERY_CONTEXT;

#if !defined(XBOX_SYSTEMOS)

typedef
NTSTATUS
(HVL_WHEA_ERROR_NOTIFICATION) (
    _In_ PWHEA_RECOVERY_CONTEXT RecoveryContext,
    _In_ BOOLEAN PlatformDirected,
    _In_ BOOLEAN Poisoned
    );

typedef HVL_WHEA_ERROR_NOTIFICATION *PHVL_WHEA_ERROR_NOTIFICATION;

extern PHVL_WHEA_ERROR_NOTIFICATION HvlpWheaErrorNotificationCallback;

NTKERNELAPI
NTSTATUS
HvlRegisterWheaErrorNotification (
    _In_ PHVL_WHEA_ERROR_NOTIFICATION Callback
    );

NTKERNELAPI
NTSTATUS
HvlUnregisterWheaErrorNotification(
    _In_ PHVL_WHEA_ERROR_NOTIFICATION Callback
    );

#endif

NTPSHEDAPI
NTSTATUS
PshedAttemptErrorRecovery(
    _Inout_ PWHEA_ERROR_RECORD ErrorRecord
    );

NTPSHEDAPI
VOID
PshedBugCheckSystem (
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _In_ PWHEA_ERROR_RECORD ErrorRecord
    );

NTPSHEDAPI
NTSTATUS
PshedClearErrorRecord(
    _In_ ULONG Flags,
    _In_ ULONGLONG RecordId
    );

NTPSHEDAPI
NTSTATUS
PshedDisableErrorSource (
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource
    );

NTPSHEDAPI
NTSTATUS
PshedEnableErrorSource (
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource
    );

NTPSHEDAPI
NTSTATUS
PshedFinalizeErrorRecord(
    _Inout_ PWHEA_ERROR_RECORD ErrorRecord,
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource
    );

NTPSHEDAPI
NTSTATUS
PshedGetAllErrorSources (
    _Out_ PULONG ErrorSourceCount,
    _Inout_ _At_(*Buffer, _Pre_readable_byte_size_(*Length) _Post_readable_byte_size_(*Length)) PUCHAR *Buffer,
    _Inout_ PULONG Length
    );

NTPSHEDAPI
NTSTATUS
PshedGetBootErrorPacket (
    _Out_ PULONG BootPacketLength,
    _Out_ PWHEA_ERROR_PACKET *BootPacket
    );

NTPSHEDAPI
NTSTATUS
PshedGetErrorSourceInfo (
    _In_ WHEA_ERROR_SOURCE_TYPE ErrorSource,
    _Inout_ PWHEA_ERROR_SOURCE_DESCRIPTOR Descriptor
    );

NTPSHEDAPI
NTSTATUS
PshedGetInjectionCapabilities (
    _Out_ PWHEA_ERROR_INJECTION_CAPABILITIES Capabilities
    );

NTPSHEDAPI
NTSTATUS
PshedInjectError (
    _In_ ULONG ErrorType,
    _In_ ULONGLONG Parameter1,
    _In_ ULONGLONG Parameter2,
    _In_ ULONGLONG Parameter3,
    _In_ ULONGLONG Parameter4
    );

NTPSHEDAPI
NTSTATUS
PshedReadErrorRecord(
    _In_ ULONG Flags,
    _In_ ULONGLONG ErrorRecordId,
    _Out_ PULONGLONG NextErrorRecordId,
    _Out_ PULONG RecordLength,
    _Outptr_result_bytebuffer_(*RecordLength) PWHEA_ERROR_RECORD *ErrorRecord
    );

NTPSHEDAPI
NTSTATUS
PshedRetrieveErrorInfo (
    _Inout_ PWHEA_ERROR_PACKET ErrorPkt,
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource
    );

NTPSHEDAPI
NTSTATUS
PshedSetErrorSourceInfo (
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource
    );

NTPSHEDAPI
NTSTATUS
PshedWriteErrorRecord(
    _In_ ULONG Flags,
    _In_ ULONG RecordLength,
    _In_reads_bytes_(RecordLength) PWHEA_ERROR_RECORD ErrorRecord
    );

NTPSHEDAPI
VOID
PshedMarkHiberPhase (
    VOID
    );

NTPSHEDAPI
LOGICAL
PshedArePluginsPresent (
    VOID
    );

#define WHEA_INTERNAL_ERROR_PSHEDHESTSOURCEINITFAILED  0x00000001
#define WHEA_INTERNAL_ERROR_WHEAINFOALLOCFAILED        0x00000002
#define WHEA_INTERNAL_ERROR_PSHEDINITFAILED            0x00000003
#define WHEA_INTERNAL_ERROR_CREATEPERPROCINFOFAILED    0x00000004
#define WHEA_INTERNAL_ERROR_QUERYERRSOURCESFAILED      0x00000005
#define WHEA_INTERNAL_ERROR_ERRSOURCEINITFAILED        0x00000006
#define WHEA_INTERNAL_ERROR_ERRSOURCETABLEINITFAILED   0x00000007
#define WHEA_INTERNAL_ERROR_PSHEDERRSOURCEINITFAILED   0x00000008
#define WHEA_INTERNAL_ERROR_INVALIDERRORSOURCE         0x00000009
#define WHEA_INTERNAL_ERROR_NOERRORRECORD              0x0000000A
#define WHEA_INTERNAL_ERROR_INVALIDFATALERROR          0x0000000B

typedef struct _WHEA_PSHED_INIT_PACKET {
    ULONG Size;
    ULONG Version;
} WHEA_PSHED_INIT_PACKET, *PWHEA_PSHED_INIT_PACKET;

_Must_inspect_result_
typedef
NTSTATUS
(*PSHED_PI_GET_ALL_ERROR_SOURCES) (
    _Inout_opt_ PVOID PluginContext,
    _Inout_ PULONG Count,
    _Inout_updates_bytes_(*Length) PWHEA_ERROR_SOURCE_DESCRIPTOR *ErrorSrcs,
    _Inout_ PULONG Length
    );

_Must_inspect_result_
typedef
NTSTATUS
(*PSHED_PI_GET_ERROR_SOURCE_INFO) (
    _Inout_opt_ PVOID PluginContext,
    _Inout_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource
    );

_Must_inspect_result_
typedef
NTSTATUS
(*PSHED_PI_SET_ERROR_SOURCE_INFO) (
    _Inout_opt_ PVOID PluginContext,
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource
    );

typedef
NTSTATUS
 (*PSHED_PI_ENABLE_ERROR_SOURCE) (
    _Inout_opt_ PVOID PluginContext,
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource
    );

typedef
NTSTATUS
 (*PSHED_PI_DISABLE_ERROR_SOURCE) (
    _Inout_opt_ PVOID PluginContext,
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource
    );

typedef
NTSTATUS
(*PSHED_PI_WRITE_ERROR_RECORD) (
    _Inout_opt_ PVOID PluginContext,
    _In_ ULONG Flags,
    _In_ ULONG RecordLength,
    _In_reads_bytes_(RecordLength) PWHEA_ERROR_RECORD ErrorRecord
    );

_Must_inspect_result_
typedef
NTSTATUS
(*PSHED_PI_READ_ERROR_RECORD) (
    _Inout_opt_ PVOID PluginContext,
    _In_ ULONG Flags,
    _In_ ULONGLONG ErrorRecordId,
    _Out_ PULONGLONG NextErrorRecordId,
    _Inout_ PULONG RecordLength,
    _Out_writes_bytes_(*RecordLength) PWHEA_ERROR_RECORD ErrorRecord
    );

typedef
NTSTATUS
(*PSHED_PI_CLEAR_ERROR_RECORD) (
    _Inout_opt_ PVOID PluginContext,
    _In_ ULONG Flags,
    _In_ ULONGLONG ErrorRecordId
    );

typedef
NTSTATUS
(*PSHED_PI_RETRIEVE_ERROR_INFO) (
    _Inout_opt_ PVOID PluginContext,
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _In_ ULONGLONG BufferLength,
    _Inout_updates_bytes_(BufferLength) PWHEA_ERROR_PACKET Packet
    );

typedef
NTSTATUS
(*PSHED_PI_FINALIZE_ERROR_RECORD) (
    _Inout_opt_ PVOID PluginContext,
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _In_ ULONG BufferLength,
    _Inout_updates_bytes_(BufferLength) PWHEA_ERROR_RECORD ErrorRecord
    );

typedef
NTSTATUS
(*PSHED_PI_CLEAR_ERROR_STATUS) (
    _Inout_opt_ PVOID PluginContext,
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _In_ ULONG BufferLength,
    _In_reads_bytes_(BufferLength) PWHEA_ERROR_RECORD ErrorRecord
    );

_Must_inspect_result_
typedef
NTSTATUS
(*PSHED_PI_ATTEMPT_ERROR_RECOVERY) (
    _Inout_opt_ PVOID PluginContext,
    _In_ ULONG BufferLength,
    _In_reads_bytes_(BufferLength) PWHEA_ERROR_RECORD ErrorRecord
    );

_Must_inspect_result_
typedef
NTSTATUS
(*PSHED_PI_GET_INJECTION_CAPABILITIES) (
    _Inout_opt_ PVOID PluginContext,
    _Out_ PWHEA_ERROR_INJECTION_CAPABILITIES Capabilities
    );

_Must_inspect_result_
typedef
NTSTATUS
(*PSHED_PI_INJECT_ERROR) (
    _Inout_opt_ PVOID PluginContext,
    _In_ ULONGLONG ErrorType,
    _In_ ULONGLONG Parameter1,
    _In_ ULONGLONG Parameter2,
    _In_ ULONGLONG Parameter3,
    _In_ ULONGLONG Parameter4
    );

typedef struct _WHEA_PSHED_PLUGIN_CALLBACKS {
    PSHED_PI_GET_ALL_ERROR_SOURCES GetAllErrorSources;
    PVOID Reserved;
    PSHED_PI_GET_ERROR_SOURCE_INFO GetErrorSourceInfo;
    PSHED_PI_SET_ERROR_SOURCE_INFO SetErrorSourceInfo;
    PSHED_PI_ENABLE_ERROR_SOURCE EnableErrorSource;
    PSHED_PI_DISABLE_ERROR_SOURCE DisableErrorSource;
    PSHED_PI_WRITE_ERROR_RECORD WriteErrorRecord;
    PSHED_PI_READ_ERROR_RECORD ReadErrorRecord;
    PSHED_PI_CLEAR_ERROR_RECORD ClearErrorRecord;
    PSHED_PI_RETRIEVE_ERROR_INFO RetrieveErrorInfo;
    PSHED_PI_FINALIZE_ERROR_RECORD FinalizeErrorRecord;
    PSHED_PI_CLEAR_ERROR_STATUS ClearErrorStatus;
    PSHED_PI_ATTEMPT_ERROR_RECOVERY AttemptRecovery;
    PSHED_PI_GET_INJECTION_CAPABILITIES GetInjectionCapabilities;
    PSHED_PI_INJECT_ERROR InjectError;
} WHEA_PSHED_PLUGIN_CALLBACKS, *PWHEA_PSHED_PLUGIN_CALLBACKS;

typedef struct _WHEA_PSHED_PLUGIN_REGISTRATION_PACKET {
    ULONG Length;
    ULONG Version;
    PVOID Context;
    ULONG FunctionalAreaMask;
    ULONG Reserved;
    WHEA_PSHED_PLUGIN_CALLBACKS Callbacks;
} WHEA_PSHED_PLUGIN_REGISTRATION_PACKET,
  *PWHEA_PSHED_PLUGIN_REGISTRATION_PACKET;

#define WHEA_PLUGIN_REGISTRATION_PACKET_VERSION 0x00010000

#define PshedFADiscovery              0x00000001
#define PshedFAErrorSourceControl     0x00000002
#define PshedFAErrorRecordPersistence 0x00000004
#define PshedFAErrorInfoRetrieval     0x00000008
#define PshedFAErrorRecovery          0x00000010
#define PshedFAErrorInjection         0x00000020

#define WHEA_WRITE_FLAG_DUMMY 0x00000001

_IRQL_requires_max_(DISPATCH_LEVEL)
__drv_allocatesMem(Mem)
_Post_writable_byte_size_(Size)
_Must_inspect_result_
NTPSHEDAPI
PVOID
PshedAllocateMemory (
    _In_ ULONG Size
    );

_IRQL_requires_max_(DISPATCH_LEVEL)
NTPSHEDAPI
VOID
PshedFreeMemory (
    _In_ __drv_freesMem(Mem) PVOID Address
    );

NTPSHEDAPI
BOOLEAN
PshedIsSystemWheaEnabled (
    VOID
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTPSHEDAPI
NTSTATUS
PshedRegisterPlugin (
    _Inout_ PWHEA_PSHED_PLUGIN_REGISTRATION_PACKET Packet
    );

NTPSHEDAPI
BOOLEAN
PshedSynchronizeExecution (
    _In_ PWHEA_ERROR_SOURCE_DESCRIPTOR ErrorSource,
    _In_ PKSYNCHRONIZE_ROUTINE SynchronizeRoutine,
    _In_ PVOID SynchronizeContext
    );

_Must_inspect_result_
__inline
BOOLEAN
WheaIsValidErrorRecordSignature (
    _In_ PWHEA_ERROR_RECORD Record)
{
    BOOLEAN Valid;

    if ((Record->Header.Signature == WHEA_ERROR_RECORD_SIGNATURE) &&
        (Record->Header.Revision.AsUSHORT == WHEA_ERROR_RECORD_REVISION) &&
        (Record->Header.SignatureEnd == WHEA_ERROR_RECORD_SIGNATURE_END)) {

        Valid = TRUE;

    } else {
        Valid = FALSE;
    }

    return Valid;
}

_Must_inspect_result_
__inline
NTSTATUS
WheaFindErrorRecordSection (
    _In_ PWHEA_ERROR_RECORD Record,
    _In_ const GUID *SectionType,
    _Out_ PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR *SectionDescriptor,
    _Out_opt_ PVOID *SectionData)
{
    NTSTATUS Status;
    PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR Descriptor;
    ULONG Index;
    ULONG MinimumLength;

    if ((Record == NULL) ||
        (SectionType == NULL) ||
        (SectionDescriptor == NULL) ||
        (WheaIsValidErrorRecordSignature(Record) == FALSE) ||
        (Record->Header.SectionCount == 0)) {

        Status = STATUS_INVALID_PARAMETER;
        goto FindErrorRecordSectionEnd;
    }

    MinimumLength = sizeof(WHEA_ERROR_RECORD_HEADER) +
        (Record->Header.SectionCount *
         sizeof(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR));

    if (Record->Header.Length < MinimumLength) {
        Status = STATUS_INVALID_PARAMETER;
        goto FindErrorRecordSectionEnd;
    }

    Descriptor = &Record->SectionDescriptor[0];
    for (Index = 0; Index < Record->Header.SectionCount; Index += 1) {
        if (RtlCompareMemory(&Descriptor->SectionType,
                             SectionType,
                             sizeof(GUID)) == sizeof(GUID)) {

            break;
        }

        Descriptor += 1;
    }

    if (Index >= Record->Header.SectionCount) {
        Status = STATUS_NOT_FOUND;
        goto FindErrorRecordSectionEnd;
    }

    if ((Descriptor->SectionOffset + Descriptor->SectionLength) >
        Record->Header.Length) {

        Status = STATUS_INVALID_PARAMETER;
        goto FindErrorRecordSectionEnd;
    }

    *SectionDescriptor = Descriptor;
    if (SectionData != NULL) {
        *SectionData = (PVOID)(((PUCHAR)Record) + Descriptor->SectionOffset);
    }

    Status = STATUS_SUCCESS;

FindErrorRecordSectionEnd:
    return Status;
}

_Must_inspect_result_
__inline
NTSTATUS
WheaFindNextErrorRecordSection (
    _In_ PWHEA_ERROR_RECORD Record,
    _Inout_ ULONG *Context,
    _Out_ PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR *SectionDescriptor,
    _Out_opt_ PVOID *SectionData)
{
    NTSTATUS Status;
    PWHEA_ERROR_RECORD_SECTION_DESCRIPTOR Descriptor;
    ULONG Index;
    ULONG MinimumLength;

    if ((Record == NULL) ||
        (Context == NULL) ||
        (SectionDescriptor == NULL) ||
        (WheaIsValidErrorRecordSignature(Record) == FALSE) ||
        (Record->Header.SectionCount == 0)) {

        Status = STATUS_INVALID_PARAMETER;
        goto FindNextErrorRecordSectionEnd;
    }

    MinimumLength = sizeof(WHEA_ERROR_RECORD_HEADER) +
        (Record->Header.SectionCount *
         sizeof(WHEA_ERROR_RECORD_SECTION_DESCRIPTOR));

    if (Record->Header.Length < MinimumLength) {
        Status = STATUS_INVALID_PARAMETER;
        goto FindNextErrorRecordSectionEnd;
    }

    Index = *Context;
    if (Index > Record->Header.SectionCount) {
        Status = STATUS_INVALID_PARAMETER;
        goto FindNextErrorRecordSectionEnd;
    }

    if (Index == Record->Header.SectionCount) {
        Status = STATUS_NOT_FOUND;
        goto FindNextErrorRecordSectionEnd;
    }

    Descriptor = &Record->SectionDescriptor[Index];

    if ((Descriptor->SectionOffset + Descriptor->SectionLength) >
        Record->Header.Length) {

        Status = STATUS_INVALID_PARAMETER;
        goto FindNextErrorRecordSectionEnd;
    }

    *Context = Index + 1;
    *SectionDescriptor = Descriptor;
    if (SectionData != NULL) {
        *SectionData = (PVOID)(((PUCHAR)Record) + Descriptor->SectionOffset);
    }

    Status = STATUS_SUCCESS;

FindNextErrorRecordSectionEnd:
    return Status;
}

typedef enum _SOC_SUBSYSTEM_TYPE {
    SOC_SUBSYS_WIRELESS_MODEM = 0,
    SOC_SUBSYS_AUDIO_DSP = 1,
    SOC_SUBSYS_WIRELSS_CONNECTIVITY = 2,
    SOC_SUBSYS_SENSORS = 3,
    SOC_SUBSYS_VENDOR_DEFINED = 0x10000
} SOC_SUBSYSTEM_TYPE, *PSOC_SUBSYSTEM_TYPE;


typedef struct _SOC_SUBSYSTEM_FAILURE_DETAILS {
    SOC_SUBSYSTEM_TYPE SubsysType;
    ULONG64 FirmwareVersion;
    ULONG64 HardwareVersion;
    ULONG   UnifiedFailureRegionSize;
    CHAR    UnifiedFailureRegion[1];
} SOC_SUBSYSTEM_FAILURE_DETAILS, *PSOC_SUBSYSTEM_FAILURE_DETAILS;

#define PROCESSOR_INTERFACE_VERSION 38

_Function_class_(PROCESSOR_FEEDBACK_INSTANTANEOUS_READ)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_FEEDBACK_INSTANTANEOUS_READ) (
    _In_ ULONG_PTR Context,
    _Out_ PULONG Value
    );

typedef PROCESSOR_FEEDBACK_INSTANTANEOUS_READ *PPROCESSOR_FEEDBACK_INSTANTANEOUS_READ;

_Function_class_(PROCESSOR_FEEDBACK_DIFFERENTIAL_READ)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_FEEDBACK_DIFFERENTIAL_READ) (
    _In_ ULONG_PTR Context,
    _In_ BOOLEAN Reset,
    _Out_ PULONG64 ReferenceCount,
    _Out_ PULONG64 ActualCount
    );

typedef PROCESSOR_FEEDBACK_DIFFERENTIAL_READ *PPROCESSOR_FEEDBACK_DIFFERENTIAL_READ;

typedef struct _PROCESSOR_FEEDBACK_COUNTER {
    union {
        PPROCESSOR_FEEDBACK_INSTANTANEOUS_READ InstantaneousRead;
        PPROCESSOR_FEEDBACK_DIFFERENTIAL_READ DifferentialRead;
    };

    ULONG NominalRate;
    ULONG Type;
    BOOLEAN Affinitized;
    BOOLEAN Differential;
} PROCESSOR_FEEDBACK_COUNTER, *PPROCESSOR_FEEDBACK_COUNTER;

#define PROCESSOR_FEEDBACK_COUNTER_FREQUENCY      0x00
#define PROCESSOR_FEEDBACK_COUNTER_PERFORMANCE    0x01
#define PROCESSOR_FEEDBACK_COUNTER_MAX            0x02

_Function_class_(PROCESSOR_FETCH_MSR_ROUTINE)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_FETCH_MSR_ROUTINE) (
    _Out_ PULONG64 MSRValue
    );

typedef PROCESSOR_FETCH_MSR_ROUTINE *PPROCESSOR_FETCH_MSR_ROUTINE;

_Function_class_(PROCESSOR_POLICY_ACTION)
_IRQL_requires_same_
typedef
NTSTATUS
(FASTCALL PROCESSOR_POLICY_ACTION) (
    VOID
    );

typedef PROCESSOR_POLICY_ACTION *PPROCESSOR_POLICY_ACTION;

_Function_class_(PROCESSOR_POLICY_HANDLER)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_POLICY_HANDLER) (
    _In_ ULONG_PTR Context,
    _In_ ULONG Policy
    );

typedef PROCESSOR_POLICY_HANDLER *PPROCESSOR_POLICY_HANDLER;

_Function_class_(PROCESSOR_COMPUTE_ENERGY_ROUTINE)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_COMPUTE_ENERGY_ROUTINE) (
    _In_ PULONG64 ActiveTime,
    _In_ PULONG64 TotalTime,
    _In_ PULONG FrequencyPercent,
    _Out_writes_(PO_EFFICIENCY_CLASSES) PULONG64 EnergyConsumed
    );

typedef PROCESSOR_COMPUTE_ENERGY_ROUTINE *PPROCESSOR_COMPUTE_ENERGY_ROUTINE;

_Function_class_(PROCESSOR_SNAP_ENERGYCOUNTERS_ROUTINE)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_SNAP_ENERGYCOUNTERS_ROUTINE) (
    __in ULONG ProcIndex,
    __in BOOLEAN Remote,
    __in BOOLEAN SnapPmc
    );

typedef PROCESSOR_SNAP_ENERGYCOUNTERS_ROUTINE *PPROCESSOR_SNAP_ENERGYCOUNTERS_ROUTINE;

_Function_class_(PROCESSOR_PERF_REINITIALIZE_HANDLER)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_PERF_REINITIALIZE_HANDLER) (
    _In_ ULONG_PTR Context
    );

typedef PROCESSOR_PERF_REINITIALIZE_HANDLER *PPROCESSOR_PERF_REINITIALIZE_HANDLER;

#define PROCESSOR_PERF_SELECTION_ALLOW_THROTTLE    0x1
#define PROCESSOR_PERF_SELECTION_ROUND_DOWN        0x2

_Function_class_(PROCESSOR_PERF_SELECTION_HANDLER)
_IRQL_requires_same_
typedef
ULONG
(FASTCALL PROCESSOR_PERF_SELECTION_HANDLER) (
    _In_ ULONG_PTR Context,
    _In_ ULONG TargetPercent,
    _In_ ULONG MinPercent,
    _In_ ULONG MaxPercent,
    _In_ ULONG Flags,
    _Out_ PULONG Frequency,
    _Out_ PULONG64 State
    );

typedef PROCESSOR_PERF_SELECTION_HANDLER *PPROCESSOR_PERF_SELECTION_HANDLER;

#define PROCESSOR_PERF_CONTEXT_FORCE_STATE         ULONG_MAX

_Function_class_(PROCESSOR_PERF_CONTROL_HANDLER)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_PERF_CONTROL_HANDLER) (
    _In_ ULONG_PTR Context,
    _In_ ULONG64 State,
    _In_ ULONG MinPercent,
    _In_ ULONG MaxPercent,
    _In_ ULONG TolerancePercent,
    _In_ BOOLEAN Autonomous,
    _In_ BOOLEAN Initiate,
    _In_ BOOLEAN Force
    );

typedef PROCESSOR_PERF_CONTROL_HANDLER *PPROCESSOR_PERF_CONTROL_HANDLER;

_Function_class_(PROCESSOR_PERF_CONTROL_CALLBACK)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_PERF_CONTROL_CALLBACK) (
    VOID
    );

typedef PROCESSOR_PERF_CONTROL_CALLBACK *PPROCESSOR_PERF_CONTROL_CALLBACK;

_Function_class_(PROCESSOR_PERF_CONTROL_ACTION)
_IRQL_requires_same_
typedef
VOID
(FASTCALL PROCESSOR_PERF_CONTROL_ACTION) (
    _In_ PPROCESSOR_PERF_CONTROL_CALLBACK Callback
    );

typedef PROCESSOR_PERF_CONTROL_ACTION *PPROCESSOR_PERF_CONTROL_ACTION;

_Function_class_(PROCESSOR_PARK_PREFERENCE_HANDLER)
_IRQL_requires_same_
typedef
VOID
(PROCESSOR_PARK_PREFERENCE_HANDLER) (
    _In_ UCHAR EvaluationType,
    _In_ ULONGLONG EvaluationTime,
    _In_ ULONG UnparkCount,
    _In_ PKAFFINITY_EX ParkGroup,
    _In_opt_ PKAFFINITY_EX Unparked,
    _Inout_opt_ PKAFFINITY_EX HintPark,
    _Inout_opt_ PKAFFINITY_EX HintUnpark
    );

typedef PROCESSOR_PARK_PREFERENCE_HANDLER *PPROCESSOR_PARK_PREFERENCE_HANDLER;

#define PROCESSOR_IDLE_OVERRIDE_DISABLED  (0xffffffff)

typedef struct _PROCESSOR_IDLE_CONSTRAINTS {
    ULONG64 TotalTime;
    ULONG64 IdleTime;
    ULONG64 ExpectedIdleDuration;
    ULONG64 MaxIdleDuration;
    ULONG OverrideState;
    ULONG TimeCheck;
    UCHAR PromotePercent;
    UCHAR DemotePercent;
    BOOLEAN Parked;
    BOOLEAN Interruptible;
    BOOLEAN PlatformIdle;
    UCHAR ExpectedWakeReason;
} PROCESSOR_IDLE_CONSTRAINTS, *PPROCESSOR_IDLE_CONSTRAINTS;

typedef struct _PROCESSOR_IDLE_DEPENDENCY {
    ULONG ProcessorIndex;
    UCHAR ExpectedState;
    BOOLEAN AllowDeeperStates;
    BOOLEAN LooseDependency;
} PROCESSOR_IDLE_DEPENDENCY, *PPROCESSOR_IDLE_DEPENDENCY;

typedef struct _PROCESSOR_IDLE_PREPARE_INFO {
    PVOID Context;
    PROCESSOR_IDLE_CONSTRAINTS Constraints;
    ULONG DependencyCount;
    _Field_range_(0, DependencyCount) ULONG DependencyUsed;
    _Field_size_part_(DependencyCount, DependencyUsed) PPROCESSOR_IDLE_DEPENDENCY DependencyArray;
    ULONG PlatformIdleStateIndex;
    ULONG ProcessorIdleStateIndex;
    ULONG IdleSelectFailureMask;
} PROCESSOR_IDLE_PREPARE_INFO, *PPROCESSOR_IDLE_PREPARE_INFO;

typedef struct _PROCESSOR_PLATFORM_STATE_RESIDENCY {
    ULONG64 Residency;
    ULONG64 TransitionCount;
} PROCESSOR_PLATFORM_STATE_RESIDENCY, *PPROCESSOR_PLATFORM_STATE_RESIDENCY;

typedef struct _PROCESSOR_PLATFORM_STATE_RESIDENCIES {
    ULONG Count;
    PROCESSOR_PLATFORM_STATE_RESIDENCY States[ANYSIZE_ARRAY];
} PROCESSOR_PLATFORM_STATE_RESIDENCIES, *PPROCESSOR_PLATFORM_STATE_RESIDENCIES;

#define PROCESSOR_NO_EXPECTED_STATE       (0xffffffff)
#define PROCESSOR_IDLE_STATE_ABORT        (0xffffffff)
#define PROCESSOR_IDLE_STATE_FALLBACK_HAL (0xfffffffe)
#define PLATFORM_IDLE_STATE_NONE          (0xffffffff)
#define PLATFORM_IDLE_STATE_UNKNOWN_RESIDENCY (0xffffffffffffffff)

_Function_class_(PROCESSOR_IDLE_PRESELECT)
_IRQL_requires_same_
typedef
ULONG
FASTCALL
PROCESSOR_IDLE_PRESELECT (
    _In_ PVOID Context,
    _Inout_ PPROCESSOR_IDLE_CONSTRAINTS Constraints
    );

typedef PROCESSOR_IDLE_PRESELECT *PPROCESSOR_IDLE_PRESELECT;

_Function_class_(PROCESSOR_IDLE_PREPARE)
_IRQL_requires_same_
typedef
VOID
FASTCALL
PROCESSOR_IDLE_PREPARE (
    _Inout_ PPROCESSOR_IDLE_PREPARE_INFO PrepareInfo
    );

typedef PROCESSOR_IDLE_PREPARE *PPROCESSOR_IDLE_PREPARE;

_Function_class_(PROCESSOR_IDLE_TEST)
_IRQL_requires_same_
typedef
ULONG
FASTCALL
PROCESSOR_IDLE_TEST (
    _In_ PVOID Context,
    _In_ ULONG ProcessorIndex,
    _In_ ULONG PlatformIndex
    );

typedef PROCESSOR_IDLE_TEST *PPROCESSOR_IDLE_TEST;

_Function_class_(PROCESSOR_IDLE_AVAILABILITY_CHECK)
_IRQL_requires_same_
typedef
ULONG
FASTCALL
PROCESSOR_IDLE_AVAILABILITY_CHECK (
    _In_ PVOID Context,
    _In_ ULONG ProcessorIndex
    );

typedef PROCESSOR_IDLE_AVAILABILITY_CHECK *PPROCESSOR_IDLE_AVAILABILITY_CHECK;

_Function_class_(PROCESSOR_IDLE_EXECUTE)
_IRQL_requires_same_
typedef
NTSTATUS
FASTCALL
PROCESSOR_IDLE_EXECUTE (
    _In_ PVOID Context,
    _In_ ULONG ProcessorState,
    _In_ ULONG PlatformState,
    _In_ ULONG CoordinatedSelectionCount,
    _In_reads_(CoordinatedSelectionCount) PULONG CoordinatedSelection
    );

typedef PROCESSOR_IDLE_EXECUTE *PPROCESSOR_IDLE_EXECUTE;

_Function_class_(PROCESSOR_IDLE_COMPLETE)
_IRQL_requires_same_
typedef
VOID
FASTCALL
PROCESSOR_IDLE_COMPLETE (
    _In_ PVOID Context,
    _In_ ULONG ProcessorState,
    _In_ ULONG PlatformState,
    _In_ ULONG CoordinatedSelectionCount,
    _In_reads_(CoordinatedSelectionCount) PULONG CoordinatedSelection
    );

typedef PROCESSOR_IDLE_COMPLETE *PPROCESSOR_IDLE_COMPLETE;

_Function_class_(PROCESSOR_IDLE_CANCEL)
_IRQL_requires_same_
typedef
VOID
FASTCALL
PROCESSOR_IDLE_CANCEL (
    _In_ PVOID Context,
    _In_ ULONG Reason
    );

typedef PROCESSOR_IDLE_CANCEL *PPROCESSOR_IDLE_CANCEL;

_Function_class_(PROCESSOR_IS_HALTED)
_IRQL_requires_same_
typedef
BOOLEAN
FASTCALL
PROCESSOR_IS_HALTED (
    _In_ PVOID Context
    );

typedef PROCESSOR_IS_HALTED *PPROCESSOR_IS_HALTED;

_Function_class_(PROCESSOR_INITIATE_WAKE)
_IRQL_requires_same_
typedef
BOOLEAN
FASTCALL
PROCESSOR_INITIATE_WAKE (
    _In_ PVOID Context
    );

typedef PROCESSOR_INITIATE_WAKE *PPROCESSOR_INITIATE_WAKE;

_Function_class_(PROCESSOR_QUERY_PLATFORM_STATE_RESIDENCY)
_IRQL_requires_same_
typedef
NTSTATUS
FASTCALL
PROCESSOR_QUERY_PLATFORM_STATE_RESIDENCY (
    _In_ PVOID Context,
    _Inout_ PPROCESSOR_PLATFORM_STATE_RESIDENCIES PlatformStateResidencies
    );

typedef PROCESSOR_QUERY_PLATFORM_STATE_RESIDENCY *PPROCESSOR_QUERY_PLATFORM_STATE_RESIDENCY;

typedef struct _PROCESSOR_IDLE_STATE_EX {
    ULONG Interruptible          :1;
    ULONG CacheCoherent          :1;
    ULONG ThreadContextRetained  :1;
    ULONG CStateType             :4;
    ULONG WakesSpuriously        :1;
    ULONG PlatformOnly           :1;
    ULONG Reserved               :21;
    ULONG NoCState               :1;
    ULONG InterruptsEnabled      :1;
    ULONG Latency;
    ULONG BreakEvenDuration;
    UNICODE_STRING Name;
} PROCESSOR_IDLE_STATE_EX, *PPROCESSOR_IDLE_STATE_EX;

typedef struct _PROCESSOR_IDLE_STATES_EX {
    ULONG Version;
    PROCESSOR_NUMBER Processor;
    PVOID Context;
    BOOLEAN EstimateIdleDuration;
    BOOLEAN Update;
    UCHAR InterfaceVersion;
    PPROCESSOR_IDLE_PREPARE IdlePrepare;
    PPROCESSOR_IDLE_CANCEL IdleCancel;
    PPROCESSOR_IDLE_PRESELECT IdlePreselect;
    PPROCESSOR_IDLE_TEST IdleTest;
    PPROCESSOR_IDLE_AVAILABILITY_CHECK IdleAvailabilityCheck;
    PPROCESSOR_IDLE_EXECUTE IdlePreExecute;
    PPROCESSOR_IDLE_EXECUTE IdleExecute;
    PPROCESSOR_IDLE_COMPLETE IdleComplete;
    PPROCESSOR_IS_HALTED IdleIsHalted;
    PPROCESSOR_INITIATE_WAKE IdleInitiateWake;
    ULONG MaximumDependencies;
    ULONG ProcessorIdleCount;
    _Field_size_(ProcessorIdleCount) PROCESSOR_IDLE_STATE_EX State[ANYSIZE_ARRAY];
} PROCESSOR_IDLE_STATES_EX, *PPROCESSOR_IDLE_STATES_EX;

#define PROCESSOR_IDLE_INTERFACE_V1  0
#define PROCESSOR_IDLE_INTERFACE_V2  1

typedef struct _PLATFORM_IDLE_STATE {
    PROCESSOR_NUMBER InitiatingProcessor;
    BOOLEAN OneInitiator;
    UCHAR InitiatingState;
    ULONG Latency;
    ULONG BreakEvenTime;
    ULONG DependencyCount;
    UNICODE_STRING Name;
    _Field_size_(DependencyCount) PPROCESSOR_IDLE_DEPENDENCY Dependencies;
} PLATFORM_IDLE_STATE, *PPLATFORM_IDLE_STATE;

typedef struct _PLATFORM_IDLE_STATES {
    ULONG Version;
    ULONG Count;
    ULONG Definitions;
    PPROCESSOR_IDLE_TEST IdleTest;
    PPROCESSOR_IDLE_EXECUTE IdlePreExecute;
    PPROCESSOR_IDLE_COMPLETE IdleComplete;
    PPROCESSOR_QUERY_PLATFORM_STATE_RESIDENCY QueryPlatformStateResidency;
    BOOLEAN Update;
    _Field_size_(Definitions) PLATFORM_IDLE_STATE State[ANYSIZE_ARRAY];
} PLATFORM_IDLE_STATES, *PPLATFORM_IDLE_STATES;

typedef struct _COORDINATED_IDLE_DEPENDENCY {
    ULONG ProcessorIndex;
    ULONG OptionCount;
    _Field_size_(OptionCount) struct _PEP_COORDINATED_DEPENDENCY_OPTION *Options;
} COORDINATED_IDLE_DEPENDENCY, *PCOORDINATED_IDLE_DEPENDENCY;

typedef struct _COORDINATED_IDLE_STATE {
    KAFFINITY_EX Processors;
    UNICODE_STRING Name;
    ULONG Latency;
    ULONG BreakEvenTime;
    ULONG MaximumDependencyOptions;
    ULONG DependencyCount;
    BOOLEAN Platform;
    BOOLEAN WakesSpuriously;
    BOOLEAN Interruptible;
    _Field_size_(DependencyCount) PCOORDINATED_IDLE_DEPENDENCY Dependencies;
} COORDINATED_IDLE_STATE, *PCOORDINATED_IDLE_STATE;

typedef struct _COORDINATED_IDLE_STATES {
    ULONG Count;
    PPROCESSOR_IDLE_TEST IdleTest;
    PPROCESSOR_IDLE_EXECUTE IdlePreExecute;
    PPROCESSOR_IDLE_COMPLETE IdleComplete;
    PPROCESSOR_QUERY_PLATFORM_STATE_RESIDENCY QueryPlatformStateResidency;
    BOOLEAN Update;
    _Field_size_(Count) COORDINATED_IDLE_STATE State[ANYSIZE_ARRAY];
} COORDINATED_IDLE_STATES, *PCOORDINATED_IDLE_STATES;

typedef struct _PROCESSOR_IDLE_STATES_HV {
    ULONG Version;
    ULONG InitialApicId;
    PVOID IdleStateConfig;
} PROCESSOR_IDLE_STATES_HV, *PPROCESSOR_IDLE_STATES_HV;

typedef struct _PROCESSOR_PERF_STATES_HV {
    ULONG Version;
    ULONG InitialApicId;
    PVOID PerfStateConfig;
    PVOID ThrottleStateConfig;
    PVOID PccConfig;
} PROCESSOR_PERF_STATES_HV, *PPROCESSOR_PERF_STATES_HV;

typedef struct _PROCESSOR_PERF_CAP_HV {
    ULONG Version;
    ULONG InitialApicId;
    ULONG Ppc;
    ULONG Tpc;
    ULONG ThermalCap;
} PROCESSOR_PERF_CAP_HV, *PPROCESSOR_PERF_CAP_HV;

typedef struct _PROCESSOR_IDLE_DOMAIN {
    KAFFINITY_EX Members;
} PROCESSOR_IDLE_DOMAIN, *PPROCESSOR_IDLE_DOMAIN;

typedef struct _PROCESSOR_IDLE_DOMAINS {
    ULONG Version;
    ULONG Count;
    KAFFINITY_EX TargetProcessors;
    _Field_size_(Count) PROCESSOR_IDLE_DOMAIN State[ANYSIZE_ARRAY];
} PROCESSOR_IDLE_DOMAINS, *PPROCESSOR_IDLE_DOMAINS;

typedef struct _PPM_FORCE_IDLE {
    ULONG CStateIndex;
    PROCESSOR_NUMBER ProcessorNumber;
} PPM_FORCE_IDLE, *PPPM_FORCE_IDLE;

typedef struct _PROCESSOR_PERF_INFO {
    PROCESSOR_NUMBER Number;
    ULONG_PTR PerfContext;
    ULONG PlatformCap;
    ULONG ThermalCap;
    ULONG LimitReasons;
} PROCESSOR_PERF_INFO, *PPROCESSOR_PERF_INFO;

typedef struct _PROCESSOR_PERF_STATES {
    ULONG Version;
    USHORT Type;
    BOOLEAN HardPlatformCap;
    BOOLEAN AffinitizeControl;
    ULONG ProcessorCount;
    ULONG NominalFrequency;
    ULONG MaxPerfPercent;
    ULONG MinPerfPercent;
    ULONG MinThrottlePercent;
    ULONG FeedbackCounterCount;
    ULONG MinimumPerfCheckPeriod;
    UCHAR AutonomousMode;
    ULONG64 MinimumRelativePerformance;
    ULONG64 NominalRelativePerformance;
    KAFFINITY_EX TargetProcessors;
    PPROCESSOR_FETCH_MSR_ROUTINE GetFFHThrottleState;
    PPROCESSOR_POLICY_HANDLER TimeWindowHandler;
    PPROCESSOR_POLICY_HANDLER BoostPolicyHandler;
    PPROCESSOR_POLICY_HANDLER BoostModeHandler;
    PPROCESSOR_POLICY_HANDLER EnergyPerfPreferenceHandler;
    PPROCESSOR_POLICY_HANDLER AutonomousActivityWindowHandler;
    PPROCESSOR_POLICY_HANDLER AutonomousModeHandler;
    PPROCESSOR_POLICY_ACTION StartPolicyUpdate;
    PPROCESSOR_POLICY_ACTION CompletePolicyUpdate;
    PPROCESSOR_PERF_REINITIALIZE_HANDLER ReinitializeHandler;
    PPROCESSOR_PERF_SELECTION_HANDLER PerfSelectionHandler;
    PPROCESSOR_PERF_CONTROL_HANDLER PerfControlHandler;
    PPROCESSOR_PERF_CONTROL_ACTION PerfControlReadFeedback;
    PPROCESSOR_PERF_CONTROL_ACTION PerfControlAcquirePerformance;
    PPROCESSOR_PERF_CONTROL_ACTION PerfControlCommitPerformance;
    PPROCESSOR_PARK_PREFERENCE_HANDLER ParkPreference;
    _Field_size_(FeedbackCounterCount)
        PPROCESSOR_FEEDBACK_COUNTER FeedbackCounters;
    _Field_size_(ProcessorCount) PPROCESSOR_PERF_INFO Processors;
    _Field_size_(ProcessorCount * FeedbackCounterCount)
        PULONG_PTR CounterContexts;
} PROCESSOR_PERF_STATES, *PPROCESSOR_PERF_STATES;

typedef struct _PROCESSOR_PERF_STATES_COUNTERS_HV {
    ULONG Version;
    PVOID HypervisorStates;
    PPROCESSOR_PERF_STATES KernelStates;
} PROCESSOR_PERF_STATES_COUNTERS_HV, *PPROCESSOR_PERF_STATES_COUNTERS_HV;

#define PROCESSOR_PERF_MINIMUM_PERIOD_LIMIT 500000

typedef struct _PROCESSOR_CAP {
    ULONG Version;
    PROCESSOR_NUMBER ProcessorNumber;
    ULONG PlatformCap;
    ULONG ThermalCap;
    ULONG LimitReasons;
} PROCESSOR_CAP, *PPROCESSOR_CAP;

typedef struct _PROCESSOR_IDLE_VETO {
    ULONG Version;
    PROCESSOR_NUMBER ProcessorNumber;
    ULONG StateIndex;
    ULONG VetoReason;
    BOOLEAN Increment;
} PROCESSOR_IDLE_VETO, *PPROCESSOR_IDLE_VETO;

typedef struct _PLATFORM_IDLE_VETO {
    ULONG Version;
    ULONG StateIndex;
    ULONG VetoReason;
    BOOLEAN Increment;
} PLATFORM_IDLE_VETO, *PPLATFORM_IDLE_VETO;

typedef struct _PREREGISTERED_VETO_LIST {
    ULONG VetoCount;
    UNICODE_STRING VetoNames[ANYSIZE_ARRAY];
} PREREGISTERED_VETO_LIST, *PPREREGISTERED_VETO_LIST;

typedef struct _PROCESSOR_LOAD {
    PROCESSOR_NUMBER ProcessorNumber;
    UCHAR BusyPercentage;
    UCHAR FrequencyPercentage;
} PROCESSOR_LOAD, *PPROCESSOR_LOAD;

typedef struct _PEP_IDLE_VETO_REQUEST {
    ULONG StateIndex;
    ULONG VetoReason;
    BOOLEAN Increment;
} PEP_IDLE_VETO_REQUEST, *PPEP_IDLE_VETO_REQUEST;

// {E1500736-3E7F-4eb8-9013-F454CD4EDF75}
DEFINE_GUID(GUID_PROCESSOR_IDLE_VETO,
0xe1500736, 0x3e7f, 0x4eb8, 0x90, 0x13, 0xf4, 0x54, 0xcd, 0x4e, 0xdf, 0x75);

// {D3DC1B9D-F2D0-4d18-B6EF-5F2C06C0A2E0}
DEFINE_GUID(GUID_PLATFORM_IDLE_VETO,
0xd3dc1b9d, 0xf2d0, 0x4d18, 0xb6, 0xef, 0x5f, 0x2c, 0x6, 0xc0, 0xa2, 0xe0);

typedef struct _PEP_IDLE_UPDATE_REQUEST {
    ULONG StateIndex;
    ULONG Latency;
    ULONG BreakEvenDuration;
} PEP_IDLE_UPDATE_REQUEST, *PPEP_IDLE_UPDATE_REQUEST;

// {00A19FE5-1DD6-494f-9D46-4F04E0295F67}
DEFINE_GUID(GUID_PROCESSOR_IDLE_UPDATE,
0xa19fe5, 0x1dd6, 0x494f, 0x9d, 0x46, 0x4f, 0x4, 0xe0, 0x29, 0x5f, 0x67);

// {1BC4B44F-06FA-4f2e-B78D-8A440924F0EE}
DEFINE_GUID(GUID_PLATFORM_IDLE_UPDATE,
0x1bc4b44f, 0x6fa, 0x4f2e, 0xb7, 0x8d, 0x8a, 0x44, 0x9, 0x24, 0xf0, 0xee);

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_PERF_STATES (
    _In_ PPROCESSOR_PERF_STATES PerfStates
    );

typedef PPM_DISPATCH_REGISTER_PERF_STATES *PPPM_DISPATCH_REGISTER_PERF_STATES;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_PERF_CAP (
    _In_ PPROCESSOR_CAP PerfCap
    );

typedef PPM_DISPATCH_REGISTER_PERF_CAP *PPPM_DISPATCH_REGISTER_PERF_CAP;

typedef
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
PPM_DISPATCH_REGISTER_SPM_SETTINGS (
    _In_opt_ HANDLE ExternalRootKey
    );

typedef PPM_DISPATCH_REGISTER_SPM_SETTINGS *PPPM_DISPATCH_REGISTER_SPM_SETTINGS;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_IDLE_STATES (
    _In_ PPROCESSOR_IDLE_STATES_EX IdleStates
    );

typedef PPM_DISPATCH_REGISTER_IDLE_STATES *PPPM_DISPATCH_REGISTER_IDLE_STATES;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_IDLE_DOMAINS (
    _In_ CONST PROCESSOR_IDLE_DOMAINS *IdleDomains
    );

typedef PPM_DISPATCH_REGISTER_IDLE_DOMAINS *PPPM_DISPATCH_REGISTER_IDLE_DOMAINS;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_PLATFORM_STATES (
    _In_ PPLATFORM_IDLE_STATES PlatformIdleStates
    );

typedef PPM_DISPATCH_REGISTER_PLATFORM_STATES
    *PPPM_DISPATCH_REGISTER_PLATFORM_STATES;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_COORDINATED_STATES (
    _In_ PCOORDINATED_IDLE_STATES CoordinatedIdleStates
    );

typedef PPM_DISPATCH_REGISTER_COORDINATED_STATES
    *PPPM_DISPATCH_REGISTER_COORDINATED_STATES;

typedef
NTSTATUS
PPM_DISPATCH_UPDATE_PROCESSOR_IDLE_VETO (
    _In_ PPROCESSOR_IDLE_VETO IdleVeto
    );

typedef PPM_DISPATCH_UPDATE_PROCESSOR_IDLE_VETO
    *PPPM_DISPATCH_UPDATE_PROCESSOR_IDLE_VETO;

typedef
NTSTATUS
PPM_DISPATCH_UPDATE_PLATFORM_IDLE_VETO (
    _In_ PPLATFORM_IDLE_VETO IdleVeto
    );

typedef PPM_DISPATCH_UPDATE_PLATFORM_IDLE_VETO
    *PPPM_DISPATCH_UPDATE_PLATFORM_IDLE_VETO;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_VETO_LIST (
    _In_ PPREREGISTERED_VETO_LIST VetoList
    );

typedef PPM_DISPATCH_REGISTER_VETO_LIST *PPPM_DISPATCH_REGISTER_VETO_LIST;

typedef
NTSTATUS
PPM_DISPATCH_REMOVE_VETO_BIAS (
    VOID
    );

typedef PPM_DISPATCH_REMOVE_VETO_BIAS *PPPM_DISPATCH_REMOVE_VETO_BIAS;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_PERF_STATES_HV (
    _In_ CONST PROCESSOR_PERF_STATES_HV *PerfStates
    );

typedef PPM_DISPATCH_REGISTER_PERF_STATES_HV
    *PPPM_DISPATCH_REGISTER_PERF_STATES_HV;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_PERF_CAP_HV (
    _In_ CONST PROCESSOR_PERF_CAP_HV *PerfCap
    );

typedef PPM_DISPATCH_REGISTER_PERF_CAP_HV *PPPM_DISPATCH_REGISTER_PERF_CAP_HV;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_PERF_STATES_COUNTERS_HV (
    _In_ CONST PROCESSOR_PERF_STATES_COUNTERS_HV *PerfStateCounters
    );

typedef PPM_DISPATCH_REGISTER_PERF_STATES_COUNTERS_HV
    *PPPM_DISPATCH_REGISTER_PERF_STATES_COUNTERS_HV;

typedef
NTSTATUS
PPM_DISPATCH_REGISTER_IDLE_STATES_HV (
    _In_ CONST PROCESSOR_IDLE_STATES_HV *IdleStates
    );

typedef PPM_DISPATCH_REGISTER_IDLE_STATES_HV
    *PPPM_DISPATCH_REGISTER_IDLE_STATES_HV;

typedef
NTSTATUS
PPM_DISPATCH_SET_PROCESSOR_PEP (
    _In_ PVOID Handle
    );

typedef PPM_DISPATCH_SET_PROCESSOR_PEP
    *PPPM_DISPATCH_SET_PROCESSOR_PEP;

typedef
NTSTATUS
PPM_DISPATCH_PARK_PREFERENCE_NOTIFICATION (
    _In_ PVOID Handle,
    _Inout_ struct _PEP_PPM_PARK_SELECTION_V2 *ParkSelection
    );

typedef PPM_DISPATCH_PARK_PREFERENCE_NOTIFICATION
    *PPPM_DISPATCH_PARK_PREFERENCE_NOTIFICATION;

typedef
NTSTATUS
PPM_DISPATCH_IDLE_SELECT_NOTIFICATION (
    _In_ PVOID Handle,
    _Inout_ struct _PEP_PPM_IDLE_SELECT *IdleSelect
    );

typedef PPM_DISPATCH_IDLE_SELECT_NOTIFICATION
    *PPPM_DISPATCH_IDLE_SELECT_NOTIFICATION;

typedef
NTSTATUS
PPM_DISPATCH_QUERY_PLATFORM_STATE_NOTIFICATION (
    _In_ PVOID Handle,
    _Inout_ struct _PEP_PPM_QUERY_PLATFORM_STATE *QueryPlatformState,
    _In_ BOOLEAN Update
    );

typedef PPM_DISPATCH_QUERY_PLATFORM_STATE_NOTIFICATION
    *PPPM_DISPATCH_QUERY_PLATFORM_STATE_NOTIFICATION;

typedef
NTSTATUS
PPM_DISPATCH_QUERY_COORDINATED_DEPENDENCY_NOTIFICATION (
    _In_ PVOID Handle,
    _Inout_ struct _PEP_PPM_QUERY_COORDINATED_DEPENDENCY *QueryDependency
    );

typedef PPM_DISPATCH_QUERY_COORDINATED_DEPENDENCY_NOTIFICATION
    *PPPM_DISPATCH_QUERY_COORDINATED_DEPENDENCY_NOTIFICATION;

typedef
VOID
PPM_DISPATCH_REGISTER_ENERGY_ESTIMATION (
    _In_ PPROCESSOR_COMPUTE_ENERGY_ROUTINE ComputeEnergy,
    _In_ PPROCESSOR_SNAP_ENERGYCOUNTERS_ROUTINE SnapEnergyCounters
    );

typedef PPM_DISPATCH_REGISTER_ENERGY_ESTIMATION
    *PPPM_DISPATCH_REGISTER_ENERGY_ESTIMATION;

typedef struct _PPM_DRIVER_DISPATCH_TABLE {
    ULONG InterfaceVersion;
    PPPM_DISPATCH_REGISTER_PERF_STATES RegisterPerfStates;
    PPPM_DISPATCH_REGISTER_PERF_CAP RegisterPerfCap;
    PPPM_DISPATCH_REGISTER_SPM_SETTINGS RegisterSpmSettings;
    PPPM_DISPATCH_REGISTER_IDLE_STATES RegisterIdleStates;
    PPPM_DISPATCH_REGISTER_IDLE_DOMAINS RegisterIdleDomains;
    PPPM_DISPATCH_REGISTER_PLATFORM_STATES RegisterPlatformStates;
    PPPM_DISPATCH_REGISTER_COORDINATED_STATES RegisterCoordinatedStates;
    PPPM_DISPATCH_REGISTER_VETO_LIST RegisterVetoList;
    PPPM_DISPATCH_REMOVE_VETO_BIAS RemoveVetoBias;
    PPPM_DISPATCH_UPDATE_PROCESSOR_IDLE_VETO UpdateProcessorIdleVeto;
    PPPM_DISPATCH_UPDATE_PLATFORM_IDLE_VETO UpdatePlatformIdleVeto;
    PPPM_DISPATCH_REGISTER_PERF_STATES_HV RegisterPerfStatesHv;
    PPPM_DISPATCH_REGISTER_PERF_CAP_HV RegisterPerfCapHv;
    PPPM_DISPATCH_REGISTER_IDLE_STATES_HV RegisterIdleStatesHv;
    PPPM_DISPATCH_REGISTER_PERF_STATES_COUNTERS_HV RegisterPerfStatesCountersHv;
    PPPM_DISPATCH_SET_PROCESSOR_PEP SetProcessorPep;
    PPPM_DISPATCH_PARK_PREFERENCE_NOTIFICATION ParkPreferenceNotification;
    PPPM_DISPATCH_IDLE_SELECT_NOTIFICATION IdleSelectNotification;
    PPPM_DISPATCH_QUERY_PLATFORM_STATE_NOTIFICATION QueryPlatformStateNotification;
    PPPM_DISPATCH_QUERY_COORDINATED_DEPENDENCY_NOTIFICATION QueryCoordinatedDependencyNotification;
    PPPM_DISPATCH_REGISTER_ENERGY_ESTIMATION RegisterEnergyEstimation;
} PPM_DRIVER_DISPATCH_TABLE, *PPPM_DRIVER_DISPATCH_TABLE;


#if !defined(XBOX_SYSTEMOS)

NTSTATUS
DbgkWerAddSecondaryData (
    _In_ HANDLE ReportHandle,
    _In_reads_bytes_(sizeof(GUID)) LPCGUID Identifier,
    _In_reads_bytes_(Size) PVOID Data,
    _In_ ULONG Size
    );

#endif

#ifndef _OB_REFERENCE_TAGS_
#define _OB_REFERENCE_TAGS_

#define REFTAG_AFDCONN 'CdfA'
#define REFTAG_AFDENDPOINT 'EdfA'
#define REFTAG_AFDPOLL 'PdfA'
#define REFTAG_ALEIO 'IelA'
#define REFTAG_ALEPROCTBL 'PelA'
#define REFTAG_ALESIDTOKEN 'SelA'
#define REFTAG_CFSFILTER 'FsfC'
#define REFTAG_DWMKERNEL 'KmwD'
#define REFTAG_HTTP 'pttH'
#define REFTAG_MAILSLOT 'sFsM'
#define REFTAG_NFSVOLUME 'VsfN'
#define REFTAG_PGMFILE 'TmgP'
#define REFTAG_PSLOOKUP 'ULsP'
#define REFTAG_PSWAKE 'kWsP'
#define REFTAG_RAWENDPOINT 'EwaR'
#define REFTAG_TCPENDPOINT 'EpcT'
#define REFTAG_TCPLISTENER 'LpcT'
#define REFTAG_TCPTCB 'TpcT'
#define REFTAG_UDPENDPOINT 'EpdU'
#define REFTAG_USRKDESKTOP 'DrsU'
#define REFTAG_VIDEO_PORT_I386 'idiV'
#define REFTAG_VIDEO_PORT 'PdiV'
#define REFTAG_WIN32K 'k23W'
#define REFTAG_WIN32KQUEUE 'q23W'
#define REFTAG_WIN32KRESTRICT 'r23W'
#define REFTAG_WIN32KSERVER 'S23W'
#define REFTAG_WIN32KSTUBS 's23W'
#define REFTAG_WS2IFSL 'i2sW'
#define REFTAG_WSKNAMERES 'NksW'
#define REFTAG_WSKPROV 'PksW'
#define REFTAG_WSKTDI 'TksW'

#endif // _OB_REFERENCE_TAGS_

typedef enum _DRIVER_RUNTIME_INIT_FLAGS
{
    DrvRtPoolNxOptIn             = 0x00000001,
    LastDrvRtFlag
} DRIVER_RUNTIME_INIT_FLAGS, * PDRIVER_RUNTIME_INIT_FLAGS;

typedef const enum _DRIVER_RUNTIME_INIT_FLAGS * PCDRIVER_RUNTIME_INIT_FLAGS;

FORCEINLINE
VOID
ExInitializeDriverRuntime(
    _In_ ULONG RuntimeFlags)
{
#if POOL_NX_OPTIN && !POOL_NX_OPTOUT
    ULONG MajorVersion;
    ULONG MinorVersion;
    NTSTATUS Status;
    RTL_OSVERSIONINFOW VersionInfo;

    VersionInfo.dwOSVersionInfoSize = sizeof (VersionInfo);

    Status = RtlGetVersion (&VersionInfo);

    if (!NT_VERIFY (NT_SUCCESS (Status))) {
        MajorVersion = 5;
        MinorVersion = 0;
    } else {
        MajorVersion = VersionInfo.dwMajorVersion;
        MinorVersion = VersionInfo.dwMinorVersion;
    }

    if ((RuntimeFlags & DrvRtPoolNxOptIn) != 0) {

        if ((MajorVersion > 6) ||
            (MajorVersion == 6 &&
             MinorVersion >= 2)) {

            ExDefaultNonPagedPoolType = NonPagedPoolNx;
            ExDefaultMdlProtection = MdlMappingNoExecute;
        }
    }
#else
    UNREFERENCED_PARAMETER (RuntimeFlags);
#endif
}

extern POBJECT_TYPE *IoFileObjectType;
extern POBJECT_TYPE *IoDriverObjectType;
extern POBJECT_TYPE *LpcPortObjectType;
extern POBJECT_TYPE *LpcWaitablePortObjectType;

#if defined (_MSC_VER)
#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4001) /* nonstandard extension : single line comment */
#pragma warning(default:4201) /* nonstandard extension used : nameless struct/union */
#pragma warning(default:4214) /* nonstandard extension used : bit field types other then int */
#pragma warning(default:4115) /* named type definition in parentheses */
#endif
#endif

#endif // _NTOSP_

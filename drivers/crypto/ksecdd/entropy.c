

// TODO:
// - Can we save the entropy we collected in the VMPCR-CTX?
// - Hash the PRCB
// - Hash the PEB
// - Hash the TEB
// - Hash the PEB->Ldr
// - Use a GUID as a nonce / IV
//
// - On DriverLoad:
//   - Try to load entropy from registry (we can't!)
//   - Generate entropy and mix it with loaded entropy, if present (just hash it with the other data)
//
// - On DriverUnload:
//   - Save entropy to registry
//
// - On Crypt/Decrypt/GenRandom:
//   - Initialize RNG (this actually gives us more entropy!)
//   - Estimate entropy from sources and fill up with tsc, if available
//
// - On GenRandom:
//   - Either synchronize against other threads
//   - Or: Create new VMPC-R context, init with current entropy (key) and new entropy (IV)
//
// NIST recommend that you double the input entropy for each bit of output entropy when using a hash based extractor
// (e.g. SHA-256). This is because the output entropy is not a random number, but a hash of the input entropy.

#include "entropy.h"

#define _NDEBUG
#include <debug.h>

BOOLEAN KsecEntropyInitialized = FALSE;

// FIXME: defined in fltkernel.h
#define Add2Ptr(P,I) ((PVOID)((PUCHAR)(P) + (I)))

typedef struct _SYSINFO_ENTRY
{
    SYSTEM_INFORMATION_CLASS InformationClass;
    const WCHAR* ClassName;
    ULONG HeaderSize;
    ULONG EntrySize;
} SYSINFO_ENTRY;

VOID
HASHKEY_Init(
    PHASHKEY_CTX Ctx)
{
    sha512_init(&Ctx->Sha512Cts[0]);
    sha512_init(&Ctx->Sha512Cts[1]);
    sha512_init(&Ctx->Sha512Cts[2]);
    sha512_init(&Ctx->Sha512Cts[3]);
}

VOID
HASHKEY_Update(
    PHASHKEY_CTX Ctx,
    const UCHAR* Buffer,
    unsigned long Size)
{
    unsigned long chunkSize = Size / 4;

    sha512_update(&Ctx->Sha512Cts[0], Buffer, chunkSize);
    Buffer += chunkSize;
    sha512_update(&Ctx->Sha512Cts[1], Buffer, chunkSize);
    Buffer += chunkSize;
    sha512_update(&Ctx->Sha512Cts[2], Buffer, chunkSize);
    Buffer += chunkSize;
    sha512_update(&Ctx->Sha512Cts[3], Buffer, Size - (3 * chunkSize));
}


VOID
HASHKEY_Finalize(
    PHASHKEY_CTX Ctx,
    PHASHKEY Hash)
{
    sha512_finalize(&Ctx->Sha512Cts[0], Hash->Hashes[0].Data);
    sha512_finalize(&Ctx->Sha512Cts[1], Hash->Hashes[1].Data);
    sha512_finalize(&Ctx->Sha512Cts[2], Hash->Hashes[2].Data);
    sha512_finalize(&Ctx->Sha512Cts[3], Hash->Hashes[3].Data);
}

#if defined(_M_IX86) || defined(_M_AMD64)
static
ULONG
EstimateTscEntropy(void)
{
    static const ULONG TSC_LOOP_COUNT = 100;
    UCHAR Probabilities[16][2];
    ULONG CheckBit, Bias = 0;

    /* We check the lower 16 bits, everything above can be considered constant */
    for (CheckBit = 0; CheckBit < 16; CheckBit++)
    {
        UCHAR Bits[2] = { 0, 0 };
        ULONG Counts[2] = { 0, 0 };

        for (ULONG i = 0; i < TSC_LOOP_COUNT; i++)
        {
            /* Get the tsc value and extract the current bit */
            ULONG Tsc = (ULONG)__rdtsc();
            UCHAR BitSet = (Tsc >> CheckBit) & 1;

            /* Count equality with previous 2 values */
            Counts[0] += (BitSet == Bits[0]);
            Counts[1] += (BitSet == Bits[1]);

            /* Update previous values */
            Bits[0] = Bits[1];
            Bits[1] = BitSet;
        }

        /* Calculate probabilities and save them */
        Probabilities[CheckBit][0] = (UCHAR)(Counts[0] * 100 / TSC_LOOP_COUNT);
        Probabilities[CheckBit][1] = (UCHAR)(Counts[1] * 100 / TSC_LOOP_COUNT);
    }

    for (CheckBit = 0; CheckBit < 16; CheckBit++)
    {
        DPRINT("Bit %u: %u%% %u%%\n", CheckBit, Probabilities[CheckBit][0], Probabilities[CheckBit][1]);
        Bias += abs(50 - Probabilities[CheckBit][0]);
        Bias += abs(50 - Probabilities[CheckBit][1]);
    }

    return 16 - (Bias / 100);
}
#endif

VOID
NTAPI
KsecReadMachineSpecificCounters(
    _Out_ PKSEC_MACHINE_SPECIFIC_COUNTERS MachineSpecificCounters)
{
#if defined(_M_IX86) || defined(_M_AMD64)
    /* Check if RDTSC is available */
    if (ExIsProcessorFeaturePresent(PF_RDTSC_INSTRUCTION_AVAILABLE))
    {
        /* Read the TSC value */
        MachineSpecificCounters->Tsc = __rdtsc();
    }
#if 0 // FIXME: investigate what the requirements are for these
    /* Read the CPU event counter MSRs */
    //MachineSpecificCounters->Ctr0 = __readmsr(0x12);
    //MachineSpecificCounters->Ctr1 = __readmsr(0x13);

    /* Check if this is an MMX capable CPU */
    if (ExIsProcessorFeaturePresent(PF_MMX_INSTRUCTIONS_AVAILABLE))
    {
        /* Read the CPU performance counters 0 and 1 */
        MachineSpecificCounters->Pmc0 = __readpmc(0);
        MachineSpecificCounters->Pmc1 = __readpmc(1);
    }
#endif
#elif defined(_M_ARM)
    /* Read the Cycle Counter Register */
    MachineSpecificCounters->Ccr = _MoveFromCoprocessor(CP15_PMCCNTR);
#else
#error Implement me!
#endif
}

VOID
NTAPI
KsecGatherFastEntropy(
    _Out_ PFAST_ENTROPY Entropy)
{
    Entropy->CurrentProcess = PsGetCurrentProcess();
    Entropy->CurrentThread = PsGetCurrentThread();
    KeQueryTickCount(&Entropy->TickCount);
    KeQuerySystemTime(&Entropy->SystemTime);
    Entropy->PerformanceCounter = KeQueryPerformanceCounter(
        &Entropy->PerformanceFrequency);
    KsecReadMachineSpecificCounters(&Entropy->MachineSpecificCounters);
}

NTSTATUS
NTAPI
KsecOpenRNGKey(
    PHANDLE KeyHandleRNG)
{
    static UNICODE_STRING KeyNameString = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\SOFTWARE\\ReactOS\\Cryptography\\RNG");
    OBJECT_ATTRIBUTES ObjectAttributes;
    NTSTATUS Status;
    HANDLE KeyHandle;

    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyNameString,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = ZwOpenKey(&KeyHandle, KEY_ALL_ACCESS, &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    *KeyHandleRNG = KeyHandle;
    return STATUS_SUCCESS;
}
    

NTSTATUS
NTAPI
KsecCreateSubKey(
    _In_ HANDLE RootHandle,
    _In_ PWSTR SubKeyName,
    _Out_ PHANDLE KeyHandle)
{
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING SubKeyNameString;
    NTSTATUS Status;

    /* Initialize the unicode string */
    RtlInitUnicodeString(&SubKeyNameString, SubKeyName);

    /* Initialize the object attributes */
    InitializeObjectAttributes(&ObjectAttributes,
        &SubKeyNameString,
        OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
        RootHandle,
        NULL);

    /* Create the key */
    Status = ZwCreateKey(KeyHandle,
        KEY_ALL_ACCESS,
        &ObjectAttributes,
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        NULL);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Return success */
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
KsecOpenRNGRegistryKey(
    _Out_ PHANDLE OutKeyHandle)
{
    HANDLE RootKeyHandle, KeyHandle;
    NTSTATUS Status;

    /* Open the SOFTWARE key */
    Status = KsecCreateSubKey(NULL, L"\\Registry\\Machine\\SOFTWARE", &RootKeyHandle);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Open the ReactOS key */
    Status = KsecCreateSubKey(RootKeyHandle, L"ReactOS", &KeyHandle);
    ZwClose(RootKeyHandle);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Open the Cryptography key */
    RootKeyHandle = KeyHandle;
    Status = KsecCreateSubKey(RootKeyHandle, L"Cryptography", &KeyHandle);
    ZwClose(RootKeyHandle);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Open the RNG key */
    RootKeyHandle = KeyHandle;
    Status = KsecCreateSubKey(RootKeyHandle, L"RNG", &KeyHandle);
    ZwClose(RootKeyHandle);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    *OutKeyHandle = KeyHandle;
    return Status;
}


static
ULONG
BitCompare(
    const ULONG* Buffer1,
    const ULONG* Buffer2,
    ULONG Length)
{
    ULONG difference = 0;

    for (ULONG i = 0; i < Length; i++)
    {
        difference += __popcnt16(Buffer1[i] ^ Buffer2[i]);
    }

    return difference;
}


static
NTSTATUS
EstimateEntropyFromRegistry(
    HANDLE KeyHandleEntropy,
    PCWSTR ValueName,
    ULONG HeaderSize,
    ULONG EntrySize,
    PVOID Buffer,
    ULONG DataLength,
    PULONG OutEntropy)
{
    UNICODE_STRING ValueNameString;
    ULONG Entropy, FullEntropy = 0;
    PVOID RegistryData;
    ULONG RegistryDataSize;
    ULONG EntryCount;
    NTSTATUS Status;
    PKEY_VALUE_PARTIAL_INFORMATION KeyValueInfo;
    ULONG KeyValueInfoSize;
    ULONG ResultLength;

    if (KeyHandleEntropy == NULL)
    {
        return STATUS_UNSUCCESSFUL;
    }

    RtlInitUnicodeString(&ValueNameString, ValueName);

    /* Allocate a buffer for the registry value (header + 1 entry) */
    KeyValueInfoSize = sizeof(KEY_VALUE_PARTIAL_INFORMATION) + HeaderSize + EntrySize;
    KeyValueInfo = (PKEY_VALUE_PARTIAL_INFORMATION)ExAllocatePoolWithTag(PagedPool,
                                                                         KeyValueInfoSize,
                                                                         'pEsK');
    if (KeyValueInfo == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // Query the keyValue into the buffer
    Status = ZwQueryValueKey(KeyHandleEntropy,
                             &ValueNameString,
                             KeyValuePartialInformation,
                             KeyValueInfo,
                             KeyValueInfoSize,
                             &ResultLength);
    if (NT_SUCCESS(Status))
    {
        RegistryData = KeyValueInfo->Data;
        RegistryDataSize = KeyValueInfo->DataLength;

        if (RegistryDataSize != (HeaderSize + EntrySize))
        {
            Status = STATUS_INTERNAL_ERROR;
            goto Exit;
        }

        // compare header
        if (HeaderSize != 0)
        {
            Entropy = BitCompare(Buffer, RegistryData, HeaderSize);
            FullEntropy += Entropy;
        }

        if (EntrySize != 0)
        {
            Entropy = BitCompare(Add2Ptr(Buffer, HeaderSize),
                Add2Ptr(RegistryData, HeaderSize),
                EntrySize);

            EntryCount = (DataLength - HeaderSize) / EntrySize;
            FullEntropy += Entropy * EntryCount;
        }
    }

    /* Write the new data to the registry */
    Status = ZwSetValueKey(KeyHandleEntropy,
                           &ValueNameString,
                           0,
                           REG_BINARY,
                           Buffer,
                           HeaderSize + EntrySize);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed to write entropy data for '%wZ' to registry.\n", &ValueName);
    }

    Status = STATUS_SUCCESS;

Exit:

    ExFreePool(KeyValueInfo);

    *OutEntropy = FullEntropy;
    return Status;
}

/*

SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION (per CPU)
    IdleTime.QuadPart = UInt32x32To64(TotalTime, KeMaximumIncrement);
    KernelTime.QuadPart =  UInt32x32To64(Prcb->KernelTime, KeMaximumIncrement);
    UserTime.QuadPart = UInt32x32To64(Prcb->UserTime, KeMaximumIncrement);
    DpcTime.QuadPart = UInt32x32To64(Prcb->DpcTime, KeMaximumIncrement);
    InterruptTime.QuadPart = UInt32x32To64(Prcb->InterruptTime, KeMaximumIncrement);
    InterruptCount = Prcb->InterruptCount;

SYSTEM_PERFORMANCE_INFORMATION
    IdleProcessTime.QuadPart = UInt32x32To64(IdleKernel, KeMaximumIncrement);
    IoReadTransferCount = IoReadTransferCount;
    IoWriteTransferCount = IoWriteTransferCount;
    IoOtherTransferCount = IoOtherTransferCount;
    IoReadOperationCount = IoReadOperationCount;
    IoWriteOperationCount = IoWriteOperationCount;
    IoOtherOperationCount = IoOtherOperationCount;
    + for each CPU from PCR

SYSTEM_EXCEPTION_INFORMATION
    All from PRCB

SYSTEM_LOOKASIDE_INFORMATION
    All from dynamic lists

SYSTEM_INTERRUPT_INFORMATION

SYSTEM_PROCESS_INFORMATION



Low-level system information:
(SYSTEM_PERFORMANCE_INFORMATION):
+ Idle Process Time,
+ Io Read Transfer Count,
+ I/O Write Transfer Count,
+ I/O Other Transfer Count,
+ I/O Read Operation Count,
+ I/O Write Operation Count,
+ I/O Other Operation Count,
+ Available Pages,
+ Committed Pages,
+ Commit Limit,
+ Peak Commitment,
+ Page Fault Count,
+ Copy On Write Count,
+ Transition Count,
+ Cache Transition Count,
+ Demand Zero Count,
+ Page Read Count,
+ Page Read I/O Count,
+ Cache Read Count,
+ Cache I/O Count,
+ Dirty Pages Write Count,
+ Dirty Write I/O Count,
+ Mapped Pages Write Count,
+ Mapped Write I/O Count,
+ Paged Pool Pages,
+ Non Paged Pool Pages,
+ Paged Pool Allocated space,
+ Paged Pool Free space,
+ Non Paged Pool Allocated space,
+ Non Paged Pool Free space,
+ Free System page table entry,
+ Resident System Code Page,
+ Total System Driver Pages,
+ Total System Code Pages,
+ Non Paged Pool Lookaside Hits,
+ Paged Pool Lookaside Hits,
- Available Paged Pool Pages, (Spare3Count?)
+ Resident System Cache Page,
+ Resident Paged Pool Page,
+ Resident System Driver Page,
+ Cache manager Fast Read with No Wait,
+ Cache manager Fast Read with Wait,
+ Cache manager Fast Read Resource Missed,
+ Cache manager Fast Read Not Possible,
+ Cache manager Fast Memory Descriptor List Read with No Wait,
+ Cache manager Fast Memory Descriptor List Read with Wait,
+ Cache manager Fast Memory Descriptor List Read Resource Missed,
+ Cache manager Fast Memory Descriptor List Read Not Possible,
+ Cache manager Map Data with No Wait,
+ Cache manager Map Data with Wait,
+ Cache manager Map Data with No Wait Miss,
+ Cache manager Map Data Wait Miss,
+ Cache manager Pin-Mapped Data Count,
+ Cache manager Pin-Read with No Wait,
+ Cache manager Pin Read with Wait,
+ Cache manager Pin-Read with No Wait Miss,
+ Cache manager Pin-Read Wait Miss,
+ Cache manager Copy-Read with No Wait,
+ Cache manager Copy-Read with Wait,
+ Cache manager Copy-Read with No Wait Miss,
+ Cache manager Copy-Read with Wait Miss,
+ Cache manager Memory Descriptor List Read with No Wait,
+ Cache manager Memory Descriptor List Read with Wait,
+ Cache manager Memory Descriptor List Read with No Wait Miss,
+ Cache manager Memory Descriptor List Read with Wait Miss,
+ Cache manager Read Ahead IOs,
+ Cache manager Lazy-Write IOs,
+ Cache manager Lazy-Write Pages,
+ Cache manager Data Flushes,
+ Cache manager Data Pages,
+ Context Switches,
+ First Level Translation buffer Fills,
+ Second Level Translation buffer Fills,
+ and System Calls.

System exception information consisting of
(SYSTEM_EXCEPTION_INFORMATION)
Alignment Fix up Count,
Exception Dispatch Count,
Floating Emulation Count,
and Byte Word Emulation Count.

System lookaside information consisting of
Current Depth,
Maximum Depth,
Total Allocates,
Allocate Misses,
Total Frees,
Free Misses,
Type,
Tag,
and Size.

System interrupt information consisting of
context switches,
deferred procedure call count,
deferred procedure call rate,
time increment,
deferred procedure call bypass count,
and asynchronous procedure call bypass count.

System process information consisting of
Next Entry Offset,
Number Of Threads,
Create Time,
User Time,
Kernel Time,
Image Name,
Base Priority,
Unique Process ID,
Inherited from Unique Process ID,
Handle Count,
Session ID,
Page Directory Base,
Peak Virtual Size,
Virtual Size,
Page Fault Count,
Peak Working Set Size,
Working Set Size,
Quota Peak Paged Pool Usage,
Quota Paged Pool Usage,
Quota Peak Non Paged Pool Usage,
Quota Non Paged Pool Usage,
Page file Usage,
Peak Page file Usage,
Private Page Count,
Read Operation Count,
Write Operation Count,
Other Operation Count,
Read Transfer Count,
Write Transfer Count,
and Other Transfer Count.
*/
#define _WS(x) L##x
#define SIC(x) (x), _WS(#x)
static const SYSINFO_ENTRY SysInfoEntries[] =
{
    { SIC(SystemBasicInformation), sizeof(SYSTEM_BASIC_INFORMATION), 0 },
    { SIC(SystemProcessorInformation), sizeof(SYSTEM_PROCESSOR_INFORMATION), 0},
    { SIC(SystemPerformanceInformation), sizeof(SYSTEM_PERFORMANCE_INFORMATION), 0},
    { SIC(SystemTimeOfDayInformation), sizeof(SYSTEM_TIMEOFDAY_INFORMATION), 0},
    // { SIC(SystemPathInformation), sizeof(SYSTEM_PATH_INFORMATION), 0}, // obsolete
    { SIC(SystemProcessInformation), sizeof(SYSTEM_PROCESS_INFORMATION), -1}, // The entries are actually dynamic
    { SIC(SystemCallCountInformation), sizeof(SYSTEM_CALL_COUNT_INFORMATION), 0}, // not implemented
    { SIC(SystemDeviceInformation), sizeof(SYSTEM_DEVICE_INFORMATION), 0},
    { SIC(SystemProcessorPerformanceInformation), sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION), 0},
    { SIC(SystemFlagsInformation), sizeof(SYSTEM_FLAGS_INFORMATION), 0},
    { SIC(SystemCallTimeInformation), sizeof(SYSTEM_CALL_TIME_INFORMATION), sizeof(LARGE_INTEGER) },
    { SIC(SystemModuleInformation), sizeof(ULONG), sizeof(RTL_PROCESS_MODULE_INFORMATION) },
    { SIC(SystemLocksInformation), sizeof(ULONG), sizeof(RTL_PROCESS_LOCK_INFORMATION) },
    { SIC(SystemStackTraceInformation), FIELD_OFFSET(RTL_PROCESS_BACKTRACES, BackTraces), sizeof(RTL_PROCESS_BACKTRACE_INFORMATION) },
    { SIC(SystemPagedPoolInformation), sizeof(SYSTEM_PAGEFILE_INFORMATION), 0}, // Dynamic!
    { SIC(SystemNonPagedPoolInformation), sizeof(SYSTEM_PAGEFILE_INFORMATION), 0}, // Dynamic!
    { SIC(SystemHandleInformation), FIELD_OFFSET(SYSTEM_HANDLE_INFORMATION, Handles), sizeof(SYSTEM_HANDLE_TABLE_ENTRY_INFO)},
    { SIC(SystemObjectInformation), sizeof(SYSTEM_OBJECT_INFORMATION), 0}, // Dynamic
    { SIC(SystemPageFileInformation), sizeof(SYSTEM_PAGEFILE_INFORMATION), 0}, // Dynamic
    { SIC(SystemVdmInstemulInformation), sizeof(SYSTEM_VDM_INSTEMUL_INFO), 0},
    { SIC(SystemVdmBopInformation), sizeof(ULONG), 0},
    { SIC(SystemFileCacheInformation), sizeof(SYSTEM_FILECACHE_INFORMATION), 0},
    { SIC(SystemPoolTagInformation), FIELD_OFFSET(SYSTEM_POOLTAG_INFORMATION, TagInfo), sizeof(SYSTEM_POOLTAG) },
    { SIC(SystemInterruptInformation), sizeof(SYSTEM_INTERRUPT_INFORMATION), 0},
    { SIC(SystemDpcBehaviorInformation), sizeof(SYSTEM_DPC_BEHAVIOR_INFORMATION), 0},
    // { SIC(SystemFullMemoryInformation), FIELD_OFFSET(SYSTEM_MEMORY_INFORMATION, Memory), sizeof(SYSTEM_MEMORY_INFO)}, DBG only function
    // { SIC(SystemLoadGdiDriverInformation), sizeof(SYSTEM_GDI_DRIVER_INFORMATION), 0},
    // { SIC(SystemUnloadGdiDriverInformation), sizeof(PVOID), 0},
    { SIC(SystemTimeAdjustmentInformation), sizeof(SYSTEM_QUERY_TIME_ADJUST_INFORMATION), 0},
    { SIC(SystemSummaryMemoryInformation), FIELD_OFFSET(SYSTEM_MEMORY_INFORMATION, Memory), sizeof(SYSTEM_MEMORY_INFO) },
    // { SIC(SystemMirrorMemoryInformation), sizeof(BOOLEAN), 0}, // SET only
    { SIC(SystemPerformanceTraceInformation), sizeof(SYSTEM_REF_TRACE_INFORMATION), 0},
    // { SIC(SystemObsolete0), sizeof(SYSTEM_OBJECT_INFORMATION), 0},
    { SIC(SystemExceptionInformation), sizeof(SYSTEM_EXCEPTION_INFORMATION), 0},
    { SIC(SystemCrashDumpStateInformation), sizeof(SYSTEM_CRASH_STATE_INFORMATION), 0},
    { SIC(SystemKernelDebuggerInformation), sizeof(SYSTEM_KERNEL_DEBUGGER_INFORMATION), 0},
    { SIC(SystemContextSwitchInformation), sizeof(SYSTEM_CONTEXT_SWITCH_INFORMATION), 0},
    { SIC(SystemRegistryQuotaInformation), sizeof(SYSTEM_REGISTRY_QUOTA_INFORMATION), 0},
    { SIC(SystemExtendServiceTableInformation), sizeof(UNICODE_STRING), 0},
    { SIC(SystemPrioritySeperation), sizeof(ULONG), 0},
    // { SIC(SystemVerifierAddDriverInformation), sizeof(UNICODE_STRING), 0 }, // SET only
    // { SIC(SystemVerifierRemoveDriverInformation), sizeof(UNICODE_STRING ), 0}, // SET only
    { SIC(SystemProcessorIdleInformation), 0, sizeof(SYSTEM_PROCESSOR_IDLE_INFORMATION) },
    { SIC(SystemLegacyDriverInformation), sizeof(SYSTEM_LEGACY_DRIVER_INFORMATION), 0},
    { SIC(SystemCurrentTimeZoneInformation), sizeof(RTL_TIME_ZONE_INFORMATION), 0},
    { SIC(SystemLookasideInformation), sizeof(SYSTEM_LOOKASIDE_INFORMATION), 0},
    { SIC(SystemTimeSlipNotification), sizeof(HANDLE), 0},
    { SIC(SystemSessionCreate), sizeof(ULONG), 0},
    { SIC(SystemSessionDetach), sizeof(ULONG), 0},
    // { SIC(SystemSessionInformation), sizeof(char), 0}, // Not implemented on Windows
    { SIC(SystemRangeStartInformation), sizeof(ULONG_PTR), 0},
    { SIC(SystemVerifierInformation), sizeof(SYSTEM_VERIFIER_INFORMATION), 0},
    // { SIC(SystemVerifierThunkExtend), sizeof(char), 0}, // Undocumented
    { SIC(SystemSessionProcessesInformation), sizeof(SYSTEM_SESSION_PROCESS_INFORMATION), 0},
    // { SIC(SystemLoadGdiDriverInSystemSpace), sizeof(char), 0},
    { SIC(SystemNumaProcessorMap), FIELD_OFFSET(SYSTEM_NUMA_INFORMATION, ActiveProcessorsAffinityMask), sizeof(GROUP_AFFINITY) },
    { SIC(SystemPrefetcherInformation), sizeof(SUPERFETCH_INFORMATION), 0},
    { SIC(SystemExtendedProcessInformation), sizeof(char), 0},
    { SIC(SystemRecommendedSharedDataAlignment), sizeof(char), 0},
    { SIC(SystemComPlusPackage), sizeof(char), 0},
    { SIC(SystemNumaAvailableMemory), FIELD_OFFSET(SYSTEM_NUMA_INFORMATION, AvailableMemory), sizeof(ULONGLONG) },
    { SIC(SystemProcessorPowerInformation), sizeof(char), 0},
    { SIC(SystemEmulationBasicInformation), sizeof(char), 0},
    { SIC(SystemEmulationProcessorInformation), sizeof(char), 0},
    { SIC(SystemExtendedHandleInformation), FIELD_OFFSET(SYSTEM_HANDLE_INFORMATION_EX, Handle), sizeof(SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX)},
    // { SIC(SystemExtendedHandleInformation), 0, 0 },
    // { SIC(SystemLostDelayedWriteInformation), 0, 0 },
    // { SIC(SystemBigPoolInformation), sizeof(_____), 0 },
    // { SIC(SystemSessionPoolTagInformation), sizeof(_____), 0 },
    // { SIC(SystemSessionMappedViewInformation), sizeof(_____), 0 },
    // { SIC(SystemHotpatchInformation), sizeof(_____), 0 },
    // { SIC(SystemObjectSecurityMode), sizeof(_____), 0 },
    // { SIC(SystemWatchdogTimerHandler), sizeof(_____), 0 },
    // { SIC(SystemWatchdogTimerInformation), sizeof(_____), 0 },
    // { SIC(SystemLogicalProcessorInformation), sizeof(_____), 0 },
    // { SIC(SystemWow64SharedInformationObsolete), sizeof(_____), 0 },
    // { SIC(SystemRegisterFirmwareTableInformationHandler), sizeof(_____), 0 },
    // { SIC(SystemFirmwareTableInformation), sizeof(_____), 0 },
    // { SIC(SystemModuleInformationEx), sizeof(_____), 0 },
    // { SIC(SystemVerifierTriageInformation), sizeof(_____), 0 },
    // { SIC(SystemSuperfetchInformation), sizeof(_____), 0 },
    // { SIC(SystemMemoryListInformation), sizeof(_____), 0 },
    // { SIC(SystemFileCacheInformationEx), sizeof(_____), 0 },
    // { SIC(SystemThreadPriorityClientIdInformation), sizeof(_____), 0 },
    // { SIC(SystemProcessorIdleCycleTimeInformation), sizeof(_____), 0 },
    // { SIC(SystemVerifierCancellationInformation), sizeof(_____), 0 },
    // { SIC(SystemProcessorPowerInformationEx), sizeof(_____), 0 },
    // { SIC(SystemRefTraceInformation), sizeof(_____), 0 },
    // { SIC(SystemSpecialPoolInformation), sizeof(_____), 0 },
    // { SIC(SystemProcessIdInformation), sizeof(_____), 0 },
    // { SIC(SystemErrorPortInformation), sizeof(_____), 0 },
    // { SIC(SystemBootEnvironmentInformation), sizeof(_____), 0 },
    // { SIC(SystemHypervisorInformation), sizeof(_____), 0 },
    // { SIC(SystemVerifierInformationEx), sizeof(_____), 0 },
    // { SIC(SystemTimeZoneInformation), sizeof(_____), 0 },
    // { SIC(SystemImageFileExecutionOptionsInformation), sizeof(_____), 0 },
    // { SIC(SystemCoverageInformation), sizeof(_____), 0 },
    // { SIC(SystemPrefetchPatchInformation), sizeof(_____), 0 },
    // { SIC(SystemVerifierFaultsInformation), sizeof(_____), 0 },

};

// FIXME:
// - 0: SystemBasicInformation -> STATUS_INFO_LENGTH_MISMATCH
// - 5: SystemCallCountInformation -> STATUS_INFO_LENGTH_MISMATCH
// - SystemProcessInformation -> STATUS_INFO_LENGTH_MISMATCH
// - SystemCallTimeInformation -> STATUS_NOT_IMPLEMENTED
// - SystemModuleInformation -> STATUS_INFO_LENGTH_MISMATCH
// - SystemLocksInformation -> STATUS_NOT_IMPLEMENTED
// - SystemHandleInformation -> STATUS_INFO_LENGTH_MISMATCH

/*!
 *  \see http://blogs.msdn.com/b/michael_howard/archive/2005/01/14/353379.aspx
 * -> https://web.archive.org/web/20180929235240/https://blogs.msdn.microsoft.com/michael_howard/2005/01/14/cryptographically-secure-random-number-on-windows-without-using-cryptoapi/
 */
ULONG
KsecHashSystemInformation(
    _In_ HANDLE KeyHandleEntropy,
    _Out_ PHASHKEY_CTX Hash2048Ctx)
{
    ULONG ReturnLength;
    ULONG Entropy, FullEntropy = 0;
    NTSTATUS Status;
    PVOID Buffer;
    ULONG BufferSize, InfoSize;
    ULONG i;
    ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);

    /* Allocate a buffer */
    BufferSize = 0x8000;
    Buffer = ExAllocatePoolWithTag(PagedPool, BufferSize, 'pEsK');
    if (Buffer == NULL)
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto Exit;
    }

    //
    for (i = 0; i < _countof(SysInfoEntries); i++)
    {
        if (SysInfoEntries[i].EntrySize != 0)
        {
            InfoSize = BufferSize;
        }
        else
        {
            InfoSize = SysInfoEntries[i].HeaderSize;
        }

        /* Query the information */
        Status = ZwQuerySystemInformation(SysInfoEntries[i].InformationClass,
                                          Buffer,
                                          InfoSize,
                                          &ReturnLength);
        if (!NT_SUCCESS(Status))
        {
            if (Status == STATUS_NOT_IMPLEMENTED) continue;

            __debugbreak();
            Status = ZwQuerySystemInformation(SysInfoEntries[i].InformationClass,
                                              Buffer,
                                              InfoSize,
                                              &ReturnLength);

            continue;
        }

        InfoSize = min(ReturnLength, BufferSize);

        /* Hash the data */
        HASHKEY_Update(Hash2048Ctx, Buffer, InfoSize);

        /* Try to figure out the entropy */
        Status = EstimateEntropyFromRegistry(KeyHandleEntropy,
                                             SysInfoEntries[i].ClassName,
                                             SysInfoEntries[i].HeaderSize,
                                             SysInfoEntries[i].EntrySize,
                                             Buffer,
                                             ReturnLength,
                                             &Entropy);
        if (!NT_SUCCESS(Status))
        {
            Entropy = 1;
        }

        FullEntropy += Entropy;
    }

Exit:

    /* Return how much entropy we estimated */
    return FullEntropy;
}


NTSTATUS
NTAPI
KsecGatherBootEntropy(
    _Out_ PHASHKEY HashKey
    )
{
    HASHKEY_CTX HashKeyCtx;
    PKPRCB Prcb;
    NTSTATUS Status;
    HANDLE KeyHandleRNG;
    HANDLE KeyHandleEntropy;
    ULONG Entropy;
    ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);

    __debugbreak();

    HASHKEY_Init(&HashKeyCtx);

   // Open the registry key
    Status = KsecOpenRNGKey(&KeyHandleRNG);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("Failed1!\n");
        // Open the registry key
        Status = KsecOpenRNGRegistryKey(&KeyHandleRNG);
        if (!NT_SUCCESS(Status))
        {
            DPRINT1("Failed2!\n");
            KeyHandleRNG = NULL;
        }
    }

    /* Open the Entropy key */
    Status = KsecCreateSubKey(KeyHandleRNG, L"Entropy", &KeyHandleEntropy);
    if (!NT_SUCCESS(Status))
    {
        KeyHandleEntropy = NULL;
        //return Status;
    }

    /* Hash previous seed from registry */

    /* Hash the PRCB */
    Prcb = KeGetCurrentPrcb();
    HASHKEY_Update(&HashKeyCtx, (PUCHAR)Prcb, sizeof(KPRCB));

    Status = EstimateEntropyFromRegistry(KeyHandleEntropy,
                                         L"Prcb",
                                         sizeof(KPRCB),
                                         0,
                                         Prcb,
                                         sizeof(KPRCB),
                                         &Entropy);

    
    // FIXME: return type!
    Status = KsecHashSystemInformation(KeyHandleRNG, &HashKeyCtx);

    ZwClose(KeyHandleRNG);
    ZwClose(KeyHandleEntropy);

    HASHKEY_Finalize(&HashKeyCtx, HashKey);

    return Status;
}

VOID
NTAPI
KsecSaveEntropy(
    VOID)
{
    // TODO: Implement
}

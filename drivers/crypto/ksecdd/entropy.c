

#include "entropy.h"

#define _NDEBUG
#include <debug.h>

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
HASH2048_Init(
    PHASH2048_CTX Ctx)
{
    sha512_init(&Ctx->Sha512Cts[0]);
    sha512_init(&Ctx->Sha512Cts[1]);
    sha512_init(&Ctx->Sha512Cts[2]);
    sha512_init(&Ctx->Sha512Cts[3]);
}

void
HASH2048_Update(
    PHASH2048_CTX Ctx,
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
HASH2048_Finalize(
    PHASH2048_CTX Ctx,
    PHASH2048 Hash)
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
    HANDLE KeyHandle,
    PUNICODE_STRING ValueName,
    ULONG HeaderSize,
    ULONG EntrySize,
    PVOID Buffer,
    ULONG DataLength,
    PULONG OutEntropy)
{
    ULONG Entropy, FullEntropy = 0;
    PVOID RegistryData;
    ULONG RegistryDataSize;
    ULONG AllocationSize;
    ULONG EntryCount;
    NTSTATUS Status;
    PKEY_VALUE_PARTIAL_INFORMATION KeyValueInfo;
    ULONG ResultLength;

    /* Allocate a buffer for the registry value (header + 1 entry) */
    AllocationSize = sizeof(KEY_VALUE_PARTIAL_INFORMATION) + HeaderSize + EntrySize;
    KeyValueInfo = (PKEY_VALUE_PARTIAL_INFORMATION)ExAllocatePoolWithTag(PagedPool, 1024, 'pEsK');
    if (KeyValueInfo == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // Query the keyValue into the buffer
    Status = ZwQueryValueKey(KeyHandle,
                             ValueName,
                             KeyValuePartialInformation,
                             KeyValueInfo,
                             sizeof(KeyValueInfo),
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

    /* Copy the new data to the registry buffer */
    RegistryDataSize = HeaderSize + EntrySize;
    RtlCopyMemory(RegistryData, Buffer, RegistryDataSize);

    /* Write the new data to the registry */
    Status = ZwSetValueKey(KeyHandle, ValueName, 0, REG_BINARY, KeyValueInfo, HeaderSize + EntrySize);
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

static const SYSINFO_ENTRY SysInfoEntries[] =
{
    { SystemBasicInformation, L"SystemBasicInformation", sizeof(SYSTEM_BASIC_INFORMATION), 0 },
    //{SystemProcessorInformation, L"SystemProcessorInformation", sizeof(SYSTEM_PROCESSOR_INFORMATION), 0}, // 0 entropy!
    { SystemPerformanceInformation, L"SystemPerformanceInformation", sizeof(SYSTEM_PERFORMANCE_INFORMATION), 0},
    { SystemTimeOfDayInformation, L"SystemTimeOfDayInformation", sizeof(SYSTEM_TIMEOFDAY_INFORMATION), 0},
    // {SystemPathInformation, L"SystemPathInformation", sizeof(SYSTEM_PATH_INFORMATION), 0}, // obsolete
    { SystemProcessInformation, L"SystemProcessInformation", sizeof(SYSTEM_PROCESS_INFORMATION), -1}, // The entries are actually dynamic
    { SystemCallCountInformation, L"SystemCallCountInformation", sizeof(SYSTEM_CALL_COUNT_INFORMATION), 0},
    { SystemDeviceInformation, L"SystemDeviceInformation", sizeof(SYSTEM_DEVICE_INFORMATION), 0},
    { SystemProcessorPerformanceInformation, L"SystemProcessorPerformanceInformation", sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION), 0},
    { SystemFlagsInformation, L"SystemFlagsInformation", sizeof(SYSTEM_FLAGS_INFORMATION), 0},

};

/*!
 *  \see http://blogs.msdn.com/b/michael_howard/archive/2005/01/14/353379.aspx
 * -> https://web.archive.org/web/20180929235240/https://blogs.msdn.microsoft.com/michael_howard/2005/01/14/cryptographically-secure-random-number-on-windows-without-using-cryptoapi/
 */
ULONG
KsecHashSystemInformation(
    _In_ HANDLE KeyHandle,
    _Out_ PHASH2048_CTX Hash2048Ctx)
{
    ULONG ReturnLength;
    ULONG Entropy, FullEntropy = 0;
    NTSTATUS Status;
    PVOID Buffer;
    ULONG BufferSize;
    ULONG i;
    UNICODE_STRING ValueName;

    // Allocate a buffer
    BufferSize = 8192;
    Buffer = ExAllocatePoolWithTag(PagedPool, BufferSize, 'pEsK');
    if (Buffer == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    //
    for (i = 0; i < _countof(SysInfoEntries); i++)
    {
        /* Query the information */
        Status = ZwQuerySystemInformation(SysInfoEntries[i].InformationClass,
                                          Buffer,
                                          BufferSize,
                                          &ReturnLength);
        if (!NT_SUCCESS(Status))
        {
            continue;
        }

        /* Try to figure out the entropy */
        RtlInitUnicodeString(&ValueName, SysInfoEntries[i].ClassName);
        Status = EstimateEntropyFromRegistry(KeyHandle,
                                             &ValueName,
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

        /* Hash the data */
        HASH2048_Update(Hash2048Ctx, Buffer, ReturnLength);
    }

    /* Return how much entropy we estimated */
    return FullEntropy;
}

NTSTATUS
NTAPI
KsecGatherBootEntropy(
    _Out_ PHASH2048 Hash2048
    )
{
    static UNICODE_STRING KeyName = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\SOFTWARE\\ReactOS\\Cryptography\\RNG");
    HASH2048_CTX Hash2048Ctx;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    HANDLE KeyHandle;

    HASH2048_Init(&Hash2048Ctx);

    InitializeObjectAttributes(&ObjectAttributes,
                               &KeyName,
                               OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);
    Status = ZwOpenKey(&KeyHandle, KEY_QUERY_VALUE, &ObjectAttributes);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    Status = KsecHashSystemInformation(KeyHandle, &Hash2048Ctx);

    HASH2048_Finalize(&Hash2048Ctx, Hash2048);

    return Status;
}

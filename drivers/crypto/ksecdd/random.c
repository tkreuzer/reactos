/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Drivers
 * PURPOSE:         Kernel Security Support Provider Interface Driver
 *
 * PROGRAMMERS:     Timo Kreuzer (timo.kreuzer@reactos.org)
 */

/* INCLUDES *******************************************************************/

#include "ksecdd.h"
#include "entropy.h"

#define NDEBUG
#include <debug.h>


/* GLOBALS ********************************************************************/

FAST_MUTEX KsecPRNGLock;

static ULONG KsecRandomSeed = 0x62b409a1;
HASHKEY HashKey;
BOOLEAN KsecPRNGInitialized = FALSE;
extern BOOLEAN KsecEntropyInitialized;

/* FUNCTIONS ******************************************************************/

NTSTATUS
NTAPI
KsecInitializePRNG(VOID)
{
    NTSTATUS Status;

    // TODO: Acquire a lock
    
    __debugbreak();
    Status = KsecGatherBootEntropy(&HashKey);
    if (NT_SUCCESS(Status))
    {
        KsecPRNGInitialized = TRUE;
    }

    // TODO: Initialize the VMPC-R context

    // TODO: Release the lock

    return Status;
}

NTSTATUS
NTAPI
KsecGenRandom(
    PVOID Buffer,
    SIZE_T Length)
{
    LARGE_INTEGER TickCount;
    ULONG i, RandomValue;
    PULONG P;

    /* Acquire the lock */
    ExAcquireFastMutex(&KsecPRNGLock);

    /* Check if we are initialized */
    if (!KsecPRNGInitialized)
    {
        KsecInitializePRNG();
    }

    // MS: gather entropy + hash into 4 SHA1s + use that as RC4 key + rc4 the buffer
    // RC4 key is max 256 bytes, use them all?
    // MD5 is fast and uniformly distributed, so it's fine to use.

    /// @todo FIXME should use entropy data and run SHA-1 over it

    /* Try to generate a more random seed */
    KeQueryTickCount(&TickCount);
    KsecRandomSeed ^= _rotl(TickCount.LowPart, (KsecRandomSeed % 23));

    P = Buffer;
    for (i = 0; i < Length / sizeof(ULONG); i++)
    {
        P[i] = RtlRandomEx(&KsecRandomSeed);
    }

    Length &= (sizeof(ULONG) - 1);
    if (Length > 0)
    {
        RandomValue = RtlRandomEx(&KsecRandomSeed);
        RtlCopyMemory(&P[i], &RandomValue, Length);
    }

    // Release the lock
    ExReleaseFastMutex(&KsecPRNGLock);

    return STATUS_SUCCESS;
}

VOID
NTAPI
KsecReadMachineSpecificCounters(
    _Out_ PKSEC_MACHINE_SPECIFIC_COUNTERS MachineSpecificCounters);

/*!
 *  \see http://blogs.msdn.com/b/michael_howard/archive/2005/01/14/353379.aspx
 * -> https://web.archive.org/web/20180929235240/https://blogs.msdn.microsoft.com/michael_howard/2005/01/14/cryptographically-secure-random-number-on-windows-without-using-cryptoapi/
 */
NTSTATUS
NTAPI
KsecGatherEntropyData(
    PKSEC_ENTROPY_DATA EntropyData) // allocate from a lookaside list?
{
    MD4_CTX Md4Context;
    PTEB Teb;
    PPEB Peb;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PWSTR Environment, String;
    ULONG ReturnLength;
    NTSTATUS Status;

    /* Query some generic values */
    EntropyData->CurrentProcessId = PsGetCurrentProcessId();
    EntropyData->CurrentThreadId = PsGetCurrentThreadId();
    KeQueryTickCount(&EntropyData->TickCount);
    KeQuerySystemTime(&EntropyData->SystemTime);
    EntropyData->PerformanceCounter = KeQueryPerformanceCounter(
                                            &EntropyData->PerformanceFrequency);

    /* Check if we have a TEB/PEB for the process environment */
    Teb = PsGetCurrentThread()->Tcb.Teb;
    if (Teb != NULL)
    {
        /* Initialize the MD4 context */
        MD4Init(&Md4Context);
        _SEH2_TRY
        {
            /* Probe the TEB pointer and capture the PEB pointer */
            ProbeForRead(Teb, sizeof(*Teb), _alignof(TEB));
            Peb = Teb->ProcessEnvironmentBlock;

            /* Probe the PEB pointer and capture the process parameters pointer */
            ProbeForRead(Peb, sizeof(*Peb), _alignof(PEB));
            ProcessParameters = Peb->ProcessParameters;

            /* Probe the process parameters and capture the environment pointer */
            ProbeForRead(ProcessParameters,
                         sizeof(*ProcessParameters)
                         , _alignof(RTL_USER_PROCESS_PARAMETERS));
            Environment = ProcessParameters->Environment;

            /* Get the end of the environment */
            String = Environment;
            while (*String)
            {
                String += wcslen(String) + 1;
            }

            /* Update the MD4 context from the environment data */
            MD4Update(&Md4Context,
                      (PUCHAR)Environment,
                      (ULONG)((PUCHAR)String - (PUCHAR)Environment));
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            /* Simply ignore the exception */
        }
        _SEH2_END;

        /* Finalize and copy the MD4 hash */
        MD4Final(&Md4Context);
        RtlCopyMemory(&EntropyData->EnvironmentHash, Md4Context.digest, 16);
    }

    /* Read some machine specific hardware counters */
    KsecReadMachineSpecificCounters(&EntropyData->MachineSpecificCounters);

    /* Query processor performance information */
    Status = ZwQuerySystemInformation(SystemProcessorPerformanceInformation,
                                      &EntropyData->SystemProcessorPerformanceInformation,
                                      sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION),
                                      &ReturnLength);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Query system performance information */
    Status = ZwQuerySystemInformation(SystemPerformanceInformation,
                                      &EntropyData->SystemPerformanceInformation,
                                      sizeof(SYSTEM_PERFORMANCE_INFORMATION),
                                      &ReturnLength);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Query exception information */
    Status = ZwQuerySystemInformation(SystemExceptionInformation,
                                      &EntropyData->SystemExceptionInformation,
                                      sizeof(SYSTEM_EXCEPTION_INFORMATION),
                                      &ReturnLength);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Query lookaside information */
    Status = ZwQuerySystemInformation(SystemLookasideInformation,
                                      &EntropyData->SystemLookasideInformation,
                                      sizeof(SYSTEM_LOOKASIDE_INFORMATION),
                                      &ReturnLength);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Query interrupt information */
    Status = ZwQuerySystemInformation(SystemInterruptInformation,
                                      &EntropyData->SystemInterruptInformation,
                                      sizeof(SYSTEM_INTERRUPT_INFORMATION),
                                      &ReturnLength);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Query process information */
    Status = ZwQuerySystemInformation(SystemProcessInformation,
                                      &EntropyData->SystemProcessInformation,
                                      sizeof(SYSTEM_PROCESS_INFORMATION),
                                      &ReturnLength); // this is actually dynamic
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    // should we hash it here straight away (into 16 MD5s?)
    return STATUS_SUCCESS;
}

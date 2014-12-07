
#pragma once

#include "ntoskrnl.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define DISPATCH_LEVEL 2

typedef UCHAR KIRQL, *PKIRQL;
typedef CCHAR KPROCESSOR_MODE;
typedef LONG KPRIORITY, *PKPRIORITY;
typedef ULONG_PTR KSPIN_LOCK, *PKSPIN_LOCK;

typedef enum _KINTERRUPT_MODE
{
    LevelSensitive,
    Latched
} KINTERRUPT_MODE;

// ntosp.h
typedef enum _KINTERRUPT_POLARITY
{
    InterruptPolarityUnknown,
    InterruptActiveHigh,
    InterruptRisingEdge = InterruptActiveHigh,
    InterruptActiveLow,
    InterruptFallingEdge = InterruptActiveLow,
#if (NTDDI_VERSION >= NTDDI_WIN8)
    InterruptActiveBoth,
#endif
#if (NTDDI_VERSION >= NTDDI_WINBLUE)
    InterruptActiveBothTriggerLow = InterruptActiveBoth,
    InterruptActiveBothTriggerHigh,
#endif
} KINTERRUPT_POLARITY, *PKINTERRUPT_POLARITY;

typedef enum _KPROFILE_SOURCE
{
    ProfileTime,
    ProfileAlignmentFixup,
    ProfileTotalIssues,
    ProfilePipelineDry,
    ProfileLoadInstructions,
    ProfilePipelineFrozen,
    ProfileBranchInstructions,
    ProfileTotalNonissues,
    ProfileDcacheMisses,
    ProfileIcacheMisses,
    ProfileCacheMisses,
    ProfileBranchMispredictions,
    ProfileStoreInstructions,
    ProfileFpInstructions,
    ProfileIntegerInstructions,
    Profile2Issue,
    Profile3Issue,
    Profile4Issue,
    ProfileSpecialInstructions,
    ProfileTotalCycles,
    ProfileIcacheIssues,
    ProfileDcacheAccesses,
    ProfileMemoryBarrierCycles,
    ProfileLoadLinkedIssues,
    ProfileMaximum
} KPROFILE_SOURCE;


typedef struct _KTHREAD *PRKTHREAD;
typedef struct _KINTERRUPT *PKINTERRUPT;
typedef struct _KTHREAD *PKTHREAD;
typedef struct _KEVENT *PKEVENT;
typedef struct _CONTEXT *PCONTEXT;
typedef struct _KDPC *PKDPC;

typedef enum _MODE
{
    KernelMode,
    UserMode,
    MaximumMode
} MODE;

#define EXCEPTION_MAXIMUM_PARAMETERS 15
typedef struct _EXCEPTION_RECORD
{
    NTSTATUS ExceptionCode;
    ULONG ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    PVOID ExceptionAddress;
    ULONG NumberParameters;
    ULONG_PTR ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD, *PEXCEPTION_RECORD;

// Simplified structure
typedef struct _DISPATCHER_HEADER
{
    volatile LONG Lock;
    LONG SignalState;
    LIST_ENTRY WaitListHead;
} DISPATCHER_HEADER, *PDISPATCHER_HEADER;

typedef struct _KEVENT
{
    DISPATCHER_HEADER Header;
} KEVENT, *PKEVENT, *PRKEVENT;

typedef struct _FAST_MUTEX
{
    LONG Count;
    PVOID Owner;
    ULONG Contention;
    KEVENT Event;
    ULONG OldIrql;
} FAST_MUTEX, *PFAST_MUTEX,
  KGUARDED_MUTEX, *PKGUARDED_MUTEX;

typedef
_IRQL_requires_same_
_Function_class_(KSTART_ROUTINE)
VOID
NTAPI
KSTART_ROUTINE (
    _In_ PVOID StartContext);
typedef KSTART_ROUTINE *PKSTART_ROUTINE;

typedef
_Function_class_(KSERVICE_ROUTINE)
_IRQL_requires_(HIGH_LEVEL)
_IRQL_requires_same_
BOOLEAN
NTAPI
KSERVICE_ROUTINE (
    _In_ struct _KINTERRUPT *Interrupt,
    _In_opt_ PVOID ServiceContext);
typedef KSERVICE_ROUTINE *PKSERVICE_ROUTINE;

typedef
_Function_class_(KMESSAGE_SERVICE_ROUTINE)
_IRQL_requires_same_
BOOLEAN
NTAPI
KMESSAGE_SERVICE_ROUTINE (
    _In_ struct _KINTERRUPT *Interrupt,
    _In_ PVOID ServiceContext,
    _In_ ULONG MessageID);
typedef KMESSAGE_SERVICE_ROUTINE *PKMESSAGE_SERVICE_ROUTINE;

_IRQL_requires_max_(DISPATCH_LEVEL)
FORCEINLINE
KPROCESSOR_MODE
NTAPI
KeGetPreviousMode (
    VOID)
{
    /* Return the current thread's previous mode */
    __debugbreak();
    return (KPROCESSOR_MODE)0;// KeGetCurrentThread()->PreviousMode;
}

#if defined(_M_IX86)
FORCEINLINE
PKTHREAD
NTAPI
KeGetCurrentThread (
    VOID)
{
    return (PKTHREAD)__readfsdword(0x124);
}
#elif defined(_M_AMD64)
FORCEINLINE
PKTHREAD
KeGetCurrentThread (
    VOID
    )
{
    return (PKTHREAD)__readgsqword(0x188);
}
#endif // _M_IX86

#ifdef __cplusplus
};
#endif // __cplusplus

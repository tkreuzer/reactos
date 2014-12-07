
#pragma once

#include "Kep.hpp"

typedef enum _KBUGCHECK_BUFFER_DUMP_STATE {
    BufferEmpty,
    BufferInserted,
    BufferStarted,
    BufferFinished,
    BufferIncomplete
} KBUGCHECK_BUFFER_DUMP_STATE;

typedef
_Function_class_(KBUGCHECK_CALLBACK_ROUTINE)
_IRQL_requires_same_
VOID
KBUGCHECK_CALLBACK_ROUTINE (
    IN PVOID Buffer,
    IN ULONG Length
    );
typedef KBUGCHECK_CALLBACK_ROUTINE *PKBUGCHECK_CALLBACK_ROUTINE;

typedef struct _KBUGCHECK_CALLBACK_RECORD {
    LIST_ENTRY Entry;
    PKBUGCHECK_CALLBACK_ROUTINE CallbackRoutine;
    _Field_size_bytes_opt_(Length) PVOID Buffer;
    ULONG Length;
    PUCHAR Component;
    ULONG_PTR Checksum;
    UCHAR State;
} KBUGCHECK_CALLBACK_RECORD, *PKBUGCHECK_CALLBACK_RECORD;

#define KeInitializeCallbackRecord(CallbackRecord) \
    (CallbackRecord)->State = BufferEmpty


typedef enum _KBUGCHECK_CALLBACK_REASON {
    KbCallbackInvalid,
    KbCallbackReserved1,
    KbCallbackSecondaryDumpData,
    KbCallbackDumpIo,
    KbCallbackAddPages,
    KbCallbackSecondaryMultiPartDumpData,
    KbCallbackRemovePages
} KBUGCHECK_CALLBACK_REASON;

typedef
_Function_class_(KBUGCHECK_REASON_CALLBACK_ROUTINE)
_IRQL_requires_same_
VOID
KBUGCHECK_REASON_CALLBACK_ROUTINE (
    _In_ KBUGCHECK_CALLBACK_REASON Reason,
    _In_ struct _KBUGCHECK_REASON_CALLBACK_RECORD* Record,
    _Inout_ PVOID ReasonSpecificData,
    _In_ ULONG ReasonSpecificDataLength
    );
typedef KBUGCHECK_REASON_CALLBACK_ROUTINE *PKBUGCHECK_REASON_CALLBACK_ROUTINE;

typedef struct _KBUGCHECK_REASON_CALLBACK_RECORD {
    LIST_ENTRY Entry;
    PKBUGCHECK_REASON_CALLBACK_ROUTINE CallbackRoutine;
    PUCHAR Component;
    ULONG_PTR Checksum;
    KBUGCHECK_CALLBACK_REASON Reason;
    UCHAR State;
} KBUGCHECK_REASON_CALLBACK_RECORD, *PKBUGCHECK_REASON_CALLBACK_RECORD;

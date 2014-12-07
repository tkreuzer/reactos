
#include "Rtl.hpp"

extern "C" {

#define HASH_STRING_ALGORITHM_DEFAULT   (0)
#define HASH_STRING_ALGORITHM_X65599    (1)
#define HASH_STRING_ALGORITHM_INVALID   (0xffffffff)

// wdm.h
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSTATUS
NTAPI
RtlHashUnicodeString (
    _In_ PCUNICODE_STRING String,
    _In_ BOOLEAN CaseInSensitive,
    _In_ ULONG HashAlgorithm,
    _Out_ PULONG HashValue)
{
    __debugbreak();
    return STATUS_NOT_IMPLEMENTED;
}

} // extern "C"

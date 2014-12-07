
#include "Rtl.hpp"

extern "C" {

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlLargeIntegerAdd (
    _In_ LARGE_INTEGER Addend1,
    _In_ LARGE_INTEGER Addend2
    )
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlLargeIntegerSubtract (
    _In_ LARGE_INTEGER Minuend,
    _In_ LARGE_INTEGER Subtrahend)
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlLargeIntegerDivide (
    _In_ LARGE_INTEGER Dividend,
    _In_ LARGE_INTEGER Divisor,
    _Out_opt_ PLARGE_INTEGER Remainder)
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlLargeIntegerArithmeticShift (
    _In_ LARGE_INTEGER LargeInteger,
    _In_ CCHAR ShiftCount
    )
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlLargeIntegerNegate (
    _In_ LARGE_INTEGER Subtrahend
    )
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlLargeIntegerShiftLeft (
    _In_ LARGE_INTEGER LargeInteger,
    _In_ CCHAR ShiftCount
    )
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlLargeIntegerShiftRight (
    _In_ LARGE_INTEGER LargeInteger,
    _In_ CCHAR ShiftCount
    )
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlEnlargedIntegerMultiply (
    _In_ LONG Multiplicand,
    _In_ LONG Multiplier
    )
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlEnlargedUnsignedMultiply (
    _In_ ULONG Multiplicand,
    _In_ ULONG Multiplier
    )
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
ULONG
NTAPI
RtlEnlargedUnsignedDivide (
    _In_ ULARGE_INTEGER Dividend,
    _In_ ULONG Divisor,
    _Out_opt_ PULONG Remainder
    )
{
    __debugbreak();
    return 0;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlExtendedIntegerMultiply (
    _In_ LARGE_INTEGER Multiplicand,
    _In_ LONG Multiplier
    )
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlExtendedLargeIntegerDivide (
    _In_ LARGE_INTEGER Dividend,
    _In_ ULONG Divisor,
    _Out_opt_ PULONG Remainder)
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlExtendedMagicDivide (
    _In_ LARGE_INTEGER Dividend,
    _In_ LARGE_INTEGER MagicDivisor,
    _In_ CCHAR ShiftCount)
{
    LARGE_INTEGER result = {{0}};
    __debugbreak();
    return result;
}


} // extern "C"

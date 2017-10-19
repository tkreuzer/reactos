
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
    LARGE_INTEGER sum;

    sum.QuadPart = Addend1.QuadPart + Addend2.QuadPart;
    return sum;
}

DECLSPEC_DEPRECATED_DDK
__drv_preferredFunction("compiler support for 64 bit", "Obsolete")
LARGE_INTEGER
NTAPI
RtlLargeIntegerSubtract (
    _In_ LARGE_INTEGER Minuend,
    _In_ LARGE_INTEGER Subtrahend)
{
    LARGE_INTEGER difference;

    difference.QuadPart = Minuend.QuadPart - Subtrahend.QuadPart;
    return difference;
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
    LARGE_INTEGER quotient;

    quotient.QuadPart = Dividend.QuadPart / Divisor.QuadPart;
    if (ARGUMENT_PRESENT(Remainder))
    {
        Remainder->QuadPart = Dividend.QuadPart % Divisor.QuadPart;
    }

    return quotient;
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
    LARGE_INTEGER result;

    result.QuadPart = LargeInteger.QuadPart >> ShiftCount;
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
    LARGE_INTEGER result;

    result.QuadPart = -Subtrahend.QuadPart;
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
    LARGE_INTEGER result;

    result.QuadPart = LargeInteger.QuadPart << ShiftCount;
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
    LARGE_INTEGER result;

    result.QuadPart = (ULONG64)LargeInteger.QuadPart >> ShiftCount;
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
    LARGE_INTEGER product;

    product.QuadPart = (LONG64)Multiplicand * (LONG64)Multiplier;
    return product;
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
    LARGE_INTEGER product;

    product.QuadPart = (ULONG64)Multiplicand * (ULONG64)Multiplier;
    return product;
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
    ULONG quotient;

    quotient = (ULONG)(Dividend.QuadPart / Divisor);
    if (ARGUMENT_PRESENT(Remainder))
    {
        *Remainder = (ULONG)(Dividend.QuadPart % Divisor);
    }

    return quotient;
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
    LARGE_INTEGER product;

    product.QuadPart = Multiplicand.QuadPart * Multiplier;
    return product;
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
    LARGE_INTEGER quotient;

    quotient.QuadPart = (ULONG64)Dividend.QuadPart / Divisor;
    if (ARGUMENT_PRESENT(Remainder))
    {
        *Remainder = (ULONG)((ULONG64)Dividend.QuadPart % Divisor);
    }

    return quotient;
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
    LARGE_INTEGER quotient;

    if (Dividend.QuadPart >= 0)
    {
        quotient.QuadPart = UnsignedMultiplyHigh(Dividend.QuadPart,
                                                 (ULONG64)MagicDivisor.QuadPart);

    }
    else
    {
        quotient.QuadPart = UnsignedMultiplyHigh(-Dividend.QuadPart,
                                                 (ULONG64)MagicDivisor.QuadPart);
    }

    quotient.QuadPart = (ULONG64)Quotient.QuadPart >> ShiftCount;
    if (Dividend.QuadPart < 0)
    {
        quotient.QuadPart = - Quotient.QuadPart;
    }

    return quotient;
}

} // extern "C"

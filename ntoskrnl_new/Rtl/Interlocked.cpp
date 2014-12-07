
#include "Rtl.hpp"

extern "C" {

#undef InterlockedDecrement
#undef InterlockedIncrement
#undef InterlockedExchange
#undef InterlockedExchangeAdd
#undef InterlockedCompareExchange

LONG
FASTCALL
InterlockedDecrement (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend)
{
    __debugbreak();
    return 0;
}

LONG
FASTCALL
InterlockedIncrement (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend)
{
    __debugbreak();
    return 0;
}

LONG
FASTCALL
InterlockedExchange (
    _Inout_ _Interlocked_operand_ LONG volatile *Target,
    _In_ LONG Value)
{
    __debugbreak();
    return 0;
}

LONG
FASTCALL
InterlockedExchangeAdd (
    _Inout_ _Interlocked_operand_ LONG volatile *Addend,
    _In_ LONG Value)
{
    __debugbreak();
    return 0;
}

LONG
FASTCALL
InterlockedCompareExchange (
    _Inout_ _Interlocked_operand_ LONG volatile * Destination,
    _In_ LONG ExChange,
    _In_ LONG Comperand)
{
    __debugbreak();
    return 0;
}

} // extern "C"

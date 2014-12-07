
#include "Exp.hpp"

extern "C" {

VOID
NTAPI
ExLocalTimeToSystemTime (
    _In_ PLARGE_INTEGER LocalTime,
    _Out_ PLARGE_INTEGER SystemTime)
{
    __debugbreak();
}

VOID
NTAPI
ExSystemTimeToLocalTime (
    _In_ PLARGE_INTEGER SystemTime,
    _Out_ PLARGE_INTEGER LocalTime)
{
    __debugbreak();
}

}; // extern "C"

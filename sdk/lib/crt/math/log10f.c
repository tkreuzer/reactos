
#include <math.h>

#if defined(_MSC_VER) && defined(_M_AMD64)
#pragma function(log10f)
#endif

_Check_return_
float
__cdecl
log10f(
    _In_ float x)
{
    return (float)log10((double)x);
}

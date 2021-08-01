
#include <math.h>

#if defined(_MSC_VER) && defined(_M_AMD64)
#pragma function(expf)
#endif

_Check_return_
float
__cdecl
expf(
    _In_ float x)
{
    return (float)exp((double)x);
}

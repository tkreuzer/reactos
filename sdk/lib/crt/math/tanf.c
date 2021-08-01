
#include <math.h>

#if defined(_MSC_VER) && defined(_M_AMD64)
#pragma function(tanf)
#endif

_Check_return_
float
__cdecl
tanf(
    _In_ float x)
{
    return (float)tan((double)x);
}


#include <math.h>

#if defined(_MSC_VER) && defined(_M_AMD64)
#pragma function(asinf)
#endif

_Check_return_
float
__cdecl
asinf(
    _In_ float x)
{
    return (float)asin((double)x);
}

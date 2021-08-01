
#include <math.h>

#if defined(_MSC_VER) && defined(_M_AMD64)
#pragma function(atanf)
#endif

_Check_return_
float
__cdecl
atanf(
    _In_ float x)
{
    return (float)atan((double)x);
}

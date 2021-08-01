
#include <math.h>

#if defined(_MSC_VER) && defined(_M_AMD64)
#pragma function(acosf)
#endif

_Check_return_
float
__cdecl
acosf(
    _In_ float x)
{
    return (float)acos((double)x);
}

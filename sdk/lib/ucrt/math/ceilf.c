
#include <math.h>

#ifdef _MSC_VER
#pragma function(ceilf)
#endif

// Instantiate the inline version of ceilf():
extern
float
__cdecl
ceilf(
    _In_ float x);

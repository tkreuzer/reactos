
#include <crtdefs.h>

void _set_statfp(uintptr_t x)
{
    unsigned int csr = _mm_getcsr();
    _mm_setcsr(x & 0x3F | csr);
}

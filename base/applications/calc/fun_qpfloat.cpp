
#include <intrin.h>
#include <__float128.h>

#pragma warning(disable:4190) // 'identifier1' has C-linkage specified, but returns UDT 'identifier2' which is incompatible with C

inline __float128 acos(__float128 x) throw() { return __float128::ACos(x); }
inline __float128 atan(__float128 x) throw() { return __float128::ATan(x); }
inline __float128 asin(__float128 x) throw() { return __float128::ASin(x); }

inline __float128 asinh(__float128 x) throw() { return 0.; }
inline __float128 acosh(__float128 x) throw() { return 0.; }
inline __float128 atanh(__float128 x) throw() { return 0.; }
inline __float128 cosh(__float128 x) throw() { return 0.; }
inline __float128 sinh(__float128 x) throw() { return 0.; }
inline __float128 tanh(__float128 x) throw() { return 0.; }
inline __float128 modf(__float128 x, double *py) throw() { return 0.; }

inline int _isnan(__float128 x) throw() { return x.IsNaN() ? 1 : 0;  }

extern "C"
{
#include "fun_ieee.c"
}

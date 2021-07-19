
#include <math.h>
#include <float.h>

// move to crt math.h
// Values for use as arguments to the _fperrraise function
#define _FE_INVALID   0x01
#define _FE_DIVBYZERO 0x04
#define _FE_OVERFLOW  0x08
#define _FE_UNDERFLOW 0x10
#define _FE_INEXACT   0x20
void __cdecl _fperrraise(_In_ int _Except);

double
log1p_(double x)
{
    int fp_class;
    union
    {
        double dbl;
        unsigned __int64 ui64;
    } u;

    fp_class = _fpclass(x);
    switch (fp_class)
    {
        case _FPCLASS_PZ:
        case _FPCLASS_NZ:
        case _FPCLASS_QNAN:
        case _FPCLASS_PINF:
            return x;
    }

    if (x <= -1.0)
    {
        if (x == -1.0)
        {
            _fperrraise(_FE_DIVBYZERO);
            u.dbl = x;
            u.ui64 |= 0x7FF0000000000000ULL;
            return u.dbl;
        }
        else
        {
            _fperrraise(_FE_INVALID);
            u.dbl = x;
            u.ui64 |= 0x7FF8000000000000ULL; // QNaN
            return u.dbl;
        }
    }

    return log(x + 1.0) - (x + 1.0 - 1.0 - x) / (x + 1.0);
}

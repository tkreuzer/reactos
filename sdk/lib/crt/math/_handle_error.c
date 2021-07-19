
#include <math.h>

double _handle_error(
    char* fname,
    int opcode,
    unsigned long long value,
    int type,
    int flags,
    int error,
    double arg1,
    double arg2,
    int nargs)
{
    return 0.;
}

float _handle_errorf(
    char *fname,
    int opcode,
    unsigned long long value,
    int type,
    int flags,
    int error,
    float arg1,
    float arg2,
    int nargs)
{
    return 0.;
}

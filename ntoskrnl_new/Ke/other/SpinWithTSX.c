BOOLEAN HasTsx;
BOOLEAN HltAbortsTsx;
#include <tsx.h>

VOID
DoHalt (
    VOID)
{
    if (HltAbortsTsx)
    {
    }
    else
    {
        __halt();
    }
}

ULONG_PTR
SpinOnSpinLock (
    volatile ULONG_PTR *Lock,
    ULONG_PTR Mask)
{
    ULONG_PTR value;

    if (HasTsx)
    {
        while (true)
        {
            /* Begin transaction */
            unsigned status = _xbegin();
            if (status == _XBEGIN_STARTED)
            {
                /* Read the lock value */
                value = *Lock;
                if ((value & Mask) == 0)
                {
                    _xend();
                    return value;
                }

                /* Lock is held, wait for an abort or interrupt */
                __halt();
            }

            /* Transaction was aborted, that means the lock value changed,
               so start over */
        }
    }
    else
    {
    }

    return 0;
}



#include <ntoskrnl.h>
#include "../Ke_internal.h"

ULONG Amd64ProfileDummy();
ULONG Amd64ProfileFunction(void);

VOID
NTAPI
Amd64DoProfiling(VOID)
{
    VidInitialize();

    ULONG a, b;
    VidPrint("value1 = %ld - %ld = %ld\n", (a = Amd64ProfileFunction()), (b = Amd64ProfileDummy()), (a-b));
    VidPrint("value2 = %ld - %ld = %ld\n", (a = Amd64ProfileFunction()), (b = Amd64ProfileDummy()), (a-b));
    VidPrint("value3 = %ld - %ld = %ld\n", (a = Amd64ProfileFunction()), (b = Amd64ProfileDummy()), (a-b));
    VidPrint("value4 = %ld - %ld = %ld\n", (a = Amd64ProfileFunction()), (b = Amd64ProfileDummy()), (a-b));
    VidPrint("value5 = %ld - %ld = %ld\n", (a = Amd64ProfileFunction()), (b = Amd64ProfileDummy()), (a-b));
    for(;;);
}


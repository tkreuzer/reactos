
#include <sal.h>
#undef _In_
#undef _Out_
#undef _Inout_
#undef _In_reads_
#define _In_reads_(Count) _In_
#undef _Reserved_
#define _Reserved_ _In_
#undef _Out_opt_
#define _Out_opt_ _Out_

#include <ntndk.h>

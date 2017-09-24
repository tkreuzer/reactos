

#define _EXPORT_LIST_FILE <./exportlist.h>
#define _ENTRY_POINT KiSystemStartup
#define _DLL_NAME "ntoskrnl.exe"
#define PeHeader NtoskrnlPeHeader
#define Fixup_PeHeader Fixup_NtoskrnlPeHeader
#define _ENABLE_IMPORT_TRACE 1

#include <genpeheader.h>


#ifndef _MSTSC_PCH_
#define _MSTSC_PCH_

#include <stdarg.h>

#define WIN32_NO_STATUS
#define _INC_WINDOWS
#define COM_NO_WINDOWS_H
#include <windef.h>
#include <winbase.h>
#include <wincrypt.h>

#include "rdesktop.h"

#define RDP_LOGON_NORMAL (RDP_INFO_MOUSE | RDP_INFO_DISABLECTRLALTDEL | RDP_INFO_UNICODE | RDP_INFO_MAXIMIZESHELL)

#define IS_PERSISTENT(id) (id < 8 && g_pstcache_fd[id] > 0)

#endif /* _MSTSC_PCH_ */

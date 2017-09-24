
#include "PageTables.hpp"

namespace Mm {

struct PTE_DATA
{
    USHORT SoftProtection : 5;
    USHORT NoExecute : 1;
    USHORT Valid : 1;
    USHORT Write : 1;
    USHORT Owner : 1;
    USHORT WriteCombining : 1;
    USHORT CacheDisable : 1;
    USHORT Accessed : 1;
    USHORT Dirty : 1;
    USHORT LargePage : 1;
    USHORT Global : 1;
    USHORT CopyOnWrite : 1;
};

const HARDWARE_PTE ProtectToPte[32] =
{
//         W C         C         N
//   V W O C D A D L G W         X
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // MM_NOACCESS
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // MM_READONLY
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_EXECUTE
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_EXECUTE_READ
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, // MM_READWRITE
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1}, // MM_WRITECOPY
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_EXECUTE_READWRITE
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0}, // MM_EXECUTE_WRITECOPY

    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,1}, // MM_NOCACHE | MM_NOACCESS
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1}, // MM_NOCACHE | MM_READONLY
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0}, // MM_NOCACHE | MM_EXECUTE
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0}, // MM_NOCACHE | MM_EXECUTE_READ
    {1,1,0,0,1,0,0,0,0,0,0,0,0,0,1}, // MM_NOCACHE | MM_READWRITE
    {1,0,0,0,1,0,0,0,0,1,0,0,0,0,1}, // MM_NOCACHE | MM_WRITECOPY
    {1,1,0,0,1,0,0,0,0,0,0,0,0,0,0}, // MM_NOCACHE | MM_EXECUTE_READWRITE
    {1,0,0,0,1,0,0,0,0,1,0,0,0,0,0}, // MM_NOCACHE | MM_EXECUTE_WRITECOPY

    {0,0,0,0,0,0,0,0,0,0,0,0,0,MM_NOACCESS,0}, // MM_DECOMMIT | MM_NOACCESS
    {0,0,0,0,0,0,0,0,0,0,0,0,0,MM_READONLY,0}, // MM_DECOMMIT | MM_READONLY
    {0,0,0,0,0,0,0,0,0,0,0,0,0,MM_EXECUTE,0}, // MM_DECOMMIT | MM_EXECUTE
    {0,0,0,0,0,0,0,0,0,0,0,0,0,MM_EXECUTE_READ,0}, // MM_DECOMMIT | MM_EXECUTE_READ
    {0,1,0,0,0,0,0,0,0,0,0,0,0,MM_READWRITE,0}, // MM_DECOMMIT | MM_READWRITE
    {0,0,0,0,0,0,0,0,0,1,0,0,0,MM_WRITECOPY,0}, // MM_DECOMMIT | MM_WRITECOPY
    {0,1,0,0,0,0,0,0,0,0,0,0,0,MM_EXECUTE_READWRITE,0}, // MM_DECOMMIT | MM_EXECUTE_READWRITE
    {0,0,0,0,0,0,0,0,0,1,0,0,0,MM_EXECUTE_WRITECOPY,0}, // MM_DECOMMIT | MM_EXECUTE_WRITECOPY

    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,1}, // MM_WRITECOMBINE | MM_NOACCESS
    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1}, // MM_WRITECOMBINE | MM_READONLY
    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0}, // MM_WRITECOMBINE | MM_EXECUTE
    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0}, // MM_WRITECOMBINE | MM_EXECUTE_READ
    {1,1,0,1,0,0,0,0,0,0,0,0,0,0,1}, // MM_WRITECOMBINE | MM_READWRITE
    {1,0,0,1,0,0,0,0,0,1,0,0,0,0,1}, // MM_WRITECOMBINE | MM_WRITECOPY
    {1,1,0,1,0,0,0,0,0,0,0,0,0,0,0}, // MM_WRITECOMBINE | MM_EXECUTE_READWRITE
    {1,0,0,1,0,0,0,0,0,1,0,0,0,0,0}, // MM_WRITECOMBINE | MM_EXECUTE_WRITECOPY

};

const HARDWARE_PTE ProtectToPteBase[8] =
{
//         W C         C         N
//   V W O C D A D L G W         X
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // MM_NOACCESS
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // MM_READONLY
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_EXECUTE
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_EXECUTE_READ
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, // MM_READWRITE
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1}, // MM_WRITECOPY
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_EXECUTE_READWRITE
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0}, // MM_EXECUTE_WRITECOPY
};

const HARDWARE_PTE ProtectToPteFlags[32] =
{
//         W C         C         N
//   V W O C D A D L G W         X
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // -
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0}, // MM_NOCACHE
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_DECOMMIT
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}, // MM_WRITECOMBINE
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}, // MM_GLOBAL
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}, // MM_GLOBAL|MM_NOCACHE
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}, // MM_GLOBAL|MM_DECOMMIT
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}, // MM_GLOBAL|MM_WRITECOMBINE

    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_USER
    {0,0,1,0,1,0,0,0,0,0,0,0,0,0,0}, // MM_USER|MM_NOCACHE
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}, // MM_USER|MM_DECOMMIT
    {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0}, // MM_USER|MM_WRITECOMBINE
    {0,0,1,0,0,0,0,0,1,0,0,0,0,0,0}, // MM_USER|MM_GLOBAL
    {0,0,1,0,0,0,0,0,1,0,0,0,0,0,0}, // MM_USER|MM_GLOBAL|MM_NOCACHE
    {0,0,1,0,0,0,0,0,1,0,0,0,0,0,0}, // MM_USER|MM_GLOBAL|MM_DECOMMIT
    {0,0,1,0,0,0,0,0,1,0,0,0,0,0,0}, // MM_USER|MM_GLOBAL|MM_WRITECOMBINE
};

#define ProtectToPteMask(Protect) \
    (*(PULONG64)&ProtectToPteBase[(Protect) & 0x7] | *(PULONG64)&ProtectToPteFlags[((Protect) & 0xF8) >> 3])

    inline
    VOID
    MakeValidPte (
        _In_ PFN_NUMBER PageFrameNumber,
        _In_ ULONG Protect)
    {
        HARDWARE_PTE HardPte = ProtectToPte(Protect);
        NT_ASSERT(!(Protect & MM_LARGEPAGE));
        if (Protect & MM_READWRITE) HardPte.Write = 1;
        if (!(Protect & MM_EXECUTE)) HardPte.NoExecute = 1;
        if (Protect & MM_GLOBAL) HardPte.Global = 1;
        HardPte.PageFrameNumber = PageFrameNumber;
        this->Hard = HardPte;
    }

}; // namespace Mm



#pragma once

#include "Kep.hpp"

typedef struct _KMUTANT
#if 0
{
    DISPATCHER_HEADER Header;
    LIST_ENTRY MutantListEntry;
    struct _KTHREAD *OwnerThread;
    BOOLEAN Abandoned;
    UCHAR ApcDisable;
}
#endif
KMUTANT, *PKMUTANT, *PRKMUTANT, KMUTEX, *PKMUTEX, *PRKMUTEX;

// http://www.brandonfa.lk/win8/win8_devrel_head_x86/windows.web.h
typedef enum _MUTANT_INFORMATION_CLASS
{
    MutantBasicInformation = 0,
    MutantOwnerInformation = 1
} MUTANT_INFORMATION_CLASS;


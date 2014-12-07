
#pragma once

#include "Exp.hpp"

typedef USHORT RTL_ATOM, *PRTL_ATOM;

// "Windows NT/2000 Native API Reference" by Gary Nebbett
// http://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FAtoms%2FATOM_INFORMATION_CLASS.html
typedef enum _ATOM_INFORMATION_CLASS
{
    AtomBasicInformation,
    AtomTableInformation
} ATOM_INFORMATION_CLASS, *PATOM_INFORMATION_CLASS;


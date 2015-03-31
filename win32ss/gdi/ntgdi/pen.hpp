/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           ReactOS win32 subsystem
 * PURPOSE:           PEN class definition
 * PROGRAMER:         Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#pragma once

#include <win32k.h>
#include "brush.hpp"

class PEN : public BRUSH
{

public:

    PEN(
        _In_ FLONG flAttrs,
        _In_ COLORREF crColor,
        _In_ ULONG ulPenStyle,
        _In_ ULONG ulWidth,
        _In_ GDILOOBJTYPE objtype);

    ~PEN(
        VOID);

    UINT
    cjGetObject(
        _In_ UINT cjBuffer,
        _Out_bytecap_(cjBuffer) PVOID pvBuffer) const;


};



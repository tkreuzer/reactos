
#pragma once

#include <win32k.h>

PDC
GetDc(
    _In_ HDC hdc);

VOID
DC_vDeleteDc(
    PDC pdc);


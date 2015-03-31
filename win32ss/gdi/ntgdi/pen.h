#pragma once

/* Internal interface */

#ifndef __cplusplus
typedef BRUSH PEN, *PPEN;
#else
class PEN;
typedef class PEN *PPEN;
#endif // __cplusplus

#define PEN_ShareUnlockPen(ppen) GDIOBJ_vDereferenceObject((POBJ)ppen)

PPEN
FASTCALL
PEN_ShareLockPen(HPEN hpen);

INT
NTAPI
PEN_GetObject(
    _In_ PPEN pPen,
    _In_ INT Count,
    _Out_ PLOGPEN Buffer);

VOID FASTCALL AddPenLinesBounds(PDC,int,POINT *);

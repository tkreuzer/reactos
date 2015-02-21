#pragma once

/* DC hook codes */
#define DCHC_INVALIDVISRGN      0x0001
#define DCHC_DELETEDC           0x0002

#define DCHF_INVALIDATEVISRGN   0x0001
#define DCHF_VALIDATEVISRGN     0x0002

typedef enum
{
    DCE_CACHE_DC,   /* This is a cached DC (allocated by USER) */
    DCE_CLASS_DC,   /* This is a class DC (style CS_CLASSDC) */
    DCE_WINDOW_DC   /* This is a window DC (style CS_OWNDC) */
} DCE_TYPE, *PDCE_TYPE;

typedef struct tagDCE *PDCE;

/* internal DCX flags, see psdk/winuser.h for the rest */
#define DCX_DCEEMPTY        0x00000800
#define DCX_DCEBUSY         0x00001000
#define DCX_DCEDIRTY        0x00002000
#define DCX_LAYEREDWIN      0x00004000
#define DCX_DCPOWNED        0x00008000
#define DCX_NOCLIPCHILDREN  0x00080000
#define DCX_NORECOMPUTE     0x00100000
#define DCX_INDESTROY       0x00400000

CODE_SEG("INIT") NTSTATUS NTAPI InitDCEImpl(VOID);
PDCE NTAPI DceAllocDCE(PWND Window, DCE_TYPE Type);
HWND NTAPI IntWindowFromDC(HDC hDc);
void NTAPI DceFreeDCE(PDCE dce, BOOLEAN Force);
void NTAPI DceEmptyCache(void);
VOID NTAPI DceResetActiveDCEs(PWND Window);
void NTAPI DceFreeClassDCE(PDCE);
HWND NTAPI UserGethWnd(HDC,PWNDOBJ*);
void NTAPI DceFreeWindowDCE(PWND);
void NTAPI DceFreeThreadDCE(PTHREADINFO);
VOID NTAPI DceUpdateVisRgn(PDCE pdce, PWND Window, ULONG Flags);
PDCE NTAPI DceGetDceFromDC(HDC hdc);


#include "RopFunctions.h"

typedef struct
{
    ULONG iFormat;
    PBYTE pvScan0;
    PBYTE pjBase;
    LONG lDelta; /// FIXME: consider merging these 2
    LONG cjAdvanceY;
    POINTL ptOrig;
    BYTE jBpp;
} SURFINFO;

typedef struct
{
    SURFINFO siSrc;
    SURFINFO siDst;
    SURFINFO siPat;
    SURFINFO siMsk;

    ULONG ulWidth;
    ULONG ulHeight;
    ULONG ulPatWidth;
    ULONG ulPatHeight;
    XLATEOBJ *pxlo;
    PFN_XLATE pfnXlate;
    ULONG rop4;
    PFN_DOROP apfnDoRop[2];
    ULONG ulSolidColor;
    LONG dy;
} BLTDATA, *PBLTDATA;

typedef
VOID
(FASTCALL
*PFN_DIBFUNCTION)(PBLTDATA pBltData);

VOID FASTCALL Dib_BitBlt_NOOP(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_SOLIDFILL(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_BLACKNESS(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_WHITENESS(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_PATCOPY(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_NOTPATCOPY(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_DSTINVERT(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_SRCCOPY(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_NOTSRCCOPY(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_SRCERASE(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_NOTSRCERASE(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_PATINVERT(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_SRCINVERT(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_SRCAND(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_MERGEPAINT(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_MERGECOPY(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_SRCPAINT(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt_PATPAINT(PBLTDATA pBltData);
VOID FASTCALL Dib_SrcPatBlt(PBLTDATA pBltData);
VOID FASTCALL Dib_PatPaint(PBLTDATA pBltData);
VOID FASTCALL Dib_SrcPaint(PBLTDATA pBltData);
VOID FASTCALL Dib_BitBlt(PBLTDATA pBltData);

VOID FASTCALL Dib_MaskCopy(PBLTDATA pBltData);
VOID FASTCALL Dib_MaskPatBlt(PBLTDATA pBltData);
VOID FASTCALL Dib_MaskSrcBlt(PBLTDATA pBltData);
VOID FASTCALL Dib_MaskSrcPatBlt(PBLTDATA pBltData);
VOID FASTCALL Dib_MaskPaint(PBLTDATA pBltData);
VOID FASTCALL Dib_MaskPatPaint(PBLTDATA pBltData);
VOID FASTCALL Dib_MaskSrcPaint(PBLTDATA pBltData);
VOID FASTCALL Dib_MaskBlt(PBLTDATA pBltData);

extern const UCHAR gajIndexPerRop[256];
extern const PFN_DIBFUNCTION gapfnDibFunction[];
extern const PFN_DIBFUNCTION gapfnMaskFunction[8];

#define RUN_MAX 20
typedef struct _LINEDATA
{
    SURFINFO siDst;

    LONG lRemainder;
    LONG lRemainder0;
    LONG lDelta;
    ULONG ulColor;
    ULONG acxyStyle[16];    /* Style array, adjusted to pixel size */
    USHORT cStyles;
    USHORT cxyStyleSize;
    USHORT iStyle;          /* Current index into pulStyle */
    USHORT xyStylePos;      /* Pixel offset from the start of iStyle */
    RUN runOtherCoordinate;
    union
    {
        UCHAR aj[FIELD_OFFSET(CLIPLINE, arun) + RUN_MAX * sizeof(RUN)];
        CLIPLINE cl;
    };

} LINEDATA, *PLINEDATA;

typedef
VOID
(FASTCALL
*PFN_DIB_LINETO)(
    _Inout_ PLINEDATA pld);

VOID
FASTCALL
Dib_Line_MajorX(
    PLINEDATA pld);

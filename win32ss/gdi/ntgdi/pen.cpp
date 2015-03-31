/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           ReactOS win32 subsystem
 * PURPOSE:           PEN class implementation
 * PROGRAMER:         Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#include "pen.hpp"

DBG_DEFAULT_CHANNEL(GdiPen);

/*

Using a PEN class
-----------------
Pro:
- BRUSH code is smaller (more separated), doesn't need to handle PEN stuff
- More "Natural"
-

Contra:
- Code duplication (e.g. DIB brushes)
- Needs delete hack

Using only BRUSH class
----------------------
Pro:
- Reduces overall complexity for the "outside", by having only one class

Contra:
- Pen specific functions (get pen width) might need checks (or asserts)


*/

#define PS_ENDCAP_SHIFT 8
#define PS_JOIN_SHIFT 12

PEN::PEN(
    _In_ FLONG flAttrs,
    _In_ COLORREF crColor,
    _In_ ULONG iHatch,
    _In_opt_ HBITMAP hbmPattern,
    _In_opt_ PVOID pvClient,
    _In_ ULONG flPenStyle,
    _In_ ULONG ulWidth,
    _In_ ULONG cstyle = 0,
    _In_ PULONG pulStyle = NULL,
    _In_ GDILOOBJTYPE loobjtype = GDILoObjType_LO_PEN_TYPE)
    : BRUSH(flAttrs, crColor, iHatch, hbmPattern, pvClient, loobjtype)
{
    NT_ASSERT(((cstyle == 0) ^ (pulStyle == 0)) == 0);

    /* Initialize pen related members */
    this->lWidth = ulWidth;
    //this->eWidth = 0.;
    this->ulPenStyle = flPenStyle;
    this->pStyle = pulStyle;
    this->dwStyleCount = cstyle;
    this->jJoin = (flPenStyle >> PS_JOIN_SHIFT) & 0x0F;
    this->jEndCap = (flPenStyle >> PS_ENDCAP_SHIFT) & 0x0F;
}

PEN::~PEN(
    VOID)
{
    __debugbreak();
}

UINT
PEN::cjGetObject(
    _In_ UINT cjBuffer,
    _Out_bytecap_(cjBuffer) PVOID pvBuffer) const
{
    UINT cjSize;

    if (this->flAttrs & BR_IS_OLDSTYLEPEN)
    {
        cjSize = sizeof(LOGPEN);

        if (pvBuffer != NULL)
        {
            if (cjBuffer < cjSize)
                return 0;

            /* Special handling for PS_NULL: creating an EXTPEN with PS_NULL
               will always return StockObject[NULL_PEN], so we allow to query
               an EXTLOGPEN */
            if (((this->ulPenStyle & PS_STYLE_MASK) == PS_NULL) &&
                (cjBuffer == sizeof(EXTLOGPEN)))
            {
                PEXTLOGPEN pelp = static_cast<PEXTLOGPEN>(pvBuffer);
                pelp->elpPenStyle = this->ulPenStyle;
                pelp->elpWidth = 0;
                pelp->elpBrushStyle = this->iBrushStyle;
                pelp->elpColor = this->BrushAttr.lbColor;
                pelp->elpHatch = 0;
                pelp->elpNumEntries = 0;
                cjSize = sizeof(EXTLOGPEN);
            }
            else
            {
                PLOGPEN plp = static_cast<PLOGPEN>(pvBuffer);
                plp->lopnWidth.x = this->lWidth;
                plp->lopnWidth.y = 0;
                plp->lopnStyle = this->ulPenStyle;
                plp->lopnColor = this->BrushAttr.lbColor;
            }
        }
    }
    else
    {
        NT_ASSERT(this->dwStyleCount <= 16);
        cjSize = sizeof(EXTLOGPEN) - sizeof(DWORD) + this->dwStyleCount * sizeof(DWORD);

        if (pvBuffer != NULL)
        {
            PEXTLOGPEN pelp = static_cast<PEXTLOGPEN>(pvBuffer);
            ULONG i;

            if (cjBuffer < cjSize)
                return 0;

            pelp->elpPenStyle = this->ulPenStyle;
            pelp->elpWidth = this->lWidth;
            pelp->elpBrushStyle = this->iBrushStyle;
            pelp->elpColor = this->BrushAttr.lbColor;
            pelp->elpHatch = (ULONG_PTR)this->hbmClient;
            pelp->elpNumEntries = this->dwStyleCount;
            for (i = 0; i < pelp->elpNumEntries; i++)
            {
                pelp->elpStyleEntry[i] = this->pStyle[i];
            }
        }
    }

    return cjSize;
}


extern "C" {

INT
APIENTRY
PEN_GetObject(PPEN ppen, INT cbCount, PLOGPEN pBuffer)
{
    return ppen->cjGetObject(cbCount, pBuffer);
}

static
HPEN
CreatePenInternal(
    _In_ FLONG flAttrs,
    _In_ COLORREF crColor,
    _In_ ULONG iHatch,
    _In_opt_ HBITMAP hbmPattern,
    _In_opt_ ULONG pvClient,
    _In_ ULONG flPenStyle,
    _In_ ULONG ulWidth,
    _In_ ULONG cstyle,
    _In_reads_opt_(cstyle) PULONG pulStyle)
{
    GDILOOBJTYPE loobjtype;
    BASEOBJECT::OWNER owner;
    PPEN ppen;
    HPEN hpen;

    /* Use the correct object type */
    loobjtype = (flAttrs & BR_IS_OLDSTYLEPEN) ? GDILoObjType_LO_PEN_TYPE :
                                                GDILoObjType_LO_EXTPEN_TYPE;

    /* Create the PEN object */
    ppen = new PEN(flAttrs,
                   crColor,
                   iHatch,
                   hbmPattern,
                   pvClient,
                   flPenStyle,
                   ulWidth,
                   cstyle,
                   pulStyle,
                   loobjtype);
    if (ppen == NULL)
    {
        ERR("Failed to allocate PEN\n");
        if (hbmPattern != NULL)
        {
            GreSetBitmapOwner(hbmPattern, BASEOBJECT::OWNER::POWNED);
            GreDeleteObject(hbmPattern);
        }
        return NULL;
    }

    /* Set the owner, either public or process owned */
    owner = (flAttrs & BR_IS_GLOBAL) ? BASEOBJECT::OWNER::PUBLIC :
                                       BASEOBJECT::OWNER::POWNED;

    /* Insert the object into the GDI handle table */
    hpen = static_cast<HPEN>(ppen->hInsertObject(owner));
    if (hpen == NULL)
    {
        ERR("Failed to insert pen\n");
        delete ppen;
        return NULL;
    }

    /* Unlock the pen */
    ppen->vUnlock();

    return hpen;
}

HPEN
NTAPI
IntCreateStockPen(
    ULONG flPenStyle,
    ULONG ulWidth,
    COLORREF crColor)
{
    FLONG flAttrs = BR_IS_GLOBAL | BR_IS_OLDSTYLEPEN;

    switch (flPenStyle & PS_STYLE_MASK)
    {
        case PS_NULL:
            flAttrs |= BR_IS_NULL;
            ulWidth = 1;
            break;

        case PS_SOLID:
        case PS_INSIDEFRAME:
            flAttrs |= BR_IS_SOLID;
            break;


    }

    return CreatePenInternal(flAttrs,
                             crColor,
                             0,
                             NULL,
                             NULL,
                             flPenStyle,
                             ulWidth,
                             0,
                             NULL);
}

PPEN
FASTCALL
PEN_ShareLockPen(HPEN hpen)
{
    return 0;
}

HPEN
APIENTRY
GreExtCreatePen(
    _In_ ULONG flPenStyle,
    _In_ ULONG ulWidth,
    _In_ ULONG iBrushStyle,
    _In_ COLORREF crColor,
    _In_ ULONG_PTR lClientHatch,
    _In_ ULONG_PTR lHatch,
    _In_ ULONG cstyle,
    _In_reads_opt_(cstyle) PULONG pulStyle,
    _In_ ULONG cjDIB,
    _In_ BOOL bOldStylePen,
    _In_opt_ HBRUSH hbr)
{
    static const ULONG aulStyleAlternate[2] = {1, 1};
    static const ULONG aulStyleDot[2] = {1, 1};
    static const ULONG aulStyleDash[2] = {3, 1};
    static const ULONG aulStyleDashDot[4] = {3, 2, 1, 2};
    static const ULONG aulStyleDashDotDot[6] = {3, 1, 1, 1, 1, 1};
    FLONG flAttrs = 0;

    if (hbr != NULL)
    {
        WARN("hbr is not supported, ignoring\n");
    }


    __debugbreak();

    /* Handle NULL pen */
    if ((flPenStyle & PS_STYLE_MASK) == PS_NULL)
    {
        return StockObjects[NULL_PEN];
    }

    /* Fix up negative width */
    if ((LONG)ulWidth < 0)
    {
        ulWidth = -(LONG)ulWidth;
    }

    /* Set pen type */
    flAttrs |= bOldStylePen ? BR_IS_OLDSTYLEPEN : BR_IS_PEN;

    switch (flPenStyle & PS_TYPE_MASK)
    {
        case PS_COSMETIC:

            /* Make sure the width is 1 */
            if (ulWidth != 1)
            {
                ERR("GreExtCreatePen: invalid pen width: %lu\n", ulWidth);
                EngSetLastError(ERROR_INVALID_PARAMETER);
                return NULL;
            }
            break;

        case PS_GEOMETRIC:
            break;

        default:
            ERR("GreExtCreatePen: invalid pen type 0x%lx\n", flPenStyle);
            EngSetLastError(ERROR_INVALID_PARAMETER);
            return NULL;
    }

    switch (flPenStyle & PS_STYLE_MASK)
    {
        case PS_NULL:
            __debugbreak();
            break;

        case PS_SOLID:
            flAttrs |= BR_IS_SOLID;
            break;

        case PS_INSIDEFRAME:
            flAttrs |= (BR_IS_SOLID | BR_IS_INSIDEFRAME);
            break;

        case PS_ALTERNATE:
            cstyle = 2;
            pulStyle = aulStyleAlternate;
            break;

        case PS_DOT:
            cstyle = 2;
            pulStyle = aulStyleDot);
            break;

        case PS_DASH:
            cstyle = 2;
            pulStyle = aulStyleDash;
            break;

        case PS_DASHDOT:
            cstyle = 4;
            pulStyle = aulStyleDashDot);
            break;

        case PS_DASHDOTDOT:
            cstyle = 6;
            pulStyle = aulStyleDashDotDot);
            break;

        case PS_USERSTYLE:

            __debugbreak();
            break;

        default:
            ERR("GreExtCreatePen: invalid pen style 0x%lx\n", flPenStyle);
            EngSetLastError(ERROR_INVALID_PARAMETER);
            return NULL;
    }

    switch (iBrushStyle)
    {
        case BS_SOLID:
            flAttrs |= BR_IS_SOLID;
            break;

        case BS_NULL:
            flAttrs |= BR_IS_NULL;
            break;

        case BS_HATCHED:
            flAttrs |= BR_IS_HATCH;
            break;

        case BS_PATTERN:
            flAttrs |= BR_IS_BITMAP;
            break;

        case BS_DIBPATTERNPT:
            flAttrs |= BR_IS_DIB;
            break;

        /* Not supported: */
        case BS_INDEXED:
        case BS_PATTERN8X8:
        case BS_DIBPATTERN8X8:
        case BS_MONOPATTERN:
        case BS_DIBPATTERN:
        default:
            ERR("GreExtCreatePen: invalid brush style 0x%lx\n", iBrushStyle);
            EngSetLastError(ERROR_INVALID_PARAMETER);
            return NULL;
    }

    hpen = CreatePenInternal(flAttrs,
                             crColor,
                             iHatch,
                             hbmPattern,
                             pvClient,
                             flPenStyle,
                             ulWidth,
                             cstyle,
                             pulStyle);
    return 0;
}

__kernel_entry
W32KAPI
HPEN
APIENTRY
NtGdiCreatePen(
    _In_ INT iPenStyle,
    _In_ INT iPenWidth,
    _In_ COLORREF crColor,
    _In_opt_ HBRUSH hbr)
{
    /* Check if the pen style is valid */
    if ((iPenStyle < PS_SOLID) || (iPenStyle > PS_INSIDEFRAME))
    {
        EngSetLastError(ERROR_INVALID_PARAMETER);
        return NULL;
    }

    /* Call the extended function */
    return GreExtCreatePen(iPenStyle,
                           iPenWidth,
                           BS_SOLID,
                           crColor,
                           0,
                           0,
                           0,
                           NULL,
                           0,
                           TRUE,
                           hbr);
}

__kernel_entry
W32KAPI
HPEN
APIENTRY
NtGdiExtCreatePen(
    _In_ ULONG flPenStyle,
    _In_ ULONG ulWidth,
    _In_ ULONG iBrushStyle,
    _In_ ULONG ulColor,
    _In_ ULONG_PTR lClientHatch,
    _In_ ULONG_PTR lHatch,
    _In_ ULONG cstyle,
    _In_reads_opt_(cstyle) PULONG pulStyle,
    _In_ ULONG cjDIB,
    _In_ BOOL bOldStylePen,
    _In_opt_ HBRUSH hbr)
{
    ULONG aulSafeStyles[16];
    HPEN hpen;

    /* Check if we have styles */
    if (pulStyle != NULL)
    {
        if ((cstyle == 0) || (cstyle > 16))
        {
            ERR("Invalid cstyle: %lu\n", cstyle);
            EngSetLastError(ERROR_INVALID_PARAMETER);
            return NULL;
        }

        _SEH2_TRY
        {
            ProbeForRead(pulStyle, cstyle * sizeof(ULONG), 1);
            RtlCopyMemory(aulSafeStyles, pulStyle, cstyle * sizeof(ULONG));
            pulStyle = aulSafeStyles;
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            ERR("Got exception! pulStyle = %p\n", pulStyle);
            return NULL;
        }
        _SEH2_END;
    }


    hpen = GreExtCreatePen(flPenStyle,
                           ulWidth,
                           iBrushStyle,
                           ulColor,  // LOGBRUSH::lbColor
                           lClientHatch, // LOGBRUSH::lbHatch
                           lHatch, // converted DIB
                           cstyle,
                           pulStyle,
                           cjDIB,
                           bOldStylePen,
                           hbr);

    return hpen;
}


} // extern "C"

/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           ReactOS win32 subsystem
 * PURPOSE:           XCLIPOBJ class implementation
 * PROGRAMER:         Timo Kreuzer (timo.kreuzer@reactos.org)
 *
 * REFERENCES:        http://www.drdobbs.com/windows/undocumented-corner/184408967
 */

#include <win32k.h>
#include "clipobj.h"

DBG_DEFAULT_CHANNEL(EngClip);

XCLIPOBJ gxcoTrivial =
{
    /* CLIPOBJ */
    {
        {
            0, /* iUniq */
            {LONG_MIN, LONG_MIN, LONG_MAX, LONG_MAX}, /* rclBounds */
            DC_TRIVIAL,    /* idCOmplexity */
            FC_RECT,       /* iFComplexity */
            TC_RECTANGLES, /* iMode */
            0              /* fjOptions */
        },
    },
    0, 0, 0
};

XCLIPOBJ::XCLIPOBJ(
    VOID)
{
    _co.iUniq = 0;
    _co.rclBounds.left = MIN_COORD;
    _co.rclBounds.top = MIN_COORD;
    _co.rclBounds.right = MAX_COORD;
    _co.rclBounds.bottom = MAX_COORD;
    _co.iDComplexity = DC_TRIVIAL;
    _co.iFComplexity = FC_RECT;
    _co.iMode = CT_RECTANGLES;
    _co.fjOptions = 0;
    _wndo.pvConsumer = NULL;
    _wndo.rclClient = _co.rclBounds;
    _wndo.psoOwner = NULL;
}


XCLIPOBJ::~XCLIPOBJ(
    VOID)
{

}

VOID
XCLIPOBJ::vUpdate(
    _In_ PRECTL prcDrawingBounds)
{
    _co.iUniq = 0;

    if (_prgn != NULL)
    {
        _cRects = _prgn->rdh.nCount;
    }

    if (!RECTL_bIntersectRect(&_co.rclBounds,
                              &_wndo.rclClient,
                              prcDrawing);

    _co.rclBounds.left = MIN_COORD;
    _co.rclBounds.top = MIN_COORD;
    _co.rclBounds.right = MAX_COORD;
    _co.rclBounds.bottom = MAX_COORD;

    if (_cRects == 1)
    {
        _co.iDComplexity = DC_RECT;
        _co.iFComplexity = FC_RECT;
    }
    else
    {
        _co.iDComplexity = DC_COMPLEX;
        _co.iFComplexity = (_cRects <= 4) ? FC_RECT4 : FC_COMPLEX;
    }

    _co.iMode = CT_RECTANGLES;
    _co.fjOptions = 0;
    _wndo.pvConsumer = NULL;
    _wndo.rclClient = _co.rclBounds;
    _wndo.psoOwner = NULL;
}

ULONG
XCLIPOBJ::cEnumStart(
    _In_ BOOL bAll,
    _In_ ULONG iType,
    _In_ ULONG iDirection,
    _In_ ULONG cLimit)
{
    PRECTL prcTopLeft, prcBottomRight;

    NT_ASSERT(iType == CT_RECTANGLES);

    /* Check if we have a region */
    if (_prgn != NULL)
    {
        /* Update rect count and buffer pointer */
        _cRects = _prgn->rdh.nCount;
        _prc = _prgn->Buffer;

        /* Check if only partial enumeration was requested, but the bounding
           box of the region is fully covered by the bounding box for the
           enumeration */
        if (!bAll &&
            (_co.rclBounds.left <= _prgn->rdh.rcBound.left) &&
            (_co.rclBounds.top <= _prgn->rdh.rcBound.top) &&
            (_co.rclBounds.right <= _prgn->rdh.rcBound.right) &&
            (_co.rclBounds.bottom <= _prgn->rdh.rcBound.bottom))
        {
            /* We can as well enumerate the whole region, which is simpler */
            bAll = TRUE;
        }
    }

    if (_cRects == 1)
    {
        iDirection = CD_ANY;
    }

    _bAll = bAll;
    _iType = iType;
    _iDirection = iDirection;

    if (bAll)
    {
        prcTopLeft = _prc;
        prcBottomRight = &_prc[_cRects];
    }
    else
    {
        PRECTL prc = _prc;

        /* Skip all rects above the bounding rect */
        while ((prc < &_prc[_cRects]) &&
               (prc->bottom <= _co.rclBounds.top))
        {
            prc++;
        }

        /* Safe this as the top index */
        prcTopLeft = prc;

        /* Loop while we are within the bounding rect */
        while ((prc < &_prc[_cRects]) &&
               (prc->top < _co.rclBounds.bottom))
        {
            prc++;
        }

        prcBottomRight = prc;
    }



    switch (iDirection)
    {
        default:
            ERR("Invalid iDirection %lu, using CD_ANY\n", iDirection);
            _iDirection = CD_ANY;
            /* Fall through */

        case CD_ANY:
        case CD_RIGHTDOWN:

            if (bAll)
            {
                _iEnumNext = 0;
                _iLast = _cRects;
            }
            else
            {
                _iEnumNext = prcTopLeft - _prc;
                _iLast = prcBottomRight - _prc;
            }

            /* These 2 are unused */
            _iRowStart = -1;
            _iLastInRow = -1;
            break;

        case CD_LEFTUP:
            if (bAll)
            {
                _iEnumNext = _cRects - 1;
                _iLast = 0;
            }
            else
            {
                _iEnumNext = prcTopLeft - _prc;
                _iLast = prcBottomRight - _prc;
            }

            /* These 2 are unused */
            _iRowStart = -1;
            _iLastInRow = -1;
            break;

        case CD_RIGHTUP:

            break;

        case CD_LEFTDOWN:

            if (bAll)
            {
                _iEnumNext = -1;
                _iRowStart = -1;
                _iLastInRow = 0;
                _iLast = _cRects;
            }
            else
            {
                _iEnumNext = -1;
                _iRowStart = -1;
                _iLastInRow = 0;
                _iLast = _cRects;
            }
    }

    return 0;
}

BOOL
XCLIPOBJ::bEnum(
    _In_ ULONG cEnum,
    _Out_ ENUMRECTS *per)
{
    ULONG cMaxRects;
    PRECTL prcSrc, prcDst, prcDstEnd, prcLeftMost;

    cMaxRects = min(cEnum, _cRemaining);

    prcDst = per->arcl;
    prcDstEnd = prcDst + cMaxRects;

    switch (_iDirection)
    {
        case CD_ANY:
        case CD_RIGHTDOWN:

            prcSrc = &_prc[_iEnumNext];
            for (ULONG i = 0; i < cMaxRects; i++)
            {
                per->arcl[i] = *prcSrc;
                prcSrc++;
            }


            break;

        case CD_LEFTUP:

            prcSrc = &_prc[_iEnumNext];
            do
            {
                *prcDst++ = *prcSrc--;
            } while (prcDst != prcDstEnd);

            break;

        case CD_RIGHTUP:

            break;

        case CD_LEFTDOWN:

            /*
             *        |-------bounding---------|
             *  +---+   +---------+  +---+    +-----+   +-----+
             *  | 0 |   |    1    |  | 2 |    |  3  |   |  4  |
             *  +---+   +---------+  +---+    +-----+   +-----+
             *          ^ LeftMost                      ^ RowStart
             *               <------ enumeration -----
             */

            prcSrc = &_prc[_iEnumNext];
            prcLeftMost = &_prc[_iLastInRow];

            do
            {
                /* Check if we are past the leftmost rect in this row */
                if (prcSrc < prcLeftMost)
                {
                    /* The next row ends one after the current row start */
                    prcSrc = &_prc[_iRowStart + 1];

                    if (!_bAll)
                    {
                        /* Loop while the rects are outside of the bounding */
                        while ((prcSrc < &_prc[_iLast]) &&
                               (prcSrc->right < _co.rclBounds.left))
                        {
                            prcSrc++;
                        }

                        /* Safe this as leftmost */
                        prcLeftMost = prcSrc;

                        /* Loop until we have found the rightmost rect within
                           the bounding rect */
                        while ((&prcSrc[1] < &_prc[_iLast]) &&
                               (prcSrc[1].top == prcSrc->top) &&
                               (prcSrc[1].left < _co.rclBounds.right))
                        {
                            prcSrc++;
                        }
                    }
                    else
                    {
                        /* Safe this as leftmost */
                        prcLeftMost = prcSrc;
                    }

                    /// FIXME: we don't want to start right, if bAll is set

                    /* Loop until we have found the rightmost rect in the row */
                    while ((&prcSrc[1] < &_prc[_iLast]) &&
                           (prcSrc[1].top == prcSrc->top))
                    {
                        prcSrc++;
                    }

                    /* Save the row start */
                    _iRowStart = prcSrc - _prc;
                }

                /* Copy one rect, go left in the source */
                *prcDst++ = *prcSrc--;

            } while (prcDst == prcDstEnd);

            /* Update values */
            _iEnumNext = prcSrc - _prc;
            _iLastInRow = prcLeftMost - _prc;

            break;

        default:
            NT_ASSERT(FALSE);
            return FALSE;
    }

    if ( !bAll || (_cEnumerated > cMaxRects))
    {
        return 0xFFFFFFFF;
    }

    return _cEnumerated;
}

extern "C" {

CLIPOBJ*
APIENTRY
EngCreateClip(
    VOID)
{
    return (CLIPOBJ*)new XCLIPOBJ;
}

VOID
APIENTRY
EngDeleteClip(
    _In_ _Post_ptr_invalid_ CLIPOBJ *pco)
{
    XCLIPOBJ *pxco = reinterpret_cast<XCLIPOBJ*>(pco);
    delete pxco;
}

ULONG
APIENTRY
CLIPOBJ_cEnumStart(
    _Inout_ CLIPOBJ *pco,
    _In_ BOOL bAll,
    _In_ ULONG iType,
    _In_ ULONG iDirection,
    _In_ ULONG cLimit)
{
    XCLIPOBJ *pxco = reinterpret_cast<XCLIPOBJ*>(pco);

    return pxco->cEnumStart(bAll, iType, iDirection, cLimit);
}

BOOL
APIENTRY
CLIPOBJ_bEnum(
    _In_ CLIPOBJ *pco,
    _In_ ULONG cj,
    _Out_bytecap_(cj) ULONG *pulEnumRects)
{
    XCLIPOBJ *pxco = reinterpret_cast<XCLIPOBJ*>(pco);
    ENUMRECTS *per = reinterpret_cast<ENUMRECTS*>(pulEnumRects);
    ULONG cRects = (cj - FIELD_OFFSET(ENUMRECTS, arcl)) / sizeof(RECTL);
    return pxco->bEnum(cRects, per);
}

} // extern "C"

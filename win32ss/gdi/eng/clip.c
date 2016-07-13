/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           ReactOS kernel
 * PURPOSE:           GDI Clipping Functions
 * FILE:              win32ss/gdi/eng/clip.c
 * PROGRAMER:         Jason Filby
 */

#include <win32k.h>
DBG_DEFAULT_CHANNEL(EngClip);


static
int
__cdecl
CompareRightDown(
    const RECTL *r1,
    const RECTL *r2)
{
    int Cmp;

    if (r1->top < r2->top)
    {
        Cmp = -1;
    }
    else if (r2->top < r1->top)
    {
        Cmp = +1;
    }
    else
    {
        ASSERT(r1->bottom == r2->bottom);
        if (r1->left < r2->left)
        {
            Cmp = -1;
        }
        else if (r2->left < r1->left)
        {
            Cmp = +1;
        }
        else
        {
            ASSERT(r1->right == r2->right);
            Cmp = 0;
        }
    }

    return Cmp;
}

static
int
__cdecl
CompareRightUp(
    const RECTL *r1,
    const RECTL *r2)
{
    int Cmp;

    if (r1->bottom < r2->bottom)
    {
        Cmp = +1;
    }
    else if (r2->bottom < r1->bottom)
    {
        Cmp = -1;
    }
    else
    {
        ASSERT(r1->top == r2->top);
        if (r1->left < r2->left)
        {
            Cmp = -1;
        }
        else if (r2->left < r1->left)
        {
            Cmp = +1;
        }
        else
        {
            ASSERT(r1->right == r2->right);
            Cmp = 0;
        }
    }

    return Cmp;
}

static
int
__cdecl
CompareLeftDown(
    const RECTL *r1,
    const RECTL *r2)
{
    int Cmp;

    if (r1->top < r2->top)
    {
        Cmp = -1;
    }
    else if (r2->top < r1->top)
    {
        Cmp = +1;
    }
    else
    {
        ASSERT(r1->bottom == r2->bottom);
        if (r1->right < r2->right)
        {
            Cmp = +1;
        }
        else if (r2->right < r1->right)
        {
            Cmp = -1;
        }
        else
        {
            ASSERT(r1->left == r2->left);
            Cmp = 0;
        }
    }

    return Cmp;
}

static
int
__cdecl
CompareLeftUp(
    const RECTL *r1,
    const RECTL *r2)
{
    int Cmp;

    if (r1->bottom < r2->bottom)
    {
        Cmp = +1;
    }
    else if (r2->bottom < r1->bottom)
    {
        Cmp = -1;
    }
    else
    {
        ASSERT(r1->top == r2->top);
        if (r1->right < r2->right)
        {
            Cmp = +1;
        }
        else if (r2->right < r1->right)
        {
            Cmp = -1;
        }
        else
        {
            ASSERT(r1->left == r2->left);
            Cmp = 0;
        }
    }
    return Cmp;
}

VOID
FASTCALL
IntEngInitClipObj(XCLIPOBJ *Clip)
{
    Clip->ClipObj.iUniq = 0;
    Clip->ClipObj.rclBounds.left = LONG_MIN;
    Clip->ClipObj.rclBounds.top = LONG_MIN;
    Clip->ClipObj.rclBounds.right = LONG_MAX;
    Clip->ClipObj.rclBounds.bottom = LONG_MAX;
    Clip->ClipObj.iDComplexity = DC_TRIVIAL;
    Clip->ClipObj.iFComplexity = FC_RECT;
    Clip->ClipObj.iMode = TC_RECTANGLES;
    Clip->ClipObj.fjOptions = 0;

    Clip->Rects = Clip->ClipObj.arcBuffer;
    Clip->BufferSize = RTL_NUMBER_OF(Clip->ClipObj.arcBuffer);
    Clip->RectCount = 1;
    Clip->ClipObj.arcBuffer[0].left = 0;
    Clip->ClipObj.arcBuffer[0].top = 0;
    Clip->ClipObj.arcBuffer[0].right = 0;
    Clip->ClipObj.arcBuffer[0].bottom = 0;
    Clip->prgn = NULL;
}

VOID FASTCALL
IntEngFreeClipResources(XCLIPOBJ *Clip)
{
    if (Clip->Rects != &Clip->rclBounds)
        EngFreeMem(Clip->Rects);
}


VOID
FASTCALL
XCLIPOBJ_vSetRect(
    XCLIPOBJ* pxco,
    const RECTL* prc)
{
    /* Set the rect */
    pxco->Rects[0] = *prc;
    pxco->RectCount = 1;
    pxco->EnumOrder = CD_ANY;

    /* Update the complexity */
    pxco->ClipObj.iDComplexity = (((prc->top == prc->bottom) &&
                                 (prc->left == prc->right))
                                 ? DC_TRIVIAL : DC_RECT);
    pxco->ClipObj.iFComplexity = FC_RECT;
}

VOID
FASTCALL
XCLIPOBJ_vUpdate(
    XCLIPOBJ* pxco,
    PREGION prgnClip)
{
    /* Update the region pointer and the count of rects */
    pxco->prgn = prgnClip;
    pxco->RectCount = prgnClip->rdh.nCount;

    /* Update the CLIPOBJ */
    pxco->ClipObj.iUniq = prgnClip->iUniq;
    if (pxco->RectCount == 1)
    {
        pxco->ClipObj.iDComplexity = RECTL_bIsEmpty(&prgnClip->rclBounds) ?
                                         DC_TRIVIAL : DC_RECT);
        pxco->ClipObj.iFComplexity = FC_RECT;
    }
    else
    {
        pxco->ClipObj.iDComplexity = DC_COMPLEX;
        pxco->ClipObj.iFComplexity = ((pxco->RectCount <= 4) ?
                                          FC_RECT4 : FC_COMPLEX);;
    }

    /* Use the buffer of the region, which is sorted right-down */
    pxco->EnumOrder = CD_RIGHTDOWN;
}

VOID
FASTCALL
XCLIPOBJ_vUpdateBufferSize(
    XCLIPOBJ* pxco,
    ULONG cRects)
{
}

VOID
FASTCALL
XCLIPOBJ_vSetDrawingBounds(
    XCLIPOBJ* pxco,
    PRECT prcDraw)
{
    if (pxco->prgn != NULL)
    {
        RECTL_bIntersectRect(&pxco->ClipObj.rclBounds,
                             pxco->prgn->rdh.Bounds,
                             prcDraw);
    }
    else
    {
        NT_ASSERT(pxco->RectCount == 1);
        pxco->ClipObj.rclBounds = *prcDraw;
    }
}


/*
 * @implemented
 */
CLIPOBJ *
APIENTRY
EngCreateClip(VOID)
{
    XCLIPOBJ *Clip = EngAllocMem(FL_ZERO_MEMORY, sizeof(XCLIPOBJ), GDITAG_CLIPOBJ);
    if(Clip != NULL)
    {
        IntEngInitClipObj(Clip);
        TRACE("Created Clip Obj %p.\n", Clip);
        return (CLIPOBJ *)Clip;
    }

    ERR("Clip object allocation failed!\n");
    return NULL;
}

/*
 * @implemented
 */
VOID
APIENTRY
EngDeleteClip(
    _In_ _Post_ptr_invalid_ CLIPOBJ *pco)
{
    XCLIPOBJ* pxco = (XCLIPOBJ *)pco;
    TRACE("Deleting %p.\n", pco);
    IntEngFreeClipResources(pxco);
    EngFreeMem(pxco);
}

/*
 * @implemented
 */
ULONG
APIENTRY
CLIPOBJ_cEnumStart(
    _Inout_ CLIPOBJ *pco,
    _In_ BOOL bAll,
    _In_ ULONG iType,
    _In_ ULONG iDirection,
    _In_ ULONG cMaxRects)
{
    XCLIPOBJ* Clip = (XCLIPOBJ *)pco;
    SORTCOMP CompareFunc;

    NT_ASSERT(iType == CT_RECTANGLES);

    /* Check if the clip object has a region */
    if (Clip->prgn != NULL)
    {
        /* Update rect count */
        Clip->RectCount = Clip->prgn->rdh.Count;
        prc = Clip->prgn->rdh.Buffer;
    }
    else
    {
        prc = Clip->Rects;
    }

    if (bAll)
    {
        Clip->EnumMax = (cMaxRects > 0) ? cMaxRects : Clip->RectCount;

    }
    else
    {

    }

    Clip->EnumPos = 0;

    if (bAll)
    {
        if ((iDirection == CD_RIGHTDOWN) && (Clip->prgn != NULL))
        {
            prcl = Clip->prgn->rdh.Buffer;
        }
        else if ((iDirection == CD_ANY) || (iDirection == Clip->EnumOrder))
        {
            prcl = Clip->Rects;
        }

        if ((iDirection != CD_ANY) && (iDirection != Clip->EnumOrder))
        {
            if ((iDirection == CD_RIGHTDOWN) && (Clip->prgn != NULL))
            {
                Clip->EnumOrder = CD_RIGHTDOWN
            }

            switch (iDirection)
            {
                case CD_RIGHTDOWN:

                    CompareFunc = (SORTCOMP) CompareRightDown;
                    break;

                case CD_RIGHTUP:
                    CompareFunc = (SORTCOMP) CompareRightUp;
                    break;

                case CD_LEFTDOWN:
                    CompareFunc = (SORTCOMP) CompareLeftDown;
                    break;

                case CD_LEFTUP:
                    CompareFunc = (SORTCOMP) CompareLeftUp;
                    break;

                default:
                    ERR("Invalid iDirection %lu\n", iDirection);
                iDirection = Clip->iDirection;
                    CompareFunc = NULL;
                    break;
            }

            if (NULL != CompareFunc)
            {
                EngSort((PBYTE) Clip->Rects, sizeof(RECTL), Clip->RectCount, CompareFunc);
            }

        Clip->iDirection = iDirection;
        }

    }
    else
    {

    }

    /* Return the number of rectangles enumerated */
    if ((cMaxRects > 0) && (Clip->RectCount > cMaxRects))
    {
        return 0xFFFFFFFF;
    }

    return Clip->RectCount;
}

/*
 * @implemented
 */
BOOL
APIENTRY
CLIPOBJ_bEnum(
    _In_ CLIPOBJ *pco,
    _In_ ULONG cj,
    _Out_bytecap_(cj) ULONG *pulEnumRects)
{
    const RECTL* src;
    XCLIPOBJ* Clip = (XCLIPOBJ *)pco;
    ULONG nCopy;
    ENUMRECTS* pERects = (ENUMRECTS*)pulEnumRects;

    // Calculate how many rectangles we should copy
    nCopy = min( Clip->EnumMax - Clip->EnumPos,
            min( Clip->RectCount - Clip->EnumPos,
            (cj - sizeof(ULONG)) / sizeof(RECTL)));

    if(nCopy == 0)
    {
        return FALSE;
    }

    /* Copy rectangles */
    src = &Clip->Rects[Clip->EnumPos];
    RtlCopyMemory(pERects->arcl, src, nCopy * sizeof(RECTL));

    pERects->c = nCopy;

    Clip->EnumPos+=nCopy;

    return Clip->EnumPos < Clip->RectCount;
}

/* EOF */

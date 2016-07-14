
#pragma once

#include "win32k.h"


enum
{
    BLT_NEED_SRC = 1,
    BLT_TRG_FIXPOINTS = 2,
    BLT_SRC_FIXPOINTS = 4,
};

class BLTOBJ
{
    PDC _pdcSrc;
    PDC _pdcTrg;
    PSURFACE _psSrc;
    PSURFACE _psTrg;
    EXLATEOBJ _exlo;
    XLATEOBJ *_pxlo;
    BRUSHOBJ *_pboFill;
    BRUSHOBJ *_pboLine;
    union
    {
        POINTL apt[4];
        struct
        {
            RECTL _rclTrg;
            RECTL _rclSrc;
        };
        POINT _ptlTrg;
        POINTFIX _ptfxTrg;
    };
    union
    {
        ULONG _fl;
        struct
        {
            FLONG _fDevicesLocked : 1;
            FLONG _fXlateInitialized : 1;
            FLONG _fXlateNeedsCleanup : 1;
            FLONG _UseFixPoints : 1;
            FLONG _UpdateCurrentPos : 1;
        };
    };

    enum STATE_FLAGS
    {
        FL_DEVICES_LOCKED = 1,
    };

public:

    BLTOBJ(
        VOID)
    {
        _fl = 0;
        _pdcSrc = NULL;
        _pdcTrg = NULL;
    }

    ~BLTOBJ(
        VOID);

    BOOL
    bInit(
        _In_ HDC hdcTrg,
        _In_opt_ HDC hdcSrc,
        _In_ PPOINT pptTrg,
        _In_ ULONG cptTrg,
        _In_opt_ PPOINT pptSrc,
        _In_ ULONG cptSrc,
        _In_ ULONG fl);

    inline
    BOOL
    bInit(
        _In_ HDC hdcTrg,
        _In_opt_ HDC hdcSrc,
        _In_ PRECTL prclTrg,
        _In_ PRECTL prclSrc,
        _In_ BOOL bNeedSource)
    {
        return bInit(hdcTrg,
                     hdcSrc,
                     reinterpret_cast<PPOINT>(prclTrg),
                     2,
                     reinterpret_cast<PPOINT>(prclSrc),
                     2,
                     bNeedSource ? BLT_NEED_SRC : 0);
    }

    inline
    BOOL
    bInit(
        _In_ HDC hdcTrg,
        _In_ ULONG x,
        _In_ ULONG y)
    {
        _UseFixPoints = TRUE;
        _UpdateCurrentPos = TRUE;
        _ptlTrg.x = x;
        _ptlTrg.y = y;
        return bInit(hdcTrg,
                     NULL,
                     &_ptlTrg,
                     2,
                     NULL,
                     0,
                     BLT_TRG_FIXPOINTS);
    }

    VOID
    vUnlockDcs(
        VOID);

    VOID
    vLockDevices(
        VOID);

    VOID
    vUnlockDevices(
        VOID);

    VOID
    vInitXlateObject(
        VOID);

    inline
    BOOL
    bTrgDcHasSurface(
        VOID)
    {
        return _pdcTrg ? (_pdcTrg->dclevel.pSurface != NULL) : FALSE;
    }

    inline
    BOOL
    bSrcDcHasSurface(
        VOID)
    {
        return _pdcSrc ? (_pdcSrc->dclevel.pSurface != NULL) : FALSE;
    }

    _Maybenull_
    inline
    SURFOBJ*
    psoTrg(
        VOID)
    {
        if (!_fDevicesLocked)
        {
            vLockDevices();
        }
        _fDevicesLocked = TRUE;
        return _psTrg ? &_psTrg->SurfObj : NULL;
    }

    _Maybenull_
    inline
    SURFOBJ*
    psoSrc(
        VOID)
    {
        if (!_fDevicesLocked)
        {
            vLockDevices();
        }
        _fDevicesLocked = TRUE;
        return _psSrc ? &_psSrc->SurfObj : NULL;
    }

    inline
    CLIPOBJ*
    pco(
        VOID)
    {
        return &_pdcTrg->co.ClipObj;
    }

    inline
    XLATEOBJ*
    pxlo(
        VOID)
    {
        if (!_fXlateInitialized)
        {
            vInitXlateObject();
        }
        return _pxlo;
    }

    inline
    BRUSHOBJ*
    pboFill(
        VOID)
    {
        if (_pdcTrg->pdcattr->ulDirty_ & (DIRTY_FILL | DC_BRUSH_DIRTY))
        {
            DC_vUpdateFillBrush(_pdcTrg);
        }
        return &_pdcTrg->eboFill.BrushObject;
    }

    inline
    BRUSHOBJ*
    pboLine(
        VOID)
    {
        if (_pdcTrg->pdcattr->ulDirty_ & (DIRTY_LINE | DC_PEN_DIRTY))
        {
            DC_vUpdateFillBrush(_pdcTrg);
        }
        return &_pdcTrg->eboLine.BrushObject;
    }

    inline
    PRECTL
    prclTrg(
        VOID)
    {
        return &_rclTrg;
    }

    inline
    PRECTL
    prclSrc(
        VOID)
    {
        return &_rclSrc;
    }

    inline
    PPOINTFIX
    pptfxTrg(
        VOID)
    {
        NT_ASSERT(_UseFixPoints);
        return &_ptfxTrg;
    }

    inline
    PPOINTFIX
    pptfxTrgCurrent(
        VOID)
    {
        return &_pdcTrg->pdcattr->ptfxCurrent;
    }

    inline
    MIX
    mix(
        VOID)
    {
        return ROP2_TO_MIX(_pdcTrg->pdcattr->jROP2);
    }

};


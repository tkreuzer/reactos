
#include <win32k.h>
#include "bltobj.hpp"

extern "C" {

BOOL
APIENTRY
GreLineTo(
    _In_ HDC hdc,
    _In_ INT x,
    _In_ INT y)
{
    BLTOBJ bltobj;
    PPOINTFIX pptfx1, pptfx2;
    RECTL rclBounds;

    /* Initialize the BLTOBJ */
    if (!bltobj.bInit(hdc, x, y))
    {
        return FALSE;
    }

    /* Check for empty memory DC */
    if (!bltobj.bTrgDcHasSurface())
    {
        return TRUE;
    }

    /* Get fix point coordinates */
    pptfx1 = bltobj.pptfxTrgCurrent();
    pptfx2 = bltobj.pptfxTrg();

    /* Calculate the bounds */
    rclBounds.left = FIX2LONG(pptfx1->x);
    rclBounds.top = FIX2LONG(pptfx1->y);
    rclBounds.right = FIX2LONG(pptfx2->x);
    rclBounds.bottom = FIX2LONG(pptfx2->y);

    /* Call the Eng / Drv function */
    return IntEngLineTo(bltobj.psoTrg(),
                        bltobj.pco(),
                        bltobj.pboLine(),
                        pptfx1->x,
                        pptfx1->y,
                        pptfx2->x,
                        pptfx2->y,
                        &rclBounds,
                        bltobj.mix());
}

} // extern "C"


#if 0
class DIBOBJ
{
    PUCHAR pjCurrent;
};

class DIBOBJ_32BPP : public DIBOBJ
{
public:

    inline
    void
    MoveRight(void)
    {
        _pjCurrent += 4;
    }

};

#endif // 0


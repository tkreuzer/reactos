/*
 * PROJECT:         ReactOS Win32k subsystem
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            subsystems/win32/win32k/ntuser/dce.c
 * PURPOSE:         Window DC management
 * COPYRIGHT:       Copyright 2007 ReactOS Team
 * REFERENCES:      http://blogs.msdn.com/b/oldnewthing/archive/2006/06/01/612970.aspx
 */

/*
    - CS_CLASSDC: If a class has CS_CLASSDC style, a DCE for the class will be
        created the first time a window is created for that class.
    - CS_OWNDC: If a class has CS_OWNDC, and you create a window based on that
        class, it will get it's own DC. This is even true, if you change the
        class style after it. Once it is there it will stay there.

*/

#include <win32k.h>
DBG_DEFAULT_CHANNEL(UserDce);

typedef struct tagDCE
{
    LIST_ENTRY leListLink; // Windows uses struct tagDCE* pdceNext;
    HDC hdc;
    PWND pwndOrg;
    PWND pwndClip;
    PWND pwndRedirect;
    HRGN hrgnClip;
    HRGN hrgnClipPublic;
    HRGN hrgnSavedVis;
    ULONG DCX_flags;
    PTHREADINFO ptiOwner;
    PPROCESSINFO ppiOwner;
    struct tagMONITOR* pMonitor;
} DCE;

/* GLOBALS *******************************************************************/

static LIST_ENTRY leFreeDceListHead;
static LIST_ENTRY leUsedDceListHead;
static LIST_ENTRY leOwnedDceListHead;
static LONG cNumberOfCachedFreeDces;
static LONG cDceCacheSize = 32;
static ULONG MIN_DCE_CACHE_SIZE = 5;
static ULONG MAX_DCE_CACHE_SIZE = 30;


/* FUNCTIONS *****************************************************************/

INIT_FUNCTION
NTSTATUS
NTAPI
InitDCEImpl(VOID)
{
    InitializeListHead(&leFreeDceListHead);
    InitializeListHead(&leUsedDceListHead);
    InitializeListHead(&leOwnedDceListHead);
    return STATUS_SUCCESS;
}

static
VOID
DcepRecalculateFreeCacheSize(
    VOID)
{
    // unimplemented
}

_Check_return_
static
PDCE
DcepAllocateDce(
    VOID)
{
    PDCE pdce;

    /* Allocate the DCE structure */
    pdce = ExAllocatePoolWithTag(PagedPool, sizeof(DCE), USERTAG_DCE);
    if (pdce == NULL)
    {
        ERR("Failed to allocate DCE\n");
        return NULL;
    }

    /// allocate a DC

    return pdce;
}

static
VOID
DcepInitializeDce(
    _Inout_ PDCE pdce,
    _In_ PWND pwndOrg,
    _In_ PWND pwndClip,
    _In_ FLONG flags)
{
    NT_ASSERT(pdce->hdc != NULL);

    pdce->pwndOrg = pwndOrg;
    pdce->pwndClip = pwndClip;
    pdce->pwndRedirect = NULL;
    pdce->hrgnClip = NULL;
    pdce->hrgnClipPublic = NULL;
    pdce->hrgnSavedVis = NULL;
    pdce->DCX_flags = flags;
    pdce->ptiOwner = NULL;
    pdce->ppiOwner = NULL;
    pdce->pMonitor = NULL;

    /* This flag is only for debugging purposes, it's not used otherwise */
    NT_ASSERT((pdce->DCX_flags & DCX_DCEBUSY) == 0);
    pdce->DCX_flags |= DCX_DCEBUSY;
}

_Check_return_
static
PDCE
DcepGetFreeDce(
    VOID)
{
    PLIST_ENTRY ple;
    PDCE pdce;

    /* Check if we have a DCE on the free list */
    if (!IsListEmpty(&leFreeDceListHead))
    {
        /* Remove the top DCE from the free list */
        ple = RemoveHeadList(&leFreeDceListHead);
        pdce = CONTAINING_RECORD(ple, DCE, leListLink);
        cNumberOfCachedFreeDces--;
        NT_ASSERT(cNumberOfCachedFreeDces >= 0);
    }
    else
    {
        /* Nothing free, create a new DCE */
        pdce = DcepAllocateDce();
        if (pdce == NULL)
        {
            ERR("Failed to allocate DCE\n");
            return NULL;
        }
    }

    return pdce;
}

_Check_return_
static
PDCE
DcepGetCachedDce(
    _In_ PWND pwndOwner,
    _In_ PWND pwndClip,
    _In_ FLONG flags)
{
    PDCE pdce;

    /* Get a free DCE either from the cache or new */
    pdce = DcepGetFreeDce();
    if (pdce == NULL)
    {
        ERR("Failed to get DCE\n");
        return NULL;
    }

    DcepInitializeDce(pdce, pwndOwner, pwndClip, flags);

    return pdce;
}

_Check_return_
static
PDCE
DcepGetOwnDce(
    _In_ PWND pwndOwner,
    _In_ PWND pwndClip,
    _In_ FLONG flags)
{
    PLIST_ENTRY ple;
    PDCE pdce;

    NT_ASSERT((flags & DCX_CACHE) == 0);
    NT_ASSERT(pwndOwner->pcls->style & CS_OWNDC);

    /* Loop over the owned DCE list */
    for (ple = leOwnedDceListHead.Flink;
         ple != &leOwnedDceListHead;
         ple = ple->Flink)
    {
        /* Check if this is the windows's own DCE */
        pdce = CONTAINING_RECORD(ple, DCE, leListLink);
        if (pdce->pwndOrg == pwndOwner)
        {
            /* We don't need to do any initialization / cleanup */
            return pdce;
        }
    }

    /* Not found */
    ERR("Could not find owned DCE\n");
    NT_ASSERT(FALSE);
    return NULL;
}

_Check_return_
static
PDCE
DcepGetClassDce(
    _In_ PWND pwnd,
    _In_ PWND pwndClip,
    _In_ FLONG flags)
{
    PDCE pdce;

    NT_ASSERT((flags & DCX_CACHE) == 0);
    NT_ASSERT(pwnd->pcls->style & CS_CLASSDC);

    /* Get the DCE from the class */
    pdce = pwnd->pcls->pdce;
    if (pdce == NULL)
    {
        return NULL;
    }

    return pdce;
}

/*!
    \brief Allocates a new DCE

    \param pwnd - Pointer to the Window for which this DCE is created

    \param dceType - ...
 */
_Check_return_
PDCE
NTAPI
DceAllocDCE(
    _In_opt_ PWND pwnd,
    _In_ DCE_TYPE dceType)
{
    UNREFERENCED_PARAMETER(dceType);

    if (dceType == DCE_WINDOW_DC)
    {
        NT_ASSERT(DcepGetOwnDce(pwnd) == NULL);
    }

    /* Get a free DCE either from the cache or new */
    pdce = DcepGetFreeDce();
    if (pdce == NULL)
    {
        ERR("Failed to get DCE\n");
        return NULL;
    }
#if 0
    /* Get flags from the window style */
    /// check if these need to be erased before
    if (pwnd->style & WS_CLIPCHILDREN)
        flags |= DCX_CLIPCHILDREN;
    if (pwnd->style & WS_CLIPSIBLINGS)
        flags |= DCX_CLIPSIBLINGS;
#endif
    /* Do the generic initialization */
    DcepInitializeDce(pdce, pwnd, pwndClip, DCX_POWNED);

    /* Insert the DC into the owned DCE list */
    InsertHeadList(&leOwnedDceListHead);

    return 0;
}

static
VOID
DcepFreeDce(
    _In_ _Post_invalid_ PDCE pdce)
{
    NT_ASSERT((pdce->DCX_flags & DCX_DCEBUSY) == 0);

    /* Delete the DC */
    /// FIXME: might need to get ownership
    NT_VERIFY(IntGdiDeleteDC(pdce->hdc, TRUE) == TRUE);

    /* Free the DCE allocation */
    ExFreePoolWithTag(pdce, USERTAG_DCE);
}

static
VOID
DcepReleaseDce(
    _In_ _Post_invalid_ PDCE pdce)
{
    NT_ASSERT(pdce->pwndOrg->pcls->pdce != pdce);

    /* Recalculate the size of the free DCE cache */
    DcepRecalculateFreeCacheSize();

    /* Remove the DCE from it's current list */
    RemoveEntryList(&pdce->leListLink);

    /* This flag is only for debugging purposes, it's not used otherwise */
    pdce->DCX_flags &= ~DCX_DCEBUSY;

    /* Check if we want to cache it */
    if (cNumberOfCachedFreeDces < cDceCacheSize)
    {
        /* Is this a process owned DCE? */
        if (pdce->DCX_flags & DCX_POWNED)
        {
            /* Reset owner */
            GreSetDCOwner(pdce->hdc, GDI_OBJ_HMGR_NONE);
            pdce->DCX_flags &= ~DCX_POWNED;
        }

        /* Insert it into the cache list */
        InsertHeadList(&leFreeDceListHead, &pdce->leListLink);
        cNumberOfCachedFreeDces++;
    }
    else
    {
        /* We have enough reserve, free this one completely */
        DcepFreeDce(pdce);
    }
}

VOID
NTAPI
DceFreeThreadDCE(
    _Inout_ PTHREADINFO pti)
{
    __debugbreak();
}

VOID
NTAPI
DceFreeClassDCE(
    _In_ PDCE pdce)
{
    __debugbreak();
}

/*!
    \brief Frees a DCE belonging to a Window
 */
VOID
NTAPI
DceFreeOwnedDCE(
    _In_ PWND pwnd)
{
    PLIST_ENTRY ple;
    PDCE pdce;

    NT_ASSERT(pwnd != NULL);

    /* Loop all DCEs in the owned DCE list */
    for (ple = leOwnedDceListHead.Flink;
         ple != &leOwnedDceListHead;
         ple = ple->Flink)
    {
        /* Get the DCE */
        pdce = CONTAINING_RECORD(ple, DCE, leListLink);

        /* Check if this is our DCE */
        if (pdce->pwndOrg == pwnd)
        {
            /* Release the DCE, potentially moving it to the cache */
            DcepReleaseDce(pdce);
#if DBG
            /* Make sure there are no other DCEs for this WND in the list */
            for (; ple != &leOwnedDceListHead; ple = ple->Flink)
            {
                pdce = CONTAINING_RECORD(ple, DCE, leListLink);
                NT_ASSERT(pdce->pwndOrg != pwnd);
            }
#endif /* DBG */
            break;
        }
    }

    /* Make sure this DCE was actually removed! */
    NT_ASSERT(ple != &leOwnedDceListHead);
}

VOID
NTAPI
DceResetActiveDCEs(
    PWND pwnd)
{
    __debugbreak();
}

/*!

    \remarks The logic regarding flags is mostly taken from wine. Some extra
        handling is taken from our own code. Things have been cleaned up and
        adjusted to fit our own structures and code logic.
 */
HDC
NTAPI
UserGetDCEx(
    _In_opt_ PWND pwnd,
    _In_ HANDLE prgnClip,
    _In_ ULONG flags)
{
    PWND pwndClip;
    PDCE pdce;

    __debugbreak();

    /* Check if a NULL window was passed */
    if (pwnd == NULL)
    {
        /* Use the desktop window */
        pwnd = IntGetThreadDesktopWindow(NULL);
        NT_ASSERT(pwnd != NULL);
    }

    /* Check if the Window is not our own window */
    if (pwnd->head.pti != PsGetCurrentThreadWin32Thread())
    {
        /* Always use cached DCE */
        flags |= DCX_CACHE;
    }

    /* Check if we should use window / class styles */
    if (flags & DCX_USESTYLE)
    {
        /* Remove the flags that we get from the window / class styles */
        flags &= ~(DCX_CLIPCHILDREN | DCX_CLIPSIBLINGS | DCX_PARENTCLIP);

        /* Check the window for WS_CLIPSIBLINGS style */
        if (pwnd->style & WS_CLIPSIBLINGS)
        {
            flags |= DCX_CLIPSIBLINGS;
        }

        /* The following checks are not done for DCX_WINDOW */
        if ((flags & DCX_WINDOW) == 0)
        {
            /* Check the window for WS_CLIPCHILDREN style */
            if (pwnd->style & WS_CLIPCHILDREN)
            {
                /* If the Window is minimized, there are no children to clip */
                if ((pwnd->style & WS_MINIMIZE) == 0)
                {
                    flags |= DCX_CLIPCHILDREN;
                }
            }

            /* Check the class for CS_PARENTDC style */
            if (pwnd->pcls->style & CS_PARENTDC)
            {
                flags |= DCX_PARENTCLIP;
            }

            /* Check if the class has neither CS_OWNDC nor CS_CLASSDC */
            if (((pwnd->pcls->style & CS_OWNDC) == 0) &&
                ((pwnd->pcls->style & CS_CLASSDC) == 0))
            {
                /* Always use the cache */
                flags |= DCX_CACHE;
            }
        }
    }

    /* All of these always use a cached DCE (even if they are overwritten) */
    if (flags & (DCX_WINDOW | DCX_NOCLIPCHILDREN | DCX_PARENTCLIP))
    {
        flags |= DCX_CACHE;
    }

    if (flags & DCX_WINDOW)
    {
        flags &= ~DCX_CLIPCHILDREN;
    }

    /* Check for DCX_NOCLIPCHILDREN */
    if (flags & DCX_NOCLIPCHILDREN)
    {
        /* This does not go together with DCX_CLIPCHILDREN or DCX_PARENTCLIP */
        flags &= ~(DCX_CLIPCHILDREN | DCX_PARENTCLIP);
    }

    /* When DCX_CLIPSIBLINGS or DCX_CLIPCHILDREN is specified,
       remove DCX_PARENTCLIP */
    if (flags & (DCX_CLIPSIBLINGS | DCX_CLIPCHILDREN))
    {
        flags &= ~DCX_PARENTCLIP;
    }

    /* Check for DCX_PARENTCLIP */
    if (flags & DCX_PARENTCLIP)
    {
        /* Use the parent window for clipping */
        pwndClip = pwnd->spwndParent;
        if (pwndClip == NULL)
        {
            /* There is no parent, use the desktop window */
            pwndClip = IntGetThreadDesktopWindow(NULL);
        }

        /* Check if the parent window has WS_CLIPCHILDREN */
        if (pwndClip->style & WS_CLIPCHILDREN)
        {
            /* Revert back to the window itself for clipping */
            pwndClip = pwnd;
        }
    }
    else
    {
        /* Use the window itself for clipping */
        pwndClip = pwnd;
    }


    if (flags & DCX_LAYEREDWIN)
    {
        ERR("DCX_LAYEREDWIN is not implemented!\n");
        NT_ASSERT(FALSE);
    }

    /* Check what type we want. Cache has highest precedence */
    if (flags & DCX_CACHE)
    {
        /* Get a DCE from the cache */
        pdce = DcepGetCachedDce(pwnd);
        if (pdce == NULL)
        {
            ERR("Failed to get a DC, out of memory?\n");
            return NULL;
        }
    }
    else
    {
        /* Otherwise, check for an own DC. Yes, we do this even, if we do not
           have the flag set! */
        pdce = DcepGetOwnDce(pwnd, pwndClip, flags);
        if (pdce == NULL)
        {
            /* No own DCE, use the class DCE, if any */
            pdce = pwnd->plcls->pdce;
        }

        if (pdce == NULL)
        {
            ERR("Cannot get a DC, no cache, no own or class DC\n");
            return NULL;
        }
    }

    /* Return the DC handle */
    return pdce->hdc;
}

HDC
NTAPI
UserGetWindowDC(
    _In_ PWND pwnd)
{
    return UserGetDCEx(pwnd, NULL, DCX_USESTYLE | DCX_WINDOW);
}

INT
NTAPI
UserReleaseDC(
    _Inout_ PWND pwnd,
    _In_ HDC hdc,
    _In_ BOOL bEndPaint)
{
    __debugbreak();
    return -1;
}

HWND
NTAPI
UserGethWnd(
    HDC hdc,
    PWNDOBJ *pwndo)
{
    __debugbreak();
    return 0;
}

HWND
NTAPI
IntWindowFromDC(
    _In_ HDC hdc)
{
    __debugbreak();
    return 0;
}

HDC
APIENTRY
NtUserGetDCEx(
    _In_opt_ HWND hwnd,
    _In_ HANDLE hrgnClip,
    _In_ ULONG flags)
{
    PWND pwnd = NULL;
    HDC hdc;

    TRACE("Enter NtUserGetDCEx: hwnd %p, hrgnClip %p, flags %x.\n",
          hwnd, hrgnClip, flags);

    /* Acquire global USER lock */
    UserEnterExclusive();

    /* Check if the caller passed a window handle */
    if (hwnd != NULL)
    {
        /* Get the window pointer */
        pwnd = UserGetWindowObject(hwnd);
        if (pwnd == NULL)
        {
            ERR("Invalid window handle: %p\n", hwnd);
            hdc = NULL;
            goto Leave;
        }
    }
    else
    {
        /* Use NULL and let UserGetDCEx handle it */
        pwnd = NULL;
    }

    /* Call the internal function */
    hdc = UserGetDCEx(pwnd, hrgnClip, flags);

Leave:
    TRACE("Leave NtUserGetDCEx, hdc = %p\n", hdc);
    UserLeave();

    return hdc;
}

HDC
APIENTRY
NtUserGetDC(
    _In_opt_ HWND hwnd)
{
    ULONG flags;

    flags = (hwnd == NULL) ? DCX_CACHE | DCX_WINDOW : DCX_USESTYLE;
    return NtUserGetDCEx(hwnd, NULL, flags);
}

HDC
APIENTRY
NtUserGetWindowDC(
    HWND hwnd)
{
    return NtUserGetDCEx(hwnd, NULL, DCX_USESTYLE | DCX_WINDOW);
}



/*!
 * Select logical palette into device context.
 * \param	hDC 				handle to the device context
 * \param	hpal				handle to the palette
 * \param	ForceBackground 	If this value is FALSE the logical palette will be copied to the device palette only when the applicatioon
 * 								is in the foreground. If this value is TRUE then map the colors in the logical palette to the device
 * 								palette colors in the best way.
 * \return	old palette
 *
 * \todo	implement ForceBackground == TRUE
*/
HPALETTE
APIENTRY
NtUserSelectPalette(HDC  hDC,
              HPALETTE  hpal,
       BOOL  ForceBackground)
{
    HPALETTE oldPal;
    UserEnterExclusive();
    // Implement window checks
    oldPal = GdiSelectPalette( hDC, hpal, ForceBackground);
    UserLeave();
    return oldPal;
}

#pragma once

#include "window.h"
#include <include/win32.h>

VOID FASTCALL IntIncrementSequenceNumber(VOID);

typedef struct _ClipboardChainElement
{
    PWINDOW_OBJECT                 window;
    struct _ClipboardChainElement *next;
} CLIPBOARDCHAINELEMENT, *PCLIPBOARDCHAINELEMENT;

typedef struct _ClipboardElement
{
    UINT                        format;
    HANDLE                      hData;
    DWORD                       size;   // data may be delayed o synth render
    struct _ClipboardElement   *next;
} CLIPBOARDELEMENT, *PCLIPBOARDELEMENT;

typedef struct _CLIPBOARDSYSTEM
{
    PTHREADINFO     ClipboardThread;
    PTHREADINFO     ClipboardOwnerThread;
    PWINDOW_OBJECT  ClipboardWindow;
    PWINDOW_OBJECT  ClipboardViewerWindow;
    PWINDOW_OBJECT  ClipboardOwnerWindow;
    BOOL            sendDrawClipboardMsg;
    BOOL            recentlySetClipboard;
    BOOL            delayedRender;
    UINT            lastEnumClipboardFormats;
    DWORD           ClipboardSequenceNumber;

    PCLIPBOARDCHAINELEMENT WindowsChain;
    PCLIPBOARDELEMENT      ClipboardData;

    PCHAR synthesizedData;
    DWORD synthesizedDataSize;

} CLIPBOARDSYSTEM, *PCLIPBOARDSYSTEM;

VOID FASTCALL
IntClipboardFreeWindow(PWINDOW_OBJECT window);

UINT APIENTRY IntEnumClipboardFormats(UINT format);

/*
UINT FASTCALL
IntEnumClipboardFormats(UINT format);
*/
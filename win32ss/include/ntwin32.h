
#pragma once

/* These are opaque for user mode */
typedef struct _PROCESSINFO *PPROCESSINFO;
typedef struct _THREADINFO *PTHREADINFO;

typedef struct _W32CLIENTINFO
{
    ULONG CI_flags;
    ULONG cSpins;
    ULONG ulWindowsVersion;
    ULONG ulAppCompatFlags;
    ULONG ulAppCompatFlags2;
    ULONG W32ClientInfo[57];
} W32CLIENTINFO, *PW32CLIENTINFO;

#define NB_HOOKS (WH_MAXHOOK - WH_MINHOOK + 1)

#define CTI_THREADSYSLOCK 0x0001
#define CTI_INSENDMESSAGE 0x0002

typedef struct _CLIENTTHREADINFO
{
    DWORD CTI_flags;
    WORD fsChangeBits;
    WORD fsWakeBits;
    WORD fsWakeBitsJournal;
    WORD fsWakeMask;
    ULONG timeLastRead; // Last time the message queue was read.
    DWORD dwcPumpHook;
} CLIENTTHREADINFO, *PCLIENTTHREADINFO;

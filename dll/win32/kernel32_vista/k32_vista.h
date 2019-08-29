
#pragma once

#undef _WIN32_WINNT
#undef WINVER
#define _WIN32_WINNT 0x600
#define WINVER 0x600

/* PSDK/NDK Headers */
#define WIN32_NO_STATUS
#include <windef.h>
#include <winbase.h>

#include <ndk/kefuncs.h>
#include <ndk/psfuncs.h>
#include <ndk/rtlfuncs.h>


/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Hardware Abstraction Layer
 * FILE:            hal/halx86/include/hal.h
 * PURPOSE:         HAL Header
 * PROGRAMMER:      Alex Ionescu (alex@relsoft.net)
 */

#ifndef _HAL_PCH_
#define _HAL_PCH_

/* INCLUDES ******************************************************************/

/* C Headers */
#include <stdio.h>

/* WDK HAL Compilation hack */
#include <excpt.h>
#include <ntdef.h>
#ifndef _MINIHAL_
#undef NTSYSAPI
#define NTSYSAPI __declspec(dllimport)
#else
#undef NTSYSAPI
#define NTSYSAPI
#endif

/* IFS/DDK/NDK Headers */
#include <xdk/xdk.h>

#include <arc/arc.h>

/* Internal shared PCI and ACPI header */
#include <drivers/pci/pci.h>
#include <drivers/acpi/acpi.h>

/* Internal kernel headers */
#define KeGetCurrentThread _KeGetCurrentThread
#ifdef _M_AMD64
#include <reactos/arch/amd64/arch_amd64.h>
#else
#error add me
#endif

#include <hackstuff.h>

#define TAG_HAL    ' laH'
#define TAG_BUS_HANDLER 'BusH'

/* Internal HAL Headers */
#include "bus.h"
#include "halirq.h"
#include "haldma.h"
#include "halp.h"
#include "mps.h"
#include "halacpi.h"

#endif /* _HAL_PCH_ */

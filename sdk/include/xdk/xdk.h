

#pragma once

/* Basic headers */
#define NT_INCLUDED
#include <excpt.h>
#include <ntdef.h>
#include <ntstatus.h>
#include <ntiologc.h>
#include <ntimage.h>
#include <mce.h>
#include <ntnls.h>
#include <guiddef.h>
#include <dpfilter.h>
#include "intrin.h"
#include <specstrings.h>

#ifdef _MAC
#ifndef _INC_STRING
#include <string.h>
#endif /* _INC_STRING */
#else
#include <string.h>
#endif /* _MAC */

#define IN
#define OUT
#define OPTIONAL

#if !defined(_NTHALDLL_) && !defined(_BLDR_)
#define NTHALAPI DECLSPEC_IMPORT
#else
#define NTHALAPI
#endif

#if !defined(_NTOSKRNL_) && !defined(_BLDR_)
#define NTKERNELAPI DECLSPEC_IMPORT
#else
#define NTKERNELAPI
#endif

#if defined(_X86_) && !defined(_NTHAL_)
#define _DECL_HAL_KE_IMPORT  DECLSPEC_IMPORT
#elif defined(_X86_)
#define _DECL_HAL_KE_IMPORT
#else
#define _DECL_HAL_KE_IMPORT NTKERNELAPI
#endif

#if defined(_WIN64)
#define POINTER_ALIGNMENT DECLSPEC_ALIGN(8)
#else
#define POINTER_ALIGNMENT
#endif

/* Helper macro to enable gcc's extension.  */
#ifndef __GNU_EXTENSION
#ifdef __GNUC__
#define __GNU_EXTENSION __extension__
#else
#define __GNU_EXTENSION
#endif
#endif

#if defined(_MSC_VER)

/* Disable some warnings */
#pragma warning(disable:4115) /* Named type definition in parentheses */
#pragma warning(disable:4201) /* Nameless unions and structs */
#pragma warning(disable:4214) /* Bit fields of other types than int */
#pragma warning(disable:4820) /* Padding added, due to alignemnet requirement */

/* Indicate if #pragma alloc_text() is supported */
#if defined(_M_IX86) || defined(_M_AMD64) || defined(_M_IA64)
#define ALLOC_PRAGMA 1
#endif

/* Indicate if #pragma data_seg() is supported */
#if defined(_M_IX86) || defined(_M_AMD64)
#define ALLOC_DATA_PRAGMA 1
#endif

#endif /* _MSC_VER */

#if defined(_WIN64)
#if !defined(USE_DMA_MACROS) && !defined(_NTHAL_)
#define USE_DMA_MACROS
#endif
#if !defined(NO_LEGACY_DRIVERS) && !defined(__REACTOS__)
#define NO_LEGACY_DRIVERS
#endif
#endif /* defined(_WIN64) */

#ifdef _MSC_VER
#define DEFINE_GUIDEX(name) EXTERN_C const CDECL GUID name
#else
#define DEFINE_GUIDEX(name) EXTERN_C const GUID name
#endif /* !_MSC_VER */

#define STATICGUIDOF(guid) STATIC_##guid
#define __IID_ALIGNED__

#define SYSTEM_PAGE_PRIORITY_BITS       3
#define SYSTEM_PAGE_PRIORITY_LEVELS     (1 << SYSTEM_PAGE_PRIORITY_BITS)

typedef GUID UUID;
typedef GUID UOW, *PUOW;
typedef GUID *PGUID;

typedef struct _PEB* PPEB;
typedef struct _HEAP_LOCK *PHEAP_LOCK;
typedef struct _EXCEPTION_RECORD *PEXCEPTION_RECORD;
typedef struct _EXCEPTION_REGISTRATION_RECORD *PEXCEPTION_REGISTRATION_RECORD;
typedef struct _RTL_ATOM_TABLE *PRTL_ATOM_TABLE;
typedef struct _RTL_ATOM_TABLE_ENTRY *PRTL_ATOM_TABLE_ENTRY;
typedef struct _LDR_RESOURCE_INFO *PLDR_RESOURCE_INFO;

/* Forward declarations */
struct _IRP;
struct _MDL;
struct _KAPC;
struct _KDPC;
struct _FILE_OBJECT;
struct _DMA_ADAPTER;
struct _DEVICE_OBJECT;
struct _DRIVER_OBJECT;
struct _IO_STATUS_BLOCK;
struct _DEVICE_DESCRIPTION;
struct _SCATTER_GATHER_LIST;
struct _DRIVE_LAYOUT_INFORMATION;
struct _COMPRESSED_DATA_INFO;
struct _IO_RESOURCE_DESCRIPTOR;

/* Structures not exposed to drivers */
typedef struct _OBJECT_TYPE *POBJECT_TYPE;
typedef struct _HAL_DISPATCH_TABLE *PHAL_DISPATCH_TABLE;
typedef struct _HAL_PRIVATE_DISPATCH_TABLE *PHAL_PRIVATE_DISPATCH_TABLE;
typedef struct _CALLBACK_OBJECT *PCALLBACK_OBJECT;
typedef struct _EPROCESS *PEPROCESS;
typedef struct _ETHREAD *PETHREAD;
typedef struct _IO_TIMER *PIO_TIMER;
typedef struct _KINTERRUPT *PKINTERRUPT;
typedef struct _KPROCESS *PKPROCESS;
typedef struct _KTHREAD *PKTHREAD, *PRKTHREAD;
typedef struct _CONTEXT *PCONTEXT;
typedef struct _FILE_OBJECT *PFILE_OBJECT;
typedef struct _MDL *PMDL;
typedef struct _BUS_HANDLER *PBUS_HANDLER;

#if defined(USE_DMA_MACROS) && !defined(_NTHAL_)
typedef struct _DMA_ADAPTER *PADAPTER_OBJECT;
#elif defined(_WDM_INCLUDED_)
typedef struct _DMA_ADAPTER *PADAPTER_OBJECT;
#else
typedef struct _ADAPTER_OBJECT *PADAPTER_OBJECT;
#endif


#define $if(x)
#define $endif(x)

/* Public interface */
#include <xdk/interlocked.h>
#include <xdk/rtltypes.h>
#include <xdk/ketypes.h>
#if defined(_M_IX86)
#include <xdk/x86/ke.h>
#elif defined(_M_AMD64)
#include <xdk/amd64/ke.h>
#elif defined(_M_IA64)
#include <xdk/ia64/ke.h>
#elif defined(_M_PPC)
#include <xdk/ppc/ke.h>
#elif defined(_M_MIPS)
#include <xdk/mips/ke.h>
#elif defined(_M_ARM)
#include <xdk/arm/ke.h>
#else
#error Unknown Architecture
#endif

#include <xdk/extypes.h>
#include <xdk/setypes.h>
#include <xdk/potypes.h>
#include <xdk/cmtypes.h>
#include <xdk/iotypes.h>
#include <xdk/haltypes.h>
#include <xdk/kdtypes.h>
#include <xdk/mmtypes.h>
#include <xdk/obtypes.h>
#include <xdk/pstypes.h>
#include <xdk/wmitypes.h>
#include <xdk/ldrtypes.h>

#if defined(_M_IX86)
#include <xdk/x86/mm.h>
#elif defined(_M_AMD64)
#include <xdk/amd64/mm.h>
#endif

#include <xdk/rtlfuncs.h>
#include <xdk/ldrfuncs.h>
#include <xdk/kefuncs.h>
#include <xdk/mmfuncs.h>
#include <xdk/sefuncs.h>
#include <xdk/cmfuncs.h>
#include <xdk/iofuncs.h>
#include <xdk/pofuncs.h>
#include <xdk/exfuncs.h>
#include <xdk/obfuncs.h>
#include <xdk/psfuncs.h>
#include <xdk/wmifuncs.h>
#include <xdk/kdfuncs.h>
#include <xdk/halfuncs.h>
#include <xdk/nttmapi.h>
#include <xdk/zwfuncs.h>


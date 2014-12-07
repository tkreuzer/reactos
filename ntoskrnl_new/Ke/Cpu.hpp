
#pragma once

#include "Kep.hpp"

typedef struct _KPRCB *PKPRCB;
typedef struct _KFLOATING_SAVE *PKFLOATING_SAVE;
typedef struct _KIO_ACCESS_MAP *PKIO_ACCESS_MAP;
typedef struct _XSTATE_SAVE *PXSTATE_SAVE;

typedef
_IRQL_requires_same_
_Function_class_(KIPI_BROADCAST_WORKER)
_IRQL_requires_(IPI_LEVEL)
ULONG_PTR
NTAPI
KIPI_BROADCAST_WORKER (
    _In_ ULONG_PTR Argument);
typedef KIPI_BROADCAST_WORKER *PKIPI_BROADCAST_WORKER;


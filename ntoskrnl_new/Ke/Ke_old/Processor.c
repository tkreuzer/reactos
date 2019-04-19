

#include <ntoskrnl.h>
#include "Ke_internal.h"

VOID
KiCpuId()
{
    __debugbreak();
}


VOID
NTAPI
KeGetXSaveFeatureFlags()
{
    __debugbreak();
}

NTSTATUS
NTAPI
KeSaveExtendedProcessorState(
  __in   ULONG64 Mask,
  __out  PXSTATE_SAVE XStateSave)
{
    __debugbreak();
    return 0;
}

VOID
NTAPI
KeRestoreExtendedProcessorState(
  __in  PXSTATE_SAVE XStateSave)
{
    __debugbreak();
}

#undef KeSaveFloatingPointState
NTSTATUS
NTAPI
KeSaveFloatingPointState(
  __out  PKFLOATING_SAVE FloatSave)
{
#ifdef _M_IX86
    __debugbreak();
    return STATUS_UNSUCCESSFUL;
#else
    return STATUS_SUCCESS;
#endif
}

#undef KeRestoreFloatingPointState
NTSTATUS
NTAPI
KeRestoreFloatingPointState(
  __in  PKFLOATING_SAVE FloatSave)
{
#ifdef _M_IX86
    __debugbreak();
    return STATUS_UNSUCCESSFUL;
#else
    return STATUS_SUCCESS;
#endif
}

VOID
__cdecl
KeSaveStateForHibernate(
    IN PKPROCESSOR_STATE State)
{
    __debugbreak();
}

VOID
NTAPI
KeFlushEntireTb(
    IN BOOLEAN Invalid,
    IN BOOLEAN AllProcessors)
{
    __debugbreak();
}


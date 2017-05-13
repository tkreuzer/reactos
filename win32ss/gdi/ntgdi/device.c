/*
 * COPYRIGHT:         See COPYING in the top level directory
 * PROJECT:           ReactOS kernel
 * PURPOSE:           Functions for creation and destruction of DCs
 * FILE:              win32ss/gdi/ntgdi/device.c
 * PROGRAMER:         Timo Kreuzer (timo.kreuzer@rectos.org)
 */

#include <win32k.h>

#define NDEBUG
#include <debug.h>

PDC defaultDCstate = NULL;

VOID FASTCALL
IntGdiReferencePdev(PPDEVOBJ ppdev)
{
    UNIMPLEMENTED;
}

VOID FASTCALL
IntGdiUnreferencePdev(PPDEVOBJ ppdev, DWORD CleanUpType)
{
    UNIMPLEMENTED;
}

BOOL FASTCALL
IntCreatePrimarySurface(VOID)
{
    /* Create surface */
    PDEVOBJ_pSurface(gpmdev->ppdevGlobal);

    DPRINT("IntCreatePrimarySurface, ppdevGlobal=%p, ppdevGlobal->pSurface = %p\n",
        gpmdev->ppdevGlobal, gpmdev->ppdevGlobal->pSurface);

    // Init Primary Displays Device Capabilities.
    PDEVOBJ_vGetDeviceCaps(gpmdev->ppdevGlobal, &GdiHandleTable->DevCaps);

    return TRUE;
}

VOID FASTCALL
IntDestroyPrimarySurface(VOID)
{
    UNIMPLEMENTED;
}

HDC APIENTRY
NtGdiCreateDC(PUNICODE_STRING Driver,
              PUNICODE_STRING Device,
              PUNICODE_STRING Output,
              CONST PDEVMODEW InitData)
{
  UNICODE_STRING SafeDriver, SafeDevice;
  DEVMODEW SafeInitData;
  HDC Ret;
  NTSTATUS Status = STATUS_SUCCESS;

  if(InitData)
  {
    _SEH_TRY
    {
      ProbeForRead(InitData,
                   sizeof(DEVMODEW),
                   1);
      RtlCopyMemory(&SafeInitData,
                    InitData,
                    sizeof(DEVMODEW));
    }
    _SEH_HANDLE
    {
      Status = _SEH_GetExceptionCode();
    }
    _SEH_END;

    if(!NT_SUCCESS(Status))
    {
      SetLastNtError(Status);
      return NULL;
    }
    /* FIXME - InitData can have some more bytes! */
  }

  if(Driver)
  {
    Status = IntSafeCopyUnicodeString(&SafeDriver, Driver);
    if(!NT_SUCCESS(Status))
    {
      SetLastNtError(Status);
      return NULL;
    }
  }

  if(Device)
  {
    Status = IntSafeCopyUnicodeString(&SafeDevice, Device);
    if(!NT_SUCCESS(Status))
    {
      /* FIXME workaround for a real bug */
      // RtlFreeUnicodeString(&SafeDriver);
      // SetLastNtError(Status);
      // DPRINT1("fail3\n");
      // return NULL;
      Device = NULL;
    }
  }

  Ret = IntGdiCreateDC(NULL == Driver ? NULL : &SafeDriver,
                       NULL == Device ? NULL : &SafeDevice, NULL,
                       NULL == InitData ? NULL : &SafeInitData, FALSE);

  return Ret;
}

HDC STDCALL
NtGdiCreateIC(PUNICODE_STRING Driver,
              PUNICODE_STRING Device,
              PUNICODE_STRING Output,
              CONST PDEVMODEW InitData)
{
  UNICODE_STRING SafeDriver, SafeDevice;
  DEVMODEW SafeInitData;
  HDC Ret;
  NTSTATUS Status = STATUS_SUCCESS;

  if(InitData)
  {
    _SEH_TRY
    {
      ProbeForRead(InitData,
                   sizeof(DEVMODEW),
                   1);
      RtlCopyMemory(&SafeInitData,
                    InitData,
                    sizeof(DEVMODEW));
    }
    _SEH_HANDLE
    {
      Status = _SEH_GetExceptionCode();
    }
    _SEH_END;
    if(!NT_SUCCESS(Status))
    {
      SetLastNtError(Status);
      return NULL;
    }
    /* FIXME - InitData can have some more bytes! */
  }

  if(Driver)
  {
    Status = IntSafeCopyUnicodeString(&SafeDriver, Driver);
    if(!NT_SUCCESS(Status))
    {
      SetLastNtError(Status);
      return NULL;
    }
  }

  if(Device)
  {
    Status = IntSafeCopyUnicodeString(&SafeDevice, Device);
    if(!NT_SUCCESS(Status))
    {
      RtlFreeUnicodeString(&SafeDriver);
      SetLastNtError(Status);
      return NULL;
    }
  }

  Ret = IntGdiCreateDC(NULL == Driver ? NULL : &SafeDriver,
                       NULL == Device ? NULL : &SafeDevice, NULL,
                       NULL == InitData ? NULL : &SafeInitData, TRUE);

  return Ret;
}

PPDEVOBJ FASTCALL
IntEnumHDev(VOID)
{
// I guess we will soon have more than one primary surface.
// This will do for now.
    return gpmdev->ppdevGlobal;
}


INT
APIENTRY
NtGdiDrawEscape(
    IN HDC hdc,
    IN INT iEsc,
    IN INT cjIn,
    IN OPTIONAL LPSTR pjIn)
{
    UNIMPLEMENTED;
    return 0;
}



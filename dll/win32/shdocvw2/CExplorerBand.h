
#pragma once

#include <atlbase.h>
#include <atlcom.h>

DEFINE_GUID(CLSID_ExplorerBand, 0xEFA24E64, 0xB078, 0x11D0, 0x89, 0xE4, 0x00, 0xC0, 0x4F, 0xC9, 0xE2, 0x6E);

class CExplorerBand
    : public CComCoClass<CExplorerBand, &CLSID_ExplorerBand>
    , public CComObjectRootEx<CComMultiThreadModelNoCS>
{
public:
    CExplorerBand();

	static HRESULT WINAPI UpdateRegistry2(_In_ BOOL /*bRegister*/) throw()\
	{return S_OK;}

    DECLARE_REGISTRY_RESOURCEID(139)
    DECLARE_NOT_AGGREGATABLE(CExplorerBand)

    BEGIN_COM_MAP(CExplorerBand)

    END_COM_MAP()

};

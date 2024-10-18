
#include "CExplorerBand.h"

DEFINE_GUID(DIID_DWebBrowserEvents, 0xeab22ac2, 0x30c1, 0x11cf, 0xa7,0xeb, 0x00,0x00,0xc0,0x5b,0xae,0x0b);

CExplorerBand::CExplorerBand()
{
}

void DoSomething(void)
{
    CComPtr<IUnknown> browserService;
    AtlAdvise(browserService, nullptr, DIID_DWebBrowserEvents, nullptr);
}

/*
 * Copyright 2008-2009 Jacek Caban for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#define COBJMACROS
#define CONST_VTABLE

#include <wine/test.h>
#include <stdarg.h>
#include <stdio.h>

#include "windef.h"
#include "winbase.h"
#include "ole2.h"
#include "wininet.h"
#include "docobj.h"
#include "dispex.h"
#include "hlink.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "initguid.h"
#include "activscp.h"
#include "activdbg.h"
#include "objsafe.h"
#include "mshtmdid.h"
#include "mshtml_test.h"

DEFINE_GUID(CLSID_IdentityUnmarshal,0x0000001b,0x0000,0x0000,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

/* Defined as extern in urlmon.idl, but not exported by uuid.lib */
const GUID GUID_CUSTOM_CONFIRMOBJECTSAFETY =
    {0x10200490,0xfa38,0x11d0,{0xac,0x0e,0x00,0xa0,0xc9,0xf,0xff,0xc0}};

#ifdef _WIN64

#define CTXARG_T DWORDLONG
#define IActiveScriptParseVtbl IActiveScriptParse64Vtbl
#define IActiveScriptParseProcedure2Vtbl IActiveScriptParseProcedure2_64Vtbl

#else

#define CTXARG_T DWORD
#define IActiveScriptParseVtbl IActiveScriptParse32Vtbl
#define IActiveScriptParseProcedure2Vtbl IActiveScriptParseProcedure2_32Vtbl

#endif

#define DEFINE_EXPECT(func) \
    static BOOL expect_ ## func = FALSE, called_ ## func = FALSE

#define SET_EXPECT(func) \
    do { called_ ## func = FALSE; expect_ ## func = TRUE; } while(0)

#define CHECK_EXPECT2(func) \
    do { \
        ok(expect_ ##func, "unexpected call " #func "\n"); \
        called_ ## func = TRUE; \
    }while(0)

#define CHECK_EXPECT(func) \
    do { \
        CHECK_EXPECT2(func); \
        expect_ ## func = FALSE; \
    }while(0)

#define CHECK_CALLED(func) \
    do { \
        ok(called_ ## func, "expected " #func "\n"); \
        expect_ ## func = called_ ## func = FALSE; \
    }while(0)

#define CHECK_CALLED_BROKEN(func) \
    do { \
        ok(called_ ## func || broken(!called_ ## func), "expected " #func "\n"); \
        expect_ ## func = called_ ## func = FALSE; \
    }while(0)

#define CHECK_NOT_CALLED(func) \
    do { \
        ok(!called_ ## func, "unexpected " #func "\n"); \
        expect_ ## func = called_ ## func = FALSE; \
    }while(0)

#define CLEAR_CALLED(func) \
    expect_ ## func = called_ ## func = FALSE


DEFINE_EXPECT(CreateInstance);
DEFINE_EXPECT(GetInterfaceSafetyOptions);
DEFINE_EXPECT(SetInterfaceSafetyOptions);
DEFINE_EXPECT(InitNew);
DEFINE_EXPECT(Close);
DEFINE_EXPECT(SetProperty_HACK_TRIDENTEVENTSINK);
DEFINE_EXPECT(SetProperty_INVOKEVERSIONING);
DEFINE_EXPECT(SetProperty_ABBREVIATE_GLOBALNAME_RESOLUTION);
DEFINE_EXPECT(SetScriptSite);
DEFINE_EXPECT(GetScriptState);
DEFINE_EXPECT(SetScriptState_STARTED);
DEFINE_EXPECT(SetScriptState_CONNECTED);
DEFINE_EXPECT(SetScriptState_DISCONNECTED);
DEFINE_EXPECT(AddNamedItem);
DEFINE_EXPECT(ParseScriptText);
DEFINE_EXPECT(GetScriptDispatch);
DEFINE_EXPECT(funcDisp);
DEFINE_EXPECT(script_divid_d);
DEFINE_EXPECT(script_testprop_d);
DEFINE_EXPECT(script_testprop_i);
DEFINE_EXPECT(script_testprop2_d);
DEFINE_EXPECT(AXQueryInterface_IActiveScript);
DEFINE_EXPECT(AXQueryInterface_IObjectSafety);
DEFINE_EXPECT(AXGetInterfaceSafetyOptions);
DEFINE_EXPECT(AXSetInterfaceSafetyOptions_IDispatch);
DEFINE_EXPECT(AXSetInterfaceSafetyOptions_IDispatchEx);
DEFINE_EXPECT(external_success);

#define TESTSCRIPT_CLSID "{178fc163-f585-4e24-9c13-4bb7faf80746}"
#define TESTACTIVEX_CLSID "{178fc163-f585-4e24-9c13-4bb7faf80646}"

#define DISPID_SCRIPT_TESTPROP   0x100000
#define DISPID_SCRIPT_TESTPROP2  0x100001

#define DISPID_EXTERNAL_OK             0x300000
#define DISPID_EXTERNAL_TRACE          0x300001
#define DISPID_EXTERNAL_REPORTSUCCESS  0x300002

static const GUID CLSID_TestScript =
    {0x178fc163,0xf585,0x4e24,{0x9c,0x13,0x4b,0xb7,0xfa,0xf8,0x07,0x46}};
static const GUID CLSID_TestActiveX =
    {0x178fc163,0xf585,0x4e24,{0x9c,0x13,0x4b,0xb7,0xfa,0xf8,0x06,0x46}};

static IHTMLDocument2 *notif_doc;
static IOleDocumentView *view;
static IDispatchEx *window_dispex;
static BOOL doc_complete;
static IDispatch *script_disp;
static BOOL ax_objsafe;
static HWND container_hwnd;
static HRESULT ax_getopt_hres = S_OK, ax_setopt_dispex_hres = S_OK, ax_setopt_disp_hres = S_OK;
static DWORD ax_setopt;

static const char *debugstr_guid(REFIID riid)
{
    static char buf[50];

    sprintf(buf, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
            riid->Data1, riid->Data2, riid->Data3, riid->Data4[0],
            riid->Data4[1], riid->Data4[2], riid->Data4[3], riid->Data4[4],
            riid->Data4[5], riid->Data4[6], riid->Data4[7]);

    return buf;
}

static int strcmp_wa(LPCWSTR strw, const char *stra)
{
    CHAR buf[512];
    WideCharToMultiByte(CP_ACP, 0, strw, -1, buf, sizeof(buf), NULL, NULL);
    return lstrcmpA(stra, buf);
}

static BSTR a2bstr(const char *str)
{
    BSTR ret;
    int len;

    len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    ret = SysAllocStringLen(NULL, len);
    MultiByteToWideChar(CP_ACP, 0, str, -1, ret, len);

    return ret;
}

static BOOL init_key(const char *key_name, const char *def_value, BOOL init)
{
    HKEY hkey;
    DWORD res;

    if(!init) {
        RegDeleteKey(HKEY_CLASSES_ROOT, key_name);
        return TRUE;
    }

    res = RegCreateKeyA(HKEY_CLASSES_ROOT, key_name, &hkey);
    if(res != ERROR_SUCCESS)
        return FALSE;

    if(def_value)
        res = RegSetValueA(hkey, NULL, REG_SZ, def_value, strlen(def_value));

    RegCloseKey(hkey);

    return res == ERROR_SUCCESS;
}

static HRESULT WINAPI PropertyNotifySink_QueryInterface(IPropertyNotifySink *iface,
        REFIID riid, void**ppv)
{
    if(IsEqualGUID(&IID_IPropertyNotifySink, riid)) {
        *ppv = iface;
        return S_OK;
    }

    return E_NOINTERFACE;
}

static ULONG WINAPI PropertyNotifySink_AddRef(IPropertyNotifySink *iface)
{
    return 2;
}

static ULONG WINAPI PropertyNotifySink_Release(IPropertyNotifySink *iface)
{
    return 1;
}

static HRESULT WINAPI PropertyNotifySink_OnChanged(IPropertyNotifySink *iface, DISPID dispID)
{
    if(dispID == DISPID_READYSTATE){
        BSTR state;
        HRESULT hres;

        static const WCHAR completeW[] = {'c','o','m','p','l','e','t','e',0};

        hres = IHTMLDocument2_get_readyState(notif_doc, &state);
        ok(hres == S_OK, "get_readyState failed: %08x\n", hres);

        if(!lstrcmpW(state, completeW))
            doc_complete = TRUE;

        SysFreeString(state);
    }

    return S_OK;
}

static HRESULT WINAPI PropertyNotifySink_OnRequestEdit(IPropertyNotifySink *iface, DISPID dispID)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static IPropertyNotifySinkVtbl PropertyNotifySinkVtbl = {
    PropertyNotifySink_QueryInterface,
    PropertyNotifySink_AddRef,
    PropertyNotifySink_Release,
    PropertyNotifySink_OnChanged,
    PropertyNotifySink_OnRequestEdit
};

static IPropertyNotifySink PropertyNotifySink = { &PropertyNotifySinkVtbl };

static HRESULT WINAPI DispatchEx_QueryInterface(IDispatchEx *iface, REFIID riid, void **ppv)
{
    *ppv = NULL;

    if(IsEqualGUID(riid, &IID_IUnknown)
       || IsEqualGUID(riid, &IID_IDispatch)
       || IsEqualGUID(riid, &IID_IDispatchEx))
        *ppv = iface;
    else
        return E_NOINTERFACE;

    return S_OK;
}

static ULONG WINAPI DispatchEx_AddRef(IDispatchEx *iface)
{
    return 2;
}

static ULONG WINAPI DispatchEx_Release(IDispatchEx *iface)
{
    return 1;
}

static HRESULT WINAPI DispatchEx_GetTypeInfoCount(IDispatchEx *iface, UINT *pctinfo)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_GetTypeInfo(IDispatchEx *iface, UINT iTInfo,
                                              LCID lcid, ITypeInfo **ppTInfo)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_GetIDsOfNames(IDispatchEx *iface, REFIID riid,
                                                LPOLESTR *rgszNames, UINT cNames,
                                                LCID lcid, DISPID *rgDispId)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_Invoke(IDispatchEx *iface, DISPID dispIdMember,
                            REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams,
                            VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_DeleteMemberByName(IDispatchEx *iface, BSTR bstrName, DWORD grfdex)
{
    ok(0, "unexpected call %s %x\n", wine_dbgstr_w(bstrName), grfdex);
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_DeleteMemberByDispID(IDispatchEx *iface, DISPID id)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_GetMemberProperties(IDispatchEx *iface, DISPID id, DWORD grfdexFetch, DWORD *pgrfdex)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_GetMemberName(IDispatchEx *iface, DISPID id, BSTR *pbstrName)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_GetNextDispID(IDispatchEx *iface, DWORD grfdex, DISPID id, DISPID *pid)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_GetNameSpaceParent(IDispatchEx *iface, IUnknown **ppunk)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI DispatchEx_GetDispID(IDispatchEx *iface, BSTR bstrName, DWORD grfdex, DISPID *pid)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI funcDisp_InvokeEx(IDispatchEx *iface, DISPID id, LCID lcid, WORD wFlags, DISPPARAMS *pdp,
        VARIANT *pvarRes, EXCEPINFO *pei, IServiceProvider *pspCaller)
{
    CHECK_EXPECT(funcDisp);

    ok(id == DISPID_VALUE, "id = %d\n", id);
    ok(lcid == 0, "lcid = %x\n", lcid);
    ok(wFlags == DISPATCH_METHOD, "wFlags = %x\n", wFlags);
    ok(pdp != NULL, "pdp == NULL\n");
    ok(pdp->cArgs == 2, "pdp->cArgs = %d\n", pdp->cArgs);
    ok(pdp->cNamedArgs == 1, "pdp->cNamedArgs = %d\n", pdp->cNamedArgs);
    ok(pdp->rgdispidNamedArgs[0] == DISPID_THIS, "pdp->rgdispidNamedArgs[0] = %d\n", pdp->rgdispidNamedArgs[0]);
    ok(V_VT(pdp->rgvarg) == VT_DISPATCH, "V_VT(rgvarg) = %d\n", V_VT(pdp->rgvarg));
    ok(V_VT(pdp->rgvarg+1) == VT_BOOL, "V_VT(rgvarg[1]) = %d\n", V_VT(pdp->rgvarg));
    ok(V_BOOL(pdp->rgvarg+1) == VARIANT_TRUE, "V_BOOL(rgvarg[1]) = %x\n", V_BOOL(pdp->rgvarg));
    ok(pvarRes != NULL, "pvarRes == NULL\n");
    ok(pei != NULL, "pei == NULL\n");
    ok(!pspCaller, "pspCaller != NULL\n");

    V_VT(pvarRes) = VT_I4;
    V_I4(pvarRes) = 100;
    return S_OK;
}

static IDispatchExVtbl testObjVtbl = {
    DispatchEx_QueryInterface,
    DispatchEx_AddRef,
    DispatchEx_Release,
    DispatchEx_GetTypeInfoCount,
    DispatchEx_GetTypeInfo,
    DispatchEx_GetIDsOfNames,
    DispatchEx_Invoke,
    DispatchEx_GetDispID,
    funcDisp_InvokeEx,
    DispatchEx_DeleteMemberByName,
    DispatchEx_DeleteMemberByDispID,
    DispatchEx_GetMemberProperties,
    DispatchEx_GetMemberName,
    DispatchEx_GetNextDispID,
    DispatchEx_GetNameSpaceParent
};

static IDispatchEx funcDisp = { &testObjVtbl };

static HRESULT WINAPI scriptDisp_GetDispID(IDispatchEx *iface, BSTR bstrName, DWORD grfdex, DISPID *pid)
{
    if(!strcmp_wa(bstrName, "testProp")) {
        CHECK_EXPECT(script_testprop_d);
        ok(grfdex == fdexNameCaseSensitive, "grfdex = %x\n", grfdex);
        *pid = DISPID_SCRIPT_TESTPROP;
        return S_OK;
    }

    if(!strcmp_wa(bstrName, "testProp2")) {
        CHECK_EXPECT(script_testprop2_d);
        ok(grfdex == fdexNameCaseSensitive, "grfdex = %x\n", grfdex);
        *pid = DISPID_SCRIPT_TESTPROP2;
        return S_OK;
    }

    if(!strcmp_wa(bstrName, "divid")) {
        CHECK_EXPECT(script_divid_d);
        ok(grfdex == fdexNameCaseSensitive, "grfdex = %x\n", grfdex);
        return E_FAIL;
    }

    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI scriptDisp_InvokeEx(IDispatchEx *iface, DISPID id, LCID lcid, WORD wFlags, DISPPARAMS *pdp,
        VARIANT *pvarRes, EXCEPINFO *pei, IServiceProvider *pspCaller)
{
    switch(id) {
    case DISPID_SCRIPT_TESTPROP:
        CHECK_EXPECT(script_testprop_i);

        ok(lcid == 0, "lcid = %x\n", lcid);
        ok(wFlags == DISPATCH_PROPERTYGET, "wFlags = %x\n", wFlags);
        ok(pdp != NULL, "pdp == NULL\n");
        ok(pdp->cArgs == 0, "pdp->cArgs = %d\n", pdp->cArgs);
        ok(pdp->cNamedArgs == 0, "pdp->cNamedArgs = %d\n", pdp->cNamedArgs);
        ok(!pdp->rgdispidNamedArgs, "pdp->rgdispidNamedArgs != NULL\n");
        ok(!pdp->rgvarg, "rgvarg != NULL\n");
        ok(pvarRes != NULL, "pvarRes == NULL\n");
        ok(pei != NULL, "pei == NULL\n");
        ok(!pspCaller, "pspCaller != NULL\n");

        V_VT(pvarRes) = VT_NULL;
        break;
    default:
        ok(0, "unexpected call\n");
        return E_NOTIMPL;
    }

    return S_OK;
}

static IDispatchExVtbl scriptDispVtbl = {
    DispatchEx_QueryInterface,
    DispatchEx_AddRef,
    DispatchEx_Release,
    DispatchEx_GetTypeInfoCount,
    DispatchEx_GetTypeInfo,
    DispatchEx_GetIDsOfNames,
    DispatchEx_Invoke,
    scriptDisp_GetDispID,
    scriptDisp_InvokeEx,
    DispatchEx_DeleteMemberByName,
    DispatchEx_DeleteMemberByDispID,
    DispatchEx_GetMemberProperties,
    DispatchEx_GetMemberName,
    DispatchEx_GetNextDispID,
    DispatchEx_GetNameSpaceParent
};

static IDispatchEx scriptDisp = { &scriptDispVtbl };

static HRESULT WINAPI externalDisp_GetDispID(IDispatchEx *iface, BSTR bstrName, DWORD grfdex, DISPID *pid)
{
    if(!strcmp_wa(bstrName, "ok")) {
        *pid = DISPID_EXTERNAL_OK;
        return S_OK;
    }
    if(!strcmp_wa(bstrName, "trace")) {
        *pid = DISPID_EXTERNAL_TRACE;
        return S_OK;
    }
    if(!strcmp_wa(bstrName, "reportSuccess")) {
        *pid = DISPID_EXTERNAL_REPORTSUCCESS;
        return S_OK;
    }

    ok(0, "unexpected name %s\n", wine_dbgstr_w(bstrName));
    return DISP_E_UNKNOWNNAME;
}

static HRESULT WINAPI externalDisp_InvokeEx(IDispatchEx *iface, DISPID id, LCID lcid, WORD wFlags, DISPPARAMS *pdp,
        VARIANT *pvarRes, EXCEPINFO *pei, IServiceProvider *pspCaller)
{
    switch(id) {
    case DISPID_EXTERNAL_OK:
        ok(wFlags == INVOKE_FUNC || wFlags == (INVOKE_FUNC|INVOKE_PROPERTYGET), "wFlags = %x\n", wFlags);
        ok(pdp != NULL, "pdp == NULL\n");
        ok(pdp->rgvarg != NULL, "rgvarg == NULL\n");
        ok(!pdp->rgdispidNamedArgs, "rgdispidNamedArgs != NULL\n");
        ok(pdp->cArgs == 2, "cArgs = %d\n", pdp->cArgs);
        ok(!pdp->cNamedArgs, "cNamedArgs = %d\n", pdp->cNamedArgs);
        ok(pei != NULL, "pei == NULL\n");

        ok(V_VT(pdp->rgvarg) == VT_BSTR, "V_VT(psp->rgvargs) = %d\n", V_VT(pdp->rgvarg));
        ok(V_VT(pdp->rgvarg+1) == VT_BOOL, "V_VT(psp->rgvargs+1) = %d\n", V_VT(pdp->rgvarg));
        ok(V_BOOL(pdp->rgvarg+1), "%s\n", wine_dbgstr_w(V_BSTR(pdp->rgvarg)));

        return S_OK;

     case DISPID_EXTERNAL_TRACE:
        ok(wFlags == INVOKE_FUNC, "wFlags = %x\n", wFlags);
        ok(pdp != NULL, "pdp == NULL\n");
        ok(pdp->rgvarg != NULL, "rgvarg == NULL\n");
        ok(!pdp->rgdispidNamedArgs, "rgdispidNamedArgs != NULL\n");
        ok(pdp->cArgs == 1, "cArgs = %d\n", pdp->cArgs);
        ok(!pdp->cNamedArgs, "cNamedArgs = %d\n", pdp->cNamedArgs);
        ok(!pvarRes, "pvarRes != NULL\n");
        ok(pei != NULL, "pei == NULL\n");

        ok(V_VT(pdp->rgvarg) == VT_BSTR, "V_VT(psp->rgvargs) = %d\n", V_VT(pdp->rgvarg));
        if(V_VT(pdp->rgvarg) == VT_BSTR)
            trace("%s\n", wine_dbgstr_w(V_BSTR(pdp->rgvarg)));

        return S_OK;

    case DISPID_EXTERNAL_REPORTSUCCESS:
        CHECK_EXPECT(external_success);

        ok(wFlags == INVOKE_FUNC, "wFlags = %x\n", wFlags);
        ok(pdp != NULL, "pdp == NULL\n");
        ok(!pdp->rgdispidNamedArgs, "rgdispidNamedArgs != NULL\n");
        ok(pdp->cArgs == 0, "cArgs = %d\n", pdp->cArgs);
        ok(!pdp->cNamedArgs, "cNamedArgs = %d\n", pdp->cNamedArgs);
        ok(!pvarRes, "pvarRes != NULL\n");
        ok(pei != NULL, "pei == NULL\n");

        return S_OK;

    default:
        ok(0, "unexpected call\n");
        return E_NOTIMPL;
    }

    return S_OK;
}

static IDispatchExVtbl externalDispVtbl = {
    DispatchEx_QueryInterface,
    DispatchEx_AddRef,
    DispatchEx_Release,
    DispatchEx_GetTypeInfoCount,
    DispatchEx_GetTypeInfo,
    DispatchEx_GetIDsOfNames,
    DispatchEx_Invoke,
    externalDisp_GetDispID,
    externalDisp_InvokeEx,
    DispatchEx_DeleteMemberByName,
    DispatchEx_DeleteMemberByDispID,
    DispatchEx_GetMemberProperties,
    DispatchEx_GetMemberName,
    DispatchEx_GetNextDispID,
    DispatchEx_GetNameSpaceParent
};

static IDispatchEx externalDisp = { &externalDispVtbl };

static HRESULT QueryInterface(REFIID,void**);

static HRESULT WINAPI DocHostUIHandler_QueryInterface(IDocHostUIHandler2 *iface, REFIID riid, void **ppv)
{
    return QueryInterface(riid, ppv);
}

static ULONG WINAPI DocHostUIHandler_AddRef(IDocHostUIHandler2 *iface)
{
    return 2;
}

static ULONG WINAPI DocHostUIHandler_Release(IDocHostUIHandler2 *iface)
{
    return 1;
}

static HRESULT WINAPI DocHostUIHandler_ShowContextMenu(IDocHostUIHandler2 *iface, DWORD dwID, POINT *ppt,
        IUnknown *pcmdtReserved, IDispatch *pdicpReserved)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI DocHostUIHandler_GetHostInfo(IDocHostUIHandler2 *iface, DOCHOSTUIINFO *pInfo)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI DocHostUIHandler_ShowUI(IDocHostUIHandler2 *iface, DWORD dwID,
        IOleInPlaceActiveObject *pActiveObject, IOleCommandTarget *pCommandTarget,
        IOleInPlaceFrame *pFrame, IOleInPlaceUIWindow *pDoc)
{
    return S_OK;
}

static HRESULT WINAPI DocHostUIHandler_HideUI(IDocHostUIHandler2 *iface)
{
    return S_OK;
}

static HRESULT WINAPI DocHostUIHandler_UpdateUI(IDocHostUIHandler2 *iface)
{
    return S_OK;
}

static HRESULT WINAPI DocHostUIHandler_EnableModeless(IDocHostUIHandler2 *iface, BOOL fEnable)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI DocHostUIHandler_OnDocWindowActivate(IDocHostUIHandler2 *iface, BOOL fActivate)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI DocHostUIHandler_OnFrameWindowActivate(IDocHostUIHandler2 *iface, BOOL fActivate)
{
    return S_OK;
}

static HRESULT WINAPI DocHostUIHandler_ResizeBorder(IDocHostUIHandler2 *iface, LPCRECT prcBorder,
        IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI DocHostUIHandler_TranslateAccelerator(IDocHostUIHandler2 *iface, LPMSG lpMsg,
        const GUID *pguidCmdGroup, DWORD nCmdID)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI DocHostUIHandler_GetOptionKeyPath(IDocHostUIHandler2 *iface,
        LPOLESTR *pchKey, DWORD dw)
{
    return S_OK;
}

static HRESULT WINAPI DocHostUIHandler_GetDropTarget(IDocHostUIHandler2 *iface,
        IDropTarget *pDropTarget, IDropTarget **ppDropTarget)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI DocHostUIHandler_GetExternal(IDocHostUIHandler2 *iface, IDispatch **ppDispatch)
{
    *ppDispatch = (IDispatch*)&externalDisp;
    return S_OK;
}

static HRESULT WINAPI DocHostUIHandler_TranslateUrl(IDocHostUIHandler2 *iface, DWORD dwTranslate,
        OLECHAR *pchURLIn, OLECHAR **ppchURLOut)
{
    return S_FALSE;
}

static HRESULT WINAPI DocHostUIHandler_FilterDataObject(IDocHostUIHandler2 *iface, IDataObject *pDO,
        IDataObject **ppPORet)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI DocHostUIHandler_GetOverrideKeyPath(IDocHostUIHandler2 *iface,
        LPOLESTR *pchKey, DWORD dw)
{
    return E_NOTIMPL;
}

static const IDocHostUIHandler2Vtbl DocHostUIHandlerVtbl = {
    DocHostUIHandler_QueryInterface,
    DocHostUIHandler_AddRef,
    DocHostUIHandler_Release,
    DocHostUIHandler_ShowContextMenu,
    DocHostUIHandler_GetHostInfo,
    DocHostUIHandler_ShowUI,
    DocHostUIHandler_HideUI,
    DocHostUIHandler_UpdateUI,
    DocHostUIHandler_EnableModeless,
    DocHostUIHandler_OnDocWindowActivate,
    DocHostUIHandler_OnFrameWindowActivate,
    DocHostUIHandler_ResizeBorder,
    DocHostUIHandler_TranslateAccelerator,
    DocHostUIHandler_GetOptionKeyPath,
    DocHostUIHandler_GetDropTarget,
    DocHostUIHandler_GetExternal,
    DocHostUIHandler_TranslateUrl,
    DocHostUIHandler_FilterDataObject,
    DocHostUIHandler_GetOverrideKeyPath
};

static IDocHostUIHandler2 DocHostUIHandler = { &DocHostUIHandlerVtbl };

static HRESULT WINAPI InPlaceFrame_QueryInterface(IOleInPlaceFrame *iface, REFIID riid, void **ppv)
{
    return E_NOINTERFACE;
}

static ULONG WINAPI InPlaceFrame_AddRef(IOleInPlaceFrame *iface)
{
    return 2;
}

static ULONG WINAPI InPlaceFrame_Release(IOleInPlaceFrame *iface)
{
    return 1;
}

static HRESULT WINAPI InPlaceFrame_GetWindow(IOleInPlaceFrame *iface, HWND *phwnd)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceFrame_ContextSensitiveHelp(IOleInPlaceFrame *iface, BOOL fEnterMode)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceFrame_GetBorder(IOleInPlaceFrame *iface, LPRECT lprectBorder)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceFrame_RequestBorderSpace(IOleInPlaceFrame *iface,
        LPCBORDERWIDTHS pborderwidths)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceFrame_SetBorderSpace(IOleInPlaceFrame *iface,
        LPCBORDERWIDTHS pborderwidths)
{
    return S_OK;
}

static HRESULT WINAPI InPlaceFrame_SetActiveObject(IOleInPlaceFrame *iface,
        IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName)
{
    return S_OK;
}

static HRESULT WINAPI InPlaceFrame_InsertMenus(IOleInPlaceFrame *iface, HMENU hmenuShared,
        LPOLEMENUGROUPWIDTHS lpMenuWidths)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceFrame_SetMenu(IOleInPlaceFrame *iface, HMENU hmenuShared,
        HOLEMENU holemenu, HWND hwndActiveObject)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceFrame_RemoveMenus(IOleInPlaceFrame *iface, HMENU hmenuShared)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceFrame_SetStatusText(IOleInPlaceFrame *iface, LPCOLESTR pszStatusText)
{
    return S_OK;
}

static HRESULT WINAPI InPlaceFrame_EnableModeless(IOleInPlaceFrame *iface, BOOL fEnable)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceFrame_TranslateAccelerator(IOleInPlaceFrame *iface, LPMSG lpmsg, WORD wID)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static const IOleInPlaceFrameVtbl InPlaceFrameVtbl = {
    InPlaceFrame_QueryInterface,
    InPlaceFrame_AddRef,
    InPlaceFrame_Release,
    InPlaceFrame_GetWindow,
    InPlaceFrame_ContextSensitiveHelp,
    InPlaceFrame_GetBorder,
    InPlaceFrame_RequestBorderSpace,
    InPlaceFrame_SetBorderSpace,
    InPlaceFrame_SetActiveObject,
    InPlaceFrame_InsertMenus,
    InPlaceFrame_SetMenu,
    InPlaceFrame_RemoveMenus,
    InPlaceFrame_SetStatusText,
    InPlaceFrame_EnableModeless,
    InPlaceFrame_TranslateAccelerator
};

static IOleInPlaceFrame InPlaceFrame = { &InPlaceFrameVtbl };

static HRESULT WINAPI InPlaceSite_QueryInterface(IOleInPlaceSite *iface, REFIID riid, void **ppv)
{
    return QueryInterface(riid, ppv);
}

static ULONG WINAPI InPlaceSite_AddRef(IOleInPlaceSite *iface)
{
    return 2;
}

static ULONG WINAPI InPlaceSite_Release(IOleInPlaceSite *iface)
{
    return 1;
}

static HRESULT WINAPI InPlaceSite_GetWindow(IOleInPlaceSite *iface, HWND *phwnd)
{
    *phwnd = container_hwnd;
    return S_OK;
}

static HRESULT WINAPI InPlaceSite_ContextSensitiveHelp(IOleInPlaceSite *iface, BOOL fEnterMode)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceSite_CanInPlaceActivate(IOleInPlaceSite *iface)
{
    return S_OK;
}

static HRESULT WINAPI InPlaceSite_OnInPlaceActivate(IOleInPlaceSite *iface)
{
    return S_OK;
}

static HRESULT WINAPI InPlaceSite_OnUIActivate(IOleInPlaceSite *iface)
{
    return S_OK;
}

static HRESULT WINAPI InPlaceSite_GetWindowContext(IOleInPlaceSite *iface,
        IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect,
        LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
    static const RECT rect = {0,0,300,300};

    *ppFrame = &InPlaceFrame;
    *ppDoc = (IOleInPlaceUIWindow*)&InPlaceFrame;
    *lprcPosRect = rect;
    *lprcClipRect = rect;

    lpFrameInfo->cb = sizeof(*lpFrameInfo);
    lpFrameInfo->fMDIApp = FALSE;
    lpFrameInfo->hwndFrame = container_hwnd;
    lpFrameInfo->haccel = NULL;
    lpFrameInfo->cAccelEntries = 0;

    return S_OK;
}

static HRESULT WINAPI InPlaceSite_Scroll(IOleInPlaceSite *iface, SIZE scrollExtant)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceSite_OnUIDeactivate(IOleInPlaceSite *iface, BOOL fUndoable)
{
    return S_OK;
}

static HRESULT WINAPI InPlaceSite_OnInPlaceDeactivate(IOleInPlaceSite *iface)
{
    return S_OK;
}

static HRESULT WINAPI InPlaceSite_DiscardUndoState(IOleInPlaceSite *iface)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceSite_DeactivateAndUndo(IOleInPlaceSite *iface)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI InPlaceSite_OnPosRectChange(IOleInPlaceSite *iface, LPCRECT lprcPosRect)
{
    return E_NOTIMPL;
}

static const IOleInPlaceSiteVtbl InPlaceSiteVtbl = {
    InPlaceSite_QueryInterface,
    InPlaceSite_AddRef,
    InPlaceSite_Release,
    InPlaceSite_GetWindow,
    InPlaceSite_ContextSensitiveHelp,
    InPlaceSite_CanInPlaceActivate,
    InPlaceSite_OnInPlaceActivate,
    InPlaceSite_OnUIActivate,
    InPlaceSite_GetWindowContext,
    InPlaceSite_Scroll,
    InPlaceSite_OnUIDeactivate,
    InPlaceSite_OnInPlaceDeactivate,
    InPlaceSite_DiscardUndoState,
    InPlaceSite_DeactivateAndUndo,
    InPlaceSite_OnPosRectChange,
};

static IOleInPlaceSite InPlaceSite = { &InPlaceSiteVtbl };

static HRESULT WINAPI ClientSite_QueryInterface(IOleClientSite *iface, REFIID riid, void **ppv)
{
    return QueryInterface(riid, ppv);
}

static ULONG WINAPI ClientSite_AddRef(IOleClientSite *iface)
{
    return 2;
}

static ULONG WINAPI ClientSite_Release(IOleClientSite *iface)
{
    return 1;
}

static HRESULT WINAPI ClientSite_SaveObject(IOleClientSite *iface)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ClientSite_GetMoniker(IOleClientSite *iface, DWORD dwAssign, DWORD dwWhichMoniker,
        IMoniker **ppmon)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ClientSite_GetContainer(IOleClientSite *iface, IOleContainer **ppContainer)
{
    return E_NOTIMPL;
}

static HRESULT WINAPI ClientSite_ShowObject(IOleClientSite *iface)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ClientSite_OnShowWindow(IOleClientSite *iface, BOOL fShow)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ClientSite_RequestNewObjectLayout(IOleClientSite *iface)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static const IOleClientSiteVtbl ClientSiteVtbl = {
    ClientSite_QueryInterface,
    ClientSite_AddRef,
    ClientSite_Release,
    ClientSite_SaveObject,
    ClientSite_GetMoniker,
    ClientSite_GetContainer,
    ClientSite_ShowObject,
    ClientSite_OnShowWindow,
    ClientSite_RequestNewObjectLayout
};

static IOleClientSite ClientSite = { &ClientSiteVtbl };

static HRESULT WINAPI DocumentSite_QueryInterface(IOleDocumentSite *iface, REFIID riid, void **ppv)
{
    return QueryInterface(riid, ppv);
}

static ULONG WINAPI DocumentSite_AddRef(IOleDocumentSite *iface)
{
    return 2;
}

static ULONG WINAPI DocumentSite_Release(IOleDocumentSite *iface)
{
    return 1;
}

static HRESULT WINAPI DocumentSite_ActivateMe(IOleDocumentSite *iface, IOleDocumentView *pViewToActivate)
{
    RECT rect = {0,0,300,300};
    IOleDocument *document;
    HRESULT hres;

    hres = IOleDocumentView_QueryInterface(pViewToActivate, &IID_IOleDocument, (void**)&document);
    ok(hres == S_OK, "could not get IOleDocument: %08x\n", hres);

    hres = IOleDocument_CreateView(document, &InPlaceSite, NULL, 0, &view);
    IOleDocument_Release(document);
    ok(hres == S_OK, "CreateView failed: %08x\n", hres);

    hres = IOleDocumentView_SetInPlaceSite(view, &InPlaceSite);
    ok(hres == S_OK, "SetInPlaceSite failed: %08x\n", hres);

    hres = IOleDocumentView_UIActivate(view, TRUE);
    ok(hres == S_OK, "UIActivate failed: %08x\n", hres);

    hres = IOleDocumentView_SetRect(view, &rect);
    ok(hres == S_OK, "SetRect failed: %08x\n", hres);

    hres = IOleDocumentView_Show(view, TRUE);
    ok(hres == S_OK, "Show failed: %08x\n", hres);

    return S_OK;
}

static const IOleDocumentSiteVtbl DocumentSiteVtbl = {
    DocumentSite_QueryInterface,
    DocumentSite_AddRef,
    DocumentSite_Release,
    DocumentSite_ActivateMe
};

static IOleDocumentSite DocumentSite = { &DocumentSiteVtbl };

static HRESULT QueryInterface(REFIID riid, void **ppv)
{
    *ppv = NULL;

    if(IsEqualGUID(&IID_IUnknown, riid) || IsEqualGUID(&IID_IOleClientSite, riid))
        *ppv = &ClientSite;
    else if(IsEqualGUID(&IID_IOleDocumentSite, riid))
        *ppv = &DocumentSite;
    else if(IsEqualGUID(&IID_IOleWindow, riid) || IsEqualGUID(&IID_IOleInPlaceSite, riid))
        *ppv = &InPlaceSite;
    else if(IsEqualGUID(&IID_IDocHostUIHandler, riid) || IsEqualGUID(&IID_IDocHostUIHandler2, riid))
        *ppv = &DocHostUIHandler;

    return *ppv ? S_OK : E_NOINTERFACE;
}

static IHTMLDocument2 *create_document(void)
{
    IHTMLDocument2 *doc;
    IHTMLDocument5 *doc5;
    HRESULT hres;

    hres = CoCreateInstance(&CLSID_HTMLDocument, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IHTMLDocument2, (void**)&doc);
    ok(hres == S_OK, "CoCreateInstance failed: %08x\n", hres);
    if (hres != S_OK) return NULL;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHTMLDocument5, (void**)&doc5);
    if(FAILED(hres)) {
        win_skip("Could not get IHTMLDocument5, probably too old IE\n");
        IHTMLDocument2_Release(doc);
        return NULL;
    }

    IHTMLDocument5_Release(doc5);
    return doc;
}

static void load_string(IHTMLDocument2 *doc, const char *str)
{
    IPersistStreamInit *init;
    IStream *stream;
    HGLOBAL mem;
    SIZE_T len;

    doc_complete = FALSE;
    len = strlen(str);
    mem = GlobalAlloc(0, len);
    memcpy(mem, str, len);
    CreateStreamOnHGlobal(mem, TRUE, &stream);

    IHTMLDocument2_QueryInterface(doc, &IID_IPersistStreamInit, (void**)&init);

    IPersistStreamInit_Load(init, stream);
    IPersistStreamInit_Release(init);
    IStream_Release(stream);
}

static void do_advise(IHTMLDocument2 *doc, REFIID riid, IUnknown *unk_advise)
{
    IConnectionPointContainer *container;
    IConnectionPoint *cp;
    DWORD cookie;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IConnectionPointContainer, (void**)&container);
    ok(hres == S_OK, "QueryInterface(IID_IConnectionPointContainer) failed: %08x\n", hres);

    hres = IConnectionPointContainer_FindConnectionPoint(container, riid, &cp);
    IConnectionPointContainer_Release(container);
    ok(hres == S_OK, "FindConnectionPoint failed: %08x\n", hres);

    notif_doc = doc;

    hres = IConnectionPoint_Advise(cp, unk_advise, &cookie);
    IConnectionPoint_Release(cp);
    ok(hres == S_OK, "Advise failed: %08x\n", hres);
}

static void set_client_site(IHTMLDocument2 *doc, BOOL set)
{
    IOleObject *oleobj;
    HRESULT hres;

    if(!set && view) {
        IOleDocumentView_Show(view, FALSE);
        IOleDocumentView_CloseView(view, 0);
        IOleDocumentView_SetInPlaceSite(view, NULL);
        IOleDocumentView_Release(view);
        view = NULL;
    }

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleObject, (void**)&oleobj);
    ok(hres == S_OK, "Could not et IOleObject: %08x\n", hres);

    hres = IOleObject_SetClientSite(oleobj, set ? &ClientSite : NULL);
    ok(hres == S_OK, "SetClientSite failed: %08x\n", hres);

    if(set) {
        IHlinkTarget *hlink;

        hres = IOleObject_QueryInterface(oleobj, &IID_IHlinkTarget, (void**)&hlink);
        ok(hres == S_OK, "Could not get IHlinkTarget iface: %08x\n", hres);

        hres = IHlinkTarget_Navigate(hlink, 0, NULL);
        ok(hres == S_OK, "Navgate failed: %08x\n", hres);

        IHlinkTarget_Release(hlink);
    }

    IOleObject_Release(oleobj);
}

typedef void (*domtest_t)(IHTMLDocument2*);

static void load_doc(IHTMLDocument2 *doc, const char *str)
{
    IHTMLElement *body = NULL;
    MSG msg;
    HRESULT hres;
    static const WCHAR ucPtr[] = {'b','a','c','k','g','r','o','u','n','d',0};
    DISPID dispID = -1;
    OLECHAR *name;

    load_string(doc, str);
    do_advise(doc, &IID_IPropertyNotifySink, (IUnknown*)&PropertyNotifySink);

    while(!doc_complete && GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    hres = IHTMLDocument2_get_body(doc, &body);
    ok(hres == S_OK, "get_body failed: %08x\n", hres);

    /* Check we can query for function on the IHTMLElementBody interface */
    name = (WCHAR*)ucPtr;
    hres = IHTMLElement_GetIDsOfNames(body, &IID_NULL, &name, 1, LOCALE_USER_DEFAULT, &dispID);
    ok(hres == S_OK, "GetIDsOfNames(background) failed %08x\n", hres);
    ok(dispID == DISPID_IHTMLBODYELEMENT_BACKGROUND, "Incorrect dispID got (%d)\n", dispID);

    IHTMLElement_Release(body);
}

static IActiveScriptSite *site;
static SCRIPTSTATE state;

static HRESULT WINAPI ObjectSafety_QueryInterface(IObjectSafety *iface, REFIID riid, void **ppv)
{
    *ppv = NULL;
    ok(0, "unexpected call %s\n", debugstr_guid(riid));
    return E_NOINTERFACE;
}

static ULONG WINAPI ObjectSafety_AddRef(IObjectSafety *iface)
{
    return 2;
}

static ULONG WINAPI ObjectSafety_Release(IObjectSafety *iface)
{
    return 1;
}

static HRESULT WINAPI ObjectSafety_GetInterfaceSafetyOptions(IObjectSafety *iface, REFIID riid,
        DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
{
    CHECK_EXPECT(GetInterfaceSafetyOptions);

    ok(IsEqualGUID(&IID_IActiveScriptParse, riid), "unexpected riid %s\n", debugstr_guid(riid));
    ok(pdwSupportedOptions != NULL, "pdwSupportedOptions == NULL\n");
    ok(pdwEnabledOptions != NULL, "pdwEnabledOptions == NULL\n");

    *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER;
    *pdwEnabledOptions = INTERFACE_USES_DISPEX;

    return S_OK;
}

static HRESULT WINAPI ObjectSafety_SetInterfaceSafetyOptions(IObjectSafety *iface, REFIID riid,
        DWORD dwOptionSetMask, DWORD dwEnabledOptions)
{
    CHECK_EXPECT(SetInterfaceSafetyOptions);

    ok(IsEqualGUID(&IID_IActiveScriptParse, riid), "unexpected riid %s\n", debugstr_guid(riid));

    ok(dwOptionSetMask == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "dwOptionSetMask=%x\n", dwOptionSetMask);
    ok(dwEnabledOptions == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "dwEnabledOptions=%x\n", dwOptionSetMask);

    return S_OK;
}

static const IObjectSafetyVtbl ObjectSafetyVtbl = {
    ObjectSafety_QueryInterface,
    ObjectSafety_AddRef,
    ObjectSafety_Release,
    ObjectSafety_GetInterfaceSafetyOptions,
    ObjectSafety_SetInterfaceSafetyOptions
};

static IObjectSafety ObjectSafety = { &ObjectSafetyVtbl };

static HRESULT WINAPI AXObjectSafety_QueryInterface(IObjectSafety *iface, REFIID riid, void **ppv)
{
    *ppv = NULL;

    if(IsEqualGUID(&IID_IActiveScript, riid)) {
        CHECK_EXPECT(AXQueryInterface_IActiveScript);
        return E_NOINTERFACE;
    }

    if(IsEqualGUID(&IID_IObjectSafety, riid)) {
        CHECK_EXPECT(AXQueryInterface_IObjectSafety);
        if(!ax_objsafe)
            return E_NOINTERFACE;
        *ppv = iface;
        return S_OK;
    }

    ok(0, "unexpected call %s\n", debugstr_guid(riid));
    return E_NOINTERFACE;
}

static HRESULT WINAPI AXObjectSafety_GetInterfaceSafetyOptions(IObjectSafety *iface, REFIID riid,
        DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
{
    CHECK_EXPECT(AXGetInterfaceSafetyOptions);

    ok(IsEqualGUID(&IID_IDispatchEx, riid), "unexpected riid %s\n", debugstr_guid(riid));
    ok(pdwSupportedOptions != NULL, "pdwSupportedOptions == NULL\n");
    ok(pdwEnabledOptions != NULL, "pdwEnabledOptions == NULL\n");

    if(SUCCEEDED(ax_getopt_hres)) {
        *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER;
        *pdwEnabledOptions = INTERFACE_USES_DISPEX;
    }

    return ax_getopt_hres;
}

static HRESULT WINAPI AXObjectSafety_SetInterfaceSafetyOptions(IObjectSafety *iface, REFIID riid,
        DWORD dwOptionSetMask, DWORD dwEnabledOptions)
{
    if(IsEqualGUID(&IID_IDispatchEx, riid)) {
        CHECK_EXPECT(AXSetInterfaceSafetyOptions_IDispatchEx);
        ok(dwOptionSetMask == ax_setopt, "dwOptionSetMask=%x, expected %x\n", dwOptionSetMask, ax_setopt);
        ok(dwEnabledOptions == ax_setopt, "dwEnabledOptions=%x, expected %x\n", dwOptionSetMask, ax_setopt);
        return ax_setopt_dispex_hres;
    }

    if(IsEqualGUID(&IID_IDispatch, riid)) {
        DWORD exopt = ax_setopt & ~INTERFACE_USES_SECURITY_MANAGER;

        CHECK_EXPECT(AXSetInterfaceSafetyOptions_IDispatch);
        ok(dwOptionSetMask == exopt, "dwOptionSetMask=%x, expected %x\n", dwOptionSetMask, exopt);
        ok(dwEnabledOptions == exopt, "dwEnabledOptions=%x, expected %x\n", dwOptionSetMask, exopt);
        return ax_setopt_disp_hres;
    }

    ok(0, "unexpected riid %s\n", debugstr_guid(riid));
    return E_NOINTERFACE;
}

static const IObjectSafetyVtbl AXObjectSafetyVtbl = {
    AXObjectSafety_QueryInterface,
    ObjectSafety_AddRef,
    ObjectSafety_Release,
    AXObjectSafety_GetInterfaceSafetyOptions,
    AXObjectSafety_SetInterfaceSafetyOptions
};

static IObjectSafety AXObjectSafety = { &AXObjectSafetyVtbl };

static BOOL set_safe_reg(BOOL init)
{
    return init_key("CLSID\\"TESTACTIVEX_CLSID"\\Implemented Categories\\{7dd95801-9882-11cf-9fa9-00aa006c42c4}",
                    NULL, init);
}

static void test_security(void)
{
    IInternetHostSecurityManager *sec_mgr;
    IServiceProvider *sp;
    DWORD policy, policy_size;
    struct CONFIRMSAFETY cs;
    BYTE *ppolicy;
    HRESULT hres;

    ax_setopt = INTERFACESAFE_FOR_UNTRUSTED_CALLER|INTERFACE_USES_SECURITY_MANAGER;

    hres = IActiveScriptSite_QueryInterface(site, &IID_IServiceProvider, (void**)&sp);
    ok(hres == S_OK, "Could not get IServiceProvider iface: %08x\n", hres);

    hres = IServiceProvider_QueryService(sp, &SID_SInternetHostSecurityManager,
            &IID_IInternetHostSecurityManager, (void**)&sec_mgr);
    IServiceProvider_Release(sp);
    ok(hres == S_OK, "QueryService failed: %08x\n", hres);

    hres = IInternetHostSecurityManager_ProcessUrlAction(sec_mgr, URLACTION_ACTIVEX_RUN, (BYTE*)&policy, sizeof(policy),
                                                         (BYTE*)&CLSID_TestActiveX, sizeof(CLSID), 0, 0);
    ok(hres == S_OK, "ProcessUrlAction failed: %08x\n", hres);
    ok(policy == URLPOLICY_ALLOW, "policy = %x\n", policy);

    cs.clsid = CLSID_TestActiveX;
    cs.pUnk = (IUnknown*)&AXObjectSafety;
    cs.dwFlags = 0;

    ax_objsafe = TRUE;
    SET_EXPECT(AXQueryInterface_IActiveScript);
    SET_EXPECT(AXQueryInterface_IObjectSafety);
    SET_EXPECT(AXGetInterfaceSafetyOptions);
    SET_EXPECT(AXSetInterfaceSafetyOptions_IDispatchEx);
    hres = IInternetHostSecurityManager_QueryCustomPolicy(sec_mgr, &GUID_CUSTOM_CONFIRMOBJECTSAFETY,
            &ppolicy, &policy_size, (BYTE*)&cs, sizeof(cs), 0);
    CHECK_CALLED(AXQueryInterface_IActiveScript);
    CHECK_CALLED(AXQueryInterface_IObjectSafety);
    CHECK_CALLED(AXGetInterfaceSafetyOptions);
    CHECK_CALLED(AXSetInterfaceSafetyOptions_IDispatchEx);

    ok(hres == S_OK, "QueryCusromPolicy failed: %08x\n", hres);
    ok(policy_size == sizeof(DWORD), "policy_size = %d\n", policy_size);
    ok(*(DWORD*)ppolicy == URLPOLICY_ALLOW, "policy = %x\n", *(DWORD*)ppolicy);
    CoTaskMemFree(ppolicy);

    ax_objsafe = FALSE;
    SET_EXPECT(AXQueryInterface_IActiveScript);
    SET_EXPECT(AXQueryInterface_IObjectSafety);
    hres = IInternetHostSecurityManager_QueryCustomPolicy(sec_mgr, &GUID_CUSTOM_CONFIRMOBJECTSAFETY,
            &ppolicy, &policy_size, (BYTE*)&cs, sizeof(cs), 0);
    CHECK_CALLED(AXQueryInterface_IActiveScript);
    CHECK_CALLED(AXQueryInterface_IObjectSafety);

    ok(hres == S_OK, "QueryCusromPolicy failed: %08x\n", hres);
    ok(policy_size == sizeof(DWORD), "policy_size = %d\n", policy_size);
    ok(*(DWORD*)ppolicy == URLPOLICY_DISALLOW, "policy = %x\n", *(DWORD*)ppolicy);
    CoTaskMemFree(ppolicy);

    if(set_safe_reg(TRUE)) {
        ax_objsafe = FALSE;
        SET_EXPECT(AXQueryInterface_IActiveScript);
        SET_EXPECT(AXQueryInterface_IObjectSafety);
        hres = IInternetHostSecurityManager_QueryCustomPolicy(sec_mgr, &GUID_CUSTOM_CONFIRMOBJECTSAFETY,
                 &ppolicy, &policy_size, (BYTE*)&cs, sizeof(cs), 0);
        CHECK_CALLED(AXQueryInterface_IActiveScript);
        CHECK_CALLED(AXQueryInterface_IObjectSafety);

        ok(hres == S_OK, "QueryCusromPolicy failed: %08x\n", hres);
        ok(policy_size == sizeof(DWORD), "policy_size = %d\n", policy_size);
        ok(*(DWORD*)ppolicy == URLPOLICY_ALLOW, "policy = %x\n", *(DWORD*)ppolicy);
        CoTaskMemFree(ppolicy);

        ax_objsafe = TRUE;
        SET_EXPECT(AXQueryInterface_IActiveScript);
        SET_EXPECT(AXQueryInterface_IObjectSafety);
        SET_EXPECT(AXGetInterfaceSafetyOptions);
        SET_EXPECT(AXSetInterfaceSafetyOptions_IDispatchEx);
        hres = IInternetHostSecurityManager_QueryCustomPolicy(sec_mgr, &GUID_CUSTOM_CONFIRMOBJECTSAFETY,
                &ppolicy, &policy_size, (BYTE*)&cs, sizeof(cs), 0);
        CHECK_CALLED(AXQueryInterface_IActiveScript);
        CHECK_CALLED(AXQueryInterface_IObjectSafety);
        CHECK_CALLED(AXGetInterfaceSafetyOptions);
        CHECK_CALLED(AXSetInterfaceSafetyOptions_IDispatchEx);

        ok(hres == S_OK, "QueryCusromPolicy failed: %08x\n", hres);
        ok(policy_size == sizeof(DWORD), "policy_size = %d\n", policy_size);
        ok(*(DWORD*)ppolicy == URLPOLICY_ALLOW, "policy = %x\n", *(DWORD*)ppolicy);
        CoTaskMemFree(ppolicy);

        set_safe_reg(FALSE);
    }else {
        skip("Could not set safety registry\n");
    }

    ax_objsafe = TRUE;

    ax_setopt_dispex_hres = E_NOINTERFACE;
    SET_EXPECT(AXQueryInterface_IActiveScript);
    SET_EXPECT(AXQueryInterface_IObjectSafety);
    SET_EXPECT(AXGetInterfaceSafetyOptions);
    SET_EXPECT(AXSetInterfaceSafetyOptions_IDispatchEx);
    SET_EXPECT(AXSetInterfaceSafetyOptions_IDispatch);
    hres = IInternetHostSecurityManager_QueryCustomPolicy(sec_mgr, &GUID_CUSTOM_CONFIRMOBJECTSAFETY,
            &ppolicy, &policy_size, (BYTE*)&cs, sizeof(cs), 0);
    CHECK_CALLED(AXQueryInterface_IActiveScript);
    CHECK_CALLED(AXQueryInterface_IObjectSafety);
    CHECK_CALLED(AXGetInterfaceSafetyOptions);
    CHECK_CALLED(AXSetInterfaceSafetyOptions_IDispatchEx);
    CHECK_CALLED(AXSetInterfaceSafetyOptions_IDispatch);

    ok(hres == S_OK, "QueryCusromPolicy failed: %08x\n", hres);
    ok(policy_size == sizeof(DWORD), "policy_size = %d\n", policy_size);
    ok(*(DWORD*)ppolicy == URLPOLICY_ALLOW, "policy = %x\n", *(DWORD*)ppolicy);
    CoTaskMemFree(ppolicy);

    ax_setopt_dispex_hres = E_FAIL;
    ax_setopt_disp_hres = E_NOINTERFACE;
    SET_EXPECT(AXQueryInterface_IActiveScript);
    SET_EXPECT(AXQueryInterface_IObjectSafety);
    SET_EXPECT(AXGetInterfaceSafetyOptions);
    SET_EXPECT(AXSetInterfaceSafetyOptions_IDispatchEx);
    SET_EXPECT(AXSetInterfaceSafetyOptions_IDispatch);
    hres = IInternetHostSecurityManager_QueryCustomPolicy(sec_mgr, &GUID_CUSTOM_CONFIRMOBJECTSAFETY,
            &ppolicy, &policy_size, (BYTE*)&cs, sizeof(cs), 0);
    CHECK_CALLED(AXQueryInterface_IActiveScript);
    CHECK_CALLED(AXQueryInterface_IObjectSafety);
    CHECK_CALLED(AXGetInterfaceSafetyOptions);
    CHECK_CALLED(AXSetInterfaceSafetyOptions_IDispatchEx);
    CHECK_CALLED(AXSetInterfaceSafetyOptions_IDispatch);

    ok(hres == S_OK, "QueryCusromPolicy failed: %08x\n", hres);
    ok(policy_size == sizeof(DWORD), "policy_size = %d\n", policy_size);
    ok(*(DWORD*)ppolicy == URLPOLICY_DISALLOW, "policy = %x\n", *(DWORD*)ppolicy);
    CoTaskMemFree(ppolicy);

    ax_setopt_dispex_hres = E_FAIL;
    ax_setopt_disp_hres = S_OK;
    ax_getopt_hres = E_NOINTERFACE;
    ax_setopt = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
    SET_EXPECT(AXQueryInterface_IActiveScript);
    SET_EXPECT(AXQueryInterface_IObjectSafety);
    SET_EXPECT(AXGetInterfaceSafetyOptions);
    SET_EXPECT(AXSetInterfaceSafetyOptions_IDispatchEx);
    SET_EXPECT(AXSetInterfaceSafetyOptions_IDispatch);
    hres = IInternetHostSecurityManager_QueryCustomPolicy(sec_mgr, &GUID_CUSTOM_CONFIRMOBJECTSAFETY,
            &ppolicy, &policy_size, (BYTE*)&cs, sizeof(cs), 0);
    CHECK_CALLED(AXQueryInterface_IActiveScript);
    CHECK_CALLED(AXQueryInterface_IObjectSafety);
    CHECK_CALLED(AXGetInterfaceSafetyOptions);
    CHECK_CALLED(AXSetInterfaceSafetyOptions_IDispatchEx);
    CHECK_CALLED(AXSetInterfaceSafetyOptions_IDispatch);

    ok(hres == S_OK, "QueryCusromPolicy failed: %08x\n", hres);
    ok(policy_size == sizeof(DWORD), "policy_size = %d\n", policy_size);
    ok(*(DWORD*)ppolicy == URLPOLICY_ALLOW, "policy = %x\n", *(DWORD*)ppolicy);
    CoTaskMemFree(ppolicy);

    IInternetHostSecurityManager_Release(sec_mgr);
}

static HRESULT WINAPI ActiveScriptProperty_QueryInterface(IActiveScriptProperty *iface, REFIID riid, void **ppv)
{
    *ppv = NULL;
    ok(0, "unexpected call\n");
    return E_NOINTERFACE;
}

static ULONG WINAPI ActiveScriptProperty_AddRef(IActiveScriptProperty *iface)
{
    return 2;
}

static ULONG WINAPI ActiveScriptProperty_Release(IActiveScriptProperty *iface)
{
    return 1;
}

static HRESULT WINAPI ActiveScriptProperty_GetProperty(IActiveScriptProperty *iface, DWORD dwProperty,
        VARIANT *pvarIndex, VARIANT *pvarValue)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ActiveScriptProperty_SetProperty(IActiveScriptProperty *iface, DWORD dwProperty,
        VARIANT *pvarIndex, VARIANT *pvarValue)
{
    switch(dwProperty) {
    case SCRIPTPROP_HACK_TRIDENTEVENTSINK:
        CHECK_EXPECT(SetProperty_HACK_TRIDENTEVENTSINK);
        ok(V_VT(pvarValue) == VT_BOOL, "V_VT(pvarValue)=%d\n", V_VT(pvarValue));
        ok(V_BOOL(pvarValue) == VARIANT_TRUE, "V_BOOL(pvarValue)=%x\n", V_BOOL(pvarValue));
        break;
    case SCRIPTPROP_INVOKEVERSIONING:
        CHECK_EXPECT(SetProperty_INVOKEVERSIONING);
        ok(V_VT(pvarValue) == VT_I4, "V_VT(pvarValue)=%d\n", V_VT(pvarValue));
        ok(V_I4(pvarValue) == 1, "V_I4(pvarValue)=%d\n", V_I4(pvarValue));
        break;
    case SCRIPTPROP_ABBREVIATE_GLOBALNAME_RESOLUTION:
        CHECK_EXPECT(SetProperty_ABBREVIATE_GLOBALNAME_RESOLUTION);
        ok(V_VT(pvarValue) == VT_BOOL, "V_VT(pvarValue)=%d\n", V_VT(pvarValue));
        ok(V_BOOL(pvarValue) == VARIANT_TRUE, "V_BOOL(pvarValue)=%x\n", V_BOOL(pvarValue));
        break;
    default:
        ok(0, "unexpected property %x\n", dwProperty);
        return E_NOTIMPL;
    }

    ok(!pvarIndex, "pvarIndex != NULL\n");
    ok(pvarValue != NULL, "pvarValue == NULL\n");

    return S_OK;
}

static const IActiveScriptPropertyVtbl ActiveScriptPropertyVtbl = {
    ActiveScriptProperty_QueryInterface,
    ActiveScriptProperty_AddRef,
    ActiveScriptProperty_Release,
    ActiveScriptProperty_GetProperty,
    ActiveScriptProperty_SetProperty
};

static IActiveScriptProperty ActiveScriptProperty = { &ActiveScriptPropertyVtbl };

static HRESULT WINAPI ActiveScriptParseProcedure_QueryInterface(IActiveScriptParseProcedure2 *iface, REFIID riid, void **ppv)
{
    *ppv = NULL;
    ok(0, "unexpected call\n");
    return E_NOINTERFACE;
}

static ULONG WINAPI ActiveScriptParseProcedure_AddRef(IActiveScriptParseProcedure2 *iface)
{
    return 2;
}

static ULONG WINAPI ActiveScriptParseProcedure_Release(IActiveScriptParseProcedure2 *iface)
{
    return 1;
}

static HRESULT WINAPI ActiveScriptParseProcedure_ParseProcedureText(IActiveScriptParseProcedure2 *iface,
        LPCOLESTR pstrCode, LPCOLESTR pstrFormalParams, LPCOLESTR pstrProcedureName,
        LPCOLESTR pstrItemName, IUnknown *punkContext, LPCOLESTR pstrDelimiter,
        CTXARG_T dwSourceContextCookie, ULONG ulStartingLineNumber, DWORD dwFlags, IDispatch **ppdisp)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static const IActiveScriptParseProcedure2Vtbl ActiveScriptParseProcedureVtbl = {
    ActiveScriptParseProcedure_QueryInterface,
    ActiveScriptParseProcedure_AddRef,
    ActiveScriptParseProcedure_Release,
    ActiveScriptParseProcedure_ParseProcedureText
};

static IActiveScriptParseProcedure2 ActiveScriptParseProcedure = { &ActiveScriptParseProcedureVtbl };

static HRESULT WINAPI ActiveScriptParse_QueryInterface(IActiveScriptParse *iface, REFIID riid, void **ppv)
{
    *ppv = NULL;
    ok(0, "unexpected call\n");
    return E_NOINTERFACE;
}

static ULONG WINAPI ActiveScriptParse_AddRef(IActiveScriptParse *iface)
{
    return 2;
}

static ULONG WINAPI ActiveScriptParse_Release(IActiveScriptParse *iface)
{
    return 1;
}

static HRESULT WINAPI ActiveScriptParse_InitNew(IActiveScriptParse *iface)
{
    CHECK_EXPECT(InitNew);
    return S_OK;
}

static HRESULT WINAPI ActiveScriptParse_AddScriptlet(IActiveScriptParse *iface,
        LPCOLESTR pstrDefaultName, LPCOLESTR pstrCode, LPCOLESTR pstrItemName,
        LPCOLESTR pstrSubItemName, LPCOLESTR pstrEventName, LPCOLESTR pstrDelimiter,
        CTXARG_T dwSourceContextCookie, ULONG ulStartingLineNumber, DWORD dwFlags,
        BSTR *pbstrName, EXCEPINFO *pexcepinfo)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT dispex_propput(IDispatchEx *obj, DISPID id, DWORD flags, VARIANT *var)
{
    DISPID propput_arg = DISPID_PROPERTYPUT;
    DISPPARAMS dp = {var, &propput_arg, 1, 1};
    EXCEPINFO ei = {0};

    return IDispatchEx_InvokeEx(obj, id, LOCALE_NEUTRAL, DISPATCH_PROPERTYPUT|flags, &dp, NULL, &ei, NULL);
}

static void test_func(IDispatchEx *obj)
{
    DISPID id;
    IDispatchEx *dispex;
    IDispatch *disp;
    EXCEPINFO ei;
    DISPPARAMS dp;
    BSTR str;
    VARIANT var;
    HRESULT hres;

    str = a2bstr("toString");
    hres = IDispatchEx_GetDispID(obj, str, fdexNameCaseSensitive, &id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);
    ok(id == DISPID_IOMNAVIGATOR_TOSTRING, "id = %x\n", id);

    memset(&dp, 0, sizeof(dp));
    memset(&ei, 0, sizeof(ei));
    VariantInit(&var);
    hres = IDispatchEx_InvokeEx(obj, id, LOCALE_NEUTRAL, DISPATCH_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_DISPATCH, "V_VT(var)=%d\n", V_VT(&var));
    ok(V_DISPATCH(&var) != NULL, "V_DISPATCH(var) == NULL\n");
    disp = V_DISPATCH(&var);

    hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
    IDispatch_Release(disp);
    ok(hres == S_OK, "Could not get IDispatchEx iface: %08x\n", hres);

    /* FIXME: Test InvokeEx(DISPATCH_METHOD) */

    memset(&dp, 0, sizeof(dp));
    memset(&ei, 0, sizeof(ei));
    VariantInit(&var);
    hres = IDispatchEx_Invoke(dispex, DISPID_VALUE, &IID_NULL, LOCALE_NEUTRAL, DISPATCH_METHOD, &dp, &var, &ei, NULL);
    ok(hres == S_OK || broken(E_ACCESSDENIED), "InvokeEx failed: %08x\n", hres);
    if(SUCCEEDED(hres)) {
        ok(V_VT(&var) == VT_BSTR, "V_VT(var)=%d\n", V_VT(&var));
        ok(!strcmp_wa(V_BSTR(&var), "[object]"), "V_BSTR(var) = %s\n", wine_dbgstr_w(V_BSTR(&var)));
        VariantClear(&var);
    }

    V_VT(&var) = VT_I4;
    V_I4(&var) = 100;
    hres = dispex_propput(obj, id, 0, &var);
    ok(hres == E_NOTIMPL, "InvokeEx failed: %08x\n", hres);

    IDispatchEx_Release(dispex);
}

static void test_nextdispid(IDispatchEx *dispex)
{
    DISPID last_id = DISPID_STARTENUM, id, dyn_id;
    BSTR name;
    VARIANT var;
    HRESULT hres;

    name = a2bstr("dynVal");
    hres = IDispatchEx_GetDispID(dispex, name, fdexNameCaseSensitive|fdexNameEnsure, &dyn_id);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);
    SysFreeString(name);

    V_VT(&var) = VT_EMPTY;
    hres = dispex_propput(dispex, dyn_id, 0, &var);

    while(last_id != dyn_id) {
        hres = IDispatchEx_GetNextDispID(dispex, fdexEnumAll, last_id, &id);
        ok(hres == S_OK, "GetNextDispID returned: %08x\n", hres);
        ok(id != DISPID_STARTENUM, "id == DISPID_STARTENUM\n");
        ok(id != DISPID_IOMNAVIGATOR_TOSTRING, "id == DISPID_IOMNAVIGATOR_TOSTRING\n");

        hres = IDispatchEx_GetMemberName(dispex, id, &name);
        ok(hres == S_OK, "GetMemberName failed: %08x\n", hres);

        if(id == dyn_id)
            ok(!strcmp_wa(name, "dynVal"), "name = %s\n", wine_dbgstr_w(name));
        else if(id == DISPID_IOMNAVIGATOR_PLATFORM)
            ok(!strcmp_wa(name, "platform"), "name = %s\n", wine_dbgstr_w(name));

        SysFreeString(name);
        last_id = id;
    }

    hres = IDispatchEx_GetNextDispID(dispex, 0, id, &id);
    ok(hres == S_FALSE, "GetNextDispID returned: %08x\n", hres);
    ok(id == DISPID_STARTENUM, "id != DISPID_STARTENUM\n");
}

static void test_global_id(void)
{
    VARIANT var;
    DISPPARAMS dp;
    EXCEPINFO ei;
    BSTR tmp;
    DISPID id;
    HRESULT hres;

    SET_EXPECT(GetScriptDispatch);
    SET_EXPECT(script_divid_d);
    tmp = a2bstr("divid");
    hres = IDispatchEx_GetDispID(window_dispex, tmp, fdexNameCaseSensitive, &id);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);
    SysFreeString(tmp);
    CHECK_CALLED(GetScriptDispatch);
    CHECK_CALLED(script_divid_d);

    VariantInit(&var);
    memset(&ei, 0, sizeof(ei));
    memset(&dp, 0, sizeof(dp));
    hres = IDispatchEx_InvokeEx(window_dispex, id, 0, DISPATCH_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_DISPATCH, "V_VT(var) = %d\n", V_VT(&var));
    VariantClear(&var);
}

static HRESULT WINAPI ActiveScriptParse_ParseScriptText(IActiveScriptParse *iface,
        LPCOLESTR pstrCode, LPCOLESTR pstrItemName, IUnknown *punkContext,
        LPCOLESTR pstrDelimiter, CTXARG_T dwSourceContextCookie, ULONG ulStartingLine,
        DWORD dwFlags, VARIANT *pvarResult, EXCEPINFO *pexcepinfo)
{
    IDispatchEx *document, *dispex;
    IHTMLWindow2 *window;
    IOmNavigator *navigator;
    IUnknown *unk;
    VARIANT var, arg;
    DISPPARAMS dp;
    EXCEPINFO ei;
    DISPID id;
    BSTR tmp;
    HRESULT hres;

    static const WCHAR documentW[] = {'d','o','c','u','m','e','n','t',0};
    static const WCHAR testW[] = {'t','e','s','t',0};
    static const WCHAR funcW[] = {'f','u','n','c',0};

    CHECK_EXPECT(ParseScriptText);

    SET_EXPECT(GetScriptDispatch);

    tmp = SysAllocString(documentW);
    hres = IDispatchEx_GetDispID(window_dispex, tmp, fdexNameCaseSensitive, &id);
    SysFreeString(tmp);
    ok(hres == S_OK, "GetDispID(document) failed: %08x\n", hres);
    ok(id == DISPID_IHTMLWINDOW2_DOCUMENT, "id=%x\n", id);

    CHECK_CALLED(GetScriptDispatch);

    VariantInit(&var);
    memset(&dp, 0, sizeof(dp));
    memset(&ei, 0, sizeof(ei));

    hres = IDispatchEx_InvokeEx(window_dispex, id, LOCALE_NEUTRAL, INVOKE_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_DISPATCH, "V_VT(var)=%d\n", V_VT(&var));
    ok(V_DISPATCH(&var) != NULL, "V_DISPATCH(&var) == NULL\n");

    hres = IDispatch_QueryInterface(V_DISPATCH(&var), &IID_IDispatchEx, (void**)&document);
    VariantClear(&var);
    ok(hres == S_OK, "Could not get DispatchEx: %08x\n", hres);

    tmp = SysAllocString(testW);
    hres = IDispatchEx_GetDispID(document, tmp, fdexNameCaseSensitive, &id);
    ok(hres == DISP_E_UNKNOWNNAME, "GetDispID(document) failed: %08x, expected DISP_E_UNKNOWNNAME\n", hres);
    hres = IDispatchEx_GetDispID(document, tmp, fdexNameCaseSensitive | fdexNameImplicit, &id);
    ok(hres == DISP_E_UNKNOWNNAME, "GetDispID(document) failed: %08x, expected DISP_E_UNKNOWNNAME\n", hres);
    SysFreeString(tmp);

    id = 0;
    tmp = SysAllocString(testW);
    hres = IDispatchEx_GetDispID(document, tmp, fdexNameCaseSensitive|fdexNameEnsure, &id);
    SysFreeString(tmp);
    ok(hres == S_OK, "GetDispID(document) failed: %08x\n", hres);
    ok(id, "id == 0\n");

    V_VT(&var) = VT_I4;
    V_I4(&var) = 100;
    hres = dispex_propput(document, id, 0, &var);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);

    tmp = SysAllocString(testW);
    hres = IDispatchEx_GetDispID(document, tmp, fdexNameCaseSensitive, &id);
    SysFreeString(tmp);
    ok(hres == S_OK, "GetDispID(document) failed: %08x\n", hres);

    VariantInit(&var);
    memset(&dp, 0, sizeof(dp));
    memset(&ei, 0, sizeof(ei));
    hres = IDispatchEx_InvokeEx(document, id, LOCALE_NEUTRAL, INVOKE_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_I4, "V_VT(var)=%d\n", V_VT(&var));
    ok(V_I4(&var) == 100, "V_I4(&var) = %d\n", V_I4(&var));

    V_VT(&var) = VT_I4;
    V_I4(&var) = 200;
    hres = dispex_propput(document, id, DISPATCH_PROPERTYPUTREF, &var);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);

    VariantInit(&var);
    memset(&dp, 0, sizeof(dp));
    memset(&ei, 0, sizeof(ei));
    hres = IDispatchEx_InvokeEx(document, id, LOCALE_NEUTRAL, INVOKE_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_I4, "V_VT(var)=%d\n", V_VT(&var));
    ok(V_I4(&var) == 200, "V_I4(&var) = %d\n", V_I4(&var));

    memset(&dp, 0, sizeof(dp));
    memset(&ei, 0, sizeof(ei));
    V_VT(&var) = VT_I4;
    V_I4(&var) = 300;
    dp.cArgs = 1;
    dp.rgvarg = &var;
    hres = IDispatchEx_InvokeEx(document, id, LOCALE_NEUTRAL, INVOKE_PROPERTYPUT, &dp, NULL, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);

    VariantInit(&var);
    memset(&dp, 0, sizeof(dp));
    memset(&ei, 0, sizeof(ei));
    hres = IDispatchEx_InvokeEx(document, id, LOCALE_NEUTRAL, INVOKE_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_I4, "V_VT(var)=%d\n", V_VT(&var));
    ok(V_I4(&var) == 300, "V_I4(&var) = %d\n", V_I4(&var));

    unk = (void*)0xdeadbeef;
    hres = IDispatchEx_GetNameSpaceParent(window_dispex, &unk);
    ok(hres == S_OK, "GetNameSpaceParent failed: %08x\n", hres);
    ok(!unk, "unk=%p, expected NULL\n", unk);

    id = 0;
    tmp = SysAllocString(funcW);
    hres = IDispatchEx_GetDispID(document, tmp, fdexNameCaseSensitive|fdexNameEnsure, &id);
    SysFreeString(tmp);
    ok(hres == S_OK, "GetDispID(func) failed: %08x\n", hres);
    ok(id, "id == 0\n");

    dp.cArgs = 1;
    dp.rgvarg = &var;
    dp.cNamedArgs = 0;
    dp.rgdispidNamedArgs = NULL;
    V_VT(&var) = VT_DISPATCH;
    V_DISPATCH(&var) = (IDispatch*)&funcDisp;
    hres = IDispatchEx_InvokeEx(document, id, LOCALE_NEUTRAL, INVOKE_PROPERTYPUT, &dp, NULL, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);

    VariantInit(&var);
    memset(&dp, 0, sizeof(dp));
    memset(&ei, 0, sizeof(ei));
    V_VT(&arg) = VT_BOOL;
    V_BOOL(&arg) = VARIANT_TRUE;
    dp.cArgs = 1;
    dp.rgvarg = &arg;

    SET_EXPECT(funcDisp);
    hres = IDispatchEx_InvokeEx(document, id, LOCALE_NEUTRAL, INVOKE_FUNC, &dp, &var, &ei, NULL);
    CHECK_CALLED(funcDisp);

    ok(hres == S_OK, "InvokeEx(INVOKE_FUNC) failed: %08x\n", hres);
    ok(V_VT(&var) == VT_I4, "V_VT(var)=%d\n", V_VT(&var));
    ok(V_I4(&var) == 100, "V_I4(&var) == NULL\n");

    IDispatchEx_Release(document);

    hres = IDispatchEx_QueryInterface(window_dispex, &IID_IHTMLWindow2, (void**)&window);
    ok(hres == S_OK, "Could not get IHTMLWindow2 iface: %08x\n", hres);

    hres = IHTMLWindow2_get_navigator(window, &navigator);
    IHTMLWindow2_Release(window);
    ok(hres == S_OK, "get_navigator failed: %08x\n", hres);

    hres = IOmNavigator_QueryInterface(navigator, &IID_IDispatchEx, (void**)&dispex);
    IOmNavigator_Release(navigator);
    ok(hres == S_OK, "Could not get IDispatchEx iface: %08x\n", hres);

    test_func(dispex);
    test_nextdispid(dispex);

    tmp = a2bstr("test");
    hres = IDispatchEx_DeleteMemberByName(dispex, tmp, fdexNameCaseSensitive);
    ok(hres == E_NOTIMPL, "DeleteMemberByName failed: %08x\n", hres);

    IDispatchEx_Release(dispex);

    script_disp = (IDispatch*)&scriptDisp;

    SET_EXPECT(GetScriptDispatch);
    SET_EXPECT(script_testprop_d);
    tmp = a2bstr("testProp");
    hres = IDispatchEx_GetDispID(window_dispex, tmp, fdexNameCaseSensitive, &id);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);
    ok(id != DISPID_SCRIPT_TESTPROP, "id == DISPID_SCRIPT_TESTPROP\n");
    CHECK_CALLED(GetScriptDispatch);
    CHECK_CALLED(script_testprop_d);
    SysFreeString(tmp);

    tmp = a2bstr("testProp");
    hres = IDispatchEx_GetDispID(window_dispex, tmp, fdexNameCaseSensitive, &id);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);
    ok(id != DISPID_SCRIPT_TESTPROP, "id == DISPID_SCRIPT_TESTPROP\n");
    SysFreeString(tmp);

    SET_EXPECT(GetScriptDispatch);
    SET_EXPECT(script_testprop_i);
    memset(&ei, 0, sizeof(ei));
    memset(&dp, 0, sizeof(dp));
    hres = IDispatchEx_InvokeEx(window_dispex, id, 0, DISPATCH_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_NULL, "V_VT(var) = %d\n", V_VT(&var));
    CHECK_CALLED(GetScriptDispatch);
    CHECK_CALLED(script_testprop_i);

    SET_EXPECT(GetScriptDispatch);
    SET_EXPECT(script_testprop2_d);
    tmp = a2bstr("testProp2");
    hres = IDispatchEx_GetDispID(window_dispex, tmp, fdexNameCaseSensitive|fdexNameEnsure, &id);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);
    ok(id != DISPID_SCRIPT_TESTPROP2, "id == DISPID_SCRIPT_TESTPROP2\n");
    CHECK_CALLED(GetScriptDispatch);
    CHECK_CALLED(script_testprop2_d);
    SysFreeString(tmp);

    tmp = a2bstr("test");
    hres = IDispatchEx_DeleteMemberByName(window_dispex, tmp, fdexNameCaseSensitive);
    ok(hres == E_NOTIMPL, "DeleteMemberByName failed: %08x\n", hres);

    test_global_id();

    test_security();

    return S_OK;
}

static const IActiveScriptParseVtbl ActiveScriptParseVtbl = {
    ActiveScriptParse_QueryInterface,
    ActiveScriptParse_AddRef,
    ActiveScriptParse_Release,
    ActiveScriptParse_InitNew,
    ActiveScriptParse_AddScriptlet,
    ActiveScriptParse_ParseScriptText
};

static IActiveScriptParse ActiveScriptParse = { &ActiveScriptParseVtbl };

static HRESULT WINAPI ActiveScript_QueryInterface(IActiveScript *iface, REFIID riid, void **ppv)
{
    *ppv = NULL;

    if(IsEqualGUID(&IID_IUnknown, riid) || IsEqualGUID(&IID_IActiveScript, riid)) {
        *ppv = iface;
        return S_OK;
    }

    if(IsEqualGUID(&IID_IActiveScriptParse, riid)) {
        *ppv = &ActiveScriptParse;
        return S_OK;
    }

    if(IsEqualGUID(&IID_IActiveScriptParseProcedure2, riid)) {
        *ppv = &ActiveScriptParseProcedure;
        return S_OK;
    }

    if(IsEqualGUID(&IID_IActiveScriptProperty, riid)) {
        *ppv = &ActiveScriptProperty;
        return S_OK;
    }

    if(IsEqualGUID(&IID_IObjectSafety, riid)) {
        *ppv = &ObjectSafety;
        return S_OK;
    }

    if(IsEqualGUID(&IID_IActiveScriptDebug, riid))
        return E_NOINTERFACE;

    ok(0, "unexpected riid %s\n", debugstr_guid(riid));
    return E_NOINTERFACE;
}

static ULONG WINAPI ActiveScript_AddRef(IActiveScript *iface)
{
    return 2;
}

static ULONG WINAPI ActiveScript_Release(IActiveScript *iface)
{
    return 1;
}

static HRESULT WINAPI ActiveScript_SetScriptSite(IActiveScript *iface, IActiveScriptSite *pass)
{
    IActiveScriptSiteInterruptPoll *poll;
    IActiveScriptSiteDebug *debug;
    IServiceProvider *service;
    ICanHandleException *canexpection;
    LCID lcid;
    HRESULT hres;

    CHECK_EXPECT(SetScriptSite);

    ok(pass != NULL, "pass == NULL\n");

    hres = IActiveScriptSite_QueryInterface(pass, &IID_IActiveScriptSiteInterruptPoll, (void**)&poll);
    ok(hres == S_OK, "Could not get IActiveScriptSiteInterruptPoll interface: %08x\n", hres);
    if(FAILED(hres))
        IActiveScriptSiteInterruptPoll_Release(poll);

    hres = IActiveScriptSite_GetLCID(pass, &lcid);
    ok(hres == S_OK, "GetLCID failed: %08x\n", hres);

    hres = IActiveScriptSite_OnStateChange(pass, (state = SCRIPTSTATE_INITIALIZED));
    ok(hres == S_OK, "OnStateChange failed: %08x\n", hres);

    hres = IActiveScriptSite_QueryInterface(pass, &IID_IActiveScriptSiteDebug, (void**)&debug);
    ok(hres == S_OK, "Could not get IActiveScriptSiteDebug interface: %08x\n", hres);
    if(SUCCEEDED(hres))
        IActiveScriptSiteDebug32_Release(debug);

    hres = IActiveScriptSite_QueryInterface(pass, &IID_ICanHandleException, (void**)&canexpection);
    ok(hres == E_NOINTERFACE, "Could not get IID_ICanHandleException interface: %08x\n", hres);

    hres = IActiveScriptSite_QueryInterface(pass, &IID_IServiceProvider, (void**)&service);
    ok(hres == S_OK, "Could not get IServiceProvider interface: %08x\n", hres);
    if(SUCCEEDED(hres))
        IServiceProvider_Release(service);

    site = pass;
    IActiveScriptSite_AddRef(site);
    return S_OK;
}

static HRESULT WINAPI ActiveScript_GetScriptSite(IActiveScript *iface, REFIID riid,
                                            void **ppvObject)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ActiveScript_SetScriptState(IActiveScript *iface, SCRIPTSTATE ss)
{
    HRESULT hres;

    switch(ss) {
    case SCRIPTSTATE_STARTED:
        CHECK_EXPECT(SetScriptState_STARTED);
        break;
    case SCRIPTSTATE_CONNECTED:
        CHECK_EXPECT(SetScriptState_CONNECTED);
        break;
    case SCRIPTSTATE_DISCONNECTED:
        CHECK_EXPECT(SetScriptState_DISCONNECTED);
        break;
    default:
        ok(0, "unexpected state %d\n", ss);
        return E_NOTIMPL;
    }

    hres = IActiveScriptSite_OnStateChange(site, (state = ss));
    ok(hres == S_OK, "OnStateChange failed: %08x\n", hres);

    return S_OK;
}

static HRESULT WINAPI ActiveScript_GetScriptState(IActiveScript *iface, SCRIPTSTATE *pssState)
{
    CHECK_EXPECT(GetScriptState);

    *pssState = state;
    return S_OK;
}

static HRESULT WINAPI ActiveScript_Close(IActiveScript *iface)
{
    CHECK_EXPECT(Close);
    return E_NOTIMPL;
}

static HRESULT WINAPI ActiveScript_AddNamedItem(IActiveScript *iface,
        LPCOLESTR pstrName, DWORD dwFlags)
{
    IDispatch *disp;
    IUnknown *unk = NULL, *unk2;
    HRESULT hres;

    static const WCHAR windowW[] = {'w','i','n','d','o','w',0};

    static const IID unknown_iid = {0x719C3050,0xF9D3,0x11CF,{0xA4,0x93,0x00,0x40,0x05,0x23,0xA8,0xA0}};

    CHECK_EXPECT(AddNamedItem);

    ok(!lstrcmpW(pstrName, windowW), "pstrName=%s\n", wine_dbgstr_w(pstrName));
    ok(dwFlags == (SCRIPTITEM_ISVISIBLE|SCRIPTITEM_ISSOURCE|SCRIPTITEM_GLOBALMEMBERS), "dwFlags=%x\n", dwFlags);

    hres = IActiveScriptSite_GetItemInfo(site, windowW, SCRIPTINFO_IUNKNOWN, &unk, NULL);
    ok(hres == S_OK, "GetItemInfo failed: %08x\n", hres);
    ok(unk != NULL, "unk == NULL\n");

    hres = IUnknown_QueryInterface(unk, &IID_IDispatch, (void**)&disp);
    ok(hres == S_OK, "Could not get IDispatch interface: %08x\n", hres);
    if(SUCCEEDED(hres))
        IDispatch_Release(disp);

    hres = IUnknown_QueryInterface(unk, &unknown_iid, (void**)&unk2);
    ok(hres == E_NOINTERFACE, "Got ?? interface: %p\n", unk2);
    if(SUCCEEDED(hres))
        IUnknown_Release(unk2);

    hres = IUnknown_QueryInterface(unk, &IID_IDispatchEx, (void**)&window_dispex);
    ok(hres == S_OK, "Could not get IDispatchEx interface: %08x\n", hres);

    IUnknown_Release(unk);
    return S_OK;
}

static HRESULT WINAPI ActiveScript_AddTypeLib(IActiveScript *iface, REFGUID rguidTypeLib,
                                         DWORD dwMajor, DWORD dwMinor, DWORD dwFlags)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ActiveScript_GetScriptDispatch(IActiveScript *iface, LPCOLESTR pstrItemName,
                                                IDispatch **ppdisp)
{
    CHECK_EXPECT(GetScriptDispatch);

    ok(!strcmp_wa(pstrItemName, "window"), "pstrItemName = %s\n", wine_dbgstr_w(pstrItemName));

    if(!script_disp)
        return E_NOTIMPL;

    *ppdisp = script_disp;
    return S_OK;
}

static HRESULT WINAPI ActiveScript_GetCurrentScriptThreadID(IActiveScript *iface,
                                                       SCRIPTTHREADID *pstridThread)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ActiveScript_GetScriptThreadID(IActiveScript *iface,
                                                DWORD dwWin32ThreadId, SCRIPTTHREADID *pstidThread)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ActiveScript_GetScriptThreadState(IActiveScript *iface,
        SCRIPTTHREADID stidThread, SCRIPTTHREADSTATE *pstsState)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ActiveScript_InterruptScriptThread(IActiveScript *iface,
        SCRIPTTHREADID stidThread, const EXCEPINFO *pexcepinfo, DWORD dwFlags)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI ActiveScript_Clone(IActiveScript *iface, IActiveScript **ppscript)
{
    ok(0, "unexpected call\n");
    return E_NOTIMPL;
}

static const IActiveScriptVtbl ActiveScriptVtbl = {
    ActiveScript_QueryInterface,
    ActiveScript_AddRef,
    ActiveScript_Release,
    ActiveScript_SetScriptSite,
    ActiveScript_GetScriptSite,
    ActiveScript_SetScriptState,
    ActiveScript_GetScriptState,
    ActiveScript_Close,
    ActiveScript_AddNamedItem,
    ActiveScript_AddTypeLib,
    ActiveScript_GetScriptDispatch,
    ActiveScript_GetCurrentScriptThreadID,
    ActiveScript_GetScriptThreadID,
    ActiveScript_GetScriptThreadState,
    ActiveScript_InterruptScriptThread,
    ActiveScript_Clone
};

static IActiveScript ActiveScript = { &ActiveScriptVtbl };

static HRESULT WINAPI ClassFactory_QueryInterface(IClassFactory *iface, REFIID riid, void **ppv)
{
    *ppv = NULL;

    if(IsEqualGUID(&IID_IUnknown, riid) || IsEqualGUID(&IID_IClassFactory, riid)) {
        *ppv = iface;
        return S_OK;
    }

    if(IsEqualGUID(&IID_IMarshal, riid))
        return E_NOINTERFACE;
    if(IsEqualGUID(&CLSID_IdentityUnmarshal, riid))
        return E_NOINTERFACE;

    ok(0, "unexpected riid %s\n", debugstr_guid(riid));
    return E_NOTIMPL;
}

static ULONG WINAPI ClassFactory_AddRef(IClassFactory *iface)
{
    return 2;
}

static ULONG WINAPI ClassFactory_Release(IClassFactory *iface)
{
    return 1;
}

static HRESULT WINAPI ClassFactory_CreateInstance(IClassFactory *iface, IUnknown *outer, REFIID riid, void **ppv)
{
    CHECK_EXPECT(CreateInstance);

    ok(!outer, "outer = %p\n", outer);
    ok(IsEqualGUID(&IID_IActiveScript, riid), "unexpected riid %s\n", debugstr_guid(riid));
    *ppv = &ActiveScript;
    return S_OK;
}

static HRESULT WINAPI ClassFactory_LockServer(IClassFactory *iface, BOOL dolock)
{
    ok(0, "unexpected call\n");
    return S_OK;
}

static const IClassFactoryVtbl ClassFactoryVtbl = {
    ClassFactory_QueryInterface,
    ClassFactory_AddRef,
    ClassFactory_Release,
    ClassFactory_CreateInstance,
    ClassFactory_LockServer
};

static IClassFactory script_cf = { &ClassFactoryVtbl };

static const char simple_script_str[] =
    "<html><head></head><body>"
    "<div id=\"divid\"></div>"
    "<script language=\"TestScript\">simple script</script>"
    "</body></html>";

static void test_simple_script(void)
{
    IHTMLDocument2 *doc;

    doc = create_document();
    if(!doc)
        return;

    SET_EXPECT(CreateInstance);
    SET_EXPECT(GetInterfaceSafetyOptions);
    SET_EXPECT(SetInterfaceSafetyOptions);
    SET_EXPECT(SetProperty_INVOKEVERSIONING); /* IE8 */
    SET_EXPECT(SetProperty_HACK_TRIDENTEVENTSINK);
    SET_EXPECT(InitNew);
    SET_EXPECT(SetScriptSite);
    SET_EXPECT(GetScriptState);
    SET_EXPECT(SetScriptState_STARTED);
    SET_EXPECT(AddNamedItem);
    SET_EXPECT(SetProperty_ABBREVIATE_GLOBALNAME_RESOLUTION); /* IE8 */
    SET_EXPECT(ParseScriptText);
    SET_EXPECT(SetScriptState_CONNECTED);

    load_doc(doc, simple_script_str);

    CHECK_CALLED(CreateInstance);
    CHECK_CALLED(GetInterfaceSafetyOptions);
    CHECK_CALLED(SetInterfaceSafetyOptions);
    CHECK_CALLED_BROKEN(SetProperty_INVOKEVERSIONING); /* IE8 */
    CHECK_CALLED(SetProperty_HACK_TRIDENTEVENTSINK);
    CHECK_CALLED(InitNew);
    CHECK_CALLED(SetScriptSite);
    CHECK_CALLED(GetScriptState);
    CHECK_CALLED(SetScriptState_STARTED);
    CHECK_CALLED(AddNamedItem);
    CHECK_CALLED_BROKEN(SetProperty_ABBREVIATE_GLOBALNAME_RESOLUTION); /* IE8 */
    CHECK_CALLED(ParseScriptText);
    CHECK_CALLED(SetScriptState_CONNECTED);

    if(site)
        IActiveScriptSite_Release(site);
    if(window_dispex)
        IDispatchEx_Release(window_dispex);

    SET_EXPECT(SetScriptState_DISCONNECTED);
    SET_EXPECT(Close);

    IHTMLDocument2_Release(doc);

    CHECK_CALLED(SetScriptState_DISCONNECTED);
    CHECK_CALLED(Close);
}

static void run_js_script(const char *test_name)
{
    WCHAR url[INTERNET_MAX_URL_LENGTH];
    char urlA[INTERNET_MAX_URL_LENGTH];
    IPersistMoniker *persist;
    IHTMLDocument2 *doc;
    IMoniker *mon;
    MSG msg;
    HRESULT hres;

    static const char res[] = "res://";

    trace("running %s...\n", test_name);

    doc = create_document();
    if(!doc)
        return;

    set_client_site(doc, TRUE);
    do_advise(doc, &IID_IPropertyNotifySink, (IUnknown*)&PropertyNotifySink);

    lstrcpyA(urlA, res);
    GetModuleFileNameA(NULL, urlA + lstrlenA(res), sizeof(urlA) - lstrlenA(res));
    lstrcatA(urlA, "/");
    lstrcatA(urlA, test_name);
    MultiByteToWideChar(CP_ACP, 0, urlA, -1, url, sizeof(url)/sizeof(WCHAR));

    hres = CreateURLMoniker(NULL, url, &mon);
    ok(hres == S_OK, "CreateURLMoniker failed: %08x\n", hres);

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IPersistMoniker, (void**)&persist);
    ok(hres == S_OK, "Could not get IPersistMoniker iface: %08x\n", hres);

    hres = IPersistMoniker_Load(persist, FALSE, mon, NULL, 0);
    ok(hres == S_OK, "Load failed: %08x\n", hres);

    IMoniker_Release(mon);
    IPersistMoniker_Release(persist);

    SET_EXPECT(external_success);

    while(!called_external_success && GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CHECK_CALLED(external_success);

    set_client_site(doc, FALSE);
    IHTMLDocument2_Release(doc);
}

static void run_js_tests(void)
{
    run_js_script("jstest.html");
}

static BOOL init_registry(BOOL init)
{
    return init_key("TestScript\\CLSID", TESTSCRIPT_CLSID, init)
        && init_key("CLSID\\"TESTSCRIPT_CLSID"\\Implemented Categories\\{F0B7A1A1-9847-11CF-8F20-00805F2CD064}",
                    NULL, init)
        && init_key("CLSID\\"TESTSCRIPT_CLSID"\\Implemented Categories\\{F0B7A1A2-9847-11CF-8F20-00805F2CD064}",
                    NULL, init);
}

static BOOL register_script_engine(void)
{
    DWORD regid;
    HRESULT hres;

    if(!init_registry(TRUE)) {
        init_registry(FALSE);
        return FALSE;
    }

    hres = CoRegisterClassObject(&CLSID_TestScript, (IUnknown *)&script_cf,
                                 CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &regid);
    ok(hres == S_OK, "Could not register screipt engine: %08x\n", hres);

    return TRUE;
}

static LRESULT WINAPI wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

static HWND create_container_window(void)
{
    static const CHAR szHTMLDocumentTest[] = "HTMLDocumentTest";
    static WNDCLASSEXA wndclass = {
        sizeof(WNDCLASSEXA),
        0,
        wnd_proc,
        0, 0, NULL, NULL, NULL, NULL, NULL,
        szHTMLDocumentTest,
        NULL
    };

    RegisterClassExA(&wndclass);
    return CreateWindowA(szHTMLDocumentTest, szHTMLDocumentTest,
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            300, 300, NULL, NULL, NULL, NULL);
}

START_TEST(script)
{
    CoInitialize(NULL);
    container_hwnd = create_container_window();

    if(winetest_interactive || ! is_ie_hardened()) {
        if(register_script_engine()) {
            test_simple_script();
            run_js_tests();
            init_registry(FALSE);
        }else {
            skip("Could not register TestScript engine\n");
        }
    }else {
        skip("IE running in Enhanced Security Configuration\n");
    }

    DestroyWindow(container_hwnd);
    CoUninitialize();
}
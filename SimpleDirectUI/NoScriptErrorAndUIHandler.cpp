#include "stdafx.h"
#include "NoScriptErrorAndUIHandler.h"

using namespace SDUI;

CNoScriptErrorAndUIHandler::CNoScriptErrorAndUIHandler()
{
}


CNoScriptErrorAndUIHandler::~CNoScriptErrorAndUIHandler()
{
}

HRESULT CNoScriptErrorAndUIHandler::SetHandler(IDispatch * pDisp)
{
	CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> spWebBrowser(pDisp);
	if (spWebBrowser)
	{
		CComPtr<IDispatch> spDisp;
		spWebBrowser->get_Document(&spDisp);

		CComQIPtr<IOleObject, &IID_IOleObject> spOleObject(spDisp);
		if (spOleObject)
		{
			CComPtr<IOleClientSite> spClientSite;
			spOleObject->GetClientSite(&spClientSite);
			if (spClientSite)
			{
				m_spDefaultOleCommandTarget = spClientSite;
				m_spDefaultDocHostUIHandler = spClientSite;				
			}

			CComQIPtr<ICustomDoc, &IID_ICustomDoc> spCustomDoc(spDisp);
			if (spCustomDoc)
			{
				HRESULT hr = spCustomDoc->SetUIHandler(this);

				return hr;
			}
		}
	}

	return E_FAIL;
}

HRESULT CNoScriptErrorAndUIHandler::QueryStatus(const GUID * pguidCmdGroup, ULONG cCmds, OLECMD prgCmds[], OLECMDTEXT * pCmdText)
{
	return m_spDefaultOleCommandTarget->QueryStatus(pguidCmdGroup, cCmds, prgCmds, pCmdText);
}

HRESULT CNoScriptErrorAndUIHandler::Exec(const GUID * pguidCmdGroup, DWORD nCmdID, DWORD nCmdexecopt, VARIANT * pvaIn, VARIANT * pvaOut)
{
	if (nCmdID == OLECMDID_SHOWSCRIPTERROR)
	{		
		(*pvaOut).vt = VT_BOOL;
		(*pvaOut).boolVal = VARIANT_TRUE;

		return S_OK;
	}

	return m_spDefaultOleCommandTarget->Exec(pguidCmdGroup, nCmdID, nCmdexecopt, pvaIn, pvaOut);
}

HRESULT CNoScriptErrorAndUIHandler::ShowContextMenu(DWORD dwID, POINT * ppt, IUnknown * pcmdtReserved, IDispatch * pdispReserved)
{
	return S_OK;
}

HRESULT CNoScriptErrorAndUIHandler::GetHostInfo(DOCHOSTUIINFO * pInfo)
{
	return m_spDefaultDocHostUIHandler->GetHostInfo(pInfo);
}

HRESULT CNoScriptErrorAndUIHandler::ShowUI(DWORD dwID, IOleInPlaceActiveObject * pActiveObject, IOleCommandTarget * pCommandTarget, IOleInPlaceFrame * pFrame, IOleInPlaceUIWindow * pDoc)
{
	return m_spDefaultDocHostUIHandler->ShowUI(dwID, pActiveObject, pCommandTarget, pFrame, pDoc);
}

HRESULT CNoScriptErrorAndUIHandler::HideUI(void)
{
	return m_spDefaultDocHostUIHandler->HideUI();
}

HRESULT CNoScriptErrorAndUIHandler::UpdateUI(void)
{
	return m_spDefaultDocHostUIHandler->UpdateUI();
}

HRESULT CNoScriptErrorAndUIHandler::EnableModeless(BOOL fEnable)
{
	return m_spDefaultDocHostUIHandler->EnableModeless(fEnable);
}

HRESULT CNoScriptErrorAndUIHandler::OnDocWindowActivate(BOOL fActivate)
{
	return m_spDefaultDocHostUIHandler->OnDocWindowActivate(fActivate);
}

HRESULT CNoScriptErrorAndUIHandler::OnFrameWindowActivate(BOOL fActivate)
{
	return m_spDefaultDocHostUIHandler->OnFrameWindowActivate(fActivate);
}

HRESULT CNoScriptErrorAndUIHandler::ResizeBorder(LPCRECT prcBorder, IOleInPlaceUIWindow * pUIWindow, BOOL fRameWindow)
{
	return m_spDefaultDocHostUIHandler->ResizeBorder(prcBorder, pUIWindow, fRameWindow);
}

HRESULT CNoScriptErrorAndUIHandler::TranslateAccelerator(LPMSG lpMsg, const GUID * pguidCmdGroup, DWORD nCmdID)
{
	return m_spDefaultDocHostUIHandler->TranslateAccelerator(lpMsg, pguidCmdGroup, nCmdID);
}

HRESULT CNoScriptErrorAndUIHandler::GetOptionKeyPath(LPOLESTR * pchKey, DWORD dw)
{
	return m_spDefaultDocHostUIHandler->GetOptionKeyPath(pchKey, dw);
}

HRESULT CNoScriptErrorAndUIHandler::GetDropTarget(IDropTarget * pDropTarget, IDropTarget ** ppDropTarget)
{
	return m_spDefaultDocHostUIHandler->GetDropTarget(pDropTarget, ppDropTarget);
}

HRESULT CNoScriptErrorAndUIHandler::GetExternal(IDispatch ** ppDispatch)
{
	return m_spDefaultDocHostUIHandler->GetExternal(ppDispatch);
}

HRESULT CNoScriptErrorAndUIHandler::TranslateUrl(DWORD dwTranslate, LPWSTR pchURLIn, LPWSTR * ppchURLOut)
{
	return m_spDefaultDocHostUIHandler->TranslateUrl(dwTranslate, pchURLIn, ppchURLOut);
}

HRESULT CNoScriptErrorAndUIHandler::FilterDataObject(IDataObject * pDO, IDataObject ** ppDORet)
{
	return m_spDefaultDocHostUIHandler->FilterDataObject(pDO, ppDORet);
}

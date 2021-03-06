#include "stdafx.h"
#include "WebBrowserEvents.h"
#include "WebBrowserControl.h"
#include "Control.h"
#include "Eventx.h"

using namespace SDUI;

CWebBrowserEvents::CWebBrowserEvents() : m_owner(nullptr)
{
}


CWebBrowserEvents::~CWebBrowserEvents()
{
}

HRESULT CWebBrowserEvents::FinalConstruct()
{	
	return S_OK;
}

bool SDUI::CWebBrowserEvents::setOwner(CControl* owner)
{
	if (m_owner)
	{
		return false;
	}

	m_owner = owner;

	return true;
}

void CWebBrowserEvents::OnBeforeNavigate2(IDispatch** ppDisp, VARIANT* vUrl, VARIANT* vFlags, VARIANT* vTargetFrameName, VARIANT* vPostData, VARIANT* vHeaders, VARIANT_BOOL* vbCancel)
{
	if (vUrl && vUrl->vt == VT_BSTR)
	{
		CComBSTR bstrUrl(vUrl->bstrVal);

		USES_CONVERSION;
		CEventx* pEvent = new CEventx(EV_WB_NAVIGATE, m_owner, (void*)W2CA(bstrUrl));
		m_owner->dispatchEvent(pEvent);

		*vbCancel = (VARIANT_BOOL)pEvent->getRetval();

		delete pEvent;
	}
}

void SDUI::CWebBrowserEvents::OnNewWindow3(IDispatch** ppDisp, VARIANT_BOOL* vbCancel, LONG dwFlags, BSTR bstrUrlContext, BSTR bstrUrl)
{
	USES_CONVERSION;
	CEventx* pEvent = new CEventx(EV_WB_NEWWINDOW3, m_owner, (void*)W2CA(bstrUrl));
	m_owner->dispatchEvent(pEvent);

	*vbCancel = (VARIANT_BOOL)pEvent->getRetval();

	delete pEvent;
}

void CWebBrowserEvents::OnDocumentComplete(IDispatch* pDisp, VARIANT* vUrl)
{	
	CEventx* pEvent = new CEventx(EV_WB_DOCCMPLETE, m_owner, NULL);
	m_owner->dispatchEvent(pEvent);

	delete pEvent;
}
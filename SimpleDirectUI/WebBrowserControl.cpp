#include "stdafx.h"
#include "HostWindow.h"
#include "WebBrowserControl.h"
#include "WebBrowserEvents.h"
#include "OleClientSiteImpl.h"
#include "XmlAttribute.h"

using namespace SDUI;


DYNAMIC_OBJECT_CREATE("WebBrowser", CWebBrowserControl, CObjectx)

CWebBrowserControl::CWebBrowserControl() : m_child(true), m_debug(false), m_transacc(false), m_rb(false)
{
}


CWebBrowserControl::~CWebBrowserControl()
{
}

bool CWebBrowserControl::createFromXml(CXmlAttribute* attr)
{
	CControl::createFromXml(attr);

	std::string child;
	if (attr->getAttribute("child", child))
	{
		setChild(CXmlAttribute::_stringToBoolean(child));
	}

	std::string transacc;
	if (attr->getAttribute("transacc", transacc))
	{
		setTransAcc(CXmlAttribute::_stringToBoolean(transacc));
	}

	std::string transrb;
	if (attr->getAttribute("transrb", transrb))
	{
		setTransRb(transrb);
		if (!m_transrb.empty())
		{
			m_rb = true;
		}		
	}

	std::string page;
	if (attr->getAttribute("page", page))
	{
		setPage(page);
	}

	std::string debug;
	if (attr->getAttribute("debug", debug))
	{
		setDebug(CXmlAttribute::_stringToBoolean(debug));
	}

	return true;
}

unsigned int CWebBrowserControl::addChild(CControl* control)
{
	ATLASSERT(FALSE);

	return 0;
}

void SDUI::CWebBrowserControl::show(bool show)
{
	if (!m_acxWindow.IsWindow())
	{
		return;
	}

	if (show)
	{
		if (m_acxWindow.IsWindowVisible())
		{
			return;
		}

		if (m_child)
		{
			m_acxWindow.ShowWindow(SW_SHOWNA);
		}
		else
		{
			m_acxWindow.SetWindowPos(HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
			::SetWindowPos(m_hostWindow->getHwnd(), m_acxWindow.m_hWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
		}
	}
	else 
	{
		if (!m_acxWindow.IsWindowVisible())
		{
			return;
		}

		if (m_child)
		{
			m_acxWindow.ShowWindow(SW_HIDE);
		}
		else
		{
			m_acxWindow.SetWindowPos(0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_HIDEWINDOW);
		}
	}

	CControl::show(show);
}

bool CWebBrowserControl::preTranslateMessage(LPMSG lpMsg)
{	
	if (m_transacc && lpMsg->message >= WM_KEYFIRST && lpMsg->message <= WM_KEYLAST)
	{
		if (::IsChild(m_acxWindow.m_hWnd, lpMsg->hwnd) || m_acxWindow.m_hWnd == lpMsg->hwnd)
		{
			if (m_spWebBrowser)
			{
				CComPtr<IDispatch> spDisp;
				m_spWebBrowser->get_Document(&spDisp);
				CComQIPtr<IOleInPlaceActiveObject> spInPlaceActiveObject = spDisp;
				if (spInPlaceActiveObject)
				{
					return S_OK == spInPlaceActiveObject->TranslateAccelerator(lpMsg) ? true : false;
				}
			}
		}		
	}

	if (m_rb && (lpMsg->message == WM_RBUTTONDOWN || lpMsg->message == WM_RBUTTONUP))
	{
		if (::IsChild(m_acxWindow.m_hWnd, lpMsg->hwnd) || m_acxWindow.m_hWnd == lpMsg->hwnd)
		{	
			if (m_transrb.compare("left") == 0)
			{
				int x = GET_X_LPARAM(lpMsg->lParam);
				int y = GET_Y_LPARAM(lpMsg->lParam);

				mouse_event(lpMsg->message == WM_RBUTTONDOWN ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP, x, y, 0, 0);
			}

			return true;
		}		
	}

	return false;
}



bool CWebBrowserControl::navigate(const std::string& url)
{
	setPage(url);

	HRESULT hr = S_FALSE;

	if (m_spWebBrowser && !url.empty())
	{
		USES_CONVERSION;
		hr = m_spWebBrowser->Navigate(A2W(url.c_str()), NULL, NULL, NULL, NULL);		
	}	

	return SUCCEEDED(hr);
}

bool CWebBrowserControl::stop()
{
	if (m_spWebBrowser)
	{
		HRESULT hr = m_spWebBrowser->Stop();
		return SUCCEEDED(hr);
	}

	return false;
}

bool CWebBrowserControl::refresh()
{
	if (m_spWebBrowser)
	{
		HRESULT hr = m_spWebBrowser->Refresh();
		return SUCCEEDED(hr);
	}

	return false;
}

void CWebBrowserControl::setPage(const std::string& page)
{
	m_page = page;
}

void CWebBrowserControl::setTransAcc(bool transAcc)
{
	m_transacc = transAcc;
}

void SDUI::CWebBrowserControl::setTransRb(const std::string& transRb)
{
	m_transrb = transRb;
}

void CWebBrowserControl::setChild(bool child)
{
	m_child = child;
}

void SDUI::CWebBrowserControl::setDebug(bool debug)
{
	m_debug = debug;
}

int CWebBrowserControl::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	int lr = CControl::onMessage(message, wparam, lparam, handled);

	if (m_child)
	{
		_onChildMessage(message, wparam, lparam, handled);
	}
	else
	{
		_onLinkageMessage(message, wparam, lparam, handled);
	}
		
	return lr;
}

int CWebBrowserControl::_onChildMessage(unsigned int message, unsigned int wparam, int lparam, bool & handled)
{
	if (message == WindowCreated)
	{
		Application::getInstance()->addMessageFilter(this);

		RECT rc{ m_x, m_y, m_x + m_cx, m_y + m_cy };
		m_acxWindow.Create(m_hostWindow->getHwnd(), rc, 0, WS_CHILD);

		if (_initWebBrowserActiveX())
		{
			navigate(m_page);
		}
	}
	else if (message == WindowSize)
	{
		if (m_acxWindow.IsWindow())
		{
			m_acxWindow.SetWindowPos(0, m_xx, m_yy, m_cxcx, m_cycy, SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
		}
	}
	else if (message == WindowShowWindow)
	{
		if ((BOOL)wparam && m_visible)
		{			
			m_acxWindow.ShowWindow(SW_SHOWNA);
		}
		else
		{
			m_acxWindow.ShowWindow(SW_HIDE);
		}
		
	}

	return 0;
}

int CWebBrowserControl::_onLinkageMessage(unsigned int message, unsigned int wparam, int lparam, bool & handled)
{
	if (message == WindowCreated)
	{
		Application::getInstance()->addMessageFilter(this);

		RECT rc{ m_x, m_y, m_x + m_cx, m_y + m_cy };
		m_acxWindow.Create(0, rc);
		if (_initWebBrowserActiveX())
		{
			navigate(m_page);
		}
	}
	else if (message == WindowSize)
	{
		if (wparam == SIZE_MINIMIZED)
		{
			m_acxWindow.SetWindowPos(0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_HIDEWINDOW);
		}
		else
		{
			POINT pt = { m_xx, m_yy };
			ClientToScreen(m_hostWindow->getHwnd(), &pt);
			
			if (m_visible)
			{
				m_acxWindow.SetWindowPos(HWND_TOP, pt.x, pt.y, m_cxcx, m_cycy, SWP_NOACTIVATE | SWP_SHOWWINDOW);
			}
			else
			{
				m_acxWindow.SetWindowPos(HWND_TOP, pt.x, pt.y, m_cxcx, m_cycy, SWP_NOACTIVATE);
			}
			
			::SetWindowPos(m_hostWindow->getHwnd(), m_acxWindow.m_hWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
		}
	}
	else if (message == WindowMove)
	{
		int x = m_x + GET_X_LPARAM(lparam);
		int y = m_y + GET_Y_LPARAM(lparam);

		// 调整位置，不调整Z序
		m_acxWindow.SetWindowPos(0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
	}
	else if (message == WindowWindowPosChanged)
	{
		LPWINDOWPOS lp = (LPWINDOWPOS)lparam;
		
		// 使用Centerwindow时，调用SetWindowPos 不会发送Moving消息 这里需要处理一下
		if (lp && lp->flags^SWP_NOMOVE)
		{
			int x = m_x + lp->x;
			int y = m_y + lp->y;
			m_acxWindow.SetWindowPos(HWND_TOP, x, y, 0, 0, SWP_NOSIZE | SWP_NOREDRAW | SWP_NOACTIVATE);
		}
		else
		{
			// 调整Z序，不调整位置
			m_acxWindow.SetWindowPos(HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOACTIVATE);
		}
				
		::SetWindowPos(m_hostWindow->getHwnd(), m_acxWindow.m_hWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
	}
	else if (message == WindowActiveApp)
	{
		if ((BOOL)wparam)
		{
			// 调整Z序，不调整位置			
			m_acxWindow.SetWindowPos(HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);					
			::SetWindowPos(m_hostWindow->getHwnd(), m_acxWindow.m_hWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
		}		
	}
	else if (message == WindowShowWindow)
	{
		if ((BOOL)wparam && m_visible)
		{
			m_acxWindow.SetWindowPos(HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
			::SetWindowPos(m_hostWindow->getHwnd(), m_acxWindow.m_hWnd, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
		}
		else
		{
			m_acxWindow.SetWindowPos(0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_HIDEWINDOW);
		}
	}

	return 0;
}

bool CWebBrowserControl::_initWebBrowserActiveX()
{
	if (m_acxWindow.IsWindow())
	{
		LPOLESTR lpszName = NULL;
		CComPtr<IUnknown> spUnk;

		ATLVERIFY(SUCCEEDED(StringFromCLSID(CLSID_WebBrowser, &lpszName)));
		ATLVERIFY(SUCCEEDED(m_acxWindow.CreateControl(lpszName, 0, &spUnk)));

		CoTaskMemFree(lpszName);
				

		ATLVERIFY(SUCCEEDED(m_acxWindow.QueryControl(&m_spWebBrowser)));
		if (m_spWebBrowser)
		{
			ATLVERIFY(SUCCEEDED(CComObject<CWebBrowserEvents>::CreateInstance(&m_pDWebBrowserEventsObj)));
			if (m_pDWebBrowserEventsObj)
			{
				m_pDWebBrowserEventsObj->setOwner(this);
				m_pDWebBrowserEventsObj->AddRef();

				ATLVERIFY(SUCCEEDED(m_pDWebBrowserEventsObj->DispEventAdvise(m_spWebBrowser)));
			}			

			if (!m_debug)
			{
				CComObject<COleClientSiteImpl>* pSite = NULL;
				ATLVERIFY(SUCCEEDED(CComObject<COleClientSiteImpl>::CreateInstance(&pSite)));
				if (pSite)
				{
					pSite->AddRef();

					CComPtr<IOleObject> spOleObject = NULL;
					ATLVERIFY(SUCCEEDED(m_spWebBrowser->QueryInterface(IID_IOleObject, (void**)&spOleObject)));
					if (spOleObject)
					{
						CComPtr<IOleClientSite> spOleClientSite = NULL;
						ATLVERIFY(SUCCEEDED(pSite->QueryInterface(IID_IOleClientSite, (void**)&spOleClientSite)));
						if (spOleClientSite)
						{
							ATLVERIFY(SUCCEEDED(spOleObject->SetClientSite(spOleClientSite)));
						}						
					}					
				}				
			}		

			return true;
		}
	}

	return false;
}

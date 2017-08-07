#include "stdafx.h"
#include "Win32ComponentHostWindow.h"
#include "Win32Component.h"

using namespace SDUI;


DYNAMIC_OBJECT_CREATE("Win32ComponentHostWindow", CWin32ComponentWindow, CObjectx)

CWin32ComponentWindow::CWin32ComponentWindow()
{
}


CWin32ComponentWindow::~CWin32ComponentWindow()
{
}

HWND CWin32ComponentWindow::getHwnd()
{
	return m_hWnd;
}

HWND CWin32ComponentWindow::create(HWND hwndParent)
{
	if (m_hWnd && IsWindow())
	{
		return m_hWnd;
	}
		
	RECT rc = { -1, -1, 0, 0 };
	Create(GetDesktopWindow(), rc, NULL, WS_POPUP, WS_EX_TOOLWINDOW);

	return CHostWindow::create(hwndParent);
}

bool CWin32ComponentWindow::createFromXml(CXmlAttribute* attr)
{
	CHostWindow::createFromXml(attr);

	return true;
}

int CWin32ComponentWindow::show(int cmd, bool top)
{
	return -1;
}

void CWin32ComponentWindow::hide(int retcode)
{
}

bool CWin32ComponentWindow::addWin32Component(CWin32Component* component)
{
	if (component)
	{		
		component->m_owner = this;
		m_components.push_back(component);		

		return true;
	}

	return false;
}

CWin32Component* CWin32ComponentWindow::getWin32Component(const char* componentid)
{
	std::vector<CWin32Component*>::iterator itr = m_components.begin();
	while (itr != m_components.end())
	{
		CWin32Component* p = *itr;
		if (p && p->getId().compare(componentid) == 0)
		{
			return p;
		}		

		++itr;
	}

	return nullptr;
}

BOOL CWin32ComponentWindow::ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
{
	BOOL bHandled = FALSE;
	lResult = onWin32ComponentMessage(uMsg, wParam, lParam, bHandled);
	if (bHandled)
	{
		return TRUE;
	}
		
	return FALSE;
}

LRESULT CWin32ComponentWindow::onWin32ComponentMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int ret = 0;
	std::vector<CWin32Component*>::iterator itr = m_components.begin();
	while (itr != m_components.end())
	{
		bool handled = false;
		ret = (*itr)->onMessage(uMsg, wParam, lParam, handled);
		if (handled)
		{
			bHandled = TRUE;
			return ret;
		}
		++itr;
	}

	return 0;
}
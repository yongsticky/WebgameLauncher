#include "stdafx.h"
#include "Win32TrayIcon.h"
#include "Application.h"
#include "XmlAttribute.h"
#include "MessageDef.h"
#include "Eventx.h"
#include "Win32ComponentHostWindow.h"
#include "LayoutLoader.h"

#include <shellapi.h>

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("Win32TrayIcon", CWin32TrayIcon, CObjectx)

CWin32TrayIcon::CWin32TrayIcon() : m_showed(false)
{
}


CWin32TrayIcon::~CWin32TrayIcon()
{
}

bool CWin32TrayIcon::createFromXml(CXmlAttribute* attr)
{
	CWin32Component::createFromXml(attr);

	std::string icon;
	if (attr->getAttribute("icon", icon))
	{	
		std::string filePath = Application::getInstance()->getLayoutLoader()->getXmlFile();

		char iconPath[MAX_PATH];
		::PathCombineA(iconPath, filePath.c_str(), "..");
		::PathAppendA(iconPath, icon.c_str());

		USES_CONVERSION;
		HICON hIcon = (HICON)LoadImage(Application::getInstance()->getAppHInstance(), 
			A2CT(iconPath), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
		if (hIcon)
		{
			setHIcon(hIcon);
		}		
	}

	std::string tip;
	if (attr->getAttribute("tip", tip))
	{
		if (m_tip.size() < 128)
		{
			setTip(tip);
		}			
	}

	return true;
}

int CWin32TrayIcon::onMessage(unsigned int message, unsigned int wparam, int lparam, bool & handled)
{
	int ret = CWin32Component::onMessage(message, wparam, lparam, handled);

	if (message == WindowCreated)
	{
		if (m_visible)
		{
			show();
		}
	}
	else if (message == WM_WIN32_SYSTRAYICON)
	{
		CEventx* pEvent = nullptr;

		if (lparam == WM_LBUTTONDBLCLK)
		{
			pEvent = new CEventx(EV_TRAYICON_LDBCLICK, this, 0);
		}
		else if (lparam == WM_RBUTTONUP)
		{
			pEvent = new CEventx(EV_TRAYICON_RCLICK, this, 0);
		}

		if (pEvent)
		{
			dispatchEvent(pEvent);
			delete pEvent;
		}
		
	}

	return ret;
}

void CWin32TrayIcon::show()
{	
	CWin32Component::show();

	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_owner->getHwnd();
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP;
	nid.uCallbackMessage = WM_WIN32_SYSTRAYICON;	
	nid.hIcon = m_hicon;
	USES_CONVERSION;
	wcscpy(nid.szTip, A2CW(m_tip.c_str()));

	m_showed = Shell_NotifyIcon(NIM_ADD, &nid) ? true:false;
}

void CWin32TrayIcon::hide()
{
	CWin32Component::hide();

	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_owner->getHwnd();
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP;
	nid.uCallbackMessage = WM_WIN32_SYSTRAYICON;
	nid.hIcon = m_hicon;

	m_showed = !Shell_NotifyIcon(NIM_DELETE, &nid);	
}

void CWin32TrayIcon::toggle(int cmd, int retcode)
{
	if (m_showed)
	{
		hide();
	}
	else
	{
		show();
	}
}

void CWin32TrayIcon::setHIcon(HICON hicon)
{
	m_hicon = hicon;
}

void CWin32TrayIcon::setTip(const std::string& tip)
{
	m_tip = tip;
}

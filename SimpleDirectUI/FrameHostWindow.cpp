#include "stdafx.h"
#include "FrameHostWindow.h"
#include "Application.h"
#include "LayoutLoader.h"
#include "XmlAttribute.h"
#include "Win32Component.h"
#include "Eventx.h"
#include "Control.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("FrameHostWindow", CFrameHostWindow, CObjectx)

CFrameHostWindow::CFrameHostWindow() : 	
	m_icon(0),
	m_layered(false), 
	m_toolwindow(false),
	m_maximizebox(false),
	m_minimizebox(false),
	m_frameWindow(NULL),
	m_showdefault(SW_SHOW)
{
}


CFrameHostWindow::~CFrameHostWindow()
{
}

bool CFrameHostWindow::createFromXml(CXmlAttribute* attr)
{
	CHostWindow::createFromXml(attr);

	std::string title;
	if (attr->getAttribute("title", title))
	{
		m_title = title;
	}

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
			setIcon(hIcon);
		}
	}

	std::string layered;
	if (attr->getAttribute("layered", layered))
	{
		setLayered(CXmlAttribute::_stringToBoolean(layered));
	}

	std::string toolwindow;
	if (attr->getAttribute("toolwindow", toolwindow))
	{
		setToolwindow(CXmlAttribute::_stringToBoolean(toolwindow));
	}

	std::string maximizebox;
	if (attr->getAttribute("maximizebox", maximizebox))
	{
		setMaximizebox(CXmlAttribute::_stringToBoolean(maximizebox));
	}

	std::string minimizebox;
	if (attr->getAttribute("minimizebox", minimizebox))
	{
		setMinimizebox(CXmlAttribute::_stringToBoolean(minimizebox));
	}

	std::string showdefault;
	if (attr->getAttribute("showdefault", showdefault))
	{
		setShowdefault(CXmlAttribute::_stringToInt(showdefault));
	}

	return true;
}

HWND CFrameHostWindow::getHwnd()
{	
	if (m_frameWindow && m_frameWindow->IsWindow())
	{
		return m_frameWindow->m_hWnd;
	}

	return NULL;	
}

HWND CFrameHostWindow::create(HWND hwndParent)
{
	HWND ret = getHwnd();
	if (!ret)
	{
		RECT rc{ m_x, m_y, m_x + m_cx, m_y + m_cy };

		DWORD dwStyle = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
		if (m_maximizebox)
		{
			dwStyle |= WS_MAXIMIZEBOX;
		}
		if (m_minimizebox)
		{
			dwStyle |= WS_MINIMIZEBOX;
		}

		m_frameWindow = new _FrameWindow(*this);

		USES_CONVERSION;
		m_frameWindow->Create(hwndParent, rc,
			m_title.empty() ? NULL : A2CT(m_title.c_str()),
			dwStyle, m_toolwindow ? WS_EX_TOOLWINDOW : 0);

		if (m_icon)
		{
			::SendMessage(m_frameWindow->m_hWnd, WM_SETICON, ICON_SMALL, (WPARAM)m_icon);
			::SendMessage(m_frameWindow->m_hWnd, WM_SETICON, ICON_BIG, (WPARAM)m_icon);
		}
	}

	return CHostWindow::create(hwndParent);
}

int CFrameHostWindow::show(int cmd, bool forcetop)
{	
	if (m_frameWindow && m_frameWindow->IsWindow())
	{
		if (cmd == 0)
		{
			cmd = m_showdefault;
		}
		else if (cmd == -1)
		{
			cmd = SW_SHOW;
		}

		BOOL ret = m_frameWindow->ShowWindow(cmd);
		if (forcetop)
		{
			m_frameWindow->bringWindowToTop();
		}

		return ret ? 1:0;
	}

	return -1;
}

void CFrameHostWindow::hide(int retcode)
{
	if (m_frameWindow && m_frameWindow->IsWindow())
	{
		m_frameWindow->ShowWindow(SW_HIDE);
	}	
}

void CFrameHostWindow::setTitle(const std::string& title)
{
	m_title = title;
}

void CFrameHostWindow::setIcon(HICON icon)
{
	m_icon = icon;
}

void CFrameHostWindow::setLayered(bool layered)
{
	m_layered = layered;
}

void CFrameHostWindow::setToolwindow(bool toolwindow)
{
	m_toolwindow = toolwindow;
}

void CFrameHostWindow::setMaximizebox(bool maximizebox)
{
	m_maximizebox = maximizebox;
}

void CFrameHostWindow::setMinimizebox(bool minimizebox)
{
	m_minimizebox = minimizebox;
}

void CFrameHostWindow::setShowdefault(int showdefault)
{
	m_showdefault = showdefault;
}
#include "stdafx.h"
#include "HostWindow.h"
#include "XmlAttribute.h"
#include "Control.h"

using namespace SDUI;

CHostWindow::CHostWindow() :
	m_x(0),m_y(0),
	m_cx(0),m_cy(0),
	m_mincx(0),m_mincy(0),
	m_center(true),
	m_visible(true),	
	m_active(false),
	m_root(nullptr),
	m_lastHover(nullptr)
{
}


CHostWindow::~CHostWindow()
{
}

bool CHostWindow::createFromXml(CXmlAttribute* attr)
{
	std::string id;
	if (attr->getAttribute("id", id))
	{
		setId(id);
	}

	std::string pos;
	if (attr->getAttribute("pos", pos))
	{
		long x, y;
		CXmlAttribute::_stringToXY(pos, x, y);
		setPos((int)x, (int)y);
	}

	std::string size;
	if (attr->getAttribute("size", size))
	{
		long cx, cy;
		CXmlAttribute::_stringToXY(size, cx, cy);
		setSize((int)cx, (int)cy);
	}

	std::string minsize;
	if (attr->getAttribute("minsize", minsize))
	{
		long cx, cy;
		CXmlAttribute::_stringToXY(minsize, cx, cy);
		setMinSize((int)cx, (int)cy);
	}

	std::string center;
	if (attr->getAttribute("center", center))
	{
		setCenter(CXmlAttribute::_stringToBoolean(center));
	}

	std::string visible;
	if (attr->getAttribute("visible", visible))
	{
		setVisible(CXmlAttribute::_stringToBoolean(visible));
	}

	std::string active;
	if (attr->getAttribute("active", active))
	{
		setActive(CXmlAttribute::_stringToBoolean(active));
	}

	return true;
}


HWND SDUI::CHostWindow::create(HWND hwndParent)
{
	HWND hwnd = getHwnd();
	return hwnd;
}

void CHostWindow::toggle(int cmd, int retcode)
{
	HWND hwnd = getHwnd();

	if (hwnd)
	{
		if (!IsWindowVisible(hwnd))
		{
			show(cmd, false);
		}
		else if (IsIconic(hwnd))
		{
			show(SW_RESTORE, false);
		}
		else
		{
			hide(retcode);
		}

	}
	else
	{
		ATLASSERT(FALSE);
	}	
}

bool CHostWindow::invalidate()
{	
	return InvalidateRect(getHwnd(), NULL, FALSE) ? true:false;	
}

int CHostWindow::getClassType()
{
	return T_Windowx;
}

bool CHostWindow::addRootControl(CControl* root)
{
	m_root = root;

	if (m_root)
	{
		m_root->_setHostWindow(this);
	}

	return true;
}

CControl* CHostWindow::getRootControl()
{
	return m_root;
}

CControl* CHostWindow::findControl(const char* path)
{
	if (!path)
	{
		return nullptr;
	}


	char buf[128];
	strcpy(buf, path);

	const char* p = strtok(buf, ":");

	CControl* cc = nullptr;

	while (p)
	{
		if (!cc)
		{
			cc = getRootControl();
			if (cc && cc->getId().compare(p) != 0)
			{
				return nullptr;
			}
		}
		else
		{
			cc = cc->findChild(p);
			if (!cc)
			{
				return nullptr;
			}
		}

		p = strtok(nullptr, ":");
	}

	return cc;
}

bool CHostWindow::addWin32Component(CWin32Component* component)
{
	return false;
}

CWin32Component* CHostWindow::getWin32Component(const char* componentid)
{
	return nullptr;
}

CControl* SDUI::CHostWindow::getLastHoverControl()
{
	return m_lastHover;
}

void SDUI::CHostWindow::setLastHoverControl(CControl* lastHover)
{
	m_lastHover = lastHover;
}

void CHostWindow::setId(const std::string& id)
{
	m_id = id;
}

std::string CHostWindow::getId()
{
	return m_id;
}

void CHostWindow::setPos(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CHostWindow::setSize(int cx, int cy)
{
	m_cx = cx;
	m_cy = cy;
}

void SDUI::CHostWindow::setMinSize(int cx, int cy)
{
	m_mincx = cx;
	m_mincy = cy;
}

void SDUI::CHostWindow::setCenter(bool center)
{
	m_center = center;
}

void CHostWindow::setVisible(bool visible)
{
	m_visible = visible;
}

void SDUI::CHostWindow::setActive(bool active)
{
	m_active = active;
}

bool SDUI::CHostWindow::getActive()
{
	return m_active;
}

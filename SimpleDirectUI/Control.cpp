#include "stdafx.h"
#include "HostWindow.h"
#include "Control.h"
#include "EventxHandler.h"
#include "MessageDef.h"
#include "XmlAttribute.h"


using namespace SDUI;

CControl::CControl() :
	m_x(0), m_y(0),
	m_cx(0), m_cy(0),
	m_hostWindow(NULL),
	m_hitable(true),
	m_visible(true),
	m_htval(-1),
	//m_show(false),
	m_parent(NULL)
{
}


CControl::~CControl()
{
	
}

bool CControl::createFromXml(CXmlAttribute* attr)
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

	std::string visible;
	if (attr->getAttribute("visible", visible))
	{
		setVisible(CXmlAttribute::_stringToBoolean(visible));
	}

	std::string hitable;
	if (attr->getAttribute("hitalbe", hitable))
	{
		setHitable(CXmlAttribute::_stringToBoolean(hitable));
	}

	std::string hitval;
	if (attr->getAttribute("hitval", hitval))
	{
		setHitvalue(CXmlAttribute::_stringToInt(hitval));
	}

	return true;	
}

int CControl::getClassType()
{
	return T_Control;
}

unsigned int CControl::addChild(CControl* control)
{
	if (control && !control->m_parent)
	{
		control->m_parent = this;
		control->m_hostWindow = m_hostWindow;

		m_children.push_back(control);		

		return m_children.size();
	}

	return 0;
}

CControl* CControl::findChild(const char* id)
{
	if (!id)
	{
		return nullptr;
	}

	std::vector<CControl*>::iterator itr = m_children.begin();
	while (itr != m_children.end())
	{
		if ((*itr)->getId().compare(id) == 0)
		{
			return (*itr);
		}

		++itr;
	}

	return nullptr;
}

std::string CControl::fromData()
{
	return std::string();
}

void CControl::updateTo(const std::string& data)
{
}

bool CControl::hitMe(int x, int y)
{
	if (!m_hitable || !m_visible)
	{
		return false;
	}
	
	if ((x >= m_xx) && (x < (m_xx + m_cxcx)) &&
		(y >= m_yy) && (y < (m_yy + m_cycy)))
	{		
		return true;
	}

	return false;
}

bool CControl::redraw()
{
	return m_hostWindow->invalidate();
}

void CControl::layout(int x, int y, int cx, int cy)
{
	m_cxcx = m_cx > 0 ? m_cx : cx + m_cx;
	m_xx = m_x < 0 ? x + cx + m_x : x + m_x;

	m_cycy = m_cy > 0 ? m_cy : cy + m_cy;
	m_yy = m_y < 0 ? y + cy + m_y : y + m_y;
}

void SDUI::CControl::show(bool show)
{
	//m_show = show;
	m_visible = show;
}

CControl* CControl::getParent()
{
	return m_parent;
}

CControl* CControl::getRoot()
{
	if (!m_parent)
	{
		return this;
	}

	CControl* p = m_parent;
	while (p)
	{
		if (p->m_parent)
		{
			p = p->m_parent;
		}
		else
		{
			break;
		}
	}

	return p;	
}

CHostWindow* CControl::getHostWindow()
{
	return m_hostWindow;
}

void CControl::_setHostWindow(CHostWindow* hostWindow)
{
	m_hostWindow = hostWindow;

	std::vector<CControl*>::iterator itr = m_children.begin();
	while (itr != m_children.end())
	{
		(*itr)->_setHostWindow(hostWindow);

		++itr;
	}
}

int CControl::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	if (message == WindowHitTest)
	{
		handled = true;
		return (m_htval==-1 ? HTCLIENT:m_htval);
	}
/*	else if (message == WindowPaint)
	{		
		if (isDrawable())
		{
			return onDraw((HDC)wparam);
		}	
	}*/
	else if (message == WindowSize)
	{
		int x = 0, y = 0, cx = 0, cy = 0;

		if (m_parent)
		{
			x = m_parent->m_xx;
			y = m_parent->m_yy;
			cx = m_parent->m_cxcx;
			cy = m_parent->m_cycy;
		}
		else
		{
			cx = GET_X_LPARAM(lparam);
			cy = GET_Y_LPARAM(lparam);
		}		

		layout(x, y, cx, cy);
	}
	else if (message == WindowMouseHover)
	{
		CControl* lastHover = getHostWindow()->getLastHoverControl();

		//ATLTRACE("CControl::onMessage lastHover:%s this:%s.\n", lastHover ? lastHover->getId().c_str():"nullptr", m_id.c_str());

		if (lastHover && !lastHover->equal(this))
		{
			bool b = false;
			lastHover->onMessage(WindowMouseLeave, 0, 0, b);

			//ATLTRACE("CControl::onMessage set lastHover %s WindowMouseLeave.\n", lastHover->getId().c_str());
		}

		getHostWindow()->setLastHoverControl(this);
		//ATLTRACE("CControl::onMessage setLastHoverControl %s.\n", m_id.c_str());
	}
	else if (message == WindowMouseLeave)
	{
		//ATLTRACE("CControl::onMessage setLastHoverControl nullptr.\n");
		getHostWindow()->setLastHoverControl(nullptr);
	}
	else
	{
		__noop;
	}

	return 0;
}

bool CControl::isDrawable()
{
	// 不展示的
	if (!m_visible)
	{
		return false;
	}
	
	// 祖先节点不展示的
	CControl* p = m_parent;
	while (p)
	{
		if (!p->m_visible)
		{
			return false;
		}

		p = p->m_parent;
	}

	// 100%被遮盖的


	return true;
}

int CControl::_firePreorderMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{	
	int retval = 0;

	// 自己先处理	
	if (_canProcessThisMessage(message, wparam, lparam))
	{
		retval = onMessage(message, wparam, lparam, handled);
		if (handled)
		{
			return retval;
		}
	}	

	// 子节点处理
	std::vector<CControl*>::iterator itr = m_children.begin();
	while (itr != m_children.end())
	{
		retval = (*itr)->_firePreorderMessage(message, wparam, lparam, handled);
		if (handled)
		{
			return retval;
		}

		++itr;
	}

	return 0;
}

int CControl::_firePosteriorMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{	
	int retval = 0;

	// 子节点处理
	std::vector<CControl*>::reverse_iterator itr = m_children.rbegin();
	while (itr != m_children.rend())
	{
		retval = (*itr)->_firePosteriorMessage(message, wparam, lparam, handled);
		if (handled)
		{
			return retval;
		}

		++itr;
	}
		
	// 消息是你的吗？
	if (_canProcessThisMessage(message, wparam, lparam))
	{
		// 自己处理
		retval = onMessage(message, wparam, lparam, handled);
		if (handled)
		{			
			return retval;
		}
	}

	return 0;
}

bool CControl::_canProcessThisMessage(unsigned int message, int wparam, int lparam)
{
	int x = 0, y = 0;

	switch (message)
	{
	case WM_NCHITTEST:
	{
		POINT pt{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };		
		ScreenToClient(m_hostWindow->getHwnd(), &pt);
		x = pt.x;
		y = pt.y;		
	}
	break;
	case WM_LBUTTONUP:
	case WM_MOUSEHOVER:
	{
		x = GET_X_LPARAM(lparam);
		y = GET_Y_LPARAM(lparam);		
	}
	break;
	case WM_MOUSELEAVE:
	{
		CControl* lastHover = getHostWindow()->getLastHoverControl();
		if (lastHover)
		{
			return lastHover->equal(this);
		}
		return false;
	}
	break;
	case (WM_USER+WM_PAINT):
	{
		return isDrawable();
	}	
	break;
	default:
		return true;
	}

	return hitMe(x, y);
}

void CControl::setId(const std::string& id)
{
	m_id = id;
}

std::string CControl::getId()
{
	return m_id;
}

void CControl::setPos(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CControl::setSize(int cx, int cy)
{
	m_cx = cx;
	m_cy = cy;
}

void CControl::setVisible(bool visible)
{
	m_visible = visible;
}

void CControl::setHitable(bool hitable)
{
	m_hitable = hitable;
}

void CControl::setHitvalue(int hitval)
{
	m_htval = hitval;
}
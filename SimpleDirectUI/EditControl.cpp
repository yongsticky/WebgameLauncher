#include "stdafx.h"
#include "EditControl.h"
#include "Eventx.h"
#include "HostWindow.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("Edit", CEditControl, CObjectx)

CEditControl::CEditControl()
{
}


CEditControl::~CEditControl()
{
}

bool CEditControl::createFromXml(CXmlAttribute* attr)
{
	CControl::createFromXml(attr);

	return true;
}

unsigned int CEditControl::addChild(CControl* control)
{
	return 0;
}

int CEditControl::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	LRESULT lr = CControl::onMessage(message, wparam, lparam, handled);

	if (message == WindowCreated || message == DialogInit)
	{
		RECT rc{ m_x, m_y, m_x + m_cx, m_y + m_cy };
		
		HWND hwnd = CWindow().Create(_T("EDIT"), m_hostWindow->getHwnd(), rc, 0, ES_LEFT | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE, WS_EX_TOOLWINDOW);		
		m_edit.Attach(hwnd);		
	}
	else if (message == WindowDestroyed)
	{
		m_edit.Detach();
	}
	
	return 0;
}

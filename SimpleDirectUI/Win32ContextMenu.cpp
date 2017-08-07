#include "stdafx.h"
#include "Win32ContextMenu.h"
#include "XmlAttribute.h"
#include "MessageDef.h"
#include "Win32ComponentHostWindow.h"
#include "Win32MenuItem.h"
#include "Eventx.h"

using namespace SDUI;


DYNAMIC_OBJECT_CREATE("Win32ContextMenu", CWin32ContextMenu, CObjectx)

CWin32ContextMenu::CWin32ContextMenu() : m_hMenu(nullptr)
{
}


CWin32ContextMenu::~CWin32ContextMenu()
{
}

bool CWin32ContextMenu::createFromXml(CXmlAttribute* attr)
{
	CWin32Component::createFromXml(attr);

	std::string group;
	if (attr->getAttribute("group", group))
	{
		setGroup(CXmlAttribute::_stringToInt(group));
	}

	return true;
}

int CWin32ContextMenu::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	if (message == WindowCreated)
	{
		m_hMenu = _create();
	}
	else if (message == WindowCommand)
	{
		int code = HIWORD(wparam);
		if (code == 0)
		{
			int id = LOWORD(wparam);
			if (id / 100 == m_group)
			{				
				return CWin32Component::onMessage(message, id%100, lparam, handled);
			}
		}
	}

	return 0;
}

void CWin32ContextMenu::show()
{	
	if (m_hMenu)
	{
		POINT pt = { m_x, m_y };
		GetCursorPos(&pt);

		SetForegroundWindow(m_owner->getHwnd());
		TrackPopupMenu(m_hMenu, TPM_LEFTALIGN, pt.x+1, pt.y-1, 0, m_owner->getHwnd(), NULL);	
	}
}

void CWin32ContextMenu::hide()
{	
}

void CWin32ContextMenu::setGroup(int group)
{
	m_group = group;
}

HMENU CWin32ContextMenu::_create()
{
	HMENU hMenu = CreatePopupMenu();

	int pos = 0;
	std::vector<CWin32Component*>::iterator itr = m_children.begin();
		
	while (itr != m_children.end())
	{
		CWin32MenuItem* item = dynamic_cast<CWin32MenuItem*>(*itr);
		if (item)
		{
			USES_CONVERSION;
			unsigned int flag = item->getSeparator() ? MF_SEPARATOR: MFT_STRING;

			AppendMenu(hMenu, flag, m_group*100+item->getIndex(), A2T(item->getText().c_str()));
		}

		++itr;
	}	

	return hMenu;
}

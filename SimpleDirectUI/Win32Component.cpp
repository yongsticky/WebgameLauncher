#include "stdafx.h"
#include "Win32Component.h"
#include "XmlAttribute.h"
#include "MessageDef.h"
#include "Win32ComponentHostWindow.h"

using namespace SDUI;

CWin32Component::CWin32Component() : m_visible(false)
{
}


CWin32Component::~CWin32Component()
{
}

int CWin32Component::getClassType()
{
	return T_Win32Component;
}

bool CWin32Component::createFromXml(CXmlAttribute* attr)
{
	std::string id;
	if (attr->getAttribute("id", id))
	{
		setId(id);
	}

	std::string visible;
	if (attr->getAttribute("visible", visible))
	{
		setVisible(CXmlAttribute::_stringToBoolean(visible));
	}

	return true;
}

int CWin32Component::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	std::vector<CWin32Component*>::iterator itr = m_children.begin();
	while (itr != m_children.end())
	{
		bool handled = false;
		int ret = (*itr)->onMessage(message, wparam, lparam, handled);
		if (handled)
		{
			return ret;
		}

		++itr;
	}

	return 0;
}

int CWin32Component::addChild(CWin32Component* child)
{
	if (child)
	{
		m_children.push_back(child);

		return m_children.size();
	}

	return 0;
	
}

void CWin32Component::show()
{
	if (m_owner)
	{
		m_owner->create();		
	}	
}

void CWin32Component::hide()
{	
}

void CWin32Component::toggle(int cmd, int retcode)
{
}

void CWin32Component::setId(const std::string& id)
{
	m_id = id;
}

std::string CWin32Component::getId()
{
	return m_id;
}

void CWin32Component::setVisible(bool visible)
{
	m_visible = visible;
}

void CWin32Component::setPos(int x, int y)
{
	m_x = x;
	m_y = y;
}

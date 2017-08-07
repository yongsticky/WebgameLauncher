#include "stdafx.h"
#include "Win32MenuItem.h"
#include "XmlAttribute.h"
#include "MessageDef.h"
#include "Eventx.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("Win32MenuItem", CWin32MenuItem, CObjectx)

CWin32MenuItem::CWin32MenuItem() : m_index(-1)
{
}


CWin32MenuItem::~CWin32MenuItem()
{
}

bool CWin32MenuItem::createFromXml(CXmlAttribute* attr)
{
	CWin32Component::createFromXml(attr);
	
	std::string separator;
	if (attr->getAttribute("separator", separator))
	{
		setSeparator(CXmlAttribute::_stringToBoolean(separator));
	}

	std::string index;
	if (attr->getAttribute("index", index))
	{
		setIndex(CXmlAttribute::_stringToInt(index));
	}

	std::string text;
	if (attr->getAttribute("text", text))
	{
		setText(text);
	}

	return true;
}

int CWin32MenuItem::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	if (message == WindowCommand)
	{
		if (wparam == m_index)
		{
			CEventx* event = new CEventx(EV_MENU_SELECT, this, 0);
			dispatchEvent(event);
			delete event;
		}
	}

	return 0;
}

void CWin32MenuItem::setSeparator(bool separator)
{
	m_separator = separator;
}

bool CWin32MenuItem::getSeparator()
{
	return m_separator;
}

void CWin32MenuItem::setIndex(int index)
{
	m_index = index;
}

int CWin32MenuItem::getIndex()
{
	return m_index;
}

void CWin32MenuItem::setText(const std::string& text)
{
	m_text = text;
}

std::string CWin32MenuItem::getText()
{
	return m_text;
}

#include "stdafx.h"
#include "HotkeyConfigReader.h"
#include "Eventx.h"
#include "AppConfiger.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("HotkeyConfigReader", CHotkeyConfigReader, CObjectx)

CHotkeyConfigReader::CHotkeyConfigReader()
{
}


CHotkeyConfigReader::~CHotkeyConfigReader()
{
}

bool CHotkeyConfigReader::createFromXml(SDUI::CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string group;
	if (attr->getAttribute("group", group))
	{
		setGroup(group);
	}

	std::string key;
	if (attr->getAttribute("key", key))
	{
		setKey(key);
	}

	std::string to;
	if (attr->getAttribute("to", to))
	{
		setTo(to);
	}

	return true;
}

bool CHotkeyConfigReader::onAction(SDUI::CEventx* event)
{
	CControl* pcon = event->getOwnerHostWindow()->findControl(m_to.c_str());
	if (pcon)
	{
		std::string value = CAppConfiger::getInstance()->read(m_group, m_key, std::string("ctrl_k"));
		pcon->updateTo(value);		
	}

	return true;
}

void CHotkeyConfigReader::setGroup(const std::string& group)
{
	m_group = group;
}

void CHotkeyConfigReader::setKey(const std::string& key)
{
	m_key = key;
}

void CHotkeyConfigReader::setTo(const std::string& to)
{
	m_to = to;
}

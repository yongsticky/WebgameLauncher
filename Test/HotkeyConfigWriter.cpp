#include "stdafx.h"
#include "HotkeyConfigWriter.h"
#include "Eventx.h"
#include "AppConfiger.h"


using namespace SDUI;

DYNAMIC_OBJECT_CREATE("HotkeyConfigWriter", CHotkeyConfigWriter, CObjectx)

CHotkeyConfigWriter::CHotkeyConfigWriter()
{
}


CHotkeyConfigWriter::~CHotkeyConfigWriter()
{
}

bool CHotkeyConfigWriter::createFromXml(SDUI::CXmlAttribute* attr)
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

	std::string from;
	if (attr->getAttribute("from", from))
	{
		setFrom(from);
	}
	
	return true;
}

bool CHotkeyConfigWriter::onAction(SDUI::CEventx* event)
{	
	CControl* pcon = event->getOwnerHostWindow()->findControl(m_from.c_str());
	if (pcon)
	{
		std::string value = pcon->fromData();
		CAppConfiger::getInstance()->write(m_group, m_key, value);
	}

	return false;
}

void CHotkeyConfigWriter::setGroup(const std::string& group)
{
	m_group = group;
}

void CHotkeyConfigWriter::setKey(const std::string& key)
{
	m_key = key;
}

void CHotkeyConfigWriter::setFrom(const std::string& from)
{
	m_from = from;
}

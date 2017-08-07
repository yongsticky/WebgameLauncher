#pragma once
#include "Action.h"

class CHotkeyConfigWriter : public SDUI::CAction
{
public:
	CHotkeyConfigWriter();
	virtual ~CHotkeyConfigWriter();

	DYNAMIC_OBJECT_DECLARE(CHotkeyConfigWriter, CObjectx)

	virtual bool createFromXml(SDUI::CXmlAttribute* attr);
	virtual bool onAction(SDUI::CEventx* event);
	
	void setGroup(const std::string& group);
	void setKey(const std::string& key);
	void setFrom(const std::string& from);

protected:
	std::string m_group;
	std::string m_key;
	std::string m_from;
};


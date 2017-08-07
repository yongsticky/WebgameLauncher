#pragma once
#include "Action.h"


class CHotkeyConfigReader : public SDUI::CAction
{
public:
	CHotkeyConfigReader();
	virtual ~CHotkeyConfigReader();

	DYNAMIC_OBJECT_DECLARE(CHotkeyConfigReader, CObjectx)

	virtual bool createFromXml(SDUI::CXmlAttribute* attr);
	virtual bool onAction(SDUI::CEventx* event);


	void setGroup(const std::string& group);
	void setKey(const std::string& key);
	void setTo(const std::string& to);

protected:
	std::string m_group;
	std::string m_key;
	std::string m_to;
};


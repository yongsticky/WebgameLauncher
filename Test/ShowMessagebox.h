#pragma once
#include "Action.h"

class CShowMessagebox : public SDUI::CAction
{
public:
	CShowMessagebox();
	virtual ~CShowMessagebox();

	DYNAMIC_OBJECT_DECLARE(CShowMessagebox, CObjectx)

	virtual bool createFromXml(SDUI::CXmlAttribute* attr);
	virtual bool onAction(SDUI::CEventx* event);

	void setWindowId(const std::string& windowid);
	void setTitle(const std::string& title);
	void setMessage(const std::string& message);
	void setYes(const std::string& yes);
	void setNo(const std::string& no);
	void setContinue(int continue_);

protected:
	std::string m_windowid;
	std::string m_title;
	std::string m_message;
	std::string m_yes;
	std::string m_no;
	int m_continue;
};
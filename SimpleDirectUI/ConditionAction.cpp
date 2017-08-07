#include "stdafx.h"
#include "ConditionAction.h"
#include "XmlAttribute.h"
#include "Eventx.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("Condition", CConditionAction, CObjectx)

CConditionAction::CConditionAction()
{
}


CConditionAction::~CConditionAction()
{
}

bool CConditionAction::createFromXml(CXmlAttribute * attr)
{
	CAction::createFromXml(attr);

	std::string str;
	if (attr->getAttribute("str", str))
	{
		setString(str);
	}

	std::string condition;
	if (attr->getAttribute("condition", condition))
	{
		setCondition(condition);
	}

	return true;
}

bool CConditionAction::onAction(CEventx* event)
{
	std::string val = (char*)event->getData();

	if (m_condition.compare("contain") == 0)
	{
		if (val.find(m_str) != -1)		// matched!
		{
			return false;
		}
	}
	else if (m_condition.compare("equal") == 0)
	{
		if (val.compare(m_str) == 0)	// matched!
		{			
			return false;
		}
	}
	
	return true;
}

void CConditionAction::setString(const std::string& str)
{	
	m_str = str;
}

void CConditionAction::setCondition(const std::string& condition)
{
	m_condition = condition;
}

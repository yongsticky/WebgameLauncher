#include "stdafx.h"
#include "EventxHandler.h"
#include "XmlAttribute.h"
#include "Eventx.h"
#include "Action.h"
#include <string>

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("EventHandler", CEventxHandler, CObjectx)

CEventxHandler::CEventxHandler() : m_interest(0)
{
}


CEventxHandler::~CEventxHandler()
{
}

bool CEventxHandler::createFromXml(CXmlAttribute* attr)
{
	std::string interest;
	if (attr->getAttribute("interest", interest))
	{
		setInterest(CXmlAttribute::_stringToInt(interest));
	}

	

	return true;
}

int CEventxHandler::getClassType()
{
	return T_EventxHandler;
}

unsigned int CEventxHandler::addAction(CAction* action)
{
	if (action)
	{
		m_actions.push_back(action);

		return m_actions.size();
	}

	return 0;
}

void CEventxHandler::runAction(CEventx* event)
{
	std::vector<CAction*>::iterator itr = m_actions.begin();
	while (itr != m_actions.end())
	{
		CAction* pAction = *itr;
		if (pAction && pAction->onAction(event))
		{			
			break;
		}

		++itr;
	}
}

void CEventxHandler::setInterest(int interst)
{
	m_interest = interst;
}

int CEventxHandler::getInterest()
{
	return m_interest;
}

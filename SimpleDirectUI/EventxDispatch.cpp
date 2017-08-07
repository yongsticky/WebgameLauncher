#include "stdafx.h"
#include "EventxDispatch.h"
#include "Eventx.h"
#include "EventxHandler.h"

using namespace SDUI;

CEventxDispatch::CEventxDispatch()
{
}


CEventxDispatch::~CEventxDispatch()
{
}

unsigned int CEventxDispatch::addEventHandlerList(CEventxHandler* handlerList)
{	
	if (handlerList)
	{
		m_handlerList.push_back(handlerList);

		return m_handlerList.size();
	}
	
	return 0;
}

bool CEventxDispatch::dispatchEvent(CEventx* event)
{
	int eventId = event->getId();

	std::vector<CEventxHandler*>::iterator itr = m_handlerList.begin();	
	while (itr != m_handlerList.end())
	{
		CEventxHandler* pHandler = *itr;
		if (pHandler && eventId == pHandler->getInterest())
		{
			pHandler->runAction(event);
			if (!event->getPropagation())
			{
				break;
			}
		}

		++itr;
	}		

	return true;
}

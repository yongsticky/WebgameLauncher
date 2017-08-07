#include "stdafx.h"
#include "CreateTimerAction.h"
#include "Eventx.h"
#include "XmlAttribute.h"
#include "Application.h"
#include "LayoutLoader.h"
#include "HostWindow.h"
#include "Control.h"


using namespace SDUI;

DYNAMIC_OBJECT_CREATE("CreateTimer", CCreateTimerAction, CObjectx)

CCreateTimerAction::CCreateTimerAction()
{
}


CCreateTimerAction::~CCreateTimerAction()
{
}

bool CCreateTimerAction::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string windowid;
	if (attr->getAttribute("windowid", windowid))
	{
		setWindowId(windowid);
	}

	std::string timerid;
	if (attr->getAttribute("timerid", timerid))
	{
		setTimerId(CXmlAttribute::_stringToInt(timerid));
	}

	std::string elapse;
	if (attr->getAttribute("elapse", elapse))
	{
		setElapse(CXmlAttribute::_stringToInt(elapse));
	}

	/*std::string once;
	if (attr->getAttribute("once", once))
	{
		setOnce(CXmlAttribute::_stringToBoolean(once));
	}*/

	return true;
}

bool CCreateTimerAction::onAction(CEventx* event)
{
	CHostWindow* pwin = nullptr;
	if (m_windowid.empty() || m_windowid.compare("owner") == 0)
	{
		pwin = event->getOwnerHostWindow();
	}
	else
	{
		pwin = (CHostWindow*)Application::getInstance()->getLayoutLoader()->getRoot(m_windowid.c_str());
	}

	::SetTimer(pwin->getHwnd(), m_timerId, 1000*m_elapse, NULL);	

	return true;
}

void SDUI::CCreateTimerAction::setWindowId(const std::string& windowid)
{
	m_windowid = windowid;
}

void CCreateTimerAction::setTimerId(unsigned int timerId)
{
	m_timerId = timerId;
}

void CCreateTimerAction::setElapse(unsigned int elapse)
{
	m_elapse = elapse;
}

/*
void SDUI::CCreateTimerAction::setOnce(bool once)
{
}
*/
#include "stdafx.h"
#include "KillTimerAction.h"
#include "Eventx.h"
#include "XmlAttribute.h"
#include "Application.h"
#include "LayoutLoader.h"
#include "HostWindow.h"
#include "Control.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("KillTimer", CKillTimerAction, CObjectx)

CKillTimerAction::CKillTimerAction()
{
}


CKillTimerAction::~CKillTimerAction()
{
}

bool CKillTimerAction::createFromXml(CXmlAttribute * attr)
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

	return true;
}

bool CKillTimerAction::onAction(CEventx* event)
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

	::KillTimer(pwin->getHwnd(), m_timerid);
	
	return false;
}

void CKillTimerAction::setWindowId(const std::string& windowid)
{
	m_windowid = windowid;
}

void CKillTimerAction::setTimerId(unsigned int timerId)
{
	m_timerid = timerId;
}

#include "stdafx.h"
#include "SendMessageAction.h"
#include "XmlAttribute.h"
#include "HostWindow.h"
#include "Application.h"
#include "LayoutLoader.h"
#include "Eventx.h"

using namespace SDUI;


DYNAMIC_OBJECT_CREATE("SendMessage", CSendMessageAction, CObjectx)

CSendMessageAction::CSendMessageAction() : m_message(0), m_sync(true)
{
}


CSendMessageAction::~CSendMessageAction()
{
}

bool SDUI::CSendMessageAction::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string windowid;
	if (attr->getAttribute("windowid", windowid))
	{
		setWindowId(windowid);
	}
	
	std::string message;
	if (attr->getAttribute("message", message))
	{
		setMessage(CXmlAttribute::_stringToInt(message));
	}

	std::string sync;
	if (attr->getAttribute("sync", sync))
	{
		setSync(CXmlAttribute::_stringToBoolean(sync));
	}

	return true;
}

bool SDUI::CSendMessageAction::onAction(CEventx* event)
{
	CHostWindow* pwin = (CHostWindow*)Application::getInstance()->getLayoutLoader()->getRoot(m_windowid.c_str());
	if (pwin)
	{
		if (m_sync)
		{
			::SendMessage(pwin->getHwnd(), m_message, 0, 0);
		}
		else
		{
			::PostMessage(pwin->getHwnd(), m_message, 0, 0);
		}
	}

	return false;
}

void SDUI::CSendMessageAction::setWindowId(const std::string& windowid)
{
	m_windowid = windowid;
}

void SDUI::CSendMessageAction::setMessage(const int message)
{
	m_message = message;
}

void SDUI::CSendMessageAction::setSync(bool sync)
{
	m_sync = sync;
}

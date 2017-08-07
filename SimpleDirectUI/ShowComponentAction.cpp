#include "stdafx.h"
#include "ShowComponentAction.h"
#include "XmlAttribute.h"
#include "HostWindow.h"
#include "Application.h"
#include "LayoutLoader.h"
#include "Win32Component.h"
#include "Eventx.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("ShowComponent", CShowComponentAction, CObjectx)

CShowComponentAction::CShowComponentAction() : m_destroy(false)
{
}


CShowComponentAction::~CShowComponentAction()
{
}

bool CShowComponentAction::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string windowid;
	if (attr->getAttribute("windowid", windowid))
	{
		setWindowId(windowid);
	}

	std::string componentid;
	if (attr->getAttribute("componentid", componentid))
	{
		setComponentId(componentid);
	}

	std::string show;
	if (attr->getAttribute("show", show))
	{
		setShow(show);
	}

	std::string destroy;
	if (attr->getAttribute("destroy", destroy))
	{
		setDestroy(CXmlAttribute::_stringToBoolean(destroy));
	}

	return true;
}

bool CShowComponentAction::onAction(CEventx* event)
{
	if (m_windowid.empty() || m_componentid.empty())
	{
		return false;
	}

	CHostWindow* pwin = (CHostWindow*)Application::getInstance()->getLayoutLoader()->getRoot(m_windowid.c_str());
	if (pwin)
	{
		CWin32Component* pcom = pwin->getWin32Component(m_componentid.c_str());
		if (pcom)
		{
			if (m_show.compare("show") == 0 || m_show.compare("true") == 0)
			{								
				pcom->show();
			}
			else if (m_show.compare("hide") == 0 || m_show.compare("false") == 0)
			{
				pcom->hide();
			}
			else if (m_show.compare("auto") == 0 || m_show.compare("toggle") == 0)
			{
				pcom->toggle(0, 0);
			}
			else
			{
				ATLASSERT(false);
			}
		}
	}

	return false;
}

void CShowComponentAction::setWindowId(const std::string& windowid)
{
	m_windowid = windowid;
}

void CShowComponentAction::setComponentId(const std::string& componentid)
{
	m_componentid = componentid;
}

void CShowComponentAction::setShow(std::string show)
{
	m_show = show;
}

void SDUI::CShowComponentAction::setDestroy(bool destroy)
{
	m_destroy = destroy;
}

#include "stdafx.h"
#include "ShowControlAction.h"
#include "XmlAttribute.h"
#include "Eventx.h"
#include "Control.h"
#include "HostWindow.h"
#include "Application.h"
#include "LayoutLoader.h"


using namespace SDUI;

DYNAMIC_OBJECT_CREATE("ShowControl", CShowControlAction, CObjectx)

CShowControlAction::CShowControlAction()
{
}


CShowControlAction::~CShowControlAction()
{
}

bool SDUI::CShowControlAction::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string controlid;
	if (attr->getAttribute("controlid", controlid))
	{
		setControlId(controlid);
	}

	std::string windowid;
	if (attr->getAttribute("windowid", windowid))
	{
		setWindowId(windowid);
	}

	std::string show;
	if (attr->getAttribute("show", show))
	{
		setShow(show);
	}

	return true;
}

bool SDUI::CShowControlAction::onAction(CEventx* event)
{	
	CControl* pcon = nullptr;

	if (m_controlid.compare("owner") == 0)
	{
		if (event->getOwnerHostWindow()->getActive())
		{
			pcon = event->getOwnerControl();
		}
	}
	else
	{					
		CHostWindow* pwin = nullptr;
		if (m_windowid.empty() || m_windowid.compare("owner") == 0)
		{
			pwin = event->getOwnerHostWindow();
		}
		else
		{
			pwin = static_cast<CHostWindow*>(Application::getInstance()->getLayoutLoader()->getRoot(m_windowid.c_str()));
		}
		
		if (pwin)
		{
			if (pwin->getActive())
			{
				pcon = pwin->findControl(m_controlid.c_str());
			}				
		}
		else
		{
			ATLASSERT(FALSE);				
		}
	}
	
	if (!pcon)
	{		
		return false;
	}
	
	if (m_show.compare("true") == 0 || m_show.compare("show") == 0)
	{
		pcon->show(true);
		pcon->redraw();
	}
	else if (m_show.compare("false") == 0 || m_show.compare("hide") == 0)
	{
		pcon->show(false);
		pcon->redraw();
	}	

	return false;
}

void SDUI::CShowControlAction::setControlId(const std::string& controlid)
{
	m_controlid = controlid;
}

void SDUI::CShowControlAction::setWindowId(const std::string& windowid)
{
	m_windowid = windowid;
}

void SDUI::CShowControlAction::setShow(const std::string& show)
{
	m_show = show;
}

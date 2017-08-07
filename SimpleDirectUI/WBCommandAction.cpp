#include "stdafx.h"
#include "WBCommandAction.h"
#include "Application.h"
#include "LayoutLoader.h"
#include "Eventx.h"
#include "XmlAttribute.h"
#include "WebBrowserControl.h"
#include "HostWindow.h"


using namespace SDUI;

DYNAMIC_OBJECT_CREATE("WBCommand", CWBCommandAction, CObjectx)

CWBCommandAction::CWBCommandAction()
{
}


CWBCommandAction::~CWBCommandAction()
{
}

bool CWBCommandAction::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string windowid;
	if (attr->getAttribute("windowid", windowid))
	{
		setWindowId(windowid);
	}

	std::string wbid;
	if (attr->getAttribute("wbid", wbid))
	{
		setWBId(wbid);
	}

	std::string cmd;
	if (attr->getAttribute("cmd", cmd))
	{
		setCmd(cmd);
	}

	std::string param;
	if (attr->getAttribute("param", param))
	{
		setParam(param);
	}

	return true;
}

bool CWBCommandAction::onAction(CEventx* event)
{
	if (m_windowid.empty())
	{
		return false;
	}

	CHostWindow* pwin = nullptr;
	if (m_windowid.compare("owner") == 0)
	{
		pwin = event->getOwnerHostWindow();
	}
	else
	{
		pwin = (CHostWindow*)Application::getInstance()->getLayoutLoader()->getRoot(m_windowid.c_str());
	}

	if (pwin)
	{
		CWebBrowserControl* pwb = (CWebBrowserControl*)pwin->findControl(m_wbid.c_str());
		if (pwb)
		{
			if (m_cmd.compare("refresh") == 0)
			{
				pwb->refresh();
			}
			
		}
	}
	
	return false;
}

void CWBCommandAction::setWindowId(const std::string& windowid)
{
	m_windowid = windowid;
}

void CWBCommandAction::setWBId(const std::string& wbid)
{
	m_wbid = wbid;
}

void CWBCommandAction::setCmd(const std::string& cmd)
{
	m_cmd = cmd;
}

void CWBCommandAction::setParam(const std::string& param)
{
	m_param = param;
}

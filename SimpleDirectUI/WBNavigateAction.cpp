#include "stdafx.h"
#include "WBNavigateAction.h"
#include "Eventx.h"
#include "HostWindow.h"
#include "XmlAttribute.h"
#include "WebBrowserControl.h"
#include "LayoutLoader.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("WBNavigate", CWBNavigateAction, CObjectx)

CWBNavigateAction::CWBNavigateAction() : m_fromdata(false)
{
}


CWBNavigateAction::~CWBNavigateAction()
{
}

bool CWBNavigateAction::createFromXml(CXmlAttribute* attr)
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

	std::string url;
	if (attr->getAttribute("url", url))
	{
		setUrl(url);
	}

	std::string fromdata;
	if (attr->getAttribute("fromdata", fromdata))
	{
		setFromData(CXmlAttribute::_stringToBoolean(fromdata));
	}

	return true;
}

bool CWBNavigateAction::onAction(CEventx* event)
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
			if (m_fromdata)
			{
				std::string url = (char*)event->getData();
				pwb->navigate(url);
			}
			else
			{
				pwb->navigate(m_url);
			}	

			event->setRetval(m_retval);
		}
	}

	return false;
}

void CWBNavigateAction::setWindowId(const std::string& windowid)
{
	m_windowid = windowid;
}

void CWBNavigateAction::setWBId(const std::string& wbid)
{
	m_wbid = wbid;
}

void CWBNavigateAction::setUrl(const std::string& url)
{
	m_url = url;
}

void CWBNavigateAction::setFromData(bool fromdata)
{
	m_fromdata = fromdata;
}

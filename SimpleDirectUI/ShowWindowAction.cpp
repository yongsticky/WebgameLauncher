#include "stdafx.h"
#include "ShowWindowAction.h"
#include "Eventx.h"
#include "XmlAttribute.h"
#include "Application.h"
#include "LayoutLoader.h"
#include "HostWindow.h"
#include "Control.h"


using namespace SDUI;

DYNAMIC_OBJECT_CREATE("ShowWindow", CShowWindowAction, CObjectx)

CShowWindowAction::CShowWindowAction() : m_parentid("desktop"), m_cmd(0), m_retcode(0)
{
}


CShowWindowAction::~CShowWindowAction()
{
}

bool CShowWindowAction::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string windowid;
	if (attr->getAttribute("windowid", windowid))
	{
		setWindowId(windowid);
	}

	std::string parentid;
	if (attr->getAttribute("parentid", parentid))
	{
		setParentId(parentid);
	}

	std::string show;
	if (attr->getAttribute("show", show))
	{
		setShow(show);
	}

	std::string showopt;
	if (attr->getAttribute("showopt", showopt))
	{
		setShowOpt(showopt);
	}

	std::string cmd;
	if (attr->getAttribute("cmd", cmd))
	{
		setCmd(CXmlAttribute::_stringToInt(cmd));
	}

	std::string retcode;
	if (attr->getAttribute("retcode", retcode))
	{
		setRetCode(CXmlAttribute::_stringToInt(retcode));
	}	

	return true;
}

bool CShowWindowAction::onAction(CEventx* event)
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

	if (!pwin)
	{
		ATLASSERT(FALSE);
		return true;
	}

	// 如果使用active选项 那么窗口如果还没有active 则会自动active
	if (m_showOpt.compare("active") == 0)
	{
		if (!pwin->getHwnd())
		{
			if (m_parentid.compare("owner") == 0)
			{
				pwin->create(event->getOwnerHostWindow()->getHwnd());
			}
			else if (m_parentid.empty() || m_parentid.compare("desktop") == 0)
			{
				pwin->create(GetDesktopWindow());
			}
			else
			{
				ATLASSERT(FALSE);
				return true;
			}
		}

		pwin->setActive(true);
	}
	

	if (pwin->getActive())
	{		
		if (m_show.compare("show") == 0 || m_show.compare("true") == 0)
		{
			pwin->show(m_cmd, false);
		}
		else if (m_show.compare("hide") == 0 || m_show.compare("false") == 0)
		{
			pwin->hide(m_retcode);		
		}
		else if (m_show.compare("min") == 0 || m_show.compare("minimize") == 0)
		{
			pwin->show(SW_SHOWMINIMIZED, false);			
		}
		else if (m_show.compare("max") == 0 || m_show.compare("maximize") == 0)
		{
			pwin->show(SW_SHOWMAXIMIZED, false);			
		}
		else if (m_show.compare("restore") == 0 || m_show.compare("nomal") == 0)
		{
			pwin->show(SW_SHOWNORMAL, false);			
		}
		else if (m_show.compare("close") == 0)
		{
			pwin->hide(m_retcode);
		}
		else if (m_show.compare("auto") == 0 || m_show.compare("toggle") == 0)
		{
			pwin->toggle(m_cmd, m_retcode);
		}
		else
		{
			ATLASSERT(FALSE);
			return true;
		}
				
		if (m_showOpt.compare("deactive") == 0)
		{
			pwin->setActive(false);
		}
		
	}	

	return false;
}

void CShowWindowAction::setWindowId(const std::string& windowid)
{
	m_windowid = windowid;
}

void SDUI::CShowWindowAction::setParentId(const std::string& parentid)
{
	m_parentid = parentid;
}

void CShowWindowAction::setShow(const std::string& show)
{
	m_show = show;
}

void SDUI::CShowWindowAction::setShowOpt(const std::string& opt)
{
	m_showOpt = opt;
}

void SDUI::CShowWindowAction::setCmd(int cmd)
{
	m_cmd = cmd;
}

void SDUI::CShowWindowAction::setRetCode(int retcode)
{
	m_retcode = retcode;
}

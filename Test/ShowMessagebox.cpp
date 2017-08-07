#include "stdafx.h"
#include "ShowMessagebox.h"
#include "Eventx.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("ShowMessagebox", CShowMessagebox, CObjectx)

CShowMessagebox::CShowMessagebox()
{
}


CShowMessagebox::~CShowMessagebox()
{
}

bool CShowMessagebox::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string windowid;
	if (attr->getAttribute("windowid", windowid))
	{
		setWindowId(windowid);
	}

	std::string title;
	if (attr->getAttribute("title", title))
	{
		setTitle(title);
	}

	std::string message;
	if (attr->getAttribute("message", message))
	{
		setMessage(message);
	}

	std::string yes;
	if (attr->getAttribute("yes", yes))
	{
		setYes(yes);
	}

	std::string no;
	if (attr->getAttribute("no", no))
	{
		setNo(no);
	}

	std::string continue_;
	if (attr->getAttribute("continue", continue_))
	{
		setContinue(CXmlAttribute::_stringToInt(continue_));
	}

	return true;
}

bool CShowMessagebox::onAction(CEventx* event)
{
	CHostWindow* pwin = (CHostWindow*)Application::getInstance()->getLayoutLoader()->getRoot(m_windowid.c_str());	

	if (pwin)
	{
		CTextControl* pTitle = (CTextControl*)pwin->getRootControl()->findChild("msgbox.title");
		if (pTitle)
		{
			pTitle->setText(m_title);
		}
		

		CTextControl* pMessage = (CTextControl*)pwin->getRootControl()->findChild("msgbox.message");
		if (pMessage)
		{
			pMessage->setText(m_message);
		}
		

		CButtonControl* pYes = (CButtonControl*)pwin->getRootControl()->findChild("msgbox.yes");
		if (pYes)
		{
			pYes->getTexter()->setText(m_yes);
		}
		

		CButtonControl* pNo = (CButtonControl*)pwin->getRootControl()->findChild("msgbox.no");
		if (pNo)
		{
			pNo->getTexter()->setText(m_no);
		}
		
		
		pwin->create(event->getOwnerHostWindow()->getHwnd());
		pwin->setActive(true);
		int ret = pwin->show(0, false);

		if (ret == m_continue)
		{
			return false;
		}
	}

	return true;
}

void CShowMessagebox::setWindowId(const std::string& windowid)
{
	m_windowid = windowid;
}

void CShowMessagebox::setTitle(const std::string& title)
{
	m_title = title;
}

void CShowMessagebox::setMessage(const std::string& message)
{
	m_message = message;
}

void CShowMessagebox::setYes(const std::string& yes)
{
	m_yes = yes;
}

void CShowMessagebox::setNo(const std::string& no)
{
	m_no = no;
}

void CShowMessagebox::setContinue(int continue_)
{
	m_continue = continue_;
}

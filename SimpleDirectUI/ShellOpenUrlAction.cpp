#include "stdafx.h"
#include "ShellOpenUrlAction.h"
#include "XmlAttribute.h"
#include "Eventx.h"
#include <shellapi.h>

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("ShellOpenUrl", CShellOpenUrlAction, CObjectx)

CShellOpenUrlAction::CShellOpenUrlAction()
{
}


CShellOpenUrlAction::~CShellOpenUrlAction()
{
}

bool CShellOpenUrlAction::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string page;
	if (attr->getAttribute("page", page))
	{
		setPage(page);
	}

	std::string browser;
	if (attr->getAttribute("browser", browser))
	{
		setBrowser(browser);
	}

	return true;
}

bool CShellOpenUrlAction::onAction( CEventx* event)
{
	if (m_page.empty())
	{
		return false;
	}

	if (m_browser.compare("ie") == 0)
	{
		_forceOpenUrlWithIE(m_page);
	}
	else if (m_browser.compare("default") == 0)
	{
		if (!_shellOpenUrl(m_page))
		{
			_forceOpenUrlWithIE(m_page);
		}
	}

	event->setRetval(m_retval);

	return false;
}


void CShellOpenUrlAction::setPage(const std::string& page)
{
	m_page = page;
}

void CShellOpenUrlAction::setBrowser(const std::string& browser)
{
	m_browser = browser;
}

bool CShellOpenUrlAction::_shellOpenUrl(const std::string& url)
{
	HINSTANCE hInst = ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOW);
	return (((int)hInst) > 32);
}

bool CShellOpenUrlAction::_forceOpenUrlWithIE(const std::string& url)
{
	HINSTANCE hInst = ShellExecuteA(NULL, "open", "iexplore.exe", url.c_str(), NULL, SW_SHOW);
	return (((int)hInst) > 32);
}

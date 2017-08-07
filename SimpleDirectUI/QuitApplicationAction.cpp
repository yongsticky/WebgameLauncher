#include "stdafx.h"
#include "QuitApplicationAction.h"
#include "Eventx.h"
#include "XmlAttribute.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("QuitApplication", CQuitApplicationAction, CObjectx)

CQuitApplicationAction::CQuitApplicationAction()
{	
}


CQuitApplicationAction::~CQuitApplicationAction()
{
}

bool SDUI::CQuitApplicationAction::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string method;
	if (attr->getAttribute("method", method))
	{
		setMethod(method);
	}


	return true;
}

bool CQuitApplicationAction::onAction(CEventx* event)
{
	if (m_method.compare("exitprocess") == 0)
	{
		ExitProcess(0);
	}
	else if (m_method.compare("quitmessage") == 0)
	{
		PostQuitMessage(0);
	}
	else
	{
		ATLASSERT(FALSE);
	}

	return false;
}

void SDUI::CQuitApplicationAction::setMethod(const std::string& method)
{
	m_method = method;
}

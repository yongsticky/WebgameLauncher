#include "stdafx.h"
#include "Action.h"
#include "XmlAttribute.h"

using namespace SDUI;

CAction::CAction() : m_interest(-1), m_retval(0)
{
}


CAction::~CAction()
{
}

bool CAction::createFromXml(CXmlAttribute* attr)
{
	std::string interest;
	if (attr->getAttribute("interest", interest))
	{
		setInterest(CXmlAttribute::_stringToInt(interest));
	}
	
	std::string retval;
	if (attr->getAttribute("retval", retval))
	{
		setRetval(CXmlAttribute::_stringToInt(retval));
	}

	return true;
}

void CAction::setInterest(int interest)
{
	m_interest = interest;
}

int CAction::getInterest()
{
	return m_interest;
}

void CAction::setRetval(int retval)
{
	m_retval = retval;
}

int CAction::getClassType()
{
	return T_Action;
}
#include "stdafx.h"
#include "Eventx.h"
#include "Objectx.h"
#include "Control.h"
#include "HostWindow.h"

using namespace SDUI;

CEventx::CEventx(int id, CObjectx* owner, void* data) : m_id(id), m_owner(owner), m_data(data), m_propagation(true)
{
}

CEventx::~CEventx()
{
}

int CEventx::getId()
{
	return m_id;
}

CObjectx* CEventx::getOwner()
{
	return m_owner;
}

CControl* SDUI::CEventx::getOwnerControl()
{
	if (m_owner->getClassType() == T_Control)
	{
		return static_cast<CControl*>(m_owner);
	}
	
	ATLASSERT(FALSE);
	return nullptr;
}

CHostWindow* SDUI::CEventx::getOwnerHostWindow()
{
	int tp = m_owner->getClassType();
	if (tp == T_Windowx || tp == T_Win32Component)
	{
		return static_cast<CHostWindow*>(m_owner);
	}
	else if (tp == T_Control)
	{
		return getOwnerControl()->getHostWindow();
	}

	ATLASSERT(FALSE);
	return nullptr;
}

void* CEventx::getData()
{
	return m_data;
}

void CEventx::stopPropagation()
{
	m_propagation = false;
}

bool CEventx::getPropagation()
{
	return m_propagation;
}

void CEventx::setRetval(long retval)
{
	m_retval = retval;
}

long CEventx::getRetval()
{
	return m_retval;
}
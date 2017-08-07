#include "stdafx.h"
#include "PopupHostDialog.h"
#include "XmlAttribute.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("PopupHostDialog", CPopupHostDialog, CObjectx)

CPopupHostDialog::CPopupHostDialog() : 
	m_popupDialog(NULL),
	m_hwndParent(NULL),
	m_modal(true)
{
}

CPopupHostDialog::~CPopupHostDialog()
{
}

bool CPopupHostDialog::createFromXml(CXmlAttribute* attr)
{
	CHostWindow::createFromXml(attr);

	std::string modal;
	if (attr->getAttribute("modal", modal))
	{
		setModal(CXmlAttribute::_stringToBoolean(modal));
	}

	std::string pwid;
	if (attr->getAttribute("pwid", pwid))
	{
		setParentWindowid(pwid);
	}

	return true;
}

HWND CPopupHostDialog::getHwnd()
{
	if (m_popupDialog && m_popupDialog->IsWindow())
	{
		return m_popupDialog->m_hWnd;
	}

	return NULL;
}

HWND CPopupHostDialog::create(HWND hwndParent)
{
	if (!m_popupDialog)
	{
		m_popupDialog = new _PopupDialog(*this);				
	}

	m_hwndParent = hwndParent;

	return CHostWindow::create(hwndParent);
}

int CPopupHostDialog::show(int cmd, bool top)
{
	int ret = -1;
	if (m_popupDialog)
	{
		if (m_modal)
		{				
			ret = m_popupDialog->DoModal(m_hwndParent);
			setActive(false);
		}		
	}	

	return ret;
}

void CPopupHostDialog::hide(int retcode)
{	
	if (m_popupDialog)
	{
		m_popupDialog->EndDialog(retcode);
	}	
}

void CPopupHostDialog::setModal(bool modal)
{
	m_modal = modal;
}

void CPopupHostDialog::setParentWindowid(std::string& pwid)
{
	m_pwid = pwid;
}

#include "stdafx.h"
#include "LayoutLoader.h"
#include "tinyxml.h"
#include "XmlAttribute.h"
#include "Objectx.h"
#include "HostWindow.h"
#include "Control.h"
#include "Win32Component.h"
#include "EventxHandler.h"

using namespace SDUI;

CLayoutLoader* CLayoutLoader::s_layout = nullptr;

CLayoutLoader::CLayoutLoader()
{
}


CLayoutLoader::~CLayoutLoader()
{
}

bool CLayoutLoader::loadFromXml(const char* xmlFile)
{
	ATLASSERT(xmlFile);

	if (m_pXmlDoc || !xmlFile)
	{		
		return false;
	}

	m_pXmlDoc = new TiXmlDocument();
	
	ATLTRACE("CLayoutLoader::loadFromXml - xmlFile=%s\n", xmlFile);
	if (!m_pXmlDoc->LoadFile(xmlFile))
	{
		ATLASSERT(FALSE);
		return false;
	}

	m_xmlFile = xmlFile;

	if (_parseAndCreate())
	{
		ATLASSERT(FALSE);
		return false;
	}
	
	return true;
}


bool CLayoutLoader::startup()
{
	std::vector<CObjectx*>::iterator itr = m_root.begin();
	while (itr != m_root.end())
	{
		CObjectx* pobj = *itr;
		if (pobj && pobj->getClassType() == 0)
		{
			CHostWindow* pwin = (CHostWindow*)pobj;
			if (pwin->getActive())
			{
				pwin->create();
				return true;
			}			
		}

		++itr;
	}

	return false;
}

void CLayoutLoader::cleanup()
{
	PostQuitMessage(0);
}

CObjectx* CLayoutLoader::getRoot(const char* id)
{
	if (!id)
	{
		return nullptr;
	}

	std::vector<CObjectx*>::iterator itr = m_root.begin();
	while (itr != m_root.end())
	{
		CObjectx* pobj = *itr;
		if (pobj && pobj->getClassType() == T_Windowx)
		{
			CHostWindow* pwin = (CHostWindow*)pobj;
			if (pwin->m_id.compare(id) == 0)
			{
				return pwin;
			}
		}

		++itr;
	}

	return nullptr;
}

const std::string& SDUI::CLayoutLoader::getXmlFile()
{
	return m_xmlFile;
}

bool CLayoutLoader::_parseAndCreate()
{
	ATLASSERT(m_pXmlDoc);

	TiXmlElement* pRoot = m_pXmlDoc->RootElement();
	ATLASSERT(pRoot);
	if (!pRoot)
	{
		return false;
	}

	// root value is 'LayoutRoot'£¿
	std::string rootName = pRoot->Value();
	if (rootName.compare("LayoutRoot") != 0)
	{
		return false;
	}
	
	TiXmlElement* pElement = pRoot->FirstChildElement();

	while (pElement)
	{
		CObjectx* pv = nullptr;
		_do(pElement, &pv);

		m_root.push_back(pv);

		pElement = pElement->NextSiblingElement();
	}
			
	return false;
}


int CLayoutLoader::_do(TiXmlElement* root, CObjectx** ppv)
{
	ATLASSERT(root);
	if (!root)
	{
		return 0;
	}
	
	CXmlAttribute attr;
	if (!attr.fromXmlElement(root))
	{
		return 0;
	}

	CObjectx* pObj = nullptr;
	CObjectxCreator<CObjectx>::getInstance().createInstance(root->Value(), &pObj);	
	pObj->createFromXml(&attr);
	
	if (pObj->getClassType() == T_Control)
	{
		CControl* pcontrol = (CControl*)pObj;

		TiXmlElement* child = root->FirstChildElement();
		while (child)
		{
			CObjectx* pv = nullptr;
			_do(child, &pv);

			if (pv->getClassType() == T_EventxHandler)
			{
				pcontrol->addEventHandlerList((CEventxHandler*)pv);
			}				
			else 
			{
				pcontrol->addChild((CControl*)pv);
			}
			
			child = child->NextSiblingElement();
		}
	} 
	else if (pObj->getClassType() == T_Windowx)
	{
		CHostWindow* pwin = (CHostWindow*)pObj;

		TiXmlElement* child = root->FirstChildElement();
		while (child)
		{
			CObjectx* pv = nullptr;
			_do(child, &pv);

			if (pv->getClassType() == T_Control)
			{
				pwin->addRootControl((CControl*)pv);
			}
			else if (pv->getClassType() == T_Win32Component)
			{
				pwin->addWin32Component((CWin32Component*)pv);
			}
			else if (pv->getClassType() == T_EventxHandler)
			{
				pwin->addEventHandlerList((CEventxHandler*)pv);
			}

			child = child->NextSiblingElement();
		}
	}	
	else if (pObj->getClassType() == T_Win32Component)
	{
		CWin32Component* pcomponent = (CWin32Component*)pObj;

		TiXmlElement* child = root->FirstChildElement();
		while (child)
		{
			CObjectx* pv = nullptr;
			_do(child, &pv);

			if (pv->getClassType() == T_EventxHandler)
			{
				pcomponent->addEventHandlerList((CEventxHandler*)pv);
			}
			else if (pv->getClassType() == T_Win32Component)
			{
				pcomponent->addChild((CWin32Component*)pv);
			}
			else
			{
				ATLASSERT(FALSE);
			}

			child = child->NextSiblingElement();
		}
	}
	else if (pObj->getClassType() == T_EventxHandler)
	{
		CEventxHandler* pHandler = (CEventxHandler*)pObj;

		TiXmlElement* child = root->FirstChildElement();
		while (child)
		{
			CObjectx* pv = nullptr;
			_do(child, &pv);

			if (pv->getClassType() == T_Action)
			{
				pHandler->addAction((CAction*)pv);
			}
			else
			{
				ATLASSERT(FALSE);
			}

			child = child->NextSiblingElement();
		}
	}

	*ppv = pObj;

	return 0;
}
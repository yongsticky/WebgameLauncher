#include "stdafx.h"
#include "ButtonControl.h"
#include "TextControl.h"
#include "ImageControl.h"
#include "XmlAttribute.h"
#include "BitmapLoader.h"
#include "Eventx.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("Button", CButtonControl, CObjectx)

CButtonControl::CButtonControl() : m_imager(nullptr), m_texter(nullptr), m_bitmaps{0}, m_curState(BS_Normal)
{	
}


CButtonControl::~CButtonControl()
{
	delete m_imager;
	delete m_texter;

	m_imager = nullptr;
	m_texter = nullptr;
}

bool CButtonControl::createFromXml(CXmlAttribute* attr)
{
	CControl::createFromXml(attr);

	std::string bitmap;
	if (attr->getAttribute("bitmap", bitmap))
	{
		std::vector<std::string> vec;
		unsigned int count = CXmlAttribute::_stringToArray(bitmap, vec);
		
		for (unsigned int i = 0; i < count; i++)
		{
			m_bitmaps[i] = CBitmapLoader::getInstance()->getBitmap(vec[i].c_str());			
		}

		m_imager = new CImageControl();
		m_imager->setId("@BUTTON.BKG");		

		CXmlAttribute attrImg;
		attrImg.fromXmlAttribute(attr, "image-");
		m_imager->createFromXml(&attrImg);
		m_imager->setHitable(false);
		m_imager->setBitmap(m_bitmaps[BS_Normal]);
		addChild(m_imager);
	}

	std::string text;
	if (attr->getAttribute("text", text))
	{
		CXmlAttribute attrText;
		attrText.fromXmlAttribute(attr, "text-");
		m_texter = new CTextControl();
		m_texter->createFromXml(&attrText);		
		addChild(m_texter);
	}
		
	return true;
}

CTextControl* CButtonControl::getTexter()
{
	return m_texter;
}

CImageControl* CButtonControl::getImager()
{
	return m_imager;
}

int CButtonControl::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	int lr = CControl::onMessage(message, wparam, lparam, handled);	
	
	if (message == WindowLButtonUp)
	{		
		handled = true;

		CEventx* pEvent = new CEventx(EV_BTN_CLICK, this, 0);
		dispatchEvent(pEvent);
		delete pEvent;		
	}
	else if (message == WindowMouseHover)
	{
		handled = true;
		//ATLTRACE("Button Control, %s handle WindowMouseHover.\n", m_id.c_str());

		if (m_curState != BS_Hover && m_bitmaps[BS_Hover])
		{
			m_curState = BS_Hover;
						
			m_imager->setBitmap(m_bitmaps[BS_Hover]);
			redraw();
		}		
	}
	else if (message == WindowMouseLeave)
	{
		handled = true;
		//ATLTRACE("Button Control, %s handle WindowMouseLeave.\n", m_id.c_str());

		if (m_curState != BS_Normal && m_bitmaps[BS_Normal])
		{
			m_curState = BS_Normal;

			m_imager->setBitmap(m_bitmaps[BS_Normal]);
			redraw();
		}		
	}

	return lr;
}

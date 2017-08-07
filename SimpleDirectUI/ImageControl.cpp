#include "stdafx.h"
#include "ImageControl.h"
#include "XmlAttribute.h"
#include "BitmapLoader.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("Image", CImageControl, CObjectx)

CImageControl::CImageControl() : m_pBitmap(NULL), m_alpha(255)
{	
}

CImageControl::~CImageControl()
{
}

bool CImageControl::createFromXml(CXmlAttribute* attr)
{
	CControl::createFromXml(attr);

	std::string bitmap;
	if (attr->getAttribute("bitmap", bitmap))
	{		
		setBitmap(CBitmapLoader::getInstance()->getBitmap(bitmap.c_str()));
	}

	std::string color;
	if (attr->getAttribute("color", color))
	{
		long x, y, z;
		CXmlAttribute::_stringToXYZ(color, x, y, z);
		setColor(x, y, z);
	}

	std::string alpha;
	if (attr->getAttribute("alpha", alpha))
	{		
		setAlpha((BYTE)CXmlAttribute::_stringToInt(alpha));
	}

	std::string fit;
	if (attr->getAttribute("fit", fit))
	{
		setFit(fit);
	}

	return true;
}

int SDUI::CImageControl::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	int lr = CControl::onMessage(message, wparam, lparam, handled);

	if (message == WindowPaint)
	{
		if (isDrawable())
		{
			return _onDraw((HDC)wparam);
		}	
	}

	return lr;
}

void CImageControl::setBitmap(Gdiplus::Bitmap* bitmap)
{
	m_pBitmap = bitmap;
}

void CImageControl::setColor(BYTE r, BYTE g, BYTE b)
{
	m_color.SetValue(Gdiplus::Color::MakeARGB(m_alpha, r, g, b));
}

void CImageControl::setAlpha(BYTE alpha)
{
	m_alpha = alpha;
}

void SDUI::CImageControl::setFit(const std::string& fit)
{
	m_fit = fit;
}

int CImageControl::_onDraw(HDC hdc)
{
	if (m_pBitmap)
	{
		return _drawBitmap(hdc);
	}
	
	return _fillColor(hdc);	
}

int CImageControl::_drawBitmap(HDC hdc)
{
	Gdiplus::Graphics g(hdc);
	
	if (m_fit.compare("wrap") == 0)		// Æ½ÆÌ
	{								
		Gdiplus::TextureBrush br(m_pBitmap, Gdiplus::WrapModeTile);		
		br.TranslateTransform(m_xx, m_yy);
		g.FillRectangle(&br, m_xx, m_yy, m_cxcx, m_cycy);
	}
	else
	{
		g.DrawImage(m_pBitmap, m_xx, m_yy, m_cxcx, m_cycy);
	}	

	return 0;
}

int CImageControl::_fillColor(HDC hdc)
{
	Gdiplus::Graphics g(hdc);

	Gdiplus::SolidBrush br(m_color);
	RECT rc{ m_xx, m_yy, m_xx + m_cxcx, m_yy + m_cycy };
	g.FillRectangle(&br, m_xx, m_yy, m_cxcx, m_cycy);		

	return 0;
}

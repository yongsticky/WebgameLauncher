#include "stdafx.h"
#include "TextControl.h"
#include "XmlAttribute.h"
#include <gdiplus.h>

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("Text", CTextControl, CObjectx)

CTextControl::CTextControl() : 
	m_weight(0),
	m_height(0),
	m_width(0),
	m_underline(false),
	m_strikeout(false),
	m_italic(false),
	m_color(0)
{
}


CTextControl::~CTextControl()
{
}

bool CTextControl::createFromXml(CXmlAttribute* attr)
{
	CControl::createFromXml(attr);

	std::string text;
	if (attr->getAttribute("text", text))
	{
		setText(text);
	}

	std::string face;
	if (attr->getAttribute("face", face))
	{
		setFace(face);
	}

	std::string weight;
	if (attr->getAttribute("weight", weight))
	{
		setWeight(CXmlAttribute::_stringToInt(weight));
	}

	std::string height;
	if (attr->getAttribute("height", height))
	{
		setHeight(CXmlAttribute::_stringToInt(height));
	}

	std::string width;
	if (attr->getAttribute("width", width))
	{
		setWidth(CXmlAttribute::_stringToInt(width));
	}

	std::string underline;
	if (attr->getAttribute("underline", underline))
	{
		setUnderline(CXmlAttribute::_stringToBoolean(underline));
	}

	std::string strikeout;
	if (attr->getAttribute("strikeout", strikeout))
	{
		setStrikeout(CXmlAttribute::_stringToBoolean(strikeout));
	}

	std::string italic;
	if (attr->getAttribute("italic", italic))
	{
		setItalic(CXmlAttribute::_stringToBoolean(italic));
	}

	std::string color;
	if (attr->getAttribute("color", color))
	{
		long x, y, z;
		CXmlAttribute::_stringToXYZ(color, x, y, z);
		setColor(x, y, z);
	}

	std::string direction;
	if (attr->getAttribute("direction", direction))
	{
		setDirection(direction);
	}

	std::string alignment;
	if (attr->getAttribute("alignment", alignment))
	{
		setAlignment(alignment);
	}

	std::string valignment;
	if (attr->getAttribute("valignment", valignment))
	{
		setVAlignment(valignment);
	}

	return true;
}

int SDUI::CTextControl::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	int lr = CControl::onMessage(message, wparam, lparam, handled);
	
	if (message == WindowPaint)
	{
		_onDraw((HDC)wparam);
	}

	return lr;
	
}

void CTextControl::setText(const std::string& text)
{
	m_text = text;
}

void CTextControl::setFace(const std::string& face)
{
	m_face = face;
}

void CTextControl::setWeight(int weight)
{
	m_weight = weight;
}

void CTextControl::setHeight(int height)
{
	m_height = height;
}

void CTextControl::setWidth(int width)
{
	m_width = width;
}

void CTextControl::setUnderline(bool underline)
{
	m_underline = underline;
}

void CTextControl::setStrikeout(bool strikeout)
{
	m_strikeout = strikeout;
}

void CTextControl::setItalic(bool italic)
{
	m_italic = italic;
}

void CTextControl::setColor(BYTE r, BYTE g, BYTE b)
{
	m_color.SetValue(Gdiplus::Color::MakeARGB(254, r, g, b));
}

void CTextControl::setDirection(const std::string& direction)
{
	m_direction = direction;
}

void CTextControl::setAlignment(const std::string& alignment)
{
	m_alignment = alignment;
}

void CTextControl::setVAlignment(const std::string& valignment)
{
	m_valignment = valignment;
}

int CTextControl::_onDraw(HDC hdc)
{
	if (!hdc || m_text.empty())
	{
		return 0;
	}

	USES_CONVERSION;
	WCHAR* pText = A2W(m_text.c_str());
	if (!pText)
	{
		return 0;
	}

	Gdiplus::Graphics g(hdc);

	LOGFONT lf;
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT), sizeof(lf), &lf);

	if (!m_face.empty() && m_face.size() < LF_FACESIZE)
	{
		USES_CONVERSION;
		_tcscpy(lf.lfFaceName, A2CT(m_face.c_str()));
	}

	if (m_weight > 0)
	{
		lf.lfWeight = m_weight;
	}

	if (m_height > 0)
	{
		lf.lfHeight = m_height;
	}

	if (m_width > 0)
	{
		lf.lfWidth = m_width;
	}

	lf.lfUnderline = m_underline ? TRUE : FALSE;
	lf.lfStrikeOut = m_strikeout ? TRUE : FALSE;
	lf.lfItalic = m_italic ? TRUE : FALSE;
	
	Gdiplus::Font font(hdc, &lf);			 
	Gdiplus::SolidBrush br(m_color);
	Gdiplus::StringFormat sf;

	if (m_direction.compare("right") == 0)
	{
		sf.SetFormatFlags(Gdiplus::StringFormatFlagsDirectionRightToLeft);
	}
	else if (m_direction.compare("vertical") == 0)
	{
		sf.SetFormatFlags(Gdiplus::StringFormatFlagsDirectionVertical);
	}

	if (m_alignment.compare("center") == 0)
	{
		sf.SetAlignment(Gdiplus::StringAlignmentCenter);
	}
	else if (m_alignment.compare("far") == 0)
	{
		sf.SetAlignment(Gdiplus::StringAlignmentFar);
	}
	else
	{
		sf.SetAlignment(Gdiplus::StringAlignmentNear);
	}
	
	if (m_valignment.compare("center") == 0)
	{
		sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	}
	else if (m_valignment.compare("far") == 0)
	{
		sf.SetLineAlignment(Gdiplus::StringAlignmentFar);
	}
	else
	{
		sf.SetLineAlignment(Gdiplus::StringAlignmentNear);
	}
		
	Gdiplus::Status sta = g.DrawString(pText, wcslen(pText), &font, Gdiplus::RectF(m_xx, m_yy, m_cxcx, m_cycy), &sf, &br);
	ATLASSERT(sta == Gdiplus::Ok);

	return 0;
}

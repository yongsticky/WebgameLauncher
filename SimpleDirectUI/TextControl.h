#pragma once

#include "Control.h"
#include <string>
#include <gdiplus.h>


namespace SDUI
{


	class CTextControl : public CControl
	{
	public:
		CTextControl();
		virtual ~CTextControl();

		DYNAMIC_OBJECT_DECLARE(CTextControl, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

		void setText(const std::string& text);
		void setFace(const std::string& face);
		void setWeight(int weight);
		void setHeight(int height);
		void setWidth(int width);
		void setUnderline(bool underline);
		void setStrikeout(bool strikeout);
		void setItalic(bool italic);
		void setColor(BYTE r, BYTE g, BYTE b);
		void setDirection(const std::string& direction);
		void setAlignment(const std::string& alignment);
		void setVAlignment(const std::string& valignment);

	protected:
		int _onDraw(HDC hdc);

	private:
		std::string m_text;

		std::string m_face;
		int m_weight;
		int m_height;
		int m_width;
		bool m_underline;
		bool m_strikeout;
		bool m_italic;
		Gdiplus::Color m_color;
		std::string m_direction;
		std::string m_alignment;
		std::string m_valignment;
	};

};
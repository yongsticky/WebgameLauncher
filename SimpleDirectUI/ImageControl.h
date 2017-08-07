#pragma once

#include "Control.h"

#include <gdiplus.h>

namespace SDUI
{


	class CImageControl : public CControl
	{
	public:
		CImageControl();
		virtual ~CImageControl();

		DYNAMIC_OBJECT_DECLARE(CImageControl, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

		

	public:
		void setBitmap(Gdiplus::Bitmap* bitmap);
		void setColor(BYTE r, BYTE g, BYTE b);
		void setAlpha(BYTE alpha);
		void setFit(const std::string& fit);

	private:
		int _onDraw(HDC hdc);

		int _drawBitmap(HDC hdc);
		int _fillColor(HDC hdc);

	private:
		Gdiplus::Bitmap* m_pBitmap;
		Gdiplus::Color m_color;

		BYTE m_alpha;
		std::string m_fit;
	};
};
#pragma once

#include "Control.h"

#include <gdiplus.h>

namespace SDUI
{


	class CTextControl;
	class CImageControl;
	class CButtonControl : public CControl
	{
	public:
		CButtonControl();
		virtual ~CButtonControl();
		
		DYNAMIC_OBJECT_DECLARE(CButtonControl, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);

		CTextControl* getTexter();
		CImageControl* getImager();

	protected:
		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

	private:
		Gdiplus::Bitmap* m_bitmaps[4];

		enum ButtonState {
			BS_Normal = 0,
			BS_Hover = 1,
			BS_Pushed = 2,
			BS_Disable = 3
		};

		ButtonState m_curState;

		CTextControl* m_texter;
		CImageControl* m_imager;
	};


};
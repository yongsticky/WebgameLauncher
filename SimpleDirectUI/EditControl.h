#pragma once
#include "Control.h"


namespace SDUI
{

	class CEditControl : public CControl
	{
	public:
		CEditControl();
		virtual ~CEditControl();


		DYNAMIC_OBJECT_DECLARE(CEditControl, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual unsigned int addChild(CControl* control);

	protected:
		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

	protected:
		CWindow m_edit;
	};


};
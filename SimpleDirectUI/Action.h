#pragma once
#include "Objectx.h"

namespace SDUI
{


	class CEventx;
	class CAction : public CObjectx
	{
	public:
		CAction();
		virtual ~CAction();

		virtual bool createFromXml(CXmlAttribute* attr);

		void setInterest(int interest);
		int getInterest();
		void setRetval(int retval);

		virtual bool onAction(CEventx* event) = 0;
		virtual int getClassType();

	protected:
		int m_interest;
		int m_retval;
	};


};
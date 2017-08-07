#pragma once
#include "Objectx.h"
#include <vector>

namespace SDUI
{



	class CAction;
	class CEventx;
	class CEventxHandler;
	class CEventxHandler : public CObjectx
	{
	public:
		CEventxHandler();
		~CEventxHandler();

		DYNAMIC_OBJECT_DECLARE(CEventxHandler, CObjectx)

			virtual bool createFromXml(CXmlAttribute* attr);
		virtual int getClassType();

		unsigned int addAction(CAction* action);
		void runAction(CEventx* event);

		void setInterest(int interest);
		int getInterest();

	protected:
		int m_interest;
		std::vector<CAction*> m_actions;
	};


};
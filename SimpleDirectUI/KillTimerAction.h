#pragma once
#include "Action.h"

namespace SDUI
{

	
	class CKillTimerAction : public CAction
	{
	public:
		CKillTimerAction();
		virtual ~CKillTimerAction();

		DYNAMIC_OBJECT_DECLARE(CKillTimerAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);

		void setWindowId(const std::string& windowid);
		void setTimerId(unsigned int timerId);

	protected:
		std::string m_windowid;
		unsigned int m_timerid;
	};


}
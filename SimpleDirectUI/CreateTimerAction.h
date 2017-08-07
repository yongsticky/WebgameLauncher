#pragma once
#include "Action.h"

namespace SDUI
{

	class CCreateTimerAction : public CAction
	{
	public:
		CCreateTimerAction();
		virtual ~CCreateTimerAction();

		DYNAMIC_OBJECT_DECLARE(CCreateTimerAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);

		void setWindowId(const std::string& windowid);
		void setTimerId(unsigned int timerId);
		void setElapse(unsigned int elapse);
		//void setOnce(bool once);

	protected:
		std::string m_windowid;
		unsigned int m_timerId;
		unsigned int m_elapse;
		//bool m_once;
	};


}
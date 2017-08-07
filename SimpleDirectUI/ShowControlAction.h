#pragma once
#include "Action.h"

namespace SDUI
{

	class CShowControlAction : public CAction
	{
	public:
		CShowControlAction();
		virtual ~CShowControlAction();


		DYNAMIC_OBJECT_DECLARE(CShowControlAction, CObjectx)


		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);

		void setControlId(const std::string& controlid);
		void setWindowId(const std::string& windowid);
		void setShow(const std::string& show);		

	protected:
		std::string m_windowid;
		std::string m_controlid;
		std::string m_show;
	};

};
#pragma once
#include "Action.h"

namespace SDUI
{

	class CShowComponentAction : public CAction
	{
	public:
		CShowComponentAction();
		virtual ~CShowComponentAction();

		DYNAMIC_OBJECT_DECLARE(CShowComponentAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);

		void setWindowId(const std::string& windowid);
		void setComponentId(const std::string& componentid);
		void setShow(std::string show);
		void setDestroy(bool destroy);

	protected:
		std::string m_windowid;
		std::string m_componentid;
				
		std::string m_show;
		bool m_destroy;
	};


};
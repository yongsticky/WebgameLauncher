#pragma once
#include "Action.h"

namespace SDUI
{




	class CWBCommandAction : public CAction
	{
	public:
		CWBCommandAction();
		virtual ~CWBCommandAction();


		DYNAMIC_OBJECT_DECLARE(CWBCommandAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);

		void setWindowId(const std::string& windowid);
		void setWBId(const std::string& wbid);
		void setCmd(const std::string& cmd);
		void setParam(const std::string& param);


	protected:
		std::string m_windowid;
		std::string m_wbid;
		std::string m_cmd;
		std::string m_param;
	};


};

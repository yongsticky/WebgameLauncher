#pragma once
#include "Action.h"
#include <string>

namespace SDUI
{
	class CShowWindowAction : public CAction
	{
	public:
		CShowWindowAction();
		virtual ~CShowWindowAction();

		DYNAMIC_OBJECT_DECLARE(CShowWindowAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);

		void setWindowId(const std::string& windowid);
		void setParentId(const std::string& parentid);
		void setShow(const std::string& show);		
		void setShowOpt(const std::string& opt);
		void setCmd(int cmd);
		void setRetCode(int retcode);
		

	protected:
		std::string m_windowid;
		std::string m_parentid;
		std::string m_show;		
		std::string m_showOpt;		// active deactive

		int m_cmd;
		int m_retcode;		
	};

};
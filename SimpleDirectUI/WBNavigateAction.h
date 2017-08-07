#pragma once
#include "Action.h"
#include <string>

namespace SDUI
{

	class CWBNavigateAction : public CAction
	{
	public:
		CWBNavigateAction();
		virtual ~CWBNavigateAction();

		DYNAMIC_OBJECT_DECLARE(CWBNavigateAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);


		void setWindowId(const std::string& windowid);
		void setWBId(const std::string& wbid);
		void setUrl(const std::string& url);
		void setFromData(bool fromdata);

	protected:
		std::string m_windowid;
		std::string m_wbid;
		std::string m_url;
		bool m_fromdata;
	};


};
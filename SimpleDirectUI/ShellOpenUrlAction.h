#pragma once
#include "Action.h"
#include <string>

namespace SDUI
{

	class CShellOpenUrlAction : public CAction
	{
	public:
		CShellOpenUrlAction();
		virtual ~CShellOpenUrlAction();

		DYNAMIC_OBJECT_DECLARE(CShellOpenUrlAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);

	public:
		void setPage(const std::string& page);
		void setBrowser(const std::string& browser);

	private:
		bool _shellOpenUrl(const std::string& url);
		bool _forceOpenUrlWithIE(const std::string& url);

	private:
		std::string m_page;
		std::string m_browser;
	};


};
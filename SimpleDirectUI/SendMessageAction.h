#pragma once
#include "Action.h"

namespace SDUI
{


	class CSendMessageAction : public CAction
	{
	public:
		CSendMessageAction();
		virtual ~CSendMessageAction();

		DYNAMIC_OBJECT_DECLARE(CSendMessageAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);

		void setWindowId(const std::string& windowid);
		void setMessage(int message);
		void setSync(bool sync);

	protected:
		std::string m_windowid;
		int m_message;
		bool m_sync;
	};


}
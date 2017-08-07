#pragma once
#include "Action.h"

namespace SDUI
{

	class CQuitApplicationAction : public CAction
	{
	public:
		CQuitApplicationAction();
		virtual ~CQuitApplicationAction();

		DYNAMIC_OBJECT_DECLARE(CQuitApplicationAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);

		virtual bool onAction(CEventx* event);

		void setMethod(const std::string& method);

	protected:
		std::string m_method;
	};


};
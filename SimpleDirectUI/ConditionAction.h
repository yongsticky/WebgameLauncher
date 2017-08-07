#pragma once
#include "Action.h"
#include <string>

namespace SDUI
{

	class CConditionAction : public CAction
	{
	public:
		CConditionAction();
		virtual ~CConditionAction();

		DYNAMIC_OBJECT_DECLARE(CConditionAction, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual bool onAction(CEventx* event);

		void setString(const std::string& str);
		void setCondition(const std::string& condition);

	protected:
		std::string m_str;
		std::string m_condition;
	};


};
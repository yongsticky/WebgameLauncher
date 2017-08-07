#pragma once
#include "ObjectxCreator.h"

namespace SDUI
{


	class CXmlAttribute;
	typedef enum _enumClassType
	{
		T_Undefined = -1,
		T_Windowx = 0,
		T_Control,
		T_Win32Component,
		T_EventxHandler,
		T_Action
	} ClassType;

	class CObjectx
	{
	public:
		CObjectx();
		virtual ~CObjectx();

		virtual bool createFromXml(CXmlAttribute* attr) = 0;
		virtual int getClassType() = 0;

		// 
		bool equal(CObjectx* obj);
	};

};
#pragma once

#include "EventId.h"


namespace SDUI
{


	class CObjectx;
	class CControl;
	class CHostWindow;
	class CEventx
	{
	public:
		CEventx(int id, CObjectx* owner, void* data);		
		virtual ~CEventx();

		int getId();

		CObjectx* getOwner();
		CControl* getOwnerControl();
		CHostWindow* getOwnerHostWindow();

		void* getData();

		void stopPropagation();
		bool getPropagation();

		void setRetval(long retval);
		long getRetval();


	protected:
		int m_id;
		CObjectx* m_owner;
		void* m_data;

		long m_retval;

		bool m_propagation;			// 事件是否继续冒泡	
	};

};
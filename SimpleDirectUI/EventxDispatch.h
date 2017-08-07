#pragma once

#include <vector>


namespace SDUI
{


	class CEventx;
	class CEventxHandler;
	class CEventxDispatch
	{
	public:
		CEventxDispatch();
		virtual ~CEventxDispatch();

		virtual unsigned int addEventHandlerList(CEventxHandler* handler);
		virtual bool dispatchEvent(CEventx* event);

	protected:
		std::vector<CEventxHandler*> m_handlerList;
	};


};
#pragma once

#include "Objectx.h"
#include "EventxDispatch.h"
#include <string>

#define WM_WIN32_SYSTRAYICON (WM_APP+1)
#define WM_WIN32_SYSMENU (WM_APP+2)


namespace SDUI
{

	class CWin32ComponentWindow;

	class CWin32Component :
		public CObjectx,
		public CEventxDispatch
	{
		friend class CWin32ComponentWindow;

	public:
		CWin32Component();
		virtual ~CWin32Component();

		virtual int getClassType();

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

		virtual int addChild(CWin32Component* child);

		virtual void show();
		virtual void hide();
		virtual void toggle(int cmd, int retcode);

		void setId(const std::string& id);
		std::string getId();
		void setVisible(bool visible);
		void setPos(int x, int y);

	protected:
		std::string m_id;
		bool m_visible;

		CWin32ComponentWindow* m_owner;

		std::vector<CWin32Component*> m_children;

		int m_x;
		int m_y;
	};


};
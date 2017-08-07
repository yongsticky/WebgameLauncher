#pragma once
#include "Win32Component.h"


namespace SDUI
{


	class CWin32ContextMenu : public CWin32Component
	{
	public:
		CWin32ContextMenu();
		virtual ~CWin32ContextMenu();

		DYNAMIC_OBJECT_DECLARE(CWin32ContextMenu, CObjectx)

			virtual bool createFromXml(CXmlAttribute* attr);
		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

		virtual void show();
		virtual void hide();

		void setGroup(int group);

	protected:
		HMENU _create();

	protected:
		HMENU m_hMenu;

		int m_group;
	};

};
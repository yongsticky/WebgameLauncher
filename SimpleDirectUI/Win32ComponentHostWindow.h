#pragma once
#include "HostWindow.h"

namespace SDUI
{



#define WM_WIN32_COMPONENT_BEGIN (WM_APP+1)
#define WM_WIN32_COMPONENT_END (WM_APP+5)

	class CXmlAttribute;
	class CWin32ComponentWindow :
		public CWindowImpl<CWin32ComponentWindow>,
		public CHostWindow
	{
	public:
		CWin32ComponentWindow();
		virtual ~CWin32ComponentWindow();

		DECLARE_WND_CLASS(_T("WIN32_COMPNONTE_WINDOW"))

		DYNAMIC_OBJECT_DECLARE(CWin32ComponentWindow, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);

		virtual HWND getHwnd();

		virtual HWND create(HWND hwndParent = nullptr);		

		virtual int show(int cmd, bool top);
		virtual void hide(int retcode);

		bool addWin32Component(CWin32Component* component);
		virtual CWin32Component* getWin32Component(const char* componentid);

		BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0);

		LRESULT onWin32ComponentMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	protected:
		std::vector<CWin32Component*> m_components;
	};



};
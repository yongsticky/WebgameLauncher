#pragma once
#include "HostWindow.h"
#include "WindowMessageDispatcher.h"
#include "MouseHoverLeaveTracker.h"

namespace SDUI
{



	class CFrameHostWindow :
		public CHostWindow,
		public CWindowMessageDispatcher

	{
	public:
		CFrameHostWindow();
		virtual ~CFrameHostWindow();

		DYNAMIC_OBJECT_DECLARE(CFrameHostWindow, CObjectx)

			virtual bool createFromXml(CXmlAttribute* attr);

		virtual HWND getHwnd();

		virtual HWND create(HWND hwndParent = nullptr);
		
		virtual int show(int cmd, bool top);
		virtual void hide(int retcode);

	public:
		void setTitle(const std::string& title);
		void setIcon(HICON icon);
		void setLayered(bool layered);
		void setToolwindow(bool toolwindow);
		void setMaximizebox(bool maximizebox);
		void setMinimizebox(bool minimizebox);
		void setShowdefault(int showdefault);

	protected:
		class _FrameWindow : 
			public CWindowImpl<_FrameWindow>,
			public _MouseHoverLeaveTracker
		{
		public:
			_FrameWindow(CFrameHostWindow& owner);
			virtual ~_FrameWindow();

			DECLARE_WND_CLASS(_T("_HOSTINNER_FRAMEWINDOW"))

			BEGIN_MSG_MAP(_FrameWindow)
				CHAIN_MSG_MAP_MEMBER(m_owner)
				CHAIN_MSG_MAP(_MouseHoverLeaveTracker)
				MESSAGE_HANDLER(WM_CREATE, OnCreate)				
				MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
				MESSAGE_HANDLER(WM_CLOSE, onClose)
				MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
				MESSAGE_HANDLER(WM_PAINT, OnPaint)
				MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
				MESSAGE_HANDLER(WM_TIMER, OnTimer)
			END_MSG_MAP()

			LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
			LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
			LRESULT onClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
			LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
			LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
			LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);			
			LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

			void bringWindowToTop();

		private:
			CFrameHostWindow& m_owner;
		};

		_FrameWindow* m_frameWindow;

		std::string m_title;
		HICON m_icon;

		bool m_layered;
		bool m_toolwindow;
		bool m_maximizebox;
		bool m_minimizebox;
		int m_showdefault;
	};


};
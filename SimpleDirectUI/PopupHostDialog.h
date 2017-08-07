#pragma once
#include "HostWindow.h"
#include "WindowMessageDispatcher.h"
#include "MouseHoverLeaveTracker.h"

namespace SDUI
{



	class CPopupHostDialog :
		public CHostWindow,
		public CWindowMessageDispatcher
	{
	public:
		CPopupHostDialog();
		virtual ~CPopupHostDialog();

		DYNAMIC_OBJECT_DECLARE(CPopupHostDialog, CObjectx)

			virtual bool createFromXml(CXmlAttribute* attr);

		virtual HWND getHwnd();
		virtual HWND create(HWND hwndParent = nullptr);
		
		virtual int show(int cmd, bool top);
		virtual void hide(int retcode);

		void setModal(bool modal);
		void setParentWindowid(std::string& pwid);

	protected:
		class _PopupDialog : 
			public CDialogImpl<CPopupHostDialog>,
			public _MouseHoverLeaveTracker
		{
		public:
			_PopupDialog(CPopupHostDialog& owner);
			virtual ~_PopupDialog();

			INT_PTR DoModal(HWND hWndParent = ::GetActiveWindow(), LPARAM dwInitParam = NULL);
			HWND Create(HWND hWndParent, LPARAM dwInitParam = NULL);

			BEGIN_MSG_MAP(_PopupDialog)
				CHAIN_MSG_MAP_MEMBER(m_owner)
				CHAIN_MSG_MAP(_MouseHoverLeaveTracker)
				MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
				MESSAGE_HANDLER(WM_PAINT, OnPaint)
				COMMAND_ID_HANDLER(IDOK, OnOK)
				COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
			END_MSG_MAP()

			LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
			LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
			LRESULT OnOK(int nID, int nCode, HWND hWnd, BOOL& bHandled);
			LRESULT OnCancel(int nID, int nCode, HWND hWnd, BOOL& bHandled);

		private:
			CPopupHostDialog& m_owner;
		};

		_PopupDialog* m_popupDialog;

		bool m_modal;		// is Modal Dialog?
		std::string m_pwid;	// parent window id

		HWND m_hwndParent;
	};


	
};
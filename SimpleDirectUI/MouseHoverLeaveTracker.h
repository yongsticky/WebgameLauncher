#pragma once

namespace SDUI
{



	class _MouseHoverLeaveTracker
	{
	public:
		_MouseHoverLeaveTracker();
		virtual ~_MouseHoverLeaveTracker();

		BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0);


	protected:
		LRESULT OnMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnMouseHover(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnMouseLeave(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		BOOL m_bTrackMouseLeave;
		BOOL m_bTrackMouseHover;
	};


};
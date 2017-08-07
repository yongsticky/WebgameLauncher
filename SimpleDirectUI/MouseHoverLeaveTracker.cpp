#include "stdafx.h"
#include "MouseHoverLeaveTracker.h"

using namespace SDUI;

_MouseHoverLeaveTracker::_MouseHoverLeaveTracker()
{
}


_MouseHoverLeaveTracker::~_MouseHoverLeaveTracker()
{
}

BOOL _MouseHoverLeaveTracker::ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
{
	BOOL bHandled = FALSE;
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
	{
		bHandled = TRUE;
		lResult = OnMouseMove(hWnd, uMsg, wParam, lParam, bHandled);
		if (bHandled)
		{
			return TRUE;
		}
	}		
	break;
	case WM_MOUSEHOVER:
	{
		bHandled = TRUE;
		lResult = OnMouseHover(hWnd, uMsg, wParam, lParam, bHandled);
		if (bHandled)
		{
			return TRUE;
		}
	}
	break;
	case WM_MOUSELEAVE:
	{
		bHandled = TRUE;
		lResult = OnMouseLeave(hWnd, uMsg, wParam, lParam, bHandled);
		if (bHandled)
		{
			return TRUE;
		}
	}
	break;
	default:
		break;
	}
	
	return FALSE;
}


LRESULT _MouseHoverLeaveTracker::OnMouseMove(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (!m_bTrackMouseLeave)
	{
		TRACKMOUSEEVENT tm;
		tm.cbSize = sizeof(tm);
		tm.hwndTrack = hWnd;
		tm.dwFlags = TME_LEAVE;
		tm.dwHoverTime = 10;
		m_bTrackMouseLeave = TrackMouseEvent(&tm);
	}

	if (!m_bTrackMouseHover)
	{
		TRACKMOUSEEVENT tm;
		tm.cbSize = sizeof(tm);
		tm.hwndTrack = hWnd;
		tm.dwFlags = TME_HOVER;
		tm.dwHoverTime = 30;
		m_bTrackMouseHover = TrackMouseEvent(&tm);
	}


	return 0;
}

LRESULT _MouseHoverLeaveTracker::OnMouseHover(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	m_bTrackMouseHover = FALSE;

	return 0;
}

LRESULT _MouseHoverLeaveTracker::OnMouseLeave(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{	
	m_bTrackMouseHover = FALSE;
	m_bTrackMouseLeave = FALSE;

	return 0;
}
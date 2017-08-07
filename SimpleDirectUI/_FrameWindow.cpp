#include "stdafx.h"
#include "FrameHostWindow.h"
#include "Eventx.h"

using namespace SDUI;

CFrameHostWindow::_FrameWindow::_FrameWindow(CFrameHostWindow& owner) : m_owner(owner)
{
}

CFrameHostWindow::_FrameWindow::~_FrameWindow()
{
}

LRESULT CFrameHostWindow::_FrameWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if (m_owner.m_visible)
	{			
		ShowWindow(SW_SHOW);		
	}

	if (m_owner.m_center)
	{
		CenterWindow();
	}
	
	CEventx* pEvent = new CEventx(EV_WIN_CREATE, &m_owner, 0);
	m_owner.dispatchEvent(pEvent);
	delete pEvent;

	return 0;
}

LRESULT CFrameHostWindow::_FrameWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CFrameHostWindow::_FrameWindow::onClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	ShowWindow(SW_HIDE);

	return 0;
}

LRESULT CFrameHostWindow::_FrameWindow::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

LRESULT CFrameHostWindow::_FrameWindow::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_owner.m_layered)
	{
		if (!(GetExStyle() & WS_EX_LAYERED))
		{
			ModifyStyleEx(0, WS_EX_LAYERED, 0);
		}
	}

	PAINTSTRUCT ps = { 0 };
	HDC paintdc = BeginPaint(&ps);

	RECT rc;
	GetClientRect(&rc);

	HDC memdc = CreateCompatibleDC(paintdc);
	HBITMAP hbmp = CreateCompatibleBitmap(paintdc, rc.right - rc.left, rc.bottom - rc.top);

	int saveid = SaveDC(memdc);
	SelectObject(memdc, hbmp);

	LRESULT lr = 0;
	m_owner.ProcessWindowMessage(m_hWnd, (WM_USER + WM_PAINT), (WPARAM)memdc, 0, lr);

	if (m_owner.m_layered)
	{
		BLENDFUNCTION bf = { 0 };
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = 255;

		POINT pt = { 0, 0 };

		RECT rcWin;
		CopyRect(&rcWin, &rc);
		ClientToScreen(&rcWin);
		POINT ptWin = { rcWin.left, rcWin.top };
		SIZE sz = { rc.right - rc.left, rc.bottom - rc.top };
		UpdateLayeredWindow(m_hWnd, paintdc, &ptWin, &sz, memdc, &pt, 0, &bf, ULW_ALPHA);
	}
	else
	{
		BitBlt(paintdc, 0, 0, rc.right - rc.left, rc.bottom - rc.left, memdc, 0, 0, SRCCOPY);
	}

	RestoreDC(memdc, saveid);

	DeleteObject(hbmp);
	DeleteObject(memdc);

	EndPaint(&ps);

	return 0;
}

LRESULT SDUI::CFrameHostWindow::_FrameWindow::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MINMAXINFO* pinfo = (MINMAXINFO*)lParam;	

	pinfo->ptMinTrackSize.x = m_owner.m_mincx;
	pinfo->ptMinTrackSize.y = m_owner.m_mincy;
		
	pinfo->ptMaxSize.x = GetSystemMetrics(SM_CXFULLSCREEN) + GetSystemMetrics(SM_CXDLGFRAME);
	pinfo->ptMaxSize.y = GetSystemMetrics(SM_CYFULLSCREEN) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME);

	return 0;
}

LRESULT CFrameHostWindow::_FrameWindow::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	unsigned int idEvent = (unsigned int)wParam;
	::KillTimer(m_hWnd, idEvent);

	CEventx* pEvent = new CEventx(EV_WIN_TIMER, &m_owner, 0);
	m_owner.dispatchEvent(pEvent);
	delete pEvent;

	return 0;
}

void CFrameHostWindow::_FrameWindow::bringWindowToTop()
{
	AttachThreadInput(GetWindowThreadProcessId(::GetForegroundWindow(), NULL), GetCurrentThreadId(), TRUE);
	SetForegroundWindow(m_hWnd);
	AttachThreadInput(GetWindowThreadProcessId(::GetForegroundWindow(), NULL), GetCurrentThreadId(), FALSE);

	BringWindowToTop();
}
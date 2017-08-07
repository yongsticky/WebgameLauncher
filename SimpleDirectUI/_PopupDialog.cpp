#include "stdafx.h"
#include "PopupHostDialog.h"
#include "Application.h"
#include "Eventx.h"

using namespace SDUI;

LPWORD lpwAlign(LPWORD lpIn)
{
	ULONG ul;

	ul = (ULONG)lpIn;
	ul++;
	ul >>= 1;
	ul <<= 1;
	return (LPWORD)ul;
}

HGLOBAL _allocBlankDialogTemplate(int x, int y, int cx, int cy)
{
	HGLOBAL hgbl;
	LPDLGTEMPLATE lpdt;
	LPDLGITEMTEMPLATE lpdit;
	LPWORD lpw;
	LPWSTR lpwsz;
	int nchar;

	hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
	if (!hgbl)
	{
		return NULL;
	}

	lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);

	// Define a dialog box.

	lpdt->style = WS_POPUP | WS_SYSMENU | WS_VISIBLE;
	lpdt->cdit = 1;         // Number of controls
	lpdt->x = x;
	lpdt->y = y;
	lpdt->cx = cx;
	lpdt->cy = cy;

	lpw = (LPWORD)(lpdt + 1);
	*lpw++ = 0;             // No menu
	*lpw++ = 0;             // Predefined dialog box class (by default)

	lpwsz = (LPWSTR)lpw;
	nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "My Dialog", -1, lpwsz, 50);
	lpw += nchar;

	lpw = lpwAlign(lpw);    // Align DLGITEMTEMPLATE on DWORD boundary
	lpdit = (LPDLGITEMTEMPLATE)lpw;
	lpdit->x = 0;
	lpdit->y = 0;
	lpdit->cx = 0;
	lpdit->cy = 0;
	lpdit->id = IDOK;       // OK button identifier
	lpdit->style = WS_CHILD | BS_DEFPUSHBUTTON;

	lpw = (LPWORD)(lpdit + 1);
	*lpw++ = 0xFFFF;
	*lpw++ = 0x0080;        // Button class

	lpwsz = (LPWSTR)lpw;
	nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "OK", -1, lpwsz, 50);
	lpw += nchar;
	*lpw++ = 0;             // No creation data


	GlobalUnlock(hgbl);

	return hgbl;
}


INT_PTR CPopupHostDialog::_PopupDialog::DoModal(HWND hWndParent, LPARAM dwInitParam)
{
	ATLASSERT(m_hWnd == NULL);
	_AtlWinModule.AddCreateWndData(&m_thunk.cd, (CDialogImplBaseT<CWindow>*)this);
#ifdef _DEBUG
	m_bModal = true;
#endif //_DEBUG
	int ret = -1;
	HGLOBAL hgbl = _allocBlankDialogTemplate(m_owner.m_x, m_owner.m_y, m_owner.m_cx, m_owner.m_cy);
	if (hgbl)
	{
		ret = DialogBoxIndirect(Application::getInstance()->getAppHInstance(),
			(LPDLGTEMPLATE)hgbl, hWndParent, _PopupDialog::StartDialogProc);
		GlobalFree(hgbl);
	}

	return ret;
}

HWND CPopupHostDialog::_PopupDialog::Create(HWND hWndParent, LPARAM dwInitParam)
{
	ATLASSERT(m_hWnd == NULL);
	_AtlWinModule.AddCreateWndData(&m_thunk.cd, (CDialogImplBaseT<CWindow>*)this);
#ifdef _DEBUG
	m_bModal = false;
#endif //_DEBUG

	HWND hWnd = NULL;
	HGLOBAL hgbl = _allocBlankDialogTemplate(m_owner.m_x, m_owner.m_y, m_owner.m_cx, m_owner.m_cy);
	if (hgbl)
	{
		hWnd = CreateDialogIndirect(Application::getInstance()->getAppHInstance(),
			(LPDLGTEMPLATE)hgbl, hWndParent, _PopupDialog::StartDialogProc);
		GlobalFree(hgbl);
	}

	return hWnd;
}

LRESULT CPopupHostDialog::_PopupDialog::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{	
	SetWindowPos(0, m_owner.m_x, m_owner.m_y, m_owner.m_cx, m_owner.m_cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW);

	if (m_owner.m_center)
	{
		CenterWindow();
	}	

	CEventx* pEvent = new CEventx(EV_DLG_INITDLG, &m_owner, 0);
	m_owner.dispatchEvent(pEvent);
	delete pEvent;

	return 0;
}

LRESULT CPopupHostDialog::_PopupDialog::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
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

	BitBlt(paintdc, 0, 0, rc.right - rc.left, rc.bottom - rc.left, memdc, 0, 0, SRCCOPY);

	RestoreDC(memdc, saveid);

	DeleteObject(hbmp);
	DeleteObject(memdc);

	EndPaint(&ps);

	return 0;
}

LRESULT CPopupHostDialog::_PopupDialog::OnOK(int nID, int nCode, HWND hWnd, BOOL & bHandled)
{
	EndDialog(IDOK);

	return 0;
}

LRESULT CPopupHostDialog::_PopupDialog::OnCancel(int nID, int nCode, HWND hWnd, BOOL & bHandled)
{
	EndDialog(IDCANCEL);

	return 0;
}

CPopupHostDialog::_PopupDialog::_PopupDialog(CPopupHostDialog& owner) : m_owner(owner)
{
}

CPopupHostDialog::_PopupDialog::~_PopupDialog()
{
}

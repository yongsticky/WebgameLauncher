#include "stdafx.h"
#include "WindowMessageDispatcher.h"
#include "Control.h"
#include "HostWindow.h"

using namespace SDUI;

BOOL CWindowMessageDispatcher::ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
{
	bool handled = false;
	int ret = 0;

	switch (uMsg)
	{	
	case WM_CREATE:
	case WM_INITDIALOG:
	case (WM_USER + WM_PAINT):
	case WM_SIZE:
	case WM_MOVE:
	case WM_WINDOWPOSCHANGED:
	case WM_SHOWWINDOW:
	case WM_ACTIVATEAPP:	
	{
		CHostWindow* pThis = dynamic_cast<CHostWindow*>(this);
		CControl* pControl = pThis->getRootControl();
		if (pControl)
		{
			ret = pControl->_firePreorderMessage(uMsg, wParam, lParam, handled);	// 先根
		}	
	}
	break;
	case WM_DESTROY:
	case WM_NCHITTEST:
	case WM_LBUTTONUP:	
	case WM_COMMAND:
	{
		CHostWindow* pThis = dynamic_cast<CHostWindow*>(this);
		CControl* pControl = pThis->getRootControl();
		if (pControl)
		{			
			ret = pControl->_firePosteriorMessage(uMsg, wParam, lParam, handled);	// 后根
		}		
	}
	break;
	case WM_MOUSEHOVER:
	case WM_MOUSELEAVE:
	{
		CHostWindow* pThis = dynamic_cast<CHostWindow*>(this);
		CControl* pControl = pThis->getRootControl();
		if (pControl)
		{			
			ret = pControl->_firePosteriorMessage(uMsg, wParam, lParam, handled);	// 后根			
		}
		handled = false;
	}
	break;
	default:
		break;
	}
		
	if (handled)
	{
		lResult = ret;
		return TRUE;
	}

	return FALSE;
}

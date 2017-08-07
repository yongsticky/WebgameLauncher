#include "stdafx.h"
#include "SimpleDirectUI.h"

#include <GdiPlus.h>  
using namespace Gdiplus;

ULONG_PTR gdiplusToken;

bool SimpleDirectUI_Init(HINSTANCE appInstance, SDUI::Application** ppApp)
{	
	if (!ppApp || *ppApp)
	{
		return false;
	}

	GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::Status ret = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	*ppApp = SDUI::Application::createInstance(appInstance);

	return (ret == Gdiplus::Ok);	
}

void SimpleDirectUI_Uninit()
{
	GdiplusShutdown(gdiplusToken);
}

void doNothing()
{	
	SDUI::CFrameHostWindow x1;
	SDUI::CPopupHostDialog x2;
	SDUI::CWin32ComponentWindow x3;

	SDUI::CLayoutControl c1;
	SDUI::CImageControl c2;
	SDUI::CButtonControl c3;
	SDUI::CTextControl c4;
	SDUI::CWebBrowserControl c5;
	SDUI::CEditControl c6;
		
	SDUI::CQuitApplicationAction h1;
	SDUI::CShellOpenUrlAction h2;
	SDUI::CShowWindowAction h3;
	SDUI::CShowControlAction h4;
	SDUI::CShowComponentAction h5;
	SDUI::CWBNavigateAction h6;
	SDUI::CWBCommandAction h7;
	SDUI::CConditionAction h8;
	SDUI::CSendMessageAction h10;
	SDUI::CCreateTimerAction h11;
	SDUI::CKillTimerAction h12;	

	SDUI::CWin32TrayIcon w1;
	SDUI::CWin32ContextMenu w2;
	SDUI::CWin32MenuItem w3;
}

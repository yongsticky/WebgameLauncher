// Test.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "resource.h"

#include "Test.h"

#include "HotkeyEditControl.h"


#include "Win32Hotkey.h"

#include "DeleteInternetExplorerCache.h"
#include "ShowMessagebox.h"
#include "HotkeyConfigWriter.h"
#include "HotkeyConfigReader.h"
#include "AppConfiger.h"



CAppModule _Module;
SDUI::Application* _app;

BOOL SingletonCheck()
{
	TCHAR szModuleName[MAX_PATH];
	GetModuleFileName(NULL, szModuleName, MAX_PATH);
	TCHAR* p = _tcsrchr(szModuleName, _T('\\'));	
	if (!p)
	{
		return TRUE;
	}

	TCHAR szEventName[MAX_PATH];
	_tcscpy(szEventName, _T("F4293D8E-E05D-4E76-B830-986EC706F735-"));
	_tcscat(szEventName, ++p);	

	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, szEventName);
	if (hEvent)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);
	
	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	if (!SingletonCheck())
	{
		MessageBox(NULL, _T("应用程序已经有一个实例在运行了"), _T("退出"), MB_OK | MB_ICONINFORMATION);
		return 0;
	}

	HRESULT hRes = ::CoInitialize(NULL);
	// If you are running on NT 4.0 or higher you can use the following call instead to 
	// make the EXE free threaded. This means that calls come in on a random RPC thread.
	//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();		// use CAxWindow

	//int nRet = Run(lpstrCmdLine, nCmdShow);

	//CLiveUpdate::getInstance()->start();
	

	CAppConfiger::getInstance();
	
	int ret = -1;
	if (SimpleDirectUI_Init(hInstance, &_app))
	{
		char root[MAX_PATH];
		GetModuleFileNameA(NULL, root, MAX_PATH);
		PathAppendA(root, "..\\..\\");

		if (lpstrCmdLine && _tcslen(lpstrCmdLine) > 0)
		{
			USES_CONVERSION;
			PathAppendA(root, T2A(lpstrCmdLine));
		}

		bool err = false;
		while (1)
		{
			char bitmap[MAX_PATH];
			PathCombineA(bitmap, root, "layout\\bitmap.xml");
			if (!_app->getBitmapLoader()->loadFromXml(bitmap))
			{
				err = true;
				break;
			}

			char layout[MAX_PATH];
			PathCombineA(layout, root, "layout\\layout.xml");
			if (!_app->getLayoutLoader()->loadFromXml(layout))
			{
				err = true;
				break;
			}						

			ret = _app->run();
			

			break;
		}		

		SimpleDirectUI_Uninit();

		if (err)
		{
			MessageBox(NULL, _T("加载配置文件出错，请尝试重新安装应用程序。"), _T("错误"), MB_ICONERROR | MB_OK);
		}		
	}	

	_Module.Term();
	::CoUninitialize();

	return ret;
}

void f()
{
	CHotkeyEditControl c1;

	CWin32Hotkey w1;

	CDeleteInternetExplorerCache a1;
	CShowMessagebox a2;
	CHotkeyConfigWriter a3;
	CHotkeyConfigReader a4;
}
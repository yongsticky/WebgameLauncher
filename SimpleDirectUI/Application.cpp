#include "stdafx.h"
#include "Application.h"

#include "LayoutLoader.h"
#include "BitmapLoader.h"
#include "StringLoader.h"


using namespace SDUI;

Application::Application(HINSTANCE appInstance) : m_appInstance(appInstance)
{
}


Application::~Application()
{
}

int Application::run()
{
	if (CLayoutLoader::getInstance()->startup())
	{
		return _run();
	}

	return false;
}

unsigned int Application::addMessageFilter(_IMessageFilter* filter)
{
	if (filter)
	{
		removeMessageFilter(filter);
		m_filters.push_back(filter);

		return m_filters.size();
	}

	return 0;
}

void Application::removeMessageFilter(_IMessageFilter* filter)
{
	std::vector<_IMessageFilter*>::iterator itr = m_filters.begin();
	while (itr != m_filters.end())
	{
		if (filter == (*itr))
		{
			itr = m_filters.erase(itr);
			continue;
		}

		++itr;
	}
}

CLayoutLoader* Application::getLayoutLoader()
{
	return CLayoutLoader::getInstance();
}

CBitmapLoader* Application::getBitmapLoader()
{
	return CBitmapLoader::getInstance();
}

CStringLoader * SDUI::Application::getStringLoader()
{
	return CStringLoader::getInstance();
}

int Application::_run()
{

	MSG msg;
	for (;;)
	{		
		BOOL bRet = ::GetMessage(&msg, NULL, 0, 0);

		if (bRet == -1)
		{
			ATLTRACE(_T("::GetMessage returned -1 (error)\n"));
			continue;   // error, don't process
		}
		else if (!bRet)
		{
			ATLTRACE(_T("CMessageLoop::Run - exiting\n"));
			break;   // WM_QUIT, exit message loop
		}

		if (!_preTranslateMessage(&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
				
	}
	
	return (int)msg.wParam;	
}

bool Application::_preTranslateMessage(LPMSG lpMsg)
{
	std::vector<_IMessageFilter*>::iterator itr = m_filters.begin();
	while (itr != m_filters.end())
	{
		_IMessageFilter* filter = *itr;
		if (filter)		
		{
			if (filter->preTranslateMessage(lpMsg))
			{
				return true;				
			}			
		}

		++itr;
	}

	return false;
}

Application* Application::_instance = nullptr;
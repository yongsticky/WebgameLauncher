#include "stdafx.h"
#include "DeleteInternetExplorerCache.h"
#include <WinInet.h>

using namespace SDUI;



DYNAMIC_OBJECT_CREATE("DeleteInternetExplorerCache", CDeleteInternetExplorerCache, CObjectx)

CDeleteInternetExplorerCache::CDeleteInternetExplorerCache() : m_sync(true), m_running(false)
{
}


CDeleteInternetExplorerCache::~CDeleteInternetExplorerCache()
{
}

bool CDeleteInternetExplorerCache::createFromXml(CXmlAttribute* attr)
{
	CAction::createFromXml(attr);

	std::string sync;
	if (attr->getAttribute("sync", sync))
	{
		setSync(CXmlAttribute::_stringToBoolean(sync));
	}


	return true;
}

bool CDeleteInternetExplorerCache::onAction(CEventx* event)
{
	if (m_sync)
	{
		_deleteImpl();
	}
	else
	{
		if (m_running)
		{
			return true;
		}

		if (!m_notifyWindow.IsWindow())
		{
			m_notifyWindow.Create(GetDesktopWindow());
		}		

		// 线程执行
		unsigned int threadId = 0;
		if (_beginthreadex(nullptr, 0, _threadProc, this, 0, &threadId) > 0)
		{
			m_running = true;
		}
		
	}

	return true;
}

void CDeleteInternetExplorerCache::setSync(bool sync)
{
	m_sync = sync;
}

void CDeleteInternetExplorerCache::showMessageBox()
{	
	CLayoutLoader* loader = Application::getInstance()->getLayoutLoader();
	CHostWindow* parent = (CHostWindow*)loader->getRoot("wnd.game");
	CHostWindow* pwin = (CHostWindow*)loader->getRoot("dlg.msgbox2");
	if (pwin && parent)
	{
		CTextControl* pTitle = (CTextControl*)pwin->getRootControl()->findChild("msgbox.title");
		if (pTitle)
		{
			pTitle->setText("清理缓存");
		}


		CTextControl* pMessage = (CTextControl*)pwin->getRootControl()->findChild("msgbox.message");
		if (pMessage)
		{
			pMessage->setText("清理缓存成功！");
		}

		pwin->create(parent->getHwnd());
		pwin->setActive(true);
		pwin->show(0, false);		
	}
}

void CDeleteInternetExplorerCache::onComplete(int status)
{	
	//MessageBox(GetDesktopWindow(), _T("缓存清理完成"), _T("清理"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);


	showMessageBox();

	m_running = false;
}

void CDeleteInternetExplorerCache::notifyComplete(int status)
{
	m_notifyWindow.PostMessage(WM_THREAD_NOTIFY, status, 0);
}

int CDeleteInternetExplorerCache::_deleteImpl()
{
	DWORD dwSize = 0;
	FindFirstUrlCacheEntry(nullptr, nullptr, &dwSize);
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		unsigned char* pBuffer = new unsigned char[dwSize];
		LPINTERNET_CACHE_ENTRY_INFO pInfo = reinterpret_cast<LPINTERNET_CACHE_ENTRY_INFO>(pBuffer);
		
		HANDLE hFind = FindFirstUrlCacheEntry(nullptr, pInfo, &dwSize);
		DeleteUrlCacheEntry(pInfo->lpszSourceUrlName);

		while (1)
		{
			if (FindNextUrlCacheEntry(hFind, pInfo, &dwSize))
			{
				DeleteUrlCacheEntry(pInfo->lpszSourceUrlName);
				continue;
			}
			else
			{
				delete[] pBuffer;

				if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				{
					pBuffer = new unsigned char[dwSize];
					pInfo = reinterpret_cast<LPINTERNET_CACHE_ENTRY_INFO>(pBuffer);
					continue;
				}
				else
				{
					break;
				}
			}
		}

		FindCloseUrlCache(hFind);		
	}

	return 0;
}

unsigned int CDeleteInternetExplorerCache::_threadProc(void* param)
{
	_deleteImpl();
	
	CDeleteInternetExplorerCache* pThis = (CDeleteInternetExplorerCache*)param;
	if (pThis)
	{
		pThis->notifyComplete(0);
	}
	
	_endthreadex(0);

	return 0;
}
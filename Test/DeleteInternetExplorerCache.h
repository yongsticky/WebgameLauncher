#pragma once

#define WM_THREAD_NOTIFY 0x402

class CDeleteInternetExplorerCache : public SDUI::CAction
{
public:
	CDeleteInternetExplorerCache();
	virtual ~CDeleteInternetExplorerCache();

	DYNAMIC_OBJECT_DECLARE(CDeleteInternetExplorerCache, SDUI::CObjectx)

	virtual bool createFromXml(SDUI::CXmlAttribute* attr);	
	virtual bool onAction(SDUI::CEventx* event);

	void setSync(bool sync);

protected:
	void showMessageBox();
	void onComplete(int status);
	void notifyComplete(int status);
	static int _deleteImpl();
	static unsigned int __stdcall _threadProc(void* param);

	class _NotifyWindow : public CWindowImpl<_NotifyWindow, CWindow, CWinTraits<WS_POPUP, WS_EX_TOOLWINDOW> >
	{
	public:
		_NotifyWindow() {}
		virtual ~_NotifyWindow() {}

		DECLARE_WND_CLASS(_T("_DeleteInternetExplorerCacheNotifyWindow"))

		BEGIN_MSG_MAP(_NotifyWindow)
			MESSAGE_HANDLER(WM_THREAD_NOTIFY, OnThreadNotify)
		END_MSG_MAP()

		LRESULT OnThreadNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
		{	
			CDeleteInternetExplorerCache* pThis = (CDeleteInternetExplorerCache*)((BYTE*)this - offsetof(CDeleteInternetExplorerCache, m_notifyWindow));			
			
			pThis->onComplete(wParam);

			return TRUE;
		}
	};
	
protected:
	bool m_running;
	bool m_sync;
	
	_NotifyWindow m_notifyWindow;
};


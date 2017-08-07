#pragma once
#include "Control.h"
#include "Application.h"


namespace SDUI
{

	class CWebBrowserEvents;

	class CWebBrowserControl :
		public CControl,
		public _IMessageFilter
	{
	public:
		CWebBrowserControl();
		virtual ~CWebBrowserControl();

		DYNAMIC_OBJECT_DECLARE(CWebBrowserControl, CObjectx)

		virtual bool preTranslateMessage(LPMSG lpMsg);

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual unsigned int addChild(CControl* control);

		virtual void show(bool show);


	public:
		void setPage(const std::string& page);
		void setTransAcc(bool transAcc);
		void setTransRb(const std::string& transRb);
		void setChild(bool child);
		void setDebug(bool debug);

		bool navigate(const std::string& url);
		bool stop();
		bool refresh();

	protected:
		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

		int _onChildMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);
		int _onLinkageMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

		bool _initWebBrowserActiveX();

	protected:
		std::string m_page;
		bool m_transacc;
		
		std::string m_transrb;
		bool m_rb;

		bool m_child;		
		bool m_debug;

		typedef CWinTraits<WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_TOOLWINDOW> _CAcxHostWindowxTraits;
		class _CAcxHostWindow :
			public CWindowImpl<_CAcxHostWindow, CAxWindow, _CAcxHostWindowxTraits>
		{
		public:
			_CAcxHostWindow() {}
			virtual ~_CAcxHostWindow() {}

			BEGIN_MSG_MAP(_CAcxHostWindow)
			END_MSG_MAP()
		};

		_CAcxHostWindow m_acxWindow;

		CComPtr<IWebBrowser2> m_spWebBrowser;
		CComObject<CWebBrowserEvents>* m_pDWebBrowserEventsObj;
	};
};
#pragma once

#include <ExDispid.h>


namespace SDUI
{


	class CControl;
	class CNoScriptErrorAndUIHandler;

	class CWebBrowserEvents :
		public CComObjectRootEx<CComSingleThreadModel>,
		public CComCoClass<CWebBrowserEvents>,
		public IDispEventImpl<1, CWebBrowserEvents, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 0>
	{
	public:
		CWebBrowserEvents();
		virtual ~CWebBrowserEvents();

		DECLARE_PROTECT_FINAL_CONSTRUCT()

		BEGIN_COM_MAP(CWebBrowserEvents)
		END_COM_MAP()

		BEGIN_SINK_MAP(CWebBrowserEvents)
			SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, OnBeforeNavigate2)
			SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_NEWWINDOW3, OnNewWindow3)			
			SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete)
		END_SINK_MAP()


		HRESULT FinalConstruct();

		bool setOwner(CControl* owner);

		void SetDebug(bool debug);

	public:
		void STDMETHODCALLTYPE OnBeforeNavigate2(IDispatch** ppDisp, VARIANT* vUrl, VARIANT* vFlags, VARIANT* vTargetFrameName, VARIANT* vPostData, VARIANT* vHeaders, VARIANT_BOOL* vbCancel);
		void STDMETHODCALLTYPE OnNewWindow3(IDispatch** ppDisp, VARIANT_BOOL* vbCancel, LONG dwFlags, BSTR bstrUrlContext, BSTR bstrUrl);
		void STDMETHODCALLTYPE OnDocumentComplete(IDispatch* pDisp, VARIANT* vUrl);

	private:
		CComObject<CNoScriptErrorAndUIHandler>* m_pHandlerObj;

		CControl* m_owner;

		bool m_debug;
	};


};
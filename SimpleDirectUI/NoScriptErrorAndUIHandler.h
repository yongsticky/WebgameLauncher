#pragma once

namespace SDUI
{



	class CNoScriptErrorAndUIHandler :
		public CComObjectRootEx<CComSingleThreadModel>,
		public CComCoClass<CNoScriptErrorAndUIHandler>,
		public IOleCommandTarget,
		public IDocHostUIHandler
	{
	public:
		CNoScriptErrorAndUIHandler();
		virtual ~CNoScriptErrorAndUIHandler();

		BEGIN_COM_MAP(CNoScriptErrorAndUIHandler)
			COM_INTERFACE_ENTRY(IDocHostUIHandler)
			COM_INTERFACE_ENTRY(IOleCommandTarget)			
		END_COM_MAP()

	public:
		HRESULT SetHandler(IDispatch* pDisp);

	public:
		virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE QueryStatus(
			/* [unique][in] */ __RPC__in_opt const GUID *pguidCmdGroup,
			/* [in] */ ULONG cCmds,
			/* [out][in][size_is] */ __RPC__inout_ecount_full(cCmds) OLECMD prgCmds[],
			/* [unique][out][in] */ __RPC__inout_opt OLECMDTEXT *pCmdText);

		virtual HRESULT STDMETHODCALLTYPE Exec(
			/* [unique][in] */ __RPC__in_opt const GUID *pguidCmdGroup,
			/* [in] */ DWORD nCmdID,
			/* [in] */ DWORD nCmdexecopt,
			/* [unique][in] */ __RPC__in_opt VARIANT *pvaIn,
			/* [unique][out][in] */ __RPC__inout_opt VARIANT *pvaOut);


		virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(
			/* [annotation][in] */
			_In_  DWORD dwID,
			/* [annotation][in] */
			_In_  POINT *ppt,
			/* [annotation][in] */
			_In_  IUnknown *pcmdtReserved,
			/* [annotation][in] */
			_In_  IDispatch *pdispReserved);

		virtual HRESULT STDMETHODCALLTYPE GetHostInfo(
			/* [annotation][out][in] */
			_Inout_  DOCHOSTUIINFO *pInfo);

		virtual HRESULT STDMETHODCALLTYPE ShowUI(
			/* [annotation][in] */
			_In_  DWORD dwID,
			/* [annotation][in] */
			_In_  IOleInPlaceActiveObject *pActiveObject,
			/* [annotation][in] */
			_In_  IOleCommandTarget *pCommandTarget,
			/* [annotation][in] */
			_In_  IOleInPlaceFrame *pFrame,
			/* [annotation][in] */
			_In_  IOleInPlaceUIWindow *pDoc);

		virtual HRESULT STDMETHODCALLTYPE HideUI(void);

		virtual HRESULT STDMETHODCALLTYPE UpdateUI(void);

		virtual HRESULT STDMETHODCALLTYPE EnableModeless(
			/* [in] */ BOOL fEnable);

		virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate(
			/* [in] */ BOOL fActivate);

		virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(
			/* [in] */ BOOL fActivate);

		virtual HRESULT STDMETHODCALLTYPE ResizeBorder(
			/* [annotation][in] */
			_In_  LPCRECT prcBorder,
			/* [annotation][in] */
			_In_  IOleInPlaceUIWindow *pUIWindow,
			/* [annotation][in] */
			_In_  BOOL fRameWindow);

		virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(
			/* [in] */ LPMSG lpMsg,
			/* [in] */ const GUID *pguidCmdGroup,
			/* [in] */ DWORD nCmdID);

		virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath(
			/* [annotation][out] */
			_Out_  LPOLESTR *pchKey,
			/* [in] */ DWORD dw);

		virtual HRESULT STDMETHODCALLTYPE GetDropTarget(
			/* [annotation][in] */
			_In_  IDropTarget *pDropTarget,
			/* [annotation][out] */
			_Outptr_  IDropTarget **ppDropTarget);

		virtual HRESULT STDMETHODCALLTYPE GetExternal(
			/* [annotation][out] */
			_Outptr_result_maybenull_  IDispatch **ppDispatch);

		virtual HRESULT STDMETHODCALLTYPE TranslateUrl(
			/* [in] */ DWORD dwTranslate,
			/* [annotation][in] */
			_In_  LPWSTR pchURLIn,
			/* [annotation][out] */
			_Outptr_  LPWSTR *ppchURLOut);

		virtual HRESULT STDMETHODCALLTYPE FilterDataObject(
			/* [annotation][in] */
			_In_  IDataObject *pDO,
			/* [annotation][out] */
			_Outptr_result_maybenull_  IDataObject **ppDORet);

	private:
		CComQIPtr<IOleCommandTarget> m_spDefaultOleCommandTarget;
		CComQIPtr<IDocHostUIHandler> m_spDefaultDocHostUIHandler;

	};



};
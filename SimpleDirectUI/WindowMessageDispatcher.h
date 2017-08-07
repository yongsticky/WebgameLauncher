#pragma once

namespace SDUI
{


	class CWindowMessageDispatcher : public CMessageMap
	{
	protected:
		CWindowMessageDispatcher() {}

	public:
		virtual ~CWindowMessageDispatcher() {}

		virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0);
	};


};
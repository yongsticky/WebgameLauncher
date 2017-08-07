#pragma once

#include "Win32Component.h"
#include <string>

namespace SDUI
{


	class CWin32TrayIcon : public CWin32Component
	{
	public:
		CWin32TrayIcon();
		virtual ~CWin32TrayIcon();

		DYNAMIC_OBJECT_DECLARE(CWin32TrayIcon, CObjectx)

		virtual bool createFromXml(CXmlAttribute* attr);

		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

		virtual void show();
		virtual void hide();
		virtual void toggle(int cmd, int retcode);

		void setHIcon(HICON hicon);
		void setTip(const std::string& tip);

	private:
		HICON m_hicon;

		std::string m_tip;

		bool m_showed;
	};



};
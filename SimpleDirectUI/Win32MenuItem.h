#pragma once
#include "Win32Component.h"
#include <string>

namespace SDUI
{



	class CWin32MenuItem : public CWin32Component
	{
	public:
		CWin32MenuItem();
		virtual ~CWin32MenuItem();

		DYNAMIC_OBJECT_DECLARE(CWin32MenuItem, CObjectx)

			virtual bool createFromXml(CXmlAttribute* attr);
		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

		void setSeparator(bool separator);
		bool getSeparator();
		void setIndex(int index);
		int getIndex();
		void setText(const std::string& text);
		std::string getText();

	protected:
		bool m_separator;
		int m_index;
		std::string m_text;
	};



};
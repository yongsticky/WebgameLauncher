#include "stdafx.h"
#include "HotkeyEditControl.h"


using namespace SDUI;

DYNAMIC_OBJECT_CREATE("HotkeyEdit", CHotkeyEditControl, CObjectx)

WNDPROC CHotkeyEditControl::s_defWndProc = NULL;

CHotkeyEditControl::CHotkeyEditControl() : m_setOK(false)
{
}


CHotkeyEditControl::~CHotkeyEditControl()
{
}

bool CHotkeyEditControl::createFromXml(CXmlAttribute* attr)
{
	CEditControl::createFromXml(attr);

	return true;
}

std::string CHotkeyEditControl::fromData()
{
	std::string ret;

	if (m_keySet.m_ctrl)
	{
		ret += "ctrl_";
	}

	if (m_keySet.m_alt)
	{
		ret += "alt_";
	}

	if (m_keySet.m_shift)
	{
		ret += "shift_";
	}

	char c[8];
	_itoa_s(m_keySet.m_char, c, 10);
		
	ret += c;

	return ret;
}

void CHotkeyEditControl::updateTo(const std::string& data)
{
	char buf[260];
	strcpy(buf, data.c_str());
	const char* p = strtok(buf, "_");

	while (p)
	{
		if (_strcmpi(p, "ctrl") == 0)
		{
			m_keySet.m_ctrl = true;
		}
		else if (_strcmpi(p, "alt") == 0)
		{
			m_keySet.m_alt = true;
		}
		else if (_strcmpi(p, "shift") == 0)
		{
			m_keySet.m_shift = true;
		}
		else
		{
			long c = _atoi64(p);
			m_keySet.m_char = c;
		}

		p = strtok(nullptr, "_");
	}

	updateUI();
}

int CHotkeyEditControl::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	LRESULT lr = CEditControl::onMessage(message, wparam, lparam, handled);

	if (message == WindowCreated || message == DialogInit)
	{			
		m_edit.SetWindowLong(GWL_USERDATA, (LONG)this);
		s_defWndProc = (WNDPROC)m_edit.SetWindowLong(GWL_WNDPROC, (LONG)HotkeyEditWndProc);
	}

	return lr;
}

LRESULT CHotkeyEditControl::HotkeyEditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN)
	{
		CHotkeyEditControl* pThis = (CHotkeyEditControl*)GetWindowLong(hWnd, GWL_USERDATA);
		if (pThis->onKeyDown(uMsg, wParam, lParam))
		{
			return 0;
		}
	}
	else if (uMsg == WM_KEYUP || uMsg == WM_SYSKEYUP)
	{
		CHotkeyEditControl* pThis = (CHotkeyEditControl*)GetWindowLong(hWnd, GWL_USERDATA);
		if (pThis->onKeyUp(uMsg, wParam, lParam))
		{
			return 0;
		}

	}
	else if (uMsg == WM_CHAR)
	{
		return 0;
	}

	return  CallWindowProc(s_defWndProc, hWnd, uMsg, wParam, lParam);
}

bool CHotkeyEditControl::onKeyDown(unsigned int message, unsigned int wparam, int lparam)
{	
	if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN)
	{
		ATLTRACE(_T("CHotkeyEditControl::onKeyDown message=%s wparam=0x%0x, lparam=0x%0x \n"), 
			message==WM_KEYDOWN?_T("WM_KEYDOWN"):_T("WM_SYSKEYDOWN"), wparam, lparam);

		if (m_keySet.repeatPressUpdate(wparam))
		{
			if (m_keySet.keyOk())
			{
				m_keySet.keyReset();
			}

			m_keySet.keyChanged(wparam, true);			

			updateUI();
		}		
	}
	
	return true;
}

bool CHotkeyEditControl::onKeyUp(unsigned int message, unsigned int wparam, int lparam)
{
	if (message == WM_KEYUP || message == WM_SYSKEYUP)
	{
		ATLTRACE(_T("CHotkeyEditControl::onKeyUp message=%s wparam=0x%0x, lparam=0x%0x \n"), 
			message==WM_KEYUP?_T("WM_KEYUP"):_T("WM_SYSKEYUP"), wparam, lparam);

		m_keySet.repeatPressUpdate(wparam, false);
		
		if (!m_keySet.keyOk())
		{
			m_keySet.keyChanged(wparam, false);

			updateUI();
		}		
	}
	
	return true;
}

void CHotkeyEditControl::updateUI()
{
	USES_CONVERSION;
	m_edit.SetWindowText(A2T(m_keySet.keyResult().c_str()));
}


void CKeySet::keyChanged(unsigned int code, bool pressed)
{	
	if (code == VK_CONTROL)
	{			
		m_ctrl = pressed;
	}
	else if (code == VK_SHIFT)
	{
		m_shift = pressed;
	}
	else if (code == VK_MENU)
	{
		m_alt = pressed;
	}
	else
	{		
		m_char = pressed ? code:0;		
	}	
}

void CKeySet::keyReset()
{	
	m_ctrl = m_alt = m_shift = false;
	m_char = 0;
}

std::string CKeySet::keyResult()
{

	std::string s;

	if (m_ctrl)
	{
		s += "CTRL + ";
	}

	if (m_alt)
	{
		s += "ALT + ";
	}	

	if (m_shift)
	{
		s += "SHIFT + ";
	}

	if (m_char)
	{
		s += codeToChar(m_char);
	}

	return s;
}

std::string CKeySet::codeToChar(unsigned int code)
{
	std::string s;
	if (code >= 0x30 && code <= 0x5A)
	{
		s = (char)code;
	}
	else if (code >= VK_F1 && code <= VK_F12)
	{
		char f[8];
		sprintf(f, "F%d", code - VK_F1 + 1);
		s = f;
	}

	return s;
}

bool CKeySet::keyOk()
{
	return m_char > 0;
}

bool CKeySet::repeatPressUpdate(unsigned int code, bool add)
{
	std::set<unsigned int>::iterator itr = m_repeat.find(code);

	if (add)
	{
		if (itr != m_repeat.end())
		{
			return false;
		}

		m_repeat.insert(code);
	}
	else
	{		
		if (itr != m_repeat.end())
		{
			m_repeat.erase(itr);
		}
	}

	return true;
}
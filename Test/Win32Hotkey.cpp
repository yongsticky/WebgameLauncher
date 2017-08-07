#include "stdafx.h"
#include "Win32Hotkey.h"
#include "Eventx.h"

#include "AppConfiger.h"

using namespace SDUI;

DYNAMIC_OBJECT_CREATE("Win32Hotkey", CWin32Hotkey, CObjectx)

CWin32Hotkey::CWin32Hotkey() : m_hotkeyId(-1), m_times(0), m_mod(0), m_char(0)
{
}


CWin32Hotkey::~CWin32Hotkey()
{
}

bool CWin32Hotkey::createFromXml(CXmlAttribute * attr)
{
	CWin32Component::createFromXml(attr);

	std::string group;
	if (attr->getAttribute("config-group", group))
	{
		setGroup(group);
	}

	std::string key;
	if (attr->getAttribute("config-key", key))
	{
		setKey(key);
	}

	return true;
}

int CWin32Hotkey::onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled)
{
	int ret = CWin32Component::onMessage(message, wparam, lparam, handled);
	if (message == WM_CREATE || message == 2001)
	{			
		registerHotkey();
	}
	else if (message == WM_HOTKEY)
	{
		if (wparam == m_hotkeyId)
		{
			++m_times;

			if (m_times % 2 == 1)
			{
				CEventx* event = new CEventx(201, this, 0);
				dispatchEvent(event);
				delete event;
			}
			else
			{
				CEventx* event = new CEventx(202, this, 0);
				dispatchEvent(event);
				delete event;
			}			
		}
	}

	return ret;
}

void CWin32Hotkey::setVerify(const std::string& verify)
{
	m_verify = verify;
}

void CWin32Hotkey::setGroup(const std::string& group)
{
	m_group = group;
}

void CWin32Hotkey::setKey(const std::string& key)
{
	m_key = key;
}

bool CWin32Hotkey::parseConfigString(const std::string& s)
{
	if (s.empty())
	{
		return false;
	}

	char buf[260];
	strcpy(buf, s.c_str());
	const char* p = strtok(buf, "_");

	while (p)
	{
		if (_strcmpi(p, "ctrl") == 0)
		{
			m_mod |= MOD_CONTROL;
		}
		else if (_strcmpi(p, "alt") == 0)
		{
			m_mod |= MOD_ALT;
		}
		else if (_strcmpi(p, "shift") == 0)
		{
			m_mod |= MOD_SHIFT;
		}
		else
		{
			long c = _atoi64(p);
			m_char = c;
		}

		p = strtok(nullptr, "_");
	}

	return true;
}

void CWin32Hotkey::registerHotkey()
{
	if (m_hotkeyId != -1)
	{
		UnregisterHotKey(m_owner->getHwnd(), m_hotkeyId);
		m_hotkeyId = -1;
	}

	std::string k = CAppConfiger::getInstance()->read(m_group, m_key, "");
	if (parseConfigString(k))
	{
		USES_CONVERSION;
		m_hotkeyId = GlobalAddAtom(CA2T(m_verify.c_str()));

		RegisterHotKey(m_owner->getHwnd(), m_hotkeyId, m_mod, m_char);
	}
}

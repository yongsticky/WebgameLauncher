#include "stdafx.h"
#include "AppConfiger.h"
#include "Shlobj.h"


CAppConfiger* CAppConfiger::_instance = nullptr;

CAppConfiger::CAppConfiger()
{
}


CAppConfiger::~CAppConfiger()
{
}

void CAppConfiger::write(const std::string & group, const std::string & key, const std::string & value)
{
	if (!m_profile.empty())
	{
		WritePrivateProfileStringA(group.c_str(), key.c_str(), value.c_str(), m_profile.c_str());
	}	
}

std::string CAppConfiger::read(const std::string& group, const std::string& key, const std::string& default)
{
	if (!m_profile.empty())
	{
		char ret[260];
		DWORD dw = GetPrivateProfileStringA(group.c_str(), key.c_str(), default.c_str(), ret, 260, m_profile.c_str());
		return std::string(ret);
	}

	return std::string();
}

void CAppConfiger::init()
{
	TCHAR szBuffer[MAX_PATH];

	if (SHGetSpecialFolderPath(0, szBuffer, CSIDL_APPDATA, 0))
	{
		PathAppend(szBuffer, _T("172le"));
		::CreateDirectory(szBuffer, 0);	
		PathAppend(szBuffer, _T("conf.dat"));		
		
		USES_CONVERSION;
		m_profile = CT2A(szBuffer);
	}	
	else
	{
		ATLASSERT(FALSE);
	}
}

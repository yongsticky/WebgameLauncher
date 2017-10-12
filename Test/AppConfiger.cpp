#include "stdafx.h"
#include "AppConfiger.h"


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

void CAppConfiger::write(const std::string& group, const std::string& key, int value)
{
	char buf[16];
	_itoa(value, buf, 10);
	write(group, key, buf);
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

int CAppConfiger::read(const std::string & group, const std::string & key, int default)
{
	std::string ret = read(group, key, "");
	if (ret.empty())
	{
		return default;
	}

	return atoi(ret.c_str());
}

void CAppConfiger::init()
{	
	char szConf[MAX_PATH];
	::GetModuleFileNameA(NULL, szConf, MAX_PATH);
	::PathAppendA(szConf, "..\\..\\conf.dat");		

	m_profile = szConf;	
}

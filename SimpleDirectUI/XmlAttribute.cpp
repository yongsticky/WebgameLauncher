#include "stdafx.h"
#include "XmlAttribute.h"
#include "tinyxml.h"

using namespace SDUI;


CXmlAttribute::CXmlAttribute()
{
}

CXmlAttribute::~CXmlAttribute()
{
}

bool CXmlAttribute::fromXmlElement(TiXmlElement* element)
{	
	return fromXmlElement(element, NULL);
}

bool CXmlAttribute::fromXmlElement(TiXmlElement* element, IXmlAttributeInsertFilter* filter)
{
	if (element)
	{
		TiXmlAttribute* pAttr = element->FirstAttribute();
		while (pAttr)
		{
			const char* name = pAttr->Name();
			const char* value = pAttr->Value();
			if (name && value)
			{
				std::string v;
				_utf8ToAnsi(value, v);

				if (filter)
				{
					std::string _name(name);
					std::string _value(v);
					if (filter->beforeInsert(_name, _value))
					{
						m_attrs[_name] = _value.c_str();
					}
					
				}
				else
				{
					m_attrs[name] = v;
				}
				
			}

			pAttr = pAttr->Next();
		}

		return true;
	}

	return false;
}

bool SDUI::CXmlAttribute::fromXmlAttribute(CXmlAttribute* attr, const char* prefix/* = nullptr */)
{
	if (!attr)
	{
		return false;
	}

	int len = 0;
	if (prefix == nullptr || (len = strlen(prefix)) == 0)
	{
		m_attrs.insert(attr->m_attrs.begin(), attr->m_attrs.end());
		return true;
	}
		
	std::map <std::string, std::string>::iterator itr = attr->m_attrs.begin();
	while (itr != attr->m_attrs.end())
	{
		std::string key = itr->first;
		if (key.find(prefix, 0) == 0)
		{
			m_attrs[key.substr(len, key.size()-len)] = itr->second;
		}

		++itr;
	}

	return true;	
}

bool CXmlAttribute::getAttribute(const std::string& name, std::string& value)
{
	std::map<std::string, std::string>::iterator itr = m_attrs.find(name);
	if (itr != m_attrs.end())
	{
		value = itr->second;
		return true;
	}

	return false;
}

unsigned int CXmlAttribute::_stringToArray(const std::string& str, std::vector<std::string>& vec)
{
	vec.clear();

	char buf[256];
	strcpy(buf, str.c_str());

	char* p = strtok(buf, ",");
	while (p)
	{
		vec.push_back(p);
		p = strtok(nullptr, ",");
	}

	return vec.size();
}

int CXmlAttribute::_stringToInt(const std::string& str)
{
	return atoi(str.c_str());
}

void CXmlAttribute::_stringToXY(const std::string& str, long& x, long& y)
{
	char buf[64];
	strcpy(buf, str.c_str());

	char* px = strtok(buf, ",");
	if (px)
	{
		char* py = strtok(NULL, ",");
		if (py)
		{
			x = atoi(px);
			y = atoi(py);
		}
	}
}

void CXmlAttribute::_stringToXYZ(const std::string& str, long& x, long& y, long& z)
{
	char buf[64];
	strcpy(buf, str.c_str());

	char* px = strtok(buf, ",");
	if (px)
	{
		char* py = strtok(NULL, ",");
		if (py)
		{
			char* pz = strtok(NULL, ",");
			if (pz)
			{
				x = atoi(px);
				y = atoi(py);
				z = atoi(pz);
			}			
		}
	}
}

bool CXmlAttribute::_stringToBoolean(const std::string& str)
{
	return str.compare("true") ? false : true;
}

bool CXmlAttribute::_setAttribute(const char* name, const char* value)
{
	ATLASSERT(name && value);
	if (name && value)
	{
		std::string v;
		_utf8ToAnsi(value, v);
		m_attrs[name] = v;

		return true;
	}

	return false;
}

bool CXmlAttribute::_utf8ToAnsi(const char* utf8, std::string& ansi)
{
	int ucsLength = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	
	// utf8 -> unicode
	wchar_t* ucsBuf = new wchar_t[ucsLength+1];
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, ucsBuf, ucsLength);
	
	// unicode -> ansi	
	int ansiLength = WideCharToMultiByte(CP_ACP, 0, ucsBuf, -1, NULL, 0, NULL, NULL);
	char* ansiBuf = new char[ansiLength + 1];
	memset((void*)ansiBuf, 0, ansiLength + 1);
	WideCharToMultiByte(CP_ACP, 0, ucsBuf, -1, ansiBuf, ansiLength, NULL, NULL);
	
	ansi = ansiBuf;

	delete[] ucsBuf;
	delete[] ansiBuf;

	return true;
}

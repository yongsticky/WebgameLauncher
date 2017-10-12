#include "stdafx.h"
#include "StringLoader.h"
#include "tinyxml.h"
#include "XmlAttribute.h"

using namespace SDUI;

CStringLoader* CStringLoader::s_loader = NULL;


CStringLoader::CStringLoader()
{
}


CStringLoader::~CStringLoader()
{
}

bool CStringLoader::loadFromXml(const char* xmlFile)
{
	ATLASSERT(xmlFile);

	m_pXmlDoc = new TiXmlDocument();


	ATLTRACE("CStringLoader::loadFromXml - xmlFile=%s\n", xmlFile);
	if (!m_pXmlDoc->LoadFile(xmlFile))
	{
		ATLASSERT(FALSE);
		return false;
	}
	
	return	_parseAndLoad();
}

std::string CStringLoader::getString(const char* id)
{
	if (id)
	{
		std::map<std::string, std::string>::iterator itr = m_strings.find(id);
		if (itr != m_strings.end())
		{
			return itr->second;
		}
	}

	return std::string("");
}

std::string CStringLoader::expandString(const char* str)
{

	ATLTRACE("CStringLoader::expandString - str=%s\n", str ? str:"NULL");
	std::string ret = _expand(str);
	ATLTRACE("CStringLoader::expandString - expaned=%s\n", ret.c_str());

	return _expand(str);
}

bool CStringLoader::_parseAndLoad()
{
	ATLASSERT(m_pXmlDoc);

	TiXmlElement* pRoot = m_pXmlDoc->RootElement();
	ATLASSERT(pRoot);
	if (!pRoot)
	{
		return false;
	}

	// root value is 'StringRoot'£¿
	std::string rootName = pRoot->Value();
	if (rootName.compare("StringRoot") != 0)
	{
		return false;
	}
		
	TiXmlElement* pElement = pRoot->FirstChildElement();

	while (pElement)
	{
		_load(pElement);

		pElement = pElement->NextSiblingElement();
	}

	return true;
}

int CStringLoader::_load(TiXmlElement* element)
{
	CXmlAttribute attr;
	attr.fromXmlElement(element);

	std::string id, value;
	if (attr.getAttribute("id", id) && attr.getAttribute("value", value))
	{
		std::string expand;
		if (!attr.getAttribute("expand", expand) || CXmlAttribute::_stringToBoolean(expand))
		{
			value = _expand(value.c_str());
		}
		
		m_strings.insert(make_pair(id, value));

		return 1;
	}

	return 0;
}

std::string CStringLoader::_expand(const char* str)
{	
	std::string ret("");
	if (!str)
	{
		return ret;
	}

	int len = strlen(str);

	const char* p = str;
	const char *q = 0;
	const char* r = 0;
	while (p - str < len)
	{
		q = strstr(p, "${");
		if (q)
		{
			if (q - p > 0)
			{
				ret += string(p, q - p);
			}
			
			q += 2;
		}
		else
		{
			ret += p;
			break;
		}
				
		r = strstr(q, "}");
		if (r)
		{
			std::string va = std::string(q, r - q);
			
			ret += getString(va.c_str());			

			p = r+1;
		}
		else
		{
			ret += q-2;
			break;
		}
	}

	return ret;
}

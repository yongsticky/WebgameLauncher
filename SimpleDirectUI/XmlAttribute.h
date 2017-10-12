#pragma once

#include <map>
#include <vector>
#include <string>

#include "IXmlAttributeInsertFilter.h"

class TiXmlElement;

namespace SDUI
{

	class CStringLoader;

	class CXmlAttribute
	{
	public:
		CXmlAttribute();		
		~CXmlAttribute();

		bool fromXmlElement(TiXmlElement* element);
		bool fromXmlElement(TiXmlElement* element, IXmlAttributeInsertFilter* filter);
		bool fromXmlAttribute(CXmlAttribute* attr, const char* prefix = nullptr);
		bool getAttribute(const std::string& name, std::string& value);

		static unsigned int _stringToArray(const std::string& str, std::vector<std::string>& vec);
		static int _stringToInt(const std::string& str);
		static void _stringToXY(const std::string& str, long& x, long& y);
		static void _stringToXYZ(const std::string& str, long& x, long& y, long& z);
		static bool _stringToBoolean(const std::string& str);

	private:
		bool _setAttribute(const char* name, const char* value);
		static bool _utf8ToAnsi(const char* utf8, std::string& ansi);

	private:
		std::map<std::string, std::string> m_attrs;
	};


};
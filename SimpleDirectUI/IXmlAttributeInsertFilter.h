#pragma once

#include<string>

interface IXmlAttributeInsertFilter
{
	virtual bool beforeInsert(std::string& name, std::string& value) = 0;
};


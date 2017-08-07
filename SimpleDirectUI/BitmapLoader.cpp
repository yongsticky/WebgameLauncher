#include "stdafx.h"
#include "BitmapLoader.h"
#include "tinyxml.h"
#include "XmlAttribute.h"

using namespace SDUI;

CBitmapLoader* CBitmapLoader::s_loader = nullptr;

CBitmapLoader::CBitmapLoader()
{
}


CBitmapLoader::~CBitmapLoader()
{
}

bool CBitmapLoader::loadFromXml(const char* xmlFile)
{
	ATLASSERT(xmlFile);

	m_pXmlDoc = new TiXmlDocument();


	ATLTRACE("CBitmapLoader::loadFromXml - xmlFile=%s\n", xmlFile);
	if (!m_pXmlDoc->LoadFile(xmlFile))
	{
		ATLASSERT(FALSE);		
		return false;
	}
	
	m_xmlFile = xmlFile;

	if (_parseAndLoad())
	{
		return true;
	}	

	return false;
}

Gdiplus::Bitmap* CBitmapLoader::getBitmap(const char* id)
{
	if (id)
	{
		std::map<std::string, Gdiplus::Bitmap*>::iterator itr = m_bitmaps.find(id);
		if (itr != m_bitmaps.end())
		{
			return itr->second;
		}
	}	

	return nullptr;
}

const std::string& SDUI::CBitmapLoader::getImageDir()
{	
	return m_imageDir;
}

bool CBitmapLoader::_parseAndLoad()
{
	ATLASSERT(m_pXmlDoc);

	TiXmlElement* pRoot = m_pXmlDoc->RootElement();
	ATLASSERT(pRoot);
	if (!pRoot)
	{
		return false;
	}

	// root value is 'BitmapRoot'£¿
	std::string rootName = pRoot->Value();
	if (rootName.compare("BitmapRoot") != 0)
	{
		return false;
	}

	std::string rootdir("rootdir");
	TiXmlAttribute* pAttr = pRoot->FirstAttribute();
	while (true)
	{		
		if (!pAttr)
		{
			return false;
		}

		if (rootdir.compare(pAttr->Name()) == 0)
		{			
			char imageDir[MAX_PATH];
			::PathCombineA(imageDir, m_xmlFile.c_str(), "..");
			::PathAppendA(imageDir, pAttr->Value());
			m_imageDir = imageDir;

			break;
		}

		pAttr = pAttr->Next();
	}
	

	TiXmlElement* pElement = pRoot->FirstChildElement();

	while (pElement)
	{	
		_load(pElement);

		pElement = pElement->NextSiblingElement();
	}

	return true;
}

int CBitmapLoader::_load(TiXmlElement* element)
{
	if (!element)
	{
		return 0;
	}

	CXmlAttribute attr;
	attr.fromXmlElement(element);

	std::string file;
	if (!attr.getAttribute("file", file))
	{
		return 0;
	}

	if (std::string("BitmapList").compare(element->Value()) == 0)
	{		
		Gdiplus::Bitmap* bitmaplist = _loadBitmap(file.c_str());
		if (bitmaplist)
		{
			TiXmlElement* child = element->FirstChildElement();
			while (child)
			{
				CXmlAttribute attr;
				attr.fromXmlElement(child);

				std::string pos, size, id;
				if (attr.getAttribute("pos", pos) && attr.getAttribute("size", size) && attr.getAttribute("id", id))
				{
					long x, y;
					CXmlAttribute::_stringToXY(pos, x, y);

					long cx, cy;
					CXmlAttribute::_stringToXY(size, cx, cy);

					
					Gdiplus::Bitmap* bitmap = bitmaplist->Clone(x, y, cx, cy, PixelFormatDontCare);
					if (bitmap)
					{
						m_bitmaps.insert(make_pair(id, bitmap));
					}
					else
					{
						ATLTRACE("CBitmapLoader load bitmap [%s] from bitmaplist failed.\n", id.c_str());
					}
				}				

				child = child->NextSiblingElement();
			}

			_freeBitmap(bitmaplist);
		}
	}
	else if (std::string("Bitmap").compare(element->Value()) == 0)
	{
		std::string id;
		if (attr.getAttribute("id", id))
		{
			Gdiplus::Bitmap* bitmap = _loadBitmap(file.c_str());
			if (bitmap)
			{
				m_bitmaps.insert(make_pair(id, bitmap));
			}
		}
	}
	else
	{
		ATLASSERT(FALSE);
		return 0;
	}

	return 1;
}

Gdiplus::Bitmap* CBitmapLoader::_loadBitmap(const char* file)
{		
	char fn[MAX_PATH];
	::PathCombineA(fn, m_imageDir.c_str(), file);

	USES_CONVERSION;
	return Gdiplus::Bitmap::FromFile(A2CW(fn));		
}

void CBitmapLoader::_freeBitmap(Gdiplus::Bitmap* bitmap)
{
	if (bitmap)
	{
		delete bitmap;
	}		
}

#pragma once

#include <gdiplus.h>
#include <map>
#include <string>

class TiXmlDocument;
class TiXmlElement;

namespace SDUI
{
	

	class CBitmapLoader
	{
		CBitmapLoader();
	public:
		~CBitmapLoader();

		static CBitmapLoader* getInstance()
		{
			if (!s_loader)
			{
				s_loader = new CBitmapLoader();
			}

			return s_loader;
		}


	public:
		bool loadFromXml(const char* xmlFile);

		Gdiplus::Bitmap* getBitmap(const char* id);

		const std::string& getImageDir();


	protected:
		bool _parseAndLoad();
		int _load(TiXmlElement* element);

		Gdiplus::Bitmap* _loadBitmap(const char* file);
		void _freeBitmap(Gdiplus::Bitmap* bitmap);


	private:
		std::map<std::string, Gdiplus::Bitmap*> m_bitmaps;
		
		TiXmlDocument* m_pXmlDoc;

		std::string m_xmlFile;
		std::string m_imageDir;

		static CBitmapLoader* s_loader;
	};



};
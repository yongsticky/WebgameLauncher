#pragma once



#include <map>
#include <string>

class TiXmlDocument;
class TiXmlElement;




namespace SDUI
{
	class CStringLoader
	{
		CStringLoader();
	public:		
		~CStringLoader();


		static CStringLoader* getInstance()
		{
			if (!s_loader)
			{
				s_loader = new CStringLoader();
			}

			return s_loader;
		}


		bool loadFromXml(const char* xmlFile);
		std::string getString(const char* id);
		std::string expandString(const char* str);
		

	protected:
		bool _parseAndLoad();
		int _load(TiXmlElement* element);
		std::string _expand(const char* str);

	private:
		static CStringLoader* s_loader;

		TiXmlDocument* m_pXmlDoc;

		std::map<std::string, std::string> m_strings;
	};

}
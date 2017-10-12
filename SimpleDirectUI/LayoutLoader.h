#pragma once

class TiXmlDocument;
class TiXmlElement;


#include "IXmlAttributeInsertFilter.h"

namespace SDUI
{



	class CObjectx;
	class CHostWindow;
	class CControl;
	class CXmlAttribute;

	class CLayoutLoader : public IXmlAttributeInsertFilter
	{
		CLayoutLoader();
	public:
		~CLayoutLoader();

		static CLayoutLoader* getInstance()
		{
			if (!s_layout)
			{
				s_layout = new CLayoutLoader();
			}

			return s_layout;
		}


		bool beforeInsert(std::string& name, std::string& value);

	public:
		bool loadFromXml(const char* xmlFile);
		bool startup();
		void cleanup();

		CObjectx* getRoot(const char* id);

		const std::string& getXmlFile();

	private:
		bool _parseAndCreate();
		int _do(TiXmlElement* root, CObjectx** ppv);

	private:
		TiXmlDocument* m_pXmlDoc;

		std::string m_xmlFile;

		std::vector<CObjectx*> m_root;

		static CLayoutLoader* s_layout;
	};


};
#pragma once

#include <map>
#include <string>


namespace SDUI
{


	class CObjectx;

	template <class T>
	class CObjectxCreator
	{
		CObjectxCreator() {}

	public:
		~CObjectxCreator() {}

		static CObjectxCreator& getInstance()
		{
			static CObjectxCreator _instance;
			return _instance;
		}

		typedef bool(__stdcall *FnCreateObjetx)(T** ppObj);

		void registerObjectxCreateFunction(const char* className, FnCreateObjetx fn)
		{
			sm_objetxFns[className] = fn;
		}

		bool createInstance(const char* className, T** ppObj)
		{
			std::map<std::string, FnCreateObjetx>::iterator itr = sm_objetxFns.find(className);
			if (itr != sm_objetxFns.end())
			{
				FnCreateObjetx fn = itr->second;
				if (fn)
				{
					return fn(ppObj);
				}
			}


			ATLASSERT(FALSE);

			return false;
		}
		

	private:
		std::map<std::string, FnCreateObjetx> sm_objetxFns;
	};



#define DYNAMIC_OBJECT_DECLARE(theClass, baseClass) \
	static bool __stdcall createInstance(baseClass** ppObj) \
	{ \
		*ppObj = new theClass(); \
		return true; \
	}


#define DYNAMIC_OBJECT_CREATE(className, theClass, baseClass) \
	class theClass##CreateHelper \
		{ \
		public: \
			theClass##CreateHelper::theClass##CreateHelper() \
			{ \
				CObjectxCreator<baseClass>::getInstance().registerObjectxCreateFunction(className, theClass::createInstance); \
			} \
	}; \
	theClass##CreateHelper _helper;

};
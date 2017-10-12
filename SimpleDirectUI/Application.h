#pragma once

#include <vector>

namespace SDUI
{
	class _IMessageFilter
	{
	public:
		virtual bool preTranslateMessage(LPMSG lpMsg) = 0;
	};

		
	class CLayoutLoader;
	class CBitmapLoader;
	class CStringLoader;


	class Application
	{
		Application(HINSTANCE appInstance);
	public:
		~Application();

		static Application* createInstance(HINSTANCE appInstance)
		{
			if (!_instance)
			{
				_instance = new Application(appInstance);
			}

			return _instance;
		}

		static Application* getInstance()
		{
			ATLASSERT(_instance);

			return _instance;
		}

		HINSTANCE getAppHInstance() { return m_appInstance; }

		int run();
		unsigned int addMessageFilter(_IMessageFilter* filter);
		void removeMessageFilter(_IMessageFilter* filter);
				
		CLayoutLoader* getLayoutLoader();
		CBitmapLoader* getBitmapLoader();
		CStringLoader* getStringLoader();

	protected:
		int _run();
		bool _preTranslateMessage(LPMSG lpMsg);

	private:
		static Application* _instance;
		HINSTANCE m_appInstance;

		std::vector<_IMessageFilter*> m_filters;
	};


};
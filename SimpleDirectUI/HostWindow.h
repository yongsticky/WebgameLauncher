#pragma once

#include "Objectx.h"
#include "EventxDispatch.h"

namespace SDUI
{



	class CControl;
	class CLayoutLoader;
	class CWin32Component;
	class CHostWindow :
		public CObjectx,
		public CEventxDispatch
	{
		friend class CLayoutLoader;

	public:
		CHostWindow();
		virtual ~CHostWindow();

		virtual bool createFromXml(CXmlAttribute* attr);

		virtual HWND getHwnd() = 0;

		virtual HWND create(HWND hwndParent = nullptr);		

		virtual int show(int cmd, bool forcetop) = 0;
		virtual void hide(int retcode) = 0;
		virtual void toggle(int cmd, int retcode);

		virtual bool invalidate();

		virtual int getClassType();		
		virtual bool addRootControl(CControl* root);
		virtual CControl* getRootControl();
		virtual CControl* findControl(const char* path);
		virtual bool addWin32Component(CWin32Component* component);
		virtual CWin32Component* getWin32Component(const char* componentid);

		CControl* getLastHoverControl();
		void setLastHoverControl(CControl* lastHover);

	public:
		void setId(const std::string& id);
		std::string getId();
		void setPos(int x, int y);
		void setSize(int cx, int cy);
		void setMinSize(int cx, int cy);
		void setCenter(bool center);
		void setVisible(bool visible);		
		void setActive(bool active);
		bool getActive();		

	protected:
		std::string m_id;
		int m_x;
		int m_y;
		int m_cx;
		int m_cy;
		int m_mincx;
		int m_mincy;
		bool m_center;
		bool m_visible;
		bool m_active;	// ¼¤»î×´Ì¬
					
		CControl* m_root;

		CControl* m_lastHover;	// 
	};

};
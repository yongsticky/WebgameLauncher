#pragma once

#include "Objectx.h"
#include "MessageDef.h"

#include "EventxDispatch.h"

namespace SDUI
{


	class CHostWindow;
	class CWindowMessageDispatcher;
	class CLayoutLoader;
	class CEventxHandler;

	class CControl :
		public CObjectx,
		public CEventxDispatch
	{
		friend class CHostWindow;
		friend class CWindowMessageDispatcher;
		friend class CLayoutLoader;

	public:
		CControl();
		virtual ~CControl();

		virtual bool createFromXml(CXmlAttribute* attr);
		virtual int getClassType();

	public:
		virtual unsigned int addChild(CControl* control);
		virtual CControl* findChild(const char* id);
		virtual std::string fromData();
		virtual void updateTo(const std::string& data);
				
		virtual bool hitMe(int x, int y);
		virtual bool redraw();
		virtual void layout(int x, int y, int cx, int cy);
		virtual void show(bool show);

		// 派发事件	
		CControl* getParent();
		CControl* getRoot();
		CHostWindow* getHostWindow();

	protected:
		// 事件
		virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);

		virtual bool isDrawable();

		// 派发来自Window的消息
		int _firePreorderMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);		// 先根遍历消息
		int _firePosteriorMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);	// 后根遍历消息

		// 是自己的消息吗？
		bool _canProcessThisMessage(unsigned int message, int wparam, int lparam);

		void _setHostWindow(CHostWindow* hostWindow);


	public:
		void setId(const std::string& id);
		std::string getId();
		void setPos(int x, int y);
		void setSize(int cx, int cy);
		void setVisible(bool visible);
		void setHitable(bool hitable);
		void setHitvalue(int hitval);

	protected:
		std::string m_id;	// id

		int m_x;		// x pos set
		int m_xx;		// paint x pos
		int m_y;		// y pos set
		int m_yy;
		int m_cx;		// cx	width
		int m_cxcx;
		int m_cy;		// cy	height
		int m_cycy;

		bool m_visible;
		bool m_hitable;		// 能否被命中

		int m_htval;		// NCHITTEST返回值  0-不命中 1-命中CLIENT 2-命中CAPTION		

		// 子节点
		std::vector<CControl*> m_children;

		// 父节点
		CControl* m_parent;

		// 	
		CHostWindow* m_hostWindow;

		// 事件通知
		std::vector<CEventxHandler*> m_handlers;;
	};

};
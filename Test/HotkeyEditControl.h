#pragma once

#include <set>

class CKeySet
{
public:
	CKeySet(){keyReset();}
	~CKeySet(){}

	void keyChanged(unsigned int code, bool pressed);
	void keyReset();
	std::string keyResult();
	std::string codeToChar(unsigned int code);
	bool keyOk();	
	bool repeatPressUpdate(unsigned int code, bool add = true);	

	bool m_ctrl;
	bool m_shift;
	bool m_alt;
	unsigned int m_char;

	std::set<unsigned int> m_repeat;
};


class CHotkeyEditControl : public SDUI::CEditControl
{
public:
	CHotkeyEditControl();
	virtual ~CHotkeyEditControl();


	DYNAMIC_OBJECT_DECLARE(CHotkeyEditControl, CObjectx)

	virtual bool createFromXml(SDUI::CXmlAttribute* attr);

	virtual std::string fromData();
	virtual void updateTo(const std::string& data);

protected:
	virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);
	
	static WNDPROC s_defWndProc;
	static LRESULT CALLBACK HotkeyEditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool onKeyDown(unsigned int message, unsigned int wparam, int lparam);
	bool onKeyUp(unsigned int message, unsigned int wparam, int lparam);

	void updateUI();

	bool m_setOK;

	CKeySet m_keySet;
};


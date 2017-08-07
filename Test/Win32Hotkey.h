#pragma once

class CWin32Hotkey : public SDUI::CWin32Component
{
public:
	CWin32Hotkey();
	virtual ~CWin32Hotkey();


	DYNAMIC_OBJECT_DECLARE(CWin32Hotkey, CObjectx)

	virtual bool createFromXml(SDUI::CXmlAttribute* attr);

	virtual int onMessage(unsigned int message, unsigned int wparam, int lparam, bool& handled);
	
	void setVerify(const std::string& verify);
	void setGroup(const std::string& group);
	void setKey(const std::string& key);

private:
	bool parseConfigString(const std::string& s);

	void registerHotkey();

protected:
	int m_hotkeyId;

	int m_times;

	std::string m_verify;
	std::string m_group;
	std::string m_key;

	unsigned int m_mod;
	unsigned int m_char;
};


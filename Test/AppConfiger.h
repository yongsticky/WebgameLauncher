#pragma once
class CAppConfiger
{
	CAppConfiger();

public:
	virtual ~CAppConfiger();

	static CAppConfiger* getInstance()
	{
		if (_instance)
		{
			return _instance;
		}

		_instance = new CAppConfiger();
		_instance->init();

		return _instance;
	}

	void write(const std::string& group, const std::string& key, const std::string& value);
	std::string read(const std::string& group, const std::string& key, const std::string& default);

private:
	void init();


	static CAppConfiger* _instance;


	std::string m_profile;

};


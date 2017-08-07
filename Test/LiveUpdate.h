#pragma once

#include "TcpClient.h"

#include <WinInet.h>


/*
class CLiveUpdate : 
	public _TcpEventHandler
	public _HttpEventHandler
{
	static CLiveUpdate* _instance;
public:
	static CLiveUpdate* getInstance()
	{
		if (!_instance)
		{
			_instance = new CLiveUpdate();
		}
		return _instance;
	}
	
	bool start();

	
private:
	CLiveUpdate();
	~CLiveUpdate();

	virtual int onConnected();
	virtual int onData(SocketStreamReader* reader);	
	virtual int onClosed();

	virtual int onRecvHeader(int field, DWORD_PTR info);
	virtual int onRecvData(char* pbuf, unsigned int size, unsigned int offset);	
	virtual int onComplete(unsigned int recv, unsigned int total);
	virtual int onError(int err);
		
	
	void startUpdate(std::string url, std::string md5);
	
private:
	TcpClient m_tcpClient;	
	HttpClient m_httpClient;
};

*/
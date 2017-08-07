#include "stdafx.h"
#include "LiveUpdate.h"

#include "TcpClient.h"
#include "OnlineCommandReq.h"
#include "OnlineCommandResp.h"

CLiveUpdate* CLiveUpdate::_instance = nullptr;

bool CLiveUpdate::start()
{	
	m_tcpClient.create();
	m_tcpClient.connect("120.76.53.140", 8172);

	//m_httpDownloader.download(std::string("http://youxi.592hi.com/static/client/mszy/172le_mszy.exe"), std::string("c:\\temp\\"));

	return true;
}

CLiveUpdate::CLiveUpdate() : m_tcpClient(this), m_httpClient(this)
{	
	
}


CLiveUpdate::~CLiveUpdate()
{
}

void CLiveUpdate::startUpdate(std::string url, std::string md5)
{
	ATLTRACE("startUpdate url=%s md5=%s.\n", url.c_str(), md5.c_str());

	HTTP_OPT_UV v;
	v.dw = 4096;
	m_httpClient.setopt(1, v);
	m_httpClient.request(url.c_str());
	
}

int CLiveUpdate::onConnected()
{
	ATLTRACE("onConnected.\n");

	COnlineCommandReq req;

	BYTE* buffer = NULL;
	unsigned int bufSize = 0;
	req.encode(&buffer, &bufSize);

	BYTE* pbuf = buffer;
	req.encrypt(&pbuf, &bufSize);

	m_tcpClient.getWriter()->write((const char*)pbuf, bufSize);

	return 0;
}


int CLiveUpdate::onData(SocketStreamReader* reader)
{	
	char* buf;
	int len;
	reader->getBuffer(&buf, &len);

	COnlineCommandResp resp;
	resp.decrypt((BYTE**)&buf, (unsigned int*)&len);
	resp.decode((BYTE*)buf, len);

	delete buf;

	return 0;
}

int CLiveUpdate::onClosed()
{
	return 0;
}

int CLiveUpdate::onError(int err)
{
	ATLTRACE("onError: err=%d.\n", err);

	return 0;
}

int CLiveUpdate::onRecvHeader(int field, DWORD_PTR info)
{
	ATLTRACE("onRecvHeader: field=%d, info=%u.\n", field, info);
	
	return 0;
}

int CLiveUpdate::onRecvData(char* pbuf, unsigned int size, unsigned int offset)
{
	ATLTRACE("onRecvData: pbuf=0x%0x, size=%u offset=%u.\n", pbuf, size, offset);
	
	return 0;
}

int CLiveUpdate::onComplete(unsigned int recv, unsigned int total)
{
	ATLTRACE("onComplete: recv=%u total=%u.\n", recv, total);
	
	return 0;
}
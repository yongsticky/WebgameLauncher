#include "stdafx.h"
#include "OnlineCommandReq.h"


COnlineCommandReq::COnlineCommandReq()
{
	packet.header.command_id = 1;
	cliVersion = 4;
}


COnlineCommandReq::~COnlineCommandReq()
{
}

bool COnlineCommandReq::encode(BYTE** ppb, unsigned int* psize)
{
	CProtoclPacket::encode(ppb, psize);
	*packet.body = cliVersion;

	return true;
}

unsigned int COnlineCommandReq::bodySize()
{
	return sizeof(BYTE);
}

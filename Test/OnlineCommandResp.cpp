#include "stdafx.h"
#include "OnlineCommandResp.h"


COnlineCommandResp::COnlineCommandResp()
{
}


COnlineCommandResp::~COnlineCommandResp()
{
}

bool COnlineCommandResp::decode(BYTE* pb, unsigned int size)
{
	CProtoclPacket::decode(pb, size);

	BYTE* p = packet.body;

	result = *((BYTE*)p);
	p += sizeof(BYTE);

	int urlSize = *((WORD*)p);
	p += sizeof(WORD);
	if (urlSize)
	{
		url = std::string((const char*)p, urlSize);
		p += urlSize;
	}

	int md5Size = *((WORD*)p);
	p += sizeof(WORD);
	if (md5Size)
	{
		md5 = std::string((const char*)p, md5Size);
		p += md5Size;
	}

	return true;
}

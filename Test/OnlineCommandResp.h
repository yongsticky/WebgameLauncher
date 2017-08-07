#pragma once

#include "ProtoclPacket.h"

class COnlineCommandResp : public CProtoclPacket
{
public:
	COnlineCommandResp();
	virtual ~COnlineCommandResp();

	bool decode(BYTE* pb, unsigned int size);
	
	BYTE result;
	std::string url;
	std::string md5;
};


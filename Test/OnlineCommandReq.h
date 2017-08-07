#pragma once

#include "ProtoclPacket.h"


class COnlineCommandReq : public CProtoclPacket
{
public:
	COnlineCommandReq();
	virtual ~COnlineCommandReq();

	bool encode(BYTE** ppb, unsigned int* psize);

	unsigned int bodySize();

private:
	BYTE cliVersion;
};


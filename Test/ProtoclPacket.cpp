#include "stdafx.h"
#include "ProtoclPacket.h"


CProtoclPacket::CProtoclPacket()
{
	::memset(&packet, 0, sizeof(packet));
	packet.header.version = 1;
	packet.header.os_ver = (DWORD)-1;
}


CProtoclPacket::~CProtoclPacket()
{
}

bool CProtoclPacket::encode(BYTE** ppb, unsigned int* psize)
{
	packet.header.total_size = headerSize() + bodySize();
	BYTE* buffer = new BYTE[packet.header.total_size];	

	BYTE* p = buffer;
	*((WORD*)p) = packet.header.total_size;
	p += sizeof(WORD);
	*((BYTE*)p) = packet.header.version;
	p += sizeof(BYTE);
	*((BYTE*)p) = packet.header.command_id;
	p += sizeof(BYTE);
	*((WORD*)p) = packet.header.ext_size;
	p += sizeof(WORD);
	*((DWORD*)p) = packet.header.os_ver;
	p += sizeof(DWORD);
	
	packet.ext = p;
	p += packet.header.ext_size;

	packet.body = p;
	
	*ppb = buffer;
	*psize = packet.header.total_size;
	
	return true;
}

bool CProtoclPacket::decode(BYTE* pb, unsigned int size)
{
	BYTE* p = pb;
	packet.header.total_size = *((WORD*)p);
	p += sizeof(WORD);
	packet.header.version = *((BYTE*)p);
	p += sizeof(BYTE);
	packet.header.command_id = *((BYTE*)p);
	p += sizeof(BYTE);
	packet.header.ext_size = *((WORD*)p);
	p += sizeof(WORD);
	packet.header.os_ver = *((DWORD*)p);
	p += sizeof(DWORD);

	packet.ext = p;
	p += packet.header.ext_size;

	packet.body = p;

	return true;
}

bool CProtoclPacket::encrypt(BYTE** ppb, unsigned int* psize)
{
	for (int i = 2; i < *psize; ++i)
	{
		(*ppb)[i] = 255 - (*ppb)[i];
	}

	return false;
}

bool CProtoclPacket::decrypt(BYTE** ppb, unsigned int* psize)
{
	for (int i = 2; i < *psize; ++i)
	{
		(*ppb)[i] = 255 - (*ppb)[i];
	}

	return false;
}

unsigned int CProtoclPacket::headerSize()
{
	return sizeof(packet.header);
}

unsigned int CProtoclPacket::bodySize()
{
	return 0;
}

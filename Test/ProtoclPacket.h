#pragma once
class CProtoclPacket
{
public:
	CProtoclPacket();
	virtual ~CProtoclPacket();

	virtual bool encode(BYTE** ppb, unsigned int* psize);
	virtual bool decode(BYTE* pb, unsigned int size);

	virtual bool encrypt(BYTE** ppb, unsigned int* psize);
	virtual bool decrypt(BYTE** ppb, unsigned int* psize);

	virtual unsigned int headerSize();
	virtual unsigned int bodySize();
	

protected:
	#pragma pack (1)
	struct _Packet {
		struct _Header {
			WORD total_size;		// 2 Bytes
			BYTE version;			// 1 Byte
			BYTE command_id;		// 1 Byte
			WORD ext_size;			// 2 Bytes
			DWORD os_ver;			// 4 Bytes
		} header;		
		BYTE* ext;
		BYTE* body;		
	} packet;
};


#pragma once
#include "StreamBuffer.h"
typedef struct MESSAGE
{
	// Ÿ��
	enum MESSAGE_TYPE
	{
		JOIN,
		LEAVE,
		PACKET,
		MAFIA
	};
	MESSAGE_TYPE type;		// Ÿ��
	__int64 sessionID;		// ���� ID
	StreamBuffer* data;	// ��Ŷ ������
}Message;
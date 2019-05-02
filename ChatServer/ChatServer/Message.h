#pragma once
#include "StreamBuffer.h"
typedef struct MESSAGE
{
	// 타입
	enum MESSAGE_TYPE
	{
		JOIN,
		LEAVE,
		PACKET,
		MAFIA
	};
	MESSAGE_TYPE type;		// 타입
	__int64 sessionID;		// 세션 ID
	StreamBuffer* data;	// 패킷 포인터
}Message;
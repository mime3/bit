#include "pch.h"
#include "ChatClient.h"
#include "MFCChatClient.h"

void ChatClient::OnClientJoin(INT64 ClientID, Session* session)
{
}

void ChatClient::OnClientLeave(INT64 ClientID)
{
	Reconnect();
}

bool ChatClient::OnConnectionRequest(char* ClientIP, int Port)
{
	return true;
}

void ChatClient::OnRecv(INT64 clientID, StreamBuffer* packet)
{
}

void ChatClient::OnSend(INT64 clientID, int sendSize)
{
}

void ChatClient::OnError(int errorCode, const WCHAR* errorMessage)
{
}

void ChatClient::OnConnect(INT64 ClientID)
{
	_serverID = ClientID;
	_connected = true;
}

ChatClient::ChatClient(CMFCChatClientApp* pointer) : _pointer(pointer)
{
}

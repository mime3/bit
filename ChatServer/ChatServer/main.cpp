#include <stdio.h>
#include "main.h"

int main()
{
	ChatLanServer * mafiaServer = new ChatLanServer();
	mafiaServer->Start();
	while (true)
	{
		mafiaServer->PrintInfo();
		Sleep(1000);
	}
	mafiaServer->Stop();
	return 0;
}
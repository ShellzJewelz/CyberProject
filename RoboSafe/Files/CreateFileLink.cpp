// ###############################
// #######  INFORMATION  #########
// ###############################
// Author: David "Shellz" Klein
// Platform: Windows 10
// Date: 04/02/2016 
// Version: Visual C++ 14
// ###############################
// #########  INCLUDES  ##########
// ###############################
#include "Engine.h"
#include "mhook.h"
#include <fstream>

#pragma comment(lib, "Engine.lib")
#pragma comment(lib, "Trampoline.lib")
// ###############################
// #########  CONSTANTS  #########
// ###############################
#define EXTENSIONS_LENGTH 16
#define EXTENSIONS "EXTENSIONS"
#define IP "127.0.0.1"
#define PORT 4000
// ###############################
// #########  GLOBALS  ###########
// ###############################
using namespace std; 

typedef HANDLE(WINAPI *fpCreateFileW)(
	LPCTSTR,
	DWORD,
	DWORD,
	LPSECURITY_ATTRIBUTES,
	DWORD,
	DWORD,
	HANDLE
	);
HMODULE hKernel32 = GetModuleHandle(L"Kernel32");
fpCreateFileW TrueCreateFileW = (fpCreateFileW) GetProcAddress(hKernel32, "CreateFileW");

bool bDone = false;
bool bRunning = false;
bool bFailed = false;
char* szExtensions[] = 
{
	".secret",
	".supersecret"
};
SocketObject* spSocketClient = new SocketObject();

ofstream f("C:\\test.log", ofstream::out);
// ###############################
// ########  FUNCTIONS  ##########
// ###############################
HANDLE WINAPI HookCreateFileW(
	LPCTSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
	)
{
	char szFileName[MAX_PATH];
	try
	{
		strcpy_s(szFileName, Encode(lpFileName, CP_UTF8));
		for	(int iExtensionIndex = 0; iExtensionIndex < 2; iExtensionIndex++)
		{
			if (strstr(szFileName, szExtensions[iExtensionIndex]))
			{
				/*
				If the program opens a file that
				already exists for for reading then
				send the server the file name and
				set the last error to a fitting error
				so the user will understand he has no
				access to that file
				*/
				if (dwCreationDisposition == OPEN_EXISTING || dwCreationDisposition == OPEN_ALWAYS)
				{
					if (dwDesiredAccess == GENERIC_READ)
					{
						spSocketClient->Send(szFileName);
						SetLastError(ERROR_ACCESS_DENIED);
						return INVALID_HANDLE_VALUE;
					}
				}
			}
		}
	}
	catch (SocketError& socketError)
	{
		bRunning = false;
	}

	return TrueCreateFileW(
		lpFileName,
		dwDesiredAccess,
		dwShareMode,
		lpSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
		);
}
// ###############################
// ###########  MAIN  ############
// ###############################
BOOL APIENTRY DllMain(HMODULE hDll, DWORD dwCallReason, LPVOID lpReserved)
{
	switch (dwCallReason)
	{
		case DLL_PROCESS_ATTACH:
			if (!bDone)
			{
				/*
				DLL Optimization
				The DLL does not need these
				thread-level notifications
				*/
				DisableThreadLibraryCalls(hDll);

				try
				{
					spSocketClient->Connect(IP, PORT);
					Mhook_SetHook((PVOID*)&TrueCreateFileW, HookCreateFileW);
					bRunning = true;
				}
				catch (SocketError& socketError)
				{
					bFailed = true;
					bRunning = false;
				}
			}
			if (bFailed)
			{
				spSocketClient->Close();
				Mhook_Unhook((PVOID*)&TrueCreateFileW);
			}
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			if (bRunning)
			{
				/*
				DLL Loading has failed or
				FreeLibrary was called or
				the process is terminating
				*/
				spSocketClient->Close();
				Mhook_Unhook((PVOID*)&TrueCreateFileW);
			}
			break;
	}
	return TRUE;
}
// ###############################
// ###########  QUIT  ############
// ###############################
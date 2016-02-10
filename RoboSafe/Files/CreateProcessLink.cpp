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
#include "Syringe.h"
#include "mhook.h"
#include <fstream>

#pragma comment(lib, "Engine.lib")
#pragma comment(lib, "Syringe.lib")
#pragma comment(lib, "Trampoline.lib")
// ###############################
// #########  CONSTANTS  #########
// ###############################
#define PROCESSES_LENGTH 32
#define PROCESSES "PROCESSES"
#define IP "127.0.0.1"
#define PORT 4000
// ###############################
// #########  GLOBALS  ###########
// ###############################
using namespace std; 

typedef BOOL(WINAPI *fpCreateProcessW)(
	LPCTSTR,
	LPTSTR,
	LPSECURITY_ATTRIBUTES,
	LPSECURITY_ATTRIBUTES,
	BOOL,
	DWORD,
	LPVOID,
	LPCTSTR,
	LPSTARTUPINFO,
	LPPROCESS_INFORMATION
	);
HMODULE hKernel32 = GetModuleHandle(L"Kernel32");
fpCreateProcessW TrueCreateProcessW = (fpCreateProcessW) GetProcAddress(hKernel32, "CreateProcessW");

bool bDone = false;
bool bRunning = false;
bool bFailed = false;
char* szProcesses[] = 
{
	"chrome.exe",
	"notepad.exe",
	NULL,
	NULL
};
SocketObject* spSocketClient = new SocketObject();
ofstream f("C:\\test.log", ofstream::out);
// ###############################
// ########  FUNCTIONS  ##########
// ###############################
BOOL WINAPI HookCreateProcessW(
	LPCTSTR lpApplicationName,
	LPTSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCTSTR lpCurrentDirectory,
	LPSTARTUPINFO lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
	)
{
	char szFullProcessName[MAX_PATH];
	char szUpperFullProcessName[MAX_PATH];
	char szUpperProcessName[MAX_PATH];

	/*
	Since lpApplicationName is an optional
	parameter it can be NULL in that case
	lpCommandLine will contain the process name
	*/
	if (lpApplicationName != NULL)
		strcpy_s(szFullProcessName, Encode(lpApplicationName, CP_UTF8));
	else if (lpCommandLine != NULL)
		strcpy_s(szFullProcessName, Encode(lpCommandLine, CP_UTF8));
	else
		return TrueCreateProcessW(
			lpApplicationName,
			lpCommandLine,
			lpProcessAttributes,
			lpThreadAttributes,
			bInheritHandles,
			dwCreationFlags,
			lpEnvironment,
			lpCurrentDirectory,
			lpStartupInfo,
			lpProcessInformation
			);

	try
	{
		for (int iProcessIndex = 0; iProcessIndex < PROCESSES_LENGTH; iProcessIndex++)
		{
			if (szProcesses[iProcessIndex] != NULL)
			{
				char szCurrentCheckedProcess[MAX_PATH];
				strcpy_s(szCurrentCheckedProcess, szProcesses[iProcessIndex]);
				f << "Process " << szProcesses[iProcessIndex] << endl;
				Upper(szFullProcessName, szUpperFullProcessName);
				Upper(szCurrentCheckedProcess, szUpperProcessName);
				f << "Upper Full Process " << szUpperFullProcessName << endl;
				f << "Upper Process " << szUpperProcessName << endl;
				if (strstr(szUpperFullProcessName, szUpperProcessName) != NULL)
				{
					BOOL bResult = TrueCreateProcessW(
						lpApplicationName,
						lpCommandLine,
						lpProcessAttributes,
						lpThreadAttributes,
						bInheritHandles,
						dwCreationFlags,
						lpEnvironment,
						lpCurrentDirectory,
						lpStartupInfo,
						lpProcessInformation
						);
					f << "Result " << bResult << endl;
					bool bInjected = Inject(lpProcessInformation->hProcess, "CreateFileLink.dll");
					f << "Inject " << szUpperProcessName << " " << bInjected << endl;
					if (strstr(szUpperFullProcessName, "CHROME.EXE") != NULL)
					{
						bInjected = Inject(lpProcessInformation->hProcess, "CreateProcessLink.dll");
						f << "Inject " << szUpperProcessName << " " << bInjected << endl;
					}
					return bResult;
				}
			}
			break;
		}
	}
	catch (SocketError& socketError)
	{
		bFailed = true;
	}

	return TrueCreateProcessW(
		lpApplicationName,
		lpCommandLine,
		lpProcessAttributes,
		lpThreadAttributes,
		bInheritHandles,
		dwCreationFlags,
		lpEnvironment,
		lpCurrentDirectory,
		lpStartupInfo,
		lpProcessInformation
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
				Mhook_SetHook((PVOID*)&TrueCreateProcessW, HookCreateProcessW);
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
			Mhook_Unhook((PVOID*)&TrueCreateProcessW);
		}
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
			Mhook_Unhook((PVOID*)&TrueCreateProcessW);
		}
		break;
}
return TRUE;
}
// ###############################
// ###########  QUIT  ############
// ###############################
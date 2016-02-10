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
#define EXPORT
#include "Syringe.h"
// ###############################
// ########  FUNCTIONS  ##########
// ###############################
HANDLE DECLSPEC GetProcessByName(const char* pszProcessName)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	HANDLE hProcess;

    if (Process32FirstW(hSnapshot, &entry) == TRUE)
    {
        while (Process32NextW(hSnapshot, &entry) == TRUE)
        {
			char szTempProcessName[MAX_PATH];
			unsigned int uiCharsConverted = 0;
			wcstombs_s(
				&uiCharsConverted,
				szTempProcessName,
				entry.szExeFile, 
				MAX_PATH
				);
            if (_stricmp(szTempProcessName, pszProcessName) == 0)
            {  
			    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				return hProcess;
            }
        }
    }
	CloseHandle(hSnapshot);
	return INVALID_HANDLE_VALUE;
}

HANDLE DECLSPEC GetProcessByName(const wchar_t* pwszProcessName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	HANDLE hProcess;

	if (Process32FirstW(hSnapshot, &entry) == TRUE)
	{
		while (Process32NextW(hSnapshot, &entry) == TRUE)
		{
			if (_wcsicmp(entry.szExeFile, pwszProcessName) == 0)
			{
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				return hProcess;
			}
		}
	}
	CloseHandle(hSnapshot);
	return INVALID_HANDLE_VALUE;
}

bool DECLSPEC Inject(HANDLE hProcess, const char* pszDllPath) 
{
	// Get address of the LoadLibrary function.
	HMODULE hModule = GetModuleHandle(L"kernel32.dll");
	LPVOID lpProcedureAddress = (LPVOID)GetProcAddress(hModule, "LoadLibraryA");
	if (!lpProcedureAddress)
		return false;

	// Allocate new memory region inside the process's address space.
	LPVOID lpBaseAddress = (LPVOID) VirtualAllocEx(
		hProcess,
		NULL,
		strlen(pszDllPath),
		MEM_RESERVE | MEM_COMMIT, 
		PAGE_READWRITE
		);
	if (!lpBaseAddress)
		return false;
	
	// Write the argument to LoadLibraryA to the process's newly allocated memory region.
	BOOL bResult = WriteProcessMemory(
		hProcess,
		lpBaseAddress,
		pszDllPath,
		strlen(pszDllPath),
		NULL
		);
	if (!bResult)
		return false;
	
	// Inject our DLL into the process's address space.
	HANDLE hThread = CreateRemoteThread(
		hProcess,
		NULL,
		0, 
		(LPTHREAD_START_ROUTINE)lpProcedureAddress,
		lpBaseAddress,
		NULL,
		NULL
		);
	if (!hThread)
		return false;

	return true;
}

bool DECLSPEC Eject(HANDLE hProcess, HANDLE hRemoteThread) 
{
    DWORD dwThreadTeminationStatus;
    HMODULE hModule;

    if (hRemoteThread != NULL)
    {
        WaitForSingleObject(hRemoteThread, INFINITE);
        GetExitCodeThread(hRemoteThread, &dwThreadTeminationStatus);
    }

    hModule = GetModuleHandle(L"Kernel32.dll");
    hRemoteThread = CreateRemoteThread(
		hProcess,
		NULL, 
		0, 
        (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "FreeLibraryA"),
        (LPVOID)dwThreadTeminationStatus,
		0,
		NULL
		);

    CloseHandle(hRemoteThread);

    return true;
}
// ###############################
// ###########  QUIT  ############
// ###############################
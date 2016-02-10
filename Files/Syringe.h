#ifndef SYRINGE_H
#define SYRINGE_H

#include <Windows.h>
#include <TlHelp32.h>

#ifdef EXPORT
#define DECLSPEC __declspec(dllexport) 
#else
#define DECLSPEC __declspec(dllimport)
#endif // EXPORT

HANDLE DECLSPEC GetProcessByName(const char* pszProcessName);
HANDLE DECLSPEC GetProcessByName(const wchar_t* pwszProcessName);
bool DECLSPEC Inject(HANDLE hProcess, const char* pszDllPath);

#endif // SYRINGE_H
#include <Windows.h>
#include <stdio.h>

char szDllRoot[] = "C:\\Users\\Admin\\Desktop\\CyberProject\\Release\\";
char szNewDllRoot[] = "C:\\Windows\\";
char* szDllNames[] = 
{
	"Engine.dll",
	"Syringe.dll",
	"Trampoline.dll",
	"CreateFileLink.dll",
	"CreateProcessLink.dll",
};

int main()
{
	for each(char* szDllName in szDllNames)
	{
		char szExistingFileName[MAX_PATH];
		char szNewFileName[MAX_PATH];
		strcpy_s(szExistingFileName, szDllRoot);
		strcpy_s(szNewFileName, szNewDllRoot);
		strcat_s(szExistingFileName, szDllName);
		strcat_s(szNewFileName, szDllName);
		BOOL bResult = CopyFileA(
			szExistingFileName,
			szNewFileName,
			FALSE
			);
		printf("%d %s\n", GetLastError(), szExistingFileName);
	}
	return 0;
}
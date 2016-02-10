#ifndef CLIENT_H
#define CLIENT_H

#include "Engine.h"
#include "Syringe.h"
#include <Windows.h>
#include <WinIoCtl.h>
#include <setupapi.h>
#include <dbt.h>
#include <tchar.h> 
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "Engine.lib")
#pragma comment(lib, "Syringe.lib")
#pragma comment(lib, "Setupapi.lib")

class Detection
{
private:
	HWND hWindow;
	bool CreateWindowClass();
	static HDEVNOTIFY CreateAndRegisterNotification(GUID InterfaceClassGuid, HWND hWindow);
	static LRESULT CALLBACK WindowCallback(HWND hWindow, UINT uiMessage, WPARAM wParam, LPARAM lParam);

public:
	Detection(wchar_t* pwszClassName);
	void MessageDispatch();
};

#endif // CLIENT_H
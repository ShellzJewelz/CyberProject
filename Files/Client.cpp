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
#include "Client.h"
// ###############################
// #########  GLOBALS  ###########
// ###############################
bool CheckAction(DWORD dwAction);
char GetVolumeLabelByDiskNumber(DWORD dwDeviceNumber);
void DetectAlreadyConnectedDevices(ThreadObject* tpThreads[]);
char DriveFromMask(ULONG ulMask);
void Redispatch(PDEV_BROADCAST_VOLUME pVolumeInterface, int iEvent);
DWORD WINAPI Inspection(LPVOID lpParameter);
DWORD WINAPI InspectionManager(LPVOID lpParameter);
DWORD WINAPI Injection(LPVOID lpParameter);
DWORD WINAPI DetectionManager(LPVOID lpParameter);
SocketObject* spSocketClient = new SocketObject();
// ###############################
// #########  CONSTANTS  #########
// ###############################
#define IP "127.0.0.1"
#define PORT 5000
#define BACKLOG 1
#define BUFFER 1024

#define ROOT 4
#define DRIVES 26
#define IN_DRIVE_LENGTH 16
#define OUT_DRIVE_LENGTH 17
#define IN_DRIVE "IN_DRIVE_LETTER_"
#define OUT_DRIVE "OUT_DRIVE_LETTER_"

#define THREADS 3
#define EVENT_NAME L"SocketCreationSignal"
#define WINDOW_CLASS L"DeviceDetectionClass"
#define INJECTION_TARGET "CreateProcessLink.dll" 

GUID USBGUID =
{
	0x25dbce51,
	0x6c8f,
	0x4a72,
	0x8a,
	0x6d,
	0xb5,
	0x4c,
	0x2b,
	0x4f,
	0xc8,
	0x35
};
// ###############################
// #########  CLASSES  ###########
// ###############################
Detection::Detection(wchar_t* wszClassName)
{
	if (this->CreateWindowClass())
	{
		this->hWindow = CreateWindow(
			wszClassName,
			NULL,
			WS_BORDER,
			0,
			0,
			0,
			0,
			NULL,
			NULL,
			NULL,
			NULL
			);

		if (hWindow != NULL)
		{
			//ShowWindow(hWindow, SW_SHOWNORMAL);
			UpdateWindow(hWindow);
		}
	}
}

bool Detection::CreateWindowClass()
{
	/*
	Define the most basic window class
	and register it in the system for
	later use
	*/
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC |
		CS_HREDRAW |
		CS_VREDRAW;
	windowClass.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(0));
	windowClass.lpfnWndProc = reinterpret_cast<WNDPROC>(Detection::WindowCallback);
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	windowClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	windowClass.hCursor = LoadCursor(0, IDC_ARROW);
	windowClass.lpszClassName = WINDOW_CLASS;
	windowClass.lpszMenuName = NULL;
	windowClass.hIconSm = windowClass.hIcon;
	if (!RegisterClassEx(&windowClass))
		return false;
	return true;
}

HDEVNOTIFY Detection::CreateAndRegisterNotification(GUID InterfaceClassGuid, HWND hWindow)
{
	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
	ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));
	NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	NotificationFilter.dbcc_classguid = InterfaceClassGuid;
	HDEVNOTIFY hDeviceNotify = RegisterDeviceNotification(
		hWindow,
		&NotificationFilter,
		DEVICE_NOTIFY_WINDOW_HANDLE
		);
	return hDeviceNotify;
}

LRESULT CALLBACK Detection::WindowCallback(
	HWND hWindow,
	UINT uiMessage,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	Process the system messages
	WM_CREATE - Window Creation System Message
	WM_DEVICECHANGE - Device Connection/Removal System Message
	WM_CLOSE - Window Termination System Message
	WM_DESTROY - Window Destruction System Message
	*/

	LRESULT lResult = 1;
	static HDEVNOTIFY hDeviceNotify;
	static HWND hWorkingWindow;
	PDEV_BROADCAST_DEVICEINTERFACE pDeviceInterface = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;
	switch (uiMessage)
	{
	case WM_CREATE:
		//hDeviceNotify = Detector::CreateAndRegisterNotification(USBGUID, hWindow);	
		try
		{
			HANDLE hEvent = OpenEvent(
				EVENT_ALL_ACCESS,
				FALSE,
				EVENT_NAME
				);
			WaitForSingleObject(hEvent, INFINITE);
			spSocketClient->Connect(IP, PORT);
		}
		catch(SocketError socketError)
		{
			printf("[%d] %s", socketError.GetErrorCode(), socketError.ErrorFormat());
		}		
		break;
	case WM_DEVICECHANGE:	
		if (pDeviceInterface != NULL && pDeviceInterface->dbcc_devicetype == DBT_DEVTYP_VOLUME)
		{
			PDEV_BROADCAST_VOLUME pVolumeInterface = (PDEV_BROADCAST_VOLUME)pDeviceInterface;
			switch (wParam)
			{
			/*
			Device insertion or removal event
			has happened
			*/
			case DBT_DEVICEARRIVAL:
				Redispatch(pVolumeInterface, wParam);
				break;
			case DBT_DEVICEREMOVECOMPLETE:
				Redispatch(pVolumeInterface, wParam);
				break;
			default:
				break;
			}
		}
		break;
	case WM_CLOSE:
		//UnregisterDeviceNotification(hDeviceNotify);
		break;
	case WM_DESTROY:
		/*
		Request the system to terminate the
		the window thread
		*/
		PostQuitMessage(0);
		break;
	default:
		/*
		For all other cases we would call
		the default window function to handle
		the parameters and save the result

		By doing this we ensure that all system 
		messages we did not process will get 
		processed by the system
		*/
		lResult = DefWindowProc(hWindow, uiMessage, wParam, lParam);
		break;
	}
	return lResult;
}

void Detection::MessageDispatch()
{
	/*
	Manually send system messages 
	to the window we created
	*/
	MSG message;
	int iResult;
	while (iResult = GetMessage(&message, NULL, 0, 0) != 0)
	{
		if (iResult == -1)
			break;
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}
// ###############################
// ########  FUNCTIONS  ##########
// ###############################
bool CheckAction(DWORD dwAction)
{
	switch (dwAction)
	{
	case FILE_ACTION_ADDED:
		return true;
	case FILE_ACTION_REMOVED:
		return false;
	case FILE_ACTION_MODIFIED:
		return false;
	case FILE_ACTION_RENAMED_OLD_NAME:
		return true;
	case FILE_ACTION_RENAMED_NEW_NAME:
		return true;
	}
	return false;
}

char GetVolumeLabelByDiskNumber(DWORD dwDeviceNumber)
{
	/*
	The returned value is like
	C:\ and a null terminator 
	seperating each drive root
	hence 4 characters per letter
	*/
	wchar_t wszDrives[26 * 4];

	DWORD dwSize = GetLogicalDriveStrings(sizeof(wszDrives), wszDrives);
	DWORD dwBytesReturned = 0;
	if (dwSize)
	{
		for (unsigned int uiCharIndex = 0; uiCharIndex <= dwSize; uiCharIndex += 4)
		{
			STORAGE_DEVICE_NUMBER storageDeviceNumber;
			ZeroMemory(&storageDeviceNumber, sizeof(STORAGE_DEVICE_NUMBER));
			storageDeviceNumber.DeviceNumber = 0;

			/*
			To obtain a drive handle we 
			need to use CreateFile with
			a path like \\.\C:
			*/
			wchar_t wszDrivePath[MAX_PATH];
			wcscpy_s(wszDrivePath, L"\\\\.\\");
			wcscat_s(wszDrivePath, wszDrives + uiCharIndex);
			wszDrivePath[wcslen(wszDrivePath) - 1] = L'\0';

			HANDLE hDrive = CreateFile(
				wszDrivePath,
				GENERIC_READ,
				FILE_SHARE_READ |
				FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				0
				);

			if (hDrive != INVALID_HANDLE_VALUE)
			{
				/*
				Get the device number of the
				device and compare it to our
				device's device number
				*/
				BOOL bResult = DeviceIoControl(
					hDrive,
					IOCTL_STORAGE_GET_DEVICE_NUMBER,
					NULL,
					0,
					&storageDeviceNumber,
					sizeof(storageDeviceNumber),
					&dwBytesReturned,
					NULL
					);
				if (bResult && dwBytesReturned)
				{
					if (storageDeviceNumber.DeviceNumber == dwDeviceNumber)
					{
						char cDrive = wctob(wszDrives[uiCharIndex]);
						return cDrive;
					}
				}
			}
			CloseHandle(hDrive);
		}
	}
	return NULL;
}

void DetectAlreadyConnectedDevices(ThreadObject* tpThreads[])
{
	HDEVINFO hDevInfo = SetupDiGetClassDevs(
		&GUID_DEVINTERFACE_DISK,
		NULL,
		NULL,
		DIGCF_PRESENT |
		DIGCF_DEVICEINTERFACE
		);
	SP_DEVINFO_DATA spDeviceInfoData;
	ZeroMemory(&spDeviceInfoData, sizeof(SP_DEVINFO_DATA));
	spDeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	LPTSTR pszPropertyBuffer[BUFFER];
	DWORD dwRequiredSize;
	DWORD dwRequiredBufferSize;
	DWORD dwProperyDatatype;
	BOOL bResult;

	for (DWORD dwDeviceInfoIndex = 0; SetupDiEnumDeviceInfo(
		hDevInfo,
		dwDeviceInfoIndex,
		&spDeviceInfoData
		);
	dwDeviceInfoIndex++)
	{
		bResult = SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&spDeviceInfoData,
			SPDRP_ENUMERATOR_NAME,
			&dwProperyDatatype,
			(LPBYTE)pszPropertyBuffer,
			BUFFER,
			&dwRequiredBufferSize);

		if (_tcscmp((LPTSTR)pszPropertyBuffer, TEXT("USBSTOR")) == 0)
		{
			SP_DEVICE_INTERFACE_DATA spDeviceInterfaceData;
			ZeroMemory(&spDeviceInterfaceData, sizeof(spDeviceInterfaceData));
			spDeviceInterfaceData.cbSize = sizeof(spDeviceInterfaceData);
			PSP_DEVICE_INTERFACE_DETAIL_DATA pspDeviceInterfaceDetailData = NULL;

			for (DWORD dwDeviceInterfacesIndex = 0; bResult = SetupDiEnumDeviceInterfaces(
				hDevInfo,
				&spDeviceInfoData,
				&GUID_DEVINTERFACE_DISK,
				dwDeviceInterfacesIndex++,
				&spDeviceInterfaceData
				);
			dwDeviceInterfacesIndex++)
			{
				DWORD dwError = GetLastError();
				if (!bResult)
				{
					if (dwError == ERROR_NO_MORE_DEVICES || dwError == ERROR_NO_MORE_ITEMS)
						break;
				}

				/*
				Get the required size for the
				PSP_DEVICE_INTERFACE_DETAIL_DATA
				structure
				*/
				bResult = SetupDiGetDeviceInterfaceDetail(
					hDevInfo,
					&spDeviceInterfaceData,
					NULL,
					0,
					&dwRequiredSize,
					NULL
					);

				/*
				Allocate that required size
				*/
				if (!bResult)
				{
					if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
					{
						pspDeviceInterfaceDetailData = new SP_DEVICE_INTERFACE_DETAIL_DATA[dwRequiredSize];//(PSP_DEVICE_INTERFACE_DETAIL_DATA)LocalAlloc(LPTR, dwRequiredSize);
						pspDeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
					}
					else
						break;
				}

				/*
				Get the details on that device
				*/
				bResult = SetupDiGetDeviceInterfaceDetail(
					hDevInfo,
					&spDeviceInterfaceData,
					pspDeviceInterfaceDetailData,
					dwRequiredSize,
					NULL,
					NULL
					);
				if (bResult)
				{
					STORAGE_DEVICE_NUMBER storageDeviceNumber;
					ZeroMemory(&storageDeviceNumber, sizeof(STORAGE_DEVICE_NUMBER));
					storageDeviceNumber.DeviceNumber = 0;
					DWORD dwSize = 0;

					/*
					Get the device handle
					*/
					HANDLE hDrive = CreateFile(
						pspDeviceInterfaceDetailData->DevicePath,
						GENERIC_READ,
						FILE_SHARE_READ |
						FILE_SHARE_WRITE,
						NULL,
						OPEN_EXISTING,
						0,
						0
						);
					if (hDrive != INVALID_HANDLE_VALUE)
					{
						/*
						Get the device number
						*/
						bResult = DeviceIoControl(
							hDrive,
							IOCTL_STORAGE_GET_DEVICE_NUMBER,
							NULL,
							0,
							&storageDeviceNumber,
							sizeof(storageDeviceNumber),
							&dwSize,
							NULL
							);
						if (bResult)
						{
							char cDrive = GetVolumeLabelByDiskNumber(storageDeviceNumber.DeviceNumber);
							if (cDrive)
							{
								int iIndex = cDrive - 'A';
								printf("%c:\\ will be watched\n", cDrive);
								tpThreads[iIndex] = new ThreadObject(Inspection, (LPVOID)cDrive);
								tpThreads[iIndex]->Start();
							}
						}
					}
					CloseHandle(hDrive);
				}
				delete pspDeviceInterfaceDetailData;
			}
		}
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);
}

char DriveFromMask(ULONG ulMask)
{
	char cDriveLetter;
	for (cDriveLetter = 'A'; cDriveLetter < 'Z'; cDriveLetter++)
	{
		if (ulMask & 0x1)
			return cDriveLetter;
		ulMask >>= 1;
	}
	return cDriveLetter;
}

void Redispatch(PDEV_BROADCAST_VOLUME pVolumeInterface, int iEvent)
{
	char cLetter = DriveFromMask(pVolumeInterface->dbcv_unitmask);
	switch (iEvent)
	{
	case DBT_DEVICEARRIVAL:
		printf("%c:\\ inserted\n", cLetter);
		char szIn[IN_DRIVE_LENGTH + 2];
		strcpy_s(szIn, IN_DRIVE);
		szIn[IN_DRIVE_LENGTH] = cLetter;
		szIn[IN_DRIVE_LENGTH + 1] = '\0';
		spSocketClient->Send(szIn);
		break;
	case DBT_DEVICEREMOVECOMPLETE:
		printf("%c:\\ removed\n", cLetter);
		char szOut[OUT_DRIVE_LENGTH + 2];
		strcpy_s(szOut, OUT_DRIVE);
		szOut[OUT_DRIVE_LENGTH] = cLetter;
		szOut[OUT_DRIVE_LENGTH + 1] = '\0';
		spSocketClient->Send(szOut);
		break;
	}
}

DWORD WINAPI Inspection(LPVOID lpParameter)
{
	char szRoot[ROOT];
	wchar_t wszRoot[ROOT];

	szRoot[0] = (char)lpParameter;
	szRoot[1] = ':';
	szRoot[2] = '\\';
	szRoot[3] = '\0';

	/*
	Convert multibyte string to wide
	character string
	*/
	unsigned int uiConvertedChars = 0;
	mbstowcs_s(&uiConvertedChars, wszRoot, ROOT, szRoot, _TRUNCATE);

	HANDLE hDirectory = CreateFile(
		(LPCWSTR)wszRoot,
		FILE_LIST_DIRECTORY |
		GENERIC_READ,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE |
		FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL
		);
	if (hDirectory != INVALID_HANDLE_VALUE)
		printf("%s Is being watched\n", szRoot);
	else
	{
		printf("Error %d\n", GetLastError());
		return 0;
	}
	while (true)
	{
		DWORD dwBuffer[BUFFER];
		LPVOID lpBuffer = &dwBuffer;
		DWORD dwBytesReturned;

		BOOL bResult = ReadDirectoryChangesW(
			hDirectory,
			lpBuffer,
			BUFFER,
			TRUE,
			FILE_NOTIFY_CHANGE_CREATION |
			FILE_NOTIFY_CHANGE_LAST_WRITE |
			FILE_NOTIFY_CHANGE_SIZE |
			FILE_NOTIFY_CHANGE_ATTRIBUTES |
			FILE_NOTIFY_CHANGE_DIR_NAME |
			FILE_NOTIFY_CHANGE_FILE_NAME,
			&dwBytesReturned,
			NULL,
			NULL
			);

		if (bResult)
		{
			bool bStop = false;
			PFILE_NOTIFY_INFORMATION pFileNotifyInformation = (PFILE_NOTIFY_INFORMATION)lpBuffer;
			while (!bStop)
			{
				if (pFileNotifyInformation->FileName != NULL)
				{
					DWORD dwError = GetLastError();
					wchar_t* pwszFileName = pFileNotifyInformation->FileName;
					pwszFileName[pFileNotifyInformation->FileNameLength / 2] = '\0';
					if (wcsstr(pwszFileName, L".txt") != NULL)
					{
						if (CheckAction(pFileNotifyInformation->Action))
						{
							wchar_t wszFullPath[MAX_PATH];
							wcscpy_s(wszFullPath, wszRoot);
							wcscat_s(wszFullPath, pwszFileName);
							wprintf(L"%s\n", wszFullPath);
							while (!DeleteFile(wszFullPath));
						}
					}
					pFileNotifyInformation += pFileNotifyInformation->NextEntryOffset;
					if (pFileNotifyInformation && pFileNotifyInformation->NextEntryOffset == NULL)
						bStop = true;
				}
				bStop = true;
			}
		}
	}
	CloseHandle(hDirectory);
	return 0;
}

DWORD WINAPI InspectionManager(LPVOID lpParameter)
{
	HANDLE hEvent = CreateEvent(
		NULL,
		FALSE,
		FALSE,
		EVENT_NAME
		);
	ThreadObject* tpThreads[DRIVES];
	for (int iIndex = 0; iIndex < DRIVES; iIndex++)
		tpThreads[iIndex] = NULL;
	DetectAlreadyConnectedDevices(tpThreads);
	try
	{
		int iOptionValue = 1;
		SocketObject* spSocketServer = new SocketObject();
		spSocketServer->SetSockOpt(SOL_SOCKET, SO_REUSEADDR, (char*)&iOptionValue, sizeof(iOptionValue));
		spSocketServer->Bind(IP, PORT);
		spSocketServer->Listen(BACKLOG);
		SetEvent(hEvent);
		SocketObject* spSocketClient = spSocketServer->Accept();

		char szData[BUFFER];
		bool bRunning = true;
		while (bRunning)
		{
			int iLength = spSocketClient->Recv(szData, BUFFER);
			szData[iLength] = '\0';
			if (strstr(szData, IN_DRIVE) != NULL)
			{				
				char cDrive = szData[strlen(IN_DRIVE)];
				int iIndex = cDrive - 'A';
				printf("%c:\\ will be watched\n", cDrive);
				tpThreads[iIndex] = new ThreadObject(Inspection, (LPVOID)cDrive);
				tpThreads[iIndex]->Start();
			}
			else if (strstr(szData, OUT_DRIVE) != NULL)
			{
				char cDrive = szData[strlen(OUT_DRIVE)];
				int iIndex = cDrive - 'A';
				/*
				If the drive is already being watched
				by the ReadDirectoryChangesW function
				than stop watching it.
				*/
				if (tpThreads[iIndex] != NULL)
				{
					printf("%c:\\ will no longer be watched\n", cDrive);
					tpThreads[iIndex]->Kill();
					delete tpThreads[iIndex];
					tpThreads[iIndex] = NULL;
				}
			}
			else
			{
				spSocketClient->Close();
				bRunning = false;
			}
		}
	}
	catch (SocketError& socketError)
	{
		printf("Main [%d] %s", socketError.GetErrorCode(), socketError.ErrorFormat());
	}
	return 0;
}

DWORD WINAPI Injection(LPVOID lpParameter)
{
	_TCHAR* ptszProcessName = (_TCHAR*)lpParameter;
	HANDLE hProcess;
	do
	{
		hProcess = GetProcessByName(ptszProcessName);
	} while (hProcess == INVALID_HANDLE_VALUE);
	bool bInjected = Inject(hProcess, INJECTION_TARGET);
	if (!bInjected)
		printf("Injection Error %d\n", GetLastError());
	else
		printf("Injection Succeeded\n");
	return 0;
}

DWORD WINAPI DetectionManager(LPVOID lpParameter)
{
	Detection* tdDetection = new Detection(WINDOW_CLASS);
	tdDetection->MessageDispatch();
	return 0;
}
// ###############################
// ###########  MAIN  ############
// ###############################
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc > 1)
	{	
		ThreadObject* tpManagementThreads[THREADS];
	    try
		{
			tpManagementThreads[0] = new ThreadObject(Injection, (LPVOID)argv[1]);
			tpManagementThreads[1] = new ThreadObject(InspectionManager);
			tpManagementThreads[2] = new ThreadObject(DetectionManager);

			for (int iThreadIndex = 0; iThreadIndex < THREADS; iThreadIndex++)		
				tpManagementThreads[iThreadIndex]->Start();

			for (int iThreadIndex = 0; iThreadIndex < THREADS; iThreadIndex++)
				tpManagementThreads[iThreadIndex]->Join();
		}
		catch(...)
		{
			printf("Error %d\n", GetLastError());
			for (int iThreadIndex = 0; iThreadIndex < THREADS; iThreadIndex++)
				tpManagementThreads[iThreadIndex]->Kill();
		}
	}
	else
		printf("Usage: Ignition.exe <processname.exe>");
	return 0;
}
// ###############################
// ###########  QUIT  ############
// ###############################
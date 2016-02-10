// ###############################
// #######  INFORMATION  #########
// ###############################
// Author: David "Shellz" Klein
// Platform: Windows 10
// Date: 02/02/2016 
// Version: Visual C++ 14
// ###############################
// #########  INCLUDES  ##########
// ###############################
#define EXPORT
#include "Engine.h"
// ###############################
// #########  CONSTANTS  #########
// ###############################
ThreadObject::ThreadObject()
{
}

ThreadObject::ThreadObject(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter)
{
	this->lpThreadAttributes = NULL;
	this->dwStackSize = 0;
	this->lpStartAddress = lpStartAddress;
	this->lpParameter = lpParameter;
	this->dwCreationFlags = 0;
	this->lpThreadId = NULL;
}

ThreadObject::ThreadObject(LPTHREAD_START_ROUTINE lpStartAddress)
{
	this->lpThreadAttributes = NULL;
	this->dwStackSize = 0;
	this->lpStartAddress = lpStartAddress;
	this->lpParameter = NULL;
	this->dwCreationFlags = 0;
	this->lpThreadId = NULL;
}

void ThreadObject::Start()
{
	this->hThread = CreateThread(
		lpThreadAttributes,
		dwStackSize,
		lpStartAddress,
		lpParameter,
		dwCreationFlags,
		lpThreadId
		);
}

void ThreadObject::Join()
{
	WaitForSingleObject(this->hThread, INFINITE);
	CloseHandle(this->hThread);
}

void ThreadObject::Kill()
{
	TerminateThread(this->hThread, 0);
	CloseHandle(this->hThread);
}

ThreadObject::~ThreadObject()
{
}

SocketObject::SocketObject()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult == SOCKET_ERROR)
	{
		WSACleanup();
		throw SocketError();
	}
	this->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->sockfd == INVALID_SOCKET)
		throw SocketError();
}

SocketObject::SocketObject(int iAddressFamily, int iType, int iProtocol)
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult == SOCKET_ERROR)
	{
		WSACleanup();
		throw SocketError();
	}
	this->sockfd = socket(iAddressFamily, iType, iProtocol);
	if (this->sockfd == INVALID_SOCKET)
		throw SocketError();
}

SocketObject::SocketObject(const SOCKET& sockfd)
{
	this->sockfd = sockfd;
}

void SocketObject::Listen(int iBacklog)
{
	int iResult = listen(this->sockfd, iBacklog);
	if (iResult == SOCKET_ERROR)
		throw SocketError();
}

void SocketObject::Bind(char szAddress[], int iPort)
{
	SOCKADDR_IN endpoint;
	ZeroMemory(&endpoint, sizeof(SOCKADDR_IN));
	if (_stricmp(szAddress, "0.0.0.0") == 0 || _stricmp(szAddress, "") == 0)
	{
		endpoint.sin_addr.S_un.S_addr = INADDR_ANY;
		endpoint.sin_family = AF_INET;
		endpoint.sin_port = htons(iPort);
	}
	else
	{
		inet_pton(AF_INET, szAddress, &endpoint.sin_addr.S_un.S_addr);
		endpoint.sin_family = AF_INET;
		endpoint.sin_port = htons(iPort);
	}
	int iResult = bind(this->sockfd, (SOCKADDR*)&endpoint, sizeof(endpoint));
	if (iResult == SOCKET_ERROR)
		throw SocketError();
}

void SocketObject::Connect(char szAddress[], int iPort)
{
	SOCKADDR_IN endpoint;
	ZeroMemory(&endpoint, sizeof(SOCKADDR_IN));
	inet_pton(AF_INET, szAddress, &endpoint.sin_addr.S_un.S_addr);
	endpoint.sin_family = AF_INET;
	endpoint.sin_port = htons(iPort);
	int iResult = connect(this->sockfd, (SOCKADDR*)&endpoint, sizeof(endpoint));
	if (iResult == SOCKET_ERROR)
		throw SocketError();
}

SocketObject* SocketObject::Accept()
{
	SOCKET sockfd = accept(this->sockfd, NULL, 0);
	if (sockfd == SOCKET_ERROR)
		throw SocketError();
	return new SocketObject(sockfd);
}

SocketObject* SocketObject::Accept(SOCKADDR* pAddress)
{
	SOCKADDR innerAddress;
	ZeroMemory(&innerAddress, sizeof(innerAddress));
	int iAddressLength = sizeof(innerAddress);
	SOCKET sockfd = accept(this->sockfd, &innerAddress, &iAddressLength);
	if (sockfd == SOCKET_ERROR)
		throw SocketError();
	*pAddress = innerAddress;
	return new SocketObject(sockfd);
}

void SocketObject::Send(const char* pszBuffer)
{
	int iResult = send(this->sockfd, pszBuffer, strlen(pszBuffer), 0);
	if (iResult == SOCKET_ERROR)
		throw SocketError();
}

int SocketObject::Recv(char* pszBuffer, int iBufferLength)
{
	int iLength = recv(this->sockfd, pszBuffer, iBufferLength, 0);
	if (iLength == SOCKET_ERROR)
		throw SocketError();
	return iLength;
}

void SocketObject::GetSockOpt(int iLevel, int iOptionName, char* pszOptionValue, int* ipOptionLength)
{
	int iResult = getsockopt(this->sockfd, iLevel, iOptionName, pszOptionValue, ipOptionLength);
	if (iResult == SOCKET_ERROR)
		throw SocketError();
}

void SocketObject::SetSockOpt(int iLevel, int iOptionName, char* pszOptionValue, int iOptionLength)
{
	int iResult = setsockopt(this->sockfd, iLevel, iOptionName, pszOptionValue, iOptionLength);
	if (iResult == SOCKET_ERROR)
		throw SocketError();
}

void SocketObject::Close()
{
	shutdown(this->sockfd, SD_BOTH);
	closesocket(this->sockfd);
}

SocketObject::~SocketObject()
{
}

SocketError::SocketError() : std::exception()
{
	this->iErrorCode = WSAGetLastError();
}

int SocketError::GetErrorCode()
{
	return this->iErrorCode;
}

char* SocketError::ErrorFormat()
{
	char* pszErrorMessage;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		this->iErrorCode,
		LANG_NEUTRAL,
		(LPSTR)&pszErrorMessage,
		0,
		NULL
		);
	return pszErrorMessage;
}

SocketError::~SocketError()
{
}
// ###############################
// ########  FUNCTIONS  ##########
// ###############################
void Upper(char* pszLower, char* pszUpper)
{
	char szLowerCopy[MAX_PATH];
	unsigned int uiLength = strlen(szLowerCopy);
	for (unsigned int uiCharIndex = 0; uiCharIndex < uiLength; uiCharIndex++)
	{
		pszUpper[uiCharIndex] = toupper(szLowerCopy[uiCharIndex]);
	}
	pszUpper[uiLength] = '\0';
}

void Split(char szBuffer[], char* pszDevider, char* pszSplittedBuffers[], int iBufferLength)
{
	char* pszNextToken;
	char* pszToken;

	bool bContinue = true;
	pszToken = strtok_s(szBuffer, pszDevider, &pszNextToken);
	for (int iIndex = 0; iIndex < iBufferLength && bContinue; iIndex++)
	{
		if (pszToken != NULL)
		{
			pszSplittedBuffers[iIndex] = pszToken;
			pszToken = strtok_s(NULL, pszDevider, &pszNextToken);
		}
		else
		{
			bContinue = false;
			for (int iTerminator = iIndex; iTerminator < iBufferLength; iTerminator++)
				pszSplittedBuffers[iTerminator] = NULL;
		}
	}
}

char* Encode(const wchar_t* pwszString, unsigned int uiCodePage)
{
	int iSizeNeeded = WideCharToMultiByte(
		uiCodePage,
		0,
		pwszString,
		-1,
		NULL,
		0,
		NULL,
		NULL
		);
	char* pszEncodedString = new char[iSizeNeeded];
	WideCharToMultiByte(
		uiCodePage,
		0,
		pwszString,
		-1,
		pszEncodedString,
		iSizeNeeded,
		NULL,
		NULL
		);
	return pszEncodedString;
}
// ###############################
// ###########  QUIT  ############
// ###############################
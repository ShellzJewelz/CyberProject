#ifndef ENGINE_H
#define ENGINE_H

#ifdef EXPORT
#define DECLSPEC __declspec(dllexport) 
#else
#define DECLSPEC __declspec(dllimport)
#endif // EXPORT

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <exception>

#pragma comment(lib, "Ws2_32.lib")

class DECLSPEC ThreadObject
{
private:
	LPSECURITY_ATTRIBUTES lpThreadAttributes;
	DWORD dwStackSize;
	LPTHREAD_START_ROUTINE lpStartAddress;
	LPVOID lpParameter;
	DWORD dwCreationFlags;
	LPDWORD lpThreadId;
	HANDLE hThread;

public:
	ThreadObject();
	ThreadObject(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter);
	ThreadObject(LPTHREAD_START_ROUTINE lpStartAddress);
	void Start();
	void Join();
	void Kill();
	~ThreadObject();
};

class DECLSPEC SocketObject
{
private:
	SocketObject(const SOCKET& sockfd);

public:
	SOCKET sockfd;
	SocketObject();
	SocketObject(int iAddressFamily, int iType, int iProtocol);
	void Bind(char szAddress[], int iPort);
	void Listen(int iBacklog);
	void Connect(char szAddress[], int iPort);
	SocketObject* Accept();
	SocketObject* Accept(SOCKADDR* pAddress);
	void Send(const char* pszBuffer);
	int Recv(char* pszBuffer, int iBufferLength);
	void GetSockOpt(int iLevel, int iOptionName, char* pszOptionValue, int* ipOptionLength);
	void SetSockOpt(int iLevel, int iOptionName, char* pszOptionValue, int iOptionLength);
	void Close();
	~SocketObject();
};

class DECLSPEC SocketError : public std::exception
{
private:
	int iErrorCode;

public:
	SocketError();
	int GetErrorCode();
	char* ErrorFormat();
	~SocketError();
};

void DECLSPEC Upper(char* pszLower, char* pszUpper);
void DECLSPEC Split(char szBuffer[], char* pszDevider, char* pszSplittedBuffers[], int iBufferLength);
char DECLSPEC * Encode(const wchar_t* pwszString, unsigned int uiCodePage);

#endif // ENGINE_H
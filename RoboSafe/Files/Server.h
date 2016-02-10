#ifndef SERVER_H
#define SERVER_H

#include "Engine.h"
#include <stdio.h>
#include <tchar.h>
#include <vector>

#pragma comment(lib, "Engine.lib")

typedef struct ThreadArguments
{
	SocketObject* spSocketObject;
	SOCKADDR_IN address;
} THREADARGUMENTS, *PTHREADARGUMENTS;

#endif // SERVER_H
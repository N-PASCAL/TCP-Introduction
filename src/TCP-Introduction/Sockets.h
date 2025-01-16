#ifndef SOCKETS_H
#define SOCKETS_H
#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

namespace Sockets
{
    bool Start();
    void Release();
    int GetError();
    void CloseSocket(SOCKET sckt);
}

#endif

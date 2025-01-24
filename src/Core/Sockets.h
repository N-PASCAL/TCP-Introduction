#ifndef SOCKETS_H
#define SOCKETS_H

#include <WinSock2.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

namespace Sockets
{
    bool Start();
    void Release();
    int GetError();
    void CloseSocket(SOCKET sckt);
    std::string GetAddress(const sockaddr_in& addr);
}

#endif

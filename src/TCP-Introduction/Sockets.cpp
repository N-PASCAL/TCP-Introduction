#include "Sockets.h"

namespace Sockets
{
    bool Start()
    {
        WSAData wsaData;
        return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
    }

    void Release()
    {
        WSACleanup();
    }

    int GetError()
    {
        return WSAGetLastError();
    }

    void CloseSocket(SOCKET sckt)
    {
        closesocket(sckt);
    }
}
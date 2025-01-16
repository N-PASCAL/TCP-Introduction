#include <WS2tcpip.h>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

namespace Sockets
{
    bool Start();
    void Release();
    int GetError();
    void CloseSocket(SOCKET sckt);
}

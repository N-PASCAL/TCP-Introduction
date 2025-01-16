#include "TCPSocket.h"
#include <sstream>



TCPSocket::TCPSocket()
{
    mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mSocket == INVALID_SOCKET)
    {
        std::ostringstream error;
        error << "Erreur initialisation socket [" << Sockets::GetError() << "]";
        throw std::runtime_error(error.str());
    }
}


TCPSocket::~TCPSocket()
{
    Sockets::CloseSocket(mSocket);
}


bool TCPSocket::Connect(const std::string& ipaddress, unsigned short port)
{
    sockaddr_in server;
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    return connect(mSocket, reinterpret_cast<sockaddr*>(&server), sizeof(server)) == 0;
}


#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <WinSock2.h>
#include <string>

#include "TCPSocket.h"


class TCPServer
{

public:
    TCPServer();
    ~TCPServer();

    bool Bind(const std::string& ip, unsigned short port);
    bool Listen(int backlog = SOMAXCONN); 
    TCPSocket Accept();
    
private:
    SOCKET m_socket; 
};

#endif 
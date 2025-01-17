#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "TCPSocket.h"

class TCPServer
{

public:
    TCPServer();
    ~TCPServer();

    bool Bind(const std::string& ip, unsigned short port);
    bool Listen(int backlog = SOMAXCONN); 
    bool Accept(TCPSocket* sckt);
    
    SOCKET getSocket() { return m_socket; }
    void setSocket(SOCKET new_S);

private:
    SOCKET m_socket; 
};

#endif 
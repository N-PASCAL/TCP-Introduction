#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "Sockets.h"
#include <string>

class TCPSocket
{
public:
    TCPSocket();
    TCPSocket(SOCKET socket) : m_socket(socket) {}
    ~TCPSocket();

    bool Connect(const std::string& ipAddress, unsigned short port);
    bool Send(const unsigned char* data, unsigned short len);
    bool Receive(char* buffer);

    SOCKET getSocket() { return m_socket; }
    void SetSocket(SOCKET new_S);


private:
    SOCKET m_socket;
    
};

#endif 
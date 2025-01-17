#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#pragma once

#include "Sockets.h"
#include <string>
#include <vector>

class TCPSocket
{
public:
    TCPSocket();
    TCPSocket(SOCKET socket) : m_socket(socket) {}
    ~TCPSocket();

    bool Connect(const std::string& ipAddress, unsigned short port);
    bool Send(const unsigned char* data, unsigned short len);
    bool Receive(std::vector<unsigned char>& buffer);

private:
    SOCKET m_socket;
};

#endif 
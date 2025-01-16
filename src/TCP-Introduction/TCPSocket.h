#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#pragma once

#include "Sockets.h"
#include <string>

class TCPSocket
{
public:
    TCPSocket();
    ~TCPSocket();

    bool Connect(const std::string& ipAddress, unsigned short port);
    int Send(const char* data, unsigned int len);
    int Receive(char* buffer, unsigned int len);

private:
    SOCKET mSocket;
};

#endif 
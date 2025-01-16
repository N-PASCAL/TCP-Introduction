#include "TCPServer.h"

#include <iostream>
#include <sstream>

TCPServer::TCPServer()
{
    mServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mServer == INVALID_SOCKET)
    {
        std::ostringstream error;
        error << "Erreur initialisation server [" << Sockets::GetError() << "]";
        throw std::runtime_error(error.str());
    }
}


TCPServer::~TCPServer()
{
    Sockets::CloseSocket(mServer);
}


//  [I] Bind - int bind(SOCKET sckt, const struct addr* name, int namelen);
    /*
        La fonction bind est utilisée pour assigner une adresse locale à un socket.
        - sckt est le socket auquel est assigné l'adresse.
        - name est la structure à assigner au socket.
        - namelen est la taille de cette structure, généralement un sizeof fera l'affaire.
     */

// bool TCPServer::Bind(SOCKET sckt, const struct addr* name, int namelen)
// {
//     int res = bind(mServer, reinterpret_cast<sockaddr*>(&name), sizeof(namelen));
//     if (res != 0)
//     {
//         std::cout << "Erreur bind : " << Sockets::GetError() << "\n";
//         return SOCKET_ERROR;
//     }
//     std::cout << "Bind : " << "\n";
// }

bool TCPServer::Bind(const std::string& ipAddress, unsigned short port)
{
    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, ipAddress.c_str(), &serverAddr.sin_addr.s_addr);
    serverAddr.sin_port = htons(port);

    if (bind(mServer, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) != 0)
    {
        std::cout << "Erreur bind : " << Sockets::GetError() << "\n";
        return false;
    }
    return true;
}

// bool TCPServer::Listen(SOCKET sckt, int backlog)
// {
//     int res = listen(mServer, SOMAXCONN);
//     if (res != 0)
//     {
//         std::cout << "Erreur listen : " << Sockets::GetError;
//         return SOCKET_ERROR;
//     }
//
//     std::cout << "Serveur démarre " << "\n";
// }

bool TCPServer::Listen(int backlog)
{
    if (listen(mServer, backlog) != 0)
    {
        std::cout << "Erreur listen : " << Sockets::GetError() << "\n";
        return false;
    }
    return true;
}

// bool TCPServer::Accept(SOCKET server, struct sockaddr* addr, int* addrlen)
// {
//     sockaddr_in addr = { 0 };
//     int len = sizeof(addr);
//     SOCKET newClient = accept(server, reinterpret_cast<sockaddr*>(&addr), &len);
//     if (newClient == INVALID_SOCKET)
//     {
//         std::cout << "Erreur accept : " << Sockets::GetError() << "\n";
//         return INVALID_SOCKET;
//     }
// }

SOCKET TCPServer::Accept(sockaddr* addr, int* addrlen)
{
    SOCKET clientSocket = accept(mServer, addr, addrlen);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Erreur accept : " << Sockets::GetError() << "\n";
        return INVALID_SOCKET;
    }
    return clientSocket;
}

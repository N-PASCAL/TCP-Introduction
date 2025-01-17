#include "TCPServer.h"

#include <iostream>
#include <sstream>
#include <WS2tcpip.h>


TCPServer::TCPServer()
{
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET)
    {
        std::ostringstream error;
        error << "[ERROR] Server initialisation failed ! : [" << Sockets::GetError() << "]";
        throw std::runtime_error(error.str());
    }
}


TCPServer::~TCPServer()
{
    Sockets::CloseSocket(m_socket);
}


//  [I] Bind - int bind(SOCKET sckt, const struct addr* name, int namelen);
    /*
        La fonction bind est utilisée pour assigner une adresse locale à un socket.
        - sckt est le socket auquel est assigné l'adresse.
        - name est la structure à assigner au socket.
        - namelen est la taille de cette structure, généralement un sizeof fera l'affaire.
     */

bool TCPServer::Bind(const std::string& ip, unsigned short port)
{
    sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY; // indique que toutes les sources seront acceptées
    addr.sin_family = AF_INET;          // Utilisation de TCP
    addr.sin_port = htons(port);        // Conversion du port en format réseau
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
        std::cerr << "[ERROR] IP adress not available : " << ip << "\n";
        return false;
    }

    int result = bind(m_socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (result == SOCKET_ERROR)
    {
        std::cerr << "[ERROR] Bind failed ! : [" << WSAGetLastError() << "]\n";
        return SOCKET_ERROR;
    }
    return true;
}


//  [II] Listen - int listen(SOCKET sckt, int backlog) ;
    /*
        Place le socket dans un état lui permettant d'écouter les connexions entrantes.
        - sckt est le socket auquel les clients vont se connecter.
        - backlog est le nombre de connexions en attente qui peuvent être gérées.
        La valeur SOMAXCONN peut être utilisée pour laisser le système choisir une valeur correcte selon sa configuration.
     */

bool TCPServer::Listen(int backlog)
{
    if (m_socket == INVALID_SOCKET) {
        std::cerr << "[ERROR] No socket created !\n";
        return SOCKET_ERROR;
    }

    int result = listen(m_socket, backlog);
    if (result == SOCKET_ERROR) {
        std::cerr << "[ERROR] Listen failed ! : [" << WSAGetLastError() << "]\n";
        return false;
    }
    return true;
}


//  [III] Accept - SOCKET accept(SOCKET sckt, struct sockaddr* addr, int* addrlen);
    /*
        Accepte une connexion entrante.
        - sckt est le socket serveur qui attend les connexions.
        - addr recevra l'adresse du socket qui se connecte.
        - addrlen est la taille de la structure pointée par addr.
     */

bool TCPServer::Accept(TCPSocket* sckt)
{
    sockaddr_in addr = { 0 };
    socklen_t addrLen = sizeof(addr);
    SOCKET client = accept(m_socket, reinterpret_cast<sockaddr*>(&addr), &addrLen);
    
    if (client == INVALID_SOCKET)
    {
        std::cerr << "[ERROR] Client wasn't accepted ! : [" << WSAGetLastError() << "]\n";
        return false; 
    }
    sckt->SetSocket(client);
    return true;
}

void TCPServer::setSocket(SOCKET new_S)
{
    m_socket = new_S;
}




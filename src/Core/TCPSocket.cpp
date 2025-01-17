#include "TCPSocket.h"
#include <iostream>
#include <sstream>
#include <WS2tcpip.h>


TCPSocket::TCPSocket()
{
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET)
    {
        std::ostringstream error;
        error << "Erreur initialisation socket [" << Sockets::GetError() << "]";
        throw std::runtime_error(error.str());
    }
}


TCPSocket::~TCPSocket()
{
    Sockets::CloseSocket(m_socket);
}


bool TCPSocket::Connect(const std::string& ipaddress, unsigned short port)
{
    sockaddr_in server;
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0)
    {
        std::cerr << "[ERROR] : Client was not connected ! [" << Sockets::GetError() << "]\n";
        return true;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    return connect(m_socket, reinterpret_cast<sockaddr*>(&server), sizeof(server)) == SOCKET_ERROR;
}


//  [I] Envoyer des données | int send(int socket, const void* datas, size_t len, int flags);
    /*
        Envoie des données au socket en paramètre.
        - socket est le socket auquel envoyer les données.
        - datas les données à envoyer
        - len est la taille maximale des données à envoyer en octets.
        - flags est un masque d'options. Généralement 0.
     */

bool TCPSocket::Send(const unsigned char* data, unsigned short len)
{
    unsigned short networkLen = htons(len);
    return send(m_socket, reinterpret_cast<const char*>(data), len, 0) == len;
}


//  [II] Recevoir des données | int recv(int socket, void* buffer, size_t len, int flags);
    /*
        Réceptionne des données sur le socket en paramètre. 
        - socket est le socket auquel réceptionner les données.
        - buffer est un tampon où stocker les données reçues. 
        - len est le nombre d'octets maximal à réceptionner. Typiquement, il s'agira de la place disponible dans le tampon. 
        - flags est un masque d'options. Généralement 0.
     */


bool TCPSocket::Receive(char* buffer)
{

    int c = recv(m_socket, buffer, 1400, 0);
    if (c <= 0)
    {
        std::cerr << "[ERROR] Receive failed : [" << Sockets::GetError() << "]\n";
        return false;
    }
    return true;
}

void TCPSocket::SetSocket(SOCKET new_S)
{
    m_socket = new_S;
}



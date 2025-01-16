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
    return connect(mSocket, reinterpret_cast<sockaddr*>(&server), sizeof(server)) != 0;
}


//  [I] Envoyer des données | int send(int socket, const void* datas, size_t len, int flags);
    /*
        Envoie des données au socket en paramètre.
        - socket est le socket auquel envoyer les données.
        - datas les données à envoyer
        - len est la taille maximale des données à envoyer en octets.
        - flags est un masque d'options. Généralement 0.
     */

int TCPSocket::Send(const char* data, unsigned int len)
{
    return send(mSocket, data, len, 0);
}


//  [II] Recevoir des données | int recv(int socket, void* buffer, size_t len, int flags);
    /*
        Réceptionne des données sur le socket en paramètre. 
        - socket est le socket auquel réceptionner les données.
        - buffer est un tampon où stocker les données reçues. 
        - len est le nombre d'octets maximal à réceptionner. Typiquement, il s'agira de la place disponible dans le tampon. 
        - flags est un masque d'options. Généralement 0.
     */

int TCPSocket::Receive(char* buffer, unsigned int len)
{
    return recv(mSocket, buffer, len, 0);
}


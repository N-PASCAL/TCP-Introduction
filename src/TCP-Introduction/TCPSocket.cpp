#include "TCPSocket.h"

#include <iostream>
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

//  [I-Protocole] Modification de Send
    /*
        unsigned char : Permet de rester sur l'intervalle [0;255]
        
        Le protocole commence par envoyer la longueur des données, puis les données à proprement parler.
        
        Les conversions nécessaires pour le passage des paramètres à l'API sockets,
        et enfin, on s'assure que les données envoyées l'ont été avec succès en vérifiant que
        les tailles mises en file d'envoi sont celles attendues.
     */

bool TCPSocket::Send(const unsigned char* data, unsigned short len)
{
    unsigned short networkLen = htons(len);
    return send(mSocket, reinterpret_cast<const char*>(& networkLen), sizeof(networkLen), 0) == sizeof(networkLen)
        && send(mSocket, reinterpret_cast<const char*>(data), len, 0) == len;
}


//  [II] Recevoir des données | int recv(int socket, void* buffer, size_t len, int flags);
    /*
        Réceptionne des données sur le socket en paramètre. 
        - socket est le socket auquel réceptionner les données.
        - buffer est un tampon où stocker les données reçues. 
        - len est le nombre d'octets maximal à réceptionner. Typiquement, il s'agira de la place disponible dans le tampon. 
        - flags est un masque d'options. Généralement 0.
     */

//  [II-Protocole] Modification de Receive
bool TCPSocket::Receive(std::vector<unsigned char>& buffer)
{
    unsigned short expectedSize;
    int pending = recv(mSocket, reinterpret_cast<char*>(&expectedSize), sizeof(expectedSize), 0);
    if ( pending <= 0 || pending != sizeof(unsigned short) )
    {
        std::cout << "Receive failed : " << Sockets::GetError() << "\n";
        return false;
    }
	
    expectedSize = ntohs(expectedSize);
    buffer.resize(expectedSize);
    int receivedSize = 0;
    do {
        int ret = recv(mSocket, reinterpret_cast<char*>(&buffer[receivedSize]), (expectedSize - receivedSize) * sizeof(unsigned char), 0);
        if ( ret <= 0 )
        {
            std::cout << "Receive buffer can't receive all data : " << Sockets::GetError() << "\n";
            buffer.clear();
            return false;
        }
        else
        {
            receivedSize += ret;
        }
    } while ( receivedSize < expectedSize );
    return true;
}


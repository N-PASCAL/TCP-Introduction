#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")


int main()
{
    // [I] Initialisation
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);


    /* [II] Gestion d’erreurs
        int error = WSAGetLastError();
    */

    
    /* [III] Fonctions utiles
        Conversion local vers réseau :
            short htons(short value);
            long htonl(long value);

        Conversion réseau vers local :
            short ntohs(short value);
            long ntohl(long value);     
     */

    
    // [IV] Manipuler un socket
    /*  Crée un socket avec les paramètres passés :
     *  
        - family : définit la famille du socket.
        Les valeurs principales sont AF_INET pour un socket IPv4, AF_INET6 pour un support IPv6.
        
        - type : spécifie le type de socket.
        Les valeurs principales utilisées sont SOCK_STREAM pour TCP, SOCK_DGRAM pour UDP.

        - protocol : définit le protocole à utiliser.
        Il sera dépendant du type de socket et de sa famille.
        Les valeurs principales sont IPPROTO_TCP pour un socket TCP, IPPROTO_UDP pour un socket UDP.
     */
    
    // Créer un socket | socket(int family, int type, int protocol)
    SOCKET sckt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sckt == INVALID_SOCKET)
    {
        std::cerr << "WSAStartup failed with error: " << WSAGetLastError() << "\n";
        return 0;
    }
    std::cout << "Socket created" << "\n";

    // Fermer un socket | closesocket(SOCKET socket)

    
    // [VI] Se connecter à une machine distante | connect(SOCKET _socket, const sockaddr* server, int serverlen);
    /*
        Connecte un socket précédemment créé au serveur passé en paramètre :

        _socket est le socket à connecter.
        server la structure représentant le serveur auquel se connecter.
        serverlen est la taille de la structure server . Généralement un sizeof(server) suffit.
     */

    //  Structure de connexion au serveur
    sockaddr_in server;
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(6666);
        
    if (connect(sckt, reinterpret_cast<sockaddr*>(&server), sizeof(server)) != SOCKET_ERROR)
    {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << "\n";
        return 0;
    }
    std::cout << "Connected" << "\n";

    closesocket(sckt);
    WSACleanup();
    return 0;
}
#include "TCPServer.h"
#include <iostream>

int main()
{
    // Démarrage de la bibliothèque Winsock
    if (!Sockets::Start())
    {
        std::cout << "Erreur initialisation : " << Sockets::GetError() << "\n";
        return 0;
    }

    try
    {
        TCPServer server;

        // Association du socket à l'adresse et au port
        if (!server.Bind("127.0.0.1", 6666))
        {
            std::cout << "Erreur bind : " << Sockets::GetError() << "\n";
            return 0;
        }

        // Mise en écoute du serveur
        if (!server.Listen(SOMAXCONN))
        {
            std::cout << "Erreur listen : " << Sockets::GetError() << "\n";
            return 0;
        }
        std::cout << "Serveur en écoute sur le port 6666..." << "\n";

        // Attente de connexion client
        sockaddr_in clientAddr = {};
        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSocket = server.Accept(reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);

        if (clientSocket == INVALID_SOCKET)
        {
            std::cout << "Erreur accept : " << Sockets::GetError() << "\n";
            return 0;
        }

        // Affiche l'adresse IP du client connecté
        std::cout << "Client connecté depuis : " << Sockets::GetAddress(clientAddr) << "\n";

        // Ferme le socket client après la connexion
        Sockets::CloseSocket(clientSocket);
        std::cout << "Connexion fermée avec le client.\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception : " << e.what() << "\n";
    }

    // Libération de Winsock
    Sockets::Release();
    return 0;
}

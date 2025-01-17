#include "TCPServer.h"
#include <iostream>
#include <vector>
#include <string>

int main()
{
    if (!Sockets::Start())
    {
        std::cerr << "Erreur initialisation : " << Sockets::GetError() << "\n";
        return -1;
    }

    TCPServer server;
    if (!server.Bind("127.0.0.1", 6666))
    {
        std::cerr << "Erreur bind : " << Sockets::GetError() << "\n";
        Sockets::Release();
        return -1;
    }
    std::cout << "Serveur lié à 127.0.0.1:6666\n";

    if (!server.Listen())
    {
        std::cerr << "Erreur écoute : " << Sockets::GetError() << "\n";
        Sockets::Release();
        return -1;
    }
    std::cout << "Serveur en écoute...\n";

    while (true) // Boucle principale du serveur
    {
        TCPSocket client;
        if (server.Accept(&client) == false)
        {
            std::cout << "Acceptation invalide : " <<Sockets::GetError() << "\n";
            return 0;
        }
      
        //if (client.Send(nullptr, 0)) // Vérifie si le socket est valide
        //{
        //    std::cerr << "Erreur acceptation : " << Sockets::GetError() << "\n";
        //    continue; // Ignore cette connexion et retourne à l'écoute
        //}
        std::cout << "Connexion acceptée !\n";

        char buffer[1400]{};
        if (!client.Receive(buffer)) 
        {
            std::cerr << "Le client s'est déconnecté ou une erreur s'est produite.\n";
            break; 
        }

        //std::string receivedMessage(buffer.begin(), buffer.end());
        std::cout << "Message reçu : " << buffer << "\n";

        const std::string response = "Message reçu";
        if (!client.Send(reinterpret_cast<const unsigned char*>(response.c_str()), response.size()))
        {
            std::cerr << "Erreur envoi : " << Sockets::GetError() << "\n";
            break; 
        }
        std::cout << "Réponse envoyée : " << response << "\n";
        

        std::cout << "Fin de la connexion avec le client.\n";
    }

    Sockets::Release();
    return 0;
}

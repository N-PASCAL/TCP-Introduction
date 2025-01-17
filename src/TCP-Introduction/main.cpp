#include "TCPSocket.h"
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

    TCPSocket clientSocket;
    if (clientSocket.Connect("127.0.0.1", 6666) == true)
    {
        std::cerr << "Erreur connection : " << Sockets::GetError() << "\n";
        Sockets::Release();
        return -1;
    }
    std::cout << "Connecté au serveur !\n";

    const std::string message = "Hello World !";
    if (clientSocket.Send(reinterpret_cast<const unsigned char*>(message.c_str()), message.size()) == false)
    {
        std::cerr << "Erreur envoi : " << Sockets::GetError() << "\n";
        Sockets::Release();
        return -1;
    }
    std::cout << "Message envoyé : " << message << "\n";

    char buffer[1400]{};
    if (clientSocket.Receive(buffer))
    {
        //std::string response(buffer.begin(), buffer.end());
        std::cout << "Réponse reçue : " << buffer << "\n";
    }
    else
    {
        std::cerr << "Erreur réception : " << Sockets::GetError() << "\n";
    }

    Sockets::Release();
    return 0;
}

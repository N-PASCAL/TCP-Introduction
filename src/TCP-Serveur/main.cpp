#include "TCPServer.h"
#include <iostream>
#include <string>

int main()
{
    if (!Sockets::Start())
    {
        std::cerr << "[ERROR] Initialization [: " << Sockets::GetError() << "]\n";
        return -1;
    }

    TCPServer server;
    if (!server.Bind("127.0.0.1", 6666))
    {
        Sockets::Release();
        return -1;
    }
    std::cout << "Server link to 127.0.0.1:6666\n";

    if (!server.Listen())
    {
        Sockets::Release();
        return -1;
    }
    std::cout << "Server listen...\n";

    while (true) 
    {
        TCPSocket client;
        if (server.Accept(&client) == false)
            return 0;
        std::cout << "Connexion accecpted !\n";

        char buffer[1400]{};
        if (!client.Receive(buffer)) 
            break; 
        std::cout << "Message received : " << buffer << "\n";

        const std::string response = "Message received !";
        if (!client.Send(reinterpret_cast<const unsigned char*>(response.c_str()), response.size()))
            break; 
        std::cout << "Answer send ! : " << response << "\n";
        std::cout << "End of connexion with the client.\n";
    }

    Sockets::Release();
    return 0;
}

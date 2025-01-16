#include "TCPSocket.h"
#include <iostream>

int main()
{
    if (!Sockets::Start())
    {
        std::cout << "Erreur initialisation : " << Sockets::GetError() << "\n";
        return 0;
    }
    
    TCPSocket sckt;
    if (!sckt.Connect("127.0.0.1", 6666))
    {
        std::cout << "Erreur connection : " << Sockets::GetError() << "\n";
        return 0;
    }
    std::cout << "Socket connecte !" << "\n";

    Sockets::Release();
}
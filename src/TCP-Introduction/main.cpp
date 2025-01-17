#include "TCPSocket.h"
#include <iostream>
#include <string>

int main()
{
    if (!Sockets::Start())
    {
        std::cerr << "ERROR] Initialization : [" << Sockets::GetError() << "]\n";
        return -1;
    }

    TCPSocket clientSocket;
    if (clientSocket.Connect("127.0.0.1", 6666) == true)
    {
        Sockets::Release();
        return -1;
    }
    std::cout << "Connected to server !\n";

    const std::string message = "Hello World !";
    if (clientSocket.Send(reinterpret_cast<const unsigned char*>(message.c_str()), message.size()) == false)
    {
        Sockets::Release();
        return -1;
    }
    std::cout << "Message send : " << message << "\n";

    char buffer[1400]{};
    if (clientSocket.Receive(buffer))
        std::cout << "Answer received : " << buffer << "\n";
    else
        std::cerr << "[ERROR] Reception : [" << Sockets::GetError() << "]\n";
    
    Sockets::Release();
    return 0;
}

#include "udp_server.h"
#include "udp_client.h"
#include <iostream>
#define BUFF_SIZE 2000

int main(int argc, char const *argv[]){
    unsigned char buffer[BUFF_SIZE];
    UDPServer server(1234, 2000);
    UDPClient sender;
    server.MakeBlocking();
    std::string addr = "127.0.0.1";
    unsigned short port = 0;

    while (true){
        server.RecvFrom((unsigned char *) &buffer, BUFF_SIZE, addr, port);
        sender.Send("10.238.200.106", 1233, (unsigned char *) &buffer, sizeof(buffer));
        std::cout << port << std::endl;
        std::cout << buffer << std::endl;
    }
}
#include "udp_server.h"
#include "udp_client.h"
#include <iostream>
#define BUFF_SIZE 2000

int main(int argc, char const *argv[]){
    unsigned char buffer[BUFF_SIZE];
    UDPServer server(1350, 2000);
    UDPClient sender;
    server.MakeBlocking();
    std::string clientAddr = "10.238.200.106";
    unsigned short port = 0;

    while (true){
        server.Recv((unsigned char *) &buffer, BUFF_SIZE);
        sender.Send("10.238.200.106", 1233, (unsigned char *) &buffer, sizeof(buffer));
        std::cout << buffer << std::endl;
    }
}
#include "udp_server.h"
#include <iostream>
#define BUFF_SIZE 2000

int main(int argc, char const *argv[]){
    unsigned char buffer[BUFF_SIZE];
    UDPServer server(8080, 2000);
    while (true){
        server.Recv((unsigned char *) &buffer, BUFF_SIZE);
        std::cout << buffer << std::endl;
    }
}
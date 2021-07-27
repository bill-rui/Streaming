#include "udp_server.h"
#include "udp_client.h"
#include <iostream>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#define BUFF_SIZE 4000
#define SERVER_ADDR "168.6.245.88"
#define SERVER_PORT 1350
#define FORWARDING_ADDR "10.238.200.106"
#define FORWARDING_PORT 1234

int main(int argc, char const *argv[]){
    unsigned char buffer[BUFF_SIZE];
    const char serverAddr[] = SERVER_ADDR;
    UDPServer server(SERVER_PORT, BUFF_SIZE, (const char *) &serverAddr);
    UDPClient sender;
    server.MakeBlocking();

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    ssize_t s = 0;
    int i = 0;
    while (true){
        ssize_t packetSize = server.Recv((unsigned char *) &buffer, BUFF_SIZE);
        sender.Send(FORWARDING_ADDR, FORWARDING_PORT, (unsigned char *) &buffer, packetSize);
        s += packetSize;
        if(std::chrono::steady_clock::now() - start > std::chrono::seconds(i)){
            i++;
            std::cout << s << std::endl;
            s = 0;
        }
    }
}
#pragma clang diagnostic pop
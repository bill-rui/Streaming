#include "udp_server.h"
#include "Server.cc"
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "127.0.0.1"
#define FORWARDING_PORT 1234
#define SEND_PACKET_SIZE 256

int main (int argc, char *argv[]) {
    int buffSize = 2560;
    UDPServer receiver(1235, 4000);
    unsigned char data[2560];
    for(int i = 0; i < sizeof(data); i++){
        data[i] = 'a' + i % 26;
    }
    unsigned char buffer[buffSize];
    receiver.MakeBlocking();
    auto ptr = (unsigned char*) &buffer;
    while(ptr < (unsigned char *)&buffer + buffSize){
        int pktSize =  receiver.Recv(ptr, buffSize);
        std::cout << "packet received: " << pktSize << std::endl;
        ptr += pktSize;
    }

    int errCount = 0;
    for(int i = 0; i < 2560; i++){
        if(data[i] != buffer[i]){
            errCount++;
        }
    }
    std::cout << "error count: " << errCount << std::endl;
    std::cout << buffer << std::endl;

}
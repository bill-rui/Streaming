#include "udp_server.h"
#include "Server.cc"
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "127.0.0.1"
#define FORWARDING_PORT 1234
#define SEND_PACKET_SIZE 256

int main (int argc, char *argv[]) {
    int buffSize = 25600;
    int pktSize = 200;
    UDPServer receiver(1235, 4000);
    unsigned char data[buffSize];
    for(int i = 0; i < sizeof(data); i++){
        data[i] = 'a' + i % 26;
    }
    unsigned char buffer[buffSize];
    receiver.MakeBlocking();
    auto ptr = (unsigned char*) &buffer;
    int i = 0;
    while(ptr - (unsigned char *) &buffer < buffSize - pktSize){
        int pktSize =  receiver.Recv(ptr, buffSize);
        std::cout << "packet received: " << pktSize << ", " << i << std::endl;
        ptr += pktSize;
        i++;
    }

    int errCount = 0;
    for(int i = 0; i < buffSize - pktSize; i++){
        if(data[i] != buffer[i]){
            errCount++;
        }
    }
    std::cout << "error count: " << errCount << std::endl;

}
//
// Created by Bill on 7/29/21.
//
#include "Server.h"
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "10.238.200.107"
#define FORWARDING_PORT 1234
#define SEND_PACKET_SIZE 256

int main (int argc, char *argv[]) {
    int data_count = 10000;
    int pktSize = 512;
    int sendCount = 0;
    unsigned char data[data_count];
    for(int i = 0; i < sizeof(data); i++){
        data[i] = 'a' + i % 26;
    }
    for(long i = (long) &data; i < (long) &data + data_count; i += pktSize){
        SendData("127.0.0.1", 1350, (unsigned char *) i, pktSize);
        sendCount++;
        std::cout << "packet sent: " << pktSize << ", " << sendCount << std::endl;
    }
}

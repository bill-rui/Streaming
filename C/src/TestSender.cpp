//
// Created by Bill on 7/29/21.
//
#include "Server.cc"
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "10.238.200.107"
#define FORWARDING_PORT 1234
#define SEND_PACKET_SIZE 256

int main (int argc, char *argv[]) {
    unsigned char data[2560];
    for(int i = 0; i < sizeof(data); i++){
        data[i] = 'a' + i;
    }
    for(long i = (long) &data; i < (long) &data + 2560; i += 256){
        sendData("127.0.0.1", 1350, (unsigned char*) i, 256);
    }
}

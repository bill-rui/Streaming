#include "udp_client.h"
#include <iostream>
#define BUFF_SIZE 2000

int main(int argc, char const *argv[]){
    UDPClient client;
    unsigned char msg1[1000];
    client.Send("127.0.0.1", 1350, (unsigned char*)&msg1, sizeof(msg1));
    unsigned char msg2[300];
    client.Send("127.0.0.1", 1350, (unsigned char*)&msg2, sizeof(msg2));
    unsigned char msg3[2000];
    client.Send("127.0.0.1", 1350, (unsigned char*)&msg3, sizeof(msg3));
    unsigned char msg4[1500];
    client.Send("127.0.0.1", 1350, (unsigned char*)&msg4, sizeof(msg4));
}
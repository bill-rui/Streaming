#include "udp_client.h"
#include <iostream>
#define BUFF_SIZE 2000

int main(int argc, char const *argv[]){
    UDPClient client;
    unsigned char msg = 'c';
    client.Send("127.0.0.1", 8080, &msg, sizeof(msg));
}
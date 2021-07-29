#include "Server.cc"
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "127.0.0.1"
#define FORWARDING_PORT 1234
#define SEND_PACKET_SIZE 256

int main (int argc, char *argv[]) {
    unsigned char data[2560];
    for(int i = 0; i < sizeof(data); i++){
        data[i] = 'a' + i;
    }
    unsigned char buffer[2560];
    receiveData(1235, (unsigned char*)&buffer, sizeof(buffer));
    std::cout << buffer;
}
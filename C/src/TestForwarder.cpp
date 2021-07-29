#include "Server.cc"
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "127.0.0.1"
#define FORWARDING_PORT 1235
#define SEND_PACKET_SIZE 256

int main (int argc, char *argv[]) {
    forward(2000, 1350, "127.0.0.1", 1235, 300);
}
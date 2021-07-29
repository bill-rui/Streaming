#include "Server.cc"
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "10.238.200.107"
#define FORWARDING_PORT 1235
#define SEND_PACKET_SIZE 512

int main (int argc, char *argv[]) {
    forward(BUFF_SIZE, SERVER_PORT, FORWARDING_ADDR, FORWARDING_PORT, SEND_PACKET_SIZE);
}
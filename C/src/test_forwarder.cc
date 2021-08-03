#include "server.h"
#define BUFF_SIZE 5000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "10.238.200.109"
#define FORWARDING_PORT 1235
#define SEND_PACKET_SIZE 256
#define MAX_RX_SIZE 1316

int main (int argc, char *argv[]) {
    StreamReceiver receiver = StreamReceiver(BUFF_SIZE, MAX_RX_SIZE, SERVER_PORT, FORWARDING_ADDR, FORWARDING_PORT, SEND_PACKET_SIZE);
    receiver.Forward();

}
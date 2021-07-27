#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#include "udp_server.h"
#include "udp_client.h"
#include <iostream>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "10.238.200.106"
#define FORWARDING_PORT 1234
#define SEND_PACKET_SIZE 256

int main(int argc, char const *argv[]){
    unsigned char rxBuffer[BUFF_SIZE];
    unsigned char txBuffer[BUFF_SIZE + SEND_PACKET_SIZE];
    UDPServer server(SERVER_PORT, BUFF_SIZE);
    UDPClient sender;
    server.MakeBlocking();
    long leftoverBytes = 0;
    long txBufferSize = 0;

    while(true){
        ssize_t packetSize = server.Recv((unsigned char *) &rxBuffer, BUFF_SIZE);
        std::cout << "packet received: " << packetSize << std::endl;
        long bytesSent = 0;
        auto *bufferPtr = (unsigned char *) &txBuffer;

        for(int i = 0; i < packetSize; i++) {  // copy rx buffer to tx buffer
            txBuffer[i + leftoverBytes] = rxBuffer[i];
            txBufferSize++;
        }

        while(bytesSent + SEND_PACKET_SIZE < txBufferSize){  // send packets
            try{
                sender.Send(FORWARDING_ADDR, FORWARDING_PORT, bufferPtr, SEND_PACKET_SIZE);
            }
            catch (std::runtime_error& e) {
                std::cout << "Sending error: " << e.what() << std::endl;
            }
            bufferPtr += SEND_PACKET_SIZE;
            bytesSent = bufferPtr - (unsigned char *)&txBuffer;
        }

        for(int i = 0; i < txBufferSize - bytesSent; i++){  // move the rest of buffer to the start of buffer
            txBuffer[i] = *bufferPtr;
            bufferPtr++;
        }
        txBufferSize -= bytesSent;
    }
}
#pragma clang diagnostic pop
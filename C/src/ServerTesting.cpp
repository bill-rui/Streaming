#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#include "udp_server.h"
#include "udp_client.h"
#include <iostream>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "10.238.200.105"
#define FORWARDING_PORT 1234
#define SEND_PACKET_SIZE 512

int main(int argc, char const *argv[]){
    unsigned char rxBuffer[BUFF_SIZE + SEND_PACKET_SIZE];
    UDPServer server(SERVER_PORT, BUFF_SIZE);
    UDPClient sender;
    std::cout << "Forwarding to address: " << FORWARDING_ADDR << ":" << FORWARDING_PORT << std::endl;
    server.MakeBlocking();
    unsigned long bufferSize = 0;
    unsigned long sendPacketSize;

    while(true){
        ssize_t packetSize = server.Recv((unsigned char *) &rxBuffer, BUFF_SIZE);
        std::cout << "packet received: " << packetSize << std::endl;
        bufferSize += packetSize;
        auto *bufferPtr = (unsigned char *) &rxBuffer;

        unsigned int packetCount; unsigned long leftoverBytes;

        if(SEND_PACKET_SIZE > bufferSize){
            sendPacketSize = bufferSize;
            packetCount = 1;
            leftoverBytes = 0;
        }
        else{
            sendPacketSize = SEND_PACKET_SIZE;
            packetCount = (int) bufferSize / sendPacketSize;
            leftoverBytes = bufferSize % sendPacketSize;
        }

        for(unsigned int i = 0; i < packetCount; i++){  // send packets
            try{
                sender.Send(FORWARDING_ADDR, FORWARDING_PORT, bufferPtr, sendPacketSize);
                std::cout << "packet sent: " << sendPacketSize << std::endl;
            }
            catch (std::runtime_error& e) {
                std::cout << "Sending error: " << e.what() << std::endl;
            }
            bufferPtr += sendPacketSize;
        }

        memcpy(&rxBuffer, bufferPtr, leftoverBytes);
        bufferSize -= packetCount * sendPacketSize;
    }
}
#pragma clang diagnostic pop
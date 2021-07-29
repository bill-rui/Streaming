#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include "udp_server.h"
#include "udp_client.h"
#include <iostream>
#pragma clang diagnostic push
#define BUFF_SIZE 4000
#define SERVER_PORT 1350
#define FORWARDING_ADDR "127.0.0.1"
#define FORWARDING_PORT 1235
#define SEND_PACKET_SIZE 256

void forward(int buffSize, int serverPort, std::string addr, int forwardingPort, int sendPktSize){
    unsigned char rxBuffer[buffSize + sendPktSize];
    UDPServer server(serverPort, buffSize);
    UDPClient sender;
    std::cout << "Forwarding to address: " << addr << ":" << forwardingPort << std::endl;
    server.MakeBlocking();
    unsigned long total_rx_data = 0;
    unsigned long buffOffset = 0;
    unsigned long sendPacketSize = sendPktSize;
    int sendPktCount = 0;
    int rcvPktCount = 0;

    while(true) {
        unsigned int packetCount;
        ssize_t packetSize = server.Recv(&rxBuffer[buffOffset], buffSize);
        rcvPktCount++;
        if (packetSize < 0) {
            throw std::runtime_error("Receive failed");
        }
        std::cout << "packet received: " << packetSize << ", " << rcvPktCount << std::endl;
        total_rx_data += packetSize;
        auto *bufferPtr = (unsigned char *) &rxBuffer;
        packetCount = (int) total_rx_data / sendPacketSize;
        buffOffset = total_rx_data % sendPacketSize;

        for (unsigned int i = 0; i < packetCount; i++) {  // send packets
            try {
                ssize_t s = sender.Send(addr, forwardingPort, bufferPtr, sendPacketSize);
                sendPktCount++;
                std::cout << "packet sent: " << s << ", " << sendPktCount << std::endl;
            }
            catch (std::runtime_error &e) {
                std::cout << "Sending error: " << e.what() << std::endl;
            }
            bufferPtr += sendPacketSize;
        }

        if (packetCount != 0) {
            memcpy(&rxBuffer, bufferPtr, buffOffset);  //move buffer to front
        }
        total_rx_data -= packetCount * sendPacketSize;
    }
}

void sendData(std::string addr, int port, const unsigned char* buffer, ssize_t len){
    UDPClient sender;
    sender.Send(addr, port, buffer, len);
}

void receiveData(int port, unsigned char *buffer, ssize_t len){
    UDPServer receiver(port, 4000);
    receiver.MakeBlocking();
    receiver.Recv(buffer, len);
}


#pragma clang diagnostic pop
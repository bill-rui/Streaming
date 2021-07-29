#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include "udp_server.h"
#include "udp_client.h"
#include "signal_handler.h"
#include <iostream>
#pragma clang diagnostic push


void forward(int buffSize, int serverPort, std::string addr, int forwardingPort, unsigned long sendPktSize){
    unsigned char rxBuffer[buffSize + sendPktSize];
    UDPServer server(serverPort, buffSize);
    UDPClient sender;
    std::cout << "Forwarding to address: " << addr << ":" << forwardingPort << std::endl;
    std::cout << "Packet size: " << sendPktSize << std::endl;
    server.MakeBlocking(1);
    unsigned long total_rx_data = 0;
    unsigned long buffOffset = 0;
    SignalHandler signal_handler;
    signal_handler.SetupSignalHandlers();

    while(!signal_handler.GotExitSignal()) {
        ssize_t packetSize = server.Recv(&rxBuffer[buffOffset], buffSize);
        if (packetSize < 0) {
            throw std::runtime_error("Receive failed");
        }
        std::cout << "packet received: " << packetSize << std::endl;
        total_rx_data += packetSize;
        auto *bufferPtr = (unsigned char *) &rxBuffer;
        unsigned int packetCount = (int) total_rx_data / sendPktSize;
        buffOffset = total_rx_data % sendPktSize;

        for (unsigned int i = 0; i < packetCount; i++) {  // send packets
            try {
                sender.Send(addr, forwardingPort, bufferPtr, sendPktSize);
                //std::cout << "packet sent: " << s << std::endl;
            }
            catch (std::runtime_error &e) {
                //std::cout << "Sending error: " << e.what() << std::endl;
            }
            bufferPtr += sendPktSize;
        }

        if (packetCount != 0) {
            memcpy(&rxBuffer, bufferPtr, buffOffset);  //move buffer to front
        }
        total_rx_data -= packetCount * sendPktSize;
    }
    std::cout << "No packet received" << std::endl;
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
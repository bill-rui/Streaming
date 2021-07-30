#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#include "Server.h"
#include "signal_handler.h"
#include "udp_client.h"
#include "udp_server.h"
#include <iostream>
#pragma clang diagnostic push

void Forward(const int kBuffSize, const int kMaxRxSize, const int kServerPort, const std::string kAddr,
             const int kForwardingPort, const unsigned long kSendPktSize){
    unsigned char rx_buffer[kBuffSize + kSendPktSize];
    UDPServer server(kServerPort, kBuffSize);
    UDPClient sender;
    std::cout << "Forwarding to address: " << kAddr << ":" << kForwardingPort << std::endl;
    std::cout << "Packet size: " << kSendPktSize << std::endl;
    server.MakeBlocking(1);
    unsigned long total_rx_data = 0;
    unsigned long leftover_data = 0;
    SignalHandler signal_handler;
    signal_handler.SetupSignalHandlers();
    auto *send_ptr = reinterpret_cast<uint8_t *>(&rx_buffer);
    auto *rcv_ptr = reinterpret_cast<uint8_t *>(&rx_buffer);

    while(!signal_handler.GotExitSignal()) {
        ssize_t packet_size = server.Recv(rcv_ptr, kBuffSize);
        if (packet_size < 0 || packet_size > kMaxRxSize) {
            throw std::runtime_error("Receive failed");
        }
        //std::cout << "packet received: " << packet_size << std::endl;
        total_rx_data += packet_size;
        unsigned int packet_count = static_cast<int>(total_rx_data / kSendPktSize);
        leftover_data = total_rx_data % kSendPktSize;

        for (unsigned int i = 0; i < packet_count; i++) {  // send packets
            try {
                ssize_t s = sender.Send(kAddr, kForwardingPort, send_ptr, kSendPktSize);
                //std::cout << "packet sent: " << s << std::endl;
            }
            catch (std::runtime_error &e) {
                std::cout << "Sending error: " << e.what() << std::endl;
            }
            send_ptr += kSendPktSize;
        }

        // move data to front if possible overflow
        if (send_ptr + leftover_data + kMaxRxSize - reinterpret_cast<const uint8_t *>(&rx_buffer) > kBuffSize) {
            //std::cout << "mem moved" << std::endl;
            memcpy(&rx_buffer, send_ptr, leftover_data);  //move buffer to front
            send_ptr = reinterpret_cast<uint8_t *>(&rx_buffer);
        }
        rcv_ptr = send_ptr + leftover_data;
        total_rx_data -= packet_count * kSendPktSize;
    }

}

void SendData(std::string addr, int port, const unsigned char* buffer, ssize_t len){
    UDPClient sender;
    sender.Send(addr, port, buffer, len);
}

void ReceiveData(int port, uint8_t *buffer, ssize_t len){
    UDPServer receiver(port, 4000);
    receiver.MakeBlocking();
    receiver.Recv(buffer, len);
}


#pragma clang diagnostic pop
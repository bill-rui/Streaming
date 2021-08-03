//
// Created by Bill on 7/29/21.
//

#ifndef UDP_SERVER_H
#define UDP_SERVER_H
#include <iostream>
#include "udp_server.h"
#include "udp_client.h"
#include "signal_handler.h"
#include <memory>
class StreamReceiver{
 private:
  UDPServer server;
  UDPClient sender;
  SignalHandler signal_handler;
  int kMaxRxSize;
  std::string kAddr;
  int kForwardingPort;
  unsigned long kSendPktSize;
  int kBuffSize;
  unsigned char* send_ptr;
  unsigned char* rcv_ptr;
  ssize_t total_rx_data;
  bool print_progress;
  unsigned char* rx_buffer;

 public:
  StreamReceiver(
      int kBuffSize, int kMaxRxSize, int kServerPort, std::string kAddr,
      int kForwardingPort, unsigned long kSendPktSize
      );
  StreamReceiver(int kBuffSize, int kMaxRxSize, int kServerPort);
  ~StreamReceiver(){
    delete[] rx_buffer;
  }
  void Forward();
  ssize_t Receive();
  ssize_t WriteTo(uint8_t *dest, ssize_t bytes);
  ssize_t Send();
};
void Forward(int kBuffSize, int kMaxRxSize, int kServerPort, std::string kAddr,
             int kForwardingPort, unsigned long kSendPktSize);
void SendData(std::string addr, int port, const unsigned char* buffer, ssize_t len);
void ReceiveData(int port, unsigned char *buffer, ssize_t len);

#endif
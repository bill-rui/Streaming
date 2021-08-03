//
// Created by Bill on 7/29/21.
//

#ifndef UDP_SERVER_H
#define UDP_SERVER_H
#include <iostream>
void Forward(int kBuffSize, int kMaxRxSize, int kServerPort, std::string kAddr,
             int kForwardingPort, unsigned long kSendPktSize);
void SendData(std::string addr, int port, const unsigned char* buffer, ssize_t len);
void ReceiveData(int port, unsigned char *buffer, ssize_t len);

#endif
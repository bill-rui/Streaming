//
// Created by Bill on 7/29/21.
//

#ifndef UDP_SERVER_SERVER_H
#define UDP_SERVER_SERVER_H
#include "Server.cpp"
void forward(int buffSize, int serverPort, std::string addr, int forwardingPort, unsigned long sendPktSize);
void sendData(std::string addr, int port, const unsigned char* buffer, ssize_t len);
void receiveData(int port, unsigned char *buffer, ssize_t len);

#endif //UDP_SERVER_SERVER_H

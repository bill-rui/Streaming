#include <cstdio>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <unistd.h>
#include<chrono>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#define SENDER_PORT 1342
#define SERVER_PORT 1234
#define BUF_SIZE 4000
int main(int argc, char const *argv[])
{
    sockaddr_in server_addr, receiver_addr, sender_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SENDER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(SERVER_PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    std::string msg = "hello";
    char buffer[BUF_SIZE];

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0){
        perror("Initialize Socket");
    }
    if (bind(sockfd, (struct  sockaddr *) &server_addr, sizeof((server_addr))) < 0) {
        perror("Bind");
    }
    int rcv_addr_len = sizeof(receiver_addr);
    std::cout << "Server successfully initialized" << std::endl;
    std::cout << "Listening at port " << SENDER_PORT << "..." << std::endl;
    std::cout << "Sending to port " << SERVER_PORT << "..." << std::endl;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    ssize_t s = 0;
    int i = 0;
    int c = 0;
    while (true){
        memset(&buffer, 0, BUF_SIZE);
        int sdr_addr_len = sizeof(sender_addr);
        ssize_t size = recvfrom(sockfd, (char *) buffer, BUF_SIZE, 0, (struct sockaddr *) &sender_addr,
                (socklen_t *) &sdr_addr_len);
        if (c != 500){
            sendto(sockfd, &buffer, BUF_SIZE, MSG_DONTROUTE, (struct sockaddr *) &receiver_addr, rcv_addr_len);
        }
        else{
            c = 0;
        }
        if(std::chrono::steady_clock::now() - start > std::chrono::seconds(i)){
            i++;
            std::cout << s << std::endl;
            s = 0;
        }
        s += size;
        c++;
    }
}
#pragma clang diagnostic pop
#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <iostream>
#include <netinet/in.h>


class SocketHandler
{
private:
    int socketFd;
    int newSockFd;
    int portNo;
    int coreCount;
    int n;
    int opt;
    char buffer[256];
    bool bound;
    std::string cpuTemp[64];
    std::string cpuName;
    socklen_t clientLength;
    struct sockaddr_in server_addr, cli_addr;

public:
    SocketHandler();
    SocketHandler(int portNumber);
    void bindSocket();
    void listenSocket();
    void acceptSocket();
    void sendCpuName();
    bool sendCpuTemp();
    std::string getCpuName();
};

#endif // SOCKETHANDLER_H

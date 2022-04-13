#include "sockethandler.h"
#include "sensordata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

SocketHandler::SocketHandler():SocketHandler(5555){}
SocketHandler::SocketHandler(int portNumber)
{
    portNo = portNumber;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    opt = 1;
    cpuName = CpuName();
    coreCount = getCpuTemp(cpuTemp);
    bindSocket();
}
void SocketHandler::bindSocket()
{
    bound = false;
    int i = 0;
    // prepare to bind socket
    memset((char*)&server_addr, 0,sizeof(server_addr));
    server_addr.sin_port = htons(portNo);
    socketFd = socket(AF_INET, SOCK_STREAM,0);
    setsockopt(socketFd, SOL_SOCKET, SO_REUSEPORT, (char *)&opt,
                     sizeof opt);
    if (socketFd < 0)
    {
        cout << "ERROR OPENING SOCKET" << endl;
    }
    while(!bound)
    {
        if (bind(socketFd,(struct sockaddr*)&server_addr, sizeof(server_addr)) <0)
        {
            cout << "error binding"<<endl;
            server_addr.sin_port = htons(portNo);
        }
        else
        {
            cout << "Server: Bound to socket on port number: " << portNo << endl;
            bound = true;
        }
    }
}
void SocketHandler::listenSocket()
{
    cout << "Sever: Listening for incomming connections on port "<< portNo << "..." << endl;
    listen(socketFd,5);
    acceptSocket();
}
void SocketHandler::acceptSocket()
{
    clientLength = sizeof(cli_addr);
    newSockFd = accept(socketFd, (struct sockaddr*)&cli_addr, &clientLength);
    if (newSockFd < 0)
    {
        cout << "ERROR ON ACCEPT" << endl;
    }
    else
    {
        cout << " Server: Got connection from: " << inet_ntoa(cli_addr.sin_addr) << ":"
             << ntohs(cli_addr.sin_port) << endl;
    }
}
void SocketHandler::sendCpuName()
{
    if (send(newSockFd, cpuName.append("\n").c_str(),cpuName.length()+1,0) == -1)
    {
        cout << "Server: ERROR sending CPU Name to socket" << endl;
    }

    memset(buffer,0,256);


    n = read(newSockFd, buffer, 255);
    if (n < 0)
    {
        cout << "client disconnected" << endl;
    }
    else if (n == 0)
    {
        cout << "client disconnected"<<endl;
    }
}
bool SocketHandler::sendCpuTemp()
{
    for (int i = 0; i < coreCount;i++)
    {
        getCpuTemp(cpuTemp);
        string tempData = cpuTemp[i];
        if (send(newSockFd, tempData.append("\n").c_str(),tempData.length()+1,0) == -1)
        {
            cout << "Server: ERROR sending CPU Temp to socket" << endl;
        }

        memset(buffer,0,256);

        n = read(newSockFd, buffer, 255);
        if (n < 0)
        {
            cout << "client disconnected" << endl;
            return false;
        }
        else if (n == 0)
        {
            cout << "client disconnected"<<endl;
            return false;
        }
    }
    return true;
}
string SocketHandler::getCpuName()
{
    return cpuName;
}




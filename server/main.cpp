#include <iostream>
#include "sockethandler.h"



int main()
{
    bool connected = false;
    SocketHandler mySocket = SocketHandler();
    while (true)
    {
        mySocket.listenSocket();
        mySocket.sendCpuName();
        connected = mySocket.sendCpuTemp();
        while (connected)
        {
            connected = mySocket.sendCpuTemp();
        }
        //mySocket.bindSocket();
    }

}

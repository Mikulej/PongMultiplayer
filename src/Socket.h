#ifndef SOCKET_H
#define SOCKET_H
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
class Socket{
    SOCKET clientSocket;
    int port;
    sockaddr_in clientService;
    
    static WSADATA wsaData;
    static int wsaerr;
    public:
    Socket(int port);
    int Connect(std::string ip);
    std::string Receive(void);
    void Send(std::string buffer);
    static void Initialize(void);
};
#endif
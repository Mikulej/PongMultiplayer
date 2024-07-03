#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include "Socket.h"
#include <thread>
#include <filesystem>
#include <memory>
#include "Collider.h"
class Client{
    std::shared_ptr<Socket> socket;
    std::string destinationIp;
    std::string bufferData;
    int playerId;
    const int tickrate = 1000 / 64;
    void readIp(void);
    public:
    void sendData(std::string buffer);
    void startReceivingData(void);
    void receiveData(void);
    std::string getBuffertData(void);
    
    Client();
    ~Client();
};
#endif
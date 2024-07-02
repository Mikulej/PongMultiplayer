#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include "Socket.h"
#include <thread>
#include <filesystem>
#include <memory>
class Client{
    std::shared_ptr<Socket> socket;
    std::string destinationIp;
    std::string bufferData;
    int playerId;
    public:
    void sendData(std::string buffer);
    void startReceivingData(void);
    void receiveData(void);
    Client(std::string destinationIp);
    ~Client();
};
#endif
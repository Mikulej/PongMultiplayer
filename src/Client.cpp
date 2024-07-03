#include "Client.h"
void Client::readIp(void){
    std::ifstream fs("../config.txt");
    getline(fs,destinationIp);
}
Client::Client(): playerId(1){
    readIp();
    socket = std::make_shared<Socket>(66671);
    if(socket->Connect(destinationIp) == 0){
        playerId++;
        socket = std::make_shared<Socket>(66672);
        if(socket->Connect(destinationIp) == 0){
            std:: cout << "Cant connect to the server" << std::endl;
        }
    }
    
}
Client::~Client(){

}
void Client::sendData(std::string buffer){
    socket->Send(buffer);
}
// void Client::startReceivingData(void){
    
// }
void Client::receiveData(void){
    while(true){
        bufferData = socket.get()->Receive();
        Collider::processReceivedData(bufferData);
        std::this_thread::sleep_for (std::chrono::milliseconds(tickrate));
    }
}
std::string Client::getBuffertData(void){
    return bufferData;
}

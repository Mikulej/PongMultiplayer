#include "Client.h"
void Client::readIp(void){
    std::ifstream fs("../config.txt");
    getline(fs,destinationIp);
}
int Client::getSetPortFromServer(void){
    std::shared_ptr<Socket> tempSocket = std::make_shared<Socket>(27000);
    if(tempSocket->Connect(destinationIp) == 0){
        std:: cout << "Cant connect to the server" << std::endl;
    }
    else{
        std:: cout << "Connected using port 27000" << std::endl;
        bufferData = tempSocket.get()->Receive();
        std:: cout << "Using port " << std::stoi(bufferData) << " now" << std::endl;
        
    }
    WSACleanup();
    return std::stoi(bufferData);
}
Client::Client(){
    readIp();
    const int port = getSetPortFromServer();
    std:: cout << "New socket with port " << port << std::endl;
    Socket::Initialize(); 
    socket = std::make_shared<Socket>(port);
    if(socket->Connect(destinationIp) == 0){
        std:: cout << "Cant connect to the server" << std::endl;
    }
    else{
        std:: cout << "Connected" << std::endl;
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


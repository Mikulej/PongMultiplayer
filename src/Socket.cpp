#include "Socket.h"

WSADATA Socket::wsaData;
int Socket::wsaerr;
void Socket::Initialize(){
    WORD wVersionRequested = MAKEWORD(2,2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if(wsaerr != 0){
        std::cout << "The Winsock dll not found!" << std::endl;
    }
    else{
        std::cout << "The Winsock dll found!" << std::endl;
        std::cout << "Status: " << wsaData.szSystemStatus << std::endl;
    }

}
Socket::Socket(int port):port(port){
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(clientSocket==INVALID_SOCKET){
        std::cout << "Error at socket()" << WSAGetLastError() << std::endl;
        WSACleanup();
    }
    else{
        std::cout << "socket() is OK!" << std::endl;
    }
}
int Socket::Connect(std::string ip){
    clientService.sin_family = AF_INET;
    std::wstring stemp = std::wstring(ip.begin(), ip.end());
    LPCSTR sw = ip.c_str();
    InetPton(AF_INET,sw,&clientService.sin_addr.s_addr);
    clientService.sin_port=htons(port);
    std::cout << "connecting to ip " << ip << " port " << port << std::endl;
    if(connect(clientSocket,(SOCKADDR*)&clientService,sizeof(clientService))==SOCKET_ERROR){
        std::cout<<"Client: connect() - Failed to connect - error " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    else{
        std::cout<<"Client: connect() is OK" << std::endl;
        std::cout<<"Client: Can start sending and receiving data..." << std::endl;
        
    }
    return 1;
}
std::string Socket::Receive(){
    char buffer[100] ={0};
    int byteCount = recv(clientSocket,buffer,sizeof(buffer),0);
    //std::cout << "byteCount=" << byteCount << std::endl;
    if(byteCount > 0){
        //std::cout<<"Received message: "<< buffer << std::endl;
    }
    else{
       WSACleanup();
    }
    return buffer;
}

void Socket::Send(std::string buffer){
    int byteCount = send(clientSocket,buffer.data(),buffer.size(),0);
    if(byteCount > 0){
        //std::cout<<"Sent message: "<< buffer << std::endl;
    }
    else{
       WSACleanup();
    }
}
void Socket::setPort(int port){
    this->port = port;
}
void Socket::CloseAll(void){
    WSACleanup();
}
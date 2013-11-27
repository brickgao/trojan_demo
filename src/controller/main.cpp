#include <stdio.h>  
#include <winsock2.h>  

#pragma comment(lib, "ws2_32.lib")  

int main() {  
    WSADATA wsaData;  
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);  
    if (iResult != NO_ERROR)  
        printf("Error at WSAStartup()\n");  
    SOCKET server;
    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
    if(server == INVALID_SOCKET){  
        printf("Error at socket(): %ld\n", WSAGetLastError() );  
        WSACleanup();
        return 0;
    }  
    sockaddr_in service;  
    service.sin_family = AF_INET;  
    service.sin_addr.s_addr = inet_addr("127.0.0.1");  
    service.sin_port = htons(8000);
    if(bind(server, (SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) {  
        printf("bind() failed.\n");
        closesocket(server);  
        return 0;
    }  
    if (listen( server, 1 ) == SOCKET_ERROR )  
        printf("Error listening on socket.\n");  
    SOCKET AcceptSocket;  
    printf("Waiting for a client to connect...\n");  
    while(1) {  
        AcceptSocket = SOCKET_ERROR;  
        while ( AcceptSocket == SOCKET_ERROR ) {  
            AcceptSocket = accept( server, NULL, NULL );  
        }  
        printf( "Client Connected.\n");  
        server = AcceptSocket;   
        break;  
    }  
    char sendbuf[1024];
    DWORD        dwRead;  
    BOOL         bRet;  
    send(server, "123",dwRead,0);  
    return 0;
}  


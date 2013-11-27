#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main() {
    while(true) {
        WSADATA wsaData;  
        int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
        if(iResult != NO_ERROR) {
            printf("Error at WSAStartup()\n");
            continue;
        }
        SOCKET client;  
        client = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
        if(client == INVALID_SOCKET) {
            printf("Error at socket(): %ld\n", WSAGetLastError());
            WSACleanup();
            continue;
        }
        sockaddr_in clientService;
        clientService.sin_family = AF_INET;
        clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
        clientService.sin_port = htons(8000);
        if(connect(client, (SOCKADDR*) &clientService, sizeof(clientService)) == SOCKET_ERROR) {  
            printf("Failed to connect.\n");
            WSACleanup();
            Sleep(5 * 1000);
            continue;
        }
        int read;
        char recvbuf[1024];
        DWORD        dwWrite;  
        BOOL         bRet;
        while(true) {
            read = recv(client, recvbuf, 1024, 0);
            if(read == -1)  break;
        }
        puts(recvbuf);
    }
    return 0;
}

 

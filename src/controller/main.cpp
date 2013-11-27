#include <stdio.h>  
#include <winsock2.h>  

#pragma comment(lib, "ws2_32.lib")  

int main() {
    printf("Controller start\n");
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
    if(listen( server, 1 ) == SOCKET_ERROR)  
        printf("Error listening on socket.\n");  
    SOCKET AcceptSocket;
    while(true) {
        printf("Waiting for a client to connect...\n");  
        while(1) {  
            AcceptSocket = SOCKET_ERROR;  
            while(AcceptSocket == SOCKET_ERROR) {  
                AcceptSocket = accept(server, NULL, NULL);  
            }  
            printf("Client Connected.\n");  
            server = AcceptSocket;   
            break;
        }  
        char sendbuf[1024];
        DWORD        dwRead;
        BOOL         bRet;  
        char command[100];
        puts("Print `help` to get help");
        while(true) {
            printf(">>");
            scanf("%s", command);
            if(command[0] == 's' && command[1] == 'e' && \
               command[2] == 'n' && command[3] == 'd' && \
               command[4] == 'f' && command[5] == 'i' && \
               command[6] == 'l' && command[7] == 'e') {
                send(server, "sendfile", 8, 0);
                printf("Ready for sending file :)\ninput filename: ");
                char filename[100];
                scanf("%s", filename);
                HANDLE hFile=CreateFile(filename, GENERIC_READ, 0, 0, \
                                        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                while(true) {
                    bRet = ReadFile(hFile, sendbuf, 1024, &dwRead, NULL);
                    if(bRet == false) {
                        puts("Read Buf ERROR!");
                        break;
                    }
                    else if(dwRead == 0) {
                        puts("Done. Then run it.");
                        break;
                    }
                    else {
                        send(server, sendbuf, dwRead, 0);
                    }
                }
                CloseHandle(hFile);
                send(server, "EOF", 3, 0);
            }
        }
    }
    return 0;
}  


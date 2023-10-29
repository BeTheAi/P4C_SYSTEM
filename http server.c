#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tchar.h>
// WIN
#include <Windows.h>
// NETWORK
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#define BUF_SIZE 2048

int main() {
    int port= 2814;                 
    SOCKET lsock, asock;
    SOCKADDR_IN addrIn, remote_sin;
    
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    lsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (lsock == INVALID_SOCKET)
        return;
   
    ZeroMemory(&addrIn, sizeof(addrIn));

    addrIn.sin_port = htons(port);
    addrIn.sin_family = AF_INET;
    addrIn.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(lsock, (struct SOCKADDR*)&addrIn, sizeof(addrIn)) == SOCKET_ERROR) {
        printf(" 오류 : 바인딩 실패. \n");
        return;
    }

    if (listen(lsock, 10) == SOCKET_ERROR) {
        printf(" 오류 : listen 실패.\n");
        return;
    }

    char szBuf[BUF_SIZE];
    memset(szBuf, 0, sizeof(szBuf));
    _snprintf(szBuf, sizeof(szBuf),
        "HTTP/1.0 200 OK\r\n"
        "Content-Length: 200\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "Client 응답용 페이지\\n");


    while (1) {
        printf("[INFO] waiting...\n");
        int addrLen = sizeof(SOCKADDR);
        asock = accept(lsock, (SOCKADDR*)&remote_sin, &addrLen);
        if (asock == INVALID_SOCKET) {
            perror(" 오류 : Accpet 실패.\n");
            printf("%d", GetLastError());
        }
        else
        {
            while (asock)
            {
                char input[BUF_SIZE];
                int len = BUF_SIZE;
                int inputLen = recv(asock, input, len, 0);
                if (inputLen <= 0) 
                    break;
                else 
                    send(asock, szBuf, (int)strlen(szBuf), 0);
            }
        }
    }
    WSACleanup();
}

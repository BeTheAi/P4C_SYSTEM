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
    int port= 2814;                 //포트번호 임의지정
    SOCKET lsock, asock;            // listen socket과 accept소켓 선언하기
    SOCKADDR_IN addrIn, remote_sin; // IP, PORT 정보를 저장할 변수
    
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  //소켓 구현을 위한 
        return 1;

    lsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //IPv4, TCP 프로토콜로 통신할 SOCKET 생성
    if (lsock == INVALID_SOCKET)                        // 생성한 lsock의 오류여부 확인
        return;
    ZeroMemory(&addrIn, sizeof(addrIn));                // 초기화

    addrIn.sin_port = htons(port);                      //임의 설정한 포트입력
    addrIn.sin_family = AF_INET;                        // ipv4로 ip 그룹 설정
    addrIn.sin_addr.s_addr = htonl(INADDR_ANY);         // 자동 할당한 ip로 주소 설정

    if (bind(lsock, (struct SOCKADDR*)&addrIn, sizeof(addrIn)) == SOCKET_ERROR) { // bind 함수 실행의 오류 발생시오류 메시지 출력
        printf(" 오류 : 바인딩 실패. \n");
        return;
    }

    if (listen(lsock, 10) == SOCKET_ERROR) {                     //socket 의 Listen시 통신의 최대 대기열 10으로 설정하고 오류 발생시 listen 실패 출력
        printf(" 오류 : listen 실패.\n");
        return;
    }

    char szBuf[BUF_SIZE];                       // 페이지 호출후 send로 보여줄 서버의 웹페이지 설정
    memset(szBuf, 0, sizeof(szBuf));    // 초기화
    _snprintf(szBuf, sizeof(szBuf), // 아래의 html 페이지 내용 설정
        "HTTP/1.0 200 OK\r\n"
        "Content-Length: 200\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "Client 응답용 페이지\\n");


    while (1) {
        printf("[INFO] waiting...\n");          // 응답 대기
        int addrLen = sizeof(SOCKADDR);
        asock = accept(lsock, (SOCKADDR*)&remote_sin, &addrLen); //데이터 accept 소켓 설정
        if (asock == INVALID_SOCKET) {          // 소켓 설정 오류시 
            perror(" 오류 : Accpet 실패.\n");   // accept 실패 출력
            printf("%d", GetLastError());       // 에러 식별을 위한 출력
        }
        else
        {
            while (asock)
            {
                char input[BUF_SIZE];           //  http 통신 데이터를 입력받을 input 문자열 선언
                int len = BUF_SIZE;             // 길이 설정(=2048)
                int inputLen = recv(asock, input, len, 0);  // inputlen을 recv/수신한 소켓 값
                if (inputLen <= 0)                          // 수신 데이터 오류시 멈추기
                    break;
                else 
                    send(asock, szBuf, (int)strlen(szBuf), 0); // 기본 페이지를 저정한 szBuf send로 CLient에게 보내기
            }
        }
    }
    WSACleanup();
}

#include <iostream>
#include <winsock2.h>
#include <windows.h>
using namespace std;

#define PORT 100
#define MAX_SIZE 100

SOCKET clientSock;

void nhanMang() {
    int n;
    float arr[MAX_SIZE];

    while (true) {
        int recvBytes = recv(clientSock, (char*)&n, sizeof(int), 0);
        if (recvBytes <= 0) break;

        if (n <= 0) {
            cout << "Nhan n <= 0. Dung chuong trinh.\n";
            break;
        }

        recv(clientSock, (char*)arr, sizeof(float) * n, 0);

        cout << "Da nhan mang: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
}

VOID CALLBACK TimerCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
    nhanMang();  
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (sockaddr*)&server, sizeof(server));
    listen(serverSock, 1);

    cout << "Dang cho ket noi...\n";
    sockaddr_in client;
    int clientLen = sizeof(client);
    clientSock = accept(serverSock, (sockaddr*)&client, &clientLen);
    cout << "Client da ket noi.\n";

    HANDLE hTimer = NULL;
    HANDLE hTimerQueue = CreateTimerQueue();

    CreateTimerQueueTimer(&hTimer, hTimerQueue, TimerCallback, NULL, 0, 0, WT_EXECUTEDEFAULT);

 
    system("pause");

    CloseHandle(hTimer);
    CloseHandle(hTimerQueue);
    closesocket(clientSock);
    closesocket(serverSock);
    WSACleanup();
    return 0;
}


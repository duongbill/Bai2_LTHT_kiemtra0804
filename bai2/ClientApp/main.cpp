
#include <iostream>
#include <winsock2.h>
using namespace std;

#define SERVER_IP "127.0.0.1"
#define PORT 100
#define MAX_SIZE 100

void nhapVaGuiMang(SOCKET sock) {
    int n;
    float arr[MAX_SIZE];

    while (true) {
        cout << "Nhap so phan tu (n <= 0 de thoat): ";
        cin >> n;

   
        send(sock, (char*)&n, sizeof(int), 0);

        if (n <= 0) break;

        for (int i = 0; i < n; i++) {
            cout << "Nhap phan tu thu " << i << ": ";
            cin >> arr[i];
        }

   
        send(sock, (char*)arr, sizeof(float) * n, 0);
    }
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    connect(sock, (sockaddr*)&server, sizeof(server));
    cout << "Da ket noi den server.\n";

    nhapVaGuiMang(sock);

    closesocket(sock);
    WSACleanup();
    return 0;
}


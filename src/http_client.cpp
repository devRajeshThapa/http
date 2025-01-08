#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

const int PORT = 8080;
const char* SERVER_IP = "127.0.0.1";

int main() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed: " << iResult << std::endl;
        return 1;
    }

    SOCKET client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == INVALID_SOCKET) {
        std::cout << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cout << "Connect failed: " << WSAGetLastError() << std::endl;
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server..." << std::endl;
    const char* request = "GET / HTTP/1.1\r\n"
                          "Host: 127.0.0.1\r\n"
                          "Connection: close\r\n"
                          "\r\n";

    send(client_fd, request, strlen(request), 0);
    std::cout << "Request sent to server." << std::endl;

    char buffer[4096] = {0};
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        std::cout << "Received from server: " << buffer << std::endl;
    } else {
        std::cout << "recv failed: " << WSAGetLastError() << std::endl;
    }

    closesocket(client_fd);
    WSACleanup();
    return 0;
}

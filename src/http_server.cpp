#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

const int PORT = 8080;

const char* RESPONSE_200 = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 20\r\n"
    "\r\n"
    "<p>Hello, World!</p>";

const char* RESPONSE_404 = 
    "HTTP/1.1 404 Not Found\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 23\r\n"
    "\r\n"
    "<p>404 - Not Found</p>";

int main() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed: " << iResult << std::endl;
        return 1;
    }

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        std::cout << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cout << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cout << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    std::cout << "HTTP Server is listening on port " << PORT << std::endl;

    SOCKET client_fd;
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[1024] = {0};

    while (true) {
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_fd == INVALID_SOCKET) {
            std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
            closesocket(server_fd);
            WSACleanup();
            return 1;
        }

        int bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_read > 0) {
            std::cout << "Received request: " << buffer << std::endl;

            // Simple filtering based on request path
            if (strstr(buffer, "GET / HTTP/1.1")) {
                send(client_fd, RESPONSE_200, strlen(RESPONSE_200), 0);
                std::cout << "200 OK response sent to client." << std::endl;
            } else {
                send(client_fd, RESPONSE_404, strlen(RESPONSE_404), 0);
                std::cout << "404 Not Found response sent to client." << std::endl;
            }
        } else if (bytes_read == 0) {
            std::cout << "Connection closing..." << std::endl;
        } else {
            std::cout << "recv failed: " << WSAGetLastError() << std::endl;
            closesocket(client_fd);
            WSACleanup();
            return 1;
        }

        closesocket(client_fd);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}

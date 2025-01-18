#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno> // For errno

int main() {
    char server_ip[16];
    int port;
    std::string path;

    std::cout << "Enter the server IP address: ";
    std::cin >> server_ip;
    std::cout << "Enter the port number: ";
    std::cin >> port;
    std::cout << "Enter the path: ";
    std::cin >> path;

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        std::cerr << "Socket creation failed: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported: " << strerror(errno) << std::endl;
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connect failed: " << strerror(errno) << std::endl;
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "\nX------X------X------X------X------X\n";
    std::cout << "Connected to server at " << server_ip << " on port " << port << "...\n";

    std::string request = "GET " + path + " HTTP/1.1\r\n";
    request += "Host: " + std::string(server_ip) + "\r\n";
    request += "Connection: close\r\n\r\n";

    std::cout << "\nHTTP Request:\n" << request << std::endl;

    send(client_fd, request.c_str(), request.length(), 0);
    std::cout << "Request sent to server.\n";

    char buffer[4096] = {0};
    int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received > 0) {
        std::cout << "\nReceived from server: \n" << buffer << std::endl;
        std::cout << "X------X------X------X------X------X\n\n";
    } else {
        std::cerr << "recv failed: " << strerror(errno) << std::endl;
        std::cout << "X------X------X------X------X------X\n\n";
    }

    close(client_fd);
    return 0;
}


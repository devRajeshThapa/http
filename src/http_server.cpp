#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib> // For exit()
#include <cerrno>  // For errno

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
    int port;
    std::cout << "Enter the port number you want to listen on: ";
    std::cin >> port;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed: " << strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed: " << strerror(errno) << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "HTTP Server is listening on port " << port << "\n";

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            std::cerr << "Accept failed: " << strerror(errno) << std::endl;
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        int bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_received > 0) {
                std::cout<< "\nX------X------X------X------X------X\n";
            std::cout << "Received request: " << buffer << std::endl;

            if (strstr(buffer, "GET / HTTP/1.1")) {
                send(client_fd, RESPONSE_200, strlen(RESPONSE_200), 0);
                std::cout << ">> 200 OK response sent to client." << std::endl;
                std::cout<< "X------X------X------X------X------X\n\n";
            } else {
                send(client_fd, RESPONSE_404, strlen(RESPONSE_404), 0);
                std::cout << ">> 404 Not Found response sent to client." << std::endl;
                std::cout<< "X------X------X------X------X------X\n\n";    
            }
        } else if (bytes_received == 0) {
            std::cout << "Connection closing..." << std::endl;
        } else {
            std::cerr << "recv failed: " << strerror(errno) << std::endl;
            close(client_fd);
            exit(EXIT_FAILURE);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}

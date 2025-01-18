# HTTP Client/Server Implementation

## Overview

This repository contains a simple implementation of an HTTP client and server, showcasing socket programming in C++. The server listens for incoming HTTP requests and responds with the appropriate content, while the client connects to the server and sends HTTP requests.

## Features

- **HTTP Server**: Listens on a specified port and handles HTTP GET requests; responds with either a "200 OK" or "404 Not Found" message.
- **HTTP Client**: Connects to the server, sends an HTTP GET request, and displays the server's response.

## Platforms 

This project is compatible with the following platforms: 

- **Linux**
- **macOS**
- **Windows Subsystem for Linux (WSL)**

## Prerequisites

Make sure you have the following installed:

- **CMake**: Version 3.28.3 or above
- **g++**: A C++ compiler

## Cloning the Repository

To get started with the project, clone the repository using the following command:

```sh
git clone https://github.com/devRajeshThapa/http.git
cd http
```

## Building the Project

Use CMake to build the project. This will create the executables in the `dist/bin` directory:

```sh
cmake ..
cmake --build .
cmake --install . --prefix ../dist
```

> Note: The `dist` directory will be created at the root of the project.

## Running the Server

1. Navigate to the `dist/bin` directory.
2. Run the `http_server` executable.
3. Enter the port number when prompted.

```sh
cd dist/bin
./http_server
Enter the port number you want to listen on: <port_number>
```

## Running the Client

1. Navigate to the `dist/bin` directory.
2. Run the `http_client` executable.
3. Enter the server IP address, port number, and path when prompted.

```sh
cd dist/bin
./http_client
Enter the server IP address: <server_ip>
Enter the port number: <port_number>
Enter the path: <path>
```

## Accessing the Server from a Browser

Once the server is running, you can access it from a web browser by entering the following URL:

```
http://<server_ip>:<port_number>
```

Replace `<server_ip>` with the IP address of the server (e.g., `127.0.0.1` if running locally) and `<port_number>` with the port number you specified.

---

### Example Usage

#### HTTP Server

```sh
./http_server
Enter the port number you want to listen on: 8080
HTTP Server is listening on port 8080
```

#### HTTP Client

```sh
./http_client
Enter the server IP address: 127.0.0.1
Enter the port number: 8080
Enter the path: /
Connected to server at 127.0.0.1 on port 8080...

HTTP Request:
GET / HTTP/1.1
Host: 127.0.0.1
Connection: close

Request sent to server.

Received from server:
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 20

<p>Hello, World!</p>
```

#### Accessing the Server from a Browser

Open your web browser and enter the following URL:

```
http://127.0.0.1:8080
```

You should see the following "Hello, World!" message displayed

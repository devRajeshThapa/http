cmake_minimum_required(VERSION 3.28.3)

project(socket LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(http_server src/http_server.cpp)
add_executable(http_client src/http_client.cpp)

install(TARGETS http_client http_server DESTINATION bin)
install(FILES LICENSE DESTINATION docs)
install(FILES docs/README_DIST.md DESTINATION docs RENAME README.md)
install(FILES LICENSE DESTINATION docs) 

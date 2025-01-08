cmake_minimum_required(VERSION 3.10)

# Define the project name and specify languages
project(socket LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(include)

# Add the executable target and the source files
add_executable(http_server src/http_server.cpp)
add_executable(http_client src/http_client.cpp)

# Link ws2_32 library for Winsock functions
target_link_libraries(http_server ws2_32)
target_link_libraries(http_client ws2_32)


# Install commands to copy files to the appropriate directories
install(TARGETS http_client http_server DESTINATION bin)
install(FILES docs/LICENSE DESTINATION docs) 
install(FILES docs/README_DIST.md DESTINATION docs/README.md) 
install(DIRECTORY include/ DESTINATION include) 
install(DIRECTORY lib/ DESTINATION lib)
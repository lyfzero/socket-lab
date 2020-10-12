cmake_minimum_required(VERSION 3.17)
project(socket_lab)

set(CMAKE_CXX_STANDARD 14)

add_executable(socket_lab main.cpp server.h request.h response.h utils.h fs.h config.h fs.cpp server.cpp request.cpp response.cpp utils.cpp my_socket.h my_socket.cpp)
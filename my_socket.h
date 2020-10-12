//
// Created by lyf on 2020/10/12.
//

#ifndef SOCKET_LAB_My_socket_H
#define SOCKET_LAB_My_socket_H


#include <netinet/in.h>
#include <string>
using namespace std;

#include "config.h"

class My_socket {
public:
    int sock_fd;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = {0};
    bool is_valid;

    My_socket();
    void setSockOpt(int opt);
    void setAddress(string ip_to_listen, int port);
    void setBind();
    void startListen(int max_listen_num);
};

#endif //SOCKET_LAB_My_socket_H

//
// Created by lyf on 2020/10/12.
//

#include "my_socket.h"
#include <sys/socket.h>
#include <arpa/inet.h>

My_socket::My_socket() {
    if ((this->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        this->is_valid = false;
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

void My_socket::setSockOpt(int opt=1) {
    if (setsockopt(this->sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, & opt, sizeof(opt))) {
        perror("set socket option");
        exit(EXIT_FAILURE);
    }
}

void My_socket::setAddress(string ip_to_listen, int port) {
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = inet_addr(ip_to_listen.c_str());
    this->address.sin_port = htons(port);
}

void My_socket::setBind() {
    if (bind(this->sock_fd, (struct sockaddr*) &this->address, sizeof(this->address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}
void My_socket::startListen(int max_listen_num) {
    if (listen(this->sock_fd, max_listen_num) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}
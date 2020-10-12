//
// Created by lyf on 2020/10/8.
//

#include "server.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "request.h"
#include "utils.h"
#include "fs.h"
#include "config.h"
#include "my_socket.h"

Server::Server() {
    this->port = 8080;
    this->ip_to_listen = "0.0.0.0";
    this->base_path = "/home/lyf/CLionProjects/socket-lab";
    this->max_listen_num = 10;
    this->stopped = true;
}

Server::Server(string ip, int port, int max_listen_num, string path) {
    this->ip_to_listen = ip;
    this->port = port;
    this->base_path = path;
    this->max_listen_num = max_listen_num;
    this->stopped = true;
}

string Server::get_base_path() {
    return this->base_path;
}

string Server::get_ip_to_listen() {
    return this->ip_to_listen;
}

int Server::get_port() {
    return this->port;
}

void Server::set_base_path(string path) {
    if (this->base_path != path) {
        this->base_path = path;
        restart();
    }
}

void Server::set_ip_to_listen(string ip) {
    if (this->ip_to_listen != ip) {
        this->ip_to_listen = ip;
        restart();
    }
}

void Server::set_port(int port) {
    if (port != this->port) {
        this->port = port;
        restart();
    }
}

void Server::run() {
    this->stopped = false;
    int opt = 1;
    cout << "Server Started......" << endl;
    int server_fd, new_socket;

    My_socket listen_sock;
    listen_sock.setSockOpt(opt);
    listen_sock.setAddress(this->ip_to_listen, this->port);
    listen_sock.setBind();
    listen_sock.startListen(this->max_listen_num);

    cout << "Running on http://" << this->ip_to_listen << ":" <<  this->port << "/ (Press CTRL+C to quit)" << endl;

    while(true) {
        // 阻塞监听
        if (this->stopped) {
            cout << "Server Stopped" << endl;
            return;
        }
        struct sockaddr_in new_address;
        int addr_len = sizeof(new_address);
        int new_socket_fd;
        if((new_socket_fd = accept(listen_sock.sock_fd, (struct sockaddr*)&new_address, (socklen_t*)&addr_len)) < 0) {
            perror("accept error");
            exit(EXIT_FAILURE);
        }
        this->data_handle(new_socket_fd, new_address);
    }
}

void Server::stop() {
    this->stopped = true;
}

void Server::restart() {
    cout << "Server Restarting" << endl;
    this->stopped = true;
    sleep(1);
    this->run();
}

void Server::data_handle(int new_socket_fd, struct sockaddr_in new_address) {
    char buffer[BUFFER_SIZE] = {0};
    read(new_socket_fd, buffer, BUFFER_SIZE);

    Request request = Request(string(buffer));
    Response response = Response(request);
    string path = PATH + request.url;
    Fs fs;

    if (request.url == "/") {
        path = INDEX;
    }
    char file_buffer[255];
    if (!Fs::check_path(path)) {
        // 如果检测不通过，访问了上级目录
        response.set_status(400);
        fs = Fs(BAD_REQUEST);
    } else {
        fs = Fs(path);
        if (fs.ok) {
            response.set_status(200);
        } else {
            fs = Fs(NOT_FIND);
            response.set_status(404);
        }
    }
    string ip_in = string(inet_ntoa(new_address.sin_addr));
    print_log(response, request, ip_in);

    response.add_header("Content-Type", fs.file_type);
    write(new_socket_fd, response.to_string().c_str(), response.to_string().size()); // 写入返回头
    // 写入返回主体
    while(fs.file.readsome(file_buffer, sizeof(file_buffer))) {
        write(new_socket_fd, file_buffer, fs.file.gcount());
    }
    close(new_socket_fd);
}

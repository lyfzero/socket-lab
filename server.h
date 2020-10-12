//
// Created by lyf on 2020/10/8.
//

#ifndef SOCKET_LAB_SERVER_H
#define SOCKET_LAB_SERVER_H

#include <string>
#include "my_socket.h"
using namespace std;
class Server {
public:
    Server();
    Server(string ip, int port, int max_listen_num, string path);

    void set_port(int port);
    void set_ip_to_listen(string ip);
    void set_base_path(string path);
    int get_port();
    string get_ip_to_listen();
    string get_base_path();

    void run();
    void stop();
    void restart();
    void data_handle(int new_socket_fd, struct sockaddr_in new_address);
private:
    bool stopped;
    int port;
    int max_listen_num;
    string ip_to_listen;
    string base_path;

    const string not_find = "/home/lyf/CLionProjects/socket-lab/404.html";
    const string bad_request = "/home/lyf/CLionProjects/socket-lab/400.html";
    const string index = "/home/lyf/CLionProjects/socket-lab/index.html";
};

#endif //SOCKET_LAB_SERVER_H

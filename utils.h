//
// Created by lyf on 2020/10/8.
//

#ifndef SOCKET_LAB_UTILS_H
#define SOCKET_LAB_UTILS_H

#include "request.h"
#include "response.h"
#include <chrono>
#include <ctime>
#include <vector>
#include <thread>
#include <mutex>

void print_log(Response, Request, string);
void data_handle(int , string);
void sigint_handle(int sig);
#endif //SOCKET_LAB_UTILS_H

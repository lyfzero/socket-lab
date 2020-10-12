//
// Created by lyf on 2020/10/8.
//

#include <iostream>
#include <unistd.h>

#include "utils.h"
#include "request.h"
#include "response.h"
#include "fs.h"

using namespace std;
void print_log(Response response, Request request, string ip) {
    auto current = chrono::system_clock::now();
    auto current_time = chrono::system_clock::to_time_t(current);
    auto out_put_time = string(ctime(&current_time));
    out_put_time = out_put_time.substr(0, out_put_time.size() - 1); // 去掉换行符
    cout << ip << " - - "
         << " [" << out_put_time << "] \" "
         << request.type << " "
         << request.url << " "
         << request.http_version << "\""
         << response.status << " - " << endl;
}

#include "server.h"
#include "config.h"

int main() {
    Server http_server = Server(IP_TO_LISTEN, PORT, MAX_LISTEN_NUM, PATH);

    http_server.run();
    return 0;
}

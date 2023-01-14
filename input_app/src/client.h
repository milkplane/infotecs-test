#ifndef CLIENT_INFOTECS_H_
#define CLIENT_INFOTECS_H_

#include "./common/socket_connection.h"
#include <sys/types.h>

class client {
public:
    client(const char* ip_address, u_int16_t port, unsigned long reconnect_time_ms = 500);
    void write(const char* data, size_t length);
    ~client();
private:
    socket_connection connection;
    int connect_descriptor;
    unsigned long reconnect_time_ms;

    void connect();
    void close_connect();
    void reconnect();
};

#endif

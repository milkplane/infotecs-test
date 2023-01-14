#ifndef LOCAL_SERVER_INFOTECS_H_
#define LOCAL_SERVER_INFOTECS_H_

#include "./common/socket_connection.h"
#include <netinet/in.h>

class local_server {
public:
    local_server(const char* ip_address, u_int16_t port, unsigned long reconnect_time_ms = 500);
    ~local_server();
    void open(int max_connections);
    void close();
    size_t read(char* output_static_buffer, size_t static_buffer_size);
private:
    socket_connection connection;
    int read_descriptor;
    unsigned long reconnect_time_ms;

    void normolize_read_descriptor();
    bool is_EOF(size_t data_length);
    void reconnect();
};

#endif

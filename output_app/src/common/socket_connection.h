#ifndef SOCKET_CONNECTION_INFOTECS_H_
#define SOCKET_CONNECTION_INFOTECS_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

class socket_connection {
public:
    socket_connection(const char* ip_address, u_int16_t port);
    void open();
    void close();
    sockaddr_in get_address() const;
    int get_file_descriptor() const;
    ~socket_connection();
private:
    sockaddr_in address;
    int file_desciptor;
};

#endif
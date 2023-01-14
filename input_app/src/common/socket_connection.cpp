#include "socket_connection.h"
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

socket_connection::socket_connection(const char* ip_address, u_int16_t port)  {
    address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip_address, &address.sin_addr);

    file_desciptor = -1;
}

void socket_connection::open() {
    file_desciptor = ::socket(AF_INET, SOCK_STREAM, 0);
}

void socket_connection::close() {
    if (file_desciptor == -1) return;

    ::close(file_desciptor);
}

socket_connection::~socket_connection() {
    close();
}

sockaddr_in socket_connection::get_address() const {
    return address;
}

int socket_connection::get_file_descriptor() const {
    return file_desciptor;
}
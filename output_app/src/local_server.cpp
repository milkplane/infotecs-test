#include "./common/socket_connection.h"
#include "local_server.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <thread>

local_server::local_server(const char* ip_address, u_int16_t port, unsigned long reconnect_time_ms): connection(ip_address, port) {
    read_descriptor = -1;
    this->reconnect_time_ms = reconnect_time_ms;
}

void local_server::open(int max_connections) {
    connection.open();
    sockaddr_in address = connection.get_address();
    bind(connection.get_file_descriptor(), (sockaddr* ) &address, sizeof address);
    if (listen(connection.get_file_descriptor(), max_connections) == -1) {
        reconnect();
        open(max_connections);
    }

    std::cout << "Server has started" << std::endl;
}

void local_server::reconnect() {
    connection.close();

    std::cout << "Trying to reconnect\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(reconnect_time_ms));
}

size_t local_server::read(char* output_static_buffer, size_t static_buffer_size) {
    normolize_read_descriptor();

    size_t data_length = ::read(read_descriptor, output_static_buffer, static_buffer_size);

    if (is_EOF(data_length)) {
        close();
    }

    return data_length;
}

void local_server::close() {
    if (read_descriptor == -1) return;

    ::close(read_descriptor);
    read_descriptor = -1;
}

local_server::~local_server() {
    close();
    std::cout << "Server has been closed" << std::endl;
}

void local_server::normolize_read_descriptor() {
    if (read_descriptor != -1) return;

    sockaddr_in address = connection.get_address();
    socklen_t address_length = sizeof address;
    read_descriptor = ::accept(connection.get_file_descriptor(), (sockaddr *) &address, &address_length);
}

inline bool local_server::is_EOF(size_t data_length) {
    return data_length == 0;
}


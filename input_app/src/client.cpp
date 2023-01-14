#include "client.h"

#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include <iostream>

client::client(const char* ip_address, u_int16_t port, unsigned long reconnect_time_ms): connection(ip_address, port) {
    connect_descriptor = -1;
    this->reconnect_time_ms = reconnect_time_ms;
}

void client::write(const char* data, size_t length) {
    connection.open();
    connect();
    
    if (::write(connection.get_file_descriptor(), data, length) == -1) {
        reconnect();
        write(data, length);
        return;
    }

    connection.close();
}

void client::connect() {
    sockaddr_in size = connection.get_address();
    connect_descriptor = ::connect(connection.get_file_descriptor(), (sockaddr*) &size, sizeof size);

    if (connect_descriptor == -1) {
        reconnect();
    }
}

void client::close_connect() {
    if (connect_descriptor == -1) return;

    ::close(connect_descriptor);
    connect_descriptor = -1;
}

void client::reconnect() {
    connection.close();
    std::cout << "Trying to reconnect" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(reconnect_time_ms));
    connection.open();
    connect();
}

client::~client() {
    close_connect();
}
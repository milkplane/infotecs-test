#ifndef ONE_VALUE_RECIPIENT_H_
#define ONE_VALUE_RECIPIENT_H_

#include "local_server.h"

template <typename receive_value_type>
class one_value_recipient {
public:
    one_value_recipient();
    receive_value_type get_next();
private:
    local_server server;
};

template <typename receive_value_type>
one_value_recipient<receive_value_type>::one_value_recipient(): server("127.0.0.1", 1234) {
    server.open(1);
}

template <typename receive_value_type>
receive_value_type one_value_recipient<receive_value_type>::get_next() {
    receive_value_type sum;

    while (true) {
        size_t data_length = server.read((char*) &sum, sizeof(receive_value_type));

        if (data_length == 0) continue;
        break;
    }

    return sum;
}

#endif
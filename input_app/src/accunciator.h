#ifndef ACCUNCIATOR_H_
#define ACCUNCIATOR_H_

#include "static_buffer.h"
#include "client.h"
#include "consumption_production_switch.h"
#include "digit_string.h"

#include <cstring>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <algorithm>

template<size_t max_buffer_size>
class accunciator {
public:
    accunciator();
    void start(static_buffer<max_buffer_size>& buffer, consumption_production_switch& locker_switch);
private:
    client output;
};

template<size_t max_buffer_size>
accunciator<max_buffer_size>::accunciator(): output("127.0.0.1", 1234) {};

template<size_t max_buffer_size>
void accunciator<max_buffer_size>::start(static_buffer<max_buffer_size>& buffer, consumption_production_switch& locker_switch) {
    digit_string<max_buffer_size / 2> str;

    while (true) {
        locker_switch.going_to_consume();

        str.copy_from(buffer.get_raw_buffer(), buffer.get_size());
        buffer.clear();

        str.print(std::cout);
        std::cout << '\n';
        
        const unsigned long sum = str.get_sum_of_digits();
        output.write((const char*) &sum, sizeof(sum));
        locker_switch.consumption_ended();
    }
}

#endif
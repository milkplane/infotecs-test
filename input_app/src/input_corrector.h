#ifndef INPUT_CORRECTOR_H_
#define INPUT_CORRECTOR_H_

#include "client.h"
#include "static_buffer.h"
#include "consumption_production_switch.h"
#include "digit_string.h"

#include <cstring>
#include <mutex>
#include <iostream>
#include <chrono>
#include <condition_variable>

template<size_t max_buffer_size>
class input_corrector {
public:
    input_corrector();
    void start(static_buffer<max_buffer_size>& buffer, consumption_production_switch& locker_switch) const;
};

template<size_t max_buffer_size>
input_corrector<max_buffer_size>::input_corrector() {}

template<size_t max_buffer_size>
void input_corrector<max_buffer_size>::start(static_buffer<max_buffer_size>& buffer, consumption_production_switch& locker_switch) const {
    digit_string<max_buffer_size / 2> digits;

    while (true) {
        locker_switch.going_to_produce();

        std::cout << "Enter sequence of digits no more than " << max_buffer_size / 2 << " characters" << std::endl; 
        digits.input(std::cin);
        digits.reverse_sort();
        digits.replace_odds();
        
        buffer.copy_from(digits.get_raw_sring(), digits.get_size());

        locker_switch.production_ended();
    }
}

#endif
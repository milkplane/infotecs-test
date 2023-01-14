#ifndef INPUT_SUM_TRANSPONDER_H_
#define INPUT_SUM_TRANSPONDER_H_

#include "input_corrector.h"
#include "accunciator.h"
#include "static_buffer.h"
#include "consumption_production_switch.h"

#include <thread>
#include <mutex>
#include <condition_variable>

template<size_t max_buffer_size>
class input_sum_transponder {
public:
    input_sum_transponder() = default;
    void start();
private:
    std::mutex thread_locker;
    static_buffer<max_buffer_size> buffer;
    input_corrector<max_buffer_size> checker;
    accunciator<max_buffer_size> alerter;
    consumption_production_switch locker_switch;
};

template<size_t max_buffer_size>
void input_sum_transponder<max_buffer_size>::start() {
    std::thread check(&input_corrector<max_buffer_size>::start, checker, std::ref(buffer), std::ref(locker_switch));
    std::thread alert(&accunciator<max_buffer_size>::start, alerter, std::ref(buffer), std::ref(locker_switch));

    alert.join();
    check.join();
}

#endif
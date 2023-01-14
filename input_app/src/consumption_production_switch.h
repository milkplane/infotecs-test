#ifndef CONSUMPTION_PRODUCTION_SWITCH_H_
#define CONSUMPTION_PRODUCTION_SWITCH_H_

#include <condition_variable>
#include <mutex>

class consumption_production_switch{
public:
    consumption_production_switch();
    void going_to_produce();
    void production_ended();
    void going_to_consume();
    void consumption_ended();
private:
    bool is_really_produced;
    bool is_really_consumed;
    std::mutex mtx;
    std::unique_lock<std::mutex> production_locker;
    std::unique_lock<std::mutex> consumption_locker;
    std::condition_variable production_ended_alert;
    std::condition_variable consumption_ended_alert;
};

#endif
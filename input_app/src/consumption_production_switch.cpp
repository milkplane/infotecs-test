#include "consumption_production_switch.h"
#include <mutex>

consumption_production_switch::consumption_production_switch(): mtx(), production_locker(mtx, std::defer_lock), consumption_locker(mtx, std::defer_lock) {
    is_really_consumed = false;
    is_really_produced = false;
}

void consumption_production_switch::going_to_produce() {
    production_locker.lock();
}

void consumption_production_switch::production_ended() {
    is_really_produced = true;
    is_really_consumed = false;
    production_ended_alert.notify_all();
    consumption_ended_alert.wait(production_locker, [&](){
        return is_really_consumed;
    });
    production_locker.unlock();
}

void consumption_production_switch::going_to_consume() {
    consumption_locker.lock();
    production_ended_alert.wait(consumption_locker, [&](){
        return is_really_produced;
    });
}

void consumption_production_switch::consumption_ended() {
    is_really_consumed = true;
    is_really_produced = false;
    consumption_locker.unlock();
    consumption_ended_alert.notify_all();
}
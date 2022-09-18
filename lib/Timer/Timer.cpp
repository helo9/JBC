#include "Timer.hpp"
#include <assert.h>

Timer *Timer::_all_timers[] = {nullptr};
size_t Timer::_timer_count = 0;

Timer::Timer(QueueTimerEventFunction fun)
    : _queue_event(fun) {
    
    assert(_timer_count < max_timer_instances);
    
    _all_timers[_timer_count] = this;
    _timer_count++;
}

void Timer::onSysTick() {
    for (size_t i=0; i<_timer_count; i++) {
        _all_timers[i]->_onSysTick();
    }
}

void Timer::start(const millis_t delay, const bool periodic) {
    _count = 1000;
    _reset_count = periodic ? delay : 0U;
}

void Timer::stop() {
    _reset_count = 0;
    _count = 0;
}

void Timer::_onSysTick() {
    if (_count > 1) {
        
        _count--;

    } else if (_count == 1) {
        _queue_event();

        _count = (_reset_count > 0) ? _reset_count : 0;
    }

}

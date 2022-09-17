#include "Timer.hpp"
#include <stdio.h>

Timer::Timer(millis_t interval_ms)
    : _target_interval_ms(interval_ms) {};

void Timer::start(const millis_t now_ms) {
    _state = WAITING;

    _last_now_ms = now_ms;
    _last_expired_ms = now_ms;

    update(now_ms);
}

void Timer::update(const millis_t now_ms) {

    const bool timer_overflow = false; //now_ms < _last_now_ms;
    _last_now_ms = now_ms;

    const bool timer_expired = [&]() {
        if (_state == WAITING_OVERFLOW || timer_overflow) {
            const millis_t passed_ms = max_millis_t - _last_expired_ms + now_ms;
            return passed_ms > _target_interval_ms;
        } else if (_state == WAITING) {
            return now_ms > (_last_expired_ms + _target_interval_ms);
        } else {
            return true;
        }
    } ();
    
    switch (_state) {
    case (NOT_STARTED):
        break;
    case (WAITING): {
            if (timer_expired) {
                _last_expired_ms = now_ms;
                _state = EXPIRED;
            } else if (timer_overflow) {
                _state = WAITING_OVERFLOW;
            } else {
                // nothing relevant happend, stay here
            }
        } break;
    case (WAITING_OVERFLOW): {
            if (timer_expired) {
                _last_expired_ms = now_ms;
                _state = EXPIRED;
            }
        } break;
    case (EXPIRED): {
            if (timer_overflow) {
                _state = EXPIRED_OVERFLOW;
            } else {
                // nothing relevant happend, stay here
            }
        } break;
    case (EXPIRED_OVERFLOW):
        // we only leave this state with reset
        break;
    }
}

void Timer::reset_expired() {
    switch (_state) {
    case (EXPIRED):
        _state = WAITING;
        break;
    case (EXPIRED_OVERFLOW):
        _state = WAITING_OVERFLOW;
        break;
    default:
        // nothing to reset..
        break;
    }
}

bool Timer::is_expired() const {
    switch (_state) {
    case (EXPIRED):
    case (EXPIRED_OVERFLOW):
        return true;
    default:
        return false;
    }
}

#ifndef TIMER_HPP
#define TIMER_HPP

typedef unsigned long millis_t;
static constexpr millis_t max_millis_t = 4294967295;

typedef millis_t (*get_millis_fun)();

class Timer {

    enum TimerStates {
        NOT_STARTED,
        WAITING,
        WAITING_OVERFLOW,
        EXPIRED,
        EXPIRED_OVERFLOW
    };

public:

    Timer(millis_t interval_ms);

    void start(millis_t now_ms);

    void update(millis_t now_ms);
    void reset_expired();

    bool is_expired() const;

private:

    const millis_t _target_interval_ms;
    TimerStates _state;
    millis_t _last_now_ms;
    millis_t _last_expired_ms;

};

#endif // TIMER_HPP

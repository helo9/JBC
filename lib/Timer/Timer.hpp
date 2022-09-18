#ifndef TIMER_HPP
#define TIMER_HPP

#include <stddef.h>

typedef unsigned long millis_t;

constexpr size_t max_timer_instances = 10;

typedef void (*QueueTimerEventFunction)();

class Timer {

public:

    static void onSysTick();

    explicit Timer(QueueTimerEventFunction fun);

    void start(millis_t delay, bool periodic=true);

    void stop();

private:

    void _onSysTick();

    static Timer *_all_timers[10];
    static size_t _timer_count;

    QueueTimerEventFunction _queue_event;
    volatile millis_t _count = 0UL;
    millis_t _reset_count = 0UL;
};

#endif // TIMER_HPP

#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <stdint.h>

enum class EventTypes {
    timer,
    button
};

struct Event {
    EventTypes type;
    uint8_t data;
    uint8_t data2;
};

#endif // EVENTS_HPP
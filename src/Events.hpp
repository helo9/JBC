#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <stdint.h>

enum class ApplicationEvent {
    regulation_pending,
    menu_up,
    menu_down,
    menu_next,
    update_display,
    check_config
};

#endif // EVENTS_HPP

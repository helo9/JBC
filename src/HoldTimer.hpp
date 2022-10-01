#ifndef HOLD_TIMER_HPP
#define HOLD_TIMER_HPP

#include <stddef.h>

namespace holdtimer {

void update(float temperature, unsigned long now_ms);
void create_status(char *buffer, size_t len, unsigned long now_ms);

}

#endif // HOLD_TIMER_HPP

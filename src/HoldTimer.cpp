#include "HoldTimer.hpp"
#include <SwitchingRegulator.hpp>
#include <stdio.h>

bool is_holding = false;
SwitchingRegulator holding_switch(80, 77);
unsigned long start_ms;

void holdtimer::update(float temperature, unsigned long now_ms) {
    
    bool new_is_holding = !holding_switch.calc_new_command(temperature);

    if (is_holding != new_is_holding) {
        is_holding = new_is_holding;
        start_ms = now_ms;
    }
}

void holdtimer::create_status(char *buffer, size_t len, unsigned long now_ms) {
    if (is_holding) {
        const auto diff_ms = now_ms - start_ms;
        const unsigned long diff_s = diff_ms / 1000;

        snprintf(buffer, len, "hold: %5ld", diff_s);
    } else {
        snprintf(buffer, len, "Not there :(");
    }
}

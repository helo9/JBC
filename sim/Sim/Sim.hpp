#ifndef ARDUINO_SIM_HPP
#define ARDUINO_SIM_HPP

#include <bsp.hpp>

struct SimState {
    float temperature = 0.0f;
    bool heater1_on = false;
    bool heater2_on = false;
};

void sim_setup();
void setup();

void sim_loop(SimState &state);
void loop();

#endif // ARDUINO_SIM_HPP

#ifndef ARDUINO_SIM_HPP
#define ARDUINO_SIM_HPP

#include <bsp.hpp>

void sim_setup();
void setup();

void sim_loop(float &temperature, const bool heater1_on, const bool heater2_on);
void loop();

#endif // ARDUINO_SIM_HPP

#ifndef SIM_BSP_HPP
#define SIM_BSP_HPP

#include <SimTypes.hpp>
#include <bsp.hpp>

void sim_setup();
void setup();

void sim_loop(SimState &state);
void loop();

#endif // SIM_BSP_HPP

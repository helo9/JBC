#ifndef REGULATION_HPP
#define REGULATION_HPP

#include <SwitchingRegulator.hpp>

namespace regulation {

struct HeaterCommand {
    bool heater1_on;
    bool heater2_on;
};

HeaterCommand run_regulation(float temperature);
void update_parameters(const int *config_temperatures);

}

#endif // REGULATION_HPP

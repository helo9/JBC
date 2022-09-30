#include "Regulation.hpp"

SwitchingRegulator regulator_heater1(82, 80);
SwitchingRegulator regulator_heater2(80, 75);

regulation::HeaterCommand regulation::run_regulation(const float temperature) {
    
    const bool heater1_on = regulator_heater1.calc_new_command(temperature);
    const bool heater2_on = regulator_heater2.calc_new_command(temperature);

    return regulation::HeaterCommand {heater1_on, heater2_on};
}

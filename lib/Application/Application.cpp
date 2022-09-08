#include <SwitchingRegulator.hpp>
#include "Application.hpp"

const BoardAPI *_api = nullptr;

SwitchingRegulator regulator_heater1(80);
SwitchingRegulator regulator_heater2(80, 75);

void application_setup(const BoardAPI *api) {
    _api = api;
}

void application_loop() {
    const float temperature = _api->get_temperature_celsius();
    
    const bool heater1_on = regulator_heater1.calc_new_command(temperature);
    _api->set_heater1(heater1_on);

    const bool heater2_on = regulator_heater2.calc_new_command(temperature);
    _api->set_heater2(heater2_on);
}

#include <SwitchingRegulator.hpp>
#include <Timer.hpp>
#include "Application.hpp"

const BoardAPI *_api = nullptr;

SwitchingRegulator regulator_heater1(82, 80);
SwitchingRegulator regulator_heater2(80, 75);

Timer timer(250);

void application_setup(const BoardAPI *api) {
    _api = api;

    timer.start(_api->get_millis());
}

void application_loop() {

    const millis_t now_ms = _api->get_millis();
    
    timer.update(now_ms);
    
    if (timer.is_expired()) {
        
        timer.reset_expired();

        const float temperature = _api->get_temperature_celsius();
        
        const bool heater1_on = regulator_heater1.calc_new_command(temperature);
        _api->set_heater1(heater1_on);

        const bool heater2_on = regulator_heater2.calc_new_command(temperature);
        _api->set_heater2(heater2_on);

    }
    
}

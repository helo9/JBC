#ifdef ARDUINO
    #include <bsp_ardu.hpp>
    #include <Arduino.h>
#else
    #include <Sim.hpp>
#endif
#include <SwitchingRegulator.hpp>
#include <Timer.hpp>

SwitchingRegulator regulator_heater1(82, 80);
SwitchingRegulator regulator_heater2(80, 75);

Timer timer(250);

void setup(void) {

    board::setup();

    timer.start(board::millis());
}

void loop(void) {

    const millis_t now_ms = board::millis();
    
    timer.update(now_ms);
    
    if (timer.is_expired()) {
        
        timer.reset_expired();

        const float temperature = board::get_temperature_celsius();
        
        const bool heater1_on = regulator_heater1.calc_new_command(temperature);
        board::set_heater1(heater1_on);

        const bool heater2_on = regulator_heater2.calc_new_command(temperature);
        board::set_heater2(heater2_on);

    }
}

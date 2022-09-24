#ifdef ARDUINO
    #include <bsp_ardu.hpp>
    #include <Arduino.h>
#else
    #include <SimBsp.hpp>
#endif
#include <DebounceFilter.hpp>
#include <SwitchingRegulator.hpp>
#include <Timer.hpp>
#include <stdio.h>

SwitchingRegulator regulator_heater1(82, 80);
SwitchingRegulator regulator_heater2(80, 75);

volatile bool timer_event = false;

void set_timer_event() {
    timer_event = true;
}

void reset_timer_event() {
    timer_event = false;
}

Timer timer(set_timer_event);

unsigned long counter = 1000;

void setup(void) {

    board::setup();

    timer.start(250, true);
}

void loop(void) {
    
    if (timer_event) {
        
        reset_timer_event();

        const float temperature = board::get_temperature_celsius();
        
        const bool heater1_on = regulator_heater1.calc_new_command(temperature);
        board::set_heater1(heater1_on);

        const bool heater2_on = regulator_heater2.calc_new_command(temperature);
        board::set_heater2(heater2_on);
    }
}

void board_evt_handler::on_systick() {
    Timer::onSysTick();
}

void board_evt_handler::on_button_event(board_evt_handler::Button btn, board_evt_handler::ButtonEvent evt) {
    char msg[50] = {};
    snprintf(msg, 50, "%d %d\n", 
        static_cast<int>(btn), static_cast<int>(evt));
    board::print(msg);
}

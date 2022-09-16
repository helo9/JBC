#include "Sim.hpp"
#include <chrono>
#include <map>
#include <stdio.h>

using namespace std::chrono;

SimState _state = {};

float board::get_temperature_celsius() {
    return _state.temperature;
}

void board::set_heater1(bool on) {
    _state.heater1_on = on;
}

void board::set_heater2(bool on) {
    _state.heater2_on = on;
}

unsigned long board::millis() {
    static const auto start = system_clock::now();

    const auto now = system_clock::now();

    const auto time_difference = duration_cast<milliseconds>(now - start);

    return time_difference.count();
}

void board::print(const char str[]) {
    printf(str);
}

void board::setup() {
    millis();
}

// Forward declared Arduino main functions
void setup();
void loop();

int main() {

    printf("SIM: Running setup\n");
    
    sim_setup();
    setup();
    

    while (true) {
        sim_loop(_state);
        loop();
    }
    
    return 0;
}

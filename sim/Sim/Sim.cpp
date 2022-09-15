#include "Sim.hpp"
#include <chrono>
#include <map>
#include <stdio.h>

using namespace std::chrono;

struct SimState {
    float temperature = 0.0f;
    bool heater1_on = false;
    bool heater2_on = false;
};

SimState _state = {};

float get_temperature_celsius() {
    return _state.temperature;
}

void set_heater1(bool on) {
    _state.heater1_on = on;
}

void set_heater2(bool on) {
    _state.heater2_on = on;
}

unsigned long millis() {
    static const auto start = system_clock::now();

    const auto now = system_clock::now();

    const auto time_difference = duration_cast<milliseconds>(now - start);

    return time_difference.count();
}

void print(const char str[]) {
    printf(str);
}

const BoardAPI board_api = {
    get_temperature_celsius,
    set_heater1,
    set_heater2,
    millis,
    print
};

void board_setup() {
    millis();
};

// Forward declared Arduino main functions
void setup();
void loop();

int main() {

    printf("SIM: Running setup\n");
    
    sim_setup();
    setup();
    

    while (true) {
        sim_loop(_state.temperature, _state.heater1_on, _state.heater2_on);
        loop();
    }
    
    return 0;
}

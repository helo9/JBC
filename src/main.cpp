#include <Application.hpp>
#include <Arduino.h>

#define HEATER1_PIN
#define HEATER2_PIN
#define MEASUREMENT_PIN

float get_temperature_celsius();
void set_heater1(bool on);
void set_heater2(bool on);

const BoardAPI api = {
    get_temperature_celsius,
    set_heater1,
    set_heater2
};

void setup() {
    application_setup(&api);
}

void loop() {
    application_loop();
}

float get_temperature_celsius() {
    return 0.0f;
}

void set_heater1(bool on) {};
void set_heater2(bool on) {};

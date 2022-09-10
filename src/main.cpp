#include <Application.hpp>
#include <Arduino.h>

static constexpr int heater1_pin = 0;
static constexpr int heater2_pin = 1;
static constexpr int measurement_pin = A0;

float get_temperature_celsius();
void set_heater1(bool on);
void set_heater2(bool on);

const BoardAPI api = {
    get_temperature_celsius,
    set_heater1,
    set_heater2,
    millis
};

void setup() {
    pinMode(heater1_pin, OUTPUT);
    pinMode(heater2_pin, OUTPUT);

    application_setup(&api);
}

void loop() {
    application_loop();
}

float get_temperature_celsius() {
    return (float)analogRead(measurement_pin);
}

void set_heater1(bool on) {
    digitalWrite(heater1_pin, (int)on);
};
void set_heater2(bool on) {
    digitalWrite(heater2_pin, (int)on);
};

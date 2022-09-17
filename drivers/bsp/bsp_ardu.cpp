#include <bsp.hpp>
#include <Arduino.h>

static constexpr int heater1_pin = 0;
static constexpr int heater2_pin = 1;
static constexpr int measurement_pin = A0;

void board::setup() {
    pinMode(heater1_pin, OUTPUT);
    pinMode(heater2_pin, OUTPUT);

    Serial.begin(115200);
}

float board::get_temperature_celsius() {
    return (float)analogRead(measurement_pin);
}

void board::set_heater1(bool on) {
    digitalWrite(heater1_pin, (int)on);
}

void board::set_heater2(bool on) {
    digitalWrite(heater2_pin, (int)on);
}

void board::print(const char str[]) {
    Serial.print(str);
}

int board::serial_available() {
    return Serial.available();
}

char board::serial_read() {
    return Serial.read();
}

unsigned long board::millis() {
    return millis();
}

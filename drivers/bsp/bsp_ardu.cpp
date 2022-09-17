#include <bsp.hpp>
#include <Arduino.h>

constexpr int heater1_pin = 13;
constexpr int heater2_pin = 4;
constexpr int measurement_pin = A0;
constexpr float vt_factor = 1.83;
constexpr float offset = -24.4;


void board::setup() {
    pinMode(heater1_pin, OUTPUT);
    pinMode(heater2_pin, OUTPUT);

    Serial.begin(115200);
}

float board::get_temperature_celsius() {
    const int sensorvalue = analogRead(measurement_pin);
    const float voltage = sensorvalue * (5.0 / 1023.0);

    const float temp_c = (((voltage * 100) / vt_factor) + offset);

    return temp_c;
}

void board::set_heater1(bool on) {
    digitalWrite(heater1_pin, (int)on);
}

void board::set_heater2(bool on) {
    digitalWrite(heater2_pin, (int)on);
}

void board::print(const char str[]) {
    Serial.print(str);
    Serial.flush();
}

unsigned long board::millis() {
    return ::millis();
}

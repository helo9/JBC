#include <chrono>
#include <map>
#include <stdio.h>

using namespace std::chrono;

unsigned long millis() {
    static const auto start = system_clock::now();

    const auto now = system_clock::now();

    const auto time_difference = duration_cast<milliseconds>(now - start);

    return time_difference.count();
}

void pinMode(int pin, int mode) {};

std::map<int, int> analog_pin_values;

int analogRead(int pin) {
    const auto it = analog_pin_values.find(pin);

    if (it == analog_pin_values.end()) {
        return 0;
    } else {
        return it->second;
    }
}

void analogWrite(int pin, int value) {
    analog_pin_values[pin] = value;
}

std::map<int, int> digital_pin_values;

int digitalRead(int pin) {
    const auto it = digital_pin_values.find(pin);

    if (it == digital_pin_values.end()) {
        return 0;
    } else {
        return it->second;
    }
}

void digitalWrite(int pin, int value) {
    digital_pin_values[pin] = value;
}

// Forward declared Arduino main functions
void setup();
void loop();

int main() {

    millis();

    printf("SIM: Running setup\n");
    setup();

    while (true) {
        loop();
    }
    
    return 0;
}

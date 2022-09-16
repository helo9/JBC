#ifndef BSP_HPP
#define BSP_HPP

namespace board {

void setup();

float get_temperature_celsius();
void set_heater1(bool on);
void set_heater2(bool on);
void print(const char str[]);

unsigned long millis();

}

#endif // BSP_HPP

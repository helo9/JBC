#ifndef BSP_HPP
#define BSP_HPP

struct BoardAPI {
    float (*get_temperature_celsius)();
    void (*set_heater1)(bool on);
    void (*set_heater2)(bool on);
    unsigned long (*get_millis)();
    void (*print)(const char str[]);
};

void board_setup();

extern const BoardAPI board_api;

#endif // BSP_HPP

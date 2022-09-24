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

// Handlers to be implemented on application side
namespace board_evt_handler {

enum Button {
    Up,
    Down,
    Next,
    _end_ // only to mark end, write nothing behind
};

enum ButtonEvent {
    Released,
    Pressed
};

void on_systick();

void on_button_event(Button button, ButtonEvent evt);

}

#endif // BSP_HPP

#include <DebounceFilter.hpp>
#include <bsp.hpp>
#include <Arduino.h>

constexpr int button_pins[] = {5, 6, 7};
constexpr int button_debounce_delay_ms = 50;
constexpr int heater1_pin = 4;
constexpr int heater2_pin = 3;
constexpr int measurement_pin = A0;
constexpr float vt_factor = 1.83;
constexpr float offset = -24.4;

DebounceFilter _button_filters[] = {
    DebounceFilter(button_debounce_delay_ms),
    DebounceFilter(button_debounce_delay_ms),
    DebounceFilter(button_debounce_delay_ms),
};

static void enable_systick_isr() {
    noInterrupts();
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    interrupts();
}

void board::setup() {
    enable_systick_isr();

    pinMode(heater1_pin, OUTPUT);
    pinMode(heater2_pin, OUTPUT);

    for (int button_no=0; button_no<board_evt_handler::Button::_end_; button_no++) {
        pinMode(button_pins[button_no], INPUT_PULLUP);
    }

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

SIGNAL(TIMER0_COMPA_vect) 
{
    for (int button_no=0; button_no<board_evt_handler::Button::_end_; button_no++) {
        const bool val = static_cast<bool>(digitalRead(button_pins[button_no]));
        const auto transition = _button_filters[button_no].update(val);

        const auto btn= static_cast<board_evt_handler::Button>(button_no);

        switch (transition) {
        case (DebounceFilter::ValueTransition::transition_up):
            board_evt_handler::on_button_event(btn, board_evt_handler::ButtonEvent::Released);
            break;
        case (DebounceFilter::ValueTransition::transition_down):
            board_evt_handler::on_button_event(btn, board_evt_handler::ButtonEvent::Pressed);
            break;
        default:
            // not of interest
            break;
        }
    }

    board_evt_handler::on_systick();
} 

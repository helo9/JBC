#include <DebounceFilter.hpp>
#include <bsp.hpp>
#include <LiquidCrystal.h>
#include <Arduino.h>

constexpr int button_pins[] = {6, 7, 8};
constexpr int button_debounce_delay_ms = 50;
constexpr int heater1_pin = 9;
constexpr int heater2_pin = 10;
constexpr int measurement_pin = A0;
constexpr float vt_factor = 1.83;
constexpr float offset = -24.4;
constexpr int lcd_rs_pin = 12, lcd_en_pin = 11, lcd_d4_pin = 5,
    lcd_d5_pin = 4, lcd_d6_pin = 3, lcd_d7_pin=2;
constexpr int lcd_num_rows = 2, lcd_num_cols = 16;

DebounceFilter _button_filters[] = {
    DebounceFilter(button_debounce_delay_ms),
    DebounceFilter(button_debounce_delay_ms),
    DebounceFilter(button_debounce_delay_ms),
};

LiquidCrystal lcd(lcd_rs_pin, lcd_en_pin, lcd_d4_pin, lcd_d5_pin, lcd_d6_pin, lcd_d7_pin);

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

    lcd.begin(lcd_num_cols, lcd_num_rows);
    lcd.clear();
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

void board::lcd_write(const char str[16], int row) {
    static char last_str[2][16] = {};
    int col=0;
    while (col<16) {
        if (str[col] != last_str[row][col]) {
            last_str[row][col] = str[col];
            if (str[col] == '\0') {
                break;
            } else {
                lcd.setCursor(col, row);
                lcd.write(str[col]);
            }
        }
        col++;
    }
    while(col<16){
        lcd.setCursor(col, row);
        lcd.write(" ");
        col++;
    }
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

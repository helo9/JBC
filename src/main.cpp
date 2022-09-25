#ifdef ARDUINO
    #include <bsp_ardu.hpp>
    #include <Arduino.h>
#else
    #include <SimBsp.hpp>
#endif
#include <DebounceFilter.hpp>
#include <SwitchingRegulator.hpp>
#include <RingBuffer.hpp>
#include <Timer.hpp>
#include <Events.hpp>
#include <stdio.h>
#include <assert.h>

constexpr size_t event_queue_size = 20;

void on_regulation_pending();
void run_regulation();
void on_display_update_required();
void update_display();

SwitchingRegulator regulator_heater1(82, 80);
SwitchingRegulator regulator_heater2(80, 75);

Timer regulation_timer(on_regulation_pending);
Timer display_timer(on_display_update_required);

RingBuffer<ApplicationEvent, event_queue_size> event_queue;

void setup(void) {

    board::setup();

    regulation_timer.start(250, true);
    display_timer.start(400, true);
}

void loop(void) {

    while(event_queue.count_free() == event_queue_size);
    
    ApplicationEvent current_event;
    if (!event_queue.get(&current_event)) {
        assert(0);
    }

    switch (current_event) {
        case (ApplicationEvent::regulation_pending): 
        {
            run_regulation();
            break;
        }
        case (ApplicationEvent::menu_up): 
        {
            board::print("Menu up :)\n");
            break;
        }
        case (ApplicationEvent::menu_down):
        {
            board::print("Menu down :)\n");
            break;
        }
        case (ApplicationEvent::menu_next):
        {
            board::print("Menu next :)\n");
            break;
        }
        case (ApplicationEvent::update_display):
        {
            update_display();
            break;
        }
        default:
            assert(0);
    }
}

void board_evt_handler::on_systick() {
    Timer::onSysTick();
}

void board_evt_handler::on_button_event(board_evt_handler::Button btn, board_evt_handler::ButtonEvent evt) {

    if (evt == board_evt_handler::ButtonEvent::Released) {
        return;
    }

    switch (btn) {
    case (board_evt_handler::Button::Down): {
            event_queue.put(ApplicationEvent::menu_down);
            break;
        }
    case (board_evt_handler::Button::Next): {
            event_queue.put(ApplicationEvent::menu_up);
            break;
        }
    case (board_evt_handler::Button::Up): {
            event_queue.put(ApplicationEvent::menu_next);
            break;
        }
    default:
        assert(0);
    }
}

void on_regulation_pending() {
    event_queue.put(ApplicationEvent::regulation_pending);
}

void run_regulation() {
    const auto temperature = board::get_temperature_celsius();
    
    const bool heater1_on = regulator_heater1.calc_new_command(temperature);
    board::set_heater1(heater1_on);

    const bool heater2_on = regulator_heater2.calc_new_command(temperature);
    board::set_heater2(heater2_on);

}

void on_display_update_required() {
    event_queue.put(ApplicationEvent::update_display);
}

void update_display() {
    board::print("\033[2JUpdate Display\n");
}
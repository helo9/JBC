#include "Menu.hpp"
#include "Regulation.hpp"
#include "PersistentConfiguration.hpp"
#include "HoldTimer.hpp"
#include <DebounceFilter.hpp>
#include <RingBuffer.hpp>
#include <Timer.hpp>
#include <Events.hpp>

#ifdef ARDUINO
    #include <bsp_ardu.hpp>
    #include <Arduino.h>
#else
    #include <SimBsp.hpp>
#endif
#include <assert.h>

constexpr size_t event_queue_size = 20;

void on_regulation_pending();
Timer regulation_timer(on_regulation_pending);

void on_display_update_required();
Timer display_timer(on_display_update_required);

void on_configuration_check_pending();
Timer configuration_check_timer(on_configuration_check_pending);

RingBuffer<ApplicationEvent, event_queue_size> event_queue;

void setup(void) {

    board::setup();

    menu::setup();

    regulation_timer.start(500, true);
    display_timer.start(200, true);
    configuration_check_timer.start(2500, true);
}

void loop(void) {

    static float temperature = 23.0f;

    while(event_queue.count_free() == event_queue_size);
    
    ApplicationEvent current_event;
    if (!event_queue.get(&current_event)) {
        assert(0);
    }

    switch (current_event) {
        case (ApplicationEvent::regulation_pending): 
        {
            temperature = board::get_temperature_celsius();

            const auto cmd = regulation::run_regulation(temperature);

            board::set_heater1(cmd.heater1_on);
            board::set_heater2(cmd.heater2_on);

            holdtimer::update(temperature, board::millis());

            break;
        }
        case (ApplicationEvent::menu_up): 
        {
            menu::on_button_up();
            board::print("Menu up :)\n");
            break;
        }
        case (ApplicationEvent::menu_down):
        {
            menu::on_button_down();
            board::print("Menu down :)\n");
            break;
        }
        case (ApplicationEvent::menu_next):
        {
            menu::on_button_next();
            board::print("Menu next :)\n");
            break;
        }
        case (ApplicationEvent::update_display):
        {
            char str[16] = "";

            menu::generate_string(str, 16, temperature);

            board::lcd_write(str, 0);

            holdtimer::create_status(str, 16, board::millis());

            board::lcd_write(str, 1);

            break;
        }
        case (ApplicationEvent::check_config):
        {
            if(menu::has_config_changed()) {
                regulation::update_parameters(menu::get_configuration());
                menu::reset_change_flag();
                board::print("Config has changed!\n");
            }
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

void on_display_update_required() {
    event_queue.put(ApplicationEvent::update_display);
}

void on_configuration_check_pending() {
    event_queue.put(ApplicationEvent::check_config);
}

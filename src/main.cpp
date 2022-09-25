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

void on_timer_event();

SwitchingRegulator regulator_heater1(82, 80);
SwitchingRegulator regulator_heater2(80, 75);

Timer timer(on_timer_event);

RingBuffer<Event, event_queue_size> event_queue;

void setup(void) {

    board::setup();

    timer.start(250, true);
}

void loop(void) {

    while(event_queue.count_free() == event_queue_size);
    
    Event current_event;
    if (!event_queue.get(&current_event)) {
        assert(0);
    }

    switch (current_event.type) {
        case (EventTypes::timer): 
        {
            const float temperature = board::get_temperature_celsius();
            
            const bool heater1_on = regulator_heater1.calc_new_command(temperature);
            board::set_heater1(heater1_on);

            const bool heater2_on = regulator_heater2.calc_new_command(temperature);
            board::set_heater2(heater2_on);
            
            break;
        }
        case (EventTypes::button): 
        {
            board::print("Irgendwas mit Button :)\n");
            break;
        }
    }
}

void board_evt_handler::on_systick() {
    Timer::onSysTick();
}

void board_evt_handler::on_button_event(board_evt_handler::Button btn, board_evt_handler::ButtonEvent evt) {
    const uint8_t button_no = static_cast<uint8_t>(btn);
    const uint8_t button_evt = static_cast<uint8_t>(evt);

    event_queue.put(Event {
        EventTypes::button,
        button_no,
        button_evt
    });
}

void on_timer_event() {
    event_queue.put(Event {
        EventTypes::timer, 0, 0
    });
}
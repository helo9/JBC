#ifdef ARDUINO
    #include <bsp_ardu.hpp>
    #include <Arduino.h>
#else
    #include <Sim.hpp>
#endif
#include <SwitchingRegulator.hpp>
#include <Timer.hpp>
#include <RingBuffer.hpp>
#include <cstdint>

constexpr size_t event_queue_length = 20;

enum class EventType {
    RegulatorTimerExpired,
    SerialCharacterReceived,
};

struct Event {
    EventType type;
    uint8_t data;
};

RingBuffer<Event, event_queue_length> event_queue;

SwitchingRegulator regulator_heater1(82, 80);
SwitchingRegulator regulator_heater2(80, 75);

Timer regulator_timer(250);

void setup(void) {

    board::setup();

    regulator_timer.start(board::millis());
}

void loop(void) {
    {
        const millis_t now_ms = board::millis();
    
        regulator_timer.update(now_ms);

        if (regulator_timer.is_expired()) {
            regulator_timer.reset_expired();
            event_queue.put(Event {EventType::RegulatorTimerExpired, 0});
        }

        while (board::serial_available() > 0) {
            const char c = board::serial_read();
            event_queue.put(Event {EventType::SerialCharacterReceived, static_cast<uint8_t>(c)});
        }
    }
    
    const size_t pending_events = event_queue_length - event_queue.count_free();

    if (pending_events == 0) {
        return;
    }

    Event evt;

    while (event_queue.get(&evt)) {
        switch (evt.type) {
        case EventType::RegulatorTimerExpired: {
            const float temperature = board::get_temperature_celsius();
            
            const bool heater1_on = regulator_heater1.calc_new_command(temperature);
            board::set_heater1(heater1_on);

            const bool heater2_on = regulator_heater2.calc_new_command(temperature);
            board::set_heater2(heater2_on);
        } break;
        case EventType::SerialCharacterReceived: {
            const char str[] = {static_cast<char>(evt.data), '\0'};
            board::print(str);
        }
        default:
            break;
        }
    }
}

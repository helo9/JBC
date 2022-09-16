#include "Sim.hpp"

#ifdef SIMGUI

#include <zmq.hpp>
#include <vector>
#include <chrono>
#include <bit>
#include <cstring>
#include <stdio.h>

using MsgData = std::vector<char>;

constexpr size_t mininmal_message_length = 2;
constexpr char bind_addr[] = "tcp://127.0.0.1:5557";
constexpr auto timeout = std::chrono::milliseconds(0);

zmq::context_t context(1);

zmq::socket_t rep(context, ZMQ_REP);

std::vector<zmq::pollitem_t> items = {
    { rep, 0, ZMQ_POLLIN, 0 },
};

static zmq::message_t build_accept_reply () {
    return zmq::message_t ("S", 1);
}
static zmq::message_t build_failure_reply () {
    return zmq::message_t ("F", 1);
}
static zmq::message_t build_value_reply (int value) {
    auto msg = zmq::message_t(5);

    auto raw_data = msg.data<char>();
    raw_data[0] = 'V';
    raw_data[4] = value & 0xFF;
    raw_data[3] = ( value >> 8 ) & 0xFF;
    raw_data[2] = ( value >> 16 ) & 0xFF;
    raw_data[1] = (value >> 24 ) & 0xFF;

    return msg;
}

static int get_value(const char *raw_data) {
    int value = 0;

    value |= raw_data[0] << 24;
    value |= raw_data[1] << 16;
    value |= raw_data[2] << 8;
    value |= raw_data[3];

    return value;
}

void sim_setup() {
    rep.bind(bind_addr);
}

void sim_loop(SimState &state) {
    zmq::message_t msg;
    zmq::poll (items, timeout);

    if (items[0].revents & ZMQ_POLLIN) {
        const auto res = rep.recv(msg);

        if (!res || res.value() < mininmal_message_length) {
            return;
        }

        const auto n = res.value();
        const auto *raw_data = msg.data<char>();

        const char field = raw_data[0];
        const char opcode = raw_data[1];
        
        if (opcode == 'W') {

            switch (field) {
            case 'T': {
                int value = get_value(&raw_data[2]);
                state.temperature = static_cast<float>(value);
                printf("Set new temp %f\n", state.temperature);
                rep.send(build_accept_reply(), zmq::send_flags::dontwait);
            } break;
            default:
                rep.send(build_failure_reply(), zmq::send_flags::dontwait);
                break;
            }        
        } else if (opcode == 'R') {
            switch (field) {
                case 'A': {
                    auto msg = build_value_reply(static_cast<int>(state.heater1_on));
                    rep.send(msg, zmq::send_flags::dontwait);
                } break;
                case 'B': {
                    auto msg = build_value_reply(static_cast<int>(state.heater2_on));
                    rep.send(msg, zmq::send_flags::dontwait);
                } break;
                default:
                    rep.send(build_failure_reply(), zmq::send_flags::dontwait);
                    break;
            }
        
        } else {
        
            rep.send(build_failure_reply(), zmq::send_flags::dontwait);
        
        }
    }
}

#else

void sim_setup() {};
void sim_loop(SimState &state) {};

#endif // SIMGUI

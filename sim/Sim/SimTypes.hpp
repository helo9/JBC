#ifndef SIM_TYPES_HPP
#define SIM_TYPES_HPP

struct SimState {
    float temperature = 0.0f;
    bool heater1_on = false;
    bool heater2_on = false;
};

#endif // SIM_TYPES_HPP
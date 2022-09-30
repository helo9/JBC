#ifndef REGULATION_HPP
#define REGULATION_HPP

#include <SwitchingRegulator.hpp>

namespace regulation {

struct HeaterCommand {
    bool heater1_on;
    bool heater2_on;
};

HeaterCommand run_regulation(float temperature);

}

#endif // REGULATION_HPP

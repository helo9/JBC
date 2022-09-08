#include "SwitchingRegulator.hpp"

SwitchingRegulator::SwitchingRegulator(float limit)
    :SwitchingRegulator(limit, limit) {};

SwitchingRegulator::SwitchingRegulator(float limit_up, float limit_down)
    :_limit_up(limit_up), _limit_down(limit_down) {};

bool SwitchingRegulator::calc_new_command(float measurement) {
    if (_was_above_limit) {
        if (measurement < _limit_down) {
            _was_above_limit = false;
            return true;
        } else {
            return false;
        }
    } else {
        if (measurement > _limit_up) {
            _was_above_limit = true;
            return false;
        } else {
            return true;
        }
    }
}

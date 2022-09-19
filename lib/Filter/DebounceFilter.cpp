#include "DebounceFilter.hpp"
#include <stdio.h>

DebounceFilter::ValueTransition DebounceFilter::update(bool val) {

    ValueTransition transition = ValueTransition::no_transition;

    switch (_state) {
    case State::idle: {
        if (val != _last_value) {
            _state = potential_transition;
            _new_value_repetitions = 1;
        }

        }
        break;
    case State::potential_transition:
        if (val == _last_value) {
            _state = idle;
        } else {
            _new_value_repetitions++;

            if (_new_value_repetitions > _minimal_value_repetitions_for_transition) {
                _state = State::idle;
                _last_value = val;
                transition = val ? ValueTransition::transition_up : ValueTransition::transition_down;
            }
        }
        break;
    }

    printf("%d\n", _new_value_repetitions);

    return transition;
}
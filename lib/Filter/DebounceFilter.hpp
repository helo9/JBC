#ifndef DEBOUNCE_FILTER_HPP
#define DEBOUNCE_FILTER_HPP

#include <stddef.h>


class DebounceFilter {
public:
    DebounceFilter(size_t minimal_value_repetitions_for_transition, bool initial_value=false)
        :_last_value(initial_value), 
         _minimal_value_repetitions_for_transition(minimal_value_repetitions_for_transition) {};

    enum class ValueTransition {
        no_transition,
        transition_up,
        transition_down
    };

    ValueTransition update(bool val);

private:
    enum State {
        idle,
        potential_transition
    };

    State _state = State::idle;

    bool _last_value;
    size_t _new_value_repetitions = 0U;
    const size_t _minimal_value_repetitions_for_transition;
};

#endif // DEBOUNCE_FILTER_HPP
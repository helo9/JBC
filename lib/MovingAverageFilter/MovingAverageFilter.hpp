#ifndef MOVING_AVERAGE_FILTER_HPP
#define MOVING_AVERAGE_FILTER_HPP

#include <stddef.h>

template<class type, size_t N>
class MovingAverageFilter {

public:

    void store(const type value) {
        _raw_buffer[_write_index] = value;
        _write_index++;

        if (_write_index == N) {
            _write_index = 0U;
        }
    }

    type calculate() {

        type sum = static_cast<type>(0), tmp;
        
        for (size_t i=0U; i<N; i++) {
            sum += _raw_buffer[i];
        }

        return sum / N;      
    }

private:

    type _raw_buffer[N] = {};
    size_t _write_index = 0;
};

#endif // MOVING_AVERAGE_FILTER_HPP

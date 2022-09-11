#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <stddef.h>

template<class element_type, size_t N>
class RingBuffer {
public:

    bool put(const element_type element) {
        auto next_write_index = _write_index + 1;
        if (next_write_index == N+1) {
            next_write_index = 0U;
        }
        if (next_write_index != _read_index) {
            _buffer[_write_index] = element;
            _write_index = next_write_index;
            return true;
        } else {
            return false;
        }
    };

    bool get(element_type *element) {
        if (_write_index == _read_index) {
            return false;
        } else {
            *element = _buffer[_read_index];
            _read_index++;
            if (_read_index == N+1) {
                _read_index = 0U;
            }
            return true;
        }
        return false;
    };

    size_t count_free() const {
        if (_write_index == _read_index) {
            return N;
        } else if (_write_index < _read_index) {
            return (_read_index - _write_index);
        } else /* _write_index > _read_index*/ {
            return (N - _write_index + _read_index);
        }
    };

private:

    element_type _buffer[N+1] = {};

    size_t _write_index = 0;
    size_t _read_index = 0;

};

#endif // RINGBUFFER_HPP

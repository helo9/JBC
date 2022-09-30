#ifndef SWITCHING_CONTROL
#define SWITCHING_CONTROL

class SwitchingRegulator {
public:
    explicit SwitchingRegulator(float limit);
    SwitchingRegulator(float limit_up, float limit_down);

    bool calc_new_command(float measurement);

    inline void set_limit_up(float limit) {
        _limit_up = limit;
    };

    inline void set_limit_down(float limit) {
        _limit_down = limit;
    };

private:
    float _limit_up;
    float _limit_down;
    bool _was_above_limit = false;
};

#endif // SWITCHING_CONTROL

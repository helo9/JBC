#ifndef SWITCHING_CONTROL
#define SWITCHING_CONTROL

class SwitchingRegulator {
public:
    explicit SwitchingRegulator(float limit);
    SwitchingRegulator(float limit_up, float limit_down);

    bool calc_new_command(float measurement);

private:
    const float _limit_up;
    const float _limit_down;
    bool _was_above_limit = false;
};

#endif // SWITCHING_CONTROL

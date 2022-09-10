#ifndef APPLICATION_H
#define APPLICATION_H

struct BoardAPI {
    float (*get_temperature_celsius)();
    void (*set_heater1)(bool on);
    void (*set_heater2)(bool on);
    unsigned long (*get_millis)();
};

void application_setup(const BoardAPI *api);
void application_loop();

#endif // APPLICATION_H

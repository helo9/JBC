#ifdef ARDUINO
    #include <bsp_ardu.hpp>
    #include <Arduino.h>
#else
    #include <Sim.hpp>
#endif
#include <bsp.hpp>
#include <Application.hpp>

void setup(void) {

    board_setup();

    application_setup(&board_api);
}

void loop(void) {
    application_loop();
}

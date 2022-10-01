#ifndef MENU_HPP
#define MENU_HPP

#include <stddef.h>

namespace menu {

    bool has_config_changed();
    const int *get_configuration();
    void reset_change_flag();

    void generate_string(char *str, size_t len, float temperature);

    void on_button_up();
    void on_button_next();
    void on_button_down();

    void setup();
};

#endif // MENU_HPP

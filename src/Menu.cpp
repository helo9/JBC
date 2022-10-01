#include "Menu.hpp"
#include <stdio.h>
#include <string.h>

#define MENU_PAGE_INFO 0

static const char _conf_temp_names[4][8] = {
    "H1-UP: ",
    "H1-DN: ",
    "H2-up: ",
    "H2-DN: "
};

int _conf_temps[4] = {
    82, 80, 80, 75
};

bool _conf_has_changed = false;
int _current_page = 0;

static int &get_selected_configuration_temperature() {
    return _conf_temps[_current_page-1];
}

bool menu::has_config_changed() {
    return _conf_has_changed;
}

const int *menu::get_configuration() {
    return _conf_temps;
}

void menu::reset_change_flag() {
    _conf_has_changed = false;
}

void menu::generate_string(char *str, size_t len, float temperature) {

    if (_current_page == 0) {
        snprintf(str, len, "T: %3d", static_cast<int>(temperature));
    } else {
        memcpy((void*)str, (const void*)(_conf_temp_names[_current_page-1]), 7);
        if (len > 5) {
            snprintf(&str[6], len - 6, "%3d", get_selected_configuration_temperature());
        }
    }
}

void menu::on_button_up() {
    if (_current_page == 0) {
        return;
    }

    get_selected_configuration_temperature()++;
    
    if (!_conf_has_changed) {
        _conf_has_changed = true;
    }
}

void menu::on_button_next() {
    _current_page += 1;

    if (_current_page >= 5) {
        _current_page = 0;
    }
}

void menu::on_button_down() {
    if (_current_page == 0) {
        return;
    }
    
    get_selected_configuration_temperature()--;

    if (!_conf_has_changed) {
        _conf_has_changed = true;
    }
}

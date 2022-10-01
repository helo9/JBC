#include "Menu.hpp"
#include <stdio.h>
#include <string.h>
#include <PersistentConfiguration.hpp>

#define MENU_PAGE_INFO 0

static const char _conf_temp_names[4][8] = {
    "H1-UP: ",
    "H1-DN: ",
    "H2-UP: ",
    "H2-DN: "
};

config::temperatures temps;

bool _conf_has_changed = false;
int _current_page = 0;

void menu::setup(){
    config::load(temps);
}

static int &get_selected_configuration_temperature() {
    return ((int*)(&temps))[_current_page-1];
}

bool menu::has_config_changed() {
    return _conf_has_changed;
}

const int *menu::get_configuration() {
    return (int*)(&temps);
}

void menu::reset_change_flag() {
    _conf_has_changed = false;
}

void menu::generate_string(char *str, size_t len, float temperature) {

    if (_current_page == 0) {
        snprintf(str, len, "T: %3d", static_cast<int>(temperature));
    } else {
        snprintf(str, len, "%s %3d", _conf_temp_names[_current_page-1], get_selected_configuration_temperature());
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

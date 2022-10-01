#ifndef PERSISTENT_CONFIGURATION_HPP
#define PERSISTENT_CONFIGURATION_HPP

namespace config {
    struct temperatures{
        int high1;
        int low1;
        int high2;
        int low2;
    };
    void load(temperatures &t);
    void store(const temperatures &t);
}

#endif // PERSISTENT_CONFIGURATION_HPP

// just a dummy file, to include, telling platform io to include
// this folder :)

#include <bsp.hpp>
#include <EEPROM.h>

template< typename T > T &memory_get( int idx, T &t ){
    return EEPROM.get(idx, t);
}
template< typename T > const T &memory_put( int idx, const T &t ){
    return EEPROM.put(idx, t);
}

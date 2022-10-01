#include <bsp_ardu.hpp>
#include <CRC.h>
#include <PersistentConfiguration.hpp>


void config::load(config::temperatures &t) {
  uint8_t crcRead;
  memory_get(0, t);
  memory_get(sizeof(t), crcRead);
  uint8_t crcCalc = crc8((uint8_t*)&t, sizeof(t));
  if(crcCalc != crcRead){
    t.high1=82;
    t.low1=80;
    t.high2=80;
    t.low2=75;
  }
}
void config::store(const config::temperatures t) {
  uint8_t crcCalc = crc8((uint8_t*)&t, sizeof(t));
  memory_put(0, t);
  memory_put(sizeof(t), crcCalc);
}

# JBC

A controller for boiling down juice using Arduino Nano and PlatformIO.

# Getting started

1. Install `pio` from PlatformIO

2. Build and flash the software to your Nano `pio run -e uno -t upload`

3. Check drivers/bsp/bsp_ardu.cpp for hardware setup, you need

   * Arduino Nano
   * Immersion Heater controllable from Arduino
   * PT-1000 temperature sensor
   * LCD display 
   * 3 buttons

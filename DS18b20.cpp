#include "DS18b20.h"


DS18b20::DS18b20(int pin) {
  ds = new OneWire(pin);
  getDeviceAddress();
}

byte DS18b20::getDeviceAddress() {
  byte i;
  while(ds->search(addr)) {
    // a check to make sure that what we read is correct.
    if ( OneWire::crc8(addr, 7) != addr[7]) {
        return 0;
    }
  }
  ds->reset_search();
  return 1;
}

float DS18b20::GetTemp() {
  // Select device
  
  // Write temperature conversion command

  // Read data

  return 6.2; // Test output
}


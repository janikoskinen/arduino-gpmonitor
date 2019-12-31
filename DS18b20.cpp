#include "DS18b20.h"

#define DEBUG
#include "debug.h"


void static printAddress(byte* addr) {
  DBG("Address: ");
  for (int i = 0 ; i < 8 ; i++) {
    if (addr[i] < 16)
      DBG('0');
    DBG(addr[i], HEX);
    DBG(' ');
  }
  DBGLN("");
}


DS18b20::DS18b20(int pin) {
  ds = new OneWire(pin);
  getDeviceAddress();
  DBG("Found @ ");
  printAddress(addr);
  delay(250);
}

byte DS18b20::getDeviceAddress() {
  byte i;
  while(ds->search(addr)) {
    // a check to make sure that what we read is correct.
    if ( OneWire::crc8(addr, 7) != addr[7]) {
        ds->reset_search();
        return 0;
    }
  }
  ds->reset_search();
  return 1;
}

float DS18b20::GetTemp() {
  // Select device (in case if other devices will be someday used)
  ds->reset();
  ds->select(addr);

  // Write temperature conversion command
  ds->write(0x44, 1);
  delay(770);

  // Read data
  ds->reset();
  ds->select(addr);
  ds->write(0xbe);

  byte d[9];
  for (int i = 0 ; i < 9 ; i++) {
    d[i] = ds->read();
    //DBG(d[i], HEX);
    //DBG(" ");
  }
  int value = int(d[1] << 8) | d[0];
  float retvalue = (float)(value);
  return retvalue / 16;
}




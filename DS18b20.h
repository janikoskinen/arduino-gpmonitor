#ifndef _DS18b20_H_
#define _DS18b20_H_



#include <OneWire.h>


class DS18b20 {
 private:
  byte addr[8];
  OneWire* ds;
  byte getDeviceAddress();

 public:
  DS18b20(int pin);
  float GetTemp();
};


#endif

#include "DS18b20.h"

//#define PROD

#define SERIAL_SPEED  115200
#define DS_PIN        2


// Debug print definitions
#ifndef PROD
  #define DBG(A, ...) Serial.print(A, ##__VA_ARGS__)
  #define DBGLN(A) Serial.println(A)
#else
  #define DBG(A, ...)
  #define DBGLN(A)
#endif


DS18b20 ds(2);


void printAddress(byte* addr) {
    for (int i = 0 ; i < 8 ; i++) {
    if (addr[i] < 16)
      DBG('0');
    DBG(addr[i], HEX);
    DBG(' ');
  }
  DBGLN("");
}


void setup(void) {
  Serial.begin(SERIAL_SPEED);
  //ds = new ds(DS_PIN);
}

void loop(void) {
  delay(5000);
  float temp = ds.GetTemp();
  DBG("Temperature: ");
  DBGLN(temp);
}


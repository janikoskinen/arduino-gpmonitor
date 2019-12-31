#include "DS18b20.h"

// Define serial debug printing (before include!)
#define DEBUG
#include "debug.h"


#define SERIAL_SPEED  115200
#define DS_PIN        11


// Temperature module
DS18b20* ds;


void setup(void) {
  Serial.begin(SERIAL_SPEED);
  ds = new DS18b20(DS_PIN);
}

void loop(void) {
  delay(2000);
  float temp = ds->GetTemp();
  DBG("Temperature: ");
  DBGLN(temp);
}


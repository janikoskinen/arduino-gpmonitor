#include "DS18b20.h"

// Define serial debug printing (before include!)
#define DEBUG
#include "debug.h"


#define SERIAL_SPEED  115200
#define DS_PIN        11

#define INT_PIN       2
#define INT_IGNORE    20

// Temperature module
DS18b20* ds;

unsigned static long last_interrupt = 0;


/*
 * *********
 * * SETUP * 
 * *********
 */
void setup(void) {
  // Serial port
  Serial.begin(SERIAL_SPEED);

  // DS temperature sensor
  ds = new DS18b20(DS_PIN);

  // Set interrupt on pin state change
  pinMode(INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), pinChanged, CHANGE);
}


/*
 * ********
 * * LOOP *
 * ********
 */
void loop(void) {
  delay(2000);
  float temp = ds->GetTemp();
  DBG("Temperature: ");
  DBGLN(temp);
}


/*
 * *************
 * * Interrupt *
 * *************
 */
void pinChanged() {
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt > INT_IGNORE) {
    delay(INT_IGNORE/2);
    DBG("Pin changed to: ");
    DBGLN(digitalRead(INT_PIN));
  }
  last_interrupt = interrupt_time;
}

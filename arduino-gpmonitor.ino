#include "DS18b20.h"

// Define serial debug printing (before include!)
//#define DEBUG
#include "debug.h"


#define SERIAL_SPEED  115200
#define SERIAL_BUF_LEN  128
#define DS_PIN        11

#define INT_PIN       2
#define INT_IGNORE    10

// Temperature module
DS18b20* ds;

// Serial buffer
char sbuffer[SERIAL_BUF_LEN];


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


// *** SERIAL FUNCTIONS ***

// Reads data from serial port and returns amount of chars excluding newline.
int read_from_serial(char* sbuf) {
  int index = 0;
  char last = 0;
  while (index < SERIAL_BUF_LEN && last != 13) {
    while (Serial.peek() == -1) {
      delay(10);
    }
    last = (char)Serial.read();
    sbuf[index++] = last;      
  }
  
  return index;
  // Read newline (from peek())
  //sbuf[index] = (char)Serial.read();
  //return index;
}

void send_response(char* msg) {
  Serial.println(msg);
}

void process_command(char* sbuf) {
  // TODO: Continue here!
  //Serial.println(sbuf);
  if (sbuf[0] == 'C' && sbuf[1] == ':') {
    // Interpret request
    char cmd = sbuf[2];
    char param = sbuf[3];
    switch(cmd) {
      case 'T':
      float temp = ds->GetTemp();
      dtostrf(temp, 4, 2, sbuffer);
      send_response(sbuffer);
      break;
      default:
      send_response("ERROR");
      break;
    }
  } else {
    send_response("Unknown command");
  }
}

/*
 * ********
 * * LOOP *
 * ********
 */
void loop(void) {
  /*
  delay(2000);
  float temp = ds->GetTemp();
  DBG("Temperature: ");
  DBGLN(temp);
  */
  // Check for command
  if (Serial.available() > 0) {
    int r = read_from_serial(sbuffer);
    sbuffer[r] = 0;
    process_command(sbuffer);

  } else {
    // Check anything that may cause spontaneous message !
    delay(100);
  }
}


/*
 * *************
 * * Interrupt *
 * *************
 */
void pinChanged() {
  noInterrupts();
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt > INT_IGNORE) {
    delay(INT_IGNORE*10);
    char buf[20];
    sprintf(buf, "Pin changed to: %d", digitalRead(INT_PIN));
    send_response(buf);
    //send_response("Pin changed to: ");
    //send_response(digitalRead(INT_PIN));
  }
  last_interrupt = interrupt_time;
  interrupts();
}

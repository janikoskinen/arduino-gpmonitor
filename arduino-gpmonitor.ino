#include "DS18b20.h"

// Define serial debug printing (before include!)
//#define DEBUG
#include "debug.h"


#define SERIAL_SPEED  115200
#define DS_PIN        11


// Temperature module
DS18b20* ds;

// Serial buffer
char sbuffer[SERIAL_BUF_LEN];


// *** SETUP ***

void setup(void) {
  Serial.begin(SERIAL_SPEED);
  ds = new DS18b20(DS_PIN);
}


// *** ADDITIONAL FUNCTIONS ***

// Reads data from serial port and returns amount of chars excluding newline.
int read_from_serial(char* sbuf) {
  int index = 0;
  while (index < SERIAL_BUF_LEN && Serial.peek() != '\n') {
    sbuf[index] = (char)Serial.read();
    index++;
  }
  // Read newline (from peek())
  sbuf[index] = (char)Serial.read();
  return index;
}

void process_command(char* sbuf) {
  // TODO: HERE!
    if (serbuf[0] == 'C' && serbuf[1] == ':') {
    // Interpret request
    char cmd = serbuf[2];
    char param = serbuf[3];
      switch(cmd) {
        case 'T':
        break;
        default:
        SendResponse("ERROR");
        break;
      }
    } else {
      // No response if no command header
    }

}

// *** THE MAIN LOOP ***

void loop(void) {
  delay(2000);
  float temp = ds->GetTemp();
  DBG("Temperature: ");
  DBGLN(temp);

  // Check for command
  if (Serial.available() > 0) {
    int r = read_from_serial(&sbuffer);


  } else {
    // Check anything that may cause spontaneous message !
    index = 0;
    delay(100);
  }
}

}


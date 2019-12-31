#ifndef _DEBUG_H_
#define _DEBUG_H_

// Debug print definitions
#ifdef DEBUG
  #define DBG(A, ...) Serial.print(A, ##__VA_ARGS__)
  #define DBGLN(A) Serial.println(A)
#else
  #define DBG(A, ...)
  #define DBGLN(A)
#endif

#endif


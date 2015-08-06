#ifndef Type_h
#define Type_h

#include "Arduino.h"
#include <avr/pgmspace.h> //PROGMEM

enum PROGMEM HW
{
  VOID,
  MOTOR,
  ARM,
  CLAMP,
  CDROM
};

typedef struct
{
  HW _hw;
  int _value;
} action;

const char* const HWstr[] = {"VOID","MOTOR","ARM","CLAMP", "CDROM"};

#endif

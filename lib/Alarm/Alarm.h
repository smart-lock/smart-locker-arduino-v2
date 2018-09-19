#ifndef Alarm_h
#define Alarm_h

#include "Arduino.h"

class Alarm
{
  public:
    Alarm(int pin);
    void printHello();
  private:
    int _pin;
};

#endif
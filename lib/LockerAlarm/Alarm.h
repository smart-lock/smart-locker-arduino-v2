#ifndef Alarm_h
#define Alarm_h

#include "Arduino.h"
#include "SystemComponent.h"

class Alarm: public ISystemComponent
{
  public:
    Alarm(const int pin);
    void printHello();

    void setup();
    void loop();
  private:
    int _pin;
    unsigned long _lastCycle;
};

#endif
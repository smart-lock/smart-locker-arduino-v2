#ifndef LockerOTA_h
#define LockerOTA_h
#include "Arduino.h"

class LockerOTA {
  public:
    LockerOTA();
    virtual void loop();
    virtual void setup();
};

#endif
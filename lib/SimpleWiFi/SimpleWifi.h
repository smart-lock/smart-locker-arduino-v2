#ifndef SimpleWifi_h
#define SimpleWifi_h

#include "Arduino.h"

class SimpleWifi {
  public:
    SimpleWifi(const char* ssid, const char* password);
    void setup();
  private:
    const char* _ssid;
    const char* _password;
};

#endif
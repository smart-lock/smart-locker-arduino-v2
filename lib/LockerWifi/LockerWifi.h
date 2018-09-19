#ifndef LockerWifi_h
#define LockerWifi_h

#include "Arduino.h"
#include <SystemComponent.h>

class LockerWifi: public ISystemComponent {
  public:
    LockerWifi(const char* ssid, const char* password);
    void setup();
    void loop();
  private:
    const char* _ssid;
    const char* _password;
};

#endif
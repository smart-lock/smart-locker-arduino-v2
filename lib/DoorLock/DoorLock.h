#ifndef DoorLock_h
#define DoorLock_h
#include <SystemComponent.h>

class DoorLock: public ISystemComponent {
  public:
    DoorLock();
    void loop();
    void setup();
};

#endif
#ifndef DoorSensor_h
#define DoorSensor_h
#include <SystemComponent.h>

class DoorSensor: public ISystemComponent {
  public:
    DoorSensor();
    void loop();
    void setup();
};

#endif
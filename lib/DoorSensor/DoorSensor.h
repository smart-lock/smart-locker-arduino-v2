#ifndef DoorSensor_h
#define DoorSensor_h
#include <SystemComponent.h>
#include <DebouncedPin.h>

class DoorSensor: public ISystemComponent {
  public:
    DoorSensor(int switchPin, void (*onOpenDoor)(void), void (*onClose)(void) );
    virtual void loop();
    virtual void setup();

    bool closed;
  private:
    int _switchPin;
};

#endif
#ifndef DoorSensor_h
#define DoorSensor_h
#include <SystemComponent.h>
#include <DebouncedPin.h>


class DoorSensorHandler {
  public:
    virtual void onOpen();
    virtual void onClose();
};

class DoorSensor: public ISystemComponent, public DebouncedPinHandler {
  public:
    DoorSensor(int switchPin);
    virtual void loop();
    virtual void setup();
    virtual void onChange(int value, bool firstCall);
    void setSensorHandler(DoorSensor *handler);
    bool closed;
  private:
    int _switchPin;
    DoorSensorHandler *_handler;
};

#endif
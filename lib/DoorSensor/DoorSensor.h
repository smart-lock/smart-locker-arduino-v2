#ifndef DoorSensor_h
#define DoorSensor_h
#include <SystemComponent.h>
#include <DebouncedPin.h>
#include <functional>
#include <DoorSensorHandler.h>

class DoorSensor: public ISystemComponent, public DebouncedPinHandler {
  public:
    DoorSensor(int switchPin, std::function<void(int value)> f);
    virtual void loop();
    virtual void setup();
    virtual void onChange(int value, bool firstCall);
    void setSensorHandler(DoorSensorHandler *handler);
    bool closed;
  private:
    int _switchPin;
    DoorSensorHandler *_handler;
    DebouncedPin *_debouncedPin;
};

#endif
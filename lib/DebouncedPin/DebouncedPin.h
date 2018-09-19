#ifndef DebouncedPin_h
#define DebouncedPin_h

#include "Arduino.h"
#include "SystemComponent.h"

class DebouncedPin: public ISystemComponent {
  public:
    DebouncedPin(int pin, unsigned long _debounceDelay, void (*onChange)(int value, bool firstCall));
    void loop();
    void setup();
  private:
    int _pin;
    int _pinValue;
    int _lastPinValue;
    bool _firstCall;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
    void(*_onChange)(int value, bool firstCall);
};

#endif
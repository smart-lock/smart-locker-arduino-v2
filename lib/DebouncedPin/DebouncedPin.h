#ifndef DebouncedPin_h
#define DebouncedPin_h

#include "Arduino.h"
#include "SystemComponent.h"
#include <DebouncedPinHandler.h>


class DebouncedPin: public ISystemComponent {
  public:
    DebouncedPin(uint8_t pin, unsigned long _debounceDelay);
    void loop();
    void setup();
    void setHandler(DebouncedPinHandler *debouncedPinhandler);
  private:
    uint8_t _pin;
    int _pinValue;
    int _lastPinValue;
    bool _firstCall;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
    DebouncedPinHandler *_handler;

};

#endif
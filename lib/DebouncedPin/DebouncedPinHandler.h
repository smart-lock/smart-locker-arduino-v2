#ifndef DebouncedPinHandler_h
#define DebouncedPinHandler_h
class DebouncedPinHandler {
  public:
    virtual void onChange(int value, bool firstCall);
};
#endif
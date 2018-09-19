#ifndef DoorSensorHandler_h
#define DoorSensorHandler_h

class DoorSensorHandler {
  public:
    virtual void onOpen();
    virtual void onClose();
};


#endif
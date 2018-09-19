#ifndef SystemComponent_h
#define SystemComponent_h

class ISystemComponent {
  public:
    virtual void setup() = 0;
    virtual void loop() = 0;
};

#endif
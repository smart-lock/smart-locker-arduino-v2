#ifndef LockerMQTT_h
#define LockerMQTT_h

#include "Arduino.h"

void reportLocked();
void reportBusy();
void reportClosed();
void reportAlarm();
void reportError(String error);
#endif
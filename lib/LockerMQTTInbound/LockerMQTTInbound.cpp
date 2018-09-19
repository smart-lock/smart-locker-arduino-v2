#include <LockerMQTTInbound.h>
#include <LockerMQTT.h>

const char CMD_CLAIM = '1';
const char CMD_UNCLAIM = '2';
const char CMD_DEACTIVATE_ALARM = '3';
const char CMD_LOCK ='4';
const char CMD_UNLOCK = '5';
const char CMD_SUDO_DEACTIVATE_ALARM ='6';

// Handlers
void handleLockCmd() {
  // if (!busy) {
    reportError("Received lock command on free locker");
    return;
  // }
  // lock();
}

void handleUnlockCmd() {
  // if (!busy) {
    reportError("Received unlock command on free locker");
    return;
  // }
  //  needs to be closed?
  // unlock();
}

void handleDeactivateAlarmCmd() {
  // if (!busy) {
    reportError("Received deactivate_alarm command on free locker");
    return;
  // }
  // deactivateAlarm();
}


void callback(char* topic, byte* payload, unsigned int length) {
  char cmd = (char)payload[0];
  switch (cmd) {
    case CMD_CLAIM:
      // claim();
      break;
    case CMD_UNCLAIM:
      Serial.println("received: unclaim");
      // unclaim();
      break;
    case CMD_DEACTIVATE_ALARM:
      Serial.println("received: deactivate_alarm");
      // handleDeactivateAlarmCmd();
      break;
    case CMD_SUDO_DEACTIVATE_ALARM:
      Serial.println("received: sudo_deactivate_alarm");
      // deactivateAlarm();
      break;
    case CMD_LOCK:
      Serial.println("received: lock");
      // handleLockCmd();
      break;
    case CMD_UNLOCK:
      Serial.println("received: unlock");
      // handleUnlockCmd();
      break;
  }
}